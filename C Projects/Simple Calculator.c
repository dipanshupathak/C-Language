#include <stdio.h>
#include <math.h>
double add(double a, double b)      { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b)   { return a / b; }

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

double readNumber(const char *prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1) {
            clearInput();
            return value;
        }
        printf("Invalid input. Please enter a number.\n");
        clearInput();
    }
}
void showMenu(void) {
    printf("\n=========== SIMPLE CALCULATOR ===========\n");
    printf("  1. Addition        (+)\n");
    printf("  2. Subtraction     (-)\n");
    printf("  3. Multiplication  (*)\n");
    printf("  4. Division        (/)\n");
    printf("  5. Modulus         (%%)  [integers]\n");
    printf("  6. Power           (x^y)\n");
    printf("  7. Square Root\n");
    printf("  0. Exit\n");
    printf("=========================================\n");
}

int main(void) {
    int choice;
    double a, b, result;

    while (1) {
        showMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number from the menu.\n");
            clearInput();
            continue;
        }
        clearInput();

        if (choice == 0) {
            printf("Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1:
                a = readNumber("Enter first number: ");
                b = readNumber("Enter second number: ");
                result = add(a, b);
                printf("Result: %g + %g = %g\n", a, b, result);
                break;

            case 2:
                a = readNumber("Enter first number: ");
                b = readNumber("Enter second number: ");
                result = subtract(a, b);
                printf("Result: %g - %g = %g\n", a, b, result);
                break;

            case 3:
                a = readNumber("Enter first number: ");
                b = readNumber("Enter second number: ");
                result = multiply(a, b);
                printf("Result: %g * %g = %g\n", a, b, result);
                break;

            case 4:
                a = readNumber("Enter dividend: ");
                b = readNumber("Enter divisor: ");
                if (b == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    result = divide(a, b);
                    printf("Result: %g / %g = %g\n", a, b, result);
                }
                break;

            case 5: {
                a = readNumber("Enter first integer: ");
                b = readNumber("Enter second integer: ");
                long x = (long)a, y = (long)b;
                if (y == 0) {
                    printf("Error: Modulus by zero is not allowed.\n");
                } else {
                    printf("Result: %ld %% %ld = %ld\n", x, y, x % y);
                }
                break;
            }

            case 6:
                a = readNumber("Enter base: ");
                b = readNumber("Enter exponent: ");
                result = pow(a, b);
                printf("Result: %g ^ %g = %g\n", a, b, result);
                break;

            case 7:
                a = readNumber("Enter a number: ");
                if (a < 0) {
                    printf("Error: Cannot take square root of a negative number.\n");
                } else {
                    result = sqrt(a);
                    printf("Result: sqrt(%g) = %g\n", a, result);
                }
                break;

            default:
                printf("Invalid choice. Please select 0-7.\n");
        }
    }

    return 0;
}