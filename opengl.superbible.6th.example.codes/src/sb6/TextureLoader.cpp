#include "TextureLoader.h"
//#include "lodepng.h"
//#include "WindowGL.h"


TextureLoader::TextureLoader(void)
{
}


TextureLoader::~TextureLoader(void)
{
}

int texture;

unsigned int TextureLoader::LoadTexture(const char* filename)
{
	std::vector<unsigned char> image;
  	unsigned width, height;
    /*	unsigned error = lodepng::decode(image, width, height, filename);

  	if(error != 0)
  	{
    	printf("[LoadTexture] unable to load texture [%s]. Reason: %s\n", filename, lodepng_error_text(error));
    	return -1;
  	}*/

  	unsigned int newTexture;  
  	glEnable(GL_TEXTURE_2D);
  	glGenTextures(1, &newTexture);
  	glBindTexture(GL_TEXTURE_2D, newTexture);

  	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // what happens if we use GL_NEAREST ?
  	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	//glDisable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return newTexture;
}