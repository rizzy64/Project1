#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t account1, account2;

void *transfer(void *arg) {
    pthread_mutex_lock(&account1);
    pthread_mutex_lock(&account2);

    printf("Transfer successful.\n");

    pthread_mutex_unlock(&account2);
    pthread_mutex_unlock(&account1);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&account1, NULL);
    pthread_mutex_init(&account2, NULL);

    pthread_create(&t1, NULL, transfer, NULL);
    pthread_create(&t2, NULL, transfer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&account1);
    pthread_mutex_destroy(&account2);

    return 0;
}
