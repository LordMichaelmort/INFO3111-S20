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

	glm::vec4 diffuseRGBA;				// RGB colour (or the object)
										// "A" for "alpha transparency"
										// 0.0f is completely transparent
										// 1.0f is solid 

	glm::vec4 specularRGB_Power;		// RGB highlight colour
										// Power (w or 4th value)
										// How "shiny" something is
										// Power STARTS at 1.0
										// Can go up to 1000s 

	glm::vec3 orientation;	//Rotation:XYZ
	float scale;
	bool isWireframe;
	bool isVisible;			// Added

	// We can assign this to whatever we want
	std::string friendlyName;

	// This is "read only"
	unsigned int getUniqueID(void);
private:
	unsigned int m_ID;
	// Note original assignment not set here, but in the cpp file (body of class)
	static unsigned int s_NextID;
};
