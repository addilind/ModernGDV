#include "Torso.h"

using ModernGDV::ColorVertex;

Torso::Torso()
: vertexBuffer(0U)
{
	std::vector<ColorVertex> vertices;
	vertices.push_back(ColorVertex(+0.00f, +0.00f, +0.0f)); //Spitze Pyramide unten

	vertices.push_back(ColorVertex(-0.10f, +0.10f, +0.15f)); //Grundflaeche Pyramide links vorne
	vertices.push_back(ColorVertex(+0.10f, +0.10f, +0.15f)); //Grundflaeche Pyramide rechts vorne
	vertices.push_back(ColorVertex(-0.10f, +0.10f, -0.15f)); //Grundflaeche Pyramide links hinten
	vertices.push_back(ColorVertex(+0.10f, +0.10f, -0.15f)); //Grundflaeche Pyramide rechts hinten

	vertices.push_back(ColorVertex(-0.10f, +0.25f, +0.15f)); //kl Quader links vorne
	vertices.push_back(ColorVertex(+0.10f, +0.25f, +0.15f)); //kl Quader rechts vorne
	vertices.push_back(ColorVertex(-0.10f, +0.25f, -0.15f)); //kl Quader links hinten
	vertices.push_back(ColorVertex(+0.10f, +0.25f, -0.15f)); //kl Quader rechts hinten

	vertices.push_back(ColorVertex(-0.20f, +0.25f, +0.2f)); //Pyramidenstumpf unten links vorne
	vertices.push_back(ColorVertex(-0.20f, +0.25f, +0.2f)); //Pyramidenstumpf unten rechts vorne
	vertices.push_back(ColorVertex(-0.20f, +0.25f, -0.2f)); //Pyramidenstumpf unten links hinten
	vertices.push_back(ColorVertex(-0.20f, +0.25f, -0.2f)); //Pyramidenstumpf unten rechts hinten

	vertices.push_back(ColorVertex(-0.25f, +0.45f, +0.2f)); //Pyramidenstumpf oben links vorne
	vertices.push_back(ColorVertex(-0.25f, +0.45f, +0.2f)); //Pyramidenstumpf oben rechts vorne
	vertices.push_back(ColorVertex(-0.25f, +0.45f, -0.2f)); //Pyramidenstumpf oben links hinten
	vertices.push_back(ColorVertex(-0.25f, +0.45f, -0.2f)); //Pyramidenstumpf oben rechts hinten

	vertices.push_back(ColorVertex(-0.30f, +0.45f, +0.25f)); //Quader unten links vorne
	vertices.push_back(ColorVertex(-0.30f, +0.45f, +0.25f)); //Quader unten rechts vorne
	vertices.push_back(ColorVertex(-0.30f, +0.45f, -0.25f)); //Quader unten links hinten
	vertices.push_back(ColorVertex(-0.30f, +0.45f, -0.25f)); //Quader unten rechts hinten

	vertices.push_back(ColorVertex(-0.30f, +1.00f, +0.25f)); //Quader oben links vorne
	vertices.push_back(ColorVertex(-0.30f, +1.00f, +0.25f)); //Quader oben rechts vorne
	vertices.push_back(ColorVertex(-0.30f, +1.00f, -0.25f)); //Quader oben links hinten
	vertices.push_back(ColorVertex(-0.30f, +1.00f, -0.25f)); //Quader oben rechts hinten


}

Torso::~Torso()
{

}

void Torso::Render()
{

}