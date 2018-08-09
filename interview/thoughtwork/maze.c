#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sds.h"

typedef struct point{
    int x;
    int y;
}Point;

typedef struct road{
    Point cellX;
    Point cellY;
}Road;

typedef struct maze{
    int row;
    int col;
    int roadNum;
    char **arr;
}Maze;

void freeMaze(Maze *M, Road **R);
void printMaze(const Maze *M);

void RobotGo(const Maze *M)
{
    Point Robot, tmp;
    SDS S;
    int i = 0, flag = 0, len = 0;

    initSDS(&S);
    getSDS(&S);

    len = S.len - 1;
    S.data[len] = '\0';

    sscanf(S.data, "%d,%d", &Robot.x, &Robot.y);

    Robot.x = Robot.x * 2 + 1; 
    Robot.y = Robot.y * 2 + 1; 

    M->arr[Robot.x][Robot.y] = '*';
    printMaze(M);
    for(i = 4; i < len; ++i)
    {
        tmp = Robot;
        if('W' == S.data[i])
        {
            flag = 0;
            Robot.x -= 1;
            printf("Robot:我要试着向上走\n");
        }
        if('S' == S.data[i])
        {
            flag = 1;
            Robot.x += 1;
            printf("Robot:我要试着向下走\n");
        }
        if('A' == S.data[i])
        {
            flag = 2;
            Robot.y -= 1;
            printf("Robot:我要试着向左走\n");
        }
        if('D' == S.data[i])
        {
            flag = 3;
            Robot.y += 1;
            printf("Robot:我要试着向右走\n");
        }

        if('W' == M->arr[Robot.x][Robot.y])
        {
            Robot = tmp;
            if(0 == flag)
            {
                while('W' == S.data[++i] && i < len){}
                
                if(i == len)
                {
                    printf("Robot:我向上走遇到墙了,无路可走啦\n");
                }
                else
                {
                    if('S' == S.data[i])
                    {
                        printf("Robot:我向上走遇到了墙!\n");
                    }
                    if('A' == S.data[i])
                    {
                        printf("Robot:我向上走遇到了墙!\n");
                    }
                    if('D' == S.data[i])
                    {
                        printf("Robot:我向上走遇到了墙!\n");
                    }
                }
                i -= 1;
            }
            if(1 == flag)
            {
                while('S' == S.data[++i] && i < len){}
                
                if(i == len)
                {
                    printf("Robot:我向下走遇到墙了,无路可走啦\n");
                }
                else
                {
                    if('W' == S.data[i])
                    {
                        printf("Robot:我向下走遇到了墙!\n");
                    }
                    if('A' == S.data[i])
                    {
                        printf("Robot:我向下走遇到了墙!\n");
                    }
                    if('D' == S.data[i])
                    {
                        printf("Robot:我向下走遇到了墙! \n");
                    }
                }
                i -= 1;
            }
            if(2 == flag)
            {
                while('A' == S.data[++i] && i < len){}
                
                if(i == len)
                {
                    printf("Robot:我向左走遇到墙了,无路可走啦\n");
                }
                else
                {
                    if('W' == S.data[i])
                    {
                        printf("Robot:我向左走遇到了墙!\n");
                    }
                    if('S' == S.data[i])
                    {
                        printf("Robot:我向左走遇到了墙!\n");
                    }
                    if('D' == S.data[i])
                    {
                        printf("Robot:我向左走遇到了墙!\n");
                    }
                }
                i -= 1;
            }
            if(3 == flag)
            {
                while('D' == S.data[++i] && i < len){}
                
                if(i == len)
                {
                    printf("Robot:我向右走遇到墙了,无路可走啦\n");
                }
                else
                {
                    if('W' == S.data[i])
                    {
                        printf("Robot:我向右走遇到了墙!\n");
                    }
                    if('S' == S.data[i])
                    {
                        printf("Robot:我向右走遇到了墙!\n");
                    }
                    if('A' == S.data[i])
                    {
                        printf("Robot:我向右走遇到了墙!\n");
                    }
                }
                i -= 1;
            }
        }
        else
        {
            M->arr[tmp.x][tmp.y] = 'R';
            M->arr[Robot.x][Robot.y] = '*';
            printMaze(M);
        }
    }
    freeSDS(&S);
}

