#include "Application.h"


bool Application::Init()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL failed to initialise! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_window = SDL_CreateWindow("Game Engine :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (m_window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Get window surface
		m_screen = SDL_GetWindowSurface(m_window);
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(m_window, -1, 0);

	SDL_GLContext glcontext = SDL_GL_CreateContext(m_window);

	if (!InitGL())
	{
		return false;
	}

	//create gameobject
	m_scene = new Scene();
	m_scene->SetScreen(m_screen);


	return true;
}

bool Application::InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("GLEW failed to initialise! GLEW Error: %s\n", glewGetErrorString(err));
		return false;
	}
	std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

bool Application::Update()
{
	unsigned int current = SDL_GetTicks();
	float deltaTime = (float)(current - lastTime) / 1000.0f;
	lastTime = current;

	float deltaX, deltaY, deltaZ;

	//Input check

	m_input.Update();

	if (m_input.GetKey(SDLK_RIGHT))
	{
		m_scene->ChangeCameraAngleY(4 * deltaTime);
	}
	if (m_input.GetKey(SDLK_LEFT))
	{
		m_scene->ChangeCameraAngleY(-4 * deltaTime);
	}
	if (m_input.GetKey(SDLK_UP))
	{
		m_scene->ChangeCameraAngleX(4 * deltaTime);
	}
	if (m_input.GetKey(SDLK_DOWN))
	{
		m_scene->ChangeCameraAngleX(-4 * deltaTime);
	}
	if (m_input.GetKey(SDLK_w))
	{
		m_scene->m_gameObjects[0]->Translate(0.0f, 10.0f * deltaTime, 0.0f);
	}
	if (m_input.GetKey(SDLK_s))
	{
		m_scene->m_gameObjects[0]->Translate(0.0f, -10.0f * deltaTime, 0.0f);
	}
	if (m_input.GetKey(SDLK_a))
	{
		m_scene->m_gameObjects[0]->Translate(-10.0f * deltaTime, 0.0f, 0.0f);
	}
	if (m_input.GetKey(SDLK_d))
	{
		m_scene->m_gameObjects[0]->Translate(10.0f * deltaTime, 0.0f, 0.0f);
	}

	if (m_input.GetKey(SDLK_ESCAPE))
	{
		isRunning = false;
	}

	if (m_input.GetButton(1))
	{
		std::cout << "X: " << m_input.GetMousePos()[0] << "Y: " << m_input.GetMousePos() [1] << std::endl;
	}

	glClearColor(0.2f, 0.8f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scene->Update(deltaTime);

	SDL_GL_SwapWindow(m_window);

	return isRunning;

}

void Application::Exit()
{

	printf("\nExiting application...\n");

	SDL_DestroyWindow(m_window);
	m_window = NULL;
	printf("Destroyed window...\n");

	SDL_FreeSurface(m_screen);
	m_screen = NULL;
	printf("Destroyed screen...\n");

	delete m_scene;
	printf("Destroyed scene...\n");

	//Quit SDL subsystems
	SDL_Quit();
}