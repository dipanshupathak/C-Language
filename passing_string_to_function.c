#include <stdio.h>
// Function declaration
void displayString(char str[]) {
printf("String inside function: %s\n", str);
}
int main() {
// String initialization
char name[] = "Neha";
// Passing string to function
displayString(name);
return 0;
}