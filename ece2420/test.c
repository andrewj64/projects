#include<stdio.h>

int main() {

int a, b;
printf("Hello wrold!\n");
printf("Enter 2 numbers!");
scanf("%d%d", &a, &b);
printf("Sum of those two numbers is %d", sum(a, b));
return 0;
}

int sum(int a, int b) {
int c = a + b;
return c;
}
