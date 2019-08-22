#include <iostream>
#include <memory.h>
using namespace std;

#define MAX_N 6

//这题使用贪心+回溯算法

//地图，格子中值为：0 表示street, 1 表示wall, 2 表示house
int graph[MAX_N][MAX_N];
//全局变量，表示搜索过程中最多的房子数
int maxHouse;

//初始化地图
//初始化过程中，在地图四周用墙围住，这样避免了数组边界检查，使得算法更具可读性
void InitGraph(int n)
{
    //将地图所有元素值设置为0
    memset(graph, 0, sizeof(graph));
    //最多房子数清空为0
    maxHouse = 0;

    int i;
    //地图四周加墙
    for(i=0; i<=n+1; ++i)
    {
        //第一行的墙
        graph[0][i] = 1;
        //最后一行的墙
        graph[n+1][i] = 1;
        //第一列的墙
        graph[i][0] = 1;
        //最后一列的墙
        graph[i][n+1] = 1;
    }
}

//检测当前位置<x,y>放置房子后是否会有冲突
bool NoConflict(int x, int y)
{
    int i;

    //往左检测冲突
    i = 1;
    while(true)
    {
        //找到了另一个房子，有冲突
        if(graph[x-i][y]==2)
            return false;
        //找到了墙，左方安全，退出检测
        else if(graph[x-i][y]==1)
            break;
        ++i;
    }

    //往右检测冲突
    i = 1;
    while(true)
    {
        //找到了另一个房子，有冲突
        if(graph[x+i][y]==2)
            return false;
        //找到了墙，右方安全，退出检测
        else if(graph[x+i][y]==1)
            break;
        ++i;
    }

    //往上检测冲突
    i = 1;
    while(true)
    {
        //找到了另一个房子，有冲突
        if(graph[x][y-i]==2)
            return false;
        //找到了墙，上方安全，退出检测
        else if(graph[x][y-i]==1)
            break;
        ++i;
    }

    //往下检测冲突
    i = 1;
    while(true)
    {
        //找到了另一个房子，有冲突
        if(graph[x][y+i]==2)
            return false;
        //找到了墙，下方安全，退出检测
        else if(graph[x][y+i]==1)
            break;
        ++i;
    }
    return true;
}

//求解地图中最多放置多少个房子，递归函数：采用贪心+回溯方法求解
//<startX,startY>是起始搜索位置，也就是这里往右逐行检测
//n是地图大小，houseNum是当前摆放状态的房子数目
//为了优化这里加了startY,可以不加此参数，j每次从1开始搜索
void Solve(int startX, int startY, int n, int houseNum)
{
    int i, j;
    //从起始位置逐行往右尝试摆放房子
    for(i=startX; i<=n; ++i)
    {
        for(j=startY; j<=n; ++j)
        {
            //如果当前位置<i, j>是街道，并且放置房子后没有冲突，则放房子（贪心）
            if(graph[i][j] == 0 && NoConflict(i, j))
            {
                //放置一个房子
                graph[i][j] = 2;
                //累加当前状态下房子数目
                ++houseNum;
                //如果当前房子数目大于最大房子数目，刷新最大房子数目
                if(houseNum>maxHouse)
                    maxHouse = houseNum;
                //如果j已经在最后一列，则换到下一行开始贪心搜索
                if(j==n)
                    Solve(i+1, 1, n, houseNum);
                else //否则换到下一列继续贪心搜索
                    Solve(i, j+1, n, houseNum);
                //回溯(backtracking)，因为上一个贪心位置的房子可能导致非最优解，所以需要回退
                //取消放置房子
                graph[i][j] = 0;
                //把房子数目减1
                --houseNum;
            }
        }
        //特别注意这个地方，因为已经到下一行了，所以必须将startY重置为1
        startY = 1;
    }
}
int main()
{
    int n, i, j;
    char c;
    while(true)
    {
        //读入地图大小
        cin>>n;
        if(n==0)
            break;
        //初始化地图
        InitGraph(n);
        //读入地图
        for(i=1; i<=n; ++i)
        {
            for(j=1; j<=n; ++j)
            {
                cin>>c;
                if(c=='X')
                    graph[i][j] = 1;
            }
        }
        //求解
        Solve(1, 1, n, 0);
        //打印结果
        cout<<maxHouse<<endl;
    }
    return 0;
}
