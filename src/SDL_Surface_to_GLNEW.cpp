#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_opengl.h"
#include "SDL_Surface_to_GL.h"
#include "globals.h"

#ifdef __MACOS__
#define HAVE_OPENGL
#endif

//#ifdef HAVE_OPENGL


/* Undefine this if you want a flat cube instead of a rainbow cube */
#define SHADED_CUBE

/* The SDL_OPENGLBLIT interface is deprecated.
   The code is still available for benchmark purposes though.
*/

static SDL_bool USE_DEPRECATED_OPENGLBLIT = SDL_FALSE;
GLuint global_texture;

/**********************************************************************/


void SDL_Surface_to_GL::SDL_GL_Enter2DMode(int alpha)
{
	/* Note, there may be other things you need to change,
	   depending on how you have your OpenGL state set up.
	*/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	/* This allows alpha blending of 2D textures with the scene */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(alpha, alpha, alpha, alpha);
}

void SDL_Surface_to_GL::SDL_GL_Leave2DMode() {
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}


/* Quick utility function for texture creation */
int SDL_Surface_to_GL::power_of_two(int input) {
	int value = 1;
	while ( value < input ) { value <<= 1; }
	return value;
}



GLuint SDL_Surface_to_GL::SDL_GL_LoadTexture(SDL_Surface *sdl_surface, GLfloat *texcoord) {
	GLuint texture;
fprintf(stdout, "\n2-1");
	int w, h;
fprintf(stdout, "2-2");
	SDL_Surface *image_i;
fprintf(stdout, "2-3");
	SDL_Rect area;
fprintf(stdout, "2-4");
	Uint32 saved_flags;
fprintf(stdout, "2-5");
	Uint8  saved_alpha;
fprintf(stdout, "2-6");
//	Uint32 SDL_flags = (use_fullscreen ? SDL_FULLSCREEN | SDL_OPENGL & ~SDL_HWSURFACE: SDL_OPENGL & ~SDL_HWSURFACE); 

fprintf(stdout, "2-7");
	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(sdl_surface->w);
fprintf(stdout, "2-8");
	h = power_of_two(sdl_surface->h);
fprintf(stdout, "2-9");
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)sdl_surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)sdl_surface->h / h;	/* Max Y */
fprintf(stdout, "2-10");
	image_i = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
#endif
	);
fprintf(stdout, "2-11");

	if (image_i == NULL) {
fprintf(stdout, "\nRETURN!!!!!!!!!!!!!!!");
		return 0;
	}
fprintf(stdout, "2-12");
	/* Save the alpha blending attributes */
	saved_flags = sdl_surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
fprintf(stdout, "2-13");
	saved_alpha = sdl_surface->format->alpha;
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) SDL_SetAlpha(sdl_surface, 0, 0);
fprintf(stdout, "2-14");

	/* Copy the surface into the GL texture image */
	area.x = 0;
fprintf(stdout, "2-15");
	area.y = 0;
fprintf(stdout, "2-16");
	area.w = sdl_surface->w;
fprintf(stdout, "2-17");
	area.h = sdl_surface->h;

fprintf(stdout, "2-18");
	//	SDL_BlitSurface(sdl_surface, &area, screen, &area);
fprintf(stdout, "2-19");

	/* Restore the alpha blending attributes */
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) SDL_SetAlpha(sdl_surface, saved_flags, saved_alpha);
fprintf(stdout, "2-20");

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
			     0,
			     GL_RGB,
			     w, h,
		    	 0,
			     GL_RGBA,
			     GL_UNSIGNED_BYTE,
			     image_i->pixels);
	SDL_FreeSurface(image_i); /* No longer needed */

	return texture;
}




