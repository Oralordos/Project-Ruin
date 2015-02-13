#include "texture.h"
#include "IL/ilut.h"

namespace
{
	GLuint defaultTextureID = 0;
	units::Pixel defaultTextureWidth = 0;
	units::Pixel defaultTextureHeight = 0;
}

Texture::Texture() :
textureID(0), w(0), h(0)
{}

Texture::~Texture()
{
	destroy();
}

bool Texture::initialize(std::string filename)
{
	ILuint imageID = loadImage(filename);
	if (imageID != 0)
	{
		bool success = uploadToGL(imageID);
		if (!success)
		{
			// TODO Add logging code about failing to upload image to OpenGL.
			return false;
		}
	}
	else if (defaultTextureID == 0)
	{
		bool success = uploadToGL(0);
		if (success)
		{
			defaultTextureID = textureID;
			defaultTextureWidth = w;
			defaultTextureHeight = h;
		}
		else
		{
			// TODO Log failure to load default image.
			return false;
		}
	}
	else
	{
		textureID = defaultTextureID;
		w = defaultTextureWidth;
		h = defaultTextureHeight;
	}
	if (imageID != 0)
	{
		destroyImage(imageID);
	}
	return true;
}

void Texture::destroy()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
}

void Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

ILuint Texture::loadImage(std::string filename)
{
	ILuint imageName = ilGenImage();
	ilBindImage(imageName);
	ILboolean success = ilLoadImage(filename.c_str());
	if (success == IL_TRUE)
	{
		return imageName;
	}
	else
	{
		// TODO Add logging code about failing to load image.
		ilDeleteImage(imageName);
		return 0;
	}
}

bool Texture::uploadToGL(ILuint imageID)
{
	ilBindImage(imageID);
	ILboolean success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	if (success == IL_TRUE)
	{
		w = ilGetInteger(IL_IMAGE_WIDTH);
		h = ilGetInteger(IL_IMAGE_HEIGHT);
		ILubyte *pixels = ilGetData();
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		return true;
	}
	else
	{
		// TODO Add logging code about failing to convert image to proper format.
		return false;
	}
}

void Texture::destroyImage(ILuint imageID)
{
	ilBindImage(0);
	ilDeleteImage(imageID);
}