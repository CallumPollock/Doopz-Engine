#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <SDL_image.h>

#include "Scene.h"
#include "Input.h"


class Application {

public:
	bool Init();
	void Exit();
	bool Update();
	

private:

	Input m_input;

	bool InitGL();

	bool isRunning = true;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	unsigned int lastTime;

	Scene* m_scene;
	
	SDL_Window* m_window = NULL;

	SDL_Surface* m_screen = NULL;

};

#endif