void SDL_Surface_to_GL::display_image(int alpha) {
	/* Show the image on the screen */
	SDL_GL_Enter2DMode(alpha);

	glBindTexture(GL_TEXTURE_2D, global_texture);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(texMinX, texMinY); glVertex2i(x,   y  );
	glTexCoord2f(texMaxX, texMinY); glVertex2i(x+w, y  );
	glTexCoord2f(texMinX, texMaxY); glVertex2i(x,   y+h);
	glTexCoord2f(texMaxX, texMaxY); glVertex2i(x+w, y+h);
	glEnd();

	SDL_GL_Leave2DMode();
}





void SDL_Surface_to_GL::create_GL_tex_from_file(char * png_file) {
	SDL_Surface *sdl_surface;

	if (!global_texture) {
		GLfloat texcoord[4];

		SDL_RWops *rwop;
		rwop=SDL_RWFromFile(png_file, "rb");
		fprintf(stdout, "Loading picture: %s\n", png_file);

		sdl_surface=IMG_LoadPNG_RW(rwop);
		if (sdl_surface == NULL) {
			fprintf(stderr, "Couldn't load SDL surface: %s\n", SDL_GetError());
			return;
		}

		w = sdl_surface->w;
		h = sdl_surface->h;

		/* Convert the image into an OpenGL texture */
		global_texture = SDL_GL_LoadTexture(sdl_surface, texcoord);

		/* Make texture coordinates easy to understand */
		texMinX = texcoord[0];
		texMinY = texcoord[1];
		texMaxX = texcoord[2];
		texMaxY = texcoord[3];

		/* We don't need the original image anymore */
		SDL_FreeSurface(sdl_surface);
		
		/* Make sure that the texture conversion is okay */
		if (!global_texture) return;
	}
}



void SDL_Surface_to_GL::create_GL_tex_from_SDL_surface(SDL_Surface * sdl_surface) {
	if (!global_texture) {
		GLfloat texcoord[4];
fprintf(stdout, "1");
		w = sdl_surface->w;
		h = sdl_surface->h;
fprintf(stdout, "2");
		/* Convert the image into an OpenGL texture */
		global_texture = SDL_GL_LoadTexture(sdl_surface, texcoord);
fprintf(stdout, "3");
		/* Make texture coordinates easy to understand */
		texMinX = texcoord[0];
		texMinY = texcoord[1];
		texMaxX = texcoord[2];
		texMaxY = texcoord[3];
fprintf(stdout, "4");
		/* We don't need the original image anymore */
		SDL_FreeSurface(sdl_surface);
fprintf(stdout, "5");		
		/* Make sure that the texture conversion is okay */
		if (!global_texture) return;
	}
}




void SDL_Surface_to_GL::save_SDL_Surface_data(char * info, SDL_Surface * surff) {
	fprintf(stdout, "\n\n \
****** SAVING SURFACE DATA ****** \n\n \
%s\n \
format->BitsPerPixel : %i\n \
format->palette : %i\n \
format->BytesPerPixel : %i\n \
format->Rloss/Gloss/Bloss/Aloss : %i %i %i %i\n \
format->Rshift/Gshift/Bshift/Ashift : %i %i %i %i \n \
format->Rmask/Gmask/Bmask/Amask : %i %i %i %i \n \
format->colorkey : %i\n \
format->alpha : %i\n \
flags : %i\n \
w : %i\n \
h : %i\n \
pitch : %i \n\n\
****** FINISHED SAVING SURFACE DATA ******\n\n",
					info,
					surff->format->BitsPerPixel,
					surff->format->palette,
					//surff->format->palette->colors->g,
					//surff->format->palette->colors->b,
					surff->format->BytesPerPixel,
					surff->format->Rloss,
					surff->format->Gloss,
					surff->format->Bloss,
					surff->format->Aloss,
					surff->format->Rshift,
					surff->format->Gshift,
					surff->format->Bshift,
					surff->format->Ashift,
					surff->format->Rmask,
					surff->format->Gmask,
					surff->format->Bmask,
					surff->format->Amask,
					surff->format->colorkey,
					surff->format->alpha,
					surff->flags,
					surff->w,
					surff->h,
					surff->pitch
	);
}


