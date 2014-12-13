#ifndef _CFONT_H_
#define _CFONT_H_

#include <vector>


class Font
{
protected:

public:
	float w,h;
	float glyphW, glyphH;
	unsigned int m_texture;

public:

	Font();
	Font(int texture, float texSize, float glyphSize)
	{
		w = h = texSize;
		glyphH = glyphW = glyphSize;
		m_texture = texture;
	}
};


#endif // _CMODEL_H_