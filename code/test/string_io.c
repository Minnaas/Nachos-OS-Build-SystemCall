/* string_io.c
.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do combination between readString and writeString syscall
 *
 */

#include "syscall.h"

int main()
{
    char buffer[100];
    int n;
    PrintString("Input length string: ");
    n=ReadNum();
    PrintString("Input string: ");
    ReadString(buffer,n);
    PrintString("Output String: ");
    PrintString(buffer);
    PrintChar('\n');
        Halt();
    /* not reached */
}
