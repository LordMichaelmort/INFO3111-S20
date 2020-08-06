#include "cJoystickManager.h"

#include "../globalOpenGLStuff.h"	// For the GLWF joystick enums, etc.#

#include <algorithm>

#include <iostream>

cJoystickManager::cJoystickManager()
{

	return;
}



void cJoystickManager::InitOrReset(void)
{
	this->m_vecJoysticks.clear();

	unsigned int JoyID = GLFW_JOYSTICK_1;
	do 
	{
		cJoystickManager::sJoyInfo curStick;
		curStick.ID = JoyID;
		if ( glfwJoystickPresent(curStick.ID) == GLFW_TRUE )
		{
			this->m_UpdateJoystickName( curStick );
		}//if(glfwJoystickPresent(curStick.ID)

		this->m_vecJoysticks.push_back(curStick);

		JoyID++;

	}while ( JoyID <= GLFW_JOYSTICK_LAST );

	// Update them all. Why not?
	this->Update();

	return;
}

void cJoystickManager::Update(void)
{
	for ( std::vector<sJoyInfo>::iterator itJoy = this->m_vecJoysticks.begin(); itJoy != this->m_vecJoysticks.end(); itJoy++ )
	{
		sJoyInfo &curJoy = *itJoy;

		if ( curJoy.bIsPresent )
		{
			this->m_UpdateJoystickAxes( curJoy );
			this->m_UpdateJoystickButtons( curJoy );
		}		
	}//for(std::vector<sJoyInfo>::iterator itJoy

	return;
}

void cJoystickManager::m_UpdateJoystickName( sJoyInfo &curJoystick )
{
	const char* joyName = glfwGetJoystickName(curJoystick.ID);
	if ( joyName != NULL )
	{
		curJoystick.name.clear();
		curJoystick.name.append(joyName);
		curJoystick.bIsPresent = true;
	}
	return;
}


void cJoystickManager::m_UpdateJoystickAxes( sJoyInfo &curJoystick )
{
	int count = 0;
	const float* axes = glfwGetJoystickAxes(curJoystick.ID, &count);
	
	curJoystick.vecAxes.clear();
	// Add enough entries...(if not present)
	while ( curJoystick.vecAxes.size() < count )
	{
		curJoystick.vecAxes.push_back(0.0f);
	}


	for ( int index = 0; index != count; index++ )
	{
		curJoystick.vecAxes[index] = axes[index];
	}
	return;
}
void cJoystickManager::m_UpdateJoystickButtons( sJoyInfo &curJoystick )
{
	int count = 0;
	const unsigned char* buttons = glfwGetJoystickButtons(curJoystick.ID, &count);
	
	curJoystick.vecButtons.clear();
	// Add enough entries...(if not present)
	while ( curJoystick.vecButtons.size() < count )
	{
		curJoystick.vecButtons.push_back(GLFW_RELEASE);
	}

	for ( int index = 0; index != count; index++ )
	{
		curJoystick.vecButtons[index] = buttons[index];
	}
	return;
}


unsigned int cJoystickManager::getFirstJoystickID(void)
{
	for ( unsigned int index = 0; index != (unsigned int)this->m_vecJoysticks.size(); index++ )
	{
		if ( this->m_vecJoysticks[index].bIsPresent )
		{
			return this->m_vecJoysticks[index].ID;
		}
	}
	// Didn't find anything
	return cJoystickManager::JOYSTICK_INVALID_ID;
}