void SDL_Surface_to_GL::create_GL_tex_from_display(SDL_Surface * sdl_surfac) {
//	SDL_Surface *sdl_surface;
//SDL_Delay(500);
//SDL_LockSurface(screen);
//flipscreen();
//SDL_Delay(500);
	//sdl_surface = SDL_GetVideoSurface();
//SDL_LockSurface(screen);

//int screen_data[24] = { 
//fprintf(stdout, "hujhujhuj");

save_SDL_Surface_data("warstwa przekazana jako argument",sdl_surfac);

save_SDL_Surface_data("warstwa screen",screen);

//SDL_LockSurface(screen);
	SDL_Surface * sdl_surface = SDL_DisplayFormat(sdl_surfac);
//	SDL_Surface * sdl_surface = SDL_CreateRGBSurfaceFrom(screen->format,
//											 screen->w,
//											 screen->h,
//											 screen->format->BitsPerPixel,
//											 screen->pitch,
//											 screen->format->Rmask,
//											 screen->format->Gmask,
//											 screen->format->Bmask,
//											 screen->format->Amask);
//SDL_UnlockSurface(screen);
save_SDL_Surface_data("warstwa utworzona przez CreateRGBSurface ze screen",sdl_surface);
fprintf(stdout, "\nwartosc alpha utworzonej warstwy: %i\n\n", sdl_surface->format->alpha);
//fprintf(stdout, "\nwartosc alpha warstwy sdl_surfac: %i\n\n", sdl_surfac->format->alpha);
//SDL_SetAlpha(sdl_surfac, 0, 255);
SDL_SetAlpha(sdl_surface, 0, 128);
//fprintf(stdout, "\nwartosc po zmianie alpha warstwy sdl_surfac: %i\n\n", sdl_surfac->format->alpha);
fprintf(stdout, "\nII wartosc alpha utworzonej warstwy: %i\n\n", sdl_surface->format->alpha);

//flipscreen();
//SDL_Delay(500);
//SDL_UnlockSurface(screen);
//flipscreen();
//SDL_Delay(500);
fprintf(stdout, "1. screen - %u %i     sdl_surface = %u %i\n", screen, screen, sdl_surface, sdl_surface);
//	SDL_BlitSurface(screen, NULL, sdl_surface, NULL);
//	SDL_BlitSurface(SDL_GetVideoSurface(), NULL, sdl_surface, NULL);
fprintf(stdout, "2. screen - %u %i     sdl_surface = %u %i\n", screen, screen, sdl_surface, sdl_surface);
//flipscreen();
//create_GL_tex_from_SDL_surface(sdl_surface);
//return;
//	flipscreen();

	if (!global_texture) {
		GLfloat texcoord[4];

		w = sdl_surface->w;
		h = sdl_surface->h;
fprintf(stdout, "lalala\n");
		/* Convert the image into an OpenGL texture */
		global_texture = SDL_GL_LoadTexture(sdl_surface, texcoord);
fprintf(stdout, "trlalala\n");
		/* Make texture coordinates easy to understand */
		texMinX = texcoord[0];
		texMinY = texcoord[1];
		texMaxX = texcoord[2];
		texMaxY = texcoord[3];
fprintf(stdout, "lalfsgfdgdala\n");
		/* We don't need the original image anymore */
		SDL_FreeSurface(sdl_surface);
fprintf(stdout, "aaaaaaaaaaaaaaaaaaalalala\n");		
		/* Make sure that the texture conversion is okay */
		if (!global_texture) return;
	}
}





//#else /* HAVE_OPENGL */

int SDL_Surface_to_GL::noGL()
{
	printf("No OpenGL support on this system\n");
	return 1;
}

//#endif /* HAVE_OPENGL */



SDL_Surface_to_GL::SDL_Surface_to_GL() {
}
SDL_Surface_to_GL::~SDL_Surface_to_GL() {
	global_texture = 0;
}
