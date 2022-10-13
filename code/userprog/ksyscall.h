/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include "extra_ksyscall.h"
#include "stdint.h"
#include "sysdep.h"
void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}
int SysReadNum()
{

  GetNumUntilBlank(0);
  int len = strlen(_numberBuffer);
  if (len == 0 || error == true)
    return 0;
  bool negative = _numberBuffer[0] == '-';
  int Return = 0;
  for (int i = negative; i < len; i++)
  {
    char c = _numberBuffer[i];
    int temp;
    if (Return < 0)
    {
      temp = -Return;
    }
    else
    {
      temp = Return;
    }
    if (((2147483647 - _numberBuffer[i]) / 10 < temp) && i < len - 1)
    {
      DEBUG(dbgSys, "\nOut of integer type range\n");
      if (Return > 0)
      {
        return INT32_MAX;
        DEBUG(dbgSys, "OKE");
      }
      else
        return INT32_MIN;
    }

    if (c > '9' || c < '0')
    {
      DEBUG(dbgSys, "\nUnexpected character - (must be ranged '0' < character < '9' )\n");
      return 0;
    }

    else
    {
      Return = Return * 10 + (c - '0');
    }
  }
  if (negative)
  {
    Return = -Return;
  }
  return Return;

  return 0;
}
// put char through kernel->consoleOut->putChar();
void SysPrintNum(int num)
{
  if (num == 0)
    return kernel->synchConsoleOut->PutChar('0');
  if (num == INT32_MIN)
  {
    kernel->synchConsoleOut->PutChar('-');
    for (int i = 0; i < 10; ++i)
      kernel->synchConsoleOut->PutChar("2147483648"[i]);
    return;
  }
  if (num == INT32_MAX)
  {
    for (int i = 0; i < 10; ++i)
      kernel->synchConsoleOut->PutChar("2147483648"[i]);
    return;
  }
  if (num < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
    num = -num;
  }
  int n = 0;
  while (num)
  {
    _numberBuffer[n++] = num % 10;
    num /= 10;
  }
  for (int i = n - 1; i >= 0; --i)
    kernel->synchConsoleOut->PutChar(_numberBuffer[i] + '0');
}

void SysPrintChar(char character)
{
  kernel->synchConsoleOut->PutChar(character);
}
// function get a char through module-build nachos
char SysReadChar() { return kernel->synchConsoleIn->GetChar(); }
// function generate a random number
int SysRandomNum()
{
  srand(time(0));
  return rand() % 100;
}
// function to return an string entered from keyboard
char *SysReadString(int length)
{
  char *tempBuffer = new char[length + 1];
  for (int i = 0; i < length; i++)
  {
    char c = kernel->synchConsoleIn->GetChar();
    if (c == '\n')
    {
      break;
    }
    tempBuffer[i] = c;
    tempBuffer[i + 1] = '\0';
  }
  return tempBuffer;
}
// function transfer string from system memory to user memory
void StringSys2User(char *str, int addr)
{
  int length = strlen(str);
  for (int i = 0; i < length; i++)
  {
    kernel->machine->WriteMem(addr + i, 1, str[i]);
  }
  kernel->machine->WriteMem(addr + length, 1, '\0');
}
// function transfer string from user  memory to system memory
char *stringUser2System(int addr)
{
  int length = 0;
  // get length of string through do while loop until we come across '\0' character
  do
  {
    int Char;
    kernel->machine->ReadMem(addr + length, 1, &Char);
    length++;
    if (Char == '\0')
    {
      break;
    }
  } while (true);
  char *temp = new char[length];
  // loop to assign each cell value to the returned character array
  for (int i = 0; i < length; i++)
  {
    int Char;
    kernel->machine->ReadMem(addr + i, 1, &Char);
    temp[i] = Char;
  }
  return temp;
}
// function print a string passed buffer argurment, and Length is length of string you want to print
void SysPrintString(char *buffer, int length)
{
  for (int i = 0; i < length; i++)
  {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }
}
#endif /* ! __USERPROG_KSYSCALL_H__ */
