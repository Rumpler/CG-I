#version 130  

in vec3 vertex;
in vec3 normal;

vec3 vert;
vec3 vertNormal;


uniform mat4 projMatrix;
uniform mat4 modelviewMatrix;
uniform mat3 normalMatrix;
uniform vec4 mycolor;
uniform vec4 matDiffuseColor;
uniform vec4 matAmbientColor;
uniform vec4 matSpecularColor; 
uniform vec4 lightDiffuseColor;
uniform vec4 lightAmbientColor;
uniform vec4 lightSpecularColor;
uniform vec3 lightdirection;
uniform vec3 viewPos;
uniform float shininess;
out vec3 alle;

    void main() {
       vert = vertex.xyz;
      vec4 vert4=vec4(vertex,1.0);  
       vertNormal = normalMatrix * normal;
       gl_Position = projMatrix * modelviewMatrix * vert4;


	vec3 E = normalize(viewPos);
	vec3 N = normalize(vertNormal);
	vec3 L = normalize(lightdirection);
	vec3 H = normalize(E+L);

	vec3 ambient  = vec3(0);
	vec3 diffuse  =vec3(0);
	vec3 specular= vec3(0);

	float diff = max(dot(L,N), 0.0);
	float spec=0.0;
	spec = pow(max(dot(H,N), 0.0), shininess);
	 ambient  += lightAmbientColor.xyz;
	 diffuse  += lightDiffuseColor.xyz * diff;
	 specular += lightSpecularColor.xyz * spec;


	 ambient  *= matAmbientColor.xyz;
	 diffuse  *= matDiffuseColor.xyz;
	 specular *= matSpecularColor.xyz;

	alle = (ambient+diffuse+specular);
    }
