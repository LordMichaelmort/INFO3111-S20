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

#include "LightManager/cLightManager.h"

// Function signature for DrawObject()
void DrawObject(cMeshObject* pCurMesh,
                GLuint program,                // Shader program
                glm::mat4& matView,            // View matrix
                glm::mat4& matProjection);      // Projection matrix


// Camera stuff
glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, +100.0f);
glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 g_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

// The objects we are drawing go in here! Hazzah!
std::vector< cMeshObject* > g_pVecObjects;
int g_selectedObjectID = 0;

cLightManager* g_pLightManager = 0;    // or NULL or nullptr
int g_selectedLightID = 0;

bool g_ShowLightDebugSpheres = true;


//// This a light structure to match what's in the shader
//struct sLight
//{
//    glm::vec4 position;
//    glm::vec4 diffuse;
//    glm::vec4 specular;	// rgb = highlight colour, w = power
//    glm::vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
//    glm::vec4 direction;	// Spot, directional lights
//    glm::vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
//                    // 0 = pointlight
//                    // 1 = spot light
//                    // 2 = directional light
//    glm::vec4 param2;	// x = 0 for off, 1 for on
//
//    //void TurnONLight();
//    //void TurnOFFLight();
//    //void MakeSpotLight();
//};



//struct sVertex
//{
//    float x, y, z;      // NEW! With Zs
//    float r, g, b;
//};
//
//int g_numberOfVerts = 0;
//sVertex* g_pVertexBuffer = 0;     // or NULL or nullptr



//sVertex myArray[100];                       // STACK  
//sVertex* pMyArray = new sVertex[100];       // HEAP 
//delete [] pMyArray;
//
//sVertex vertices[6] =
//{
//    { -0.6f, -0.4f, 0.0f /*z*/, 1.0f, 0.0f, 0.0f },         // 0
//    {  0.6f, -0.4f, 0.0f /*z*/, 0.0f, 1.0f, 0.0f },         // 1 
//    {  0.0f,  0.6f, 0.0f /*z*/, 0.0f, 0.0f, 1.0f },         // 2
//    { -0.6f,  0.4f, 0.0f /*z*/, 1.0f, 0.0f, 0.0f },         // 3
//    {  0.6f,  0.4f, 0.0f /*z*/, 0.0f, 1.0f, 0.0f },
//    {  0.0f,  1.6f, 0.0f /*z*/, 0.0f, 0.0f, 1.0f }          // 5
//};


// Yes, it's global. Just be calm, for now.
cShaderManager* g_pShaderManager = 0;       // NULL

cVAOManager* g_pTheVAOManager = 0;          // NULL or nullptr

bool g_isWireFrame = false;

// For the AT-AT shooting thing
glm::vec3 g_TorpedoStartLocation = glm::vec3(0.25f, 3.5f, 4.5f);
bool g_bTorpedoIsMoving = false;


//static const char* vertex_shader_text =
//"#version 110\n"
//"uniform mat4 MVP;\n"
//"attribute vec3 vCol;\n"        
//"attribute vec3 vPos;\n"        
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = MVP * vec4(vPos, 1.0);\n"
//"    color = vCol;\n"
//"}\n";
//
//static const char* fragment_shader_text =
//"#version 110\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_FragColor = vec4(color, 1.0);\n"
//"}\n";

//void LoadPlyFile( std::string fileName )
//{
//    std::ifstream theFile( fileName.c_str() );
//
//    if (!theFile.is_open())
//    {
//        std::cout << "Oh NO!!" << std::endl;
//        return;
//    }
//
//    // Look for the work "vertex"
//    std::string temp;
//
//    bool bKeepReading = true;
//
//    while (bKeepReading)
//    {
//        theFile >> temp;    // Read next string
//        if (temp == "vertex")
//        {
//            bKeepReading = false;
//        }
//    }//while
//
////    int numberOfVerts = 0;
//    theFile >> ::g_numberOfVerts;
//    std::cout << ::g_numberOfVerts << std::endl;
//
//    // Make the vertex buffer the size we need
//    // Allocate "this" number of vertices
//    ::g_pVertexBuffer = new sVertex[::g_numberOfVerts];
//
//    while (true)
//    {
//        theFile >> temp;    // Read next string
//        if (temp == "face")
//        {
//            break;
//        }
//    }//while
//
//    int numberOfTriangles = 0;
//    theFile >> numberOfTriangles;
//    std::cout << numberOfTriangles << std::endl;
//
//
//    while (true)
//    {
//        theFile >> temp;    // Read next string
//        if (temp == "end_header")
//        {
//            break;
//        }
//    }//while
//
//    for (int index = 0; index != ::g_numberOfVerts; index++)
//    {
//        float x,y,z,r,g,b,a;
//        theFile >> x >> y >> z >> r >> g >> b >> a;
//
//        ::g_pVertexBuffer[index].x = x;
//        ::g_pVertexBuffer[index].y = y;
//        ::g_pVertexBuffer[index].z = z;
//        ::g_pVertexBuffer[index].r = r / 255.0f;
//        ::g_pVertexBuffer[index].g = g / 255.0f;
//        ::g_pVertexBuffer[index].b = b / 255.0f;
//    }
//
//    return;
//}

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
        

        if ( key==GLFW_KEY_0) { ::g_ShowLightDebugSpheres = true; }
        if ( key==GLFW_KEY_9) { ::g_ShowLightDebugSpheres = false; }

    }//if ( mods == GLFW_MOD_SHIFT )
            

    //std::cout << ::g_pLightManager->vecLights[0].atten.y 
    //    << "  " 
    //    << ::g_pLightManager->vecLights[0].atten.z << std::endl;


    // if ( mods == 0 ) then no "modifiers" are pressed
    if (mods == 0)
    {
        //::g_cameraEye.x -= CAMERASPEED;
        if (key == GLFW_KEY_A) { ::g_cameraEye.x -= CAMERASPEED; }
        if (key == GLFW_KEY_D) { ::g_cameraEye.x += CAMERASPEED; }
        if (key == GLFW_KEY_W) { ::g_cameraEye.z += CAMERASPEED; }
        if (key == GLFW_KEY_S) { ::g_cameraEye.z -= CAMERASPEED; }
        if (key == GLFW_KEY_Q) { ::g_cameraEye.y -= CAMERASPEED; }
        if (key == GLFW_KEY_E) { ::g_cameraEye.y += CAMERASPEED; }
    }//if (mods == 0)

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

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

