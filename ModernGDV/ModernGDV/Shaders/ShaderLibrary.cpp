#include "ShaderLibrary.h"
#include "ShaderSet.h"
#include "../Textures/Texture.h"

ModernGDV::Shaders::ShaderLibrary::ShaderLibrary()
	: activeShader(0U), shaders(), shaderNames(), model(), normal(), projection(), view(),
	lightPos(), lightColor(), lightPower(), ambient(), specularColor(), specularExponent(),
	diffuseTexure(0U), heightTexure(0U), terrainSegSize(1.f)
{

}

ModernGDV::Shaders::ShaderLibrary::~ShaderLibrary()
{
	UnloadShaders();
}

void ModernGDV::Shaders::ShaderLibrary::UnloadShaders()
{
	shaders.clear();
	shaderNames.clear();
	activeShader = 0U;
}

void ModernGDV::Shaders::ShaderLibrary::ReloadShaders()
{
	std::vector<std::string> names;
	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader)
		names.push_back(shader->GetName() );
	shaders.clear();
	for (auto shader = names.begin(); shader != names.end(); ++shader)
		shaders.push_back( ShaderSet( this, *shader ) );
}

void ModernGDV::Shaders::ShaderLibrary::UseShader(size_t shaderID)
{
	if (activeShader == shaderID)
		return;
	shaders[activeShader].Unbind();
	activeShader = shaderID;
	shaders[shaderID].Bind();
}

void ModernGDV::Shaders::ShaderLibrary::ReapplyShader()
{
	shaders[activeShader].Unbind();
	shaders[activeShader].Bind();
}

size_t ModernGDV::Shaders::ShaderLibrary::GetShaderID(const std::string& name)
{
	auto shaderEntry = shaderNames.find( name );
	if (shaderEntry != shaderNames.end())
		return shaderEntry->second;

	shaders.push_back( ShaderSet( this, name ) );
	Log( "SLIB", "Storing shader as id ", std::to_string(shaders.size() - 1U) );
	shaderNames.insert( std::pair<const std::string, size_t>( name, shaders.size() - 1U ) );
	shaders[activeShader].Bind(); //Reload currently active shader
	return shaders.size() - 1U;
}

void ModernGDV::Shaders::ShaderLibrary::SetModel( const glm::mat4& newModel )
{
	model = newModel;
	normal = glm::mat3( glm::transpose( glm::inverse( view * model ) ) ); //Transformation f�r Normalen berechnen
	shaders[activeShader].UploadModel();
}

void ModernGDV::Shaders::ShaderLibrary::SetView( const glm::mat4& newView )
{
	view = newView;
	shaders[activeShader].UploadView();
}

void ModernGDV::Shaders::ShaderLibrary::SetProj( const glm::mat4& newProj )
{
	projection = newProj;
	shaders[activeShader].UploadProj();
}

void ModernGDV::Shaders::ShaderLibrary::SetDiffuseTex(const Textures::Texture* texture)
{
	diffuseTexure = texture->GetID();
	shaders[activeShader].UploadTextures();
}

void ModernGDV::Shaders::ShaderLibrary::SetHeightTex(const Textures::Texture* texture)
{
	heightTexure = texture->GetID();
	shaders[activeShader].UploadTerrainProperties();
}

void ModernGDV::Shaders::ShaderLibrary::SetLight(const glm::vec3& position, const glm::vec3& color, const float& power, const float& newAmbient)
{
	lightPos = position;
	lightColor = color;
	lightPower = power;
	ambient = newAmbient;
	shaders[activeShader].UploadLight();
}

void ModernGDV::Shaders::ShaderLibrary::SetSun(const glm::vec3& dir, const glm::vec3& color)
{
	sunDirection = glm::normalize(dir);
	sunColor = color;
	shaders[activeShader].UploadSun();
}

void ModernGDV::Shaders::ShaderLibrary::SetSpecularProperties(const glm::vec3& specColor, const float& specExp)
{
	specularColor = specColor;
	specularExponent = specExp;
	shaders[activeShader].UploadSpecularProperties();
}

void ModernGDV::Shaders::ShaderLibrary::SetTerrainSegmentSize(const float& segmentSize)
{
	terrainSegSize = segmentSize;
	shaders[activeShader].UploadTerrainProperties();
}

void ModernGDV::Shaders::ShaderLibrary::SetTerrainFadeDistance(const float& distance)
{
	terrainFadeDist = distance;
	shaders[activeShader].UploadTerrainProperties();
}