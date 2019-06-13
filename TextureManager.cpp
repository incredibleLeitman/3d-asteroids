#include "TextureManager.h"

TextureManager* TextureManager::m_inst(0);

TextureManager* TextureManager::Inst()
{
	if (!m_inst)
		m_inst = new TextureManager();

	return m_inst;
}

TextureManager::TextureManager()
{
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise(); // call this ONL-Y when linking with FreeImage as a static library
#endif
}

TextureManager::~TextureManager()
{
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise(); // call this ONLY when linking with FreeImage as a static library
#endif

	UnloadAllTextures();
	m_inst = 0;
}

void TextureManager::reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
	}
	return;
}

bool TextureManager::LoadTexture(const char* filename, const unsigned int texID, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	/* TODO: maybe use FREEIMAGE_LIB to be able to load .jpg files?
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	//if this texture ID is in use, unload the current texture
	if (m_texID.find(texID) != m_texID.end())
		glDeleteTextures(1, &(m_texID[texID]));

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//store the texture ID mapping
	m_texID[texID] = gl_texID;
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);*/

	tgaInfo *info = 0;
	info = tgaLoad((char *)filename);
	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);
		return false;
	}

	//if this texture ID is in use, unload the current texture
	if (m_texID.find(texID) != m_texID.end())
		glDeleteTextures(1, &(m_texID[texID]));

	GLuint gl_texID;
	int mode = info->pixelDepth / 8; // will be 3 for rgb, 4 for rgba
	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	GLsizei w = info->width;
	GLsizei h = info->height;

	glGenTextures(1, &gl_texID); //generate an OpenGL texture ID for this texture
	m_texID[texID] = gl_texID; //store the texture ID mapping
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // should be default
	glBindTexture(GL_TEXTURE_2D, gl_texID); //bind to the new texture ID

	// additional params:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLint clamp_mode = GL_REPEAT; // or GL_CLAMP, GL_CLAMP_TO_EDGE in newer versions
	clamp_mode = GL_CLAMP;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp_mode); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp_mode);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	reportGLError("before uploading texture");
	//store the texture data for OpenGL use
	//glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, border, image_format, GL_UNSIGNED_BYTE, bits);
	glTexImage2D(GL_TEXTURE_2D, level, format, w, h, 0, format, GL_UNSIGNED_BYTE, info->imageData);
	reportGLError("after uploading texture");

	tgaDestroy(info);
	return true;
}

bool TextureManager::UnloadTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if (m_texID.find(texID) != m_texID.end())
	{
		glDeleteTextures(1, &(m_texID[texID]));
		m_texID.erase(texID);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	if (m_texID.find(texID) != m_texID.end()) //if this texture ID mapped, bind it's texture as current
	{
		glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	}
	else //otherwise, binding failed
	{
		fprintf(stderr, "error binding texture image for id: %d\n", texID);
		result = false;
	}
	return result;
}

void TextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<unsigned int, GLuint>::iterator i = m_texID.begin();

	//Unload the textures untill the end of the texture map is found
	while (i != m_texID.end())
		UnloadTexture(i->first);

	//clear the texture map
	m_texID.clear();
}