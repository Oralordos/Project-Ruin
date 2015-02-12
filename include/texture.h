#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include "IL/il.h"
#include "SDL_opengl.h"
#include "units.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool initialize(std::string filename);
	void destroy();
	void bindTexture() const;

	inline units::Pixel getWidth() const;
	inline units::Pixel getHeight() const;
private:
	static ILuint loadImage(std::string filename);
	void uploadToGL(ILuint imageID);
	static void destroyImage(ILuint imageID);

	GLuint textureID;
	units::Pixel w;
	units::Pixel h;
};

inline units::Pixel Texture::getWidth() const
{
	return w;
}

inline units::Pixel Texture::getHeight() const
{
	return h;
}

#endif // TEXTURE_H_