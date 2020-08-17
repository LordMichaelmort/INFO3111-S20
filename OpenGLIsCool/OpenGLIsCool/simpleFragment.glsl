#version 420

in vec4 fColour;		// colour
in vec4 fNormal;
in vec4 fUVx2;			// ADDED
in vec4 fVertWorldPos;	// ADDED

out vec4 outputColour;	// Added. 

// Fragment shader
struct sLight
{
	vec4 position;			
	vec4 diffuse;	
	vec4 specular;	// rgb = highlight colour, w = power
	vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 direction;	// Spot, directional lights
	vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	                // 0 = pointlight
					// 1 = spot light
					// 2 = directional light
	vec4 param2;	// x = 0 for off, 1 for on
};


const int POINT_LIGHT_TYPE = 0;
const int SPOT_LIGHT_TYPE = 1;
const int DIRECTIONAL_LIGHT_TYPE = 2;

//const int NUMBEROFLIGHTS = 10;
const int NUMBEROFLIGHTS = 10;
uniform sLight theLights[NUMBEROFLIGHTS];  	// 80 uniforms

// This is the objects colour ('material')
uniform vec4 diffuseColourRGBA;				// A is alpha transparency
uniform vec4 specularColour;

uniform vec4 eyeLocation;

// If this is true, then don't apply the lighting calculation.
// (used for wireframe and debug type objects)
// (bool is really a float, either 0.0 or non-zero)
uniform bool hasNoLighting;	

// Can't make arrays of samplers
uniform sampler2D texture0A;		// Cobblestone texture
uniform sampler2D texture0B;		// Fauci texture
uniform sampler2D texture0C;
uniform sampler2D texture0D;
uniform vec4 textureRatios;		//  = vec4( 0.0f, 1.0f, 0.0f, 0.0f );

// A "mask" or "discard" texture
uniform sampler2D textureDiscard;
uniform bool bUseDiscardTexture;	

uniform bool bTreeDiscardExample;

// CP11
uniform sampler2D textTransp;	// Texture used to sample alpha values
uniform bool bUseTranspTexture;	// If true, then use transparency texture
uniform bool bUseDiscardTransp;

// Cube map texture(s)
uniform samplerCube texCubeSkyBox01;
uniform bool bIsSkybox;			// If true, samples from cubemap

// Cubemaps can be used for other things, like reflection and refraction
uniform bool bObjectReflectsSkyBox;


vec4 calcualteLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, 
                            vec3 vertexWorldPos, vec4 vertexSpecular );
							
