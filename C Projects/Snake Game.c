/*
 * Snake Game in C (terminal, cross-platform: Windows / Linux / macOS)
 * Controls: W A S D or Arrow keys to move, Q to quit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <sys/select.h>
#endif

#define WIDTH   40
#define HEIGHT  20
#define MAX_LEN (WIDTH * HEIGHT)

typedef struct { int x, y; } Point;

typedef struct {
    Point body[MAX_LEN];
    int   length;
    int   dx, dy;
} Snake;

#ifndef _WIN32
static struct termios orig_term;
#endif

static void restore_terminal(void)
{
    printf("\033[?25h");           
    fflush(stdout);
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
#endif
}

static void init_terminal(void)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | 0x0004);   
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_term);
    raw = orig_term;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
#endif
    atexit(restore_terminal);
    printf("\033[2J\033[?25l");     
}

static void delay_ms(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static int key_pressed(void)
{
#ifdef _WIN32
    return _kbhit();
#else
    fd_set fds;
    struct timeval tv = {0, 0};
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
#endif
}

/* Reads one key and normalises it to 'w','a','s','d','q','r' (or 0) */
static int read_key(void)
{
#ifdef _WIN32
    int c = _getch();
    if (c == 0 || c == 224) {
        switch (_getch()) {
            case 72: return 'w';
            case 80: return 's';
            case 75: return 'a';
            case 77: return 'd';
        }
        return 0;
    }
#else
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return 0;
    if (c == 27) {                          /* escape sequence: arrows */
        unsigned char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return 0;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return 0;
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 'w';
                case 'B': return 's';
                case 'D': return 'a';
                case 'C': return 'd';
            }
        }
        return 0;
    }
#endif
    if (c >= 'A' && c <= 'Z') c += 32;
    switch (c) {
        case 'w': case 'a': case 's': case 'd': case 'q': case 'r':
            return c;
    }
    return 0;
}


static int on_snake(const Snake *s, int x, int y)
{
    for (int i = 0; i < s->length; i++)
        if (s->body[i].x == x && s->body[i].y == y)
            return 1;
    return 0;
}

static Point spawn_food(const Snake *s)
{
    Point f;
    do {
        f.x = rand() % WIDTH;
        f.y = rand() % HEIGHT;
    } while (on_snake(s, f.x, f.y));
    return f;
}

static void reset_game(Snake *s, Point *food, int *score)
{
    s->length  = 3;
    s->dx      = 1;
    s->dy      = 0;
    for (int i = 0; i < s->length; i++) {
        s->body[i].x = WIDTH / 2 - i;
        s->body[i].y = HEIGHT / 2;
    }
    *food  = spawn_food(s);
    *score = 0;
}

static void draw(const Snake *s, Point food, int score, int high)
{
    static char buf[(WIDTH + 3) * (HEIGHT + 2) + 256];
    char *p = buf;

    p += sprintf(p, "\033[H");           /* cursor to top-left */
    p += sprintf(p, "  SNAKE   Score: %-4d  High: %-4d  (WASD/Arrows, Q=quit)\n", score, high);

    for (int i = 0; i < WIDTH + 2; i++) *p++ = '#';
    *p++ = '\n';

    for (int y = 0; y < HEIGHT; y++) {
        *p++ = '#';
        for (int x = 0; x < WIDTH; x++) {
            char ch = ' ';
            if (x == food.x && y == food.y)             ch = '*';
            else if (x == s->body[0].x && y == s->body[0].y) ch = 'O';
            else if (on_snake(s, x, y))                 ch = 'o';
            *p++ = ch;
        }
        *p++ = '#';
        *p++ = '\n';
    }

    for (int i = 0; i < WIDTH + 2; i++) *p++ = '#';
    *p++ = '\n';
    *p = '\0';

    fputs(buf, stdout);
    fflush(stdout);
}

int main(void)
{
    Snake snake;
    Point food;
    int score = 0, high = 0;

    srand((unsigned)time(NULL));
    init_terminal();
    reset_game(&snake, &food, &score);

    for (;;) {
        while (key_pressed()) {
            int k = read_key();
            if (k == 'q') return 0;
            if (k == 'w' && snake.dy !=  1) { snake.dx =  0; snake.dy = -1; }
            if (k == 's' && snake.dy != -1) { snake.dx =  0; snake.dy =  1; }
            if (k == 'a' && snake.dx !=  1) { snake.dx = -1; snake.dy =  0; }
            if (k == 'd' && snake.dx != -1) { snake.dx =  1; snake.dy =  0; }
        }

        
        Point head = { snake.body[0].x + snake.dx, snake.body[0].y + snake.dy };

        int dead = (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT);
        if (!dead) {
            /* tail will move away this tick, so ignore it unless we grow */
            int check_len = snake.length - 1;
            for (int i = 0; i < check_len; i++)
                if (snake.body[i].x == head.x && snake.body[i].y == head.y)
                    dead = 1;
        }

        if (dead) {
            if (score > high) high = score;
            draw(&snake, food, score, high);
            printf("\n  GAME OVER! Final score: %d\n  Press R to restart or Q to quit.\n", score);
            fflush(stdout);

            int choice = 0;
            while (!choice) {
                if (key_pressed()) {
                    int k = read_key();
                    if (k == 'q') return 0;
                    if (k == 'r') choice = 1;
                }
                delay_ms(50);
            }
            printf("\033[2J");
            reset_game(&snake, &food, &score);
            continue;
        }

        int ate = (head.x == food.x && head.y == food.y);
        if (ate && snake.length < MAX_LEN) snake.length++;

        for (int i = snake.length - 1; i > 0; i--)
            snake.body[i] = snake.body[i - 1];
        snake.body[0] = head;

        if (ate) {
            score += 10;
            if (score > high) high = score;
            food = spawn_food(&snake);
        }
        draw(&snake, food, score, high);

        int speed = 140 - (score / 10) * 4;
        if (speed < 50) speed = 50;
        if (snake.dy != 0) speed += speed / 3;
        delay_ms(speed);
    }
}