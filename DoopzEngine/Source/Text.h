#ifndef _TEXT_H
#define _TEXT_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

class Text {

public:
	Text();
	std::string m_text = "insert text here";
	SDL_Surface* SetText(const char* _font, const char* _text);


private:

};

#endif