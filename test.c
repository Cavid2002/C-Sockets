#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

typedef struct{
    int count;
    const char* msg;
} argum;

void* doo_work(void* args){
    argum* parg = (argum*)args;
    for(int i = 0; i < parg->count; i++){
        fprintf(stdout,"%d -> %s\n", i, parg->msg);
        sleep(2);
    }
}

int main(int argc, char* argv[]){
    pthread_t t1;
    argum first = {.count = 5, .msg = "Thread 1"};
    argum second = {.count = 10, .msg = "Thread 2"};
    pthread_create(&t1, NULL, doo_work, &first);
    int a;
    scanf("%d",&a);
    printf("Res: %d\n",a);
    pthread_join(t1,NULL);
}