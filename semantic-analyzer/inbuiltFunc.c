#include <stdio.h>
#include <math.h>

int getInt()
{
    int a;
    scanf("%d", &a);

    return a;
}

void display(int a)
{
    printf("%d\n", a);
}

void displaySameline(int a)
{
    printf("%d ", a);
}

void displayChar(int c)
{
    printf("%c", c);
}