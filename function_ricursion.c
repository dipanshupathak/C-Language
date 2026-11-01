#include <stdio.h>
int add(int x, int y) {
return x + y;
}
int main() {
int (*fp)(int, int); // function pointer
fp = add; // store address of add
int s = fp(3, 4); // call using pointer
printf("%d\n", s); // prints 7
return 0;
}