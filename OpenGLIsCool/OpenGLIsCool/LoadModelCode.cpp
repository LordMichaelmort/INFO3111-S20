// Here's where all the models are loaded into
// the VAO and the "scene" 

#include "globalThings.h"

#include "cVAOManager.h"
#include "cMeshObject.h"
#include "cBasicTextureManager/cBasicTextureManager.h"
#include <iostream>


extern cBasicTextureManager* g_pTheTextureManager;

void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager, 
                       std::string modelsToLoad );


void LoadAllThemodels( unsigned int program, 
                       cVAOManager* pTheVAOManager )
{
    ::g_pTheTextureManager->SetBasePath("assets/textures");

    if (::g_pTheTextureManager->Create2DTextureFromBMPFile("cobblestone.bmp", true))
    {
        std::cout << "Texture loaded OK" << std::endl;
    }
    else
    {
        std::cout << "Error: Didn't load texture" << ::g_pTheTextureManager->getLastError() << std::endl;
    }
    // Force cout to flush to screen.
    std::cout.flush();

    // This is a fairly big texture, so comment it out if your Debug build is taking a long
    //   time to load... 
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("fauci.bmp", true, false );
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("DarkGrey.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("IslandHeightMap.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("02-australia-gray.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("StoneTexture.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("SandTexture.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("WaterSurfaceTexture.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("pool-water-caustic.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("SpidermanUV_square.bmp", true);

    ::g_pTheTextureManager->Create2DTextureFromBMPFile("tree_texture.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("tree_texture_mask.bmp", true);

    // For CP#11
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("PerlinNoise.bmp", true);

    // This is an example of a "mask" or "discard" texture
    // Using the texture to "discard" parts of the model
    // (like holes, chain link fence, etc.)
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("HeyThereTexture_Mask_or_discard.bmp", true);
    ::g_pTheTextureManager->Create2DTextureFromBMPFile("PolkaDotMask.bmp", true);

    std::string ErrorString = "";
    if (!::g_pTheTextureManager->CreateCubeTextureFromBMPFiles("sunnyday",
                                                               "cubemaps/TropicalSunnyDayRight2048.bmp",   /* +ve X */
                                                               "cubemaps/TropicalSunnyDayLeft2048.bmp",   /* -ve X */
                                                               "cubemaps/TropicalSunnyDayUp2048.bmp",   /* +ve Y */
                                                               "cubemaps/TropicalSunnyDayDown2048.bmp",   /* -ve Y */
                                                               "cubemaps/TropicalSunnyDayBack2048.bmp",   /* +ve Z */
                                                               "cubemaps/TropicalSunnyDayFront2048.bmp",   /* -ve Z */
                                                               true, /*is Seamless*/
                                                               ErrorString, 
                                                               false ))
    {
        std::cout << "Error: Didn't load cubemap because: " << ErrorString << std::endl;
    }
    else
    {
        std::cout << "Loaded cube map OK." << std::endl;
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
        sModelDrawInfo mdiFLATterrain;
        pTheVAOManager->LoadModelIntoVAO("assets/models/00_FLAT_terrain_xyz_n_rgba_uv.ply",
                                         mdiFLATterrain, program);
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
    {
        sModelDrawInfo mdiSpiderman;
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_head.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_body.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Hips.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Left_arm.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Left_hand.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Left_leg.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Right_arm.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Right_hand.ply", mdiSpiderman, program);
        pTheVAOManager->LoadModelIntoVAO("assets/models/Spiderman (2017 final exam)/legospiderman_Right_leg.ply", mdiSpiderman, program);
 
    
        // Add to the list of things to draw
        cMeshObject* pSpiderHead = new cMeshObject();
        pSpiderHead->meshName = "assets/models/Spiderman (2017 final exam)/legospiderman_head.ply";
        pSpiderHead->textureNames[0] = "SpidermanUV_square.bmp";
        pSpiderHead->texRatios[0] = 1.0f;
        pSpiderHead->scale = 10.0f;
        pSpiderHead->position.y = 10.0f;
        pSpiderHead->orientation.x = glm::radians(-90.0f);
        pSpiderHead->friendlyName = "Spidey";
        ::g_pVecObjects.push_back(pSpiderHead);

        cMeshObject* pSpiderBody = new cMeshObject();
        pSpiderBody->meshName = "assets/models/Spiderman (2017 final exam)/legospiderman_body.ply";
        pSpiderBody->textureNames[0] = "SpidermanUV_square.bmp";
        pSpiderBody->texRatios[0] = 1.0f;
        pSpiderBody->scale = 10.0f;
        pSpiderBody->position.y = 10.0f;
        pSpiderBody->orientation.x = glm::radians(-90.0f);
        pSpiderBody->friendlyName = "Spidey";
        pSpiderBody->diffuseRGBA.a = 0.99f;
        ::g_pVecObjects.push_back(pSpiderBody);

        cMeshObject* pSpiderLeftArm = new cMeshObject();
        pSpiderLeftArm->meshName = "assets/models/Spiderman (2017 final exam)/legospiderman_Left_arm.ply";
        pSpiderLeftArm->textureNames[0] = "SpidermanUV_square.bmp";
        pSpiderLeftArm->texRatios[0] = 1.0f;
        pSpiderLeftArm->scale = 10.0f;
        pSpiderLeftArm->position.y = 10.0f;
        pSpiderLeftArm->orientation.x = glm::radians(-90.0f);
        pSpiderLeftArm->friendlyName = "Spidey";
        ::g_pVecObjects.push_back(pSpiderLeftArm);
    }    

    // Skybox (cubemap) object
    sModelDrawInfo mdiISOSphereIN;
    pTheVAOManager->LoadModelIntoVAO("assets/models/ISO_Sphere_Smooth_inverted_normals_xyz_n_rgba_uv.ply", mdiISOSphereIN, program);
    
    cMeshObject* pSkyBox = new cMeshObject();
    pSkyBox->meshName = "assets/models/ISO_Sphere_Smooth_inverted_normals_xyz_n_rgba_uv.ply";
    // Because this is using a cubeMap for the skybox, we aren't 
    // actually using the regular 2D texture stuff.
//    pSkyBox->textureNames[0] = "SpidermanUV_square.bmp";
//    pSkyBox->texRatios[0] = 1.0f;
    pSkyBox->scale = 1000.0f;
    pSkyBox->friendlyName = "SkyBox";
    ::g_pVecObjects.push_back(pSkyBox);



    sModelDrawInfo mdiSmallQuad;
    pTheVAOManager->LoadModelIntoVAO("assets/models/2_tri_quad_XY_axis_1x1.ply", mdiSmallQuad, program);

    cMeshObject* pQuadTree = new cMeshObject();
    pQuadTree->meshName = "assets/models/2_tri_quad_XY_axis_1x1.ply";
    pQuadTree->friendlyName = "QuadForTree";
    pQuadTree->textureNames[0] = "tree_texture.bmp";       //tree_texture
    pQuadTree->texRatios[0] = 1.0f;
    pQuadTree->scale = 60.0f;
    pQuadTree->position.y = 50.0f;
    ::g_pVecObjects.push_back(pQuadTree);



     // Add to the list of things to draw
    cMeshObject* pBunny = new cMeshObject();
    pBunny->meshName = "assets/models/bun_zipper_res2_xyz_n_rgba_uv.ply";
    pBunny->friendlyName = "Bugs";
    
    pBunny->position.y = 10.0f;

    pBunny->textureNames[0] = "cobblestone.bmp";
    pBunny->texRatios[0] = 0.0f;

    pBunny->textureNames[1] = "fauci.bmp";
    pBunny->texRatios[1] = 1.0f;

    ::g_pVecObjects.push_back(pBunny);


    // Add to the list of things to draw
    cMeshObject* pSeaFloor = new cMeshObject();
    pSeaFloor->meshName = "assets/models/00_terrain_xyz_n_rgba_uv.ply";
//    pTerrain->meshName = "assets/models/00_FLAT_terrain_xyz_n_rgba_uv.ply";
    pSeaFloor->friendlyName = "seaFloor";
    pSeaFloor->scale = 2.0f;
    pSeaFloor->position.y = -10.0f;
    pSeaFloor->specularRGB_Power.r = 1.0f;
    pSeaFloor->specularRGB_Power.g = 1.0f;
    pSeaFloor->specularRGB_Power.b = 1.0f;
//    pSeaFloor->specularRGB_Power.w = 1000.0f;        // REALLY shinny
//    pSeaFloor->specularRGB_Power.w = 10.0f;          // Sort of (like silk)
    pSeaFloor->specularRGB_Power.w = 1.0f;           // No specular ("flat", like dry clay)
 //   pSeaFloor->textureNames[0] = "02-australia-gray.bmp";
 //   pSeaFloor->textureNames[0] = "SandTexture.bmp";
    pSeaFloor->textureNames[0] = "fauci.bmp";
    pSeaFloor->textureNames[1] = "pool-water-caustic.bmp";
    pSeaFloor->textureNames[2] = "";
    pSeaFloor->textureNames[3] = "";

    pSeaFloor->texRatios[0] = 1.0f;
    pSeaFloor->texRatios[1] = 0.0f;
    pSeaFloor->texRatios[2] = 0.0f;
    pSeaFloor->texRatios[3] = 0.0f;

    ::g_pVecObjects.push_back(pSeaFloor);


    // Add to the list of things to draw
    cMeshObject* pWaterSurface = new cMeshObject();
    pWaterSurface->meshName = "assets/models/00_FLAT_terrain_xyz_n_rgba_uv.ply";
    pWaterSurface->friendlyName = "terrain";
    pWaterSurface->scale = 2.0f;
    pWaterSurface->position.y = 35.0f;
    pWaterSurface->specularRGB_Power.r = 1.0f;
    pWaterSurface->specularRGB_Power.g = 1.0f;
    pWaterSurface->specularRGB_Power.b = 0.0f;
    pWaterSurface->specularRGB_Power.w = 1000.0f;        // REALLY shinny
    pWaterSurface->textureNames[0] = "WaterSurfaceTexture.bmp";
    pWaterSurface->textureNames[1] = "fauci.bmp";
    pWaterSurface->textureNames[2] = "";
    pWaterSurface->textureNames[2] = "";

    pWaterSurface->texRatios[0] = 0.0f;
    pWaterSurface->texRatios[1] = 1.0f;

 //   pWaterSurface->diffuseRGBA.a = 0.65f;    // Semi-transparent
    pWaterSurface->diffuseRGBA.a = 1.0f;  

    // This "water" object will now have a "discard" or "masking" texture
    pWaterSurface->discardTexture = "HeyThereTexture_Mask_or_discard.bmp";
    pWaterSurface->discardTexture = "PolkaDotMask.bmp";

    ::g_pVecObjects.push_back(pWaterSurface);




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

   pATAT->textureNames[0] = "DarkGrey.bmp";
   pATAT->texRatios[0] = 1.0f;

   //    pATAT->isWireframe = true;
   pATAT->diffuseRGBA = glm::vec4(0.85f, 0.85f, 0.85f, 1.0f);
   // Specular HIGHLIGHT colour 
   pATAT->specularRGB_Power.r = 1.0f;
   pATAT->specularRGB_Power.g = 1.0f;
   pATAT->specularRGB_Power.b = 1.0f;
   // Specular highlight POWER
   pATAT->specularRGB_Power.w = 1000.0f;

   pATAT->friendlyName = "ATAT";

   ::g_pVecObjects.push_back(pATAT);



   //// Lots of bunnies
   //float boxLimit = 400.0f;
   //float boxStep = 100.0f;
   //for (float x = -boxLimit; x <= boxLimit; x += boxStep)
   //{
   //    for (float y = -boxLimit; y <= boxLimit; y += boxStep)
   //    {
   //        for (float z = 0.0f; z <= (boxLimit*2.0f); z += boxStep)
   //        {
   //            // Add to the list of things to draw
   //            cMeshObject* pBunny = new cMeshObject();
   //            pBunny->meshName = "assets/models/bun_zipper_res2_xyz_n_rgba_uv.ply";
   //            pBunny->scale = 3.0f;

   //            pBunny->textureNames[0] = "cobblestone.bmp";
   //            pBunny->texRatios[0] = 1.0f;

   //            pBunny->textureNames[1] = "fauci.bmp";
   //            pBunny->texRatios[1] = 0.0f;

   //            pBunny->position = glm::vec3(x,y,z);
   //            pBunny->diffuseRGBA.a = 0.35f;

   //            ::g_pVecObjects.push_back(pBunny);
   //        }
   //     }
   //}

    return;
}
