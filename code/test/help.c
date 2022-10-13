/* num_io
.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do print out screen some of information about my team and descript briefly 
 *  about my  sort and acsii program
 *
 */


#include "syscall.h"

int main()
{
    PrintString("***Our team:\n");
    PrintString("--20120605 Phan Nhat Trieu\n");
    PrintString("--20120614 Nguyen Anh Tuan\n");
    PrintString("--20120588 Le Quang Tho\n");
    PrintString("  ->>> ASCII: Write User's Ascii program and then go into Makefile at test folder\nmake some the same step instroduced in document\nFirst you do make ascii and then type ..//build.linux//nachos -x acsii -d u");
    PrintString("  ->> Do something like ascii program\nwhen program launch you need do some following step:\n\n");
    PrintString("\t- Enter n (the length of the array, 0 <= n <= 100)\n");
    PrintString("\t- Enter n elements of the array\n");
    PrintString("\t- Enter n (the length of the array, 0 <= n <= 100)\n");
    PrintString("\t- Enter n elements of the array\n");
    PrintString(
        "\t- Enter the order you want to sort the array with (1: increasing, "
        "2: decreasing)\n");
    PrintString(
        "\t- The program will print out the sorted array and then exit");
        Halt();
}
