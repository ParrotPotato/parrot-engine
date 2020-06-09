#ifndef PARROT_WINDOW

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <assert.h>

#include "parrot.hh"

namespace parrot{

	struct Window
	{
		public:
		void create_widnow(const char * buffer, int width, int height);

		void set_clear_color(uint8 r, uint8 g, uint8 b, uint8 a);
		void set_clear_depth(float d);

		void clear();
		void update();

		real32 get_per_frame_render_time() const;

		private:
		SDL_Window * sdlwindow = 0;
		SDL_GLContext sdlcontext = 0;

		uint32 height = 0;
		uint32 width = 0;

		real32 rendertime = 0;
	
	};
}

#define PARROT_WINDOW
#endif
