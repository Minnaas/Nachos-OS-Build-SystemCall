/* bubbleSort.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just sort again all elemement in an array follow the certain order (descending or ascending )
 *
 */

#include "syscall.h"
#define SIZE 100
int main()
{

    int a[SIZE], n, i, temp, j, order;
    do
    {
        PrintString("Enter n (0 <= n <= 100): ");
        n = ReadNum();
    } while (n < 0 || n > 100);

    for (i = 0; i < n; i++)
    {
        PrintString("Enter a[");
        PrintNum(i);
        PrintString("]= ");
        a[i] = ReadNum();
    }

    do
    {
        PrintString("Enter sort order (1. Increasing, 2. Decreasing): ");
        order = ReadNum();
    } while (order != 1 && order != 2);

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i-1; j++)
        {
            if (order == 1)
            {
                if (a[j] > a[j + 1])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
            }
            else if (order == 2)
            {
                if(a[j]<a[j+1])
                {
                      temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
            }
        }
    }

    PrintString("Sorted array: ");
    for (i = 0; i < n; i++)
    {
        PrintNum(a[i]);
        PrintChar(' ');
    }
    PrintChar('\n');
    Halt();
    /* not reached */
}
