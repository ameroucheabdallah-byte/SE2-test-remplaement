#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// each thread gets its type and number
typedef struct {
    int num;
    char* game;
} Player;

void* play(void* arg) {
    Player* p = (Player*)arg;
    printf("%s player n%d : waiting to play\n", p->game, p->num);
    int sec = rand() % 3 + 1;
    sleep(sec);
    printf("%s player n%d : finished playing\n", p->game, p->num);
    free(p);
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t th[16];
    int k = 0;

    int i;
    // football x8
    for(i = 0; i < 8; i++) {
        Player* p = malloc(sizeof(Player));
        p->num = i;
        p->game = "Football";
        pthread_create(&th[k++], NULL, play, p);
    }

    // supermario x4
    for(i = 0; i < 4; i++) {
        Player* p = malloc(sizeof(Player));
        p->num = i;
        p->game = "SuperMario";
        pthread_create(&th[k++], NULL, play, p);
    }

    // nfs x4
    for(i = 0; i < 4; i++) {
        Player* p = malloc(sizeof(Player));
        p->num = i;
        p->game = "NFS";
        pthread_create(&th[k++], NULL, play, p);
    }

    for(i = 0; i < 16; i++)
        pthread_join(th[i], NULL);

    printf("session over.\n");
    return 0;
}
