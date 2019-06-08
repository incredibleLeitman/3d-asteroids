#pragma once
#ifndef TextureManager_H
#define TextureManager_H

#ifdef WIN32
	#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <map>

//#include "FreeImage.h" // for .jpg
#include "tga.h" // for .tga

//Usage
//------------------------------------------------------------
//To load a texture, simply call the LoadTexture function:
//TextureManager::Inst()->LoadTexture("img\\bg.jpg", BACKGROUND_IMAGE_ID);
//This also binds the loaded texture as the current texture, so after calling it you may make any calls to glTexParameter you may need to specify the properties of the texture.

//When you are rendering, just call the TextureManager's BindImage function instead of glBindImage:
//TextureManager::Inst()->BindTexture(BACKGROUND_IMAGE_ID);
class TextureManager
{
public:
	static TextureManager* Inst();
	virtual ~TextureManager();

	void reportGLError(const char * msg);

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	bool LoadTexture(const char* filename,	//where to load the file from
		const unsigned int texID,			//arbitrary id you will reference the texture by
											//does not have to be generated with glGenTextures
		GLenum image_format = GL_RGB,		//format the image is in
		GLint internal_format = GL_RGB,		//format to store the image in
		GLint level = 0,					//mipmapping level
		GLint border = 0);					//border size

	//free the memory for a texture
	bool UnloadTexture(const unsigned int texID);

	//set the current texture
	bool BindTexture(const unsigned int texID);

	//free all texture memory
	void UnloadAllTextures();

protected:
	TextureManager();
	TextureManager(const TextureManager& tm);
	TextureManager& operator=(const TextureManager& tm);

	static TextureManager* m_inst;
	std::map<unsigned int, GLuint> m_texID;
};

#endif