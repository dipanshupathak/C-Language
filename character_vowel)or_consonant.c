#include<stdio.h>
int main()
{
  char ch;
  printf("Enter The Character : ");
  scanf("%c",&ch);
  if(ch=='a' || ch=='e' || ch=='o' || ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U'){
    printf("%cis a vowel",ch);
  }
  else{
    printf("%c is a consonant",ch);
  }
  return 0;
}