//    // NOTE: OpenGL error checks have been omitted for brevity
//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//
//    //sVertex vertices[6]
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    unsigned int sizeOfVertBufferInBytes = sizeof(sVertex) * ::g_numberOfVerts;
//
//    glBufferData( GL_ARRAY_BUFFER, 
//                  sizeOfVertBufferInBytes,      // Size in bytes
//                  ::g_pVertexBuffer,            // Pointer to START of local array
//                  GL_STATIC_DRAW);

    //cShaderManager* g_pShaderManager = 0;
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

    //vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //glCompileShader(vertex_shader);
//
    //fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //glCompileShader(fragment_shader);
//
    //program = glCreateProgram();
    //glAttachShader(program, vertex_shader);
    //glAttachShader(program, fragment_shader);
    //glLinkProgram(program);

    program = ::g_pShaderManager->getIDFromFriendlyName("SimpleShaderProg");

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 
//                          3, GL_FLOAT, 
//                          GL_FALSE,
//                          sizeof(sVertex),      // "stride"
//                          (void*)offsetof(sVertex, x) );
//    //struct sVertex
    //{
    //    float x, y, z;      // NEW! With Zs
    //    float r, g, b;
    //};
//
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 
//                          3, GL_FLOAT, 
//                          GL_FALSE,
//                          sizeof(sVertex),               // "stride"
//                          (void*)offsetof(sVertex, r) ); // "offset" (how many bytes 'in' is this member?)

    // STARTOF: Loading the models
    ::g_pTheVAOManager = new cVAOManager();

    sModelDrawInfo mdiArena;
    if ( ! ::g_pTheVAOManager->LoadModelIntoVAO( "assets/models/free_arena_ASCII_xyz_n_rgba_uv.ply",
                                                 mdiArena, program) )
    {
        std::cout << "Error: " << ::g_pTheVAOManager->getLastError() << std::endl;
    }


    // Load the models
    LoadAllThemodels( program, ::g_pTheVAOManager );



    ::g_pLightManager = new cLightManager();

    ::g_pLightManager->LoadUniformLocations(program);

    ::g_pLightManager->vecLights[0].position = glm::vec4(34.0f, 87.0f, 47.0f, 1.0f);
    ::g_pLightManager->vecLights[0].param1.x = 0;   // Point light
    ::g_pLightManager->vecLights[0].atten.x = 0.0f;     // Constant
    ::g_pLightManager->vecLights[0].atten.y = 0.0150704719f;    // Linear
    ::g_pLightManager->vecLights[0].atten.z = 2.42356309e-05;    // Quadratic
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
    ::g_pLightManager->vecLights[3].atten.z = 0.0470901;    // Quadratic
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



    // Get the locations for the "uniform variables"
    //  uniform vec4 objectColour;



    std::cout << "We're all set! Buckle up!" << std::endl;

    while ( ! glfwWindowShouldClose(window) )
    {
        float ratio;
        int width, height;
        //       mat4x4 m, p, mvp;
//        uniform mat4 matModel;	// "model" or "world" matrix
//        uniform mat4 matView;		// "view" or "camera" or "eye" matrix
//        uniform mat4 matProj;		// "projection" matrix (ortographic or perspective)

//        glm::mat4 matModel;   // Moved to DrawObject() function
        glm::mat4 matProjection; 
        glm::mat4 matView; 
        // glm::mat4 mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);


        //mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//        glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
//                                        (float)glfwGetTime(),
//                                        glm::vec3(0.0f, 0.0, 1.0f));
//
//       m = m * rotateZ;

        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        matProjection = glm::perspective( 0.6f,
                                          ratio,
                                          0.1f,          // Near plane
                                          10000.0f);      // Far plane

        matView = glm::mat4(1.0f);

        //glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0f);
        //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        //glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

        matView = glm::lookAt( ::g_cameraEye,     // "position" "eye"
                         ::g_cameraTarget,  // "at"  (looking "at")
                         ::g_upVector );    

        
        // Pass the lighting info to the shader
        ::g_pLightManager->CopyLightValuesToShader();

        //// Get the uniform locations for the light(s)
        //GLint theLights_0_position_LocID = glGetUniformLocation(program, "theLights[0].position");
        //GLint theLights_0_diffuse_LocID = glGetUniformLocation(program, "theLights[0].diffuse");
        //GLint theLights_0_specular_LocID = glGetUniformLocation(program, "theLights[0].specular");
        //GLint theLights_0_atten_LocID = glGetUniformLocation(program, "theLights[0].atten");
        //GLint theLights_0_direction_LocID = glGetUniformLocation(program, "theLights[0].direction");
        //GLint theLights_0_param1_LocID = glGetUniformLocation(program, "theLights[0].param1");
        //GLint theLights_0_param2_LocID = glGetUniformLocation(program, "theLights[0].param2");

        //// Set the ligthing for the "scene"
        //glUniform4f( theLights_0_position_LocID, 50.0f, 100.0f, 100.0f, 1.0f);      // "theLights[0].position");
        //glUniform4f( theLights_0_diffuse_LocID, 1.0f, 1.0f, 1.0f, 1.0f);            //"theLights[0].diffuse");
        //glUniform4f( theLights_0_specular_LocID, 1.0f, 1.0f, 1.0f, 1.0f);       //"theLights[0].specular");
        //glUniform4f( theLights_0_atten_LocID, 0.0f, 0.01f, 0.0f, 1.0f );         //"theLights[0].atten");
        //glUniform4f( theLights_0_direction_LocID, 0.0f, 0.0f, 0.0f, 1.0f);      //"theLights[0].direction");
        //glUniform4f( theLights_0_param1_LocID, 0.0f, 0.0f, 0.0f, 0.0f );        //"theLights[0].param1");
        ////x = 0 for off, 1 for on
        //glUniform4f( theLights_0_param2_LocID, 1.0f, 0.0f, 0.0f, 1.0f );        //  "theLights[0].param2");


        // STARTOF: Update anything per frame
        {
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

                float rPerterb = ((float)rand() / (RAND_MAX));
                // Pick a number between 0.25 and 0.5f;
//                rPerterb /= 2.0f;
//                rPerterb += 0.25f;
                ::g_pLightManager->vecLights[index].atten.y += rPerterb;    // Linear
            }


        }
        // ENDOF: Update anything per frame


        // *******************************************
        // **** Draw the entire scene of objects *****
        // *******************************************
        for ( std::vector< cMeshObject* >::iterator it_pCurMesh = ::g_pVecObjects.begin();
              it_pCurMesh != ::g_pVecObjects.end(); it_pCurMesh++ )
        {
            cMeshObject* pTheObject = *it_pCurMesh;
            
            // All the draw code was here:
            DrawObject( pTheObject, program, matView, matProjection );

        }//for ( std::vector< cMeshObject* >


        // ADD 
        if (::g_ShowLightDebugSpheres)
        {

            cMeshObject* pDebugBall = findObjectByName("DebugSphere");

            pDebugBall->isVisible = true;
            pDebugBall->position = ::g_pLightManager->vecLights[g_selectedLightID].position;
            pDebugBall->scale = 1.0f;
            pDebugBall->colourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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
            pDebugBall->colourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            pDebugBall->scale = dist5;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->colourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            pDebugBall->scale = dist25;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->colourRGBA = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
            pDebugBall->scale = dist50;
            DrawObject(pDebugBall, program, matView, matProjection);

            pDebugBall->colourRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
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

        std::string sTitleText = ssTitle.str();

        glfwSetWindowTitle(window, sTitleText.c_str());



        glfwSwapBuffers(window);
        glfwPollEvents();

    }//while ( ! glfwWindowShouldClose(window) )


    delete ::g_pShaderManager;


    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}



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


    // Get the uniform location variables (can do this outside of call for performance)
    GLint diffuseColour_LocID = glGetUniformLocation(program, "diffuseColour");

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


    // set the uniform colour info
    //  GLint objectColour_LocID = glGetUniformLocation(program, "objectColour");
    glUniform3f(diffuseColour_LocID,
                pCurMesh->colourRGBA.r,
                pCurMesh->colourRGBA.g,
                pCurMesh->colourRGBA.b);


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
