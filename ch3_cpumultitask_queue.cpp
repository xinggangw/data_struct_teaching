/*
  版权声明：本文为CSDN博主「洋__」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_34115899/article/details/79389440
*/

#include <stdio.h>
#include <string.h>
#define LEN 1000


/*
现有名称为namei且处理时间为timei的n个任务按照顺序排成一列，
CPU通过循环调度法逐一处理这些任务，每个任务最多处理q ms
(这个时间称为时间片)。如果q ms之后任务尚未处理完毕，那么该任务
将被移动至队伍最末尾，CPU随即开始处理下一个任务
    举个例子，假设q是100，然后有如下任务队列。
    A(150) -- B(80) -- C(200) -- D(200)
    首先A被处理100 ms，然后带着剩余的50 ms移动至队尾
    B(80) -- C(200) -- D(200) -- A(50)
    随后B被处理80 ms，在总计第180 ms时完成处理，从队列中消失
    C(200) -- D(200) -- A(50)
    接下来C被处理100 ms，然后带着剩余的100 ms移动至队尾。
    D(200) -- A(50) -- C(100) 
    之后同理，一直循环到处理完所有任务。
    请编写一个程序，模拟循环调度法。
输入
    输入形式如下
    n q
    name1 time1
    name2 time2
    ...
    namen timen
    第一行输入表示任务数的整数n与时间片的整数q，用一个空格隔开
    接下来n行输入各任务的信息。字符串namei与timei用一个空格隔开。
输出
    按照任务完成的先后顺序输出各任务名以及结束时间，任务名与对应结束时间用空格隔开，
    每一对任务名与结束时间占一行。
限制
    1 ≤n ≤100 000
    1 ≤q ≤1000
    1 ≤timei ≤50 000
    1 ≤字符串namei的长度 ≤10
    1 ≤timei的和 ≤1 000 000 
    
    输入示例                输出示例 
    5 100                    p2 180 
    p1 150                    p5 400
    p2 80                    p1 450
    p3 200                    p3 350
    p4 350                    p4 800
    p5 20 
*/
 
/* 代表任务的结构体 */
typedef struct pp{
    char name[100];
    int t;
} P; 
 
P Q[LEN];
int head, tail, n;
 
void enqueue(P x)
{
    Q[tail] = x;
    tail = (tail + 1) % LEN;
}
 
P dequeue()
{
    P x = Q[head];
    head = (head + 1) % LEN;
    return x;
}
 
int min(int a, int b)
{
    return a < b ? a : b;
}
 
int main()
{
    int elapsed = 0, c;
    int i, q;
    P u;
    scanf("%d %d", &n, &q);
    /* 按顺序将所有任务添加到队列 */
    for (i = 1; i <= n; ++i) {
        scanf("%s %d", Q[i].name, &Q[i].t);
    }
    head = 1;
    tail = n + 1;
    /* 模拟 */
    while ( head != tail ) {
        u = dequeue();
        c = min(u.t, q);
        u.t -= c;
        elapsed += c;
        if (u.t > 0) {
            enqueue(u);
        }
        else {
            printf("%s %d\n", u.name, elapsed);
        }
    }
    return 0;
}



