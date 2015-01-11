#include "../../include/dropDownList.h"


DropDownList::DropDownList():
	winWidth(0),
	winHeight(0),
	iwidth(0),
	iheight(0),
	ix(0),
	iy(0),
	mousePosX(0),
	mousePosY(0),
	width(0),
	height(0),
	x(0),
	y(0),
	program(0),
	vao(0),
	positionBuffer(0),
	texCoordBuffer(0),
	indexBuffer(0),
	mv_location(0),
	proj_location(0),
	btnColor(0),
	aspect(0),
	proj_matrix(0),
	tex_object(0),
	TexturePath(0),
	numOfElements(0),
	currentElement(0),
	activeElement(0),
	offsetValue(0),
	insideWholeArea(false),
	insideBtnArea(false),
	btnClicked(false),
	color(0)
{

}
DropDownList::~DropDownList() {
	ShoutDown();
}

void DropDownList::ShoutDown() {

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(program);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &texCoordBuffer);
}

void DropDownList::WinLog(const wchar_t *text, int n = 0) {
	wchar_t buf[1024];
	_snwprintf_s(buf, 1024, _TRUNCATE, L"%s %d\n", text, n);
	OutputDebugString(buf);
}
int DropDownList::GetCurrentElement() {
	return this->currentElement;
}

void DropDownList::SetCurrentElement(int index)
{
	this->currentElement = index;
}

