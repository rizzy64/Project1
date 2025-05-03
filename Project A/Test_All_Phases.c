#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_PHASES 4

// Commands to run for each phase
static const char *cmds[N_PHASES] = {
    "./phase1",
    "./phase2",
    "./phase3",
    "./phase4"
};

// Thread entry: run one phases test
void *run_phase(void *arg) {
    const char *cmd = (const char *)arg;
    printf("[MASTER] Launching %s\n", cmd);
    int ret = system(cmd);
    printf("[MASTER] %s exited with status %d\n", cmd, ret);
    return NULL;
}

int main(void) {
    pthread_t threads[N_PHASES];

    // 1) Spawn one thread per phase
    for (int i = 0; i < N_PHASES; i++) {
        if (pthread_create(&threads[i], NULL, run_phase, (void*)cmds[i])) {
            perror("pthread_create");
            exit(1);
        }
    }

    // 2) Wait for all to finish
    for (int i = 0; i < N_PHASES; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("[MASTER] All phases complete.\n");
    return 0;