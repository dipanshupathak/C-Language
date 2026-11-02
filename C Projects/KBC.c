/*
 * KAUN BANEGA CROREPATI (KBC) - Console Quiz Game in C
 * Features:
 *   - 15 questions with a prize ladder from Rs 1,000 to Rs 1 Crore
 *   - Safe levels at Question 5 (Rs 10,000) and Question 10 (Rs 3,20,000)
 *   - 3 Lifelines: 50-50, Audience Poll, Phone a Friend
 *   - Quit option to leave with the money won so far
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TOTAL 15

typedef struct {
    const char *question;
    const char *option[4];
    int answer;             
} Question;

static const long prize[TOTAL] = {
    1000, 2000, 3000, 5000, 10000,
    20000, 40000, 80000, 160000, 320000,
    640000, 1250000, 2500000, 5000000, 10000000
};

static const Question quiz[TOTAL] = {
    {"What is the capital of India?",
     {"Mumbai", "New Delhi", "Kolkata", "Chennai"}, 1},
    {"Which is the national animal of India?",
     {"Lion", "Elephant", "Tiger", "Leopard"}, 2},
    {"Who wrote the song 'Vande Mataram'?",
     {"Rabindranath Tagore", "Bankim Chandra Chatterjee", "Sarojini Naidu", "Subramania Bharati"}, 1},
    {"Which planet is known as the Red Planet?",
     {"Venus", "Jupiter", "Saturn", "Mars"}, 3},
    {"Which is the largest Indian state by area?",
     {"Madhya Pradesh", "Maharashtra", "Rajasthan", "Uttar Pradesh"}, 2},
    {"Who was the first Prime Minister of India?",
     {"Sardar Patel", "Jawaharlal Nehru", "Lal Bahadur Shastri", "Dr. Rajendra Prasad"}, 1},
    {"The Taj Mahal is located in which city?",
     {"Delhi", "Jaipur", "Agra", "Lucknow"}, 2},
    {"What is the chemical symbol of Gold?",
     {"Ag", "Au", "Gd", "Go"}, 1},
    {"Who is known as the 'Missile Man of India'?",
     {"Vikram Sarabhai", "Homi Bhabha", "C. V. Raman", "A. P. J. Abdul Kalam"}, 3},
    {"Who won India's first individual Olympic gold medal (2008)?",
     {"Abhinav Bindra", "Leander Paes", "Sushil Kumar", "Vijender Singh"}, 0},
    {"Which gas is the most abundant in Earth's atmosphere?",
     {"Oxygen", "Nitrogen", "Carbon Dioxide", "Argon"}, 1},
    {"Who is the author of the ancient text 'Arthashastra'?",
     {"Kalidasa", "Banabhatta", "Kautilya", "Vishakhadatta"}, 2},
    {"Chandrayaan-3 landed near which region of the Moon?",
     {"North Pole", "South Pole", "Equator", "Far side centre"}, 1},
    {"Which Article of the Indian Constitution abolishes untouchability?",
     {"Article 14", "Article 15", "Article 17", "Article 21"}, 2},
    {"In which year was the Constitution of India adopted by the Constituent Assembly?",
     {"1947", "1949", "1950", "1952"}, 1}
};
static void format_money(long n, char *out)
{
    char raw[32], tmp[48];
    int len, i, j = 0;

    sprintf(raw, "%ld", n);
    len = (int)strlen(raw);

    for (i = 0; i < len; i++) {
        int r = len - i - 1;      
        tmp[j++] = raw[i];
        if (r >= 3 && (r % 2 == 1))
            tmp[j++] = ',';
    }
    tmp[j] = '\0';
    strcpy(out, tmp);
}

static void print_money(long n)
{
    char buf[48];
    format_money(n, buf);
    printf("Rs %s", buf);
}

static long safe_amount(int questions_cleared)
{
    if (questions_cleared >= 10) return prize[9];
    if (questions_cleared >= 5)  return prize[4];
    return 0;
}

static void line(void)
{
    printf("==============================================================\n");
}

static void show_ladder(int current)
{
    int i;
    char buf[48];
    printf("\n------------- PRIZE LADDER -------------\n");
    for (i = TOTAL - 1; i >= 0; i--) {
        format_money(prize[i], buf);
        printf(" %s Q%-2d  Rs %-12s %s\n",
               (i == current) ? ">>" : "  ",
               i + 1, buf,
               (i == 4 || i == 9) ? "[SAFE LEVEL]" : "");
    }
    printf("----------------------------------------\n");
}

static void show_question(int q, const int hidden[4], int lifeline[3])
{
    int i;
    char buf[48];
    format_money(prize[q], buf);

    printf("\n");
    line();
    printf(" QUESTION %d for Rs %s\n", q + 1, buf);
    line();
    printf(" %s\n\n", quiz[q].question);

    for (i = 0; i < 4; i++) {
        if (hidden[i])
            printf("   %c) ---\n", 'A' + i);
        else
            printf("   %c) %s\n", 'A' + i, quiz[q].option[i]);
    }

    printf("\n Lifelines left: ");
    if (lifeline[0]) printf("[1] 50-50  ");
    if (lifeline[1]) printf("[2] Audience Poll  ");
    if (lifeline[2]) printf("[3] Phone a Friend  ");
    if (!lifeline[0] && !lifeline[1] && !lifeline[2]) printf("None");
    printf("\n Type A/B/C/D to answer, L for lifeline, Q to quit.\n");
}
static void fifty_fifty(int q, int hidden[4])
{
    int removed = 0;
    while (removed < 2) {
        int r = rand() % 4;
        if (r != quiz[q].answer && !hidden[r]) {
            hidden[r] = 1;
            removed++;
        }
    }
    printf("\n  Two wrong options have been removed!\n");
}

static void audience_poll(int q, const int hidden[4])
{
    int pct[4] = {0, 0, 0, 0};
    int i, left = 100, count = 0;

    for (i = 0; i < 4; i++)
        if (!hidden[i]) count++;
    int base = 75 - q * 2;
    if (base < 40) base = 40;
    int correct = base + rand() % 15;
    if (correct > 95) correct = 95;
    pct[quiz[q].answer] = correct;
    left -= correct;

    int others = count - 1;
    for (i = 0; i < 4 && others > 0; i++) {
        if (i == quiz[q].answer || hidden[i]) continue;
        int share = (others == 1) ? left : rand() % (left + 1);
        pct[i] = share;
        left -= share;
        others--;
    }

    printf("\n  --- AUDIENCE POLL ---\n");
    for (i = 0; i < 4; i++) {
        if (hidden[i]) continue;
        int bars = pct[i] / 4, b;
        printf("   %c) %3d%% ", 'A' + i, pct[i]);
        for (b = 0; b < bars; b++) printf("#");
        printf("\n");
    }
}

static void phone_a_friend(int q, const int hidden[4])
{
    int chance = 90 - q * 4;              /* friend gets less sure later on */
    int guess = quiz[q].answer;

    if (rand() % 100 >= chance) {         /* friend is wrong */
        do { guess = rand() % 4; }
        while (guess == quiz[q].answer || hidden[guess]);
    }

    printf("\n  --- PHONE A FRIEND ---\n");
    printf("  Friend: \"Hmm... let me think.\"\n");
    if (chance >= 70)
        printf("  Friend: \"I am quite sure it is option %c (%s).\"\n",
               'A' + guess, quiz[q].option[guess]);
    else
        printf("  Friend: \"I'm not fully sure, but I'd go with option %c (%s).\"\n",
               'A' + guess, quiz[q].option[guess]);
}

