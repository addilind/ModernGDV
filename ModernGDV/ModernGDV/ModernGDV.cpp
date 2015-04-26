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
	app( nullptr )
{
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
		app->Render( now - lastTime );
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

GLuint ModernGDV::Driver::GetShaderProgram()
{
	return shaderProgram;
}

GLFWwindow* ModernGDV::Driver::GetWindow()
{
	return window;
}

void ModernGDV::Driver::SetProjectionMatrix( glm::mat4& projectionMat )
{
	projectionMatrix = projectionMat;
	uploadProj();
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
		return cacheEntry->second; //Gib gefundene ID zurück

	GLuint texID = loadTexture( "../Data/" + filename + ".dds" ); //Lade Textur
	textureCache.insert( std::pair<std::string, GLuint>( filename, texID ) ); //Speichere die Textur im cache
	return texID;
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

void ModernGDV::Driver::uploadProj()
{
	glUniformMatrix4fv( shaderUniformProj, 1, GL_FALSE, &projectionMatrix[0][0] ); //An Grafikkarte uebertragen
}

#define DXT1 0x31545844 // "DXT1" in ASCII
#define DXT3 0x33545844 // "DXT3" in ASCII
#define DXT5 0x35545844 // "DXT5" in ASCII
GLuint ModernGDV::Driver::loadTexture( const std::string& filename )
{
	std::ifstream file( filename, std::ifstream::binary );
	if (!file)
		throw std::runtime_error( "Cannot open texture file!" );

	char filecode[4]; //Dateiheader überprüfen
	file.read( filecode, 4 );
	if (strncmp( filecode, "DDS ", 4 ) != 0)
		throw std::runtime_error( "Invalid texture file, must be using DXT1/3/5 compression!" );

	char header[124];
	file.read( header, 124 );

	unsigned int height = *reinterpret_cast<unsigned int*>(&(header[8]));
	unsigned int width = *reinterpret_cast<unsigned int*>(&(header[12]));
	unsigned int linearSize = *reinterpret_cast<unsigned int*>(&(header[16]));
	unsigned int mipMapCount = *reinterpret_cast<unsigned int*>(&(header[24]));
	unsigned int fourCC = *reinterpret_cast<unsigned int*>(&(header[80]));

	unsigned int bufsize;

	/* Buffergröße errechnen: Falls die Textur vorberechnete MIPMAPs mitbringt, ist sie doppelt so groß */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	std::vector<char> imageData( bufsize );
	file.read( &imageData[0], bufsize );

	file.close();

	unsigned int components = (fourCC == DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		throw std::runtime_error( "Texture declares unknown compression format!" );
	}

	// OpenGL-Textur erstellen
	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	// Einzelne Bildversionen laden
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D( GL_TEXTURE_2D, level, format, width, height, 0, size, &imageData[0] + offset );

		offset += size;
		width /= 2;
		height /= 2;

		if (width < 1) width = 1;
		if (height < 1) height = 1;
	}

	return textureID;
}

void ModernGDV::Driver::deinit()
{
	for (auto tex = textureCache.begin(); tex != textureCache.end(); ++tex)
		glDeleteTextures( 1, &tex->second );
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
}