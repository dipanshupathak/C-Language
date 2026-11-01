#include<stdio.h>
int main()
{
  int n;
  printf("Enter A Number : ");
  scanf("%d",&n);
  for(int i=2;i<=n;i++){
    if(n%i==0){ // i is a factor of n
      printf("The Given Number Is Composite\n");
    break;
    }
  }
  return 0;
}