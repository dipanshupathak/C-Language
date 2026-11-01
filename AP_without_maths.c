#include<stdio.h>
int main()
{
  int n; // itni baar loop chalega
  printf("Enter The Number : ");
  scanf("%d",&n);
  // 1 3 5 7 9 ... upto n number of terms
  // we are going to use extra variables
  int a = 4;
  for(int i=1;i<=n;i++){
    printf("%d ",a);
    a = a + 3;
  }
  return 0;
}