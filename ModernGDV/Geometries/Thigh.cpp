#include "Thigh.h"

using ModernGDV::ColorVertex;

Thigh::Thigh()
: vertexBuffer(0U)
{
	std::vector<ColorVertex> vertices;

	vertices.push_back(ColorVertex(-0.075f, -0.50f, +0.075f)); //Oberschenekl unten links vorne	0
	vertices.push_back(ColorVertex(+0.075f, -0.50f, +0.075f)); //Oberschenekl unten rechts vorne	
	vertices.push_back(ColorVertex(-0.075f, -0.50f, -0.075f)); //Oberschenekl unten links hinten	2
	vertices.push_back(ColorVertex(+0.075f, -0.50f, -0.075f)); //Oberschenekl unten rechts hinten	

	vertices.push_back(ColorVertex(-0.075f, +0.05f, +0.075f)); //Oberschenekl oben links vorne	4
	vertices.push_back(ColorVertex(+0.075f, +0.05f, +0.075f)); //Oberschenekl oben rechts vorne		
	vertices.push_back(ColorVertex(-0.075f, +0.05f, -0.075f)); //Oberschenekl oben links hinten	6
	vertices.push_back(ColorVertex(+0.075f, +0.05f, -0.075f)); //Oberschenekl oben rechts hinten	

	createVertexBuffer(vertices);
}

Thigh::~Thigh()
{

}

void Thigh::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	ColorVertex::SetLayout();

	unsigned char front[10] = { 0, 1, 4, 5, 6, 7, 2, 3, 0, 1 };
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, front);

	unsigned char right[4] = { 1, 3, 5 ,7 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, right);

	unsigned char left[4] = { 0, 2, 4, 6 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, left);

	ColorVertex::ResetLayout();
}

void Thigh::createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData)
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof(ColorVertex), &vertexBufferData[0], GL_STATIC_DRAW);
}