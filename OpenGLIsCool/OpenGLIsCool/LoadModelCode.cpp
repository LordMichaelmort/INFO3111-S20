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
    {// Load the bunny, too
        sModelDrawInfo mdiRabbit;
        pTheVAOManager->LoadModelIntoVAO("assets/models/bun_zipper_xyz_n_rgba_uv.ply",
                                             mdiRabbit, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mdiSpaceShuttle;
        pTheVAOManager->LoadModelIntoVAO("assets/models/SpaceShuttleOrbiter_xyz_n_rgba_uv.ply",
                                             mdiSpaceShuttle, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mdiKlingon;
        pTheVAOManager->LoadModelIntoVAO("assets/models/KlingonCruiser_xyz_n_rgba_uv.ply",
                                             mdiKlingon, program);
    }
    {// Load the space shuttle, too
        sModelDrawInfo mdiTerrain;
        pTheVAOManager->LoadModelIntoVAO("assets/models/Mountain_Terrain_xyz_n_rgba_uv.ply",
                                             mdiTerrain, program);
    }
    // ENDOF: Loading the models

     // Add to the list of things to draw
    cMeshObject* pShuttle01 = new cMeshObject();
    pShuttle01->meshName = "assets/models/SpaceShuttleOrbiter_xyz_n_rgba_uv.ply";
    pShuttle01->position.x = -10.0f;
    pShuttle01->scale = 1.0f / 100.0f;    // 100th of it's normal size 0.001
    pShuttle01->colourRGBA = glm::vec4(207.0f / 255.0f, 181.0f / 255.0f, 59.0f / 255.0f, 1.0f);
    ::g_pVecObjects.push_back(pShuttle01);

    cMeshObject* pShuttle02 = new cMeshObject();
    pShuttle02->meshName = "assets/models/SpaceShuttleOrbiter_xyz_n_rgba_uv.ply";
    pShuttle02->position.x = +10.0f;
    pShuttle02->scale = 1.0f / 100.0f;    // 100th of it's normal size
    pShuttle02->orientation.z = glm::radians(135.0f);
    pShuttle02->colourRGBA = glm::vec4(189.0f / 255.0f, 183.0f / 255.0f, 107.0f / 255.0f, 1.0f);
    ::g_pVecObjects.push_back(pShuttle02);

    cMeshObject* pBunny = new cMeshObject();
    pBunny->meshName = "assets/models/bun_zipper_xyz_n_rgba_uv.ply";
    pBunny->position.y = +10.0f;
    pBunny->scale = 25.0f;
    pBunny->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    ::g_pVecObjects.push_back(pBunny);

    cMeshObject* pArena = new cMeshObject();
    pArena->meshName = "assets/models/free_arena_ASCII_xyz_n_rgba_uv.ply";
    pArena->position.y = -20.0f;
    pArena->scale = 1.0f;
    pArena->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    ::g_pVecObjects.push_back(pArena);

    cMeshObject* pKling1 = new cMeshObject();
    pKling1->meshName = "assets/models/KlingonCruiser_xyz_n_rgba_uv.ply";
    pKling1->position.y = 10.0f;
    pKling1->position.x = -10.0f;
    pKling1->scale = 1.0f;
    pKling1->colourRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    ::g_pVecObjects.push_back(pKling1);

    cMeshObject* pKling2 = new cMeshObject();
    pKling2->meshName = "assets/models/KlingonCruiser_xyz_n_rgba_uv.ply";
    pKling2->position.y = 10.0f;
    pKling2->position.x = 20.0f;
    pKling2->scale = 2.0f;
    pKling2->colourRGBA = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    ::g_pVecObjects.push_back(pKling2);

    cMeshObject* pTerrain = new cMeshObject();
    pTerrain->meshName = "assets/models/Mountain_Terrain_xyz_n_rgba_uv.ply";
    pTerrain->position.y = -150.0f;
    pTerrain->orientation.y = glm::radians(180.0f);
    pTerrain->scale = 5.0f;
    //    pTerrain->isWireframe = true;
    pTerrain->colourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pVecObjects.push_back(pTerrain);

    return;
}
