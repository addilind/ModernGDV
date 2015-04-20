#include "Shank.h"

using ModernGDV::ColorVertex;

Shank::Shank()
: vertexBuffer(0U)
{
	std::vector<ColorVertex> vertices;
	
	//Unterschenkel linke Seite
	vertices.push_back(ColorVertex(-0.10f, -0.45f, +0.10f)); // unten links vorne	0
	vertices.push_back(ColorVertex(-0.05f, -0.45f, +0.10f)); // unten rechts vorne	
	vertices.push_back(ColorVertex(-0.10f, -0.45f, -0.10f)); // unten links hinten	2
	vertices.push_back(ColorVertex(-0.05f, -0.45f, -0.10f)); // unten rechts hinten	

	vertices.push_back(ColorVertex(-0.10f, +0.05f, +0.10f)); // oben links vorne	4
	vertices.push_back(ColorVertex(-0.05f, +0.05f, +0.10f)); // oben rechts vorne		
	vertices.push_back(ColorVertex(-0.10f, +0.05f, -0.10f)); // oben links hinten	6
	vertices.push_back(ColorVertex(-0.05f, +0.05f, -0.10f)); // oben rechts hinten	

	//Unterschenkel rechte Seite
	vertices.push_back(ColorVertex(+0.05f, -0.45f, +0.10f)); // unten links vorne	8
	vertices.push_back(ColorVertex(+0.10f, -0.45f, +0.10f)); // unten rechts vorne	
	vertices.push_back(ColorVertex(+0.05f, -0.45f, -0.10f)); // unten links hinten	10
	vertices.push_back(ColorVertex(+0.10f, -0.45f, -0.10f)); // unten rechts hinten	

	vertices.push_back(ColorVertex(+0.05f, +0.05f, +0.10f)); // oben links vorne	12
	vertices.push_back(ColorVertex(+0.10f, +0.05f, +0.10f)); // oben rechts vorne		
	vertices.push_back(ColorVertex(+0.05f, +0.05f, -0.10f)); // oben links hinten	14
	vertices.push_back(ColorVertex(+0.10f, +0.05f, -0.10f)); // oben rechts hinten	

	createVertexBuffer(vertices);
}

Shank::~Shank()
{

}

void Shank::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	ColorVertex::SetLayout();
	//Unterschenkel linke Seite
	unsigned char front[10] = { 0, 1, 4, 5, 6, 7, 2, 3, 0, 1 };
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, front);

	unsigned char right[4] = { 1, 3, 5, 7 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, right);

	unsigned char left[4] = { 0, 2, 4, 6 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, left);

	//Unterschenkel rechte Seite    alle Indizes + 8
	unsigned char frontr[10] = { 8, 9, 12, 13, 14, 15, 10, 11, 8, 9 };
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, frontr);

	unsigned char rightr[4] = { 9, 11, 13, 15 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, rightr);

	unsigned char leftr[4] = { 8, 10, 12, 14 };
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, leftr);


	ColorVertex::ResetLayout();
}

void Shank::createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData)
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof(ColorVertex), &vertexBufferData[0], GL_STATIC_DRAW);
}