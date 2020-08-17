#ifndef _cBasicTextureManager_HG_
#define _cBasicTextureManager_HG_

#include <string>
#include <map>
#include "CTextureFromBMP.h"
#include "../globalOpenGLStuff.h"		// For GLuint, etc.

class cBasicTextureManager
{
public:
	bool Create2DTextureFromBMPFile( std::string textureFileName, bool bGenerateMIPMap, bool bUse_glTexImage2D_instead_of_glTexStorage2D = false );

	// Picks a random texture from the textures loaded
	std::string PickRandomTexture(void);

	bool CreateCubeTextureFromBMPFiles( std::string cubeMapName, 
		                                std::string posX_fileName, std::string negX_fileName, 
		                                std::string posY_fileName, std::string negY_fileName, 
										std::string posZ_fileName, std::string negZ_fileName, 
										bool bIsSeamless, std::string &errorString, 
									    bool bUse_glTexImage2D_instead_of_glTexStorage2D = false );


	// returns 0 on error
	GLuint getTextureIDFromName( std::string textureFileName );

	void SetBasePath(std::string basepath);

	// Added August 3, 2020
	std::string getLastError(void);

private:
	std::string m_basePath;
	std::string m_lastError;
	void m_appendErrorString( std::string nextErrorText );
	void m_appendErrorStringLine( std::string nextErrorTextLine );

	std::map< std::string, CTextureFromBMP* > m_map_TexNameToTexture;


};

#endif
