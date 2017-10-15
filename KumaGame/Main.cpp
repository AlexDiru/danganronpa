#pragma comment( linker, "/subsystem:windows" )
//#pragma comment( linker, "/subsystem:console" )

#include <string>
#include <iostream>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#define NOMINMAX 
#define STRICT 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "FileIO.h"

#include "SDLMaster.h"
#include "Image.h"
#include "Font.h"
#include "GLCharacter.h"

#include "Lexer.h"
#include "Parser.h"

using namespace KumaGame;

bool initialise();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void RunGame();

int sdlMain()
{
	//Run the compiler before setting SDL up 
	std::string source = KumaCore::FileIO::loadFile(KumaCore::FileIO::getScripts("test.txt"));

	KumaCompiler::Lexer lexer{};
	KumaCompiler::LexerFlags flags{};
	flags.ignoreWhitespaceTokens = true;

	lexer.setLexerFlags(flags);

	lexer.tokenise(source);

	std::cout << "Source: " << std::endl;
	std::cout << source.c_str() << std::endl;
	std::cout << std::endl;

	for (auto const &token : lexer.getTokens())
		std::cout << token.toString() << std::endl;

	std::cin.get();

	KumaCompiler::Parser parser(lexer.getTokens());
	parser.parse();

	// Now let's grab a scene and display it
	auto parsedScene = parser.getDatabase().lookupScene("Outside");

	if (parsedScene != nullptr)
		while (parsedScene->hasActionsLeft())
		{
			parsedScene->show();
			std::cin.get();
		}


	if (!initialise())
		return -1;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(SDLMaster::get().mainWindow);

	// Initialised GL stuff from compiled stuff
	std::vector<GLCharacter> characters;
	auto charactersToLoad = parsedScene->getCharactersInvolvedInScene();
	for (const KumaCore::Character* characterToLoad : charactersToLoad)
		characters.push_back(GLCharacter(*characterToLoad));

	// RUN GAME BEGIN
	bool loop = true;

	Font font("../content/Fonts/Raleway/Raleway-Regular.ttf", 24);

	while (loop)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);


		//Render texture to screen
		characters[rand() % characters.size()].render("");
		font.setColour({ 0, 0,0,255 });
		font.render("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 0, 0);

		//Update screen
		SDL_RenderPresent(KumaGame::SDLMaster::get().renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;
				case SDLK_r:
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(SDLMaster::get().mainWindow);
					break;
				case SDLK_g:
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(SDLMaster::get().mainWindow);
					break;
				case SDLK_b:
					// Cover with blue and update
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(SDLMaster::get().mainWindow);
					break;
				default:
					break;
				}
			}
		}
	}
	// RUN GAME END

	SDL_GL_DeleteContext(SDLMaster::get().mainContext);
	SDL_DestroyWindow(SDLMaster::get().mainWindow);
	SDL_Quit();

	return 0;
}


bool initialise()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	SDLMaster::get().mainWindowWidth = 1366;
	SDLMaster::get().mainWindowHeight = 768;
	SDLMaster::get().mainWindow = SDL_CreateWindow("Kuma Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDLMaster::get().mainWindowWidth, SDLMaster::get().mainWindowHeight, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!SDLMaster::get().mainWindow)
	{
		std::cout << "Unable to create window\n";
		CheckSDLError(__LINE__);
		return false;
	}

	SDLMaster::get().mainContext = SDL_GL_CreateContext(SDLMaster::get().mainWindow);
	SDLMaster::get().screenSurface = SDL_GetWindowSurface(SDLMaster::get().mainWindow);

	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	// Init GLEW
	// Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif

	TTF_Init();

	KumaGame::SDLMaster::get().renderer = SDL_CreateRenderer(SDLMaster::get().mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (KumaGame::SDLMaster::get().renderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void CheckSDLError(int line = -1)
{
	std::string error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

void PrintSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) { sdlMain(); }
int main() { sdlMain(); }