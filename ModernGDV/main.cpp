//ModernGDV main.cpp - Adrian Müller

#include <stdexcept>
#include <iostream>

int main( int argc, char** argv ) {
	try {

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