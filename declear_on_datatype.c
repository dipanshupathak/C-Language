#include<stdio.h>
int main()
{
  int integer;
  float decimal;
  double doub;
  char character;
  printf("The Size of int is %lu bytes",sizeof(integer));
  printf("\nThe Size of float is %lu bytes",sizeof(decimal));
  printf("\nThe Size of double is %lu bytes",sizeof(doub));
  printf("\nThe Size of char is %lu bytes",sizeof(character));
}