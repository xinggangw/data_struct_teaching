#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 27
#define M 100

typedef struct _huffmantree
{
    char ch;
    int weight;
    int parent,lchild,rchild;
} Huffmantree;//这种程序名称大写，利于区分

typedef struct _hfmcode//一个字母对应的码
{
    char code[M];
} Hfmcode;

void creat(Huffmantree *hfmtree, int pindu[30], int n)
{
    int i,j;

    /*下面进行结点赋值操作*/
    for(i=0; i<n; i++)
    {
        hfmtree[0].ch=' ';
        if(i>0)
        {
            hfmtree[i].ch='A'+i-1;
        }
        hfmtree[i].weight = pindu[i];
        hfmtree[i].parent = hfmtree[i].lchild = hfmtree[i].rchild = -1;
    }

    /*下面进行Huffmantree的搭建操作*/
    for(i=n; i<2*n-1; i++)
    {
        int mw1 = 1000000;
        int mi1 = -1;
        int mw2 = 1000000;
        int mi2 = -1;

        /*寻找权值最小的两个结点*/
        for(j=0; j<i; j++)//多加建一棵树，要遍历的就多一个，所以j<i
        {
            if(hfmtree[j].parent == -1)//如果该结点上面是空的
            {
                if(hfmtree[j].weight < mw1)
                {
                    mi1 = j;
                    mw1 = hfmtree[j].weight;
                }
            }
        }

        for(j=0; j<i; j++)
        {

            if( j!= mi1 && hfmtree[j].parent==-1)
            {
                if(hfmtree[j].weight < mw2)
                {
                    mi2 = j;
                    mw2 = hfmtree[j].weight;
                }
            }
        }

        //printf("min_1, %d, %d\n", mi1, hfmtree[mi1].weight);
        // printf("min_2, %d, %d\n", mi2, hfmtree[mi2].weight);

        hfmtree[i].weight= mw1 + mw2;
        hfmtree[i].parent= -1;
        hfmtree[i].lchild = mi1;
        hfmtree[i].rchild = mi2;//记录孩子结点次序
        hfmtree[mi1].parent = i;//记录双亲结点次序
        hfmtree[mi2].parent = i;
    }
}

/*先做出霍夫曼对应表，再根据要求进行对应编码*/
void hfmcoding(Huffmantree *hfmtree, Hfmcode codelist[N], int n)
{
    int i,c,p;
    for(i=0; i<n; i++)
    {
        char *s = (char *)malloc(sizeof(char) * M);

        c=i;
        p=hfmtree[c].parent;
        int num = M;
        s[num] = '\0';

        while(p!=-1)
        {
            if(hfmtree[p].lchild==c)
            {
                s[--num]='0';
            }
            else
                s[--num]='1';

            c=p;
            p=hfmtree[c].parent;
        }

        for (int j=0; num<=M; j++, num++)
            codelist[i].code[j] = s[num];//
        //for(int x=0;x<=M; ++x)
        //printf("每个字母对应的编码：%c ，%s\n",'A'+i-1,codelist[i].code[x]);

        free(s);
    }
}

int hfmdecoding(Huffmantree *hfmtree, char *decodestr, char *decodelist, int n)
{
    int root = 2*n-2;
    int length = 0, i = 0;
    while(decodestr[i])
    {
        printf("current decode char is %c\n", decodestr[i]);
        if(decodestr[i] == '0')
            root = hfmtree[root].lchild;
        else if(decodestr[i] == '1')
            root = hfmtree[root].rchild;
        else
            return 0;
        if(hfmtree[root].lchild == -1 && hfmtree[root].rchild == -1)
        {
            decodelist[length++]=hfmtree[root].ch;
            root=2*n-2;
        }
        i++;
    }
    decodelist[length]='\0';
    if(root==2*n-2)
        return 1;
    return 1;
}

int main()
{
    Huffmantree* hfmtree = (Huffmantree*)malloc((2*N-1)*sizeof(Huffmantree));

    char *codestr = "THE PTOJECT IS MY FAVORITE";
    int pindu[30]= {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
    int i;

    creat(hfmtree, pindu, N);

    Hfmcode codelist[N];//这里不需要分配内存吗？
    hfmcoding(hfmtree, codelist, N);


    for(i=0; i<N; i++)
    {
        if(codestr[i] == ' ')
            printf("%c: %s\n", codestr[i], codelist[0].code);
        else
            printf("%c: %s\n", codestr[i], codelist[codestr[i]-'A'+1].code);
    }


    char * decodestr = "1101000101011110001000101001110000100001000000110111101100011111110010100011111110011101011000001001001001101101010";
    char * decodelist = (char*)malloc(M*sizeof(char));//设置最多只能解码出M个字母

    int rtn = hfmdecoding(hfmtree, decodestr, decodelist, N);
    printf("return is %d\n", rtn);
    if(rtn)
        puts(decodelist);
    else
        printf("解码失败\n");

    return 0;
}
