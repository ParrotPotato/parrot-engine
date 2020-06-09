#include "input.hh"

#include "parrot.hh"

#include <SDL2/SDL.h>

#include <functional>
#include <iostream>

namespace parrot{
	
	InputHandler::InputHandler()
	{
		keydown = &placeholder_func;
		keyup = &placeholder_func;
		keypress = &placeholder_func;
	}

	void InputHandler::update()
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


	void InputHandler::set_keydown_callback(std::function<void(int)> func)
	{
		keydown =  func;
	}
	void InputHandler::set_keyup_callback(std::function<void(int)> func)
	{
		keyup =  func;
	}
	void InputHandler::set_keypress_callback(std::function<void(int)> func)
	{
		keypress = func;
	}

	void InputHandler::placeholder_func(int x)
	{
		return; 
	}

}

