#include "Torso.h"

using ModernGDV::ColorVertex;

Torso::Torso()
: vertexBuffer(0U)
{

	//shaderTransform = glGetUniformLocation(mgdv->GetShaderProgram(), "transformation");

	//std::vector<ColorVertex> vertexBufferData;

	std::vector<ColorVertex> vertices;
	vertices.push_back(ColorVertex(+0.00f, +0.00f, +0.0f)); //Spitze Pyramide unten	0

	vertices.push_back(ColorVertex(-0.10f, +0.10f, +0.15f)); //Grundflaeche Pyramide links vorne	
	vertices.push_back(ColorVertex(+0.10f, +0.10f, +0.15f)); //Grundflaeche Pyramide rechts vorne	2
	vertices.push_back(ColorVertex(-0.10f, +0.10f, -0.15f)); //Grundflaeche Pyramide links hinten	
	vertices.push_back(ColorVertex(+0.10f, +0.10f, -0.15f)); //Grundflaeche Pyramide rechts hinten	4

	vertices.push_back(ColorVertex(-0.10f, +0.25f, +0.15f)); //kl Quader links vorne	
	vertices.push_back(ColorVertex(+0.10f, +0.25f, +0.15f)); //kl Quader rechts vorne	6
	vertices.push_back(ColorVertex(-0.10f, +0.25f, -0.15f)); //kl Quader links hinten	
	vertices.push_back(ColorVertex(+0.10f, +0.25f, -0.15f)); //kl Quader rechts hinten	8

	vertices.push_back(ColorVertex(-0.20f, +0.25f, +0.2f)); //Pyramidenstumpf unten links vorne
	vertices.push_back(ColorVertex(+0.20f, +0.25f, +0.2f)); //Pyramidenstumpf unten rechts vorne	10
	vertices.push_back(ColorVertex(-0.20f, +0.25f, -0.2f)); //Pyramidenstumpf unten links hinten
	vertices.push_back(ColorVertex(+0.20f, +0.25f, -0.2f)); //Pyramidenstumpf unten rechts hinten	12

	vertices.push_back(ColorVertex(-0.25f, +0.45f, +0.2f)); //Pyramidenstumpf oben links vorne
	vertices.push_back(ColorVertex(+0.25f, +0.45f, +0.2f)); //Pyramidenstumpf oben rechts vorne		14
	vertices.push_back(ColorVertex(-0.25f, +0.45f, -0.2f)); //Pyramidenstumpf oben links hinten
	vertices.push_back(ColorVertex(+0.25f, +0.45f, -0.2f)); //Pyramidenstumpf oben rechts hinten	16

	vertices.push_back(ColorVertex(-0.30f, +0.45f, +0.25f)); //Quader unten links vorne
	vertices.push_back(ColorVertex(+0.30f, +0.45f, +0.25f)); //Quader unten rechts vorne	18
	vertices.push_back(ColorVertex(-0.30f, +0.45f, -0.25f)); //Quader unten links hinten
	vertices.push_back(ColorVertex(+0.30f, +0.45f, -0.25f)); //Quader unten rechts hinten	20

	vertices.push_back(ColorVertex(-0.30f, +1.00f, +0.25f)); //Quader oben links vorne
	vertices.push_back(ColorVertex(+0.30f, +1.00f, +0.25f)); //Quader oben rechts vorne		22
	vertices.push_back(ColorVertex(-0.30f, +1.00f, -0.25f)); //Quader oben links hinten
	vertices.push_back(ColorVertex(+0.30f, +1.00f, -0.25f)); //Quader oben rechts hinten	24


	createVertexBuffer(vertices);
}

Torso::~Torso()
{

}

void Torso::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	ColorVertex::SetLayout();

	unsigned char front[15] = { 0, 1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 23, 24 };
	glDrawElements(GL_TRIANGLE_STRIP, 15, GL_UNSIGNED_BYTE, front);	

	unsigned char left[13] = { 0, 3, 1, 7, 5, 11, 9, 15, 13, 19, 17, 23, 21};
	glDrawElements(GL_TRIANGLE_STRIP, 13, GL_UNSIGNED_BYTE, left);
	
	unsigned char right[13] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 };
	glDrawElements(GL_TRIANGLE_STRIP, 13, GL_UNSIGNED_BYTE, right);

	unsigned char back[13] = { 0, 4, 3, 8, 7, 12, 11, 16, 15, 20, 19, 24, 23 };
	glDrawElements(GL_TRIANGLE_STRIP, 13, GL_UNSIGNED_BYTE, back);

	ColorVertex::ResetLayout();
}

void Torso::createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData)
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof(ColorVertex), &vertexBufferData[0], GL_STATIC_DRAW);
}