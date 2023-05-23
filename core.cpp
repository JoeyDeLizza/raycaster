#include "core.h"

void initialize(SDL_Window **w, SDL_Renderer **r, SDL_Surface **s, SDL_Texture **t) {
  
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
  else
    {
      //Create window
      *w = SDL_CreateWindow( "Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_SHOWN );
      // Sdl_SetWindowSize(window , w*2,
      //		     h);
      //Create renderer for window
      //The window renderer

  //The surface contained by the window


      
      *r = SDL_CreateRenderer( *w, -1, SDL_RENDERER_ACCELERATED );

      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
      SDL_RenderSetLogicalSize(*r, 512, 512);

      

      *t = SDL_CreateTexture(*r,
			     SDL_PIXELFORMAT_ARGB8888,
			     SDL_TEXTUREACCESS_STREAMING,
			     512, 512);
   	// SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_ARGB8888);
   	*s = SDL_CreateRGBSurface(0, 512, 512, 32,
				  0x00FF0000,
				  0x0000FF00,
				  0x000000FF,
				  0xFF000000);

	//   *s = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_ARGB32);
      //draw_pixel(*s, 0, 512/2);
      //SDL_UpdateTexture(*t, NULL, s->pixels, s->pitch);
      //SDL_SetRenderDrawColor(*r, 255, 255, 255, 255);
      //SDL_RenderClear(*r);
      //SDL_RenderCopy(*r, *t, NULL, NULL);
      //SDL_RenderPresent(*r);
      if( *w == NULL )
	{
	  printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}

    }
}
