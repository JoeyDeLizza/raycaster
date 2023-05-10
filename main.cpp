#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <cassert>
#include "graphics.h"
#include "map.h"
#include "SDL2/SDL.h"


uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b,
                    const uint8_t a = 255);
void unpack_color(uint32_t c, const uint8_t &r, const uint8_t &g,
                  const uint8_t &b, const uint8_t &a);
void drop_ppm_image(const std::string filename,
                    const std::vector<uint32_t> pixels, int h, int w);
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);
void render(SDL_Renderer* r, int h, int w);


int main(int argc, char **argv) {
  int h = 512;
  int w = 512;

  uint8_t a;
  std::vector<uint32_t> framebuffer(h*w, 255);
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      uint8_t r, g, b;
      r = 255*i/(float)w;
      g = 255*j/(float)h;
      b = 0;
      framebuffer[i+j*w] = pack_color(r, g, b, a);
    }
  }
  Cell white = Cell(pack_color(255, 255, 255));
  std::vector<Cell> cells(16*16, white);
  Map m = Map(cells, 16, 16);
  uint32_t c = pack_color(255,255,255);
  draw_rectangle(50,50,h,w,5,5,c, framebuffer);
  //map m = map(cells, 16, 16);
  drop_ppm_image("image.ppm", framebuffer, h, w);
  m.drawCell(0,0, framebuffer, white);
  drop_ppm_image("image2.ppm", framebuffer, h, w);

  //The window we'll be rendering to
  SDL_Window* window = NULL;
    
  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;


  int wid, hei;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
  else
    {
      //Create window
      window = SDL_CreateWindow( "Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
      // Sdl_SetWindowSize(window , w*2,
      //		     h);
      //Create renderer for window
      //The window renderer
      SDL_Renderer* gRenderer = NULL;

  //The surface contained by the window


      
      gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
      SDL_RenderSetLogicalSize(gRenderer, 512, 512);

      

      SDL_Texture *texture = SDL_CreateTexture(gRenderer,
					       SDL_PIXELFORMAT_ARGB32,
					       SDL_TEXTUREACCESS_STREAMING,
					       512, 512);
      SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_ARGB32);
      draw_pixel(surface, 0, 512/2);
      SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
      SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
      SDL_RenderClear(gRenderer);
      SDL_RenderCopy(gRenderer, texture, NULL, NULL);
      SDL_RenderPresent(gRenderer);

      if( window == NULL )
        {
	  printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
      else
        {
	  //While application is runninG
            while( !quit )
            {


	      // SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	      //  SDL_RenderClear(gRenderer);
	      // SDL_RenderCopy(gRenderer, texture, NULL, NULL);
	      // SDL_RenderPresent(gRenderer);

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
		  
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }



		    if (e.type == SDL_WINDOWEVENT) {
		      switch (e.window.event) {
		      case SDL_WINDOWEVENT_SHOWN:
			std::cout << "shown" << std::endl;
			break;
		      case SDL_WINDOWEVENT_HIDDEN:
			std::cout << "Hidden" << std::endl;
			break;
		      case SDL_WINDOWEVENT_EXPOSED:
			std::cout << "Exposed" << std::endl;
			break;
		      case SDL_WINDOWEVENT_MOVED:
			std::cout << "Moved" << std::endl;
			break;
		      case SDL_WINDOWEVENT_RESIZED:
			std::cout << "Resized" << std::endl;
			//SDL_GetWindowSize(window, &wid, &hei);
			//SDL_SetWindowSize(window, wid, hei);
			std::cout << w << h;


			
			//	SDL_RenderClear( gRenderer );
			//SDL_RenderPresent( gRenderer );
			break;
		      case SDL_WINDOWEVENT_SIZE_CHANGED:
			std::cout << "Size changed:" << std::endl;
			break;
		      case SDL_WINDOWEVENT_MINIMIZED:
			std::cout << "Minim" << std::endl;
			break;
		      case SDL_WINDOWEVENT_MAXIMIZED:
			std::cout << "Maxim" << std::endl;
			break;
		      case SDL_WINDOWEVENT_RESTORED:
			std::cout << "Restored" << std::endl;
			break;
		      case SDL_WINDOWEVENT_ENTER:
			//std::cout << "Here" << std::endl;
			break;
		      case SDL_WINDOWEVENT_LEAVE:
			//std::cout << "Here" << std::endl;
			break;
		      case SDL_WINDOWEVENT_FOCUS_GAINED:
			std::cout << "Focused" << std::endl;
			break;
		      case SDL_WINDOWEVENT_FOCUS_LOST:
			//std::cout << "Here" << std::endl;
			break;
		      case SDL_WINDOWEVENT_CLOSE:
			std::cout << "Closed" << std::endl;
			break;
		      }
		    }
		}
		//Get window surface
		//screenSurface = SDL_GetWindowSurface( window );

		//get window size
		//SDL_GetRendererOutputSize(gRenderer, &wid, &hei);
	  
		//Fill the surface white
		//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface.format, 0xFF, 0xFF, 0xFF ) );
            
		//Update the surface
		//SDL_UpdateWindowSurface( window );



	  
	      	// Grenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		
		//Render(Grenderer, h, w);
	    }
        }
    }	
  //Destroy window


  std::cout << wid << hei;
  
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}

//void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width, const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
//  for(int i = y; i < rect_height+y; i++) {
//    for(int j = x; j < rect_width+x; j++) {
//      framebuffer[j + i*img_width] = c;
//    }
//  }
//}

void render(SDL_Renderer* r, int h, int w)
{
  SDL_RenderClear( r );
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      SDL_SetRenderDrawColor( r, 255*i/(float)w, 255*j/(float)h, 0x00, 0xFF );
      SDL_RenderDrawPoint( r, i, j);
    }
  }
  
  SDL_RenderPresent( r );
}

uint32_t pack_color(const uint8_t r, const uint8_t g, const  uint8_t b, const uint8_t a) {
  return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpack_color(const uint32_t &c,  uint8_t &r,  uint8_t &g,  uint8_t &b,  uint8_t &a) {
  r = (c >> 0) & 255;
  g = (c >> 8) & 255;
  b = (c >> 16) & 255;
  a = (c >> 24) & 255;
}

void drop_ppm_image(const std::string filename, const std::vector<uint32_t> pixels, const int h, const int w) {
  std::fstream file = std::fstream(filename, std::fstream::out | std::fstream::binary);

  file << "P6\n" << h << " " << w << "\n255\n";
  

  for(int i = 0; i < h*w; i++) {
    uint8_t r, g, b, a;
    unpack_color(pixels.at(i), r, g, b, a);
    file << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
  }
  file.close();
}


  
