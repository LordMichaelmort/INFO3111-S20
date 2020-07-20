#ifndef _globalThings_HG_
#define _globalThings_HG_
// globalVariables.h

#include "cMeshObject.h"
#include "cVAOManager.h"
#include <vector>

// If it's a header, but struct, class, or extern
// NEVER the actual variable. 

void LoadAllThemodels(unsigned int program,
                      cVAOManager* pTheVAOManager);

extern std::vector< cMeshObject* > g_pVecObjects;



#endif 
