#include "../../include/textEdit.h"


TextEdit::TextEdit():
	insideArea(false),
	currentState(false),
	activeCursor(false),
	previousTime(0),
    clickCounter(0)

{
	myLabel = new Label();
	myButton = new Button();
}
TextEdit::~TextEdit() {

}

bool TextEdit::CheckArea(int posX, int posY) {

	return myButton->CheckArea(posX, posY);
}

void TextEdit::ShoutDown() {
	myLabel->ShoutDown();
	myButton->ShoutDown();
}


bool TextEdit::onMouseButton(int button, int action) {

	//myLabel->onMouseButton(button, action);
	
	currentState= myButton->onMouseButton(button, action);


	if (clickCounter == 1 && action == 1) {
		
		clickCounter++;
	}

	if (currentState == true && clickCounter == 0) {
		clickCounter++;
	}

	if (clickCounter == 2) {
		myButton->ChangeColor(0.2, 0.1, 0.1, 1.0);
		clickCounter = 0;
	}

	return TRUE;
}

void TextEdit::CheckKey(int key, int action) {


	if (currentText.length() > 0) {
		if (currentText.back() == '/') {
			currentText.pop_back();
		}
	}

	if (action) {

		switch (key) {
		case 294://Enter
			if (clickCounter == 1) {
				myButton->ChangeColor(0.2, 0.1, 0.1, 1.0);
				clickCounter++;
			}
			break;

		case 295://Backspace
			currentText.pop_back();
			break;
				
		default:
				currentText += (char)key;
			break;
		}

		
		if (clickCounter == 1) {
			myLabel->ChangeText(currentText);
		}

	}
}

void TextEdit::Init(int winW, int winH, float posX, float posY, int width, int hight, const char * bitmap, std::string textToDraw) {

	myLabel->Init(winW, winH, posX, posY, hight, textToDraw);
	myButton->Init(winW, winH, posX, posY, width, hight, bitmap);
}


void TextEdit::Render(double currentTime) {

	myButton->Render(currentTime);
	
	if (clickCounter == 1) {
		if (int(currentTime) != previousTime) {
			if (previousTime % 2 == 0) {
				currentText += '/';
			} else {
				if (currentText.length() > 0) {
					if (currentText.back() == '/') {
						currentText.pop_back();
					}
				}	
			}
		}
	}

	myLabel->ChangeText(currentText);
	myLabel->Render(currentTime);

	previousTime = int(currentTime);
}