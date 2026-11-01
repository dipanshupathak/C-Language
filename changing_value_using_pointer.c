#include <stdio.h>
int main() {
int a = 10;
int *p = &a;
printf("Before change: a = %d\n", a);
*p = 50; // change value of a using pointer
printf("After change: a = %d\n", a);
return 0;
}