unsigned int cJoystickManager::getNumberOfJoysticksPresent(void)
{
	unsigned int joystickCount = 0;

	for ( unsigned int index = 0; index != (unsigned int)this->m_vecJoysticks.size(); index++ )
	{
		if ( this->m_vecJoysticks[index].bIsPresent )
		{
			joystickCount++;
		}
	}

	return joystickCount;
}
bool cJoystickManager::isJoystickButtonDown( unsigned int JoystickID, unsigned int buttonID, bool bUpdateFirst /*=false*/ )
{
	if ( JoystickID > this->m_vecJoysticks.size() )
	{
		// Invalid joystick ID
		return false;
	}

	if ( ! this->m_IsJoystickPresent(JoystickID) )
	{
		// It's not there...
		return false;
	}

	if ( ! this->m_vecJoysticks[JoystickID].bIsPresent )
	{
		// not present
		return false;
	}

	if ( bUpdateFirst )
	{
		this->m_UpdateJoystickButtons( this->m_vecJoysticks[JoystickID] );
	}

	if ( buttonID > this->m_vecJoysticks[JoystickID].vecButtons.size() )
	{
		// Invalid button ID
		return false;
	}

	if ( this->m_vecJoysticks[JoystickID].vecButtons[buttonID] == GLFW_PRESS )
	{
		return true;
	}
	// else it's == GLFW_RELEASE

	return false;
}

bool cJoystickManager::Update( unsigned int JoystickID )
{
	if ( JoystickID > this->m_vecJoysticks.size() )
	{
		// Invalid joystick ID
		return false;
	}

	this->m_UpdateJoystickAxes( this->m_vecJoysticks[JoystickID] );
	this->m_UpdateJoystickButtons( this->m_vecJoysticks[JoystickID] );

	return true;
}



bool cJoystickManager::getJoystickState( unsigned int JoystickID, std::vector<float> &vecAxes, bool bUpdateFirst /*=false*/ )
{
	if ( bUpdateFirst )
	{
		if ( ! this->Update( JoystickID ) )
		{
			// Invalid joystick ID
			return false;
		}
	}

	if ( ! this->m_IsJoystickPresent(JoystickID) )
	{
		// It's not there...
		return false;
	}

	if ( JoystickID > this->m_vecJoysticks.size() )
	{
		// Invalid Joystick ID
		return false;
	}

	// Copy state back
	while ( vecAxes.size() < this->m_vecJoysticks[JoystickID].vecAxes.size() )
	{
		vecAxes.push_back(0.0f);
	}
	
	std::copy( this->m_vecJoysticks[JoystickID].vecAxes.begin(), 
			   this->m_vecJoysticks[JoystickID].vecAxes.end(), 
			   vecAxes.begin() );
	return true;
}

bool cJoystickManager::getJoystickState( unsigned int JoystickID, std::vector<unsigned char> &vecButtons, bool bUpdateFirst /*=false*/ )
{
	if ( bUpdateFirst )
	{
		if ( ! this->Update( JoystickID ) )
		{
			// Invalid joystick ID
			return false;
		}
	}

	if ( ! this->m_IsJoystickPresent(JoystickID) )
	{
		// It's not there...
		return false;
	}

	if ( JoystickID > this->m_vecJoysticks.size() )
	{
		// Invalid Joystick ID
		return false;
	}

	// Copy state back
	while ( vecButtons.size() < this->m_vecJoysticks[JoystickID].vecButtons.size() )
	{
		vecButtons.push_back(GLFW_RELEASE);
	}
	
	std::copy( this->m_vecJoysticks[JoystickID].vecButtons.begin(), 
			   this->m_vecJoysticks[JoystickID].vecButtons.end(), 
			   vecButtons.begin() );
	return true;
}

bool cJoystickManager::getJoystickState( unsigned int JoystickID, std::vector<float> &vecAxes, std::vector<unsigned char> &vecButtons, bool bUpdateFirst /*=false*/ )
{
	if ( ! this->getJoystickState( JoystickID, vecAxes, bUpdateFirst ) )
	{
		return false;
	}
	if ( ! this->getJoystickState( JoystickID, vecButtons, bUpdateFirst ) )
	{
		return false;
	}
	//
	return true;
}

