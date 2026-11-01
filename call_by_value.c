#include <stdio.h>
void change(int x) {
// x = 100; // changing the value inside function
printf("Inside function x = %d\n", x);
}
int main() {
int a = 10;
change(a); // call by value
printf("Inside main a = %d\n", a); // original value remains
return 0;
}