/*初始化可连通的道路网格*/
int initRoad(Road **R, int maxNum)
{
    assert(NULL == *R);
    
    SDS S;
    char tmp, str[SDS_LEN];
    int roadNum = 0, i = 0, m = 0;
   
    initSDS(&S);
    getSDS(&S);
    roadNum = S.len / 8;
    if(roadNum > maxNum)
    {
        printf(":38 Number out of range.\n");

        return -1;
    }

    *R = (Road*)malloc(sizeof(Road) * roadNum);
    if(NULL == *R)
    {
        perror("malloc_road");

        return -1;
    }
    
    for(; i < roadNum; ++i)
    {
        memset(str, 0, SDS_LEN);
        memcpy(str, S.data + m, SDS_LEN - 1);
        m += strlen(str);
        sscanf(str, "%d,%d %d,%d%c", &(*R)[i].cellX.x, &(*R)[i].cellX.y, &(*R)[i].cellY.x, &(*R)[i].cellY.y, &tmp);
    }

    freeSDS(&S);

    return roadNum;
}

/*初始化迷宫*/
void initMaze(Maze *M, Road **R, int row, int col)
{
    int i = 0, j = 0;
    M->row = row * 2 + 1;
    M->col = col * 2 + 1;
    M->roadNum = 2 * row * col - row - col;
    M->arr = NULL;

    M->arr = (char**)malloc(sizeof(char*) * M->row);
    if(NULL == M->arr)
    {
        perror("malloc_row");
        exit(1);
    }
    for(; i < M->row; ++i)
    {
        M->arr[i] = (char*)malloc(sizeof(char) * M->col);
    }

    for(i = 0; i < M->row; ++i)
    {
        for(j = 0; j < M->col; ++j)
        {
            if((i%2) && (j%2))
            {
                M->arr[i][j] = 'R';
            }
            else
            {
                M->arr[i][j] = 'W';
            }
        }
    }

    if(-1 == (M->roadNum = initRoad(R, M->roadNum)))
    {
        freeMaze(M, R);
        exit(1);
    }
}

/*连通迷宫可连通的道路*/
void createMaze(Maze *M, Road *R)
{
    int i = 0, x = 0, y = 0;
    for(; i < M->roadNum; ++i)
    {
        if(0 > R[i].cellX.x || 0 > R[i].cellX.y || 0 > R[i].cellY.x || 0 > R[i].cellY.y)
        {
            printf("Invalid number format: (%d,%d %d,%d)\n", R[i].cellX.x, R[i].cellX.y, R[i].cellY.x, R[i].cellY.y);
            freeMaze(M, &R);
            exit(1);
        }
        else
        {
            x = R[i].cellX.x + R[i].cellY.x + 1;
            y = R[i].cellX.y + R[i].cellY.y + 1;
            if(0 == x || M->row - 1 == x || 0 == y || M->col -1 == y) //检查连通点是否在边框
            {
                printf("Maze format error: (%d,%d %d,%d)\n", R[i].cellX.x, R[i].cellX.y, R[i].cellY.x, R[i].cellY.y);
                freeMaze(M, &R);
                exit(1);
            }
            if(((x % 2)&&(0 == y % 2)) || ((0 == x % 2)&&(y % 2))) //检查连通点是否在正南、正北、正东、正西
            {
                M->arr[x][y] = 'R';
            }
            else
            {
                printf("Maze format error: (%d,%d %d,%d)\n", R[i].cellX.x, R[i].cellX.y, R[i].cellY.x, R[i].cellY.y);
                freeMaze(M, &R);
                exit(1);
            }
        }
    }
}

/*输出迷宫的道路连通信息*/
void printRoad(const Road *R, int roadNum)
{
    printf("Road Info:\n");
    int i = 0;
    for(; i < roadNum; ++i)
    {
        printf("(%d,%d) (%d,%d)\n", R[i].cellX.x, R[i].cellX.y, R[i].cellY.x, R[i].cellY.y);
    }
}

/*输出迷宫信息*/
void printMaze(const Maze *M)
{
    printf("Maze Info:\n");
    int i = 0, j = 0;
    for(; i < M->row; ++i)
    {
        for(j = 0; j < M->col; ++j)
        {
            printf("%c    ", M->arr[i][j]);
        }
        printf("\n");
    }
}

void freeRoad(Road **R)
{
    if(NULL != *R)
    {
        free(*R);
        R = NULL;
    }
}

void freeMaze(Maze *M, Road **R)
{
    int i = 0;
    M->row = 0;
    M->col = 0;

    freeRoad(R);
    if(NULL != M->arr)
    {
        for(; i < M->row; ++i)
        {
            free(M->arr[i]);
            M->arr[i] = NULL;
        }
        free(M->arr);
        M->arr = NULL;
    }
}

int main(int argc, char *argv[])
{
    Maze m;
    Road *r = NULL;
    int row = 0, col = 0;

    printf("Please input info of Maze:\n");
    scanf("%d %d", &row, &col);
    getchar();
    if(0 > row || 0 > col)
    {
        printf("Invalid number format.(row:%d col:%d)\n", row, col);
        return 0;
    }

    initMaze(&m, &r, row, col);
    createMaze(&m, r);
    RobotGo(&m);
    freeMaze(&m, &r);

    return 0;
}

