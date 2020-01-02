//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
/////////////////////////////////////////
//  $Id$
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>

#ifndef WIN32
#include <sys/types.h>
#include <ctype.h>
#endif

#include "defines.h"
#include "globals.h"
#include "screen.h"
#include "setup.h"
#include "type.h"

/* Needed for line calculations */
#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
#define ABS(x) ((x)>0 ? (x) : (-x))

/* --- CLEAR SCREEN --- */
void clearscreen(int r, int g, int b)
{
#ifndef NOOPENGL
  if(use_gl)
    {
      glClearColor(r/256, g/256, b/256, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
  else
  {
#endif

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
#ifndef NOOPENGL

    }
#endif
}

/* --- DRAWS A VERTICAL GRADIENT --- */

void drawgradient(Color top_clr, Color bot_clr)
{
#ifndef NOOPENGL
  if(use_gl)
    {
      glBegin(GL_QUADS);
      glColor3ub(top_clr.red, top_clr.green, top_clr.blue);
      glVertex2f(0, 0);
      glVertex2f(640, 0);
      glColor3ub(bot_clr.red, bot_clr.green, bot_clr.blue);
      glVertex2f(640, 480);
      glVertex2f(0, 480);
      glEnd();
    }
  else
  {
#endif

    for(float y = 0; y < 480; y += 2)
      fillrect(0, (int)y, 640, 2,
                     (int)(((float)(top_clr.red-bot_clr.red)/(0-480)) * y + top_clr.red),
                     (int)(((float)(top_clr.green-bot_clr.green)/(0-480)) * y + top_clr.green),
                     (int)(((float)(top_clr.blue-bot_clr.blue)/(0-480)) * y + top_clr.blue), 255);
/* calculates the color for each line, based in the generic equation for functions: y = mx + b */

#ifndef NOOPENGL

    }
#endif
}

/* --- FADE IN --- */

/** Fades the given surface into a black one. If fade_out is true, it will fade out, else
it will fade in */

void fade(Surface *surface, int seconds, bool fade_out);

void fade(const std::string& surface, int seconds, bool fade_out)
{
Surface* sur = new Surface(datadir + surface, IGNORE_ALPHA);
fade(sur, seconds, fade_out);
delete sur;
}

void fade(Surface *surface, int seconds, bool fade_out)
{
int alpha;
if (fade_out)
  alpha = 0;
else
  alpha = 255;

  int cur_time, old_time;
  cur_time = SDL_GetTicks();
  int alphadiff = 1;
	int x = 0;
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w = 640;
			src.h = 480;

		std::vector<Surface *> ants_pointer(256);
		SDL_Surface * ants_SDL[256];
		while (alpha >= 0 && alpha < 256) {
//			ants_SDL[x] = SDL_CreateRGBSurface(screen->flags,
//												screen->w,
//												screen->h,
//												screen->format->BitsBerPixel,
//												screen->format->Rmask,
//												screen->format->Gmask,
//												screen->format->Bmask,
//												screen->format->Amask);
//			ants_SDL[alphadiff] = surface->impl->get_sdl_surface();

//ants_SDL[alphadiff] = sdl_surface_from_sdl_surface(surface->impl->get_sdl_surface(), 1);


/*    ants_SDL[alphadiff] = SDL_DisplayFormatAlpha(surface->impl->get_sdl_surface());
			SDL_SetAlpha(ants_SDL[alphadiff], ants_SDL[alphadiff]->flags, alphadiff);*/
			
//			ants_SDL[alphadiff] = SDL_CreateRGBSurface(screen->flags, 640, 480, screen->format->BitsPerPixel,
//						screen->format->Rmask,
//						screen->format->Gmask,
//						screen->format->Bmask,
//						screen->format->Amask);
//	ants_SDL[alphadiff] = surface->impl->get_sdl_surface();
//	ants_SDL[alphadiff] = sdl_surface_from_file("./data/images/background/superturr/gods.png", 0);
ants_SDL[alphadiff] = SDL_DisplayFormat(surface->impl->get_sdl_surface());

//	SDL_FillRect(ants_SDL[alphadiff], &src, SDL_MapRGBA(surface->impl->get_sdl_surface()->format, 255, 255, 0, 255));

			
			
//fprintf(stdout, "alpha #%i = %u\n", alphadiff, ants_SDL[alphadiff]->format->Amask);
			alphadiff++;
		    if(fade_out)
				alpha += alphadiff;
		    else
				alpha -= alphadiff;
//			ants_pointer(x) = ants_SDL[x];
fprintf(stdout, "jeden %i\n", alpha);
			if (alpha < 255) SDL_SetAlpha(ants_SDL[alphadiff - 1], SDL_SRCALPHA, alpha);
				else SDL_SetAlpha(ants_SDL[alphadiff - 1], SDL_SRCALPHA, alpha);


ants_pointer.at(alphadiff - 1) = new Surface(ants_SDL[alphadiff - 1], 0);
//ants_pointer.at(alphadiff) = surface;
fprintf(stdout, "lalala %i\n", alphadiff);
		}
fprintf(stdout, "skurwysyn");
if (fade_out)
  alpha = 0;
else
  alpha = 255;
	alphadiff = 1;
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = screen->w;
	dest.h = screen->h;
//alpha = 1;
  while(alpha >= 0 && alpha < 256)
    {
clearscreen(0, 0, 0);
fprintf(stdout, "alpha #%i = %u\n", alphadiff, ants_SDL[alphadiff]->format->Gmask);


		if (use_gl)	{
//		ants_pointer.at(alphadiff)->draw_stretched((screen->w - rotozoom_pictureSDL[framecount]->w) / 2,
//																	30,
//																	(int)rotozoom_pictureSDL[framecount]->w,
//																	(int)rotozoom_pictureSDL[framecount]->h,
//																	255,
//																	true);
		ants_pointer.at(alphadiff)->draw_bg(255, true);
		}
			else {
			SDL_BlitSurface(ants_SDL[alphadiff], NULL, screen, &dest);
			}



updatescreen();
//		SDL_BlitSurface(ants_SDL[alphadiff], NULL, screen, &dest);
//    surface->draw(0,0,alpha, false);
    flipscreen();



//    			SDL_BlitSurface(ants_SDL[20], NULL, screen, &dest);
  //  			    			SDL_BlitSurface(ants_SDL[10], NULL, screen, &dest);
    			    flipscreen();
SDL_Delay(100);

//SDL_Delay(1);
//    old_time = cur_time;
//    cur_time = SDL_GetTicks();

    /* Calculate the next alpha value */
//    float calc = (float) ((cur_time - old_time) / seconds);
//fprintf(stdout, "curr - old = %f\n", (float)(cur_time - old_time));
//fprintf(stdout, "time: %f\n", calc);
	alphadiff++;
    if(fade_out)
		alpha += alphadiff;
    else
		alpha -= alphadiff;
//      alpha += 255 / calc;
//      alpha -= 255 / calc;
    }
}

/* 'Stolen' from the SDL documentation.
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to set */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp)
    {
    case 1:
      *p = pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
          p[0] = (pixel >> 16) & 0xff;
          p[1] = (pixel >> 8) & 0xff;
          p[2] = pixel & 0xff;
        }
      else
        {
          p[0] = pixel & 0xff;
          p[1] = (pixel >> 8) & 0xff;
          p[2] = (pixel >> 16) & 0xff;
        }
      break;

    case 4:
      *(Uint32 *)p = pixel;
      break;
    }
}

