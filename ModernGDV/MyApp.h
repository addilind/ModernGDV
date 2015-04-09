#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"

#include <vector>

class MyApp : public ModernGDV::App
{
public:
	MyApp( std::vector<std::string> commandline );
	virtual ~MyApp();

	virtual void Render();
	virtual const char* GetWindowTitle();
};

#endif