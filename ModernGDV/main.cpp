//ModernGDV main.cpp - Adrian Müller

#include <stdexcept>
#include <iostream>
#include <vector>

#include "ModernGDV/ModernGDV.h"
#include "MyApp.h"
#include <iomanip>
#include "PlatformSpecific/DebugHelper.h"

void printManual()
{
	std::cout << "W; S\t\tKamera vorwaerts, rueckwaerts bewegen\n"
		 "A; D\t\tKamera nach rechts, nach links bewegen\n"
		 "Shift; Strg\tKamera auf / ab bewegen\n"
		 "Pfeiltasten \tKamera drehen\n"
		 "Bild hoch\tHeranzoomen\n"
		 "Bild runter\tHerauszoomen\n"
		 "1\t\tTransformationen der Roboter nicht aktualisieren\n"
		 "2\t\tPiste nicht weiterschieben\n"
		 "3\t\tWireframe - Ansicht umschalten\n"
		 "4\t\tShader neu laden\n"
		 "5\t\tLampe im LookAt - Punkt zeichnen\n"
		 "6\t\tLampe schwaecher machen (aktueller Wert in Konsole)\n"
		 "7\t\tLampe stärker machen\n"
		 "J; L\t\tVordersten Roboter nach rechts bzw. nach links neigen\n" << std::endl;
}

int main( int argc, char** argv ) {
	try{
		PlatformSpecific::RegisterExceptionHandler();

		std::cout << "ModernGDV Build " __DATE__ << std::endl; //Banner auf Konsole ausgeben
		printManual();

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