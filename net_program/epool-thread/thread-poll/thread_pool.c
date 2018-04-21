/*************************************************************************
	> File Name: thread_pool.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月14日 星期六 22时27分10秒
 ************************************************************************/

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

/*线程池中所有运行和等待的任务都是一个CThread_worker
 * 由于所有任务都在链表里，所以是一个链表结构
 */
typedef struct worker
{
	/*回调函数，任务运行时会调用次函数*/
	 void *(*process)(void *arg);     //返回值为指针的函数指针
	 void *arg;                       //回调函数的参数
	 struct worker *next;
} CThread_worker;

/*线程池结构*/
typedef struct 
{
	pthread_mutex_t queue_lock;
	pthread_cond_t  queue_ready;

	/*链表结构，线程池中所有的等待任务*/
	CThread_worker *queue_head;

	/*是否销毁线程池*/
	int shutdown;
	pthread_t *threadid;
	/*线程池中允许的活动线程数目*/
	int max_thread_num;
	/*当前等待队列的任务数目*/
	int cur_queue_size;
} CThread_pool;

int pool_add_worker(void *(process)(void *arg), void *arg);
void *thread_routine(void *arg);

//共享资源
static CThread_pool *pool = NULL;

//初始化线程池
void pool_init(int max_thread_num)
{
	pool = (CThread_pool *)malloc(sizeof(CThread_pool));

	pthread_mutex_init(&(pool->queue_lock), NULL);
	pthread_cond_init(&(pool->queue_ready), NULL);

	pool->queue_head = NULL;

	pool->max_thread_num = max_thread_num;
	pool->cur_queue_size = 0;

	pool->shutdown = 0;

	pool->threadid = (pthread_t *)malloc(max_thread_num * sizeof(pthread_t));
	int i = 0;
	for (i = 0; i < max_thread_num; i++)
	{
		pthread_create(&(pool->threadid[i]), NULL, thread_routine, NULL);
	}
}

void *thread_routine(void *arg)
{
	printf("strating thread %lu\n", pthread_self());

	while(1)
	{
		pthread_mutex_lock(&(pool->queue_lock));
		/*如果等待线程为0并且不销毁线程池，则处于阻塞状态；
		 * 注意pthread_cond_wait是一个原子操作，等待前会解锁，
		 * 唤醒后会加锁
		*/
		while(pool->cur_queue_size == 0 && !pool->shutdown)
		{
			printf("thread %lu is waiting\n", pthread_self());
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
		}

		/*线程池要销毁*/
		if (pool->shutdown)
		{
			/*遇到break, continue, return等跳转语句，千万不要忘记先解锁*/
			pthread_mutex_unlock(&(pool->queue_lock));
			printf("thread %lu will exit.\n", pthread_self());
			pthread_exit(NULL);
		}

		printf("thread %lu is starting to work\n", pthread_self());

		//assert用于调试
		assert(pool->cur_queue_size != 0);
		assert(pool->queue_head != NULL);

		/*等待队列长度减去1,并取出链表中的头元素*/
		pool->cur_queue_size--;
		CThread_worker *worker = pool->queue_head;
		pool->queue_head = worker->next;
		pthread_mutex_unlock(&(pool->queue_lock));

		/*调用回调函数，执行任务*/
		(*(worker->process))(worker->arg);
		free(worker);
		worker = NULL;
	}

	pthread_exit(NULL);
}

/*向线程池中添加任务*/
int pool_add_worker(void *(*process)(void *arg), void *arg)
{
	printf("add worker is %d\n", *(int *)arg);
	/*构造一个新任务*/
	CThread_worker *newworking = (CThread_worker *)malloc(sizeof(CThread_worker));
	newworking->process = process;
	newworking->arg = arg;
	newworking->next = NULL;

	pthread_mutex_lock(&(pool->queue_lock));
	/*将任务加到等待队列中*/
	CThread_worker *member = pool->queue_head;
	if (member != NULL)
	{
		while (member->next != NULL)
		{
			member = member->next;
		}
		member->next = newworking;
	}
	else
	{
		pool->queue_head = newworking;
	}

	assert(pool->queue_head != NULL);

	pool->cur_queue_size++;
	pthread_mutex_unlock(&(pool->queue_lock));

	/*等待队列中有任务了，唤醒一个等待线程，
	 * 注意所有的线程都在忙碌，这句话就不会起作用
	*/
	pthread_cond_signal(&(pool->queue_ready));
	return 0;
}

void *myprocess(void *arg)
{
	printf("thread is %lu, working on task %d\n", pthread_self(), *(int *)arg);
	sleep(1);        /*休息1秒，延长任务执行时间*/
	return NULL;
}

/*销毁线程池，等待队列中的任务不会再执行，但是正在运行的线程会一直把任务运行完后退出*/
int pool_destroy()
{
	if (pool->shutdown)
	      return -1;         /*防止2次调用*/
	pool->shutdown = 1;

	/*唤醒所有等待的线程，线程池要销毁*/
	pthread_cond_broadcast(&(pool->queue_ready));

	/*阻塞等待线程退出，否则就会编程僵尸进程*/
	int i;
	for (i = 0; i < pool->max_thread_num; i++)
	      pthread_join(pool->threadid[i], NULL);
	free(pool->threadid);

	/*销毁等待队列*/
	CThread_worker *head = NULL;
	while (pool->queue_head != NULL)
	{
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	/*条件变量和互斥量也要销毁*/
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	free(pool);
	/*销毁指针置空*/
	pool = NULL;
	printf("thread pool destroy finish!\n");
	return 0;
}

int main(int argc, char *argv[])
{
	pool_init(3);               /*线程池中最多有3个线程*/

	/*连续向池中投放10个任务*/
 	int *workingnum = (int *)malloc(sizeof(int) * 10);
	int i;
	for (i = 0; i < 10; i++)
	{
		workingnum[i] = i;
		pool_add_worker(myprocess, &workingnum[i]);
	}

	/*等待所有的任务完成*/
	//sleep(5);

	/*销毁线程池*/
	pool_destroy();

	free(workingnum);
	return 0;
}
