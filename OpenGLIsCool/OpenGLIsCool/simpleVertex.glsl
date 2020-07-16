#version 420

// Vertices coming INTO the vertex shader
in vec4 vPos;   	// vec3 vCol;
in vec4 vNormal;	// ADDED
in vec4 vCol;   	// vec3 vCol; 	
in vec4 vUVx2;		// ADDED (after the mid-term)		

out vec4 fColour;	// Now with "f"
out vec4 fNormal;	// ADDED
out vec4 fUVx2;		// ADDED

uniform mat4 MVP;
uniform vec4 objectColour;

void main()
{
	vec3 positionXYZ = vec3( vPos.xyz );
    gl_Position = MVP * vec4(positionXYZ, 1.0);
	
	// Copying the normals & texture coords
	fNormal = vNormal;
	fUVx2 = vUVx2;
	
	fColour = vCol;
	
	// Set to essentially black (but keep the vCol variable)
	fColour.rgb *= 0.001f;	
	fColour.rgb += objectColour.rgb;
	
}
