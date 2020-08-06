#ifndef _globalThings_HG_
#define _globalThings_HG_
// globalVariables.h

#include "globalOpenGLStuff.h"
#include <vector>
#include <glm/vec3.hpp>
#include "cMeshObject.h"
#include "cVAOManager.h"
#include "cBasicTextureManager/cBasicTextureManager.h"
#include "FlyCamera/cFlyCamera.h"
#include "Joystick/cJoystickManager.h"

// If it's a header, but struct, class, or extern
// NEVER the actual variable. 

void LoadAllThemodels(unsigned int program,
                      cVAOManager* pTheVAOManager);



extern glm::vec3 g_TorpedoStartLocation;    // glm::vec3(0.25f, 3.5f, 4.5f);
extern bool g_bTorpedoIsMoving;             // = false

extern std::vector< cMeshObject* > g_pVecObjects;       // in theMain.cpp
extern cBasicTextureManager* g_pTheTextureManager;      // in theMain.cpp
extern cJoystickManager* g_pJoysticks;                  // in theMain.cpp
extern cFlyCamera* g_pFlyCamera;                        // in theMain.cpp



void cursor_enter_callback(GLFWwindow* window, int entered);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);

void ProcessAsyncMouse(GLFWwindow* window);
void ProcessAsyncKeys(GLFWwindow* window);
void ProcessAsyncJoysticks(void);

#endif 
