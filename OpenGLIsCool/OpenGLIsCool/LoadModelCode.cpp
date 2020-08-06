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
        sModelDrawInfo mdiLightPole;
        pTheVAOManager->LoadModelIntoVAO("assets/models/LightPole_xyz_n_rgba_uv.ply",
                                         mdiLightPole, program);
    }    
    {
        sModelDrawInfo mdiBunny;
        pTheVAOManager->LoadModelIntoVAO("assets/models/bun_zipper_res2_xyz_n_rgba_uv.ply",
                                         mdiBunny, program);
    }    

     // Add to the list of things to draw
    cMeshObject* pBunny = new cMeshObject();
    pBunny->meshName = "assets/models/bun_zipper_res2_xyz_n_rgba_uv.ply";
    pBunny->position.y = 10.0f;

    pBunny->textureNames[0] = "cobblestone.bmp";
    pBunny->texRatios[0] = 1.0f;

    pBunny->textureNames[1] = "fauci.bmp";
    pBunny->texRatios[1] = 0.0f;

    ::g_pVecObjects.push_back(pBunny);


    // Add to the list of things to draw
    cMeshObject* pTerrain = new cMeshObject();
    pTerrain->meshName = "assets/models/00_terrain_xyz_n_rgba_uv.ply";
    pTerrain->scale = 1.0f;
    pTerrain->position.y = -10.0f;
    pTerrain->diffuseRGBA = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
    // Make the ground shiny 

    // Specular HIGHLIGHT colour 
    pTerrain->specularRGB_Power.r = 1.0f;
    pTerrain->specularRGB_Power.g = 0.0f;
    pTerrain->specularRGB_Power.b = 0.0f;
    //    229, 234, 145
        // Specular highlight POWER
    pTerrain->specularRGB_Power.w = 1000.0f;

    pTerrain->textureNames[0] = "fauci.bmp";
    pTerrain->texRatios[0] = 1.0f;

    ::g_pVecObjects.push_back(pTerrain);

     // Add to the list of things to draw
    cMeshObject* pISOBall = new cMeshObject();
    pISOBall->meshName = "assets/models/ISO_Shphere_flat_4div_xyz_n_rgba_uv.ply";
    pISOBall->diffuseRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    pISOBall->position.z = 0.0f;
    pISOBall->isWireframe = true;
    // If this is false, just don't draw it.
    pISOBall->isVisible = false;
    pISOBall->friendlyName = "DebugSphere"; // We can find it later.
    ::g_pVecObjects.push_back(pISOBall);

    cMeshObject* pTorpedo = new cMeshObject();
    pTorpedo->meshName = "assets/models/0_review_TearDropBullet_inverted_normals_xyz_n_rgba_uv.ply";
    pTorpedo->diffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    pTorpedo->position = glm::vec3(0.25f, 3.5f, 4.5f);
    pTorpedo->scale = 1.0f;
    pTorpedo->friendlyName = "Torpedo";
    pTorpedo->isWireframe = false;
    pTorpedo->isVisible = false;
    ::g_pVecObjects.push_back(pTorpedo);




    // Add to the list of things to draw
    cMeshObject* pSpeeder = new cMeshObject();
    pSpeeder->meshName = "assets/models/00_Star Wars Snowspeeder_xyz_n_rgba_uv_2.ply";
    pSpeeder->scale = 1.0f;
    pSpeeder->diffuseRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pSpeeder->position = glm::vec3(0.0f, 10.0f, 17.0f);
    pSpeeder->orientation.y = glm::radians(180.0f);
    //pSpeeder->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pSpeeder->isWireframe = true;
   ::g_pVecObjects.push_back(pSpeeder);

    // Add to the list of things to draw
    cMeshObject* pYWing = new cMeshObject();
    pYWing->meshName = "assets/models/0_review_y-wing_xyz_n_rgba_uv_2.ply";
    pYWing->scale = 1.0f;
    pYWing->diffuseRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pYWing->position = glm::vec3(10.0f, 10.0f, 0.0f);
    pYWing->orientation.x = glm::radians(-90.0f);
    //pYWing->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pYWing->isWireframe = true;
   ::g_pVecObjects.push_back(pYWing);

    // Add to the list of things to draw
    cMeshObject* pXWing = new cMeshObject();
    pXWing->meshName = "assets/models/0_review_X-Wing_Attack_xyz_n_rgba_uv.ply";
    pXWing->scale = 1.0f;
    pXWing->diffuseRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 0.5f);
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
    pInvertedNormalSphere->diffuseRGBA = glm::vec4(0.91f, 0.80f, 0.85f, 1.0f);
    pInvertedNormalSphere->position = glm::vec3(10.0f, 10.0f, -20.0f);
    pInvertedNormalSphere->orientation.x = glm::radians(-90.0f);
    //pInvertedNormalSphere->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //pInvertedNormalSphere->isWireframe = true;
   ::g_pVecObjects.push_back(pInvertedNormalSphere);

   // Add to the list of things to draw
   cMeshObject* pLightPole = new cMeshObject();
   pLightPole->meshName = "assets/models/LightPole_xyz_n_rgba_uv.ply";
   pLightPole->scale = 1.0f;
   pLightPole->position.x = -5.0f;
   pLightPole->diffuseRGBA = glm::vec4(0.85f, 0.85f, 0.85f, 1.0f);
   // Specular HIGHLIGHT colour 
   pLightPole->specularRGB_Power.r = 1.0f;
   pLightPole->specularRGB_Power.g = 1.0f;
   pLightPole->specularRGB_Power.b = 1.0f;
   // Specular highlight POWER
   pLightPole->specularRGB_Power.w = 1000.0f;
   ::g_pVecObjects.push_back(pLightPole);


   // Add to the list of things to draw
   cMeshObject* pATAT = new cMeshObject();
   pATAT->meshName = "assets/models/00_atat_xyz_n_rgba_uv.ply";
   pATAT->scale = 1.0f;
   pATAT->position.y = 0.0f;
   pATAT->position.x = 50.0f;
   //    pATAT->isWireframe = true;
   pATAT->diffuseRGBA = glm::vec4(0.85f, 0.85f, 0.85f, 0.5f);
   // Specular HIGHLIGHT colour 
   pATAT->specularRGB_Power.r = 1.0f;
   pATAT->specularRGB_Power.g = 1.0f;
   pATAT->specularRGB_Power.b = 1.0f;
   // Specular highlight POWER
   pATAT->specularRGB_Power.w = 1000.0f;
   ::g_pVecObjects.push_back(pATAT);



   // Lots of bunnies
   float boxLimit = 400.0f;
   float boxStep = 100.0f;
   for (float x = -boxLimit; x <= boxLimit; x += boxStep)
   {
       for (float y = -boxLimit; y <= boxLimit; y += boxStep)
       {
           for (float z = 0.0f; z <= (boxLimit*2.0f); z += boxStep)
           {
               // Add to the list of things to draw
               cMeshObject* pBunny = new cMeshObject();
               pBunny->meshName = "assets/models/bun_zipper_res2_xyz_n_rgba_uv.ply";
               pBunny->scale = 3.0f;

               pBunny->textureNames[0] = "cobblestone.bmp";
               pBunny->texRatios[0] = 1.0f;

               pBunny->textureNames[1] = "fauci.bmp";
               pBunny->texRatios[1] = 0.0f;

               pBunny->position = glm::vec3(x,y,z);
               pBunny->diffuseRGBA.a = 0.35f;

               ::g_pVecObjects.push_back(pBunny);
           }
        }
   }

    return;
}
