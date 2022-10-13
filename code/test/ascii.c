/* char_io.c
.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do print ascii code 
 *
 */

#include "syscall.h"

int main() {
    int i;
    PrintString("ASCII table:\n");
    for (i = 32; i <= 126; i++) {
        PrintNum(i);
        PrintChar(' ');
        PrintChar((char)i);
        PrintChar('\n');
    }
    Halt();
}
