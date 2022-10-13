#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
void moveRegister();
void ExceptionHandler(ExceptionType which);
#endif