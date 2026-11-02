#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_ONE_SECOND() Sleep(1000)
#else
    #include <unistd.h>
    #define SLEEP_ONE_SECOND() sleep(1)
#endif

int main(int argc, char *argv[])
{
    int use12Hour = (argc > 1 && strcmp(argv[1], "-12") == 0);
    time_t now;
    struct tm *t;
    char buffer[32];

    printf("=== DIGITAL CLOCK (press Ctrl+C to exit) ===\n\n");

    while (1) {
        now = time(NULL);          /* get current time */
        t = localtime(&now);       /* convert to local time */

        if (use12Hour)
            strftime(buffer, sizeof(buffer), "%I:%M:%S %p", t);
        else
            strftime(buffer, sizeof(buffer), "%H:%M:%S", t);

        /* \r returns to line start so the time updates in place */
        printf("\r   %s   ", buffer);
        fflush(stdout);

        SLEEP_ONE_SECOND();
    }

    return 0;
}