#include <stdio.h>
int main() {
int choice, num;
printf("Enter a number: ");
scanf("%d", &num);
printf("Choose operation:\n");
printf("1. Find Square\n");
printf("2. Find Cube\n");
printf("Enter your choice (1 or 2): ");
scanf("%d", &choice);
switch (choice) {
case 1:
printf("Square of %d = %d\n", num, num * num);
break;
case 2:
printf("Cube of %d = %d\n", num, num * num * num);
break;
default:
printf("Invalid choice!\n");
}
return 0; }