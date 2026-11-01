#include <stdio.h>
void change(int *x) { // pointer parameter
*x = 100; // change the value at the address
// printf("Inside function x = %d\n", *x);
}
int main() {
int a = 10;
change(&a); // pass address of a
printf("Inside main a = %d\n", a); // original value is changed
return 0;
}