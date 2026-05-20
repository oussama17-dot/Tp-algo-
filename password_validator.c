#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
 * checkLength - checks if password length is >= min
 * Parameters: p[] - the password, min - minimum length
 * Returns: 1 if length >= min, else 0
 */
int checkLength(char p[], int min) {
    return (int)strlen(p) >= min ? 1 : 0;
}

/*
 * hasUppercase - checks if password contains at least one uppercase letter
 * Parameters: p[] - the password
 * Returns: 1 if found, else 0
 */
int hasUppercase(char p[]) {
    for (int i = 0; p[i] != '\0'; i++)
        if (p[i] >= 'A' && p[i] <= 'Z') return 1;
    return 0;
}

/*
 * hasLowercase - checks if password contains at least one lowercase letter
 * Parameters: p[] - the password
 * Returns: 1 if found, else 0
 */
int hasLowercase(char p[]) {
    for (int i = 0; p[i] != '\0'; i++)
        if (p[i] >= 'a' && p[i] <= 'z') return 1;
    return 0;
}

/*
 * hasDigit - checks if password contains at least one digit
 * Parameters: p[] - the password
 * Returns: 1 if found, else 0
 */
int hasDigit(char p[]) {
    for (int i = 0; p[i] != '\0'; i++)
        if (p[i] >= '0' && p[i] <= '9') return 1;
    return 0;
}

/*
 * hasSpecialChar - checks if password contains at least one special character
 * Parameters: p[] - the password
 * Returns: 1 if found, else 0
 */
int hasSpecialChar(char p[]) {
    char specials[] = "!#$%&*+-=?^_";
    for (int i = 0; p[i] != '\0'; i++)
        for (int j = 0; specials[j] != '\0'; j++)
            if (p[i] == specials[j]) return 1;
    return 0;
}

/*
 * hasNoSpace - checks if password contains no whitespace characters
 * Parameters: p[] - the password
 * Returns: 1 if no spaces found, else 0
 */
int hasNoSpace(char p[]) {
    for (int i = 0; p[i] != '\0'; i++)
        if (p[i] == ' ' || p[i] == '\t') return 0;
    return 1;
}

/*
 * calculateStrength - calls all checkers and returns total score
 * Parameters: p[] - the password
 * Returns: score from 0 to 6
 */
int calculateStrength(char p[]) {
    int score = 0;
    score += checkLength(p, 8);
    score += hasUppercase(p);
    score += hasLowercase(p);
    score += hasDigit(p);
    score += hasSpecialChar(p);
    score += hasNoSpace(p);
    return score;
}

/*
 * printFeedback - prints colored score label and lists missing requirements
 * Parameters: p[] - the password
 * Returns: void
 */
void printFeedback(char p[]) {
    int score = calculateStrength(p);

    char *red    = "\033[1;31m";
    char *yellow = "\033[1;33m";
    char *white  = "\033[1;37m";
    char *green  = "\033[1;32m";
    char *reset  = "\033[0m";

    printf("Score: %d/6\t", score);

    if (score <= 1)
        printf("%s[!] Very Weak - do not use this password.%s\n", red, reset);
    else if (score == 2)
        printf("%s[!] Weak - significant improvements needed.%s\n", red, reset);
    else if (score == 3)
        printf("%s[ ] Fair - getting there, but not safe yet.%s\n", yellow, reset);
    else if (score == 4)
        printf("%s[+] Good - a few tweaks and you are set.%s\n", white, reset);
    else if (score == 5)
        printf("%s[+] Strong - almost perfect.%s\n", green, reset);
    else
        printf("%s[*] Very Strong - excellent password.%s\n", green, reset);

    if (score < 6) {
        printf("Missing requirements:\n");
        if (!checkLength(p, 8))
            printf("  - At least 8 characters\t(current: %d)\n", (int)strlen(p));
        if (!hasUppercase(p))
            printf("  - At least one uppercase letter\n");
        if (!hasLowercase(p))
            printf("  - At least one lowercase letter\n");
        if (!hasDigit(p))
            printf("  - At least one digit\n");
        if (!hasSpecialChar(p))
            printf("  - At least one special character (!#$%%&*+-=?^_)\n");
        if (!hasNoSpace(p))
            printf("  - No whitespace characters allowed\n");
    } else {
        printf("All requirements satisfied.\n");
    }
}

/*
 * generateSuggestion - generates and prints a random valid password
 * Parameters: len - desired length of the password
 * Returns: void
 */
void generateSuggestion(int len) {
    if (len < 8) len = 8;
    srand((unsigned int)time(NULL));

    char upper[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[]   = "abcdefghijklmnopqrstuvwxyz";
    char digits[]  = "0123456789";
    char special[] = "!#$%&*+-=?^_";
    char all[100];

    strcpy(all, upper);
    strcat(all, lower);
    strcat(all, digits);
    strcat(all, special);

    char password[101];
    int allLen = (int)strlen(all);

    password[0] = upper[rand() % 26];
    password[1] = lower[rand() % 26];
    password[2] = digits[rand() % 10];
    password[3] = special[rand() % 12];

    for (int i = 4; i < len; i++)
        password[i] = all[rand() % allLen];

    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char tmp = password[i];
        password[i] = password[j];
        password[j] = tmp;
    }

    password[len] = '\0';
    printf("Suggested password: %s\n", password);
}

int main() {
    char password[200];

    while (1) {
        printf("\nEnter password (or q to quit): ");
        scanf("%199s", password);

        if (password[0] == 'q' && strlen(password) == 1)
            break;

        printFeedback(password);
    }

    printf("\nGenerating a strong password suggestion (length 12):\n");
    generateSuggestion(12);

    return 0;
}
