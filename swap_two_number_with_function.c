#include <stdio.h>
void swap(int x, int y) { // normal parameters (not pointers)
int temp;
temp = x;
x = y;
y = temp;
printf("Inside function: x = %d, y = %d\n", x, y);
}
int main() {
int a = 5, b = 10;
printf("Before swap: a = %d, b = %d\n", a, b);
swap(a, b); // pass only values
printf("After swap: a = %d, b = %d\n", a, b);
return 0;
}