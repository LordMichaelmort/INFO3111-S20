// Here's where all the models are loaded into
// the VAO and the "scene" 

#include "globalThings.h"

#include "cVAOManager.h"
#include "cMeshObject.h"
#include <iostream>

void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager, 
                       std::string modelsToLoad );


void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager )
{
    {
        sModelDrawInfo mdi3AxisCursor;
        pTheVAOManager->LoadModelIntoVAO("assets/models/three_axis_cursor_xyz_n_rgba_uv.ply",
                                         mdi3AxisCursor, program);
    }
    {
        sModelDrawInfo mdiIsosphere;
        pTheVAOManager->LoadModelIntoVAO("assets/models/ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply",
                                          mdiIsosphere, program);
    }
    {
        sModelDrawInfo mdiATAT;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_atat_xyz_n_rgba_uv.ply",
                                         mdiATAT, program);
    }
    {
        sModelDrawInfo mdiSpeeder;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_Star Wars Snowspeeder_xyz_n_rgba_uv_2.ply",
                                         mdiSpeeder, program);
    }
    {
        sModelDrawInfo mdiYWing;
        pTheVAOManager->LoadModelIntoVAO("assets/models/0_review_y-wing_xyz_n_rgba_uv_2.ply",
                                         mdiYWing, program);
    }
    {
        sModelDrawInfo mdiXWing;
        pTheVAOManager->LoadModelIntoVAO("assets/models/0_review_X-Wing_Attack_xyz_n_rgba_uv.ply",
                                         mdiXWing, program);
    }
    {
        sModelDrawInfo mdiInvertedNormalSphere;
        pTheVAOManager->LoadModelIntoVAO("assets/models/0_review_Isoshphere_xyz_n_rgba_uv_InvertedNormals.ply",
                                         mdiInvertedNormalSphere, program);
    }
    {
        sModelDrawInfo mditerrain;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_terrain_xyz_n_rgba_uv.ply",
                                         mditerrain, program);
    }    
    {
        sModelDrawInfo mdiTorpedo;
        pTheVAOManager->LoadModelIntoVAO("assets/models/0_review_TearDropBullet_inverted_normals_xyz_n_rgba_uv.ply",
                                         mdiTorpedo, program);
    }    
    {
        sModelDrawInfo mdiIsland;
        if (pTheVAOManager->LoadModelIntoVAO("assets/models/SM_Env_Rock_Skull_01.ply",
                                             mdiIsland, program))
        {
            std::cout << "Loaded the island. Hazzah!" << std::endl;
        }
    }    
     // Add to the list of things to draw
    cMeshObject* pIsland = new cMeshObject();
    pIsland->meshName = "assets/models/SM_Env_Rock_Skull_01.ply";
    pIsland->colourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    pIsland->position.x = 10.0f;
 //   pIsland->isWireframe = true;
    ::g_pVecObjects.push_back(pIsland);

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

    cMeshObject* pTorpedo = new cMeshObject();
    pTorpedo->meshName = "assets/models/0_review_TearDropBullet_inverted_normals_xyz_n_rgba_uv.ply";
    pTorpedo->colourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    pTorpedo->position = glm::vec3(0.25f, 3.5f, 4.5f);
    pTorpedo->scale = 1.0f;
    pTorpedo->friendlyName = "Torpedo";
    pTorpedo->isWireframe = false;
    pTorpedo->isVisible = false;
    ::g_pVecObjects.push_back(pTorpedo);

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
    pSpeeder->position = glm::vec3(0.0f, 10.0f, 17.0f);
    pSpeeder->orientation.y = glm::radians(180.0f);
    //pSpeeder->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pSpeeder->isWireframe = true;
   ::g_pVecObjects.push_back(pSpeeder);

    // Add to the list of things to draw
    cMeshObject* pYWing = new cMeshObject();
    pYWing->meshName = "assets/models/0_review_y-wing_xyz_n_rgba_uv_2.ply";
    pYWing->scale = 1.0f;
    pYWing->colourRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pYWing->position = glm::vec3(10.0f, 10.0f, 0.0f);
    pYWing->orientation.x = glm::radians(-90.0f);
    //pYWing->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pYWing->isWireframe = true;
   ::g_pVecObjects.push_back(pYWing);

    // Add to the list of things to draw
    cMeshObject* pXWing = new cMeshObject();
    pXWing->meshName = "assets/models/0_review_X-Wing_Attack_xyz_n_rgba_uv.ply";
    pXWing->scale = 1.0f;
    pXWing->colourRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pXWing->position = glm::vec3(-3.5f, 6.0f, 20.0f);
    pXWing->orientation.x = glm::radians(90.0f);
    pXWing->orientation.z = glm::radians(180.0f);
    //pYWing->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pYWing->isWireframe = true;
   ::g_pVecObjects.push_back(pXWing);

    // Add to the list of things to draw
    cMeshObject* pInvertedNormalSphere = new cMeshObject();
    pInvertedNormalSphere->meshName = "assets/models/0_review_Isoshphere_xyz_n_rgba_uv_InvertedNormals.ply";
    pInvertedNormalSphere->scale = 1.0f;
    pInvertedNormalSphere->colourRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pInvertedNormalSphere->position = glm::vec3(10.0f, 10.0f, -20.0f);
    pInvertedNormalSphere->orientation.x = glm::radians(-90.0f);
    //pInvertedNormalSphere->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pInvertedNormalSphere->isWireframe = true;
   ::g_pVecObjects.push_back(pInvertedNormalSphere);

    cMeshObject* p3AxisCursor = new cMeshObject();
    p3AxisCursor->meshName = "assets/models/three_axis_cursor_xyz_n_rgba_uv.ply";
    p3AxisCursor->scale = 1.0f;
    p3AxisCursor->colourRGBA = glm::vec4(0.47f, 0.19f, 0.33f, 1.0f); // Hot pink
    p3AxisCursor->friendlyName = "3 Axis Cursor";
   ::g_pVecObjects.push_back(p3AxisCursor);

    return;
}
