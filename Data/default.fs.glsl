#version 400

// Eigenschaften, die der VertexShader zusätzlich zur Position übergeben hat
in vec2 texcoord;		//Texturkoordinate
in vec3 position_world;	//Position im Weltkoordinatensystem
in vec3 normal_cam;		//Normale im Kamerakoordinatensystem
in vec3 eyedir_cam;		//Vektor, der in Richtung Kamera zeigt (im Kamerakoordinatensystem)
in vec3 lightdir_cam;	//Vektor, der in Richtung Licht zeigt (im Kamerakoordinatensystem)

// Eigenschaften, die der FragmentShader ausgibt (normalerweise nur die Farbe, die auf den Monitor gezeichnet werden soll, als RGBA, also mit Transparenz als 4. Wert)
out vec4 endColor;		//Farbe

uniform sampler2D diffuseTextureSampler;
uniform vec3 lightPos;	//Position der Lichtquelle in Weltkoordinaten
uniform vec3 lightColor;
uniform float lightPower;
uniform float ambientLight;
uniform vec3 specularColor;
uniform float specularExponent;

//diese Funktion wird für jeden Pixel, der in einem durch die Vertices definierten Dreieck liegt einzeln aufgerufen - auf der Grafikkarte
void main(void) {

	vec4 diffuse = texture( diffuseTextureSampler, texcoord );
	vec3 ambient = ambientLight * diffuse.rgb;

	float lightDistance = length( lightPos - position_world );

	vec3 n = normalize( normal_cam );
	vec3 l = normalize( lightdir_cam );

	float entryangle = clamp( dot( n, l ), 0, 1 );

	vec3 e = normalize( eyedir_cam );
	vec3 reflektionsrichtung = reflect( -l, n );

	float reflectionangle = clamp( dot( e, reflektionsrichtung ), 0, 1 );
	
	endColor = vec4(ambient +
		diffuse.rgb * lightColor * lightPower * entryangle / (lightDistance * lightDistance) +
		specularColor * lightColor * lightPower * pow( reflectionangle, specularExponent ) / (lightDistance * lightDistance), diffuse.a);
}