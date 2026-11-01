#include <stdio.h>
int main() {
// Array of strings (2D char array)
char fruits[4][10] = {
"Apple",
"Mango",
"Grapes",
"Banana"
};
// Accessing individual characters
printf("First character of Apple: %c\n", fruits[0][0]); // A
printf("Third character of Mango: %c\n", fruits[1][2]); // n
printf("Fourth character of Grapes: %c\n", fruits[2][3]); // p
printf("Second character of Banana: %c\n", fruits[3][1]); // a
return 0;
}