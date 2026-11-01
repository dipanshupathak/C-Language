#include<stdio.h>
int main()
{
  int a,b;
  char op;
  printf("Enter First Number : ");
  scanf("%d",&a);
  printf("Enetr Second Number : ");
  scanf("%d",&b);
  printf("Enter Operator(+,-,*,/):");
  scanf("%c",&op);//space before %c to ignore newline
  if(op=='+'){
    printf("Result = %d\n",a+b);
  }else if(op=='-'){
    printf("Result = %d\n",a-b);
  }else if(op=='*'){
    printf("Result = %d\n",a*b);
  }else if(op=='/'){
    if(b !=0)
  printf("Result = %d\n",a/b);
  else printf("Error : Division By Zero!\n");
  }else{
    printf("Invalid Operator.\n");
  }
  return 0;
}