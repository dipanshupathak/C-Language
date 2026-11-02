/*
 * Simple Banking System in C
 * Features: create account, login with PIN, deposit, withdraw, transfer,
 *           balance check, transaction history, change PIN, close account.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 100
#define DATA_FILE    "bank.dat"
#define TXN_FILE     "transactions.txt"
#define MIN_BALANCE  0.0
#define MAX_ATTEMPTS 3

typedef struct {
    int    accNo;
    char   name[50];
    int    pin;
    double balance;
} Account;

static Account accounts[MAX_ACCOUNTS];
static int     accountCount = 0;
static int     nextAccNo    = 1001;

static void readLine(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    if (!fgets(buf, (int)size, stdin)) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

static int readInt(const char *prompt) {
    char buf[64];
    char *end;
    while (1) {
        readLine(prompt, buf, sizeof buf);
        long v = strtol(buf, &end, 10);
        if (end != buf && *end == '\0') return (int)v;
        printf("Invalid number. Try again.\n");
    }
}

static double readAmount(const char *prompt) {
    char buf[64];
    char *end;
    while (1) {
        readLine(prompt, buf, sizeof buf);
        double v = strtod(buf, &end);
        if (end != buf && *end == '\0' && v > 0) return v;
        printf("Enter a valid positive amount.\n");
    }
}

static int readPin(const char *prompt) {
    while (1) {
        int pin = readInt(prompt);
        if (pin >= 1000 && pin <= 9999) return pin;
        printf("PIN must be exactly 4 digits (1000-9999).\n");
    }
}

static void saveData(void) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf("Error: could not save data.\n");
        return;
    }
    fwrite(&nextAccNo, sizeof nextAccNo, 1, fp);
    fwrite(&accountCount, sizeof accountCount, 1, fp);
    fwrite(accounts, sizeof(Account), accountCount, fp);
    fclose(fp);
}

static void loadData(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return; /* first run */
    if (fread(&nextAccNo, sizeof nextAccNo, 1, fp) != 1 ||
        fread(&accountCount, sizeof accountCount, 1, fp) != 1 ||
        accountCount < 0 || accountCount > MAX_ACCOUNTS ||
        fread(accounts, sizeof(Account), accountCount, fp) != (size_t)accountCount) {
        printf("Warning: data file is corrupt. Starting fresh.\n");
        accountCount = 0;
        nextAccNo = 1001;
    }
    fclose(fp);
}

