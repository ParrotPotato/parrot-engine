#ifndef NGX_INPUT

#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>

#include <iostream>

namespace ngx{
	
	struct InputHandler
	{
		public:
		InputHandler()
		{
			keydown = &placeholder_func;
			keyup = &placeholder_func;
			keypress = &placeholder_func;
		}

		void update()
		{
			SDL_Event event;
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_QUIT:
						Core::terminate_core();
						break;

					case SDL_KEYDOWN:
						if(event.key.keysym.sym >= 322) 
						{
							std::cout << "Unhandled key pressed as input " << std::endl;
							break;
						}
						else if(keys[event.key.keysym.sym] == true)
							keypress(event.key.keysym.sym);
						else 
							keydown(event.key.keysym.sym);
						keys[event.key.keysym.sym] = true;
						break;

					case SDL_KEYUP:
						if(event.key.keysym.sym >= 322) 
						{
							std::cout << "Unhandled key pressed as input " << std::endl;
							break;
						}
						else if(keys[event.key.keysym.sym] == true)
							keyup(event.key.keysym.sym);
						keys[event.key.keysym.sym] = false;
						break;

					default:
						break;
				}
			}
		}


		void set_keydown_callback(std::function<void(int)> func)
		{
			keydown =  func;
		}
		void set_keyup_callback(std::function<void(int)> func)
		{
			keyup =  func;
		}
		void set_keypress_callback(std::function<void(int)> func)
		{
			keypress = func;
		}

		private:

		// NOTE(nitesh) : This function is a place holder for the key event listener
		//
		static void placeholder_func(int x)
		{
			return; 
		}
		
		// we are keeping the record of all the keys that were pressed 
		//
		// NOTE(nitesh): Maybe we would be using this for partial input processing 
		// per frame, instead of processing the entire input stream using some 
		// reference counter or something else that can take care this implementation
		//
		// NOTE(nitesh): We are currently using array of bool as value for key log,
		// this can be made more efficient using a fixed size array with bit mapping 
		//
		bool keys[322] =  {false};
		std::function <void(int)> keydown; // key was pressed this frame
		std::function <void(int)> keyup;  // key was release this frame
		std::function <void(int)> keypress; // key was down for this and the last frame
	};
}


#define NGX_INPUT
#endif