void DropDownList::SetProjMat(int w, int h) {

	aspect = (float)w / (float)h;
}
void DropDownList::SetWinSize(int w, int h) {
	winWidth = w;
	winHeight = h;

	//Normalizacja potrzebna w przeliczaniu wspó³rzednych
	x /= winWidth;
	y /= winHeight;

	width /= winWidth;
	height /= winHeight;
}
bool DropDownList::CheckArea(int posX, int posY) {
	
	mousePosX = posX;
	mousePosY = posY;

	if (posX > ix && posX<(ix + iwidth)) {
		if (posY>iy) {

			if (posY < (iy + iheight)) {
				insideBtnArea = TRUE;
				activeElement = 0;
			} else {
				if (insideBtnArea) {
					insideWholeArea = TRUE;
					activeElement = 0;
				}
			}

			if (insideWholeArea) {

				for (int i = 0; i < numOfElements; i++) {
					if (posY <= (iy + ((i+1) * iheight)) && posY >(iy + (i * iheight))) {
						insideWholeArea = TRUE;
						activeElement = i;
					}
				}

				if (posY > (iy + (numOfElements * iheight))) {
					insideWholeArea = FALSE;
					insideBtnArea = FALSE;
					//activeElement = -1;
				}
			}


		}
		else {
			insideWholeArea = FALSE;
			insideBtnArea = FALSE;
			//activeElement = -1;
		}
	}
	else {
		insideWholeArea = FALSE;
		insideBtnArea = FALSE;
		//activeElement = -1;
	}


	SetColor(insideWholeArea);

	return insideWholeArea;
}
void DropDownList::SetColor(bool mouseOver) {

	if (mouseOver) {
		//color = vmath::vec4(0.6f, 0.6f, 0.6f, 0.0f);
		//color = vmath::vec4(a, a, a, 0.0f);
	} else {
		//color = vmath::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	}
}
bool DropDownList::onMouseButton(int button, int action) {
	if (CheckArea(mousePosX, mousePosY) && action==1) {
		//color = vmath::vec4(0.6f, 0.1f, 0.5f, 1.0f);
		currentElement = activeElement;
		btnClicked = true;
	} else {
		btnClicked = false;
	}

	return btnClicked;
}

void DropDownList::generate_texture(float * data, int width, int height) {
	int x, y;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			data[(y * width + x) * 2 + 0] =  0.5f;
			data[(y * width + x) * 2 + 1] =  0.5f;
			//data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
			//data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}


static const GLfloat vertex_positions2[] =
{
	-0.5f, 0.5f, 0,
	-0.5f, -0.5f, 0,
	0.5f, -0.5f, 0,
	0.5f, -0.5f, 0,
	0.5f, 0.5f, 0,
	-0.5f, 0.5f, 0,
};

static GLfloat tex_coords_pos2[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

//static const GLushort vertex_indices[] =
//{
//	0, 1, 2,
//	2, 4, 0
//};

void DropDownList::Init(int winW, int winH, float posX, float posY, int btnWidth, int btnHeight, const char * bitmap, int numOfElementsInList) {

	winWidth = winW;
	winHeight = winH;

	ix = posX;
	iy = posY;
	iwidth = btnWidth;
	iheight = btnHeight;

	x = posX;
	y = posY;
	width = btnWidth;
	height = btnHeight;
	TexturePath = bitmap;

	x /= winWidth;
	y /= winHeight;

	width /= winWidth;
	height /= winHeight;


	numOfElements = numOfElementsInList;

	static const char * vs_source[] =
	{
		"#version 410 core                                                  \n"
		"                                                                   \n"
		"in vec4 position2;										            \n"
		"in vec2 texPos;													     \n"
		//"layout (location = 14) in vec2 tc;                                  \n"
		"out VS_OUT                                                         \n"
		"{                                                                  \n"
		"    vec4 color;													\n"
		"	 vec2 tc;														\n"
		"} vs_out;                                                          \n"
		"                                                                   \n"
		"uniform mat4 mv_matrix;                                            \n"
		"uniform mat4 proj_matrix;                                          \n"
		"uniform vec4 btnColor;			                                    \n"
		"                                                                   \n"
		"const vec2[6] texPos2 = vec2[6](vec2(0.0f, 1.0f),                  \n"
		"                                 vec2(0.0f, 0.0f),                 \n"
		"                                 vec2(1.0f, 0.0f),                 \n"
		"                                 vec2(1.0f, 0.0f),                 \n"
		"                                 vec2(1.0f, 1.0f),                 \n"
		"                                 vec2(0.0f, 1.0f));                \n"
		"void main(void)                                                    \n"
		"{                                                                  \n"
		"    gl_Position =  mv_matrix*position2;							\n"
		"    vs_out.tc = texPos.xy;							\n"
		"    vs_out.color = btnColor;										\n"
		"}                                                                  \n"
	};
	
	static const char * fs_source[] =
	{
		"#version 410 core                                                  \n"
		"                                                                   \n"
		"out vec4 color;                                                    \n"
		//"layout (binding = 10) uniform sampler2D tex_object;                \n"
		"uniform sampler2D sss;												\n"
		"in VS_OUT                                                          \n"
		"{                                                                  \n"
		"    vec4 color;													\n"
		"    vec2 tc;														\n"
		"} fs_in;                                                           \n"
		"                                                                   \n"
		"void main(void)                                                    \n"
		"{                                                                  \n"
		"    color = texture(sss, fs_in.tc )*fs_in.color;	\n"
		//"    color = texture(sss, (gl_FragCoord.xy)/ textureSize(sss, 0) )*fs_in.color;	\n"
		//"    color = texture(sss, (vec2(30.0,1.0)+gl_FragCoord.xy) / textureSize(sss, 0));	\n"
		//"    color = fs_in.color;									        \n"
		"}                                                                  \n"
	};


	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	mv_location = glGetUniformLocation(program, "mv_matrix");
	proj_location = glGetUniformLocation(program, "proj_matrix");
	btnColor = glGetUniformLocation(program, "btnColor");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vertecies
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions2), vertex_positions2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	////texture vertecies
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords_pos2), tex_coords_pos2, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	LoadBMPTexture(bitmap);
	glBindVertexArray(0);
}
	


GLuint DropDownList::LoadBMPTexture(const char * imagepath) {


	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	

	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file) {
		printf("Image could not be opened\n");
		WinLog(L"Image could not be opened");
		return 0;
	}
	
	// The first thing in the file is a 54-bytes header. It contains information such as “Is this file really a BMP file?”, the size of the image, the number of bits per pixel, etc. So let’s read this header :
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		WinLog(L"Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		WinLog(L"Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	fileWidth = *(int*)&(header[0x12]);
	fileHeight = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = fileWidth*fileHeight * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	textureData = new unsigned char[imageSize];
	//float * data;

	// Read the actual data from the file into the buffer
	fread(textureData, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	// Define some data to upload into the texture
	//data = new float[fileWidth * fileHeight * 4];

	// generate_texture() is a function that fills memory with image data
	//generate_texture(data, fileWidth, fileHeight);

	// Create one OpenGL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fileWidth, fileHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16, fileWidth, fileHeight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, fileWidth, fileHeight, GL_BGR, GL_UNSIGNED_BYTE, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
}

void DropDownList::ChangeToElement(int index) {

	tex_coords_pos2[1] = 1.0f;
	tex_coords_pos2[3] = 1.0f;
	tex_coords_pos2[5] = 1.0f;
	tex_coords_pos2[7] = 1.0f;
	tex_coords_pos2[9] = 1.0f;
	tex_coords_pos2[11] = 1.0f;

	offsetValue = float(1) / (float)numOfElements;

	tex_coords_pos2[3] -= offsetValue;
	tex_coords_pos2[5] -= offsetValue;
	tex_coords_pos2[7] -= offsetValue;

	offsetValue = float(index) / (float)numOfElements;

	tex_coords_pos2[1] -= offsetValue;
	tex_coords_pos2[3] -= offsetValue;
	tex_coords_pos2[5] -= offsetValue;
	tex_coords_pos2[7] -= offsetValue;
	tex_coords_pos2[9] -= offsetValue;
	tex_coords_pos2[11] -= offsetValue;
}
void DropDownList::Render(double currentTime) {

	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glUseProgram(program);

	proj_matrix = vmath::perspective(50.0f, aspect, 0.1f, 1000.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
	
	vmath::mat4 m1, m2, m3;

	m1 = vmath::mat4::identity();	
	m2 = vmath::translate(2*(x+width/2)-1, 1-2*(y+height/2), 0.0f);
	m3 = vmath::scale(2 * width, 2 * height, 0.0f);

	//WinLog(L"dropDownlist render");

	if (insideWholeArea || insideBtnArea) {
		//mouse over
		tex_coords_pos2[1] = 1.0f;
		tex_coords_pos2[3] = 0.0f;
		tex_coords_pos2[5] = 0.0f;
		tex_coords_pos2[7] = 0.0f;
		tex_coords_pos2[9] = 1.0f;
		tex_coords_pos2[11] = 1.0f;

		m2 = vmath::translate(2 * (x + width / 2) - 1, (1 - 2 * (y + height / 2)) - ((numOfElements-1)*height), 0.0f);
		m3 = vmath::scale(2 * width, numOfElements*(2 * height), 0.0f);
		color = vmath::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	} else {
		//mouse out of area
		m2 = vmath::translate(2 * (x + width / 2) - 1, 1 - 2 * (y + height / 2), 0.0f);
		m3 = vmath::scale(2 * width, 2 * height, 0.0f);
		color = vmath::vec4(1.0f, 1.0f, 1.0f, 0.0f);
		ChangeToElement(currentElement);
	}
		
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords_pos2), tex_coords_pos2, GL_STATIC_DRAW);
	
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, m1*m2*m3);
	glUniform4fv(btnColor, 1, color);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (insideWholeArea || insideBtnArea) {


		m2 = vmath::translate(2 * (x + width / 2) - 1, (1 - 2 * (y + height / 2)) - ((currentElement)* 2 * height), 0.0f);
		m3 = vmath::scale(2 * width, 2 * height, 0.0f);
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, m1*m2*m3);

		ChangeToElement(currentElement);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords_pos2), tex_coords_pos2, GL_STATIC_DRAW);
		
		color = vmath::vec4(0.2f, 0.2f, 0.8f, 0.0f);
		glUniform4fv(btnColor, 1, color);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		m2 = vmath::translate(2 * (x + width / 2) - 1, (1 - 2 * (y + height / 2)) - ((activeElement) * 2*height), 0.0f);
		m3 = vmath::scale(2 * width, 2 * height, 0.0f);
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, m1*m2*m3);

		ChangeToElement(activeElement);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords_pos2), tex_coords_pos2, GL_STATIC_DRAW);
		
		if (btnClicked) {
			color = vmath::vec4(0.2f, 0.8f, 0.3f, 0.0f);
		} else {
			color = vmath::vec4(0.5f, 0.5f, 0.5, 0.0f);
		}


		glUniform4fv(btnColor, 1, color);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		


	}

	//This is optional drawcall
	//When using given draw calls there is memory access violation (why?):
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,0);
	//glDrawElementsInstancedBaseInstance(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, 1, 0);

}