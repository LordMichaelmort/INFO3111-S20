#ifndef _cJoystickManager_HG_
#define _cJoystickManager_HG_

#include <vector>
#include <string>

class cJoystickManager
{
public:
	cJoystickManager();

	// Goes through all the joysticks, getting the ID, name, etc.
	// Can be called any time
	void InitOrReset(void);

	static const unsigned int JOYSTICK_INVALID_ID = UINT_MAX;


	// returns JOYSTICK_INVALID_ID if there aren't any joysticks
	unsigned int getFirstJoystickID(void);
	unsigned int getNumberOfJoysticksPresent(void);
	
	bool isJoystickButtonDown( unsigned int JoystickID, unsigned int buttonID, bool bUpdateFirst = false );
	float getJoystickAxis( unsigned int JoystickID, unsigned int axisIndex, bool bUpdateFirst = false );
	std::string getJoystickName(unsigned int JoystickID, bool bUpdateFirst = false);


	// These only get information about axes and buttons
	void Update(void);						// Updates all joysticks present
	// These return false if that joystick isn't present
	bool Update( unsigned int JoystickID );	
	bool getJoystickState( unsigned int JoystickID, std::vector<float> &vecAxes, bool bUpdateFirst = false );
	bool getJoystickState( unsigned int JoystickID, std::vector<unsigned char> &vecButtons, bool bUpdateFirst = false );
	bool getJoystickState( unsigned int JoystickID, std::vector<float> &vecAxes, std::vector<unsigned char> &vecButtons, bool bUpdateFirst = false );


	//
//private:


	bool m_IsJoystickPresent( unsigned int joystickID );

	// Used inside manager to hold joystick info
	struct sJoyInfo
	{
		enum eJoystickType
		{
			UNKNOWN,
			XboxOne_Controller,	// Xbox 360 Controller
			PS4_Controller,		// Wireless Controller
			NINTENDO_STYLE_GAMEPAD,		// "usb gamepad           " (yes, there's a bunch of spaces...)

			JOYSTICK_NOT_PRESENT
		};

		sJoyInfo() : 
			bIsPresent(false), 
			ID(0), 
			JoystickType(sJoyInfo::JOYSTICK_NOT_PRESENT) {};
		bool bIsPresent;
		std::string name;
		unsigned int ID;
		std::vector<float> vecAxes;
		std::vector<unsigned char> vecButtons;
		void DetectJoystickType(void);
		eJoystickType JoystickType;
		std::string getJoystickTypeAsString(void);
	};
public:	
	sJoyInfo::eJoystickType DetectJoystickType(unsigned int JoystickID);
	sJoyInfo::eJoystickType GetJoystickType(unsigned int JoystickID, bool bDetect = false);
	bool GetJoystickInfo(unsigned int JoystickID, cJoystickManager::sJoyInfo& joyInfo, bool bDetect =false);


private:
	std::vector<sJoyInfo> m_vecJoysticks;

	// NOTE: These assume the joystickID (Joystick.ID) is present
	// (The DON'T check to see if the joystick ID is OK)
	void m_UpdateJoystickAxes( sJoyInfo &Joystick );
	void m_UpdateJoystickButtons( sJoyInfo &Joystick );
	void m_UpdateJoystickName( sJoyInfo &Joystick );
};

#endif
