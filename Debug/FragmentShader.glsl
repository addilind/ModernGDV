#version 400

// Eigenschaften, die der VertexShader zus�tzlich zur Position �bergeben hat
in vec3 color;	//Farbe

// Eigenschaften, die der FragmentShader ausgibt (normalerweise nur die Farbe, die auf den Monitor gezeichnet werden soll, als RGBA, also mit Transparenz als 4. Wert)
out vec4 endColor;		//Farbe

//diese Funktion wird f�r jeden Pixel, der in einem durch die Vertices definierten Dreieck liegt einzeln aufgerufen - auf der Grafikkarte
void main(void) {
	endColor = vec4(color, 1.0f); //Die Farbe wird einfach �bernommen, der Alpha-Wert auf 1 gesetzt
}