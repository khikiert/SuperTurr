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

bool title_animation = 0;

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

void TestRotozoomSTurri::ClearScreen(Surface *screen)
{
//	int i;
//	/* Set the screen to black */
//	if ( SDL_LockSurface(screen) == 0 ) {
//		Uint8 *pixels;
//		pixels = (Uint8 *)screen->pixels;
//		for ( i=0; i<screen->h; ++i ) {
//			memset(pixels, 0,
//				screen->w*screen->format->BytesPerPixel);
//			pixels += screen->pitch;
//		}
//		SDL_UnlockSurface(screen);
//	}
}



void TestRotozoomSTurri::RotatePicture(SDL_Surface * screen, Surface * picture, int rotate, int flip, int smooth, int position, Surface * background) 
{
//	SDL_Surface * rotozoom_picture[1440];
const int x = 1440;
	Surface * rotozoom_picture[1440];
	SDL_Rect dest[1440];
	int framecount, framemax, frameinc;
	double zoomf, zoomfx, zoomfy;

	SDL_Rect dest_bkg;
	dest_bkg.x = 0;
	dest_bkg.y = 0;
	dest_bkg.w = screen->w;
	dest_bkg.h = screen->h;

	fprintf(stdout, "%s\n", messageText);

	/* Rotate and display the picture */
	framemax=4*360; 
	frameinc=1;

	clearscreen(0, 0, 0);

   /*
     * Palettized screen modes will have a default palette (a standard
     * 8*8*4 colour cube), but if the image is palettized as well we can
     * use that palette for a nicer colour matching
     */
    if (background->impl->get_sdl_surface()->format->palette && screen->format->palette) {
	    SDL_SetColors(screen, background->impl->get_sdl_surface()->format->palette->colors, 0,
	        background->impl->get_sdl_surface()->format->palette->ncolors);
    }

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(background->impl->get_sdl_surface(), NULL, screen, &dest_bkg) < 0) {
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		}

//	background->draw_part(0, 0, 0, 0, screen->w, screen->h);
//    if (draw_part(0, 0, 0, 0, 100, 100,125,1) == -2)
//      Surface::reload();
//background->reload();
flipscreen();

fprintf(stdout, "dupa 1");
fprintf(stdout, "%i", (background->impl->get_sdl_surface()));
fprintf(stdout, " --- ");
fprintf(stdout, "%i", (screen));
fprintf(stdout, " --- ");
//fprintf(stdout, "%i", (background->impl->get_sdl_surface() = screen));
fprintf(stdout, "dupa 2");
//    SDL_UpdateRect(screen, 0, 0, background->w, background->h);
				//updatescreen();

SDL_Surface * dupa;	
	fprintf(stdout, " ---4 ");
