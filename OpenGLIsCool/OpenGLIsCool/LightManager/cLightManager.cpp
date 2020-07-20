#include "../globalOpenGLStuff.h"	// GLFW and glad calls
#include "cLightManager.h"

#include <sstream>			// String Stream
#include <string>

sLight::sLight()
{

	// Set all the other things to some sensible value
	this->position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // rgb = highlight colour, w = power
	this->atten = glm::vec4(0.0f, 0.1f, 0.1, 10.0f);		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	this->direction = glm::vec4( 0.0f, -1.0f, 0.0f, 1.0f);	// Spot, directional lights (default is pointing down in y direction)
	
	//glm::vec4 param1;		// x = lightType, y = inner angle, z = outer angle, w = TBD
	this->SetLightType(sLight::POINT_LIGHT);
	this->SetSpotConeAngles(glm::radians(15.0f), glm::radians(45.0f));	

	//glm::vec4 param2;		// x = 0 for off, 1 for on
	this->TurnOffLight();

	// Set all the uniform variable locations to -1 (if not found, they are -1)
	this->position_UniLoc = -1;
	this->diffuse_UniLoc = -1;
	this->specular_UniLoc = -1;
	this->atten_UniLoc = -1;
	this->direction_UniLoc = -1;
	this->param1_UniLoc = -1;
	this->param2_UniLoc = -1;

	return;
}

void sLight::TurnOnLight(void)
{
	// 	glm::vec4 param2;		// x = 0 for off, 1 for on
	this->param2.x = 1.0f;		
}

void sLight::TurnOffLight(void)
{
	// 	glm::vec4 param2;		// x = 0 for off, 1 for on
	this->param2.x = 0.0f;		
}

// returns true if light is "on" (param2.x = 1)
bool sLight::isOn(void)
{
	if (this->param2.x == 0.0f)
	{
		return false;
	}
	return true;
}


void sLight::SetLightType( std::string typeAsString )
{
	// TODO:

	return;
}

void sLight::SetLightType( sLight::eLightType lightType )
{
	switch ( lightType )
	{
	case sLight::POINT_LIGHT:
		this->param1.x = 0.0f;		// Point
		break;
	case sLight::SPOT_LIGHT:
		this->param1.x = 1.0f;		// Spot
		break;
	case sLight::DIRECTIONAL_LIGHT:
		this->param1.x = 2.0f;		// Directional
		break;
	default:
		// Make point if we don't know
		// (shouldn't happen)
		this->param1.x = 0.0f;		// Point
		break;
	};

	return;
}

void sLight::SetSpotConeAngles( float innerAngleDegrees, float outerAngleDegrees )
{
	//if ( outerAngleDegrees > innerAngleDegrees )
	//{	// Switch them
	//	float temp = innerAngleDegrees;
	//	innerAngleDegrees = outerAngleDegrees;
	//	outerAngleDegrees = temp;
	//}

	//	glm::vec4 param1;		// x = lightType, y = inner angle, z = outer angle, w = TBD
	this->param1.y = innerAngleDegrees;
	this->param1.z = outerAngleDegrees;

	return;
}

void sLight::SetRelativeDirection( glm::vec3 relDirection )
{
	// To set the vec4 that's being passed
	this->direction = glm::vec4( relDirection, 1.0f );
	return;
}

cLightManager::cLightManager()
{
	for (int count = 0; count != NUMBEROFLIGHTS; count++)
	{
		this->vecLights.push_back(sLight());
	}
	return;
}

