/* num_io
.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do combination between readNum and printNUm syscall
 *
 */


#include "syscall.h"

int main()
{
int n;
    PrintString("Enter an integer: ");
    n=ReadNum();
    PrintString("Print Num: ");
    PrintNum(n);
    PrintChar('\n');
    Halt();
    /* not reached */
}
