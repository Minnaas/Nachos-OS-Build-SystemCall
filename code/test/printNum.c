/* printNum.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a printNum syscall that print a number out the screen
 *
 */

#include "syscall.h"

int main()
{
    PrintNum(2345);
    PrintString("\n");
    Halt();
    /* not reached */
}
