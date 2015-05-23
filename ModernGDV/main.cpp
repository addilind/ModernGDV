//ModernGDV main.cpp - Adrian Müller

#include <stdexcept>
#include <iostream>
#include <vector>

#include "ModernGDV/ModernGDV.h"
#include "MyApp.h"
#include <iomanip>
#include "PlatformSpecific/DebugHelper.h"

int main( int argc, char** argv ) {
	try{
		PlatformSpecific::RegisterExceptionHandler();

		std::cout << "ModernGDV Build " __DATE__ << std::endl; //Banner auf Konsole ausgeben
		std::clog << std::fixed << std::setprecision( 4 );

		//Kommandozeilenparameter in vector lesen
		std::vector<std::string> commandline;
		for (int i = 0; i < argc; ++i)
			commandline.push_back( std::string( argv[i] ) );

		ModernGDV::Driver mgdv;
		{
			MyApp myApp( commandline, &mgdv );
			mgdv.Run();
			mgdv.SetApp( nullptr );
		}
		
		return 0;
	}
	catch (std::exception& ex) {
		std::cerr << "\nUnhandled exception: " << ex.what() << "\n\n";
		system( "pause" );
		return -1;
	}
	catch ( ... ) {
		std::cerr << "\nUnhandled exception: Unknown exception\n\n";
		system( "pause" );
		return -1;
	}
}