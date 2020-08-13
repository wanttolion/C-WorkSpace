#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _info_st
{
    int *res;
    int cnt;
    struct _info_st *nxt;
}info_st;

void my_strcpy(char *d, char *s, int len)
{
    for(int i = 0; i < len; i++)
    {
        d[i] = s[i];
    }
    d[len] = '\0';
}

int* diffWaysToCompute(char * input, int* returnSize){
    if(input == NULL || strlen(input) == 0)
    {
        *returnSize = 0;
        return NULL;
    }

    int ilen = strlen(input);

    int flag = 0;       // 计算标志，1：+，2：-，3：*

    //将子串按照符号切分
    char *lstr = (char *)calloc(ilen + 1, sizeof(char));
    char *rstr = (char *)calloc(ilen + 1, sizeof(char));

    info_st *head = NULL;       // 初始化单链表头
    int rsize = 0;              // 记录结果总数

    int mid = 0;
    while(mid < ilen)
    {
        if(input[mid] >= '0' && input[mid] <= '9')
        {
            mid++;
            continue;
        }

        flag =  input[mid] == '+'? 1 : 
                (input[mid] == '-'? 2 : 3);

        my_strcpy(lstr, input, mid);
        my_strcpy(rstr, input + mid + 1, ilen - mid - 1);

        //printf("lstr = %s, rstr = %s\n", lstr, rstr);

        int llen, rlen;
        int *lres = diffWaysToCompute(lstr, &llen);
        int *rres = diffWaysToCompute(rstr, &rlen);
/*
        printf("lres: ");
        for(int i = 0; i < llen; i++)
        {
            printf("%d   ", lres[i]);
        }
        printf("\n");

        printf("rres: ");
        for(int i = 0; i < rlen; i++)
        {
            printf("%d   ", rres[i]);
        }
        printf("\n");
*/
        int *tres = (int *)calloc(llen * rlen, sizeof(int));
        int tid = 0;
        for(int m = 0; m < llen; m++)
        {
            for(int n = 0; n < rlen; n++)
            {
                if(flag == 1)
                {
                    tres[tid++] = lres[m] + rres[n];
                }
                else if(flag == 2)
                {
                    tres[tid++] = lres[m] - rres[n];
                }
                else if(flag == 3)
                {
                    tres[tid++] = lres[m] * rres[n];
                }
            }
        }
/*
        printf("tres: ");
        for(int i = 0; i < tid; i++)
        {
            printf("%d   ", tres[i]);
        }
        printf("\n");
*/
        rsize += tid;

        info_st *cur = (info_st *)calloc(1, sizeof(info_st));
        cur->res = tres;
        cur->cnt = tid;

        cur->nxt = head;
        head = cur;

        // 开始下一次寻找
        mid++;
    }

    // 没有找到第一个计算符号
    if(flag == 0)
    {
        int *res = (int *)calloc(1, sizeof(int));
        res[0] = atoi(input);

        *returnSize = 1;
        return res;
    }

    // 将单链表重构结果
    int *res = (int *)calloc(rsize, sizeof(int));
    int rid = 0;
    info_st *cur = head;
    while (cur != NULL)
    {
        for(int i = 0; i < cur->cnt; i++)
        {
            res[rid++] = cur->res[i];
            //printf("res[%d] = %d\n", rid - 1, res[rid - 1]);
        }

        cur = cur->nxt;
    }

    

    *returnSize = rsize;
    return res;
}

int main(int argc, char const *argv[])
{
    int returnsize = 0;
    int *res;
    char input[10] = "2-1-1";
    res = diffWaysToCompute(input, &returnsize);

    printf("res: ");
    for(int i = 0; i < returnsize; i++)
    {
        printf("%d   ", res[i]);
    }
    printf("\n");
    return 0;
}
