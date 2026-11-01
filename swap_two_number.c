#include<stdio.H>
int main ()
{
  int first, second, temp;
  printf("Plese Enter The First Number : ");
  scanf("%d",&first);
  printf("Now Enter The Second Number : ");
  scanf("%d",&second);
  //swapping
  temp = first;
  first = second;
  second = temp;
  printf("The Value Of Fiest Is %d And Secondb  Is %d",first, second);
  return 0;
}