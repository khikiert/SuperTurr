	/* 

TestRotozoom.c: test program for rotozoom routines

(C) A. Schiffler, 2001-2011, zlib License

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "TestRotozoomSTurri.h"

#include "SDL.h"
#include "SDL_image.h"

#ifdef WIN32
#include <windows.h>
#include "SDL_gfxPrimitives.h"
#include "SDL_rotozoom.h"
#else
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_rotozoom.h"
#endif

/* Pause flag */
int pause = 0;

/* Custom rotation setup */
double custom_angle=0.0;
double custom_fx=1.0;
double custom_fy=1.0;
int custom_smooth=0;

/* Delay between frames */
int delay;
int start_delay;

/* Curren message */
char *messageText;

void TestRotozoomSTurri::HandleEvent()
{
	SDL_Event event; 

	/* Check for events */
	while ( SDL_PollEvent(&event) || pause ) {
		switch (event.type) {
			 case SDL_QUIT:
				 exit(0);
				 break;
		}
		
		if (pause) {
			SDL_Delay(100);
		}
	}
}

void TestRotozoomSTurri::ClearScreen(SDL_Surface *screen)
{
	int i;
	/* Set the screen to black */
	if ( SDL_LockSurface(screen) == 0 ) {
		Uint8 *pixels;
		pixels = (Uint8 *)screen->pixels;
		for ( i=0; i<screen->h; ++i ) {
			memset(pixels, 0,
				screen->w*screen->format->BytesPerPixel);
			pixels += screen->pitch;
		}
		SDL_UnlockSurface(screen);
	}
}



void TestRotozoomSTurri::RotatePicture(SDL_Surface *screen, SDL_Surface *picture, int rotate, int flip, int smooth, int position, SDL_Surface *background) 
{
	SDL_Surface *rotozoom_picture[1440];
	SDL_Rect dest[1440];
	int framecount, framemax, frameinc;
	double zoomf, zoomfx, zoomfy;

	SDL_Rect dest_bkg;
	dest_bkg.x = 0;
	dest_bkg.y = 0;
	dest_bkg.w = screen->w;
	dest_bkg.h = screen->h;

	printf("%s\n", messageText);

	/* Rotate and display the picture */
	framemax=4*360; 
	frameinc=1;
	ClearScreen(screen);

   /*
     * Palettized screen modes will have a default palette (a standard
     * 8*8*4 colour cube), but if the image is palettized as well we can
     * use that palette for a nicer colour matching
     */
    if (background->format->palette && screen->format->palette) {
	    SDL_SetColors(screen, background->format->palette->colors, 0,
	        background->format->palette->ncolors);
    }

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(background, NULL, screen, &dest_bkg) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, background->w, background->h);
	
	
	
	for (framecount=0; framecount<framemax; framecount += frameinc) {
//		if ((framecount % 360)==0) frameinc++;
		frameinc++;
		zoomf=(float)(framecount+2*360)/(float)framemax;
		zoomf=0.448*zoomf*zoomf;
		if ((rotozoom_picture[framecount] = rotozoomSurface(picture, 0, zoomf, smooth)) != NULL) {
			dest[framecount].x = (screen->w - rotozoom_picture[framecount]->w)/2;
			dest[framecount].y = 30;
			dest[framecount].w = rotozoom_picture[framecount]->w;
			dest[framecount].h = rotozoom_picture[framecount]->h;
		}
	}

	frameinc = 1;
	for (framecount=0; framecount<framemax; framecount += frameinc) {
//		if ((framecount % 360)==0) frameinc++;
		frameinc++;
		HandleEvent();
		if ( SDL_BlitSurface(rotozoom_picture[framecount] , NULL, screen, &dest[framecount]) < 0 ) {
			fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
			break;
		}

		/* Display by flipping screens */
		SDL_Flip(screen);

		/* Delay */
		SDL_Delay(delay);
	}

	frameinc = 1;
	for (framecount=0; framecount<framemax; framecount += frameinc) {
//		if ((framecount % 360)==0) frameinc++;
		frameinc++;
		SDL_FreeSurface(rotozoom_picture[framecount]);
	}
}





void TestRotozoomSTurri::Draw(SDL_Surface *screen, int start, int end)
{
	SDL_Surface *picture, *picture_again;
	char *pngfile;	
	char *bkgfile;

	/* Define masking bytes */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 rmask = 0xff000000; 
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00; 
	Uint32 amask = 0x000000ff;
#else
	Uint32 amask = 0xff000000; 
	Uint32 bmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00; 
	Uint32 rmask = 0x000000ff;
#endif

	/* Load the image into a surface */
	SDL_Surface *title_image, *background_image;
	SDL_RWops *rwop;

	pngfile = "title-32.png";
	rwop=SDL_RWFromFile(pngfile, "rb");
	printf("Loading picture: %s\n", pngfile);
	title_image=IMG_LoadPNG_RW(rwop);
	if ( title_image == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", pngfile, SDL_GetError());
		return;
	}

	bkgfile = "title.png";
	rwop=SDL_RWFromFile(bkgfile, "rb");
	printf("Loading picture: %s\n", bkgfile);
	background_image=IMG_LoadPNG_RW(rwop);
	if ( background_image == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", bkgfile, SDL_GetError());
		return;
	}

	sprintf(messageText, "8a.  rotozoom: Just zooming (angle=0), no interpolation, centered");
	// rotate, flip, smoothing, position
	RotatePicture(screen, title_image, 0, 0, 0, 1, background_image);

	/* Free the picture */
	SDL_FreeSurface(title_image);
	SDL_FreeSurface(background_image);

	return;
}

/*
// \brief SDL_rotozoom test
*/
int TestRotozoomSTurri::maint()
{

	SDL_Surface *screen;
	int w, h;
	int desired_bpp;
	Uint32 video_flags;
	int start, end;

	/* Title */
	fprintf(stderr,"SDL_rotozoom test\n");
	messageText = (char *)malloc(128);

	/* Set default options and check command-line */
	w = 640;
	h = 480;
	desired_bpp = 32;
	video_flags = 1;
	start = 1;
	end = 9999;
	delay = 25;
	start_delay = 50;

	/* Force double buffering */
	video_flags |= SDL_DOUBLEBUF;
	if (use_fullscreen) video_flags |= SDL_FULLSCREEN;

	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);			/* Clean up on exit */

	/* Initialize the display */
	screen = SDL_SetVideoMode(w, h, desired_bpp, video_flags);

	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
			w, h, desired_bpp, SDL_GetError());
		exit(1);
	}

	/* Show some info */
	printf("Set %dx%dx%d mode\n",
		screen->w, screen->h, screen->format->BitsPerPixel);
	printf("Video surface located in %s memory.\n",
		(screen->flags&SDL_HWSURFACE) ? "video" : "system");

	/* Check for double buffering */
	if ( screen->flags & SDL_DOUBLEBUF ) {
		printf("Double-buffering enabled - good!\n");
	}

	/* Set the window manager title bar */
	SDL_WM_SetCaption("SDL_rotozoom test", "rotozoom");

	/* Do all the drawing work */
	Draw(screen, start, end);	
	free(messageText);

	return(0);
}


TestRotozoomSTurri::TestRotozoomSTurri() {
	maint();
}
TestRotozoomSTurri::~TestRotozoomSTurri() {
}