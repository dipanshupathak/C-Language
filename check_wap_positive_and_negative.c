#include <stdio.h>
int main() {
int num;
printf("Enter a number: ");
scanf("%d", &num);
switch ((num > 0) - (num < 0)) {
case 1:
printf("The number is Positive.\n");
break;
case -1:
printf("The number is Negative.\n");
break;
case 0:
printf("The number is Zero.\n");
break;
default:
printf("Error!\n");
}
return 0;
}