/* Draw a single pixel on the screen. */
void drawpixel(int x, int y, Uint32 pixel)
{
  /* Lock the screen for direct access to the pixels */
  if ( SDL_MUSTLOCK(screen) )
    {
      if ( SDL_LockSurface(screen) < 0 )
        {
          fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
          return;
        }
    }

  if(!(x < 0 || y < 0 || x > screen->w || y > screen->h))
    putpixel(screen, x, y, pixel);

  if ( SDL_MUSTLOCK(screen) )
    {
      SDL_UnlockSurface(screen);
    }
  /* Update just the part of the display that we've changed */
  SDL_UpdateRect(screen, x, y, 1, 1);
}

void drawline(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
#ifndef NOOPENGL
  if(use_gl)
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4ub(r, g, b,a);

      glBegin(GL_LINES);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
      glEnd();
      glDisable(GL_BLEND);
    }
  else
    {
#endif

      /* Basic unantialiased Bresenham line algorithm */
      int lg_delta, sh_delta, cycle, lg_step, sh_step;
      Uint32 color = SDL_MapRGBA(screen->format, r, g, b, a);

      lg_delta = x2 - x1;
      sh_delta = y2 - y1;
      lg_step = SGN(lg_delta);
      lg_delta = ABS(lg_delta);
      sh_step = SGN(sh_delta);
      sh_delta = ABS(sh_delta);
      if (sh_delta < lg_delta)
        {
          cycle = lg_delta >> 1;
          while (x1 != x2)
            {
              drawpixel(x1, y1, color);
              cycle += sh_delta;
              if (cycle > lg_delta)
                {
                  cycle -= lg_delta;
                  y1 += sh_step;
                }
              x1 += lg_step;
            }
          drawpixel(x1, y1, color);
        }
      cycle = sh_delta >> 1;
      while (y1 != y2)
        {
          drawpixel(x1, y1, color);
          cycle += lg_delta;
          if (cycle > sh_delta)
            {
              cycle -= sh_delta;
              x1 += lg_step;
            }
          y1 += sh_step;
        }
      drawpixel(x1, y1, color);
#ifndef NOOPENGL

    }
