#include <stdio.h>
int main() {
char light;
printf("Enter traffic light color (R/G/Y): ");
scanf(" %c", &light); // space before %c taaki extra newline skip ho jaye
switch (light) {
case 'R':
case 'r':
printf("STOP! The light is RED.\n");
break;
case 'G':
case 'g':
printf("GO! The light is GREEN.\n");
break;
case 'Y':
case 'y':
printf("WAIT! The light is YELLOW.\n");
break;
default:
printf("Invalid input! Please enter R, G, or Y.\n");
}
return 0;}