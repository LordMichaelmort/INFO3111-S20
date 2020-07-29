// Here's where all the models are loaded into
// the VAO and the "scene" 

#include "globalThings.h"

#include "cVAOManager.h"
#include "cMeshObject.h"
#include <iostream>

//void LoadAllThemodels( unsigned int program, 
//                       cVAOManager* pTheVAOManager, 
//                       std::string modelsToLoad );



void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager )
{

    pTheVAOManager->setBaseLoadPath("assets/models/");

    std::string ErrorString;
    std::vector<sModelDrawInfo> vecDrawInfos;

    vecDrawInfos.push_back(sModelDrawInfo("FeeneyIslandSeed1295.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("ISO_Shphere_flat_3div_xyz_n_rgba_uv.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Bush_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Bush_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Fern_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Flowers_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Flowers_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Mangrove_Roots_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Mangrove_Tree_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Mangrove_Tree_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmBush_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_04.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_Tall_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_PalmTree_Tall_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Plants_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Plants_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Plants_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rocks_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rocks_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rocks_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Arch_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Huge_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Huge_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Huge_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Huge_04.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_010.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_011.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_04.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_05.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_06.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_07.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_08.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Large_09.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Rock_Skull_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Seaweed_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_SmallRock_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_SmallRock_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Base_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Base_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Canopy_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Canopy_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Canopy_03.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Canopy_04.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Dead_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Large_01.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("SM_Env_Tree_Large_02.ply"));
    vecDrawInfos.push_back(sModelDrawInfo("three_axis_cursor_xyz_n_rgba_uv.ply"));


    if (!pTheVAOManager->LoadModelsInfoVAO( vecDrawInfos, program, ErrorString ))
    {
        std::cout << "There were errors: " << std::endl;
        std::cout << ErrorString << std::endl;
    }
    else
    {
        std::cout << "All models loaded OK" << std::endl;
    }

    //{
    //    sModelDrawInfo mdiIsosphere;
    //    pTheVAOManager->LoadModelIntoVAO("ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply",
    //                                      mdiIsosphere, program);
    //}
 
     // Add to the list of things to draw
    cMeshObject* pISOBall = new cMeshObject();
    pISOBall->meshName = "ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply";
    pISOBall->colourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    pISOBall->position.z = 0.0f;
    pISOBall->isWireframe = true;
    // If this is false, just don't draw it.
    pISOBall->isVisible = false;
    pISOBall->friendlyName = "DebugSphere"; // We can find it later.
    ::g_pVecObjects.push_back(pISOBall);

    cMeshObject* p3AxisCursor = new cMeshObject();
    p3AxisCursor->meshName = "three_axis_cursor_xyz_n_rgba_uv.ply";
    p3AxisCursor->scale = 1.0f;
    p3AxisCursor->colourRGBA = glm::vec4(0.47f, 0.19f, 0.33f, 1.0f); // Hot pink
    p3AxisCursor->friendlyName = "3 Axis Cursor";
    ::g_pVecObjects.push_back(p3AxisCursor);

    cMeshObject* pIsland = new cMeshObject();
    pIsland->meshName = "FeeneyIslandSeed1295.ply";
    pIsland->scale = 1.0f;
    pIsland->bUseVertexColours = true;      // Use colours from the file
    ::g_pVecObjects.push_back(pIsland);

    cMeshObject* pSkull = new cMeshObject();
    pSkull->meshName = "SM_Env_Rock_Skull_01.ply";
    pSkull->scale = 1.0f;
    pSkull->bUseVertexColours = false;      // Use colours from the file
    pSkull->colourRGBA = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // "light stone grey"
    pSkull->position.y = 50.0f;
    //pSkull->colourRGBA = glm::vec4(0.47f, 0.19f, 0.33f, 1.0f); // Hot pink
    //pSkull->isWireframe = true;
    ::g_pVecObjects.push_back(pSkull);

    cMeshObject* pTreeCanopy = new cMeshObject();
    pTreeCanopy->meshName = "SM_Env_Tree_Canopy_01.ply";
    pTreeCanopy->scale = 1.0f;
    pTreeCanopy->bUseVertexColours = false;      // Use colours from colourRGB
    pTreeCanopy->colourRGBA = glm::vec4(0.58f, 0.95f, 0.11f, 1.0f); // "dark green"
    pTreeCanopy->position.y = 5.0f;
    ::g_pVecObjects.push_back(pTreeCanopy);

    cMeshObject* pTreeTrunk = new cMeshObject();
    pTreeTrunk->meshName = "SM_Env_Tree_Base_01.ply";
    pTreeTrunk->scale = 1.0f;
    pTreeTrunk->bUseVertexColours = false;      // Use colours from colourRGB
    pTreeTrunk->colourRGBA = glm::vec4(0.4539f, 0.3208f, 0.2253f, 1.0f); // "dark brown"
    ::g_pVecObjects.push_back(pTreeTrunk);

    return;
}
