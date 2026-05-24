#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// semaphores
sem_t mtx;
sem_t sem_f, sem_sm, sem_nfs;

// counters
int playing_f = 0, playing_sm = 0, playing_nfs = 0;
int pending_f = 0, pending_sm = 0, pending_nfs = 0;

// 0=free 1=football 2=mario 3=nfs
int console = 0;

#define CAP_F   4
#define CAP_SM  2
#define CAP_NFS 1

void take_console_f(int n) {
    sem_wait(&mtx);
    if(console == 0 || console == 1) {
        if(playing_f < CAP_F) {
            console = 1;
            playing_f++;
            printf("[F-%d] starts  | football players active: %d\n", n, playing_f);
            sem_post(&mtx);
            return;
        }
    }
    pending_f++;
    sem_post(&mtx);
    sem_wait(&sem_f);
    sem_wait(&mtx);
    console = 1;
    playing_f++;
    printf("[F-%d] starts  | football players active: %d\n", n, playing_f);
    sem_post(&mtx);
}

void release_console_f(int n) {
    sem_wait(&mtx);
    playing_f--;
    printf("[F-%d] done    | football players active: %d\n", n, playing_f);
    if(playing_f == 0) {
        console = 0;
        if(pending_f > 0) {
            pending_f--; console = 1; sem_post(&sem_f);
        } else if(pending_sm > 0) {
            pending_sm--; console = 2; sem_post(&sem_sm);
        } else if(pending_nfs > 0) {
            pending_nfs--; console = 3; sem_post(&sem_nfs);
        }
    } else {
        if(pending_f > 0 && playing_f < CAP_F) {
            pending_f--;
            sem_post(&sem_f);
        }
    }
    sem_post(&mtx);
}

void take_console_sm(int n) {
    sem_wait(&mtx);
    if((console == 0 || console == 2) && playing_sm < CAP_SM) {
        console = 2;
        playing_sm++;
        printf("[SM-%d] starts | mario players active: %d\n", n, playing_sm);
        sem_post(&mtx);
        return;
    }
    pending_sm++;
    sem_post(&mtx);
    sem_wait(&sem_sm);
    sem_wait(&mtx);
    console = 2;
    playing_sm++;
    printf("[SM-%d] starts | mario players active: %d\n", n, playing_sm);
    sem_post(&mtx);
}

void release_console_sm(int n) {
    sem_wait(&mtx);
    playing_sm--;
    printf("[SM-%d] done   | mario players active: %d\n", n, playing_sm);
    if(playing_sm == 0) {
        console = 0;
        if(pending_sm > 0) {
            pending_sm--; console = 2; sem_post(&sem_sm);
        } else if(pending_f > 0) {
            pending_f--; console = 1; sem_post(&sem_f);
        } else if(pending_nfs > 0) {
            pending_nfs--; console = 3; sem_post(&sem_nfs);
        }
    } else if(pending_sm > 0 && playing_sm < CAP_SM) {
        pending_sm--;
        sem_post(&sem_sm);
    }
    sem_post(&mtx);
}

void take_console_nfs(int n) {
    sem_wait(&mtx);
    if((console == 0 || console == 3) && playing_nfs < CAP_NFS) {
        console = 3;
        playing_nfs++;
        printf("[NFS-%d] starts | nfs players active: %d\n", n, playing_nfs);
        sem_post(&mtx);
        return;
    }
    pending_nfs++;
    sem_post(&mtx);
    sem_wait(&sem_nfs);
    sem_wait(&mtx);
    console = 3;
    playing_nfs++;
    printf("[NFS-%d] starts | nfs players active: %d\n", n, playing_nfs);
    sem_post(&mtx);
}

void release_console_nfs(int n) {
    sem_wait(&mtx);
    playing_nfs--;
    printf("[NFS-%d] done   | nfs players active: %d\n", n, playing_nfs);
    if(playing_nfs == 0) {
        console = 0;
        if(pending_nfs > 0) {
            pending_nfs--; console = 3; sem_post(&sem_nfs);
        } else if(pending_f > 0) {
            pending_f--; console = 1; sem_post(&sem_f);
        } else if(pending_sm > 0) {
            pending_sm--; console = 2; sem_post(&sem_sm);
        }
    }
    sem_post(&mtx);
}

void* football(void* arg) {
    int id = *((int*)arg);
    free(arg);
    printf("[F-%d] waiting\n", id);
    take_console_f(id);
    sleep(rand()%3+1);
    release_console_f(id);
    return NULL;
}

void* supermario(void* arg) {
    int id = *((int*)arg);
    free(arg);
    printf("[SM-%d] waiting\n", id);
    take_console_sm(id);
    sleep(rand()%3+1);
    release_console_sm(id);
    return NULL;
}

void* needforspeed(void* arg) {
    int id = *((int*)arg);
    free(arg);
    printf("[NFS-%d] waiting\n", id);
    take_console_nfs(id);
    sleep(rand()%3+1);
    release_console_nfs(id);
    return NULL;
}

int main() {
    srand(time(NULL));

    sem_init(&mtx, 0, 1);
    sem_init(&sem_f, 0, 0);
    sem_init(&sem_sm, 0, 0);
    sem_init(&sem_nfs, 0, 0);

    pthread_t t[16];
    int idx = 0, i, *p;

    for(i=0; i<8; i++) {
        p = malloc(sizeof(int)); *p=i;
        pthread_create(&t[idx++], NULL, football, p);
    }
    for(i=0; i<4; i++) {
        p = malloc(sizeof(int)); *p=i;
        pthread_create(&t[idx++], NULL, supermario, p);
    }
    for(i=0; i<4; i++) {
        p = malloc(sizeof(int)); *p=i;
        pthread_create(&t[idx++], NULL, needforspeed, p);
    }

    for(i=0; i<16; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&mtx);
    sem_destroy(&sem_f);
    sem_destroy(&sem_sm);
    sem_destroy(&sem_nfs);

    printf("session over.\n");
    return 0;
}
