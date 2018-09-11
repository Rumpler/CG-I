#version 130

in vec3 vert;
in vec3 vertNormal;

flat in vec3 alle;
uniform vec4 mycolor;

    void main() {
 
	//gl_FragColor=vec4(alle,1.0);
	gl_FragColor=vec4(vec3(0.0f,1.0f,0.0f),1.0);
    }
