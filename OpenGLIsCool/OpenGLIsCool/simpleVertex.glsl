#version 420

// Vertices coming INTO the vertex shader
in vec4 vPos;   	// vec3 vCol;
in vec4 vNormal;	// ADDED
in vec4 vCol;   	// vec3 vCol; 	
in vec4 vUVx2;		// ADDED (after the mid-term)		

out vec4 fColour;	// Now with "f"
out vec4 fNormal;	// ADDED
out vec4 fUVx2;		// ADDED
out vec4 fVertWorldPos;		// Vertex position in world space

//uniform mat4 MVP;
//uniform vec4 objectColour;
uniform mat4 matModel;		// "model" or "world" matrix
uniform mat4 matView;		// "view" or "camera" or "eye" matrix
uniform mat4 matProj;		// "projection" matrix (ortographic or perspective)

// Using textures as DATA, not just images
uniform sampler2D textureHeightMap;
uniform bool bUseHeightMap;
uniform vec2 textOffsetVS;
uniform mat4 matTextRotation;

void main()
{
	vec3 positionXYZ = vec3( vPos.xyz );

	// This is the code that perturbs the height map (flat terrain mesh)
	// Based on colour values.
	if ( bUseHeightMap )
	{
		//vec2 uvActaul = vUVx2.st + textOffsetVS;		// 0 to 1
		vec4 uvActaul = matTextRotation * vec4(vUVx2.st, 0.0f, 1.0f);
	
		vec4 texHeight = texture( textureHeightMap, uvActaul.st );
		
		float height = (texHeight.r + texHeight.g + texHeight.b)/3.0f;
		const float SCALERATIO = 10.0f;
		
		positionXYZ.y += (height * SCALERATIO);
	}
	// End of: Perterb of height map
	
	// Note reverse order because we need to apply these
	// in order of M, then V, then P, and matrix multiply goes "backwards"
	mat4 MVP = matProj * matView * matModel;
	
    gl_Position = MVP * vec4(positionXYZ, 1.0);
	
	fVertWorldPos = matModel * vec4(positionXYZ, 1.0);
	
	// We want to remove translation and scaling from the normals...
	// ...leaving ONLY rotation. The "inverse transpose" of a matrix does that 
	// (for 4x4 matrices)
	// Or "because math"
	fNormal = inverse(transpose(matModel)) * vec4(vNormal.xyz, 1.0f);
	
	// Copying the normals & texture coords
	fUVx2 = vUVx2;
	
	fColour = vCol;
	
//	// Set to essentially black (but keep the vCol variable)
//	fColour.rgb *= 0.001f;	
//	fColour.rgb += objectColour.rgb;
	
}
