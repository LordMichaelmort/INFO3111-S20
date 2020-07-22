// Here's where all the models are loaded into
// the VAO and the "scene" 

#include "globalThings.h"

#include "cVAOManager.h"
#include "cMeshObject.h"

void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager, 
                       std::string modelsToLoad );


void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager )
{
    {// Load the space shuttle, too
        sModelDrawInfo mdiIsosphere;
        pTheVAOManager->LoadModelIntoVAO("assets/models/ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply",
                                          mdiIsosphere, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mdiATAT;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_atat_xyz_n_rgba_uv.ply",
                                         mdiATAT, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mdiSpeeder;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_Star Wars Snowspeeder_xyz_n_rgba_uv.ply",
                                         mdiSpeeder, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mditerrain;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_terrain_xyz_n_rgba_uv.ply",
                                         mditerrain, program);
    }    // ENDOF: Loading the models

     // Add to the list of things to draw
    cMeshObject* pISOBall = new cMeshObject();
    pISOBall->meshName = "assets/models/ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply";
    pISOBall->colourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    pISOBall->position.z = 0.0f;
    pISOBall->isWireframe = true;
    // If this is false, just don't draw it.
    pISOBall->isVisible = false;
    pISOBall->friendlyName = "DebugSphere"; // We can find it later.

    ::g_pVecObjects.push_back(pISOBall);


     // Add to the list of things to draw
    cMeshObject* pTerrain = new cMeshObject();
    pTerrain->meshName = "assets/models/00_terrain_xyz_n_rgba_uv.ply";
    pTerrain->scale = 1.0f;
    pTerrain->position.y = -10.0f;
    pTerrain->colourRGBA = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
    ::g_pVecObjects.push_back(pTerrain);

      // Add to the list of things to draw
    cMeshObject* pATAT = new cMeshObject();
    pATAT->meshName = "assets/models/00_atat_xyz_n_rgba_uv.ply";
    pATAT->scale = 1.0f;
    pATAT->position.y = 0.0f;
//    pATAT->isWireframe = true;
    pATAT->colourRGBA = glm::vec4(0.85f, 0.85f, 0.85f, 1.0f);
    ::g_pVecObjects.push_back(pATAT);

    // Add to the list of things to draw
    cMeshObject* pSpeeder = new cMeshObject();
    pSpeeder->meshName = "assets/models/00_Star Wars Snowspeeder_xyz_n_rgba_uv_2.ply";
    pSpeeder->scale = 1.0f;
    pSpeeder->colourRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pSpeeder->position = glm::vec3(0.0f, 10.0f, 15.0f);
    pSpeeder->orientation.y = glm::radians(180.0f);
    //pSpeeder->isWireframe = true;
    //pSpeeder->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
   ::g_pVecObjects.push_back(pSpeeder);


    return;
}
