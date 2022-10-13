/* printChar.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a printNum syscall that print a chacacter out the screen
 *
 */


#include "syscall.h"

int main()
{
    PrintChar('u');
    PrintChar('\n');
    Halt();
    /* not reached */
}
