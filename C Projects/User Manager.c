#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATA_FILE     "users.dat"
#define USERNAME_LEN  32
#define PASSWORD_LEN  64
#define EMAIL_LEN     64
#define ROLE_LEN      16

typedef struct {
    int           id;
    char          username[USERNAME_LEN];
    char          email[EMAIL_LEN];
    char          role[ROLE_LEN];      
    unsigned long pass_hash;
} User;

static User  *users    = NULL;
static size_t count    = 0;
static size_t capacity = 0;
static int    next_id  = 1;

static unsigned long hash_password(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

static void read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (!fgets(buf, (int)size, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int ch;                        
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

static int read_int(const char *prompt) {
    char buf[32];
    read_line(prompt, buf, sizeof buf);
    return atoi(buf);
}

static void to_lower(char *s) {
    for (; *s; s++) *s = (char)tolower((unsigned char)*s);
}

static int valid_email(const char *e) {
    const char *at = strchr(e, '@');
    return at && at != e && strchr(at, '.') && *(at + 1) != '.' && e[strlen(e) - 1] != '.';
}

static int valid_username(const char *u) {
    if (strlen(u) < 3) return 0;
    for (; *u; u++)
        if (!isalnum((unsigned char)*u) && *u != '_') return 0;
    return 1;
}
static int ensure_capacity(void) {
    if (count < capacity) return 1;
    size_t new_cap = capacity ? capacity * 2 : 8;
    User *tmp = realloc(users, new_cap * sizeof(User));
    if (!tmp) {
        fprintf(stderr, "Error: out of memory.\n");
        return 0;
    }
    users = tmp;
    capacity = new_cap;
    return 1;
}

static int save_users(void) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        perror("Could not save users");
        return 0;
    }
    fwrite(&next_id, sizeof next_id, 1, fp);
    fwrite(&count, sizeof count, 1, fp);
    if (count) fwrite(users, sizeof(User), count, fp);
    fclose(fp);
    return 1;
}

static void load_users(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return;

    size_t n = 0;
    if (fread(&next_id, sizeof next_id, 1, fp) != 1 ||
        fread(&n, sizeof n, 1, fp) != 1) {
        fclose(fp);
        return;
    }
    for (size_t i = 0; i < n; i++) {
        if (!ensure_capacity()) break;
        if (fread(&users[count], sizeof(User), 1, fp) != 1) break;
        count++;
    }
    fclose(fp);
}
static User *find_by_id(int id) {
    for (size_t i = 0; i < count; i++)
        if (users[i].id == id) return &users[i];
    return NULL;
}

static User *find_by_username(const char *name) {
    for (size_t i = 0; i < count; i++)
        if (strcmp(users[i].username, name) == 0) return &users[i];
    return NULL;
}

static int admin_count(void) {
    int n = 0;
    for (size_t i = 0; i < count; i++)
        if (strcmp(users[i].role, "admin") == 0) n++;
    return n;
}

static void print_header(void) {
    printf("\n%-5s %-20s %-30s %-8s\n", "ID", "Username", "Email", "Role");
    printf("---------------------------------------------------------------\n");
}

static void print_user(const User *u) {
    printf("%-5d %-20s %-30s %-8s\n", u->id, u->username, u->email, u->role);
}

static void add_user(void) {
    User u;
    char pass[PASSWORD_LEN], role[ROLE_LEN];

    memset(&u, 0, sizeof u);
    printf("\n--- Add New User ---\n");

    read_line("Username (letters, digits, _; min 3): ", u.username, sizeof u.username);
    to_lower(u.username);
    if (!valid_username(u.username)) {
        printf("Invalid username.\n");
        return;
    }
    if (find_by_username(u.username)) {
        printf("Username already exists.\n");
        return;
    }

    read_line("Email: ", u.email, sizeof u.email);
    if (!valid_email(u.email)) {
        printf("Invalid email address.\n");
        return;
    }

    read_line("Password (min 6 chars): ", pass, sizeof pass);
    if (strlen(pass) < 6) {
        printf("Password too short.\n");
        return;
    }

    read_line("Role (admin/user) [user]: ", role, sizeof role);
    to_lower(role);
    if (role[0] == '\0') strcpy(role, "user");
    if (strcmp(role, "admin") != 0 && strcmp(role, "user") != 0) {
        printf("Invalid role.\n");
        return;
    }
    strcpy(u.role, role);

    u.id = next_id++;
    u.pass_hash = hash_password(pass);

    if (!ensure_capacity()) return;
    users[count++] = u;
    if (save_users()) printf("User '%s' added (ID %d).\n", u.username, u.id);
}

static void list_users(void) {
    if (count == 0) {
        printf("\nNo users found.\n");
        return;
    }
    print_header();
    for (size_t i = 0; i < count; i++) print_user(&users[i]);
    printf("\nTotal: %zu user(s)\n", count);
}

static void search_users(void) {
    char term[USERNAME_LEN];
    int found = 0;

    read_line("\nSearch (username or email contains): ", term, sizeof term);
    to_lower(term);
    if (term[0] == '\0') return;

    for (size_t i = 0; i < count; i++) {
        char uname[USERNAME_LEN], email[EMAIL_LEN];
        strcpy(uname, users[i].username);
        strcpy(email, users[i].email);
        to_lower(uname);
        to_lower(email);
        if (strstr(uname, term) || strstr(email, term)) {
            if (!found) print_header();
            print_user(&users[i]);
            found++;
        }
    }
    if (!found) printf("No matching users.\n");
    else printf("\n%d match(es).\n", found);
}

static void update_user(void) {
    int id = read_int("\nEnter ID of user to update: ");
    User *u = find_by_id(id);
    if (!u) {
        printf("User not found.\n");
        return;
    }

    char buf[PASSWORD_LEN];
    printf("Updating '%s' (leave blank to keep current value)\n", u->username);

    read_line("New email: ", buf, EMAIL_LEN);
    if (buf[0]) {
        if (valid_email(buf)) strcpy(u->email, buf);
        else printf("Invalid email, keeping old one.\n");
    }

    read_line("New role (admin/user): ", buf, ROLE_LEN);
    to_lower(buf);
    if (buf[0]) {
        if (strcmp(buf, "admin") == 0 || strcmp(buf, "user") == 0) {
            if (strcmp(u->role, "admin") == 0 && strcmp(buf, "admin") != 0 &&
                admin_count() <= 1) {
                printf("Cannot demote the last admin.\n");
            } else {
                strcpy(u->role, buf);
            }
        } else {
            printf("Invalid role, keeping old one.\n");
        }
    }

    read_line("New password (min 6 chars): ", buf, sizeof buf);
    if (buf[0]) {
        if (strlen(buf) >= 6) u->pass_hash = hash_password(buf);
        else printf("Password too short, keeping old one.\n");
    }

    if (save_users()) printf("User updated.\n");
}

static void delete_user(const User *current) {
    int id = read_int("\nEnter ID of user to delete: ");
    User *u = find_by_id(id);
    if (!u) {
        printf("User not found.\n");
        return;
    }
    if (u->id == current->id) {
        printf("You cannot delete your own account while logged in.\n");
        return;
    }
    if (strcmp(u->role, "admin") == 0 && admin_count() <= 1) {
        printf("Cannot delete the last admin.\n");
        return;
    }

    char confirm[8];
    printf("Delete user '%s'? (y/N): ", u->username);
    read_line("", confirm, sizeof confirm);
    if (tolower((unsigned char)confirm[0]) != 'y') {
        printf("Cancelled.\n");
        return;
    }

    size_t idx = (size_t)(u - users);
    memmove(&users[idx], &users[idx + 1], (count - idx - 1) * sizeof(User));
    count--;
    if (save_users()) printf("User deleted.\n");
}

static void change_password(User *u) {
    char old_pw[PASSWORD_LEN], new_pw[PASSWORD_LEN], confirm[PASSWORD_LEN];

    read_line("\nCurrent password: ", old_pw, sizeof old_pw);
    if (hash_password(old_pw) != u->pass_hash) {
        printf("Incorrect password.\n");
        return;
    }
    read_line("New password (min 6 chars): ", new_pw, sizeof new_pw);
    if (strlen(new_pw) < 6) {
        printf("Password too short.\n");
        return;
    }
    read_line("Confirm new password: ", confirm, sizeof confirm);
    if (strcmp(new_pw, confirm) != 0) {
        printf("Passwords do not match.\n");
        return;
    }
    u->pass_hash = hash_password(new_pw);
    if (save_users()) printf("Password changed.\n");
}

static User *login(void) {
    char name[USERNAME_LEN], pass[PASSWORD_LEN];

    printf("\n=== Login ===\n");
    read_line("Username: ", name, sizeof name);
    to_lower(name);
    read_line("Password: ", pass, sizeof pass);

    User *u = find_by_username(name);
    if (u && u->pass_hash == hash_password(pass)) {
        printf("\nWelcome, %s! (%s)\n", u->username, u->role);
        return u;
    }
    printf("Invalid username or password.\n");
    return NULL;
}

static void admin_menu(User *me) {
    for (;;) {
        printf("\n===== Admin Menu =====\n"
               "1. Add user\n"
               "2. List users\n"
               "3. Search users\n"
               "4. Update user\n"
               "5. Delete user\n"
               "6. Change my password\n"
               "0. Logout\n");
        switch (read_int("Choice: ")) {
            case 1: add_user();         break;
            case 2: list_users();       break;
            case 3: search_users();     break;
            case 4: update_user();      break;
            case 5: delete_user(me);    break;
            case 6: change_password(me);break;
            case 0: printf("Logged out.\n"); return;
            default: printf("Invalid choice.\n");
        }
        me = find_by_username(me->username);   
        if (!me) return;
    }
}

static void user_menu(User *me) {
    for (;;) {
        printf("\n===== User Menu =====\n"
               "1. View my profile\n"
               "2. Change my password\n"
               "0. Logout\n");
        switch (read_int("Choice: ")) {
            case 1: print_header(); print_user(me); break;
            case 2: change_password(me);            break;
            case 0: printf("Logged out.\n"); return;
            default: printf("Invalid choice.\n");
        }
    }
}

int main(void) {
    load_users();

    if (count == 0) {                       
        User admin = { 0 };
        admin.id = next_id++;
        strcpy(admin.username, "admin");
        strcpy(admin.email, "admin@example.com");
        strcpy(admin.role, "admin");
        admin.pass_hash = hash_password("admin123");
        if (ensure_capacity()) {
            users[count++] = admin;
            save_users();
            printf("First run: default account created (admin / admin123).\n");
        }
    }

    for (;;) {
        printf("\n===== User Management System =====\n"
               "1. Login\n"
               "0. Exit\n");
        int choice = read_int("Choice: ");
        if (choice == 0) break;
        if (choice == 1) {
            User *me = login();
            if (me) {
                if (strcmp(me->role, "admin") == 0) admin_menu(me);
                else                                user_menu(me);
            }
        } else {
            printf("Invalid choice.\n");
        }
    }

    free(users);
    printf("Goodbye!\n");
    return 0;
}