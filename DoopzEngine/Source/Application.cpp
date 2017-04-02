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

	m_window = SDL_CreateWindow("Doopz Engine v2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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

	SDL_Surface *icon;
	icon = IMG_Load("images/Icon.png");
	if (!icon) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}

	// The icon is attached to the window pointer
	SDL_SetWindowIcon(m_window, icon);

	SDL_FreeSurface(icon);

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

	if (m_input.GetKey(SDLK_w))
	{
		m_scene->m_objects[0]->Translate(glm::vec3(0.0f, 0.0f, -3.0f * deltaTime));
	}
	if (m_input.GetKey(SDLK_s))
	{
		m_scene->m_objects[0]->Translate(glm::vec3(0.0f, 0.0f, 3.0f * deltaTime));
	}
	if (m_input.GetKey(SDLK_a))
	{
		m_scene->m_objects[0]->Translate(glm::vec3(-3.0f * deltaTime, 0.0f, 0.0f));
	}
	if (m_input.GetKey(SDLK_d))
	{
		m_scene->m_objects[0]->Translate(glm::vec3(3.0f * deltaTime, 0.0f, 0.0f));
	}

	if (m_input.GetKey(SDLK_ESCAPE))
	{
		isRunning = false;
	}

	if (m_input.GetButton(1))
	{
		//std::cout << "X: " << m_input.GetMousePos()[0] << "Y: " << m_input.GetMousePos() [1] << std::endl;
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

	printf("Destroying window...");
	if (m_window != NULL)
	{
		SDL_DestroyWindow(m_window);
		m_window = NULL;
		printf("(Destroyed)\n");
	}
	else
	{
		printf("(Failed)\n");
	}
	
	printf("Destroying scene...\n--\n");
	if (m_scene != NULL)
	{
		delete m_scene;
		printf("\n--\nScene destroyed.\n");
	}
	else
	{
		printf("\n--\n(Failed)\n");
	}
	

	//Quit SDL subsystems
	SDL_Quit();
}