void cLightManager::LoadUniformLocations(int shaderID)
{

	// Get the uniform location for each of the lights....
	//int position_UniLoc;
	//int diffuse_UniLoc;
	//int specular_UniLoc;
	//int atten_UniLoc;
	//int direction_UniLoc;
	//int param1_UniLoc;
	//int param2_UniLoc;

	this->vecLights[0].position_UniLoc = glGetUniformLocation(shaderID, "theLights[0].position");
	this->vecLights[0].diffuse_UniLoc = glGetUniformLocation(shaderID, "theLights[0].diffuse");
	this->vecLights[0].specular_UniLoc = glGetUniformLocation(shaderID, "theLights[0].specular");
	this->vecLights[0].atten_UniLoc = glGetUniformLocation(shaderID, "theLights[0].atten");
	this->vecLights[0].direction_UniLoc = glGetUniformLocation(shaderID, "theLights[0].direction");
	this->vecLights[0].param1_UniLoc = glGetUniformLocation(shaderID, "theLights[0].param1");
	this->vecLights[0].param2_UniLoc = glGetUniformLocation(shaderID, "theLights[0].param2");

	// For light #1: 
	this->vecLights[1].position_UniLoc = glGetUniformLocation(shaderID, "theLights[1].position");
	this->vecLights[1].diffuse_UniLoc = glGetUniformLocation(shaderID, "theLights[1].diffuse");
	this->vecLights[1].specular_UniLoc = glGetUniformLocation(shaderID, "theLights[1].specular");
	this->vecLights[1].atten_UniLoc = glGetUniformLocation(shaderID, "theLights[1].atten");
	this->vecLights[1].direction_UniLoc = glGetUniformLocation(shaderID, "theLights[1].direction");
	this->vecLights[1].param1_UniLoc = glGetUniformLocation(shaderID, "theLights[1].param1");
	this->vecLights[1].param2_UniLoc = glGetUniformLocation(shaderID, "theLights[1].param2");

	// And so on...



	// Or something more sexy, maybe?:
	// Go through all the lights and set the uniform locations...
	for (unsigned int lightIndex = 0; lightIndex != NUMBEROFLIGHTS; lightIndex++ )
	{
		std::stringstream ssLightUniformName;

		//"theLights[0].position"
		ssLightUniformName << "theLights[" << lightIndex << "]."; 
		std::string lightBaseName = ssLightUniformName.str();

		// Get position location
		std::string strPosition = lightBaseName + "position";
		this->vecLights[lightIndex].position_UniLoc = glGetUniformLocation( shaderID, strPosition.c_str());

		// Diffuse...
		std::string strDiffuse = lightBaseName + "diffuse";
		this->vecLights[lightIndex].diffuse_UniLoc = glGetUniformLocation( shaderID, strDiffuse.c_str());

		// Specular...
		std::string strSpecular = lightBaseName + "specular";		// rgb = highlight colour, w = power
		this->vecLights[lightIndex].specular_UniLoc = glGetUniformLocation( shaderID, strSpecular.c_str());

		// Attenuation
		std::string strAtten = lightBaseName + "atten";		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
		this->vecLights[lightIndex].atten_UniLoc = glGetUniformLocation( shaderID, strAtten.c_str());

		// Direction
		std::string strDirection = lightBaseName + "direction";	// Spot, directional lights
		this->vecLights[lightIndex].direction_UniLoc = glGetUniformLocation( shaderID, strDirection.c_str());

		// Param1
		std::string strParam1 = lightBaseName + "param1";		// x = lightType, y = inner angle, z = outer angle, w = TBD
		this->vecLights[lightIndex].param1_UniLoc = glGetUniformLocation( shaderID, strParam1.c_str());

		// Param2
		std::string strParam2 = lightBaseName + "param2";		// x = 0 for off, 1 for on
		this->vecLights[lightIndex].param2_UniLoc = glGetUniformLocation( shaderID, strParam2.c_str());
	}

	return;
}


void cLightManager::CopyLightValuesToShader(void)
{
	// Call glUniformX() a million times...
	for (unsigned int index = 0; index != NUMBEROFLIGHTS; index++)
	{
		//glUniform4f(light0_position_loc, g_light0_position.x,
		//	g_light0_position.y, g_light0_position.z, 1.0f);		// make the 4th a 1.0, if you don't know what to make it

		// vec4 theLights[X]position;	in the shader, so glUniform4f()
		
		glUniform4f( 
			this->vecLights[index].position_UniLoc,
			this->vecLights[index].position.x, 
			this->vecLights[index].position.y, 
			this->vecLights[index].position.z, 
			1.0f );		// set 4th value to 1.0f if unsure

		glUniform4f( 
			this->vecLights[index].diffuse_UniLoc,
			this->vecLights[index].diffuse.r,
			this->vecLights[index].diffuse.g,
			this->vecLights[index].diffuse.b,
			1.0f );		// set 4th value to 1.0f if unsure

		glUniform4f( 
			this->vecLights[index].specular_UniLoc,
			this->vecLights[index].specular.r,
			this->vecLights[index].specular.g,
			this->vecLights[index].specular.b,
			this->vecLights[index].specular.w );		// set 4th value to 1.0f if unsure

		glUniform4f( 
			this->vecLights[index].atten_UniLoc,
			this->vecLights[index].atten.x,			// Constant
			this->vecLights[index].atten.y,			// Linear
			this->vecLights[index].atten.z,			// Quadratic
			this->vecLights[index].atten.w );		// set 4th value to 1.0f if unsure

		glUniform4f( 
			this->vecLights[index].direction_UniLoc,
			this->vecLights[index].direction.x,
			this->vecLights[index].direction.y,
			this->vecLights[index].direction.z,
			1.0f );		// set 4th value to 1.0f if unsure

		//vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
						// 0 = pointlight
						// 1 = spot light
						// 2 = directional light
		glUniform4f( 
			this->vecLights[index].param1_UniLoc,
			this->vecLights[index].param1.x,		// x = lightType
			this->vecLights[index].param1.y,		// y = inner angle
			this->vecLights[index].param1.z,		// z = outer angle, w = TBD
			this->vecLights[index].param1.w );		// set 4th value to 1.0f if unsure

		//vec4 param2;	// x = 0 for off, 1 for on
		glUniform4f( 
			this->vecLights[index].param2_UniLoc,
			this->vecLights[index].param2.x,		// x = 0 for off, 1 for on
			this->vecLights[index].param2.y,
			this->vecLights[index].param2.z,
			this->vecLights[index].param2.w );		// set 4th value to 1.0f if unsure

	}
}
