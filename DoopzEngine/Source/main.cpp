#include "Application.h"

bool isRunning;

int main(int argc, char* args[])
{
	
	Application *app = new Application();

	if (app->Init())
	{
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
	while (isRunning)
	{
		if (!app->Update())
		{
			isRunning = false;
		}
	}

	app->Exit();
	delete app;
	
	SDL_Delay(2000);

	return 0;
}