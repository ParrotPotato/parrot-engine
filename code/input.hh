#ifndef PARROT_INPUT

#include "parrot.hh"

#include <SDL2/SDL.h>

#include <functional>

namespace parrot{
	
	struct InputHandler
	{
		public:
		InputHandler();
		void update();


		void set_keydown_callback(std::function<void(int)> func);
		void set_keyup_callback(std::function<void(int)> func);
		void set_keypress_callback(std::function<void(int)> func);

		// We are passing the SDL_Event struct instance to callback for event handling
		// we can later add a custom structure for carrying mouse event information

		void set_mousemotion_callback(std::function<void(const SDL_Event &sdlevent)> func);
		void set_mousebutton_callback(std::function<void(const SDL_Event &sdlevent)> func);

		private:

		// NOTE(nitesh) : This function is a place holder for the key event listener
		//
		static void placeholder_func(int x);
		static void placeholder_mouseevent(const SDL_Event & sdlevent);
		
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

		std::function <void(const SDL_Event & sdlevent)> mousemotion;
		std::function <void(const SDL_Event & sdlevent)> mousebutton;
	};
}


#define PARROT_INPUT
#endif
