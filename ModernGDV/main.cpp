//ModernGDV main.cpp - Adrian M�ller

#include <stdexcept>
#include <iostream>
#include <vector>

#include "ModernGDV/ModernGDV.h"
#include "MyApp.h"

int main( int argc, char** argv ) {
	try {
		std::cout << "ModernGDV Build " __DATE__ << std::endl; //Banner auf Konsole ausgeben

		//Kommandozeilenparameter in vector lesen
		std::vector<std::string> commandline;
		for (int i = 0; i < argc; ++i)
			commandline.push_back( std::string( argv[i] ) );

		ModernGDV::ModernGDV mgdv;

		MyApp myApp( commandline );
		mgdv.SetApp( &myApp );

		mgdv.Run();
		
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