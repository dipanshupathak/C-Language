#include <stdio.h>
int main() {
int arr[5]; // user-defined 1D array
int i;
// input values
printf("Enter 5 numbers:\n");
for(i = 0; i < 5; i++) {
scanf("%d", &arr[i]);
}
// output values
printf("You entered:\n");
for(i = 0; i < 5; i++) {
printf("%d ", arr[i]);
}
return 0;
}