Surface * psikutas[1];
int www = 0;
std::vector<Surface *> ants_pointer(1440);
SDL_Surface * huj[1440];
Surface * pustaw;

					for (framecount = 0, frameinc = 1; framecount < framemax; framecount += frameinc) {
//		if ((framecount % 360)==0) frameinc++;
//clearscreen(0,0,0);
	fprintf(stdout, " ---5 ");
						frameinc++;
//		fprintf(stdout, "ramka %d\n", framecount);
//		zoomf=(float)(framecount+2*360)/(float)framemax;
						zoomf = (float)(framecount + 720) / (float)framemax;
	fprintf(stdout, " ---6 ");
						zoomf = 0.448 * zoomf * zoomf;
	fprintf(stdout, " ---7 ");

										//ants_pointer.push_back(pustaw);
//fprintf(stdout, "sdffds %i", huj->flags);
//fprintf(stdout, "sdffds %a", rotozoom_picture[framecount]->impl->get_sdl_surface());
//huj = SDL_ConvertSurface(rotozoom_picture[framecount]->impl->get_sdl_surface(), rotozoom_picture[framecount]->impl->get_sdl_surface()->format, rotozoom_picture[framecount]->impl->get_sdl_surface()->flags);

	fprintf(stdout, " ---8 ");
//						if ((rotozoom_picture[framecount]->impl->get_sdl_surface() = rotozoomSurface(picture->impl->get_sdl_surface(), 0, zoomf, smooth)) != NULL) {
//			if ((dupa = rotozoomSurface(picture->impl->get_sdl_surface(), 0, zoomf, smooth)) != NULL) {
if (framemax == 0) fprintf(stdout, "xxx");
	fprintf(stdout, " ---9 ");
//rotozoom_picture[framecount]->impl->get_sdl_surface() = rotozoomSurface(picture->impl->get_sdl_surface(), 0, zoomf, smooth);
if ((huj[framecount] = rotozoomSurface(picture->impl->get_sdl_surface(), 0, zoomf, smooth)) != NULL) {
	fprintf(stdout, " ---ihuj. ");
//							dest[framecount].x = (screen->w - rotozoom_picture[framecount]->impl->get_sdl_surface()->w) / 2;
					dest[framecount].x = (screen->w - huj[framecount]->w) / 2;
	fprintf(stdout, " ---ihuj1. ");
int num_ants = 140;
	fprintf(stdout, " ---ihuj2. ");

//ants.resize(new_num_ants);
	fprintf(stdout, " ---ihuj3. ");
// if ((huj[0] = background->impl->get_sdl_surface()) == NULL) fprintf(stdout, "srul");
	fprintf(stdout, " ---ihuj4. ");
//fprintf(stdout,"\n\nuwaga... %i\n", psikutas[www]->impl->set_sdl_surface());
//ants_pointer.resize(20);

	fprintf(stdout, " ---ihuj5. ");

	fprintf(stdout, " ---ihuj6. ");
//fprintf(stdout, "\nuwaga... %i\n", ants_pointer[1]->impl->set_sdl_surface());
//rotozoom_picture[framecount]->impl->get_sdl_surface() = rotozoomSurface(picture->impl->get_sdl_surface(), 0, zoomf, smooth);
	fprintf(stdout, " ---10 %i", picture->impl->get_sdl_surface()->w);
							dest[framecount].y = 30;
	fprintf(stdout, " ---11 ");
//							dest[framecount].w = rotozoom_picture[framecount]->impl->get_sdl_surface()->w;
					dest[framecount].w = huj[framecount]->w;
	fprintf(stdout, " ---12 ");
	//						dest[framecount].h = rotozoom_picture[framecount]->impl->get_sdl_surface()->h;
					dest[framecount].h = huj[framecount]->h;
					}
fprintf(stdout, "\nuwaga...%i \n",ants_pointer.size());
  fprintf(stdout,"ants_pointer.front() is now %i\n", &ants_pointer.at(0));
  fprintf(stdout,"ants_pointer.front() is now %i\n", &ants_pointer.at(1));
ants_pointer.at(framecount) = picture;
fprintf(stdout,"huj framecount = %i x %i\n", huj[framecount]->w, huj[framecount]->h);
//ants_pointer.at(framecount)->impl->resize(huj[framecount]->w, huj[framecount]->h);
//ants_pointer.at(framecount)->impl->set_sdl_surface(huj[framecount]);
//ants_pointer.at(framecount)->sdl_surface_from_file(dupa);
	fprintf(stdout, " ---12b ");
  fprintf(stdout,"ants_pointer.front() is now %s\n", &ants_pointer.at(0));
    fprintf(stdout,"ants_pointer.front() is now %s\n", &ants_pointer.at(1));
  fprintf(stdout,"ants_pointer.front() is now %i\n", &ants_pointer.at(0));
    fprintf(stdout,"ants_pointer.front() is now %i\n", &ants_pointer.at(1));
  fprintf(stdout,"ants_pointer.front() is now %d\n", &ants_pointer.at(0));
    fprintf(stdout,"ants_pointer.front() is now %d\n", &ants_pointer.at(1));
  fprintf(stdout,"ants_pointer.front() is now %f\n", &ants_pointer.at(0));
    fprintf(stdout,"ants_pointer.front() is now %f\n", &ants_pointer.at(1));
  fprintf(stdout,"ants_pointer.front() is now %&\n", &ants_pointer.at(0));
    fprintf(stdout,"ants_pointer.front() is now %&\n", &ants_pointer.at(1));

fprintf(stdout, "surfac: %i\n", ants_pointer.at(framecount)->impl->get_sdl_surface()->w);

//		fprintf(stdout, " ---12c %i", (ants_pointer.at(0))->impl->get_sdl_surface()->w);
//	fprintf(stdout, " ---%i   13 ",ants_pointer.size());
//						}
					}

	frameinc = 1;
	fprintf(stdout, " ---14 ");
					for (framecount = 0, frameinc = 1; framecount < framemax; framecount += frameinc) {
	fprintf(stdout, " ---15 %i", framecount);
//		if ((framecount % 360)==0) frameinc++;
						frameinc++;
	fprintf(stdout, " ---16 ");
						HandleEvent();
						clearscreen(0, 0, 0);
	fprintf(stdout, " ---17 ");
//						if ( SDL_BlitSurface(rotozoom_picture[framecount], NULL, screen, &dest[framecount]) < 0 ) {
//							fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
//							break;

//rotozoom_picture[framecount]->draw_part(0, 0, 0, 0, screen->w, screen->h);
fprintf(stdout,"wymiary #%i: %i x %i, %i x %i\n", framecount, ants_pointer.at(framecount)->impl->w, ants_pointer.at(framecount)->impl->h, huj[framecount]->w, huj[framecount]->h);
//ants_pointer.at(framecount)->draw_part(0, 0, 0, 0, huj[framecount]->w, huj[framecount]->h);
if (use_gl)						ants_pointer.at(framecount)->draw_stretched((screen->w - huj[framecount]->w) / 2, 30, (int)huj[framecount]->w, (int)huj[framecount]->h, 255, false);
else {
						if (SDL_BlitSurface(huj[framecount], NULL, screen, &dest[framecount]) < 0) {
							fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
							break;
						}
}
// ants_pointer.at(framecount)->draw_stretched(0.0f, 0.0f, (int)huj[framecount]->w, (int)huj[framecount]->h, 128, false);
	fprintf(stdout, " ---18 ");
flipscreen();
		/* Delay */
		SDL_Delay(delay + (framecount / 104) * (framecount / 208));

						}