static void use_lifeline(int q, int hidden[4], int lifeline[3])
{
    char buf[16];
    int choice;

    if (!lifeline[0] && !lifeline[1] && !lifeline[2]) {
        printf("\n  You have no lifelines left!\n");
        return;
    }

    printf("\n  Choose a lifeline:\n");
    if (lifeline[0]) printf("   1) 50-50\n");
    if (lifeline[1]) printf("   2) Audience Poll\n");
    if (lifeline[2]) printf("   3) Phone a Friend\n");
    printf("   0) Go back\n  > ");

    if (!fgets(buf, sizeof buf, stdin)) return;
    choice = atoi(buf);

    switch (choice) {
        case 1:
            if (lifeline[0]) { lifeline[0] = 0; fifty_fifty(q, hidden); }
            else printf("  Already used.\n");
            break;
        case 2:
            if (lifeline[1]) { lifeline[1] = 0; audience_poll(q, hidden); }
            else printf("  Already used.\n");
            break;
        case 3:
            if (lifeline[2]) { lifeline[2] = 0; phone_a_friend(q, hidden); }
            else printf("  Already used.\n");
            break;
        default:
            break;
    }
}
static void show_rules(void)
{
    line();
    printf("        KAUN BANEGA CROREPATI  -  C Language Edition\n");
    line();
    printf("\n RULES:\n");
    printf("  1. Answer 15 questions correctly to win Rs 1 Crore.\n");
    printf("  2. Safe levels: Q5 = Rs 10,000  and  Q10 = Rs 3,20,000.\n");
    printf("     If you answer wrong, you fall back to the last safe level.\n");
    printf("  3. You have 3 lifelines: 50-50, Audience Poll, Phone a Friend.\n");
    printf("  4. You can QUIT (press Q) any time to keep the money won so far.\n");
    printf("\n Press ENTER to begin...");
    getchar();
}

