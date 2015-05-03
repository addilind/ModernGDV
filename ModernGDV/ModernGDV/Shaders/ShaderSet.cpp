#include "ShaderSet.h"
#include <iostream>
#include <string>
#include <fstream>

ModernGDV::Shaders::ShaderSet::ShaderSet( ShaderLibrary* lib, const std::string& name )
	: name(name), library( lib ),
	vertexShader( 999U ), fragmentShader( 999U ), shaderProgram( 999U ), vertexArray( 999U ),
	shaderUniformModel( 999U ), shaderUniformNormal( 999U ), shaderUniformView( 999U ), shaderUniformProj( 999U ), shaderUniformLightPos( 999U ),
	shaderUniformDiffuseTextureSampler( 999U ), shaderUniformLightColor( 999U ), shaderUniformLightPower( 999U ), shaderUniformAmbientLight( 999U ), shaderUniformSpecularColor( 999U )
{
	createShaders();
	createShaderProgram();
	createVertexArray();
	loadActiveUniforms();
}

ModernGDV::Shaders::ShaderSet::~ShaderSet()
{
	if (shaderProgram < 999U)
		glDeleteProgram( shaderProgram );
	if (fragmentShader < 999U)
		glDeleteShader( fragmentShader );
	if (vertexShader < 999U)
		glDeleteShader( vertexShader );
}

void ModernGDV::Shaders::ShaderSet::Bind()
{
	//glBindVertexArray( vertexArray );
	glUseProgram( shaderProgram );

	UploadModel();
	UploadView();
	UploadProj();
	UploadTextures();
	UploadLight();
	UploadSpecularProperties();
}

void ModernGDV::Shaders::ShaderSet::Unbind()
{
}

void ModernGDV::Shaders::ShaderSet::UploadModel()
{
	if (shaderUniformModel < 999U)
		glUniformMatrix4fv( shaderUniformModel, 1, GL_FALSE, &library->model[0][0] ); //An Grafikkarte uebertragen
	if (shaderUniformNormal < 999U)
		glUniformMatrix3fv( shaderUniformNormal, 1, GL_FALSE, &library->normal[0][0] ); //An Grafikkarte uebertragens
}

void ModernGDV::Shaders::ShaderSet::UploadView()
{
	if (shaderUniformView < 999U)
		glUniformMatrix4fv( shaderUniformView, 1, GL_FALSE, &library->view[0][0] ); //An Grafikkarte uebertragen
}

void ModernGDV::Shaders::ShaderSet::UploadProj()
{
	if (shaderUniformProj < 999U)
		glUniformMatrix4fv( shaderUniformProj, 1, GL_FALSE, &library->projection[0][0] ); //An Grafikkarte uebertragen
}

void ModernGDV::Shaders::ShaderSet::UploadTextures()
{
	if (shaderUniformDiffuseTextureSampler < 999U)
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, library->diffuseTexure ); //Gegebene Textur in TEXTURE0-Slot einhängen
		glUniform1i( shaderUniformDiffuseTextureSampler, 0 ); //TEXTURE0 als diffuseTexture verwenden
	}
}

void ModernGDV::Shaders::ShaderSet::UploadLight()
{
	if (shaderUniformLightPos < 999U)
		glUniform3f( shaderUniformLightPos, library->lightPos.x, library->lightPos.y, library->lightPos.z );
	if (shaderUniformLightColor < 999U)
		glUniform3f( shaderUniformLightColor, library->lightColor.x, library->lightColor.y, library->lightColor.z );
	if (shaderUniformLightPower < 999U)
		glUniform1f( shaderUniformLightPower, library->lightPower );
	if (shaderUniformAmbientLight < 999U)
		glUniform1f( shaderUniformAmbientLight, library->ambient );
}

void ModernGDV::Shaders::ShaderSet::UploadSpecularProperties()
{
	if (shaderUniformSpecularColor < 999U)
		glUniform3f( shaderUniformSpecularColor, library->specularColor.x, library->specularColor.y, library->specularColor.z );
	if (shaderUniformSpecularExponent < 999U)
		glUniform1f( shaderUniformSpecularExponent, library->specularExponent );
}

std::vector<char> ModernGDV::Shaders::ShaderSet::readShaderFile( const char* filename )
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

