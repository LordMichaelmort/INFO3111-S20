//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "globalOpenGLStuff.h"

#include "globalThings.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "cShaderManager.h"
#include "cVAOManager.h"            // NEW!
#include <string>

#include "cMeshObject.h"
#include <vector>
#include <sstream>          // Stupid name because it's stringstring, not sstream
#include <algorithm>

#include "LightManager/cLightManager.h"

bool StartErUp(std::vector<std::string> vecCommands);
bool ShutErDown(void);


// Function signature for DrawObject()
void DrawObject(cMeshObject* pCurMesh,
                GLuint program,                // Shader program
                glm::mat4& matView,            // View matrix
                glm::mat4& matProjection);      // Projection matrix


// Camera stuff
//glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, +100.0f);
//glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec3 g_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

extern cJoystickManager* g_pJoysticks;
extern cFlyCamera* g_pFlyCamera;

// The objects we are drawing go in here! Hazzah!
std::vector< cMeshObject* > g_pVecObjects;
int g_selectedObjectID = 0;

cLightManager* g_pLightManager = 0;    // or NULL or nullptr
int g_selectedLightID = 0;

bool g_ShowLightDebugSpheres = true;

cBasicTextureManager* g_pTheTextureManager = NULL;  // Or 0 or nullprt


cJoystickManager* g_pJoysticks = NULL;  // Or 0 or nullprt;
cFlyCamera* g_pFlyCamera = NULL;  // Or 0 or nullprt;

// Yes, it's global. Just be calm, for now.
cShaderManager* g_pShaderManager = 0;       // NULL

cVAOManager* g_pTheVAOManager = 0;          // NULL or nullptr

bool g_isWireFrame = false;

// For the AT-AT shooting thing
glm::vec3 g_TorpedoStartLocation = glm::vec3(0.25f, 3.5f, 4.5f);
bool g_bTorpedoIsMoving = false;


// Returns pointer to zero (NULL) if NOT found
cMeshObject* findObjectByName(std::string friendlyNameToFind)
{
    // Search by name 'till we find the object.
    for (std::vector<cMeshObject*>::iterator it_pCO = ::g_pVecObjects.begin();
         it_pCO != ::g_pVecObjects.end(); it_pCO++)
    {
        cMeshObject* pCO = *it_pCO;

        // Is this the one? 
        if ( pCO->friendlyName == friendlyNameToFind )
        {   
            // Yes! So return it
            return pCO;
        }
    }
    // DIDN'T find it, so return 0 or NULL
    return 0;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float CAMERASPEED = 1.0f;
    // WSAD - AD are "right and left"
    //      - SW are "forward and back"
    //      - QE are "up and down"

    // if there are NO "modifier" keys (mods), then mods == 0 
   

    // Shoot the torpedo (from the AT-AT)
    if (::g_bTorpedoIsMoving == false)
    {
        if ( key == GLFW_KEY_ENTER )
        {
            // Reset the torpedo to the end of the AT-AT gun
            cMeshObject* pTorpedo = findObjectByName("Torpedo");
            pTorpedo->position = ::g_TorpedoStartLocation;
            ::g_bTorpedoIsMoving = true;
        }
    }//if (::g_bTorpedoIsMoving == false)


    // ONLY shift is down (control light)
    if ( mods == GLFW_MOD_SHIFT )
    {  
        if (key == GLFW_KEY_1) { ::g_pLightManager->vecLights[g_selectedLightID].atten.y *= 0.99f;}    // Linear
        if (key == GLFW_KEY_2) { ::g_pLightManager->vecLights[g_selectedLightID].atten.y *= 1.01f;}    // Linear
        if (key == GLFW_KEY_3) { ::g_pLightManager->vecLights[g_selectedLightID].atten.z *= 0.99f;}    // Quardatic
        if (key == GLFW_KEY_4) { ::g_pLightManager->vecLights[g_selectedLightID].atten.z *= 1.01f;}    // Quardatic

        if (key == GLFW_KEY_A) { ::g_pLightManager->vecLights[g_selectedLightID].position.x -= CAMERASPEED; }
        if (key == GLFW_KEY_D) { ::g_pLightManager->vecLights[g_selectedLightID].position.x += CAMERASPEED; }
        if (key == GLFW_KEY_W) { ::g_pLightManager->vecLights[g_selectedLightID].position.z += CAMERASPEED; }
        if (key == GLFW_KEY_S) { ::g_pLightManager->vecLights[g_selectedLightID].position.z -= CAMERASPEED; }
        if (key == GLFW_KEY_Q) { ::g_pLightManager->vecLights[g_selectedLightID].position.y -= CAMERASPEED; }
        if (key == GLFW_KEY_E) { ::g_pLightManager->vecLights[g_selectedLightID].position.y += CAMERASPEED; }

        // Change the angle of the spotlight
        // "Inner" angle of spot
        if (key == GLFW_KEY_I ) { ::g_pLightManager->vecLights[g_selectedLightID].param1.y -= 0.1f; }
        if (key == GLFW_KEY_O ) { ::g_pLightManager->vecLights[g_selectedLightID].param1.y += 0.1f; }
        // "Outer" angle of spot
        if (key == GLFW_KEY_L ) { ::g_pLightManager->vecLights[g_selectedLightID].param1.z -= 0.1f; }
        if (key == GLFW_KEY_K ) { ::g_pLightManager->vecLights[g_selectedLightID].param1.z += 0.1f; }

        if ( key==GLFW_KEY_0) { ::g_ShowLightDebugSpheres = true; }
        if ( key==GLFW_KEY_9) { ::g_ShowLightDebugSpheres = false; }

    }//if ( mods == GLFW_MOD_SHIFT )
            

    //std::cout << ::g_pLightManager->vecLights[0].atten.y 
    //    << "  " 
    //    << ::g_pLightManager->vecLights[0].atten.z << std::endl;


    // if ( mods == 0 ) then no "modifiers" are pressed
    //if (mods == 0)
    //{
    //    //::g_cameraEye.x -= CAMERASPEED;
    //    if (key == GLFW_KEY_A) { ::g_cameraEye.x -= CAMERASPEED; }
    //    if (key == GLFW_KEY_D) { ::g_cameraEye.x += CAMERASPEED; }
    //    if (key == GLFW_KEY_W) { ::g_cameraEye.z += CAMERASPEED; }
    //    if (key == GLFW_KEY_S) { ::g_cameraEye.z -= CAMERASPEED; }
    //    if (key == GLFW_KEY_Q) { ::g_cameraEye.y -= CAMERASPEED; }
    //    if (key == GLFW_KEY_E) { ::g_cameraEye.y += CAMERASPEED; }
    //}//if (mods == 0)

    //if (key == GLFW_KEY_L)
    //{
    //    ::g_pVecObjects[::g_selectedObjectID]->orientation.z += glm::radians(CAMERASPEED);
    //}
    //if (key == GLFW_KEY_K)
    //{
    //    ::g_pVecObjects[::g_selectedObjectID]->orientation.z -= glm::radians(CAMERASPEED);
    //}
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        ::g_selectedLightID--;
        std::cout << ::g_selectedLightID << std::endl;
    }
    if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        ::g_selectedLightID++;
        std::cout << ::g_selectedLightID << std::endl;

    }

 
    // Switches from wireframe to solid (glPolygonMode)
    if (key == GLFW_KEY_9 && action == GLFW_PRESS ) {::g_isWireFrame = true; }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS ) {::g_isWireFrame = false; }


    //// Print out camera location:
    //std::cout << "cam: " 
    //    << ::g_cameraEye.x << ", "
    //    << ::g_cameraEye.y << ", "
    //    << ::g_cameraEye.z << std::endl;



    return;
}


