#pragma once
#include "GL/gl3w.h"
#include "GL/glfw.h"
#include <vector>

class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static unsigned LoadTexture(const char* filename);
};

