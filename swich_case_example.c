#include <stdio.h>
int main() {
int choice;
printf("Enter a number (1 or 2): ");
scanf("%d", &choice);
switch (choice) {
case 1:
printf("Hello\n");
break;
case 2:
printf("Welcome\n");
break;
default:
printf("Invalid choice\n");
}
return 0;
}