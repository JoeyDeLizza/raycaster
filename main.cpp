//#include <iostream>
//#include <fstream>
//#include <ostream>
//#include <sys/types.h>
//#include <vector>
//#include <cstdint>
//#include <cassert>
//#include "graphics.h"
//#include "map.h"
//#include "SDL2/SDL.h"
#include "core.h"
#include "lineseg.h"
#include "point.h"
#include <math.h>
#define PI 3.14159265


uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b,
                    const uint8_t a = 255);
void unpack_color(uint32_t c, const uint8_t &r, const uint8_t &g,
                  const uint8_t &b, const uint8_t &a);
void drop_ppm_image(const std::string filename,
                    const std::vector<uint32_t> pixels, int h, int w);
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);
void render(SDL_Renderer* r, int h, int w);

vec2 rotate(vec2 u, double ang);

//double lin_interp(double x, double xi, double xi2, double yi, double yi2); 


int main(int argc, char **argv) {
  int h = 512;
  int w = 512;

  //  uint8_t a;
  //  std::vector<uint32_t> framebuffer(h*w, 255);
  //  for(int i = 0; i < h; i++) {
  //    for(int j = 0; j < w; j++) {
  //      uint8_t r, g, b;
  //      r = 255*i/(float)w;
  //      g = 255*j/(float)h;
  //      b = 0;
  //      framebuffer[i+j*w] = pack_color(r, g, b, a);  //    }
  //  }
  //  Cell white = Cell(pack_color(255, 255, 255));
  //  std::vector<Cell> cells(16*16, white);
  //  Map m = Map(cells, 16, 16);
  //  uint32_t c = pack_color(255,255,255);
  //  draw_rectangle(50,50,h,w,5,5,c, framebuffer);
  //  //map m = map(cells, 16, 16);
  //  drop_ppm_image("image.ppm", framebuffer, h, w);
  //  m.drawCell(0,0, framebuffer, white);
  //  drop_ppm_image("image2.ppm", framebuffer, h, w);

  // The window we'll be rendering to
  SDL_Window *window = NULL;

  SDL_Renderer *gRenderer = NULL;
  SDL_Surface *mapsurface = NULL;
  SDL_Texture *texture = NULL;

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;


  int wid, hei;
  initialize(&window, &gRenderer, &mapsurface, &texture); 
  //Initialize SDL
  //    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  //      {
  //        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  //      }
  //    else
  //      {
  //        //Create window
  //        window = SDL_CreateWindow( "Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
  //        // Sdl_SetWindowSize(window , w*2,
  //        //		     h);
  //        //Create renderer for window
  //        //The window renderer
  //  
  //    //The surface contained by the window
  //  
  //  
  // 	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  //        
  //  
  //        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother
  //        SDL_RenderSetLogicalSize(gRenderer, 512, 512);
  //  
  //        
  //  
  //        SDL_Texture *texture = SDL_CreateTexture(gRenderer,
  //  					       SDL_PIXELFORMAT_ARGB8888,
  //  					       SDL_TEXTUREACCESS_STREAMING,
  //  					       512, 512);
  //  
  // 	// SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_ARGB8888);
  // 	SDL_Surface *surface = SDL_CreateRGBSurface(0, 512, 512, 32,
  //                                        0x00FF0000,
  //                                        0x0000FF00,
  //                                        0x000000FF,
  //                                        0xFF000000);
  //        //update_pixel(surface, 0, 512/2);

  // 	//Uint32 blue = SDL_MapRGBA(surface->format, 255, 0, 0, 0);
  // 	SDL_Color blue = { .r = 0, .g = 0, .b = 255, .a = 255};
  // 	Uint32 bluei = SDL_MapRGB(surface->format, blue.r, blue.g, blue.b);
  // 	//std::cout << blue;
  //	Uint32 *tp = (Uint32*) surface->pixels+((0*512) + 512/2);
  //	*tp = 0xFF00FF00;


  //        SDL_UpdateTexture(texture, NULL, surface->pixels, 512*4);
  //        SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
  //        SDL_RenderClear(gRenderer);
  //        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
  //        
  //	 SDL_RenderPresent(gRenderer);
  //Uint32 blue = SDL_MapRGBA(surface->format, 255, 0, 0, 255);
  // SDL_memset(surface->pixels, 0xFF0000FF, surface->h * surface->pitch);
  //lineseg seg = lineseg(10, 10, 502, 10);

  //lineseg seg1 = lineseg(10, 10, 10, 502);

  //Init seg list with bounding border
  std::vector<lineseg> segs(1, lineseg(i_point(10, 10), i_point(502, 10), 0xFFFF0000));
  segs.push_back(lineseg(i_point(10, 10), i_point(10, 502),0xFF00FF00));
  //segs.push_back(lineseg(i_point(10, 502), i_point(502, 502), 0xFF0000FF));
  segs.push_back(lineseg(i_point(502, 502), i_point(502, 10), 0xFF0000FF));

  // Walls surrounding player
  //segs.push_back(lineseg(i_point( (512/2 -50), (512/2) ), i_point( (512/2 - 50), (512/2 - 50) ), 0xFF0000FF));
  //segs.push_back(lineseg( i_point( (512/2 +50), (512/2) ), i_point( (512/2 + 50), (512/2 - 50) ), 0xFFFF0000));
  //segs.push_back(lineseg(i_point( (512/2 +50), (512/2-50) ), i_point( (512/2 - 50), (512/2 - 50) ), 0xFF00FF00));

  SDL_Surface* surface = SDL_CreateRGBSurface(0, 512, 512, 32,
				    0x00FF0000,
				    0x0000FF00,
				    0x000000FF,
				    0xFF000000);
  SDL_memset(surface->pixels, 0, mapsurface->h * mapsurface->pitch);

  bool mapdisplay = 1;

  vec2 o = vec2(0, 0);
  vec2 d = vec2(-1, 0);
  paraLine p = paraLine(o, d);
  //segs.push_back(lineseg(p.p(0), p.p(100), 0xFF0000FF));

  std::cout << std::endl;
  vec2 ppp = vec2(450, 100);
  vec2 u = vec2(-1, 0);
  vec2 v = vec2(0, -1);
  u = rotate(u, PI/6);
  v = rotate(v, PI/6);
  coord c = coord(ppp, u, v);

  vec2 origin = vec2(300, 300);
  //segs.push_back(lineseg(502, 10, 502, 10));
  //line(seg.x1, seg.y1, seg.x2, seg.y2,surface, 0xFF00FF00);
  vec2 position = vec2(150, 512/2);
  i_point pp = i_point(150, 150);
  vec2 angle = vec2(cos(PI/4) , sin(PI/4) );
  paraLine angleLine = paraLine(o, angle);
  //segs.push_back(lineseg((angleLine.p(0)), angleLine.p(100),  0xFFFFFF00));
    std::vector<lineseg> cone;

    std::vector<lineseg> basis;
    basis.push_back(lineseg(i_point(450, 100), c.vector_to_point(c.local_to_global(vec2(1,0).mul(10))), 0xff00ffff));

    basis.push_back(lineseg(i_point(450, 100), c.vector_to_point(c.local_to_global(vec2(0,1).mul(10))), 0xff00ffff));

    cone.push_back(lineseg((c.vector_to_point(c.local_to_global(c.point_to_vector(angleLine.p(0))))), c.vector_to_point(c.local_to_global(c.point_to_vector(angleLine.p(300)))),  0xFFFFFFFF));
  angle = vec2(cos(3*PI/4), sin(3*PI/4));
  angleLine = paraLine(o, angle);
  cone.push_back(lineseg((c.vector_to_point(c.local_to_global(c.point_to_vector(angleLine.p(0))))), c.vector_to_point(c.local_to_global(c.point_to_vector(angleLine.p(300)))),  0xFFFFFF00));

  // update_pixel(mapsurface, 0xFFFF0000, pp.x, pp.y );
  //update_pixel(mapsurface, 0xFFFFFF00, 265, 256 );
  //segs.push_back(lineseg(c.vector_to_point(c.global_to_local(p.p(0))), c.vector_to_point(c.global_to_local(p.p(50))), 0xFFFF0000));
  vec2 a = vec2(1, 2);
  vec2 a_to_local = c.global_to_local(a);
  std::cout << std::endl;
  std::cout << a_to_local.get_x() << "," << a_to_local.get_y();
  std::vector<lineseg> xbuf(1, lineseg(i_point(0, 0), i_point(0, 0), 0xFFFF0000));
  std::vector<lineseg> xbufs;
  xbufs = process_segs(segs, c);
  for(auto s : segs) {
    std::cout << "Looping:" << std::endl;
    std::cout << s.p0.x << " " << origin.get_x() << std::endl;

    std::cout << s.p0.y << " " << origin.get_x() << std::endl;
    std::cout << s.p1.x << " " << origin.get_x() << std::endl;

    std::cout << s.p1.y << " " << origin.get_x() << std::endl;
    // process_seg(s);
    //    | for each point           |
    //    |   calculate_angle(point) |
    //    |   x_to_screenspace(ang)  |
    //    | for p in between points  |
    //    |   draw_column(p, z)      |
    //    |    |
    //lineseg x = process_seg(s, c);

    //if (x.p0.x >= 0 && x.p0.x <= 512)
    //  xbufs.push_back(lineseg(x.p0, x.p0, x.color));
    //if (x.p1.x >= 0 && x.p1.x <= 512)
    //xbufs.push_back(lineseg(x.p1, x.p1, x.color));
    
    if (1) {
      vec2 l = vec2(s.p0.x, s.p0.y);
      vec2 loc_l = c.global_to_local(l);

      double ang = atan2( (double) (loc_l.get_y()) ,(double) ( loc_l.get_x()) );
      std::cout << "Angle p0: " << ang << std::endl;
      // negative to switch coord space, should find a better way
      double xpos = lin_interp(ang, PI/4, 3 * PI/4, 0, 512);
      std::cout << "xpos" << "\n";
      std::cout << xpos << "\n";
        if (xpos >= 0 && xpos <= 512) {
	  // xbuf.push_back(lineseg(i_point(xpos, 512/2), i_point(xpos, 512/2), 0xFFFF0000));
	 }
      //if(ang >= 0)
	//	segs.push_back(lineseg(i_point(300, 300), s.p0,  0xFFFFFFFF));
      //	}
      if (1) {
	vec2 l1 = vec2(s.p1.x, s.p1.y);
	vec2 loc_l1 = c.global_to_local(l1);
	double ang1 = atan2( (double) (loc_l1.get_y()) ,(double) ( loc_l1.get_x()) );
	std::cout << "Anglep1: " << ang1 << std::endl;
	double xpos1 = lin_interp(ang1, PI/4, 3 * PI/4, 0, 512);
	if (xpos1 >= 0 && xpos1 <= 512) {
	  std::cout << "// XXX: pos1" << "\n";
	  std::cout << xpos1 << "\n";
	    
	  //xbuf.push_back(lineseg(i_point(xpos1, 512/2), i_point(xpos1, 512/2), 0xFFFF0000));
	  }

      //if(ang1 >=0)
	//segs.push_back(lineseg(i_point(300, 300), s.p1,  0xFF00FFFF));
	//}
      
      //segs.push_back(lineseg(c.vector_to_point(c.global_to_local(p.p(0))), c.vector_to_point(c.global_to_local(p.p(100))), 0xFFFF0000));
      }
    }
  }
  //line(seg1.x1, seg1.y1, seg1.x2, seg1.y2,surface, 0xFF00FF00);
  for(auto s : xbuf) {
    
    //line(s.p0, s.p1, surface, s.color);
    
  }
  for(auto s : xbufs) {
    std::cout << s.p0.x << "," << s.p0.y << "\n";
    std::cout << s.p1.x << "," << s.p1.y << "\n";


     line(s.p0, s.p1, surface, s.color);
  }
  for(auto s : segs) {
    line(s.p0, s.p1, mapsurface, s.color);

    //std::cout << "P0 x: " << s.p0.x << " Angle: " << atan( std::abs(pp.x - s.p0.y) / std::abs(pp.x - s.p0.x) )-PI;

    //std::cout << "P1 x: " << s.p1.x << " Angle: " << atan( std::abs(pp.x - s.p1.y) / std::abs(pp.x - s.p1.x) )-PI;
  }
  for(auto s : cone) {
    
    line(s.p0, s.p1, mapsurface, s.color);
  }
  for(auto s : basis) {
    
    line(s.p0, s.p1, mapsurface, s.color);
  }
  draw_screen(mapsurface, texture, gRenderer);

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



	      switch (e.type) {
	      case SDL_KEYDOWN:
		std::cout << "Key press detected" << std::endl;
		if (mapdisplay) {
		  
		  draw_screen(mapsurface, texture, gRenderer);
		  mapdisplay = !mapdisplay;

		} else {
		  draw_screen(surface, texture, gRenderer);
		  mapdisplay = !mapdisplay;
		}
	      default:
		break;
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
  
  // std::cout << "ANGLELINE: " <<  angleLine.p(0).x << angleLine.p(0).y << std::endl;
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

vec2 rotate(vec2 u, double ang) {
  return vec2(u.get_x() * cos(ang) -u.get_y() * sin(ang), u.get_y() * cos(ang) + u.get_x() * sin(ang));
}

//double lin_interp(double x, double xi, double xi2, double yi, double yi2) {
//
//  return yi + ( (x - xi) / (xi2 - xi) ) * (yi2 -yi);
//}
  
