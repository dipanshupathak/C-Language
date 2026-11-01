#include<stdio.h>
int main()
{
  int first, second;
  printf("Plese enter The First Numbeer : ");
  scanf("%d",&first);
  printf("Now Enter The Second Number : ");
  scanf("%d",&second);
  printf("Here are teh resultes of the operations\n");
  printf("\n%d + %d = %d", first, second,(first + second));
  printf("\n%d - %d = %d", first, second, (first - second));
  printf("\n%d * %d = %d", first, second, (first * second));
  printf("\n%d / %d = %d", first, second, (first * second));
  printf("\n%d % %d = %d", first, second, (first % second));
  return 0;
}