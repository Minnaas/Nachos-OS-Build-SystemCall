/* readChar.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a readNum syscall that read an character from keyboard.
 *
 */

#include "syscall.h"

int
main()
{
  char a= ReadChar();
  Halt();
  /* not reached */
}
