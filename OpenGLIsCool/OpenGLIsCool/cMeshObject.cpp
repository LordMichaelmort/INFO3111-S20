#include "cMeshObject.h"

//static 
// Will start the "unique ID" at 1001 (rather than 0 or 1 or whatever)
unsigned int cMeshObject::s_NextID = 1001;

cMeshObject::cMeshObject()
{
	// Clear the glm numbers
	this->position = glm::vec3(0.0f,0.0f,0.0f);
	this->orientation = glm::vec3(0.0f,0.0f,0.0f);

	this->scale = 1.0f;	
	this->isWireframe = false;

	this->isVisible = true;		
	this->friendlyName = "UNASSIGNED";

	this->diffuseRGBA = glm::vec4(0.0f,0.0f,0.0f,1.0f);
	// Specular highlight COLOUR is white
	// Power is 1.0 (which is really "no" shininess)
	this->specularRGB_Power = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->m_ID = cMeshObject::s_NextID;
	cMeshObject::s_NextID++;

	for (unsigned int index = 0; index != cMeshObject::NUMBEROFTEXTURES; index++)
	{
		this->texRatios[index] = 0.0f;
	}

	return;
}

unsigned int cMeshObject::getUniqueID(void)
{
	return this->m_ID;
}