void main()
{
    //gl_FragColor = vec4(colour, 1.0);
	//gl_FragColor = colour;
	//outputColour = fNormal;
//	
//	outputColour = fColour;

	if ( bTreeDiscardExample )
	{
		vec4 treeColour = texture( texture0A, fUVx2.st );				// Tree texture
		float treeMaskColourBW = texture( textureDiscard, fUVx2.st ).r; 	// Tree 'mask' texture
	
		// Check to see if the mask is white or black
		// Where "white" --> Draw the tree colour
		// Where "black" --> Don't draw anything (discard)
		if ( treeMaskColourBW > 0.5f )	// "White"
		{
			outputColour.rgb = treeColour.rgb;
			outputColour.a = 1.0f;
			return;
		}
		else
		{	// Mask is "black" so draw nothing
			discard;
		}	
	}


	if ( hasNoLighting )
	{
		outputColour.rgb = diffuseColourRGBA.rgb;
		return;
	}
	
	// Skybox (cubemap) object
	if ( bIsSkybox )
	{
		// Sample from the cubemap using the inverted normals
		// uniform samplerCube texCubeSkyBox01;
		vec3 skyboxNormal = fNormal.xyz;
		// Invert so ray projected FROM sphere to inside of cubemap
		skyboxNormal = -skyboxNormal;
		
		vec4 skyPixelColour = texture(texCubeSkyBox01, skyboxNormal.xyz);
		
		// Note: No lighting 
		outputColour.rgb = skyPixelColour.rgb;
		outputColour.a = 1.0f;
		
		// Early exit
		return;
	
	}//if ( bIsSkybox )
	
	
	// For when we want to completely elimiate part of the model
	if ( bUseDiscardTexture )
	{
		vec4 textDiscard = texture( textureDiscard, fUVx2.st );
		
		// Discard is black or white
		// Just compare one of the colours, say red
		if ( textDiscard.r > 0.5f )
		{
			// Discard this fragment
			discard;
		}
	
	}//if ( bUseDiscardTexture )

	
	
	// Else regular ligthing

	// Now passing specular, too
	// Make "black"
	
	// "Sample" a pixel from the texture sampler "texture0A"
	// 					uniform sampler2D texture0A;
	vec4 texRGBAPixel_0A = texture( texture0A, fUVx2.st );
	vec4 texRGBAPixel_0B = texture( texture0B, fUVx2.st );
	vec4 texRGBAPixel_0C = texture( texture0C, fUVx2.st );
	vec4 texRGBAPixel_0D = texture( texture0D, fUVx2.st );

//	This is a uniform (see the top of the file)		
//	vec4 texRatios = vec4( 0.0f, 1.0f, 0.0f, 0.0f );


	vec4 finalTexColour =   ( texRGBAPixel_0A * textureRatios.x )   
						  + ( texRGBAPixel_0B * textureRatios.y )   
						  + ( texRGBAPixel_0C * textureRatios.z )
						  + ( texRGBAPixel_0D * textureRatios.w );
						  					  


	outputColour = calcualteLightContrib( finalTexColour.rgb,		// diffuseColourRGBA.rgb, 
										  vec3(fNormal.xyz),
										  vec3(fVertWorldPos),
										  specularColour.rgba );

	
//	outputColour.rgb += finalTexColour.rgb;
	
//	outputColour.rgb *= 0.0001f;
//	outputColour.rg += fUVx2.st;
	
	
	// With alpha blending, there is hardware 
	// that reads the 4th value (the "alpha channel")
	// directly. 
	outputColour.a = diffuseColourRGBA.a;				// Set "alpha" to 1.0f
	
	
	// Another use for cube maps is reflection and refraction
	if ( bObjectReflectsSkyBox )
	{
		vec3 viewRay = normalize(eyeLocation.xyz - fVertWorldPos.xyz);
		
		vec3 reflectionRay = reflect(viewRay, fNormal.xyz);
		
		vec4 skyPixelColour = texture(texCubeSkyBox01, reflectionRay.xyz);
		
		outputColour.rgb *= 0.0001f;
		outputColour.rgb += skyPixelColour.rgb;
	}
	
	
	// CP11
	if ( bUseTranspTexture )
	{
		// uniform sampler2D textTransp;
//		vec4 alphaTextRGBA = texture( textTransp, fUVx2.st );
//		float alphaText = (alphaTextRGBA.a + alphaTextRGBA.b + alphaTextRGBA.g)/ 3.0f;
		
		// If it's greyscale, then R = G = B (likely) so just sample R
		float alphaText = texture( textTransp, fUVx2.st ).r;
		
		// Assume range is from 0.4 to 0.6 (range of 0.2)
		alphaText -= 0.4f;
		alphaText = clamp(alphaText, 0.0f, 1.0f);
		alphaText *= 1.0f/0.2f;		// x5
		
		outputColour.a = alphaText;
		
		// You'd really see this:
		//outputColour.a = texture( textTransp, fUVx2.st ).r;
		
		// Discard transparency
//		float alphaText = texture( textTransp, fUVx2.st ).r;
//		if ( alphaText < 0.5f )
//		{
//			// MIGHT be a performance on some desktop cards. 
//			// It's NOT on mobile and usually not on colsole
//			discard;
//		}
	}
	
}


