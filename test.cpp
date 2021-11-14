#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;
//No need to use array
//int buf[1000];


int main()
{
    int n;
    priority_queue<int, greater<int>, vector<int> > q;
    while (scanf("%d", &n) != EOF)
    {
        //Important, make sure q is empty every time
        while (!q.empty())
            q.pop();
        for (int i = 0; i < n; i++)
        {
            int x;
            scanf("%d",&x);
            q.push(x);
        }
        //The final weighted path length
        int res = 0;
        while (q.size() != 1)
        {
            int l_min = q.top();
            q.pop();
            int r_min = q.top();
            q.pop();
            int sum;
            sum = l_min + r_min;
            res += sum;
            q.push(sum);
        }
        printf("%d\n",res);


    }
    return 0;
}
