#include "ModernGDV.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

ModernGDV::Driver::Driver()
	: glfwInitialized( false ), window( nullptr ),
	vertexShader( 0U ), fragmentShader( 0U ), shaderProgram( 0U ), vertexArray( 0U ),
	shaderUniformModel( 0U ), shaderUniformNormal( 0U ), shaderUniformView( 0U ), shaderUniformProj( 0U ), shaderUniformLightPos( 0U ),
	shaderUniformDiffuseTextureSampler( 0U ), shaderUniformLightColor( 0U ), shaderUniformLightPower( 0U ), shaderUniformAmbientLight( 0U ), shaderUniformSpecularColor( 0U ),
	aspectRatio(4.f/3.f), fov(45.f), farDist(100.f),
	textureCache(), app( nullptr )
{
	Callbacks::mgdvDriverInstance = this;

	if (!glfwInit()) //GLFW Initialisieren
		throw std::runtime_error( "Cannot initialize GLFW" );

	glfwInitialized = true;
	std::cout << "GLFW initialized" << std::endl;

	try
	{
		createWindow();
		std::cout << "Window created" << std::endl;

		createShaders();
		createShaderProgram();

		createVertexArray();

		shaderUniformModel = glGetUniformLocation( shaderProgram, "model" );
		shaderUniformNormal = glGetUniformLocation( shaderProgram, "normal" );
		shaderUniformView = glGetUniformLocation( shaderProgram, "view" );
		shaderUniformProj = glGetUniformLocation( shaderProgram, "proj" );
		shaderUniformLightPos = glGetUniformLocation( shaderProgram, "lightPos" );
		shaderUniformDiffuseTextureSampler = glGetUniformLocation( shaderProgram, "diffuseTextureSampler" );
		shaderUniformLightColor = glGetUniformLocation( shaderProgram, "lightColor" );
		shaderUniformLightPower = glGetUniformLocation( shaderProgram, "lightPower" );
		shaderUniformAmbientLight = glGetUniformLocation( shaderProgram, "ambientLight" );
		shaderUniformSpecularColor = glGetUniformLocation( shaderProgram, "specularColor" );
		shaderUniformSpecularPower = glGetUniformLocation( shaderProgram, "specularPower" );

		updateProj();

		glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );
	}
	catch (...)
	{
		deinit(); //Destructor would not be called on exception in constructor (since there never really was an instance to destruct) -> manually clean up
		throw;
	}


	std::cout << "ModernGDV Initialization finished" << std::endl;
}

ModernGDV::Driver::~Driver()
{
	deinit();
}

void ModernGDV::Driver::Run()
{
	if (app == nullptr)
		throw std::logic_error( "Must call SetApp before running" );

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose( window )) { //Dauerschleife, solange das Fenster offen ist
		glUseProgram( shaderProgram );
		
		ResetTransform();
		uploadProj();

		double now = glfwGetTime();
		app->Render( static_cast<float>( now - lastTime ) );
		lastTime = now;

		glfwSwapBuffers( window ); //Gezeichnetes auf den Monitor bringen
		glfwPollEvents(); //Tastendrücke, Mausbewegungen, Meldungen vom Betriebssystem etc. verarbeiten
	}
}

void ModernGDV::Driver::SetApp( App* application )
{
	if (application == nullptr)
		throw std::logic_error( "Passed invalid app pointer" );
	app = application;
}

void ModernGDV::Driver::FramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport( 0, 0, width, height );
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	updateProj();
}

GLuint ModernGDV::Driver::GetShaderProgram()
{
	return shaderProgram;
}

GLFWwindow* ModernGDV::Driver::GetWindow()
{
	return window;
}

void ModernGDV::Driver::SetProjectionOptions(const float& fov, const float& farPlane)
{
	this->fov = fov;
	farDist = farPlane;
	updateProj();
}

void ModernGDV::Driver::SetViewMatrix( glm::mat4& viewMat )
{
	viewMatrix = viewMat;
	uploadView();
	ResetTransform();
}

const glm::mat4* ModernGDV::Driver::Transform()
{
	return &transform;
}

void ModernGDV::Driver::SetTransform( glm::mat4& trans )
{
	transform = trans; //Transformation speichern
	uploadTransform();
}

void ModernGDV::Driver::PushTransform()
{
	transformStack.push( transform );
}

void ModernGDV::Driver::ReloadTransform()
{
	transform = transformStack.top();
	uploadTransform();
}

void ModernGDV::Driver::PopTransform( int count )
{
	for (int i = 0; i < count; ++i)
		transformStack.pop();
	if (transformStack.empty())
		ResetTransform();
	else
		ReloadTransform();
}

void ModernGDV::Driver::ResetTransform()
{
	while (!transformStack.empty())
		transformStack.pop();
	transform = glm::mat4();
	uploadTransform();
}

void ModernGDV::Driver::SetLight( const glm::vec3& position, const glm::vec3& color, const float& power, const float& ambient )
{
	glUniform3f( shaderUniformLightPos, position.x, position.y, position.z );
	glUniform3f( shaderUniformLightColor, color.x, color.y, color.z );
	glUniform1f( shaderUniformLightPower, power );
	glUniform1f( shaderUniformAmbientLight, ambient );
}

void ModernGDV::Driver::SetSpecularProperties(const glm::vec3& specularColor, const float& specularPower)
{
	glUniform3f( shaderUniformSpecularColor, specularColor.x, specularColor.y, specularColor.z );
	glUniform1f( shaderUniformSpecularPower, specularPower );
}

