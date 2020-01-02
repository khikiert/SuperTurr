#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_opengl.h"
#include "SDL_Surface_to_GL.h"
#include "globals.h"
#include "texture.h"

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


void SDL_Surface_to_GL::print_SDL_Surface_info(char * info, SDL_Surface * surff) {
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
flags li : %li\n \
flags lu : %lu\n \
w : %i\n \
h : %i\n \
pitch : %i \n\n \
SDL_HWSURFACE | SDL_DOUBLEBUF = %lu \n\n \
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
					surff->flags, 					surff->flags,
					surff->w,
					surff->h,
					surff->pitch,
					SDL_HWSURFACE | SDL_DOUBLEBUF
	);
	
}


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



GLuint SDL_Surface_to_GL::SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord) {
	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;
	Uint8 SDL_flags = (use_fullscreen ? SDL_FULLSCREEN | SDL_OPENGL & ~SDL_HWSURFACE: SDL_OPENGL & ~SDL_HWSURFACE); 

	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(surface->w);
	h = power_of_two(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */
	image = SDL_CreateRGBSurface(
			SDL_flags,
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
	if (image == NULL) return 0;

	/* Save the alpha blending attributes */
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) SDL_SetAlpha(surface, 0, 0);

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) SDL_SetAlpha(surface, saved_flags, saved_alpha);

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
			     image->pixels);
	SDL_FreeSurface(image); /* No longer needed */

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




SDL_Surface * SDL_Surface_to_GL::create_GL_tex_from_display() {
	SDL_Surface * sdl_surface;
	if (use_gl) sdl_surface = Surface::CaptureScreen()->impl->get_sdl_surface();
	return SDL_DisplayFormat(sdl_surface);
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
