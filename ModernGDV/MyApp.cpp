#include "MyApp.h"

MyApp::MyApp( std::vector<std::string> commandline )
{

}

MyApp::~MyApp()
{

}

void MyApp::Render () {
	glClear( GL_COLOR_BUFFER_BIT );

}

const char* MyApp::GetWindowTitle()
{
	return "Modern GDV App";
}