#ifndef _globalThings_HG_
#define _globalThings_HG_
// globalVariables.h

#include "globalOpenGLStuff.h"
#include "cMeshObject.h"
#include "cVAOManager.h"
#include <vector>
#include <glm/vec3.hpp>

// If it's a header, but struct, class, or extern
// NEVER the actual variable. 

void LoadAllThemodels(unsigned int program,
                      cVAOManager* pTheVAOManager);

extern std::vector< cMeshObject* > g_pVecObjects;


extern glm::vec3 g_TorpedoStartLocation;    // glm::vec3(0.25f, 3.5f, 4.5f);
extern bool g_bTorpedoIsMoving;             // = false



#endif 
