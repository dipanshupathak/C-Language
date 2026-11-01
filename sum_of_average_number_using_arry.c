#include <stdio.h>
int main() {
int n, i;
printf("Enter number of elements: ");
scanf("%d", &n);
int a[n], sum = 0;
printf("Enter %d numbers:\n", n);
for(i = 0; i < n; i++) {
scanf("%d", &a[i]);
sum += a[i];
}
float avg = sum / (float)n;
printf("Sum = %d\n", sum);
printf("Average = %.2f", avg);
return 0;
}