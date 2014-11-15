#include "../../include/label.h"

Label::Label() : Button()
{
}


Label::~Label()
{
	Button::ShoutDown();
}

//void Label::DrawASCII(Font* font, int x, int y, char symbol)
//{
//	if (!font) return;
//	symbol -= 32;
//	float texX = (symbol % 16) / 16.0f;
//	float texY = ((symbol / 16)) / 16.f;
//	float step = 1.0f / 16.0f;
//
//	/*
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glUseProgram(program);
//	proj_matrix = vmath::perspective(50.0f, aspect, 0.1f, 1000.0f);
//	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
//	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
//	glUniform4fv(btnColor, 1, color);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	*/
//
//	View2d();
//	glBindTexture(GL_TEXTURE_2D, font->m_texture);
//	glPushMatrix();
//	glTranslatef(x, y, 0.0f);
//
//	glBegin(GL_TRIANGLE_STRIP);
//
//	glTexCoord2d(texX, texY + step);
//	glVertex2f(0, 0 + font->glyphH);
//
//	glTexCoord2d(texX, texY);
//	glVertex2f(0, 0);
//
//	glTexCoord2d(texX + step, texY + step);
//	glVertex2f(0 + font->glyphW, 0 + font->glyphH);
//
//	glTexCoord2d(texX + step, texY);
//	glVertex2f(0 + font->glyphW, 0);
//
//	glEnd();
//
//	glPopMatrix();
//	View3d();
//}
//
//void Label::DrawText(Font* font, int x, int y, const char *fmt, ...)
//{
//	if (!font) return;
//	va_list args;
//	va_start(args, fmt);
//
//	while (*fmt != '\0')
//	{
//		if (*fmt == '%')
//		{
//			fmt++;
//			if (*fmt == 'd')
//			{
//				int i = va_arg(args, int);
//				DrawASCII(font, x, y, (char)i + 48);
//			}
//		}
//		else
//		{
//			DrawASCII(font, x, y, *fmt);
//		}
//		++fmt;
//		x += font->glyphW;
//	}
//	va_end(args);
//}