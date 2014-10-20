#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "GL/gl3w.h"
#include "GL/glfw.h"
#include "sb6ext.h"
#include <vmath.h>
#include <stdio.h>



class Button {
public:
	Button();
	~Button();

	void WinLog(const wchar_t *text, int n );
	GLuint LoadBMPTexture(const char * imagepath);
	void generate_texture(float * data, int width, int height);

	void Init(int winW, int winH, float x, float y, int width, int hight, const char * bitmap);
	void Render(double currentTime);
	void ShoutDown();

	void SetProjMat(int w, int h);
	void SetWinSize(int w, int h);

	bool CheckArea(int x, int y);
	void SetColor(bool mouseStatus);
	bool onMouseButton(int a, int b);
private:

	int winWidth, winHeight;
	float width, height;
	float x, y;

	int iwidth, iheight;
	int ix, iy;

	int mousePosX, mousePosY;

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
	vmath::vec4		color;

};


#endif /* __SB6EXT_H__ */