#endif
}

/* --- FILL A RECT --- */

void fillrect(float x, float y, float w, float h, int r, int g, int b, int a) {
	if(w < 0) {
		x += w;
		w = -w;
	}
	if(h < 0) {
		y += h;
		h = -h;
	}

#ifndef NOOPENGL
	if(use_gl) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(r, g, b,a);

		glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y+h);
		glVertex2f(x, y+h);
		glEnd();
		glDisable(GL_BLEND);
	}
	else {
#endif

		SDL_Rect src, rect;
		SDL_Surface *temp = NULL;

		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;

		if(a != 255) {
			temp = SDL_CreateRGBSurface(screen->flags, rect.w, rect.h, screen->format->BitsPerPixel,
						screen->format->Rmask,
						screen->format->Gmask,
						screen->format->Bmask,
						screen->format->Amask);
			src.x = 0;
			src.y = 0;
			src.w = rect.w;
			src.h = rect.h;

			SDL_FillRect(temp, &src, SDL_MapRGBA(screen->format, r, g, b, a));

			SDL_SetAlpha(temp, SDL_SRCALPHA, a);
			SDL_BlitSurface(temp,0,screen,&rect);
			SDL_FreeSurface(temp);
        }
		else
			SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, r, g, b));

#ifndef NOOPENGL
	}
#endif

}

/* --- UPDATE SCREEN --- */

void updatescreen(void)
{
  if(use_gl)  /*clearscreen(0,0,0);*/
    SDL_GL_SwapBuffers();
  else
    SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

void flipscreen(void)
{
  if(use_gl)
    SDL_GL_SwapBuffers();
  else
    SDL_Flip(screen);
}

void fadeout()
{
  clearscreen(0, 0, 0);
  white_text->draw_align("Loading...", screen->w/2, screen->h/2, A_HMIDDLE, A_TOP);
  flipscreen();
}

void update_rect(SDL_Surface *scr, Sint32 x, Sint32 y, Sint32 w, Sint32 h)
{
  if(!use_gl)
    SDL_UpdateRect(scr, x, y, w, h);
}

