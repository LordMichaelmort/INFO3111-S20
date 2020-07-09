#include "cMeshObject.h"

cMeshObject::cMeshObject()
{
	// Clear the glm numbers
	this->position = glm::vec3(0.0f,0.0f,0.0f);
	this->colourRGBA = glm::vec4(0.0f,0.0f,0.0f,1.0f);
	this->orientation = glm::vec3(0.0f,0.0f,0.0f);

	this->scale = 1.0f;	
	this->isWireframe = false;

	return;
}