vec4 calcualteLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, 
                            vec3 vertexWorldPos, vec4 vertexSpecular )
{
	vec3 norm = normalize(vertexNormal);
	
	vec4 finalObjectColour = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	
	for ( int index = 0; index < NUMBEROFLIGHTS; index++ )
	{	
		// ********************************************************
		// is light "on"
		if ( theLights[index].param2.x == 0.0f )
		{	// it's off
			continue;
		}
		
		// Cast to an int (note with c'tor)
		int intLightType = int(theLights[index].param1.x);
		
		// We will do the directional light here... 
		// (BEFORE the attenuation, since sunlight has no attenuation, really)
		if ( intLightType == DIRECTIONAL_LIGHT_TYPE )		// = 2
		{
			// This is supposed to simulate sunlight. 
			// SO: 
			// -- There's ONLY direction, no position
			// -- Almost always, there's only 1 of these in a scene
			// Cheapest light to calculate. 

			vec3 lightContrib = theLights[index].diffuse.rgb;
			
			// Get the dot product of the light and normalize
			float dotProduct = dot( -theLights[index].direction.xyz,  
									   normalize(norm.xyz) );	// -1 to 1

			dotProduct = max( 0.0f, dotProduct );		// 0 to 1
			
			lightContrib *= dotProduct;		
			
			finalObjectColour.rgb += (vertexMaterialColour.rgb * theLights[index].diffuse.rgb * lightContrib); 
									 //+ (materialSpecular.rgb * lightSpecularContrib.rgb);
			// NOTE: There isn't any attenuation, like with sunlight.
			// (This is part of the reason directional lights are fast to calculate)


			return finalObjectColour;		
		}
		
		// Assume it's a point light 
		// intLightType = 0
		
		// Contribution for this light
		vec3 vLightToVertex = theLights[index].position.xyz - vertexWorldPos.xyz;
		float distanceToLight = length(vLightToVertex);	

		// Distance cut off (for performance)
//		if (distanceToLight > theLights[index].atten.w)
//		{
//			// Light is too far away, skip this light
//			// i.e. light is "black" at this distance
//			continue;
//		}

		vec3 lightVector = normalize(vLightToVertex);
		float dotProduct = dot(lightVector, vertexNormal.xyz);	 
		
		dotProduct = max( 0.0f, dotProduct );	
		
		vec3 lightDiffuseContrib = dotProduct * theLights[index].diffuse.rgb;
			

		// Specular 
		vec3 lightSpecularContrib = vec3(0.0f);
			
		vec3 reflectVector = reflect( -lightVector, normalize(norm.xyz) );

		// Get eye or view vector
		// The location of the vertex in the world to your eye
		vec3 eyeVector = normalize(eyeLocation.xyz - vertexWorldPos.xyz);

		// To simplify, we are NOT using the light specular value, just the object’s.
		float objectSpecularPower = vertexSpecular.w; 
		
		lightSpecularContrib = pow( max(0.0f, dot( eyeVector, reflectVector) ), objectSpecularPower )
			                   * vertexSpecular.rgb;	//* theLights[lightIndex].Specular.rgb
					   
		// Attenuation
		float attenuation = 1.0f / 
				( theLights[index].atten.x + 										
				  theLights[index].atten.y * distanceToLight +						
				  theLights[index].atten.z * distanceToLight*distanceToLight );  	
				  
		// total light contribution is Diffuse + Specular
		lightDiffuseContrib *= attenuation;
		lightSpecularContrib *= attenuation;
		
		
		// But is it a spot light
		if ( intLightType == SPOT_LIGHT_TYPE )		// = 1
		{	
		

			// Yes, it's a spotlight
			// Calcualate light vector (light to vertex, in world)
			vec3 vertexToLight = vertexWorldPos.xyz - theLights[index].position.xyz;

			vertexToLight = normalize(vertexToLight);

			float currentLightRayAngle
					= dot( vertexToLight.xyz, theLights[index].direction.xyz );
					
			currentLightRayAngle = max(0.0f, currentLightRayAngle);

			//vec4 param1;	
			// x = lightType, y = inner angle, z = outer angle, w = TBD

			// Is this inside the cone? 
			float outerConeAngleCos = cos(radians(theLights[index].param1.z));
			float innerConeAngleCos = cos(radians(theLights[index].param1.y));
							
			// Is it completely outside of the spot?
			if ( currentLightRayAngle < outerConeAngleCos )
			{
				// Nope. so it's in the dark
				lightDiffuseContrib = vec3(0.0f, 0.0f, 0.0f);
				lightSpecularContrib = vec3(0.0f, 0.0f, 0.0f);
			}
			else if ( currentLightRayAngle < innerConeAngleCos )
			{
				// Angle is between the inner and outer cone
				// (this is called the penumbra of the spot light, by the way)
				// 
				// This blends the brightness from full brightness, near the inner cone
				//	to black, near the outter cone
				float penumbraRatio = (currentLightRayAngle - outerConeAngleCos) / 
									  (innerConeAngleCos - outerConeAngleCos);
									  
				lightDiffuseContrib *= penumbraRatio;
				lightSpecularContrib *= penumbraRatio;
			}
						
		}// if ( intLightType == 1 )
		
		
					
		finalObjectColour.rgb += (vertexMaterialColour.rgb * lightDiffuseContrib.rgb)
								  + (vertexSpecular.rgb * lightSpecularContrib.rgb );
	}//for(intindex=0...
	finalObjectColour.a = 1.0f;
	
	return finalObjectColour;
}

