#version 400

// Eigenschaften, die der VertexShader zusätzlich zur Position übergeben hat
in vec2 texcoord;		//Texturkoordinate
in vec3 position_world;	//Position im Weltkoordinatensystem
in vec3 normal_cam;		//Normale im Kamerakoordinatensystem
in vec3 eyedir_cam;		//Vektor, der in Richtung Kamera zeigt (im Kamerakoordinatensystem)
in vec3 lightdir_cam;	//Vektor, der in Richtung Licht zeigt (im Kamerakoordinatensystem)

// Eigenschaften, die der FragmentShader ausgibt (normalerweise nur die Farbe, die auf den Monitor gezeichnet werden soll, als RGBA, also mit Transparenz als 4. Wert)
out vec3 endColor;		//Farbe

uniform sampler2D diffuseTextureSampler;
uniform vec3 lightPos;	//Position der Lichtquelle in Weltkoordinaten

//diese Funktion wird für jeden Pixel, der in einem durch die Vertices definierten Dreieck liegt einzeln aufgerufen - auf der Grafikkarte
void main(void) {
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 1.0f;

	vec3 diffuse = texture2D( diffuseTextureSampler, texcoord ).rgb;
	vec3 ambient = 0.1f * diffuse;
	vec3 specular = vec3(0.3,0.3,0.3);

	float lightDistance = length( lightPos - position_world );

	vec3 n = normalize( normal_cam );
	vec3 l = normalize( lightdir_cam );

	float entryangle = clamp( dot( n, l ), 0, 1 );

	vec3 e = normalize( eyedir_cam );
	vec3 reflektionsrichtung = reflect( -l, n );

	float reflectionangle = clamp( dot( e, reflektionsrichtung ), 0, 1 );
	
	endColor = ambient +
		diffuse * lightColor * lightPower * entryangle / (lightDistance * lightDistance) +
		specular * lightColor * lightPower * pow( reflectionangle, 5 ) / (lightDistance * lightDistance);
}