#version 420

uniform mat4 MVP;

uniform vec4 objectColour;

// Vertices coming INTO the vertex shader
in vec4 vCol;   	// vec3 vCol; 			
in vec4 vPos;   	// vec3 vCol;

out vec4 colour;

void main()
{
	vec3 positionXYZ = vec3( vPos.xyz );
    gl_Position = MVP * vec4(positionXYZ, 1.0);
	
	colour = vCol;
	
	// Set to essentially black (but keep the vCol variable)
	colour.rgb *= 0.001f;	

	colour.rgb += objectColour.rgb;
}
