#version 400

// Eigenschaften, die ein Eingabe-Vertex aufweisen soll
in vec3 inPosition;	//Position
in vec3 inNormal;	//Normale
in vec2 inTexcoord; //Texturkoordinate

// Eigenschaften, die ZUS�TZLICH zur Position weitergegeben werden sollen (VertexShader M�SSEN eine Position ausgeben, deshalb ist sie immer als Ausgabe "vordefiniert")
out vec2 texcoord;		//Texturkoordinate
out vec3 position_world;//Position im Weltkoordinatensystem
out vec3 normal_cam;	//Normale im Kamerakoordinatensystem
out vec3 eyedir_cam;	//Vektor, der in Richtung Kamera zeigt (im Kamerakoordinatensystem)
out vec3 lightdir_cam;	//Vektor, der in Richtung Licht zeigt (im Kamerakoordinatensystem)

// Eigenschaften, die sich alle Eingabe-Vertices teilen (also f�r alle gleich sind)
uniform mat4 model;		//Modell-Transformationen
uniform mat3 normal;	//Transponiertes Inverses der Modell-Transformation fuer Normalen = transpose(inverse(view * model)
uniform mat4 view;		//View-Matrix
uniform mat4 proj;		//Projection-Matrix
uniform vec3 lightPos;	//Position der Lichtquelle in Weltkoordinaten

uniform sampler2D heightTextureSampler;
uniform float segmentSize;

//diese Funktion wird f�r jeden Vertex einzeln aufgerufen - auf der Grafikkarte
void main() {
	
	texcoord = inTexcoord + vec2(float(gl_InstanceID) * segmentSize,0);

	vec4 position_model = vec4(inPosition, 1.0f) +
		vec4(gl_InstanceID * segmentSize * 2, texture(heightTextureSampler, texcoord).x, 0.f, 0.0f);

	position_world = (model * position_model ).xyz;
	vec4 position_cam = view * vec4( position_world, 1.0f );
	gl_Position = proj * position_cam;
	
	normal_cam = normal * inNormal;
	//Die Normale wird in das Kamerakoordinatensystem ueberfuehrt. (Siehe http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/ , warum nicht einfach view * world)

	eyedir_cam = vec3(0,0,0) - position_cam.xyz;
	lightdir_cam = (view * vec4( lightPos, 1.0f ) ).xyz - position_cam.xyz;

}