//			screen->draw_part(0, 0, 0, 0, 100, 100);

		/* Display by flipping screens */
//		SDL_Flip(screen);
	fprintf(stdout, " ---19 ");
SDL_Delay(1000);
flipscreen();

		/* Delay */
//		SDL_Delay(5000);
				//		SDL_FreeSurface(rotozoom_picture[framecount]);
//		SDL_Flip(screen);
//flipscreen();
	}

////	frameinc = 1;
//	for (framecount = 0, frameinc = 1; framecount < framemax; framecount += frameinc) {
////		if ((framecount % 360)==0) frameinc++;
//		frameinc++;
//	}
				//}





void TestRotozoomSTurri::Draw(SDL_Surface * screen, int start, int end)
{
//	Surface * picture, *picture_again;
	char *pngfile;	
	char *bkgfile;

	/* Define masking bytes */
/*#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 rmask = 0xff000000; 
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00; 
	Uint32 amask = 0x000000ff;
#else
	Uint32 amask = 0xff000000; 
	Uint32 bmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00; 
	Uint32 rmask = 0x000000ff;
#endif*/

	/* Load the image into a surface */
	static Surface * title_img, * background_img;

  title_img = new Surface(datadir + "/images/title/superturr/title-32.png", USE_ALPHA);
  background_img = new Surface(datadir + "/images/background/superturr/title.png", USE_ALPHA);



	SDL_Surface *title_image, *background_image;
	SDL_RWops *rwop;

	pngfile = "title-32.png";
	rwop=SDL_RWFromFile(pngfile, "rb");
	fprintf(stdout, "Loading picture: %s\n", pngfile);
	title_image=IMG_LoadPNG_RW(rwop);
	if ( title_image == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", pngfile, SDL_GetError());
		return;
	}

	bkgfile = "title.png";
	rwop=SDL_RWFromFile(bkgfile, "rb");
	fprintf(stdout, "Loading picture: %s\n", bkgfile);
	background_image=IMG_LoadPNG_RW(rwop);
	if ( background_image == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s\n", bkgfile, SDL_GetError());
		return;
	}

	sprintf(messageText, "8a.  rotozoom: Just zooming (angle=0), no interpolation, centered");
	// rotate, flip, smoothing, position
	title_animation = 1;
	RotatePicture(screen, title_img, 0, 0, 0, 1, background_img);
fprintf(stdout, "koniec RotatePicture()\n");
	/* Free the picture */
//	SDL_FreeSurface(title_image);
//	SDL_FreeSurface(background_image);


	return;
}

/*
// \brief SDL_rotozoom test
*/
int TestRotozoomSTurri::maint()
{

//	SDL_Surface *screen;
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
	delay = 15;
	start_delay = 50;

	/* Force double buffering */
////	video_flags |= SDL_DOUBLEBUF;
//	if (use_fullscreen) video_flags |= SDL_FULLSCREEN;

	/* Initialize SDL */
////	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
////		fprintf(stderr,
////			"Couldn't initialize SDL: %s\n", SDL_GetError());
////		exit(1);
////	}
////	atexit(SDL_Quit);			/* Clean up on exit */

	/* Initialize the display */
//	screen = SDL_SetVideoMode(w, h, desired_bpp, video_flags);

	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
			w, h, desired_bpp, SDL_GetError());
		exit(1);
	}

	/* Show some info */
	fprintf(stdout, "Set %dx%dx%d mode\n",
		screen->w, screen->h, screen->format->BitsPerPixel);
	fprintf(stdout, "Video surface located in %s memory.\n",
		(screen->flags&SDL_HWSURFACE) ? "video" : "system");

	/* Check for double buffering */
	if ( screen->flags & SDL_DOUBLEBUF ) {
		fprintf(stdout, "Double-buffering enabled - good!\n");
	}

	/* Set the window manager title bar */
//	SDL_WM_SetCaption("SDL_rotozoom test", "rotozoom");

	/* Do all the drawing work */
	Draw(screen, start, end);	
fprintf(stdout, "koniec Draw()\n");

	free(messageText);

	return(0);
}


TestRotozoomSTurri::TestRotozoomSTurri() {
	maint();
}
TestRotozoomSTurri::~TestRotozoomSTurri() {
}