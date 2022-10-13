/* readNum.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a readNum syscall that read an integer type.
 *
 */

#include "syscall.h"

int
main()
{
  int value =ReadNum();
  Halt();
  /* not reached */
}