// Predicate function
bool IsACloserToCamera(cMeshObject* pA, cMeshObject* pB)
{
    float distToCamera_A = glm::distance( pA->position, ::g_pFlyCamera->getEye() );
    float distToCamera_B = glm::distance( pB->position, ::g_pFlyCamera->getEye() );

    if (distToCamera_A < distToCamera_B)
    {
        return true;
    }
    return false;
}

// Functor for sorting the objects back to front
class cIsACloserToCamera
{
public:
    cIsACloserToCamera(glm::vec3 cameraEye) 
    {
        this->m_CameraEye = cameraEye;
        return;
    }

    // No one uses operator()
    bool operator() (cMeshObject* pA, cMeshObject* pB)
    {
        float distToCamera_A = glm::distance( pA->position, this->m_CameraEye);
        float distToCamera_B = glm::distance( pB->position, this->m_CameraEye);

        if (distToCamera_A < distToCamera_B)
        {
            return true;
        }
        return false;
    }
private:
    glm::vec3 m_CameraEye;
};


int main(void)
{

 //   LoadPlyFile("assets/models/bun_zipper_res4_xyz_colour.ply");

    std::cout << "About to start..." << std::endl;

    GLFWwindow* window;
//    GLuint vertex_buffer;
//    GLuint vertex_shader; 
//    GLuint fragment_shader;
    GLuint program;

    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        std::cout << "Can't init GLFW. Exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    std::cout << "About to create window..." << std::endl;
    window = glfwCreateWindow(1024, 700, "9 is wireframe, 0 is solid", NULL, NULL);
    if (!window)
    {
        // Can't init openGL. Oh no. 
        std::cout << "ERROR: Can't create window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //// Print out some texture stats
    //GLint texture_units = 0;
    //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
    //std::cout << "GL_MAX_TEXTURE_IMAGE_UNITS = " << texture_units << std::endl;
    //std::cout << "(aka, the MAXIMUM number of texture units that can be run AT THE SAME TIME)" << std::endl;
    //
    //GLint combined_texture_unit_count = 0;
    //glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &combined_texture_unit_count);
    //std::cout << "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = " << combined_texture_unit_count << std::endl;


    // Note the additional GLFW callbacks (we only had the key and error callbacks)
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetWindowSizeCallback(window, window_size_callback);


    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


    ::g_pShaderManager = new cShaderManager();          // HEAP  

    cShaderManager::cShader vertShader;
    cShaderManager::cShader fragShader;

    vertShader.fileName = "simpleVertex.glsl";
    fragShader.fileName = "simpleFragment.glsl";

    if ( ! ::g_pShaderManager->createProgramFromFile( "SimpleShaderProg",
                                                      vertShader, fragShader) )
    {
        // There was problem. 
        std::cout << "ERROR: can't make shader program because: " << std::endl;
        std::cout << ::g_pShaderManager->getLastError() << std::endl;
        
        // Exit program (maybe add some cleanup code)
        return -1;
    }
    else
    {
        std::cout << "Shader complie and link = OK" << std::endl;
    }
    //createProgramFromFile


    program = ::g_pShaderManager->getIDFromFriendlyName("SimpleShaderProg");

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");


    // STARTOF: Loading the models
    ::g_pTheVAOManager = new cVAOManager();

    sModelDrawInfo mdiArena;
    if ( ! ::g_pTheVAOManager->LoadModelIntoVAO( "assets/models/free_arena_ASCII_xyz_n_rgba_uv.ply",
                                                 mdiArena, program) )
    {
        std::cout << "Error: " << ::g_pTheVAOManager->getLastError() << std::endl;
    }

    // Create a texture manager
    ::g_pTheTextureManager = new cBasicTextureManager();


    // Load the models
    LoadAllThemodels( program, ::g_pTheVAOManager );



    ::g_pLightManager = new cLightManager();

    ::g_pLightManager->LoadUniformLocations(program);

    ::g_pLightManager->vecLights[0].position = glm::vec4(34.0f, 87.0f, 47.0f, 1.0f);
    ::g_pLightManager->vecLights[0].param1.x = 0;   // Point light
    ::g_pLightManager->vecLights[0].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[0].atten.y = 0.0150704719f;    // Linear
    ::g_pLightManager->vecLights[0].atten.z = 2.42356309e-05f;    // Quadratic
    ::g_pLightManager->vecLights[0].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[0].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[0].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    // Engine lights on the Y-Wing
    ::g_pLightManager->vecLights[1].position = glm::vec4(14.0f, 10.0f, 7.0f, 1.0f);
    ::g_pLightManager->vecLights[1].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[1].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[1].atten.y = 0.0001f;    // Linear
    ::g_pLightManager->vecLights[1].atten.z = 0.457916f;    // Quadratic
    ::g_pLightManager->vecLights[1].diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[1].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[1].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    ::g_pLightManager->vecLights[2].position = glm::vec4(7.0f, 10.0f, 7.0f, 1.0f);
    ::g_pLightManager->vecLights[2].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[2].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[2].atten.y = 0.0001f;    // Linear
    ::g_pLightManager->vecLights[2].atten.z = 0.457916f;    // Quadratic
    ::g_pLightManager->vecLights[2].diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[2].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[2].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    // Light inside the "torpedo" (blue)
    ::g_pLightManager->vecLights[3].position = glm::vec4(10.0f, 10.0f, -20.0f, 1.0f);
    ::g_pLightManager->vecLights[3].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[3].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[3].atten.y = 0.0001f;    // Linear
    ::g_pLightManager->vecLights[3].atten.z = 0.0470901f;    // Quadratic
    ::g_pLightManager->vecLights[3].diffuse = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[3].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[3].param2.x = 1.0f;        // 1.0 for on (0.0 for off)


    // Engine lights for the X-wing
    ::g_pLightManager->vecLights[4].position = glm::vec4(-4.2f, 5.0f, 24.0f, 1.0f);
    ::g_pLightManager->vecLights[4].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[4].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[4].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[4].atten.z = 3.71354f;    // Quadratic
    ::g_pLightManager->vecLights[4].diffuse = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[4].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[4].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    ::g_pLightManager->vecLights[5].position = glm::vec4(-2.7f, 5.0f, 24.0f, 1.0f);
    ::g_pLightManager->vecLights[5].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[5].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[5].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[5].atten.z = 3.71354f;    // Quadratic
    ::g_pLightManager->vecLights[5].diffuse = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[5].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[5].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    ::g_pLightManager->vecLights[6].position = glm::vec4(-4.2f, 6.7f, 24.0f, 1.0f);
    ::g_pLightManager->vecLights[6].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[6].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[6].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[6].atten.z = 3.71354f;    // Quadratic
    ::g_pLightManager->vecLights[6].diffuse = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[6].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[6].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    ::g_pLightManager->vecLights[7].position = glm::vec4(-2.7f, 6.7f, 24.0f, 1.0f);
    ::g_pLightManager->vecLights[7].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[7].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[7].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[7].atten.z = 3.71354f;    // Quadratic
    ::g_pLightManager->vecLights[7].diffuse = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[7].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[7].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

//    ::g_pLightManager->vecLights[8].position = glm::vec4(-2.7f, 6.7f, 24.0f, 1.0f);
    ::g_pLightManager->vecLights[8].param1.x = 0.0f;   // Point light
    ::g_pLightManager->vecLights[8].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[8].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[8].atten.z = 0.21354f;    // Quadratic
    ::g_pLightManager->vecLights[8].diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[8].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // Make light OFF to start
    ::g_pLightManager->vecLights[8].param2.x = 0.0f;        // 1.0 for on (0.0 for off)

    ::g_pLightManager->vecLights[9].position = glm::vec4(0.0f, 20.0f, 0.0f, 1.0f);
    ::g_pLightManager->vecLights[9].param1.x = 1.0f;   // Spot light
    ::g_pLightManager->vecLights[9].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[9].atten.y = 0.00001f;    // Linear
    ::g_pLightManager->vecLights[9].atten.z = 0.002f;    // Quadratic
    ::g_pLightManager->vecLights[9].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[9].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pLightManager->vecLights[9].param2.x = 1.0f;        // 1.0 for on (0.0 for off)

    // Direction is relative to the light
    // 0, -1, 0 is stright down from the light
    ::g_pLightManager->vecLights[9].direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);
//    ::g_pLightManager->vecLights[9].direction = glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f);

    // If you do what you're looking at minus the position of spot, 
    //  that will give you a spot light that will "follow" objects. 

    // Pick the inner and outer angle of spot in degrees (this shader uses degrees)
    ::g_pLightManager->vecLights[9].param1.y = 15.0f;   // y = inner angle
    ::g_pLightManager->vecLights[9].param1.z = 30.0f;   // z = outer angle






    // STARTOF: Joysticks
    ::g_pJoysticks = new cJoystickManager();
    ::g_pJoysticks->InitOrReset();
    if (::g_pJoysticks->getNumberOfJoysticksPresent() > 0)
    {
        std::cout << "Found " << ::g_pJoysticks->getNumberOfJoysticksPresent() << " joysticks" << std::endl;
        for (int index = 0; index != ::g_pJoysticks->getNumberOfJoysticksPresent(); index++)
        {
            cJoystickManager::sJoyInfo joyInfo;
            ::g_pJoysticks->GetJoystickInfo(index, joyInfo, true);

            std::cout << "Joystick #" << index << " is a: " << joyInfo.getJoystickTypeAsString() << std::endl;
        }
    }
    else
    {
        std::cout << "Didn't find any joystocks." << std::endl;
    }
    // ENDOF: Joysticks

    
    // STARTOF: Fly Camera
    ::g_pFlyCamera = new cFlyCamera();
    ::g_pFlyCamera->eye = glm::vec3(0.0f, 30.0, -180.0);
    ::g_pFlyCamera->movementSpeed = 0.25f;
    // ENDOF: Fly Camera

    std::cout << "We're all set! Buckle up!" << std::endl;

    while ( ! glfwWindowShouldClose(window) )
    {
        float ratio;
        int width, height;


        glm::mat4 matProjection; 
        glm::mat4 matView; 
        // glm::mat4 mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);



        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        matProjection = glm::perspective( 0.6f,
                                          ratio,
                                          1.0f,          // Near plane
                                          2000.0f);      // Far plane


        matView = glm::mat4(1.0f);

        //matView = glm::lookAt( ::g_cameraEye,     // "position" "eye"
        //                       ::g_cameraTarget,  // "at"  (looking "at")
        //                       ::g_upVector );    

        matView = glm::lookAt( ::g_pFlyCamera->getEye(),     // "position" "eye"
                               ::g_pFlyCamera->getAt(),  // "at"  (looking "at")
                               ::g_pFlyCamera->getUp());


        GLint eyeLocation_UniLoc = glGetUniformLocation( program, "eyeLocation");
        //glUniform4f( eyeLocation_UniLoc, 
        //            ::g_cameraEye.x, ::g_cameraEye.y, ::g_cameraEye.z, 
        //            1.0f);  // Not using 4th, so set to 1.0f
        glUniform4f( eyeLocation_UniLoc, 
                    ::g_pFlyCamera->getEye().x, ::g_pFlyCamera->getEye().y, ::g_pFlyCamera->getEye().z,
                    1.0f);  // Not using 4th, so set to 1.0f
        
        // Pass the lighting info to the shader
        ::g_pLightManager->CopyLightValuesToShader();



        // STARTOF: Update anything per frame
        {
            // Move the skybox object to the location of the camera
            cMeshObject* pSkybox = findObjectByName("SkyBox");
            pSkybox->position = ::g_pFlyCamera->getEye();





            cMeshObject* pTorpedo = findObjectByName("Torpedo");

            if ( ::g_bTorpedoIsMoving )
            {
                // Update the topedo location
                const float TORPEDOMOVESPEED = 0.5f;
                pTorpedo->position.z += TORPEDOMOVESPEED;
                
                // Place the light inside the torpedo (i.e. at the same location)
                ::g_pLightManager->vecLights[8].position = glm::vec4(pTorpedo->position, 1.0f);
                // Turn light ON
                ::g_pLightManager->vecLights[8].param2.x = 1.0f;

                // Make torpedo visible
                pTorpedo->isVisible = true;

                // How far is the topedo?
                const float MAXTORPEDODISTANCE = 300.0f;
                if (glm::distance(pTorpedo->position, ::g_TorpedoStartLocation) > MAXTORPEDODISTANCE)
                {
                    ::g_bTorpedoIsMoving = false;
                }
            }
            else
            {
                // Turn light OFF
                ::g_pLightManager->vecLights[8].param2.x = 0.0f;
                // Hide torpedo
                pTorpedo->isVisible = false;
            }

            // "flicker" the engine lights on the X-Wing (not on exam, just something you could do...
            for (unsigned int index = 4; index != 8; index++)
            {
                ::g_pLightManager->vecLights[index].atten.x = 0.0f;         // Constant
                ::g_pLightManager->vecLights[index].atten.y = 0.00001f;    // Linear
                ::g_pLightManager->vecLights[index].atten.z = 3.71354f;    // Quadratic
                // Limit the light distance to a finite amount
//                ::g_pLightManager->vecLights[index].atten.w = 1.0f;         // No light beyond 5 units

                float rPerterb = ((float)rand() / (RAND_MAX));
                // Pick a number between 0.25 and 0.5f;
//                rPerterb /= 2.0f;
//                rPerterb += 0.25f;
                ::g_pLightManager->vecLights[index].atten.y += rPerterb;    // Linear
            }


            // Point the spot light at the AT-AT
            cMeshObject* pATAT = findObjectByName("ATAT");

            // Take the position of the ATAT - position of the light
            glm::vec3 spotDirection = pATAT->position - glm::vec3(::g_pLightManager->vecLights[9].position);
            // "Normalize", making ray a length of 1.0f; 
            spotDirection = glm::normalize(spotDirection);

            ::g_pLightManager->vecLights[9].direction = glm::vec4(spotDirection, 1.0f);


        }
        // ENDOF: Update anything per frame


        // *******************************************
        //    ____                       ____                       
        //   |  _ \ _ __ __ ___      __ / ___|  ___ ___ _ __   ___  
        //   | | | | '__/ _` \ \ /\ / / \___ \ / __/ _ \ '_ \ / _ \ 
        //   | |_| | | | (_| |\ V  V /   ___) | (_|  __/ | | |  __/ 
        //   |____/|_|  \__,_| \_/\_/   |____/ \___\___|_| |_|\___| 
        //                                                          
        // *******************************************

        // Separate non-transparent and transparent
        std::vector< cMeshObject* > vecTransparentObjects;
        std::vector< cMeshObject* > vecOpaqueObjects;

        for (std::vector< cMeshObject* >::iterator it_pCurMesh = ::g_pVecObjects.begin();
             it_pCurMesh != ::g_pVecObjects.end(); it_pCurMesh++)
        {
            cMeshObject* pCO = *it_pCurMesh;

            if (pCO->diffuseRGBA.a < 1.0f)
            {
                // It's transparent
                vecTransparentObjects.push_back(pCO);
            }
            else
            {
                vecOpaqueObjects.push_back(pCO);
            }
        }


        // Sort the transparent object from FAR to CLOSE (relative to the camer)
//        std::sort(vecOpaqueObjects.begin(), vecOpaqueObjects.end(), IsACloserToCamera);
        std::sort(vecOpaqueObjects.begin(), vecOpaqueObjects.end(), cIsACloserToCamera(::g_pFlyCamera->getEye() ) );


        // Draw the opaque things first 
        for ( std::vector< cMeshObject* >::iterator it_pCurMesh = vecOpaqueObjects.begin();
              it_pCurMesh != vecOpaqueObjects.end(); it_pCurMesh++ )
        {
            cMeshObject* pTheObject = *it_pCurMesh;
            
            // All the draw code was here:
            DrawObject( pTheObject, program, matView, matProjection );

        }//for ( std::vector< cMeshObject* >




        // Draw the opaque things first 
        for ( std::vector< cMeshObject* >::iterator it_pCurMesh = vecTransparentObjects.begin();
              it_pCurMesh != vecTransparentObjects.end(); it_pCurMesh++ )
        {
            cMeshObject* pTheObject = *it_pCurMesh;
            
            // All the draw code was here:
            DrawObject( pTheObject, program, matView, matProjection );

        }//for ( std::vector< cMeshObject* >

        // *******************************************
        //    ____                       ____                       
        //   |  _ \ _ __ __ ___      __ / ___|  ___ ___ _ __   ___  
        //   | | | | '__/ _` \ \ /\ / / \___ \ / __/ _ \ '_ \ / _ \ 
        //   | |_| | | | (_| |\ V  V /   ___) | (_|  __/ | | |  __/ 
        //   |____/|_|  \__,_| \_/\_/   |____/ \___\___|_| |_|\___| 
        //                                                          
        // *******************************************


        // ADD 
        if (::g_ShowLightDebugSpheres)
        {

            cMeshObject* pDebugBall = findObjectByName("DebugSphere");

            pDebugBall->isVisible = true;
            pDebugBall->position = ::g_pLightManager->vecLights[g_selectedLightID].position;
            pDebugBall->scale = 1.0f;
            pDebugBall->diffuseRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            DrawObject(pDebugBall, program, matView, matProjection );
            pDebugBall->isVisible = false;

            cLightHelper myHelper;
            float dist5 = myHelper.calcApproxDistFromAtten(0.05f, 0.01f, 1000000,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.x,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.y,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.z,
                                                           50);
            float dist25 = myHelper.calcApproxDistFromAtten(0.25f, 0.01f, 1000000,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.x,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.y,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.z,
                                                           50);
            float dist50 = myHelper.calcApproxDistFromAtten(0.50f, 0.01f, 1000000,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.x,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.y,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.z,
                                                           50);

            float dist75 = myHelper.calcApproxDistFromAtten(0.75f, 0.01f, 1000000,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.x,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.y,
                                                           g_pLightManager->vecLights[g_selectedLightID].atten.z,
                                                           50);

            // Draw sphere to match the brightness of the light
            pDebugBall->isVisible = true;
            pDebugBall->diffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            pDebugBall->scale = dist5;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->diffuseRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            pDebugBall->scale = dist25;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->diffuseRGBA = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
            pDebugBall->scale = dist50;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->diffuseRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
            pDebugBall->scale = dist75;
            DrawObject(pDebugBall, program, matView, matProjection);
            pDebugBall->isVisible = false;\
        
        }// if (::g_ShowLightDebugSpheres)

       // ****************************
        // **** END OF: Draw scene ****
        // ****************************


        // Update the window title
        std::stringstream ssTitle;
        ssTitle 
            << "Light# " << g_selectedLightID << " : " 
            << ::g_pLightManager->vecLights[g_selectedLightID].position.x << ", "
            << ::g_pLightManager->vecLights[g_selectedLightID].position.y << ", "
            << ::g_pLightManager->vecLights[g_selectedLightID].position.z << "  "
            << "Lin:" << ::g_pLightManager->vecLights[g_selectedLightID].atten.y << "  "
            << "Quad:" << ::g_pLightManager->vecLights[g_selectedLightID].atten.z;

        if (::g_pLightManager->vecLights[g_selectedLightID].param1.x == 1.0f)
        {
            // It's a spot light, so print angles, too
            ssTitle << "  "
                << "Inner: " << ::g_pLightManager->vecLights[g_selectedLightID].param1.y << "   "
                << "Outer: " << ::g_pLightManager->vecLights[g_selectedLightID].param1.z;
        }

        std::string sTitleText = ssTitle.str();

        glfwSetWindowTitle(window, sTitleText.c_str());

        ProcessAsyncKeys(window);
        ProcessAsyncMouse(window);
        ::g_pJoysticks->Update();
        ProcessAsyncJoysticks();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }//while ( ! glfwWindowShouldClose(window) )


    ShutErDown();


    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


// HACK: 
static glm::vec2 heightMapTextureOffset = glm::vec2(0.0f, 0.0f);
static float textureRotationAngle = 0.0f;


void DrawObject( cMeshObject* pCurMesh, 
                 GLuint program,                // Shader program
                 glm::mat4 &matView,            // View matrix
                 glm::mat4 &matProjection)      // Projection matrix
{
    // For ease, copy the pointer to a sensible variable name
//    cMeshObject* pCurMesh = *it_pCurMesh;

    if ( !pCurMesh->isVisible )
    {
        // Don't draw it
        return;
    }

    GLint bTreeDiscardExample_UL = glGetUniformLocation(program, "bTreeDiscardExample");
    if (pCurMesh->friendlyName == "QuadForTree")
    {
        // Set this flag to turn on this "tree discard" example
        glUniform1f(bTreeDiscardExample_UL, (float)GL_TRUE);

        glActiveTexture(GL_TEXTURE25);
        glBindTexture(GL_TEXTURE_2D, ::g_pTheTextureManager->getTextureIDFromName("tree_texture.bmp"));
        GLint texture0A_UL = glGetUniformLocation(program, "texture0A");
        glUniform1i(texture0A_UL, 25);  // 25, not GL_TEXTURE25


        glActiveTexture(GL_TEXTURE26);
        glBindTexture(GL_TEXTURE_2D, ::g_pTheTextureManager->getTextureIDFromName("tree_texture_mask.bmp"));
        GLint textureDiscard_UL = glGetUniformLocation(program, "textureDiscard");
        glUniform1i(textureDiscard_UL, 26);  // 25, not GL_TEXTURE25
    }
    else
    {
        glUniform1f(bTreeDiscardExample_UL, (float)GL_FALSE);
    }


    // STARTOF: Discard texture portion

    // If the object has a "discard" texutre, then enable this
    GLint bUseDiscardTexture_UniLoc = glGetUniformLocation(program, "bUseDiscardTexture");
    if (pCurMesh->discardTexture != "")
    {
        // uniform sampler2D textureDiscard;
        // uniform bool bUseDiscardTexture;
        GLint textureDiscardSampler_UniLoc = glGetUniformLocation(program, "textureDiscard");

        glUniform1f( bUseDiscardTexture_UniLoc, (float)GL_TRUE);

        glActiveTexture(GL_TEXTURE16);
        GLuint discardTextureID = ::g_pTheTextureManager->getTextureIDFromName(pCurMesh->discardTexture);
        glBindTexture(GL_TEXTURE_2D, discardTextureID);

        glUniform1i(textureDiscardSampler_UniLoc, 16);  // Note 16, not GL_TEXTURE16
    }
    else
    {
        glUniform1f( bUseDiscardTexture_UniLoc, (float)GL_FALSE);
    }//if (pCurMesh->discardTexture != "")

    // ENDOF: Discard texture portion

    // ***********************************************************
    //    _____        _                  ___ _         __  __ 
    //   |_   _|____ _| |_ _  _ _ _ ___  / __| |_ _  _ / _|/ _|
    //     | |/ -_) \ /  _| || | '_/ -_) \__ \  _| || |  _|  _|
    //     |_|\___/_\_\\__|\_,_|_| \___| |___/\__|\_,_|_| |_|  
    //                                                         
    // glActiveTexture(GL_TEXTURE1 );	
    // glBindTexture(GL_TEXTURE_2D, 15);
    // glUniform1i(UniformLoc_Sampler0A, GL_TEXTURE1);

    // Inside the shader, we have these samplers:
    // uniform sampler2D texture0A;
    // uniform sampler2D texture0B;

    GLint texture0A_UniLoc = glGetUniformLocation( program, "texture0A" );
    GLint texture0B_UniLoc = glGetUniformLocation( program, "texture0B" );
    GLint texture0C_UniLoc = glGetUniformLocation( program, "texture0C" );
    GLint texture0D_UniLoc = glGetUniformLocation( program, "texture0D" );

    // Choose texture units for the textures
    // Cobblestone: Pick texture unit 0
    glActiveTexture( GL_TEXTURE0 ); // Choose texture unit #0
    // Get texture id (from the name we loaded using the texture manager)
//    GLuint cobblestoneText_ID = ::g_pTheTextureManager->getTextureIDFromName("cobblestone.bmp");
    GLuint texture_00_ID = ::g_pTheTextureManager->getTextureIDFromName(pCurMesh->textureNames[0]);
    // Make that texture "current" (aka "bind" it)
    glBindTexture( GL_TEXTURE_2D, texture_00_ID);    // This is the "current" texture
    // Connect the sampler to the "Texture Unit"
    glUniform1i( texture0A_UniLoc, 0 );     // Note: we pass a NUMBER, not an enum (GL_TEXTURE0)


    // TODO: You will have to set these texture names form the cMeshObject, too
    glActiveTexture( GL_TEXTURE1 );
//    GLuint fauci_TextID = ::g_pTheTextureManager->getTextureIDFromName("fauci.bmp");
    GLuint texture_01_ID = ::g_pTheTextureManager->getTextureIDFromName(pCurMesh->textureNames[1]);
    glBindTexture( GL_TEXTURE_2D, texture_01_ID);
    glUniform1i( texture0B_UniLoc, 1 );     // Note the integer '1' instead of GL_TEXTURE7


    glActiveTexture( GL_TEXTURE2 );    
    GLuint texture_02_ID = ::g_pTheTextureManager->getTextureIDFromName(pCurMesh->textureNames[2]);
    glBindTexture(GL_TEXTURE_2D, texture_02_ID);
    glUniform1i(texture0C_UniLoc, 2);     

    glActiveTexture( GL_TEXTURE3 );
    GLuint texture_03_ID = ::g_pTheTextureManager->getTextureIDFromName(pCurMesh->textureNames[3]);
    glBindTexture(GL_TEXTURE_2D, texture_03_ID);
    glUniform1i(texture0C_UniLoc, 3);     
    // ...and so on

    //uniform vec4 textureRatios;
    GLint textureRatio_UniLoc = glGetUniformLocation( program, "textureRatios" );

    //glUniform4f( textureRatio_UniLoc, 
    //             0.0f,      // Cobblestone
    //             1.0f,      // Fauci
    //             0.0f,      // (Undefined - texture will be black)
    //             0.0f );    // (Undefined - texture will be black)
    glUniform4f( textureRatio_UniLoc, 
                 pCurMesh->texRatios[0],      
                 pCurMesh->texRatios[1],
                 pCurMesh->texRatios[2],     
                 pCurMesh->texRatios[3]);    


    // Height map in vertex shader
    //    _  _     _      _   _                      
    //   | || |___(_)__ _| |_| |_   _ __  __ _ _ __  
    //   | __ / -_) / _` | ' \  _| | '  \/ _` | '_ \ 
    //   |_||_\___|_\__, |_||_\__| |_|_|_\__,_| .__/ 
    //              |___/                     |_|    
//
//   GLint textureHeightMap_UniLoc = glGetUniformLocation( program, "textureHeightMap" );
//   GLint bUseHeightMap_UniLoc = glGetUniformLocation( program, "bUseHeightMap" );
//
//   // HACK: If this is the terrain, then set these uniforms
//   if (pCurMesh->friendlyName == "terrain")
//   {
//       glUniform1f(bUseHeightMap_UniLoc, (float)GL_TRUE );
//
//       // 
//       glActiveTexture(GL_TEXTURE30);
//       GLuint heightMap_TextID = ::g_pTheTextureManager->getTextureIDFromName("02-australia-gray.bmp");
//       glBindTexture(GL_TEXTURE_2D, heightMap_TextID);
//       glUniform1i(textureHeightMap_UniLoc, 30);     // Note the integer '30' instead of GL_TEXTUREXX
//
//       // HACK: Change the value over time
///        heightMapTextureOffset.x += 0.001f;
//       textureRotationAngle += glm::radians(0.1f);
//
//       glm::mat4 matRotTexture = glm::rotate(glm::mat4(1.0f),
//                                             textureRotationAngle, // (float) glfwGetTime(), 
//                                             glm::vec3(0.0f, 0.0f, 1.0f));
//       GLint matTextRotation_UniLoc = glGetUniformLocation(program, "matTextRotation");
//       glUniformMatrix4fv(matTextRotation_UniLoc, 1, GL_FALSE, glm::value_ptr(matRotTexture));
//
//
//       GLint textOffsetVS_UniLoc = glGetUniformLocation( program, "textOffsetVS" );
//       glUniform2f(textOffsetVS_UniLoc, heightMapTextureOffset.x, heightMapTextureOffset.y);
//   }
//   else
//   {
//       glUniform1f(bUseHeightMap_UniLoc, (float)GL_FALSE );
//   }
//   //    _  _     _      _   _                      
//   //   | || |___(_)__ _| |_| |_   _ __  __ _ _ __  
//   //   | __ / -_) / _` | ' \  _| | '  \/ _` | '_ \ 
//   //   |_||_\___|_\__, |_||_\__| |_|_|_\__,_| .__/ 
//   //              |___/                     |_|    
    //    _____        _                  ___ _         __  __ 
    //   |_   _|____ _| |_ _  _ _ _ ___  / __| |_ _  _ / _|/ _|
    //     | |/ -_) \ /  _| || | '_/ -_) \__ \  _| || |  _|  _|
    //     |_|\___/_\_\\__|\_,_|_| \___| |___/\__|\_,_|_| |_|  
    //                                                         
     // ***********************************************************


    // Get the uniform location variables (can do this outside of call for performance)
    GLint diffuseColourRGBA_LocID = glGetUniformLocation(program, "diffuseColourRGBA");
    GLint specularColour_LocID = glGetUniformLocation(program, "specularColour");
    if (specularColour_LocID == -1)
    {
        std::cout << "Can't find specularColour uniform in shader" << std::endl;
    }


    GLint matModel_LocID = glGetUniformLocation(program, "matModel");
    GLint matView_LocID = glGetUniformLocation(program, "matView");
    GLint matProj_LocID = glGetUniformLocation(program, "matProj");

    GLint hasNoLighting_LocID = glGetUniformLocation(program, "hasNoLighting");


    glm::mat4 matModel;

    //         mat4x4_identity(m);
    matModel = glm::mat4(1.0f);

    // ****************************
    // *** Model transfomations ***
    // Place the object in the world at 'this' location
    glm::mat4 matTranslation
        = glm::translate(glm::mat4(1.0f),
                         glm::vec3(pCurMesh->position.x,
                                   pCurMesh->position.y,
                                   pCurMesh->position.z));
    matModel = matModel * matTranslation;


    //mat4x4_rotate_Z(m, m, );
    //*************************************
    // ROTATE around Z
    glm::mat4 matRotateZ = glm::rotate(glm::mat4(1.0f),
                                       pCurMesh->orientation.z, // (float) glfwGetTime(), 
                                       glm::vec3(0.0f, 0.0f, 1.0f));
    matModel = matModel * matRotateZ;
    //*************************************

    //*************************************
    // ROTATE around Y
    glm::mat4 matRotateY = glm::rotate(glm::mat4(1.0f),
                                       pCurMesh->orientation.y, // (float) glfwGetTime(), 
                                       glm::vec3(0.0f, 1.0f, 0.0f));
    matModel = matModel * matRotateY;
    //*************************************

    //*************************************
    // ROTATE around X
    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
                                    pCurMesh->orientation.x, // (float) glfwGetTime(), 
                                    glm::vec3(1.0f, 0.0, 0.0f));
    matModel = matModel * rotateX;
    //*************************************


    // Set up a scaling matrix
    glm::mat4 matScale = glm::mat4(1.0f);

    float theScale = pCurMesh->scale;		// 1.0f;		
    matScale = glm::scale(glm::mat4(1.0f),
                          glm::vec3(theScale, theScale, theScale));


    // Apply (multiply) the scaling matrix to 
    // the existing "model" (or "world") matrix
    matModel = matModel * matScale;

    // *** Model transfomations ***
    // *********************************


    glUseProgram(program);

    //mat4x4_mul(mvp, p, m);
    //mvp = p * v * matModel;
    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glUniformMatrix4fv(matModel_LocID, 1, GL_FALSE, glm::value_ptr(matModel));
    glUniformMatrix4fv(matView_LocID, 1, GL_FALSE, glm::value_ptr(matView));
    glUniformMatrix4fv(matProj_LocID, 1, GL_FALSE, glm::value_ptr(matProjection));


    // This will change the model to "wireframe" and "solid"
    // In this example, it's changed by pressing "9" and "0" keys
    if (pCurMesh->isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe
        // Note: there's no "bool", but you pass a float
        // Turn OFF the lighting on THIS object
        glUniform1f(hasNoLighting_LocID, (float)GL_TRUE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Solid
        // Turn ON the lighting on THIS object
        glUniform1f(hasNoLighting_LocID, (float)GL_FALSE);
    }

    // Alpha transparency using the "blend" function
    // it's a "2 pass" effect, reading then writing to the "back buffer" (the screen)
    // If we DON'T need it, then disable it
    // The "alpha" value can be from 0.0 to 1.0f
    // If it's 1.0, then there's NO transparency, so there's no reason to enable this
    if (pCurMesh->diffuseRGBA.a < 1.0f)
    {
        // Enable transparency 
        glEnable(GL_BLEND);
    }
    else
    {
        // Disable 
        glDisable(GL_BLEND);
    }
    // This sets the state of the blend function
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );



    // **********************************************************
    // Is this the tranparent thing Feeney wanted for CP11?
    // uniform bool bUseTranspTexture;	// If true, then use transparency texture
    GLint bUseTranspTexture_UL = glGetUniformLocation(program, "bUseTranspTexture");

    if (pCurMesh->friendlyName == "Spidey")
    {
        // This is sort of redundant as I could have set the diffuseRGBA.a < 1.0f;
        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        // 
        // Picked 16 becauss it's not yet being used
        glActiveTexture(GL_TEXTURE16);
        GLuint texPerlinNoise_ID = ::g_pTheTextureManager->getTextureIDFromName("PerlinNoise.bmp");
        glBindTexture(GL_TEXTURE_2D, texPerlinNoise_ID);

        // uniform sampler2D textTransp;	// Texture used to sample alpha values
        GLint textTransp_UL = glGetUniformLocation(program, "textTransp");
        glUniform1i(textTransp_UL, 16);     // GL_TEXTURE16


        // uniform bool bUseTranspTexture;	// If true, then use transparency texture
        glUniform1f(bUseTranspTexture_UL, static_cast<float>(GL_TRUE));

    }
    else
    {
        glDisable(GL_BLEND);
        glUniform1f(bUseTranspTexture_UL, static_cast<float>(GL_FALSE));
    }//if (pCurMesh->friendlyName
    // **********************************************************



    // set the uniform colour info
    //  GLint objectColour_LocID = glGetUniformLocation(program, "objectColour");
    glUniform4f(diffuseColourRGBA_LocID,
                pCurMesh->diffuseRGBA.r,        
                pCurMesh->diffuseRGBA.g,        
                pCurMesh->diffuseRGBA.b,        
                pCurMesh->diffuseRGBA.a);       
    glUniform4f(specularColour_LocID,
                pCurMesh->specularRGB_Power.r,
                pCurMesh->specularRGB_Power.g,
                pCurMesh->specularRGB_Power.b,
                pCurMesh->specularRGB_Power.w); 





    //    ___ _        _                _____     _         __  __         __   
    //   / __| |___  _| |__  _____ __  / / __|  _| |__  ___|  \/  |__ _ _ _\ \  
    //   \__ \ / / || | '_ \/ _ \ \ / | | (_| || | '_ \/ -_) |\/| / _` | '_ \ | 
    //   |___/_\_\\_, |_.__/\___/_\_\ | |\___\_,_|_.__/\___|_|  |_\__,_| .__/ | 
    //            |__/                 \_\                             |_| /_/  
    // Is this the skybox object we're drawing
    // uniform bool bIsSkybox;			// If true, samples from cubemap
    GLint bIsSkybox_UL = glGetUniformLocation(program, "bIsSkybox");
    if (pCurMesh->friendlyName == "SkyBox")
    {
        // yes
        glUniform1f(bIsSkybox_UL, (float)GL_TRUE);

        glActiveTexture(GL_TEXTURE20);
        GLuint texSunnyDaySkyBox_ID = ::g_pTheTextureManager->getTextureIDFromName("sunnyday");
        // Note that this is GL_TEXTURE_CUBE_MAP instead of GL_TEXTURE_2D
        glBindTexture(GL_TEXTURE_CUBE_MAP, texSunnyDaySkyBox_ID);   // ***WARNING WILL ROBINSON!!!****

        // uniform samplerCube skyBox01;
        GLint texCubeSkyBox01_UL = glGetUniformLocation(program, "texCubeSkyBox01");
        glUniform1i(texCubeSkyBox01_UL, 20);     // GL_TEXTURE20

    }
    else
    {
        // Is NOT a skybox, so turn this "off"
        glUniform1f(bIsSkybox_UL, (float)GL_FALSE);
    }



    sModelDrawInfo mdoModelToDraw;
    if (::g_pTheVAOManager->FindDrawInfoByModelName(pCurMesh->meshName,
                                                    mdoModelToDraw))
    {
        glBindVertexArray(mdoModelToDraw.VAO_ID);

        glDrawElements(GL_TRIANGLES,
                       mdoModelToDraw.numberOfIndices,
                       GL_UNSIGNED_INT,     // How big the index values are 
                       0);        // Starting index for this model

        glBindVertexArray(0);
    }

    return;
}// DrawObject()


bool StartErUp(std::vector<std::string> vecCommands)
{


    return true;
}

bool ShutErDown(void)
{
    if (::g_pShaderManager)
    {
        delete ::g_pShaderManager;
    }

    if (::g_pTheTextureManager)
    {
        delete ::g_pTheTextureManager;
    }

    if (::g_pLightManager)
    {
        delete ::g_pLightManager;
    }

    return true;
}
