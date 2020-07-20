#include "cMeshObject.h"

//static 
// Will start the "unique ID" at 1001 (rather than 0 or 1 or whatever)
unsigned int cMeshObject::s_NextID = 1001;

cMeshObject::cMeshObject()
{
	// Clear the glm numbers
	this->position = glm::vec3(0.0f,0.0f,0.0f);
	this->colourRGBA = glm::vec4(0.0f,0.0f,0.0f,1.0f);
	this->orientation = glm::vec3(0.0f,0.0f,0.0f);

	this->scale = 1.0f;	
	this->isWireframe = false;

	this->isVisible = true;		
	this->friendlyName = "UNASSIGNED";

	this->m_ID = cMeshObject::s_NextID;
	cMeshObject::s_NextID++;

	return;
}

unsigned int cMeshObject::getUniqueID(void)
{
	return this->m_ID;
}