static void logTransaction(int accNo, const char *type, double amount, double balance) {
    FILE *fp = fopen(TXN_FILE, "a");
    if (!fp) return;
    time_t now = time(NULL);
    char ts[32];
    strftime(ts, sizeof ts, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(fp, "%d|%s|%s|%.2f|%.2f\n", accNo, ts, type, amount, balance);
    fclose(fp);
}

static Account *findAccount(int accNo) {
    for (int i = 0; i < accountCount; i++)
        if (accounts[i].accNo == accNo) return &accounts[i];
    return NULL;
}

static void createAccount(void) {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Bank is full. Cannot create more accounts.\n");
        return;
    }
    Account a;
    memset(&a, 0, sizeof a);

    readLine("Enter your full name: ", a.name, sizeof a.name);
    if (strlen(a.name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }
    a.pin = readPin("Set a 4-digit PIN: ");

    char buf[64];
    readLine("Initial deposit (0 for none): ", buf, sizeof buf);
    double dep = atof(buf);
    if (dep < 0) dep = 0;
    a.balance = dep;
    a.accNo   = nextAccNo++;

    accounts[accountCount++] = a;
    saveData();
    logTransaction(a.accNo, "OPEN", dep, a.balance);

    printf("\nAccount created successfully!\n");
    printf("Your account number: %d (keep it safe)\n", a.accNo);
}

static Account *login(void) {
    int accNo = readInt("Account number: ");
    Account *a = findAccount(accNo);
    if (!a) {
        printf("Account not found.\n");
        return NULL;
    }
    for (int tries = 1; tries <= MAX_ATTEMPTS; tries++) {
        int pin = readInt("PIN: ");
        if (pin == a->pin) {
            printf("\nWelcome, %s!\n", a->name);
            return a;
        }
        printf("Wrong PIN (%d/%d).\n", tries, MAX_ATTEMPTS);
    }
    printf("Too many failed attempts.\n");
    return NULL;
}

static void deposit(Account *a) {
    double amt = readAmount("Amount to deposit: ");
    a->balance += amt;
    saveData();
    logTransaction(a->accNo, "DEPOSIT", amt, a->balance);
    printf("Deposited %.2f. New balance: %.2f\n", amt, a->balance);
}

static void withdraw(Account *a) {
    double amt = readAmount("Amount to withdraw: ");
    if (a->balance - amt < MIN_BALANCE) {
        printf("Insufficient funds. Balance: %.2f\n", a->balance);
        return;
    }
    a->balance -= amt;
    saveData();
    logTransaction(a->accNo, "WITHDRAW", amt, a->balance);
    printf("Withdrew %.2f. New balance: %.2f\n", amt, a->balance);
}

static void transfer(Account *a) {
    int toNo = readInt("Recipient account number: ");
    if (toNo == a->accNo) {
        printf("You cannot transfer to your own account.\n");
        return;
    }
    Account *to = findAccount(toNo);
    if (!to) {
        printf("Recipient account not found.\n");
        return;
    }
    double amt = readAmount("Amount to transfer: ");
    if (a->balance - amt < MIN_BALANCE) {
        printf("Insufficient funds. Balance: %.2f\n", a->balance);
        return;
    }
    a->balance  -= amt;
    to->balance += amt;
    saveData();
    logTransaction(a->accNo, "TRANSFER_OUT", amt, a->balance);
    logTransaction(to->accNo, "TRANSFER_IN", amt, to->balance);
    printf("Transferred %.2f to %s (A/C %d). New balance: %.2f\n",
           amt, to->name, to->accNo, a->balance);
}

static void showBalance(const Account *a) {
    printf("\n--- Account Summary ---\n");
    printf("Account No : %d\n", a->accNo);
    printf("Holder     : %s\n", a->name);
    printf("Balance    : %.2f\n", a->balance);
}

static void showHistory(const Account *a) {
    FILE *fp = fopen(TXN_FILE, "r");
    if (!fp) {
        printf("No transactions yet.\n");
        return;
    }
    char line[256];
    int found = 0;
    printf("\n%-20s %-14s %12s %12s\n", "Date/Time", "Type", "Amount", "Balance");
    printf("-----------------------------------------------------------\n");
    while (fgets(line, sizeof line, fp)) {
        int no;
        char ts[32], type[20];
        double amt, bal;
        if (sscanf(line, "%d|%31[^|]|%19[^|]|%lf|%lf", &no, ts, type, &amt, &bal) == 5
            && no == a->accNo) {
            printf("%-20s %-14s %12.2f %12.2f\n", ts, type, amt, bal);
            found = 1;
        }
    }
    if (!found) printf("No transactions found.\n");
    fclose(fp);
}

static void changePin(Account *a) {
    int oldPin = readInt("Current PIN: ");
    if (oldPin != a->pin) {
        printf("Incorrect PIN.\n");
        return;
    }
    a->pin = readPin("New 4-digit PIN: ");
    saveData();
    printf("PIN changed successfully.\n");
}

static int closeAccount(Account *a) {
    char buf[8];
    printf("Closing the account will withdraw the remaining balance of %.2f.\n", a->balance);
    readLine("Type YES to confirm: ", buf, sizeof buf);
    if (strcmp(buf, "YES") != 0) {
        printf("Cancelled.\n");
        return 0;
    }
    int idx = (int)(a - accounts);
    logTransaction(a->accNo, "CLOSE", a->balance, 0.0);
    printf("Please collect %.2f in cash. Account closed.\n", a->balance);
    for (int i = idx; i < accountCount - 1; i++)
        accounts[i] = accounts[i + 1];
    accountCount--;
    saveData();
    return 1;
}
static void accountMenu(Account *a) {
    while (1) {
        printf("\n===== ACCOUNT MENU =====\n");
        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\n");
        printf("5. Transaction History\n6. Change PIN\n7. Close Account\n8. Logout\n");
        int ch = readInt("Choice: ");
        switch (ch) {
            case 1: showBalance(a);  break;
            case 2: deposit(a);      break;
            case 3: withdraw(a);     break;
            case 4: transfer(a);     break;
            case 5: showHistory(a);  break;
            case 6: changePin(a);    break;
            case 7: if (closeAccount(a)) return; break;
            case 8: printf("Logged out.\n"); return;
            default: printf("Invalid choice.\n");
        }
    }
}

int main(void) {
    loadData();
    while (1) {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Create Account\n2. Login\n3. Exit\n");
        int ch = readInt("Choice: ");
        switch (ch) {
            case 1: createAccount(); break;
            case 2: {
                Account *a = login();
                if (a) accountMenu(a);
                break;
            }
            case 3:
                saveData();
                printf("Thank you for banking with us. Goodbye!\n");
                return 0;
            default: printf("Invalid choice.\n");
        }
    }
}