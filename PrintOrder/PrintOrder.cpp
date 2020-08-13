#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int n;
    pthread_mutex_t lock0;
    pthread_mutex_t lock1;
    pthread_mutex_t lock2;
    bool flg;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    pthread_mutex_init(&obj->lock0, NULL);
    pthread_mutex_init(&obj->lock1, NULL);
    pthread_mutex_init(&obj->lock2, NULL);

    pthread_mutex_lock(&obj->lock1);
    pthread_mutex_lock(&obj->lock2);
    obj->flg = true;
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd* obj) {
    int i = 0;
    for(i = 0; i < obj->n; i++)
    {
        pthread_mutex_lock(&obj->lock0);
        printf("0 ");
        if(obj->flg){
            pthread_mutex_unlock(&obj->lock1);
        }else{
            pthread_mutex_unlock(&obj->lock2);
        }

        obj->flg = !obj->flg;
    }    
}

void even(ZeroEvenOdd* obj) {
    int i = 0;
    for(i = 2; i <= obj->n; i+=2)
    {
        pthread_mutex_lock(&obj->lock2);
        printf("%d ", i);
        pthread_mutex_unlock(&obj->lock0);
        
    }
}

void odd(ZeroEvenOdd* obj) {
    int i = 0;
    for(i = 1; i <= obj->n; i+=2)
    {
        pthread_mutex_lock(&obj->lock1);
        printf("%d ", i);
        pthread_mutex_unlock(&obj->lock0);
        
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->lock0);
    pthread_mutex_destroy(&obj->lock0);
    pthread_mutex_destroy(&obj->lock0);
    free(obj);
}

void *PrintZero(void * arg)
{
    zero((ZeroEvenOdd *)arg);
}

void *PrintOdd(void * arg)
{
    odd((ZeroEvenOdd *)arg);
}

void *PrintEven(void * arg)
{
    even((ZeroEvenOdd *)arg);
}

int main(int argc, char const *argv[])
{
    pthread_t pid1, pid2, pid3;
    ZeroEvenOdd *num = zeroEvenOddCreate(7);
    //Create pthread
    pthread_create(&pid1, NULL, PrintZero, num);
    pthread_create(&pid2, NULL, PrintOdd, num);
    pthread_create(&pid3, NULL, PrintEven, num);

    
    while(1){
     //   sleep(1);
    }
    zeroEvenOddFree(num);  
    return 0;
}
