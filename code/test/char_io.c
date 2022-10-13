/* char_io.c
.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do combination between readChar and printChar syscall
 *
 */


#include "syscall.h"

int main()
{
    PrintChar(ReadChar());
    Halt();
    /* not reached */
}
