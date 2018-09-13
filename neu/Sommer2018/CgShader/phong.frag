#version 130

in vec3 vert;
in vec3 vertNormal;

uniform vec4 matDiffuseColor;
uniform vec4 matAmbientColor;
uniform vec4 matSpecularColor; 
uniform vec4 lightDiffuseColor;
uniform vec4 lightAmbientColor;
uniform vec4 lightSpecularColor;
uniform vec3 lightdirection;
uniform vec3 viewPos;
uniform float shininess;

    void main() {
       	vec3 E = normalize(-viewPos);
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

	vec3 alle = (ambient+diffuse+specular);
	gl_FragColor=vec4(alle,1.0);
	//gl_FragColor=vec4(vec3(0.0f,0.0f,1.0f),1.0);
    }
