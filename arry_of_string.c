#include <stdio.h>
int main() {
char fruits[4][10] = {
"Apple",
"Mango",
"Grapes",
"Banana"
};
printf("List of Fruits:\n");
for(int i = 0; i < 4; i++) {
printf("%s\n", fruits[i]);
}
return 0;
}