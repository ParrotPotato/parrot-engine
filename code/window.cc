#include "window.hh"
#include "parrot.hh"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <assert.h>

namespace parrot{

		void Window::create_widnow(const char * buffer, int width, int height)
		{
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

			// creating window itself
			sdlwindow = SDL_CreateWindow(buffer, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
			assert(sdlwindow);
			
			sdlcontext = SDL_GL_CreateContext(sdlwindow);

			assert(sdlcontext);

			// Initializing glew for graphics accleration 
			assert(glewInit() == GLEW_OK);	

			// Enable depth buffer for rendering 2d Objects
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
			glClearDepth(1.0f);

			this->height = height;
			this->width = width;
		}

		void Window::set_clear_color(uint8 r, uint8 g, uint8 b, uint8 a)
		{
			glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
		}

		void Window::set_clear_depth(float d)
		{
			glClearDepth(d);
		}

		void Window::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void Window::update()
		{
			static uint32 lastticks = 0;
			if(lastticks != 0) 
			{
				uint32 currentticks = SDL_GetTicks();
				rendertime = (float)(currentticks - lastticks) * 0.5f  / 1000.0f + 0.5 * (rendertime);
			}	
			SDL_GL_SwapWindow(sdlwindow);
			lastticks = SDL_GetTicks();
		}

		real32 Window::get_per_frame_render_time() const 
		{
			return rendertime;
		}

}
