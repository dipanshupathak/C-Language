#include <stdio.h>
int main() {
int r, c, i, j;
printf("Enter rows and columns: ");
scanf("%d %d", &r, &c);
int A[r][c], B[r][c], S[r][c];
printf("Enter Matrix A:\n");
for(i=0; i<r; i++)
for(j=0; j<c; j++)
scanf("%d", &A[i][j]);
printf("Enter Matrix B:\n");
for(i=0; i<r; i++)
for(j=0; j<c; j++)
scanf("%d", &B[i][j]);
for(i=0; i<r; i++)
for(j=0; j<c; j++)
S[i][j] = A[i][j] + B[i][j];
printf("Sum Matrix:\n");
for(i=0; i<r; i++) {
for(j=0; j<c; j++)
printf("%d ", S[i][j]);
printf("\n");
}
return 0;
}