void ModernGDV::Shaders::ShaderSet::createShaders()
{
	//GLSL-Dateien einlesen
	auto vertexShaderGLSL = readShaderFile( ("../Data/" + name + ".vs.glsl").c_str() );
	auto fragmentShaderGLSL = readShaderFile( ("../Data/" + name + ".fs.glsl").c_str() );
	char* vertexShaderGLSLptr = &vertexShaderGLSL[0]; //glShaderSource erwartet die Adresse eines Pointers auf die Zeichen (doppelte Dereferenzierung)
	char* fragmentShaderGLSLptr = &fragmentShaderGLSL[0];

	//Shader laden
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderGLSLptr, nullptr );
	glCompileShader( vertexShader );

	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderGLSLptr, nullptr );
	glCompileShader( fragmentShader );

	GLint result = 0;

	//auf Fehler überprüfen, falls Fehler: Exception werfen
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &result );
	if (result != 0) {
		int infoLogLength = -1;
		glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> vertexShaderErrorMessage( infoLogLength + 4 );
		vertexShaderErrorMessage[0] = 'V'; vertexShaderErrorMessage[1] = 'S'; vertexShaderErrorMessage[2] = ':'; vertexShaderErrorMessage[3] = ' ';
		glGetShaderInfoLog( vertexShader, infoLogLength, nullptr, &vertexShaderErrorMessage[4] );
		throw std::runtime_error( &vertexShaderErrorMessage[0] );
	}

	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result );
	if (result != 0) {
		int infoLogLength = -1;
		glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> fragmentShaderErrorMessage( infoLogLength + 4 );
		fragmentShaderErrorMessage[0] = 'F'; fragmentShaderErrorMessage[1] = 'S'; fragmentShaderErrorMessage[2] = ':'; fragmentShaderErrorMessage[3] = ' ';
		glGetShaderInfoLog( fragmentShader, infoLogLength, nullptr, &fragmentShaderErrorMessage[4] );
		throw std::runtime_error( &fragmentShaderErrorMessage[0] );
	}
}

void ModernGDV::Shaders::ShaderSet::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, fragmentShader );
	glAttachShader( shaderProgram, vertexShader );
	glLinkProgram( shaderProgram );

	GLint result = 0;

	//auf Fehler überprüfen, falls Fehler: Exception werfen
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &result );
	if (result != 0) {
		int infoLogLength = -1;
		glGetProgramiv( shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength );
		if (infoLogLength < 1)
			throw std::runtime_error( "Unable to link program, no error message" );
		std::vector<char> shaderProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog( shaderProgram, infoLogLength, nullptr, &shaderProgramErrorMessage[0] );
		throw std::runtime_error( &shaderProgramErrorMessage[0] );
	}
}

void ModernGDV::Shaders::ShaderSet::createVertexArray()
{
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );
}

void ModernGDV::Shaders::ShaderSet::loadActiveUniforms()
{
	GLint total = -1;
	glGetProgramiv( shaderProgram, GL_ACTIVE_UNIFORMS, &total );
	for (GLuint i = 0U; static_cast<GLint>(i)<total; ++i)  {
		GLint nameLength = -1;
		GLint size = -1;
		GLenum type = GL_ZERO;
		char uniformName[100];
		glGetActiveUniform( shaderProgram, i, sizeof( uniformName ) - 1, &nameLength, &size, &type, uniformName );
		uniformName[nameLength] = 0; //Gültigen C-String erzeugen
		GLuint location = glGetUniformLocation( shaderProgram, uniformName );
		std::string name( uniformName );

		if (name == "model")
			shaderUniformModel = location;
		else if (name == "normal")
			shaderUniformNormal = location;
		else if (name == "view")
			shaderUniformView = location;
		else if (name == "proj")
			shaderUniformProj = location;
		else if (name == "lightPos")
			shaderUniformLightPos = location;
		else if (name == "diffuseTextureSampler")
			shaderUniformDiffuseTextureSampler = location;
		else if (name == "lightColor")
			shaderUniformLightColor = location;
		else if (name == "lightPower")
			shaderUniformLightPower = location;
		else if (name == "ambientLight")
			shaderUniformAmbientLight = location;
		else if (name == "specularColor")
			shaderUniformSpecularColor = location;
		else if (name == "specularExponent")
			shaderUniformSpecularExponent = location;
		else
			std::cout << "Warn: Unknown shader uniform '" << name << "'!" << std::endl;
		
	}
}