
#include <stdio.h>

#define MAXSIZE 100
int ig = 0;


typedef struct _stack
{
    int data[MAXSIZE];
    int top;
}Stack, pStack;

void init(Stack &s)
{
    s.top = -1;
}

int empty(Stack &s)
{
    if (-1 == s.top)
        return 1;
    else
        return 0;
}

void push(Stack &s, int x)
{
    ++s.top;
    if (s.top == MAXSIZE)
        printf("error: stack full\n");
    s.data[s.top] = x;
}

void pop(Stack &s, int &x)
{
    if (empty(s))
        printf("error: no data to fetch\n");
    x = s.data[s.top];
    --s.top;
}

int zeros(int *a, int n)
{
    int c =0;
    for (int i=0; i<n; ++i )
    {
        if (0 == a[i])
            ++c;
    }
    return c;
}

Stack copy(Stack &s)
{
    Stack t;
    t.top = s.top;
    for (int i=0; i<=s.top; ++i)
    {
        t.data[i] = s.data[i];
    }
    return t;
}

void possible_out(int *in, Stack s, int *out, int n)
{
    if ( zeros(out, n) == 0 )
    {
        ++ig;
        printf("%d: ", ig);
        for (int i=0; i<n; ++i)
        {
            printf("%d ", out[i]);
        }
        printf("\n");
        return;
    }

    int x, i;
    
    /*
    Stack scp;
    scp.top = s.top;
    if (!empty(s))
    {
        for(i=0; i<=s.top; scp.data[i]=s.data[i], ++i);
    }
    */
 
    if ( zeros(in, n) < n )
    {
        int outcp[n], incp[n];
        for (i=0; i<n; outcp[i]=out[i], incp[i]=in[i], ++i);
        Stack scp = copy(s);  
        
        for (i=0; i<n && incp[i]==0; ++i);
        x = incp[i];
        incp[i] = 0;
        push(scp, x);
        possible_out( incp, scp, outcp, n );
    }
   

    if (!empty(s))
    {
        int outcp[n], incp[n];
        for (i=0; i<n; outcp[i]=out[i], incp[i]=in[i], ++i);
        Stack scp = copy(s);

        pop(scp, x);
        for (i=0; i<n && outcp[i]!=0; ++i);
        outcp[i] = x;
    
        possible_out( incp, scp, outcp, n );
    }
}

int main()
{
    Stack s;
    init(s);
    
    int i, x;
    int n = 9;
    int in[n];
    int out[n];
    
    for (i=1; i<=n; in[i-1]=i, ++i);
    for (i=1; i<=n; out[i-1]=0, ++i);

    possible_out(in, s, out, n);

    /*
    for (i=0; i<n; ++i)
    {
        push(s, i*i);
    }
    Stack t = copy(s);
    while (!empty(t))
    {
        int e;
        pop(t, e);
        printf("%d ", e);
    }
    printf("\n");
    */
}