GLuint ModernGDV::Driver::GetTexture( const std::string& filename )
{
	//Suche nach Datei in Texturcache
	auto cacheEntry = textureCache.find( filename );
	if (cacheEntry != textureCache.end())
		return cacheEntry->second.GetID(); //Gib gefundene ID zurück

	//Speichere die Textur im cache und gib ihre ID zurück
	return textureCache.insert( std::pair<std::string, Textures::Texture>(
		filename, Textures::Texture( "../Data/" + filename + ".dds" )  ) ).first->second.GetID(); 
}

void ModernGDV::Driver::UseTexture( GLuint id )
{
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, id ); //Gegebene Textur in TEXTURE0-Slot einhängen
	glUniform1i( shaderUniformDiffuseTextureSampler, 0 ); //TEXTURE0 als diffuseTexture verwenden
}

GLuint ModernGDV::Driver::CreateVertexBuffer( const std::vector<ModernGDV::Vertex>& vertices )
{//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	GLuint vertexBuffer;
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[0], GL_STATIC_DRAW );
	return vertexBuffer;
}

void ModernGDV::Driver::createWindow()
{
	glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x Antialiasing
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 ); //OpenGL-Version 4.0 verwenden
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	window = glfwCreateWindow( 1024, 768, "GDV: Bastian Kreuzer (734877), Adrian Mueller (734922)", nullptr, nullptr ); //Fenster erstellen
	glfwSetFramebufferSizeCallback( window, Callbacks::glfwFramebufferSizeCallback );

	if (!window)
		throw std::runtime_error( "Cannot create window" );

	glfwMakeContextCurrent( window ); //Fenster für alle zukünftigen OpenGL-Aufrufe als Ziel setzen
}

std::vector<char> ModernGDV::Driver::readShaderFile( const char* filename )
{
	std::ifstream shaderFile( filename );
	if (!shaderFile)
		throw std::runtime_error( "Cannot read Shader file" );

	//Dateilänge bestimmen
	shaderFile.seekg( 0, shaderFile.end );
	int shaderLength = static_cast<int>(shaderFile.tellg());
	shaderFile.seekg( 0, shaderFile.beg );

	std::vector<char> shaderGLSL( shaderLength + 1 );
	memset( &shaderGLSL[0], 0, shaderLength + 1 ); //Speicher mit nullen füllen, damit nach einlesen der Datei der String durch ein 0-byte terminiert wird
	shaderFile.read( &shaderGLSL[0], shaderLength );

	shaderFile.close();

	return shaderGLSL;
}

void ModernGDV::Driver::createShaders()
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
		std::vector<char> vertexShaderErrorMessage( infoLogLength + 4 );
		vertexShaderErrorMessage[0] = 'V'; vertexShaderErrorMessage[1] = 'S'; vertexShaderErrorMessage[2] = ':'; vertexShaderErrorMessage[3] = ' ';
		glGetShaderInfoLog( vertexShader, infoLogLength, nullptr, &vertexShaderErrorMessage[4] );
		throw std::runtime_error( &vertexShaderErrorMessage[0] );
	}

	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> fragmentShaderErrorMessage( infoLogLength + 4 );
		fragmentShaderErrorMessage[0] = 'F'; fragmentShaderErrorMessage[1] = 'S'; fragmentShaderErrorMessage[2] = ':'; fragmentShaderErrorMessage[3] = ' ';
		glGetShaderInfoLog( fragmentShader, infoLogLength, nullptr, &fragmentShaderErrorMessage[4] );
		throw std::runtime_error( &fragmentShaderErrorMessage[0] );
	}
}

void ModernGDV::Driver::createShaderProgram()
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

void ModernGDV::Driver::createVertexArray()
{	//Speichert im Hintergrund die Eigenschaften der VertexBuffer
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );
}

void ModernGDV::Driver::uploadTransform()
{
	glUniformMatrix4fv( shaderUniformModel, 1, GL_FALSE, &transform[0][0] ); //An Grafikkarte uebertragen
	glm::mat3 normal( glm::transpose( glm::inverse( viewMatrix * transform ) ) ); //Transformation für Normalen berechnen
	glUniformMatrix3fv( shaderUniformNormal, 1, GL_FALSE, &normal[0][0] ); //An Grafikkarte uebertragens
}

void ModernGDV::Driver::uploadView()
{
	glUniformMatrix4fv( shaderUniformView, 1, GL_FALSE, &viewMatrix[0][0] ); //An Grafikkarte uebertragen
}

void ModernGDV::Driver::updateProj()
{
	projectionMatrix = glm::perspective( fov, aspectRatio, 0.1f, farDist );
	uploadProj();
}

void ModernGDV::Driver::uploadProj()
{
	glUniformMatrix4fv( shaderUniformProj, 1, GL_FALSE, &projectionMatrix[0][0] ); //An Grafikkarte uebertragen
}

void ModernGDV::Driver::deinit()
{
	for (auto tex = textureCache.begin(); tex != textureCache.end(); ++tex)
		tex->second.Unload();
	if (shaderProgram > 0U)
		glDeleteProgram( shaderProgram );
	if (fragmentShader > 0U)
		glDeleteShader( fragmentShader );
	if (vertexShader > 0U)
		glDeleteShader( vertexShader );
	if (window) {
		glfwDestroyWindow( window ); //Fenster entladen, falls vorhanden
		glfwPollEvents();
	}
	if (glfwInitialized)
		glfwTerminate(); //GLFW beenden, falls initialisiert
	Callbacks::mgdvDriverInstance = nullptr;
}