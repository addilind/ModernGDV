#version 330

// Eigenschaften, die ein Eingabe-Vertex aufweisen soll
in vec3 inPosition;	//Position
in vec3 inNormal;	//Normale
in vec2 inTexcoord; //Texturkoordinate

// Eigenschaften, die ZUSÄTZLICH zur Position weitergegeben werden sollen (VertexShader MÜSSEN eine Position ausgeben, deshalb ist sie immer als Ausgabe "vordefiniert")
out vec2 texcoord;		//Texturkoordinate
out vec3 position_world;//Position im Weltkoordinatensystem
out vec3 normal_cam;	//Normale im Kamerakoordinatensystem
out vec3 eyedir_cam;	//Vektor, der in Richtung Kamera zeigt (im Kamerakoordinatensystem)
out vec3 lightdir_cam;	//Vektor, der in Richtung Licht zeigt (im Kamerakoordinatensystem)

// Eigenschaften, die sich alle Eingabe-Vertices teilen (also für alle gleich sind)
uniform mat4 model;		//Modell-Transformationen
uniform mat3 normal;	//Transponiertes Inverses der Modell-Transformation fuer Normalen = transpose(inverse(view * model)
uniform mat4 view;		//View-Matrix
uniform mat4 proj;		//Projection-Matrix
uniform vec3 lightPos;	//Position der Lichtquelle in Weltkoordinaten

//diese Funktion wird für jeden Vertex einzeln aufgerufen - auf der Grafikkarte
void main() {
	position_world = (model * vec4( inPosition, 1.0f )).xyz;
	vec4 position_cam = view * vec4( position_world, 1.0f );
	gl_Position = proj * position_cam;
	
	//gl_Position ist die vordefinierte Ausgabeeigenschaft für die Position.
	//Um die Transformationen, die im C++-Teil zu einer Matrix berechnet wurden, anzuwenden, wird der Vertex mit der Matrix multipliziert.
	//3D-Koordinaten werden dabei als Vektor mit 4! Elementen angegeben, wobei das letzte Element immer 1 ist, weshalb wir den eingegebenen Vertex um eine 1 erweitern
	//Dies hat mathematische Hintergründe (sonst könnte man keine Translationen aka Verschiebungen machen)

	normal_cam = normal * inNormal;
	//Die Normale wird in das Kamerakoordinatensystem ueberfuehrt. (Siehe http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/ , warum nicht einfach view * world)

	eyedir_cam = vec3(0,0,0) - position_cam.xyz;
	lightdir_cam = (view * vec4( lightPos, 1.0f ) ).xyz - position_cam.xyz;

	texcoord = inTexcoord;
}