float cJoystickManager::getJoystickAxis( unsigned int JoystickID, unsigned int axisIndex, bool bUpdateFirst /*=false*/ )
{
	if ( ! this->m_IsJoystickPresent(JoystickID) )
	{
		// It's not there...
		return 0.0f;
	}

	if ( bUpdateFirst )
	{
		if ( ! this->Update( JoystickID ) )
		{
			// Invalid joystick ID
			return 0.0f;
		}
	}

	if ( JoystickID > this->m_vecJoysticks.size() )
	{
		// Invalid Joystick ID
		return 0.0f;
	}

	if ( axisIndex > this->m_vecJoysticks[JoystickID].vecAxes.size() )
	{
		// Invalid axis ID
		return 0.0f;
	}

	// It's all good, so get the data
	return this->m_vecJoysticks[JoystickID].vecAxes[axisIndex];
}

std::string cJoystickManager::getJoystickName(unsigned int JoystickID, bool bUpdateFirst /*=false*/ )
{
	if ( bUpdateFirst )
	{
		if ( glfwJoystickPresent(JoystickID) != GLFW_TRUE )
		{
			// Invalid joystick ID
			return "";
		}
	}

	// Joystick is present

	this->m_UpdateJoystickName( this->m_vecJoysticks[JoystickID] );

	return this->m_vecJoysticks[JoystickID].name;
}

bool cJoystickManager::m_IsJoystickPresent( unsigned int joystickID )
{
	if ( glfwJoystickPresent(joystickID) == GLFW_FALSE )
	{
		this->m_vecJoysticks[joystickID].bIsPresent = false;
		return false;
	}
	return true;
}

cJoystickManager::sJoyInfo::eJoystickType cJoystickManager::DetectJoystickType(unsigned int JoystickID)
{
	if ( this->m_IsJoystickPresent(JoystickID) )
	{
		this->m_vecJoysticks[JoystickID].DetectJoystickType();
		return this->m_vecJoysticks[JoystickID].JoystickType;
	}

	return sJoyInfo::JOYSTICK_NOT_PRESENT;
}
	
cJoystickManager::sJoyInfo::eJoystickType cJoystickManager::GetJoystickType(unsigned int JoystickID, bool bDetect /*=false*/)
{
	if ( this->m_IsJoystickPresent(JoystickID) )
	{
		if ( bDetect )
		{
			this->DetectJoystickType(JoystickID);
		}
		return this->m_vecJoysticks[JoystickID].JoystickType;
	}
	// Else;
	return sJoyInfo::JOYSTICK_NOT_PRESENT;
}

bool cJoystickManager::GetJoystickInfo(unsigned int JoystickID, cJoystickManager::sJoyInfo &joyInfo, bool bDetect /*=false*/)
{
	if ( this->m_IsJoystickPresent(JoystickID) )
	{
		if ( bDetect )
		{
			this->DetectJoystickType(JoystickID);
		}
		joyInfo = this->m_vecJoysticks[JoystickID];
		return true;
	}
	// Else;
	return false;
}

void cJoystickManager::sJoyInfo::DetectJoystickType(void)
{
	std::cout << this->name << std::endl;
	std::cout << "axes: " << this->vecAxes.size() << std::endl;
	std::cout << "buttons: " << this->vecButtons.size() << std::endl;

	// PS4?
	// "Wireless Controller
	// axes: 6
	// buttons: 18
	// Joystick not present
	if ( ( this->name == "Wireless Controller" ) &&
		 ( this->vecAxes.size() == 6 ) && 
		 ( this->vecButtons.size() == 18 ) )
	{
		this->JoystickType = sJoyInfo::PS4_Controller;
	}
		

	std::cout << this->getJoystickTypeAsString() << std::endl;

	return;
}

std::string cJoystickManager::sJoyInfo::getJoystickTypeAsString(void)
{
	switch ( this->JoystickType )
	{
	case UNKNOWN:
		return "UNKNOWN";
		break;
	case XboxOne_Controller:	// Xbox 360 Controller
		return "Xbox One Controller";
		break;
	case PS4_Controller:		// Wireless Controller
		return "PS4 Controller";
		break;
	case NINTENDO_STYLE_GAMEPAD:		// "usb gamepad           " (yes, there's a bunch of spaces...)
		return "Nintendo Style Gamepad";
		break;
	case JOYSTICK_NOT_PRESENT:		// 
		return "Joystick not present";
		break;
	}
	return "UNKNOWN";
}



