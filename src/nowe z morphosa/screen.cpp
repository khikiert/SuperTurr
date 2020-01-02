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
#include "SDL_Surface_to_GL.h"
#include "text.h"

/* Needed for line calculations */
#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
#define ABS(x) ((x)>0 ? (x) : (-x))




/* --- CLEAR SCREEN --- */
void clearscreen(int r, int g, int b) {
#ifndef NOOPENGL
	if(use_gl) {
		glClearColor(r/256, g/256, b/256, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else {
#endif
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
#ifndef NOOPENGL
	}
#endif
}


void ClearScreenSDL(SDL_Surface *screenx)
{
	int i;
	/* Set the screen to black */
	if ( SDL_LockSurface(screenx) == 0 ) {
		Uint8 *pixels;
		pixels = (Uint8 *)screenx->pixels;
		for ( i=0; i<screenx->h; ++i ) {
			memset(pixels, 0,
				screenx->w*screenx->format->BytesPerPixel);
			pixels += screenx->pitch;
		}
		SDL_UnlockSurface(screenx);
	}
}



/* --- DRAWS A VERTICAL GRADIENT --- */
void drawgradient(Color top_clr, Color bot_clr) {
#ifndef NOOPENGL
	if(use_gl) {
		glBegin(GL_QUADS);
		glColor3ub(top_clr.red, top_clr.green, top_clr.blue);
		glVertex2f(0, 0);
		glVertex2f(640, 0);
		glColor3ub(bot_clr.red, bot_clr.green, bot_clr.blue);
		glVertex2f(640, 480);
		glVertex2f(0, 480);
		glEnd();
	}
	else {
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
void fade_screen(int seconds, const char mode[], int alphainc, bool clrscr) {

	// ustal poczatkowa wartosc alpha
	int alpha = 255;
	if (strcmp(mode, "fadein") == 0) alpha = 0;
	int alphadiff = 1;

	// dest okresla wspolrzedne obrazu dla fadein/out
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = screen->w;
	dest.h = screen->h;

	SDL_Surface * screen_SDL;
	if (!use_gl) { 					// OpenGL OFF
		screen_SDL = SDL_DisplayFormat(screen);
	}

	SDL_Surface_to_GL * screen_GL = new SDL_Surface_to_GL();
	if (use_gl) {					// OpenGL ON
		screen_GL->create_GL_tex_from_display();
	}

	int loop_Timer;
	int loop_Delay = 0;
	while(alpha >= 0 && alpha < 256) {

		// odczekaj okreslona przerwe i zapisz czas do zmiennej
		SDL_Delay(loop_Delay);
		loop_Timer = SDL_GetTicks();

		// w razie potrzeby wyczysc ekran
		if ((clrscr) || (strcmp(mode, "fadeout") == 0)) clearscreen(0, 0, 0);

		/* Display the surface */
		if (!use_gl) {			// OpenGL OFF
			SDL_SetAlpha(screen_SDL, SDL_SRCALPHA, alpha);
			SDL_BlitSurface(screen_SDL, NULL, screen, &dest);
		}
		else {					// OpenGL ON
			screen_GL->display_image(screen_GL, alpha);
		}

	    flipscreen();

	    /* Calculate the next alpha value */
		alphadiff += alphainc;
    	if(strcmp(mode, "fadein") == 0) alpha += alphadiff;
	    else alpha -= alphadiff;

		// oblicz czas trwania przerwy przed powtorzeniem petli
		loop_Delay = 100 - (SDL_GetTicks() - loop_Timer);
    }
	delete screen_GL;
}





void fade_surface(SDL_Surface * sdl_surface, int seconds, const char mode[], int alphainc, bool clrscr) {

	// ustal poczatkowa wartosc alpha
	int alpha = 255;
	if (strcmp(mode, "fadein") == 0) alpha = 0;
	int alphadiff = 1;

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = screen->w;
	dest.h = screen->h;

//	SDL_Surface * screen_SDL;
	SDL_Surface * screen_SDL = SDL_CreateRGBSurface(screen->flags,
													sdl_surface->w,
													sdl_surface->h,
													sdl_surface->format->BitsPerPixel,
													sdl_surface->format->Rmask,
													sdl_surface->format->Gmask,
													sdl_surface->format->Bmask,
													sdl_surface->format->Amask);
	screen_SDL = SDL_DisplayFormat(sdl_surface);

	SDL_Surface_to_GL * screen_GL = new SDL_Surface_to_GL();
	if (use_gl) {					// OpenGL ON
		screen_GL->create_GL_tex_from_SDL_surface(screen_SDL);
	}

	int loop_Timer;
	int loop_Delay = 0;
	while(alpha >= 0 && alpha < 256) {

		// odczekaj okreslona przerwe i zapisz czas do zmiennej
		SDL_Delay(loop_Delay);
		loop_Timer = SDL_GetTicks();

		// w razie potrzeby wyczysc ekran
		if ((clrscr) || (strcmp(mode, "fadeout") == 0)) clearscreen(0, 0, 0);

		/* Display the surface */
		if (!use_gl) {			// OpenGL OFF
			SDL_SetAlpha(screen_SDL, SDL_SRCALPHA, alpha);
			SDL_BlitSurface(screen_SDL, NULL, screen, &dest);
		}
		else {					// OpenGL ON
			screen_GL->display_image(screen_GL, alpha);
		}

	    flipscreen();

	    /* Calculate the next alpha value */
		alphadiff += alphainc;
    	if(strcmp(mode, "fadein") == 0) alpha += alphadiff;
	    else alpha -= alphadiff;

		fprintf(stdout, "LOOP REPEAT %i %i %i TIMER: %i GETTICKS: %i.\n", alphainc, alphadiff, alpha, loop_Delay, SDL_GetTicks());

		// oblicz czas trwania przerwy przed powtorzeniem petli
		loop_Delay = 100 - (SDL_GetTicks() - loop_Timer);
    }

	delete screen_GL;
}






void fade_file(char * filename, int seconds, const char mode[], int alphainc, bool clrscr) {
	// ustal poczatkowa wartosc alpha
	int alpha = 255;
	if (strcmp(mode, "fadein") == 0) alpha = 0;
	int alphadiff = 1;

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = screen->w;
	dest.h = screen->h;

	SDL_Surface * screen_SDL;
	SDL_Surface_to_GL * screen_GL = new SDL_Surface_to_GL();

	if (!use_gl) {				// OpenGL OFF
			SDL_RWops * rwop;
			rwop = SDL_RWFromFile(filename, "rb");
			fprintf(stdout, "Creating surface from file: %s\n", filename);
			screen_SDL = IMG_LoadPNG_RW(rwop);
			if (screen_SDL == NULL) {
				fprintf(stderr, "Couldn't load SDL surface: %s\n", SDL_GetError());
				return;
			}
			else fprintf(stdout, "Surface succesfully created");
			screen_SDL = SDL_DisplayFormat(screen_SDL);
	}
	else {						// OpenGL ON
			screen_GL->create_GL_tex_from_file(filename);
	}		

	int loop_Timer;
	int loop_Delay = 0;
	while(alpha >= 0 && alpha < 256) {

		// odczekaj okreslona przerwe i zapisz czas do zmiennej
		SDL_Delay(loop_Delay);
		loop_Timer = SDL_GetTicks();

		// w razie potrzeby wyczysc ekran
		if ((clrscr) || (strcmp(mode, "fadeout") == 0)) clearscreen(0, 0, 0);

		/* Display the surface */
		if (!use_gl) {			// OpenGL OFF
			SDL_SetAlpha(screen_SDL, SDL_SRCALPHA, alpha);
			SDL_BlitSurface(screen_SDL, NULL, screen, &dest);
		}
		else {					// OpenGL ON
			screen_GL->display_image(screen_GL, alpha);
		}

	    flipscreen();

	    /* Calculate the next alpha value */
		alphadiff += alphainc;
    	if(strcmp(mode, "fadein") == 0) alpha += alphadiff;
	    else alpha -= alphadiff;

		// oblicz czas trwania przerwy przed powtorzeniem petli
		loop_Delay = 100 - (SDL_GetTicks() - loop_Timer);
    }

	delete screen_GL;
}




void fade_textfile(char * textfilename, char * filename, int seconds, const char mode[], int alphainc, bool clrscr) {
	// ustal poczatkowa wartosc alpha
	int alpha = 255;
	if (strcmp(mode, "fadein") == 0) alpha = 0;
	int alphadiff = 1;

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = screen->w;
	dest.h = screen->h;

	SDL_Surface * screen_SDL;
	SDL_Surface_to_GL * screen_GL = new SDL_Surface_to_GL();

	if (!use_gl) {				// OpenGL OFF
			SDL_RWops * rwop;
			rwop = SDL_RWFromFile(filename, "rb");
			fprintf(stdout, "Creating surface from file: %s\n", filename);
			screen_SDL = IMG_LoadPNG_RW(rwop);
			if (screen_SDL == NULL) {
				fprintf(stderr, "Couldn't load SDL surface: %s\n", SDL_GetError());
				return;
			}
			else fprintf(stdout, "Surface succesfully created");
			screen_SDL = SDL_DisplayFormatAlpha(screen_SDL);

	}
	else {						// OpenGL ON
			screen_GL->create_GL_tex_from_file(filename);
	}		

	int loop_Timer;
	int loop_Delay = 0;
	while(alpha >= 0 && alpha < 256) {

		// odczekaj okreslona przerwe i zapisz czas do zmiennej
		SDL_Delay(loop_Delay);
		loop_Timer = SDL_GetTicks();

		// w razie potrzeby wyczysc ekran
		if ((clrscr) || (strcmp(mode, "fadeout") == 0)) {
			fprintf(stdout, "fading out!!!!!\n");
			clearscreen(0, 0, 0);
		}

		/* Display the surface */
		if (!use_gl) {			// OpenGL OFF
			SDL_SetAlpha(screen_SDL, SDL_SRCALPHA, alpha);
			SDL_BlitSurface(screen_SDL, NULL, screen, &dest);
		}
		else {					// OpenGL ON
			screen_GL->display_image(screen_GL, alpha);
		}

	    flipscreen();

	    /* Calculate the next alpha value */
		alphadiff += alphainc;
    	if(strcmp(mode, "fadein") == 0) alpha += alphadiff;
	    else alpha -= alphadiff;

		// oblicz czas trwania przerwy przed powtorzeniem petli
		loop_Delay = 100 - (SDL_GetTicks() - loop_Timer);
    }

	delete screen_GL;
	fprintf(stdout, "koniec funkcji fade_out");
	display_text_file("intro.txt", "/images/background/superturr/title.png", SCROLL_SPEED_MESSAGE);
	fprintf(stdout, "koniec wyswietlania intro.txt");
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

//			SDL_FillRect(temp, &src, SDL_MapRGB(screen->format, r, g, b));
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

