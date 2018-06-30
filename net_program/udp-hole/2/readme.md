T: 客户端通过服务器获取对方的公网IP+PORT
T: cli0向cli1发送hello world. (cli0先打通到cli1的单向洞-允许cli0发送数据到cli1)
T: cli1向cli0发送hello future.(T2隐含cli1到cli0的单向洞-允许cli1发送数据到cli0)

测试需求：一台云服务器（外网地址+PORT）,两台在不同网段的本地电脑。
