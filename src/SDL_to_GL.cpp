#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "globals.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Surface_to_GL.h"

#ifdef __MACOS__
#define HAVE_OPENGL
#endif

//#ifdef HAVE_OPENGL




/* Undefine this if you want a flat cube instead of a rainbow cube */
#define SHADED_CUBE

/* Define this to be the name of the logo image to use with -logo */
#define LOGO_FILE	"./testimg.bmp"
#define PNG_FILE "./data/images/background/superturr/gods.png"

/* The SDL_OPENGLBLIT interface is deprecated.
   The code is still available for benchmark purposes though.
*/

static SDL_bool USE_DEPRECATED_OPENGLBLIT = SDL_FALSE;


/**********************************************************************/


void SDL_Surface_to_GL::SDL_GL_Enter2DMode(int alpha)
{
//	SDL_Surface *screen = SDL_GetVideoSurface();

	/* Note, there may be other things you need to change,
	   depending on how you have your OpenGL state set up.
	*/
//	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	/* This allows alpha blending of 2D textures with the scene */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(alpha, alpha, alpha, alpha);





  glViewport(0, 0, screen->w, screen->h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen->w, screen->h, 0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, 0.0f);


/*	glViewport(0, 0, screen->w, screen->h);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)screen->w, (GLdouble)screen->h, 0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);*/
}

void SDL_Surface_to_GL::SDL_GL_Leave2DMode()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

//	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();

//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();

//	glPopAttrib();
}


/* Quick utility function for texture creation */
int SDL_Surface_to_GL::power_of_two(int input)
{
	int value = 1;
	while ( value < input ) { value <<= 1; }
	return value;
}



GLuint SDL_Surface_to_GL::SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;
	Uint8 SDL_flags = (use_fullscreen ? SDL_FULLSCREEN | SDL_OPENGL : SDL_OPENGL ); 

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
	if ( image == NULL ) {
		return 0;
	}

	/* Save the alpha blending attributes */
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, 0, 0);
	}

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}

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




void SDL_Surface_to_GL::show_image(int alpha) {
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



void SDL_Surface_to_GL::create_image(SDL_Surface * surfing)
{


	SDL_Surface *screen = SDL_GetVideoSurface();

	if ( ! global_texture ) {
//		SDL_Surface *image;

//	char *pngfile;
//	SDL_RWops *rwop;
//	SDL_Surface *surfing;
//	pngfile = "./data/images/background/superturr/gods.png";
//	rwop=SDL_RWFromFile(pngfile, "rb");
//	fprintf(stdout, "Loading picture: %s\n", pngfile);



		
		GLfloat texcoord[4];

		/* Load the image (could use SDL_image library here) */
//		image = SDL_LoadBMP(LOGO_FILE);
//		if ( image == NULL ) {
//			return;
//		}

//	surfing=IMG_LoadPNG_RW(rwop);
	if ( surfing == NULL ) {
		fprintf(stderr, "Couldn't load SDL surface: %s\n", SDL_GetError());
		return;
	}

		w = surfing->w;
		h = surfing->h;

		/* Convert the image into an OpenGL texture */
		global_texture = SDL_GL_LoadTexture(surfing, texcoord);

		/* Make texture coordinates easy to understand */
		texMinX = texcoord[0];
		texMinY = texcoord[1];
		texMaxX = texcoord[2];
		texMaxY = texcoord[3];

		/* We don't need the original image anymore */
		SDL_FreeSurface(surfing);

		/* Make sure that the texture conversion is okay */
		if ( ! global_texture ) {
			return;
		}
	}

	/* Move the image around */
	x += delta_x;
	if ( x < 0 ) {
		x = 0;
		delta_x = -delta_x;
	} else
	if ( (x+w) > screen->w ) {
		x = screen->w-w;
		delta_x = -delta_x;
	}
	y += delta_y;
	if ( y < 0 ) {
		y = 0;
		delta_y = -delta_y;
	} else
	if ( (y+h) > screen->h ) {
		y = screen->h-h;
		delta_y = -delta_y;
	}
//this->show_image();
}



//#else /* HAVE_OPENGL */

int SDL_Surface_to_GL::maint()
{
	printf("No OpenGL support on this system\n");
	return 1;
}

//#endif /* HAVE_OPENGL */



SDL_Surface_to_GL::SDL_Surface_to_GL() {
}
SDL_Surface_to_GL::~SDL_Surface_to_GL() {
}


