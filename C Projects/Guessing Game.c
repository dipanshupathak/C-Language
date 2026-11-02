/*
 * Number Guessing Game in C
 * -------------------------
 * Features:
 *  - 3 difficulty levels (Easy / Medium / Hard)
 *  - Limited attempts with hot/cold hints
 *  - Score based on attempts left
 *  - Persistent high score saved in highscore.txt
 *  - Safe input validation (letters won't crash it)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HIGHSCORE_FILE "highscore.txt"

typedef struct {
    const char *name;
    int max_number;
    int max_attempts;
    int multiplier;
} Difficulty;

static const Difficulty LEVELS[] = {
    {"Easy",   50,  10, 10},
    {"Medium", 100,  7, 20},
    {"Hard",   500,  9, 40}
};

int read_int(int *value)
{
    char buffer[64];
    char *end;
    long n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        exit(0);                           

    n = strtol(buffer, &end, 10);
    if (end == buffer)
        return 0;                           
    while (*end == ' ' || *end == '\t')
        end++;
    if (*end != '\n' && *end != '\0')
        return 0;                           

    *value = (int)n;
    return 1;
}


int load_high_score(void)
{
    FILE *fp = fopen(HIGHSCORE_FILE, "r");
    int score = 0;

    if (fp != NULL) {
        if (fscanf(fp, "%d", &score) != 1)
            score = 0;
        fclose(fp);
    }
    return score;
}

void save_high_score(int score)
{
    FILE *fp = fopen(HIGHSCORE_FILE, "w");
    if (fp != NULL) {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}

int choose_difficulty(void)
{
    int choice;

    printf("\nChoose difficulty:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %d. %-6s (1-%d, %d attempts)\n",
               i + 1, LEVELS[i].name,
               LEVELS[i].max_number, LEVELS[i].max_attempts);
    }

    while (1) {
        printf("Your choice (1-3): ");
        if (read_int(&choice) && choice >= 1 && choice <= 3)
            return choice - 1;
        printf("Invalid choice. Please enter 1, 2 or 3.\n");
    }
}

void give_hint(int guess, int secret, int range)
{
    int diff = abs(guess - secret);

    printf(guess < secret ? "Too low! " : "Too high! ");

    if (diff <= range / 20)
        printf("(Burning hot!)\n");
    else if (diff <= range / 10)
        printf("(Very close)\n");
    else if (diff <= range / 4)
        printf("(Warm)\n");
    else
        printf("(Cold)\n");
}

int play_round(const Difficulty *level)
{
    int secret = rand() % level->max_number + 1;
    int attempts_left = level->max_attempts;
    int guess;

    printf("\nI'm thinking of a number between 1 and %d.\n", level->max_number);
    printf("You have %d attempts. Good luck!\n\n", attempts_left);

    while (attempts_left > 0) {
        printf("[%d left] Enter your guess: ", attempts_left);

        if (!read_int(&guess)) {
            printf("Please enter a valid whole number.\n");
            continue;                       /* invalid input costs no attempt */
        }
        if (guess < 1 || guess > level->max_number) {
            printf("Out of range! Pick between 1 and %d.\n", level->max_number);
            continue;
        }

        if (guess == secret) {
            int score = attempts_left * level->multiplier;
            printf("\n*** Correct! The number was %d. ***\n", secret);
            printf("You earned %d points.\n", score);
            return score;
        }

        attempts_left--;
        give_hint(guess, secret, level->max_number);
    }

    printf("\nOut of attempts! The number was %d.\n", secret);
    return 0;
}

int ask_play_again(void)
{
    char buffer[16];

    while (1) {
        printf("\nPlay again? (y/n): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            return 0;
        if (buffer[0] == 'y' || buffer[0] == 'Y')
            return 1;
        if (buffer[0] == 'n' || buffer[0] == 'N')
            return 0;
        printf("Please type y or n.\n");
    }
}

int main(void)
{
    int high_score = load_high_score();
    int total_score = 0;
    int rounds = 0, wins = 0;

    srand((unsigned int)time(NULL));

    printf("=====================================\n");
    printf("        NUMBER GUESSING GAME\n");
    printf("=====================================\n");
    printf("High score: %d\n", high_score);

    do {
        int level_index = choose_difficulty();
        int earned = play_round(&LEVELS[level_index]);

        rounds++;
        if (earned > 0)
            wins++;
        total_score += earned;

        printf("Session score: %d\n", total_score);

        if (total_score > high_score) {
            high_score = total_score;
            save_high_score(high_score);
            printf("New high score: %d!\n", high_score);
        }
    } while (ask_play_again());

    printf("\n----------- Game Summary -----------\n");
    printf("Rounds played : %d\n", rounds);
    printf("Rounds won    : %d\n", wins);
    printf("Session score : %d\n", total_score);
    printf("High score    : %d\n", high_score);
    printf("Thanks for playing!\n");

    return 0;
}