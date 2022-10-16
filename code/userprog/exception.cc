// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "exception.h"

#define MAX_READ_STRING_LENGTH 255
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

// Change Current regiter, previous register, next register
void moveRegister()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	switch (which)
	{
	case NoException:
	{
		DEBUG(dbgSys, "Switch to system mode\n");
		SysHalt();
		break;
	}
	case PageFaultException:
	{
		DEBUG('a', "Page fault EXC: No valid translation found\n");
		SysHalt();
		break;
	}
	case ReadOnlyException:
	{
		DEBUG('a', "Read only EXC: Write attempted to page marked\n");
		SysHalt();
		break;
	}

	case BusErrorException:

	{
		DEBUG('a', "Bus error EXC: Translation resulted in an in valid physical address\n");
		SysHalt();
		break;
	}

	case AddressErrorException:
	{
		DEBUG('a', "Address error EXC: unaligned reference or one that was beyond the system\n");
		SysHalt();
		break;
	}
	case OverflowException:
	{
		DEBUG('a', "Overflow EXC: integer overflow in add or sub\n");
		SysHalt();
		break;
	}

	case IllegalInstrException:
	{

		DEBUG('a', "Illegal instructions EXC: Unimplemented or reserved insrt\n");
		SysHalt();
		break;
	}

	case NumExceptionTypes:
	{
		 cerr << "Error " << which << " occurs\n";
            SysHalt();
            ASSERTNOTREACHED();
			break;
	}
		
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
		{
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;
		}
		case SC_Add:
		{
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			/* Modify return point */
			moveRegister();

			return;

			ASSERTNOTREACHED();

			break;
		}
		case SC_PrintNum:
		{
			int num = kernel->machine->ReadRegister(4); // Get number user passed as argument at Register 4
			SysPrintNum(num);
			return moveRegister();
		}
		case SC_ReadNum:
		{
			int result = SysReadNum();
			kernel->machine->WriteRegister(2, result); // write the result to register 2
			return moveRegister();
		}
		case SC_PrintChar:
		{
			char character = (char)kernel->machine->ReadRegister(4); // Get char user passed as argument at Register 4
			SysPrintChar(character);
			return moveRegister();
			break;
		}
		case SC_ReadChar:
		{
			char result = SysReadChar();
			kernel->machine->WriteRegister(2, (int)result);
			return moveRegister();
		}
		case SC_RandomNum:
		{
			int result;
			result = SysRandomNum();
			DEBUG(dbgSys, "\nRandom number: " << result << "\n");
			kernel->machine->WriteRegister(2, result);
			return moveRegister();
		}
		case SC_ReadString:
		{
			int memPtr = kernel->machine->ReadRegister(4);
			int length = kernel->machine->ReadRegister(5);
			char *buffer = SysReadString(length);
			StringSys2User(buffer, memPtr);
			delete[] buffer;
			return moveRegister();
		}
		case SC_PrintString:
		{
			int memPtr = kernel->machine->ReadRegister(4); // read address of C-string
			char *buffer = stringUser2System(memPtr);
			SysPrintString(buffer, strlen(buffer));
			delete[] buffer;
			return moveRegister();
		}
		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
