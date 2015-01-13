#ifndef __DROPDOWNLIST_H__
#define __DROPDOWNLIST_H__


#include "GL/gl3w.h"
#include "GL/glfw.h"
#include "sb6ext.h"
#include <vmath.h>
#include <stdio.h>
#include <fstream>



class DropDownList {

public:

	DropDownList();
	~DropDownList();

	void Init(int winW, int winH, float x, float y, int width, int hight, const char * bitmap,int numOfElementsInList);
	void Render(double currentTime);
	void UpdateSize(int winW, int winH);
	void ShoutDown();

	bool CheckArea(int x, int y);
	bool onMouseButton(int a, int b);

	int GetCurrentElement();
	void ChangeToElement(int index);
	int activeElement;
	void SetCurrentElement(int index);
private:

	void WinLog(const wchar_t *text, int n);
	GLuint LoadBMPTexture(const char * imagepath);
	void generate_texture(float * data, int width, int height);

	void SetProjMat(int w, int h);
	void SetWinSize(int w, int h);

	void SetColor(bool mouseStatus);
	



	int winWidth, winHeight;
	float width, height;
	float x, y;

	int iwidth, iheight;
	int ix, iy;

	int mousePosX, mousePosY;

	int numOfElements;
	
	int currentElement;
	float offsetValue;
	bool insideWholeArea;
	bool insideBtnArea;
	bool btnClicked;

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


#endif /* __DROPDOWNLIST_H__ */