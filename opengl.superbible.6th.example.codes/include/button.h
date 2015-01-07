#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "GL/gl3w.h"
#include "GL/glfw.h"
#include "sb6ext.h"
#include <vmath.h>
#include <stdio.h>
#include <fstream>



class Button {
public:
	Button();
	~Button();

	void Init(int winW, int winH, float x, float y, int width, int hight, const char * bitmap);
	void Render(double currentTime);
	void ShoutDown();

	bool CheckArea(int x, int y);
	bool onMouseButton(int a, int b);
	void SetColor(bool mouseStatus);
	void ChangeColor(float r, float g, float b, float a);

private:
	void WinLog(const wchar_t *text, int n );
	void generate_texture(float * data, int width, int height);

	void SetProjMat(int w, int h);
	void SetWinSize(int w, int h);

	int winWidth, winHeight;
	float width, height;
	float x, y;

	const char * TexturePath;
	unsigned char * textureData;
	unsigned int fileWidth, fileHeight;

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

protected:
	int mousePosX, mousePosY;
	int ix, iy;
	int iwidth, iheight;
	vmath::vec4 color;

	GLuint LoadBMPTexture(const char * imagepath);
};


#endif /* __BUTTON_H__ */