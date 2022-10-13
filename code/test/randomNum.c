/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a randomNum syscall that generate  random number.
 *
 */

#include "syscall.h"

int
main()
{
  int result;
  result =  RandomNum();
  Halt();
  /* not reached */
}
