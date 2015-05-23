#ifdef WIN32

#include "../DebugHelper.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <DbgHelp.h>
#include <iostream>

LONG WINAPI Crash( PEXCEPTION_POINTERS ex )
{
	HANDLE hFile = CreateFile( L"moderngdv.dmp", GENERIC_READ | GENERIC_WRITE,
		0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

	if ((hFile != nullptr) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = ex;
		mdei.ClientPointers = FALSE;

		MINIDUMP_TYPE mdt = MiniDumpNormal;

		BOOL result = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(),
			hFile, mdt, (ex != nullptr) ? &mdei : 0, 0, 0 );

		if (result)
			std::cerr << "Crash. Wrote MiniDump to moderngdv.dmp" << std::endl;
		else
			std::cerr << "MiniDumpWriteDump failed: 0x" << std::hex << GetLastError() << std::endl;

		CloseHandle( hFile );
	}
	else
	{
		std::cerr << "CreateFile failed: 0x" << std::hex << GetLastError() << std::endl;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void PlattformSpecific::RegisterExceptionHandler()
{
	SetUnhandledExceptionFilter( Crash );
}

#endif