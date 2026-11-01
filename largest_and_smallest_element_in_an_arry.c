#include <stdio.h>
int main() {
// Array is initialized at the time of declaration
int a[] = {12, 7, 25, 3, 18};
int n = 5;
int max = a[0];
int min = a[0];
for(int i = 1; i < n; i++) {
if(a[i] > max)
max = a[i];
if(a[i] < min)
min = a[i];
}
printf("Largest = %d\n", max);
printf("Smallest = %d", min);
return 0;
}