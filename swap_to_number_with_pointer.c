#include <stdio.h>
void swap(int *x, int *y) {
int temp;
temp = *x;
*x = *y;
*y = temp;
}
int main() {
int a = 5, b = 10;
printf("Before swap: a = %d, b = %d\n", a, b);
swap(&a, &b); // passing address of a and b
printf("After swap: a = %d, b = %d\n", a, b);
return 0;
}