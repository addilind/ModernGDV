#include "ModernGDV.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

ModernGDV::ModernGDV::ModernGDV( )
	: glfwInitialized( false ), window( nullptr ), vertexShader( 0U ), fragmentShader( 0U ), shaderProgram( 0U ), vertexArray( 0U ), app( nullptr )
{
	if (!glfwInit()) //GLFW Initialisieren
		throw std::runtime_error( "Cannot initialize GLFW" );

	glfwInitialized = true;
	std::cout << "GLFW initialized" << std::endl;

	createWindow();
	std::cout << "Window created" << std::endl;

	createShaders();
	createShaderProgram();

	createVertexArray();

	shaderTransform = glGetUniformLocation( shaderProgram, "transformation" );

	std::cout << "ModernGDV Initialization finished" << std::endl;
}

ModernGDV::ModernGDV::~ModernGDV()
{
	if (shaderProgram > 0U)
		glDeleteProgram( shaderProgram );
	if (fragmentShader > 0U)
		glDeleteShader( fragmentShader );
	if (vertexShader > 0U)
		glDeleteShader( vertexShader );
	if (window)
		glfwDestroyWindow( window ); //Fenster entladen, falls vorhanden
	if (glfwInitialized)
		glfwTerminate(); //GLFW beenden, falls initialisiert
}

void ModernGDV::ModernGDV::Run()
{
	if (app == nullptr)
		throw std::logic_error( "Must call SetApp before running" );


	while (!glfwWindowShouldClose( window )) { //Dauerschleife, solange das Fenster offen ist
		glUseProgram( shaderProgram );
		glm::mat4 transform;
		glUniformMatrix4fv( shaderTransform, 1, GL_FALSE, &transform[0][0] ); //Einheitsmatrix als Standard-Transformation setzen
		app->Render();

		glfwSwapBuffers( window ); //Gezeichnetes auf den Monitor bringen
		glfwPollEvents(); //Tastendrücke, Mausbewegungen, Meldungen vom Betriebssystem etc. verarbeiten
	}
}

void ModernGDV::ModernGDV::SetApp( App* application )
{
	if (application == nullptr)
		throw std::logic_error( "Passed invalid app pointer" );
	app = application;
}

GLuint ModernGDV::ModernGDV::GetShaderProgram()
{
	return shaderProgram;
}

GLFWwindow* ModernGDV::ModernGDV::GetWindow()
{
	return window;
}

void ModernGDV::ModernGDV::createWindow()
{
	glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x Antialiasing
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 ); //OpenGL-Version 4.0 verwenden
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	window = glfwCreateWindow( 1024, 768, "GDV: Bastian Kreuzer (734877), Adrian Mueller (734922)", nullptr, nullptr ); //Fenster erstellen

	if (!window)
		throw std::runtime_error( "Cannot create window" );

	glfwMakeContextCurrent( window ); //Fenster für alle zukünftigen OpenGL-Aufrufe als Ziel setzen
}

std::vector<char> ModernGDV::ModernGDV::readShaderFile( const char* filename )
{
	std::ifstream shaderFile( filename );
	if (!shaderFile)
		throw std::runtime_error( "Cannot read Shader file" );

	//Dateilänge bestimmen
	shaderFile.seekg( 0, shaderFile.end );
	int shaderLength = static_cast<int>(shaderFile.tellg());
	shaderFile.seekg( 0, shaderFile.beg );

	std::vector<char> shaderGLSL(shaderLength + 1);
	memset( &shaderGLSL[0], 0, shaderLength + 1 ); //Speicher mit nullen füllen, damit nach einlesen der Datei der String durch ein 0-byte terminiert wird
	shaderFile.read( &shaderGLSL[0], shaderLength );

	shaderFile.close();

	return shaderGLSL;
}

void ModernGDV::ModernGDV::createShaders( )
{
	//GLSL-Dateien einlesen
	auto vertexShaderGLSL = readShaderFile( "VertexShader.glsl" );
	auto fragmentShaderGLSL = readShaderFile( "FragmentShader.glsl" );
	char* vertexShaderGLSLptr = &vertexShaderGLSL[0]; //glShaderSource erwartet die Adresse eines Pointers auf die Zeichen (doppelte Dereferenzierung)
	char* fragmentShaderGLSLptr = &fragmentShaderGLSL[0];

	//Shader laden
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderGLSLptr, NULL );
	glCompileShader( vertexShader );

	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderGLSLptr, NULL );
	glCompileShader( fragmentShader );

	GLint result = GL_FALSE;

	//auf Fehler überprüfen, falls Fehler: Exception werfen
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> vertexShaderErrorMessage( infoLogLength );
		glGetShaderInfoLog( vertexShader, infoLogLength, NULL, &vertexShaderErrorMessage[0] );
		throw std::runtime_error( &vertexShaderErrorMessage[0] );
	}

	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> fragmentShaderErrorMessage( infoLogLength );
		glGetShaderInfoLog( fragmentShader, infoLogLength, NULL, &fragmentShaderErrorMessage[0] );
		throw std::runtime_error( &fragmentShaderErrorMessage[0] );
	}
}

void ModernGDV::ModernGDV::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, fragmentShader );
	glAttachShader( shaderProgram, vertexShader );
	glLinkProgram( shaderProgram );

	GLint result = GL_FALSE;

	//auf Fehler überprüfen, falls Fehler: Exception werfen
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetProgramiv( shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength );
		if (infoLogLength < 1)
			throw std::runtime_error( "Unable to link program, no error message" );
		std::vector<char> shaderProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog( shaderProgram, infoLogLength, NULL, &shaderProgramErrorMessage[0] );
		throw std::runtime_error( &shaderProgramErrorMessage[0] );
	}
}

void ModernGDV::ModernGDV::createVertexArray()
{	//Speichert im Hintergrund die Eigenschaften der VertexBuffer
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );
}