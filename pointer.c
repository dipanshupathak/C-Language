#include <stdio.h>
int main() {
int x = 10;
int *y = &x;
printf("%d", x); // 10
printf("%p", &x); // 0x7fff942c6e6c
printf("%p", y); // 0x7fff942c6e6c
printf("%d", *y); // 10
printf("%p", &y); // 0x7fff942c6e60
printf("\n");
return 0;
}