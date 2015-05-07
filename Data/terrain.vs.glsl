#version 400

// Eigenschaften, die ein Eingabe-Vertex aufweisen soll
in vec3 inPosition;	//Position
//in vec3 inNormal;	//Normale
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

uniform sampler2D heightTextureSampler;
uniform float segmentSize;

//diese Funktion wird für jeden Vertex einzeln aufgerufen - auf der Grafikkarte
void main() {
	
	texcoord = inTexcoord + vec2(float(gl_InstanceID) * segmentSize,0);

	float myheight = texture(heightTextureSampler, texcoord).x; // x Rotkanal Farbwert fuer Hoehe

	vec4 position_model = vec4(inPosition, 1.0f) + vec4(gl_InstanceID * segmentSize * 2, myheight, 0.f, 0.0f);

	position_world = (model * position_model ).xyz;
	vec4 position_cam = view * vec4( position_world, 1.0f );
	gl_Position = proj * position_cam;

	float heightNegX = texture( heightTextureSampler, texcoord - vec2( segmentSize, 0.f )).x;
	float heightPosX = texture( heightTextureSampler, texcoord + vec2( segmentSize, 0.f )).x;
	float heightNegZ = texture( heightTextureSampler, texcoord - vec2( 0.f, segmentSize )).x;
	float heightPosZ = texture( heightTextureSampler, texcoord + vec2( 0.f, segmentSize )).x;

	float heightNegXNegZ = texture( heightTextureSampler, texcoord + vec2( -segmentSize, -segmentSize ) ).x;
	float heightNegXPosZ = texture( heightTextureSampler, texcoord + vec2( -segmentSize, segmentSize ) ).x;
	float heightPosXNegZ = texture( heightTextureSampler, texcoord + vec2( segmentSize, -segmentSize ) ).x;
	float heightPosXPosZ = texture( heightTextureSampler, texcoord + vec2( segmentSize, segmentSize ) ).x;

	vec3 dirNegX = vec3( -segmentSize, heightNegX - myheight, 0.f );
	vec3 dirPosX = vec3( +segmentSize, heightPosX - myheight, 0.f );
	vec3 dirNegZ = vec3( 0.f, heightNegZ - myheight, -segmentSize );
	vec3 dirPosZ = vec3( 0.f, heightPosZ - myheight, +segmentSize );

	vec3 dirNegXNegZ = vec3( -segmentSize, heightNegXNegZ - myheight, -segmentSize );
	vec3 dirNegXPosZ = vec3( -segmentSize, heightNegXPosZ - myheight, +segmentSize );
	vec3 dirPosXNegZ = vec3( +segmentSize, heightPosXNegZ - myheight, -segmentSize );
	vec3 dirPosXPosZ = vec3( +segmentSize, heightPosXPosZ - myheight, +segmentSize );
	
	normal_cam = normal * (cross( dirNegZ, dirNegX ) + cross( dirPosZ, dirPosX ) + cross(dirPosXNegZ, dirNegXNegZ) + cross(dirNegXPosZ, dirPosXPosZ));
	//Die Normale wird in das Kamerakoordinatensystem ueberfuehrt. (Siehe http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/ , warum nicht einfach view * world)

	eyedir_cam = vec3(0,0,0) - position_cam.xyz;
	lightdir_cam = (view * vec4( lightPos, 1.0f ) ).xyz - position_cam.xyz;

}
