#ifndef __Label_H__
#define __Label_H__

#include "GL/gl3w.h"
#include "GL/glfw.h"
#include "sb6ext.h"
#include "lodepng.h"

#include <vmath.h>
#include <stdio.h>
#include <fstream>

#include <iostream>     // std::cout
#include <algorithm>    // std::fill
#include <vector>       // std::vector


class Label {
public:
	Label();
	~Label();

	void Init(int winW, int winH, float x, float y, int fontsize, const char * labeltext);
	void Render(double currentTime);
	void ShoutDown();

	bool CheckArea(int x, int y);
	bool onMouseButton(int a, int b);
	void ChangeTexCoord(int index);
	void SetTexCoordASCII(char symbol,float);
	
private:
	void WinLog(const wchar_t *text, int n);
	GLuint LoadBMPTexture(const char * imagepath);
	unsigned int LoadPNGTexture();
	void generate_texture(unsigned char * data, int width, int height);

	void SetProjMat(int w, int h);
	void SetWinSize(int w, int h);

	void SetColor(bool mouseStatus);

	int winWidth, winHeight;
	float width, height;
	float x, y;

	int iwidth, iheight;
	int ix, iy;

	int mousePosX, mousePosY;

	const char * labelText;

	unsigned char * textureData;
	unsigned int fileWidth, fileHeight;
	std::vector<unsigned char> image;

	GLuint          program;

	GLuint          vao;
	GLuint          positionBuffer;
	GLuint			texCoordBuffer;
	GLuint          indexBuffer;

	GLint           mv_location;
	GLint           proj_location;

	GLint           btnColor;
	GLuint			tex_object;
	GLuint			textureID;

	float           aspect;
	vmath::mat4     proj_matrix;
	vmath::vec4		textColor;

};


#endif /* __Label_H__ */