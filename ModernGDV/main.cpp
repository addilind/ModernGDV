//ModernGDV main.cpp - Adrian Müller

#include <stdexcept>
#include <iostream>
#include <vector>

#include "ModernGDV/ModernGDV.h"
#include "MyApp.h"
#include "Teil1.h"
#include "Teil2.h"
#include "Teil3.h"

int main( int argc, char** argv ) {
	try {
		std::cout << "ModernGDV Build " __DATE__ << std::endl; //Banner auf Konsole ausgeben

		//Kommandozeilenparameter in vector lesen
		std::vector<std::string> commandline;
		for (int i = 0; i < argc; ++i)
			commandline.push_back( std::string( argv[i] ) );

		std::cout << "Aufgabe: ";
		char input = 0;
		std::cin >> input;

		ModernGDV::ModernGDV mgdv;
		switch (input)
		{
		case '1': {
			Teil1 t1( commandline, &mgdv );
			mgdv.Run();
			break; }
		case '2': {
			Teil2 t2(commandline, &mgdv);
			mgdv.Run();
			break; }
		case '3': {
			Teil3 t3(commandline, &mgdv);
			mgdv.Run();
			break; }
		default: {
			MyApp myApp( commandline, &mgdv );
			mgdv.Run();
			break; }
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