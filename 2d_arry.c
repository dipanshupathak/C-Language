#include <stdio.h>
int main() {
int a[3][3] = {
{10, 20, 30},
{40, 50, 60},
{70, 80, 90}
};
int i, j;
printf("The 3x3 matrix is:\n");
for(i = 0; i < 3; i++) { // row loop
for(j = 0; j < 3; j++) { // column loop
printf("%d ", a[i][j]); // access each element
}
printf("\n");
}
return 0;
}