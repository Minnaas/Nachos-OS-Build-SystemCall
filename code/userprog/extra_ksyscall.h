/*This file is as a addtional file created by me. The main purpose is to
 * provide some valuale declaration and some side functions
 * to be called by functions placed in ksycall.h
 */

#ifndef EXTRA_KSYCALL_H__
#define EXTRA_KSYCALL_H__
#include "kernel.h"
#include "synchconsole.h"

#define MAX_NUM_LENGTH 11
char _numberBuffer[MAX_NUM_LENGTH + 2];
//error to check user hit a blank 
// if error =true, in SysReadnum will return 0 because of error when user type 
//example 123 3 -> return 0
bool error = false;
//function to check a char is a blank 
bool isBlank(char c)
{
    return (c == char(32) || c == char(9));
}

//function  get string input on keyboard  until the length of number is too long
//or user hit enter keyboard or user hit space keyboard
void GetNumUntilBlank(int i)
{

    char c = kernel->synchConsoleIn->GetChar();

    if (c == EOF) {
        DEBUG(dbgSys, "\nUnexpected end of file - number expected");
        return;
    }

    if (isBlank(c)) {
        DEBUG(dbgSys, "\nUnexpected white-space - number expected");
        error=true;
        return;
    }

    if(c==char(10)||c==char(13))
    {
        return ;
    }
    if(i>MAX_NUM_LENGTH-1)
    {
         DEBUG(dbgSys, "\nUnexpected number - The number is too long");
         error =true;
         return;
    }
    _numberBuffer[i]=c;
    _numberBuffer[i+1]='\0';
    //recursion
    GetNumUntilBlank(i+1);
}
 
#endif