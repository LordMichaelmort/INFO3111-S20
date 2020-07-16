#ifndef _cVAOManager_HG_
#define _cVAOManager_HG_

// Will load the models and place them 
// into the vertex and index buffers to be drawn

#include <string>
#include <map>

// The vertex structure 
//	that's ON THE GPU (eventually) 
// So dictated from THE SHADER
// Original layout for what matched the shader
//struct sVert		
//{
//	float x, y, z;		// added "z"
//	float r, g, b;
//};


//struct sVert_xyzw_rgba		
//{
//	sVert_xyzw_rgba()
//	{
//		this->x = this->y = this->z = this->w = 0.0f;
//		this->r = this->g = this->b = this->a = 0.0f;
//		return;
//	}
//	float x, y, z, w;		// Added 4th element ("w")
//	float r, g, b, a;		// Added 4th element ("a" for alpha)
//};

// Now our vertex shader has this "vertex layout"
// (aka what the vertex shader is expecting)
// 
//	in vec4 vPos;   	// vec3 vCol;
//	in vec4 vNormal;	// ADDED
//	in vec4 vCol;   	// vec3 vCol; 	
//	in vec4 vUVx2;		// ADDED (after the mid-term)

struct sVert_xyzw_n_rgba_UVx2
{
	sVert_xyzw_n_rgba_UVx2()
	{
		this->x = this->y = this->z = this->w = 0.0f;
		this->nx = this->ny = this->nz = this->nw = 0.0f;
		this->r = this->g = this->b = this->a = 0.0f;
		this->u1 = this->v1 = this->u2 = this->v2 = 0.0f;
		return;
	}
	float x, y, z, w;		// Added 4th element ("w")
	float nx, ny, nz, nw;	// Ignore the 4th element
	float r, g, b, a;		// Added 4th element ("a" for alpha)
	float u1, v1, u2, v2;	// 2 sets of texture ("UV") coordinates
};

struct sModelDrawInfo
{
	sModelDrawInfo(); 

	std::string meshName;

	unsigned int VAO_ID;

	unsigned int VertexBufferID;
	unsigned int VertexBuffer_Start_Index;
	unsigned int numberOfVertices;

	unsigned int IndexBufferID;
	unsigned int IndexBuffer_Start_Index;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	// Extents: Largest and smallest values ("bounding box" or "hit box")
	float maxX, maxY, maxZ;
	float minX, minY, minZ;
	float deltaX, deltaY, deltaZ;	// Length of each side of the "box" 
	                                // max - min for each side
	float maxExtent;				// Largest size
	float scaleForUnitBB;			// 1.0 / maxExtent
//	10.0f ---> 1.0		0.1    1.0/10
//  0.01f ---> 1.0    100.0    1.0/0.01 --> 100.0

	// The "local" (i.e. "CPU side" temporary array)
	//sVert* pVertices;	//  = 0;
	//sVert_xyzw_rgba* pVertices;
	sVert_xyzw_n_rgba_UVx2* pVertices;

	// The index buffer (CPU side)
	unsigned int* pIndices;
};


class cVAOManager
{
public:

	bool LoadModelIntoVAO(std::string fileName, 
						  sModelDrawInfo &drawInfo, 
						  unsigned int shaderProgramID);

	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
								 sModelDrawInfo &drawInfo);

	std::string getLastError(bool bAndClear = true);

private:

	std::map< std::string /*model name*/,
		      sModelDrawInfo /* info needed to draw*/ >
		m_map_ModelName_to_VAOID;

	// Loads the ply model file into a temporary array
	bool m_LoadTheModel( std::string fileName, 
						 sModelDrawInfo &drawInfo);

	std::string m_lastErrorString;
	void m_AppendTextToLastError(std::string text, bool addNewLineBefore = true);
};

#endif	// _cVAOManager_HG_
