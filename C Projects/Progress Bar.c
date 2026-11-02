#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define sleep_ms(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms) * 1000)
#endif

#define BAR_WIDTH 40

void print_progress(int percent) {
    int filled = percent * BAR_WIDTH / 100;

    printf("\r[");
    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i < filled)
            printf("#");
        else
            printf("-");
    }
    printf("] %3d%%", percent);
    fflush(stdout);
}

int main(void) {
    printf("Processing...\n");

    for (int i = 0; i <= 100; i++) {
        print_progress(i);
        sleep_ms(50);   
    }

    printf("\nDone!\n");
    return 0;
}