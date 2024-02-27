#include<stdio.h>
// int main()
// {
//     fputs("hello stdin\n", stdout);
//     fputs("hello stdout\n", stdout);
//     fputs("hello stderr\n", stdout);
//     return 0;
// }
//
#include<stdio.h>
#define PRINT_A 0x1 //0000 0001
#define PRINT_B 0x2 //0000 0010
#define PRINT_C 0x4 //0000 0100
#define PRINT_D 0x8 //0000 1000
#define PRINT_DFL 0x0
void Show(int flags)
{
    if (flags & PRINT_A)  printf("hello A\n");
    if (flags & PRINT_B)  printf("hello B\n");
    if (flags & PRINT_C)  printf("hello C\n");
    if (flags & PRINT_D)  printf("hello D\n");
    if (flags == PRINT_DFL) printf("hello Default\n");
}
int main()
{
    printf("PRINT_DFL:\n");
    Show(PRINT_DFL);
    printf("PRINT_A\n");
    Show(PRINT_A);
    printf("PRINT_B\n");
    Show(PRINT_B);
    printf("PRINT_A 和 PRINT_B\n");
    Show(PRINT_A | PRINT_B);
    printf("PRINT_C 和 PRINT_D\n");
    Show(PRINT_C | PRINT_D);
    printf("PRINT all:\n");
    Show(PRINT_A | PRINT_B | PRINT_C | PRINT_D);
    return 0;
}
