#version 420

uniform mat4 MVP;

uniform vec4 objectColour;

// Vertices coming INTO the vertex shader
in vec3 vCol;     			
in vec3 vPos;   

out vec3 color;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
	
	// Set to essentially black (but keep the vCol variable)
	color.rgb *= 0.001f;	

	color.rgb += objectColour.rgb;
}
