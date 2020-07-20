#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class cMeshObject
{
public:
	cMeshObject();
	~cMeshObject()  {};
	std::string meshName;
	glm::vec3 position;		//xyz
	glm::vec4 colourRGBA;	//RGBA
	glm::vec3 orientation;	//Rotation:XYZ
	float scale;
	bool isWireframe;
	bool isVisible;			// Added

	// We can assign this to whatever we want
	std::string friendlyName;
};
