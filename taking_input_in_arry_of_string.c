#include <stdio.h>
int main() {
int n,m;
char names[n][m];
printf("enter the rows");
scanf("%d",&n);
printf("enter the column");
scanf("%d",&m);
printf("Enter 3 names:\n");
for(int i = 0; i < 3; i++) {
scanf("%s", names[i]);
}
printf("\nYou entered:\n");
for(int i = 0; i < 3; i++) {
printf("%s\n", names[i]);
}
return 0;
}