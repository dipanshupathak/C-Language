#include<stdio.h>
int main() {
int marks;
printf("Enter your marks: ");
scanf("%d", &marks);
if (marks >= 40) {
if (marks >= 75) {
printf("You got Distinction.\n");
} else {
printf("You Passed.\n");
}
} else {
printf("You Failed.\n");
}
return 0;
}