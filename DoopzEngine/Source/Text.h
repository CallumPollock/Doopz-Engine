#ifndef _TEXT_H
#define _TEXT_H

#include "GameObject.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

class Text :GameObject {

public:
	std::string m_text = "insert text here";
	void SetText(const char* _font, const char* _text);

private:

};

#endif