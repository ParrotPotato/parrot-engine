#ifndef PARROT_HEADER

#include <SDL2/SDL.h>


// NOTE(nitesh) : The other system classes (window, input etc) can inherit from this 
// engine class and should only be the one changing state of the game engine
//
//
namespace parrot{

	class Core{
		public:
			static void init()
			{
				SDL_Init(SDL_INIT_EVERYTHING);
				is_engine_running = true;
			}

			static bool is_running()
			{
				return is_engine_running;
			}

			static bool terminate_core()
			{
				is_engine_running = false;
			}

		private:
			static bool is_engine_running;	
	};

	bool Core::is_engine_running = false; 
}

#define PARROT_HEADER
#endif 