static void end_game(const char *msg, long amount)
{
    printf("\n");
    line();
    printf(" %s\n", msg);
    printf(" You are going home with: ");
    print_money(amount);
    printf("\n");
    line();
    printf(" Thank you for playing KBC!\n\n");
}

int main(void)
{
    char name[50], buf[32];
    int lifeline[3] = {1, 1, 1};
    int q;

    srand((unsigned)time(NULL));

    show_rules();

    printf("\n Enter your name: ");
    if (!fgets(name, sizeof name, stdin)) return 0;
    name[strcspn(name, "\n")] = '\0';
    if (name[0] == '\0') strcpy(name, "Player");

    printf("\n Namaskar %s! Welcome to Kaun Banega Crorepati!\n", name);
    printf(" Let's play!\n");

    for (q = 0; q < TOTAL; q++) {
        int hidden[4] = {0, 0, 0, 0};
        int answered = 0;

        while (!answered) {
            char c;
            show_question(q, hidden, lifeline);
            printf("\n %s, your choice: ", name);

            if (!fgets(buf, sizeof buf, stdin)) return 0;
            c = (char)toupper((unsigned char)buf[0]);

            if (c == 'L') {
                use_lifeline(q, hidden, lifeline);
            }
            else if (c == 'Q') {
                long won = (q == 0) ? 0 : prize[q - 1];
                printf("\n The correct answer was %c) %s\n",
                       'A' + quiz[q].answer, quiz[q].option[quiz[q].answer]);
                end_game("You chose to QUIT.", won);
                return 0;
            }
            else if (c >= 'A' && c <= 'D') {
                int pick = c - 'A';

                if (hidden[pick]) {
                    printf("\n  That option was removed. Choose another.\n");
                    continue;
                }

                printf("\n Locked: %c) %s ... ", c, quiz[q].option[pick]);
                fflush(stdout);

                if (pick == quiz[q].answer) {
                    printf("CORRECT!\n");
                    printf(" You have won ");
                    print_money(prize[q]);
                    printf("\n");
                    if (q == 4 || q == 9)
                        printf(" *** You have reached a SAFE LEVEL! ***\n");
                    answered = 1;

                    if (q < TOTAL - 1) {
                        show_ladder(q + 1);
                        printf(" Press ENTER for the next question...");
                        getchar();
                    }
                } else {
                    printf("WRONG!\n");
                    printf(" The correct answer was %c) %s\n",
                           'A' + quiz[q].answer, quiz[q].option[quiz[q].answer]);
                    end_game("Better luck next time!", safe_amount(q));
                    return 0;
                }
            }
            else {
                printf("\n  Invalid input. Please type A, B, C, D, L or Q.\n");
            }
        }
    }

    printf("\n");
    line();
    printf("   CONGRATULATIONS %s!  YOU ARE A CROREPATI!\n", name);
    line();
    end_game("You answered all 15 questions correctly!", prize[TOTAL - 1]);
    return 0;
}