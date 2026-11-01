#include <stdio.h>
int main() {
char name[] = "NEHA";
printf("Characters in the string:\n");
for(int i = 0; name[i] != '\0'; i++) {
printf("%c ", name[i]);
}
return 0;
}