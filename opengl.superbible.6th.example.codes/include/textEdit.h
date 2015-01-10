#ifndef __TextEdit_H__
#define __TextEdit_H__

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
#include <string>
#include <sstream>
#include <stdlib.h>

#include "label.h"
#include "button.h"

class TextEdit {
public:
	TextEdit();
	~TextEdit();

	void Init(int winW, int winH, float x, float y, int width, int hight, const char * bitmap, std::string labeltext);
	void Render(double currentTime);
	void ShoutDown();

	bool CheckArea(int x, int y);
	void CheckKey(int key, int action);
	bool onMouseButton(int a, int b);
	
	bool insideArea;
	bool currentState;

	int clickCounter;
	int previousTime;

	std::string getCurrentText();
	void setCurrentText(std::string text);

private:

	Label* myLabel;
	Button* myButton;

	std::string currentText;
	std::string textToDisplay;
};


#endif /* __TextEdit_H__ */