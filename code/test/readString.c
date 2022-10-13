/* printChar.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a readString syscall that read a string from user's input
 *
 */


#include "syscall.h"

int main()
{
    char buffer[100];
    ReadString(buffer,20);
    PrintChar('\n');
    Halt();
    /* not reached */
}
