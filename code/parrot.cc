#include "parrot.hh"

#include <SDL2/SDL.h>

// NOTE(nitesh) : The other system classes (window, input etc) can inherit from this 
// engine class and should only be the one changing state of the game engine
//
//
namespace parrot{

	bool Core::is_engine_running = false; 

	void Core::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		is_engine_running = true;
	}

	bool Core::is_running()
	{
		return is_engine_running;
	}

	bool Core::terminate_core()
	{
		is_engine_running = false;
	}
}
