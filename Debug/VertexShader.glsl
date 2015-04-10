#version 400

// Eigenschaften, die ein Eingabe-Vertex aufweisen soll
in vec3 inPosition;	//Position
in vec3 inColor;	//Farbe

// Eigenschaften, die ZUSÄTZLICH zur Position weitergegeben werden sollen (VertexShader MÜSSEN eine Position ausgeben, deshalb ist sie immer als Ausgabe "vordefiniert")
out vec3 color;		//Farbe

// Eigenschaften, die sich alle Eingabe-Vertices teilen (also für alle gleich sind)
uniform mat4 transformation;	//Transformationen als Matix

//diese Funktion wird für jeden Vertex einzeln aufgerufen - auf der Grafikkarte
void main() {
	gl_Position = transformation * vec4( inPosition, 1.0f );
	
	//gl_Position ist die vordefinierte Ausgabeeigenschaft für die Position.
	//Um die Transformationen, die im C++-Teil zu einer Matrix berechnet wurden, anzuwenden, wird der Vertex mit der Matrix multipliziert.
	//3D-Koordinaten werden dabei als Vektor mit 4! Elementen angegeben, wobei das letzte Element immer 1 ist, weshalb wir den eingegebenen Vertex um eine 1 erweitern
	//Dies hat mathematische Hintergründe (sonst könnte man keine Translationen aka Verschiebungen machen)

	color = inColor; //Die Farbe wird einfach übernommen
}