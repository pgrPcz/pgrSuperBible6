#include "../../include/textEdit.h"


TextEdit::TextEdit():
	insideArea(false),
	currentState(false),
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
	
	currentState = myButton->onMouseButton(button, action);


	if (clickCounter == 1 && action == 1) {
		
		clickCounter++;
	}

	if (currentState == true && clickCounter == 0) {
		clickCounter++;
	}

	if (clickCounter == 2) {
		myButton->ChangeColor(0.8, 0.9, 0.8, 1.0);
		clickCounter = 0;
	}

	return currentState;
}

void TextEdit::CheckKey(int key, int action) {


	//if (textToDisplay.length() > 0) {
	//	if (textToDisplay.back() == '/') {
	//		textToDisplay.pop_back();
	//	}
	//}

	if (action && clickCounter) {

		switch (key) {
		case 294://Enter
				myButton->ChangeColor(0.8, 0.9, 0.8, 1.0);
				clickCounter++;
			break;

		case 295://Backspace
			if (currentText.length() > 0) {
				currentText.pop_back();
			}
			break;
				
		default:
			currentText += (char)key;
			break;

		}
		myLabel->ChangeText(currentText);
		textToDisplay = currentText;
	}	
}

std::string TextEdit::getCurrentText() {
	return currentText;
}

void TextEdit::setCurrentText(std::string text) {
	currentText = text;
	textToDisplay = currentText;	
}

void TextEdit::UpdateSize(int winW, int winH) {
	myLabel->UpdateSize(winW, winH);
	myButton->UpdateSize(winW, winH);
}

void TextEdit::Init(int winW, int winH, float posX, float posY, int width, int hight, const char * bitmap, std::string textToDraw) {

	textToDisplay = textToDraw;
	currentText = textToDraw;
	myLabel->Init(winW, winH, posX, posY, hight, textToDraw);
	myButton->Init(winW, winH, posX, posY, width, hight, bitmap);
}


void TextEdit::Render(double currentTime) {

	myButton->Render(currentTime);
	
	if (clickCounter == 1) {
		if (int(currentTime) != previousTime) {

			if (textToDisplay.length() > 0) {
				if (textToDisplay.back() == '/') {
					textToDisplay.pop_back();
				} else {
					textToDisplay += '/';
				}
			}
			if (textToDisplay.length() == 0) {
					textToDisplay += '/';
				}
			
		}
	}

	myLabel->ChangeText(textToDisplay);
	myLabel->Render(currentTime);

	previousTime = int(currentTime);
}