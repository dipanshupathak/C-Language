#include <stdio.h>
int main() {
int a = 10;
int *p = &a; // pointer to int
int **q = &p; // pointer to pointer
printf("Value of a = %d\n", a);
printf("Address of a = %p\n", &a);
printf("Value of p (address of a) = %p\n", p);
printf("Address of p = %p\n", &p);
printf("Value of q (address of p) = %p\n", q);
printf("Value pointed by q (*q) = %p\n", *q);
printf("Value pointed by *q (**q) = %d\n", **q);
return 0;
}