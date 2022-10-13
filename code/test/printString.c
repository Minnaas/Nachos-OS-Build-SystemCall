/* printNum.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a printString syscall that print a String out the screen
 *
 */

#include "syscall.h"

int main()
{
    char buffer[20];
    PrintString("hello world");
    Halt();
    /* not reached */
}
