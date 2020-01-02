#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <sdl.h>
#undef main				// Undo SDL's desire to link with SDLmain.lib, as we don't need it!
#include "SDL_anigif.h"


#define APP_NAME				"AniGIF"
#define APP_TITLE				"AniGIF Demo"
#define SAMPLE_FILE				"sample.gif"
#define	FRAME_SLEEP_MS			16						// Frames with zero delay attempt 60fps



static HINSTANCE	ghInstance;							// Instance handle
static HINSTANCE	ghPrevInst;							// Previous instance handle
static int			gnCmdShow;							// Show window mode (from WinMain)
static const char	gszAppName[] = APP_NAME;			// Application name
static const char	gszAppTitle[] = APP_TITLE;			// Application title

static SDL_Surface*	gSurface = NULL;					// SDL created window surface
static SDL_Surface* gSaveSurface = NULL;				// SDL surface for GIF disposal mode 3
static unsigned		gBackground;						// SDL Background window color
static SDL_Color	gRGB = { 0,0,128 };					// RGB Background color (default light blue)
static int			giColor = 0;						// User color index

static bool			gfRunning = true;					// True if app is running (no exit request)
static char			gszGifFile[_MAX_PATH];				// GIF File to open
static AG_Frame*	gpAG = NULL;						// Pointer to array of anigif frames
static int			gnAG;								// Number of frames
static int			giAG;								// Index to current frame
static int			gTickMS;							// Start-of-frame time tick (zero to zero to force frame)
static SDL_Rect		gFrame;								// Frame dimension on screen (based on frame zero)



static bool			RunSample( void );
static bool			HandleEvents( void );
static bool			SetupWindowSurface( int Width, int Height );
static void			InitAnimation( void );
static void			RenderDisplay( void );
static void			UnionRectangle( SDL_Rect& d, const SDL_Rect& s1, const SDL_Rect& s2 );
static void			SetWindowTitle( const char* pszSuffix );



//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ghInstance	= hInstance;
	ghPrevInst	= hPrevInstance;
	gnCmdShow	= nCmdShow;

	while ( *lpCmdLine == ' ' )
		lpCmdLine++;
	if ( *lpCmdLine )
	{
		strcpy( gszGifFile, lpCmdLine );
	}
	else
	{
		GetModuleFileName( NULL, gszGifFile, sizeof(gszGifFile) );
		strcpy( strrchr(gszGifFile,'\\')+1, SAMPLE_FILE );
	}

	if ( !RunSample() )
		MessageBox( NULL, "Error - something went horribly wrong!", gszAppName, MB_ICONWARNING|MB_OK );

	return 0;
}



//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
static bool RunSample( void )
{
	bool fResult = false;

	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE) == 0 )
	{
		gnAG = AG_LoadGIF( gszGifFile, NULL, 0 );

		if ( gnAG )
		{
			gpAG = new AG_Frame[gnAG];
			AG_LoadGIF( gszGifFile, gpAG, gnAG );

			// Use frame zero's size (it should be the largest size).
			gFrame.w = gpAG[0].surface->w;
			gFrame.h = gpAG[0].surface->h;

			if ( SetupWindowSurface(gFrame.w*3/2,gFrame.h*3/2) )
			{
				char* pFile = strrchr( gszGifFile, '\\' );
				SetWindowTitle( (pFile)?pFile+1:gszGifFile );

				// Optionally convert surfaces to display window format.
				AG_ConvertSurfacesToDisplayFormat( gpAG, gnAG );

				while ( gfRunning )
				{
					if ( HandleEvents() )
					{
						RenderDisplay();
						SDL_Delay( FRAME_SLEEP_MS );
					}
				}

				fResult = true;
			}

			if ( gSaveSurface )
				SDL_FreeSurface( gSaveSurface );

			AG_FreeSurfaces( gpAG, gnAG );
			delete [] gpAG;
		}

		SDL_Quit();
	}

	return fResult;
}



//----------------------------------------------------------------------------
// returns true if no events pending, so animation can run.
//----------------------------------------------------------------------------
static bool HandleEvents( void )
{
	SDL_Event event;

	while ( gfRunning )
	{
		if ( SDL_PollEvent(&event) )
		{
			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
				  case SDLK_ESCAPE:
					gfRunning = false;
					break;

				  case SDLK_w:
					SetupWindowSurface( gFrame.w, gFrame.h );
					break;

				  case SDLK_b:
					switch ( ++giColor & 0x03 )
					{
					  case 0:	gRGB.r = 0;		gRGB.g = 0;		gRGB.b = 128;	break;
					  case 1:	gRGB.r = 192;	gRGB.g = 192;	gRGB.b = 192;	break;
					  case 2:	gRGB.r = 255;	gRGB.g = 255;	gRGB.b = 255;	break;
					  case 3:	gRGB.r = 0;		gRGB.g = 0;		gRGB.b = 0;		break;
					}
					InitAnimation();
					break;

				  case SDLK_F1:
				  case SDLK_SLASH:
					MessageBox( NULL, 
						"Keyboard Commands:\n\n"
						"  Esc\tExit program\n"
						"   w\tSet window size to GIF size\n"
						"   b\tToggle different background colors\n"
						"   F1\tDisplay this help\n",
						gszAppName, MB_OK );
					break;

				  case SDLK_LSHIFT:
				  case SDLK_LCTRL:
				  case SDLK_LALT:
					break;

				  default:
					MessageBeep( MB_OK );
					break;
				}
			}
			else if ( event.type == SDL_VIDEORESIZE )
			{
				SetupWindowSurface( event.resize.w, event.resize.h );
			}
			else if ( event.type == SDL_QUIT )
			{
				gfRunning = false;
			}
		}
		else
		{
			if ( (SDL_GetAppState() & SDL_APPACTIVE) )
				break;
			else
				SDL_Delay( 100 );	// SDL window minimized, so take a long nap.
		}
	}

	return gfRunning;
}



//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
static bool SetupWindowSurface( int Width, int Height )
{
	if ( Width < 128 )
		Width = 128;
	if ( Height < 32 )
		Height = 32;

	SDL_Surface* Surface = SDL_SetVideoMode( Width, Height, 32, SDL_SWSURFACE|SDL_RESIZABLE );

	// Update lots of stuff if we got a good video mode.
	if ( Surface )
	{
		gSurface = Surface;

		if ( gSaveSurface )
			SDL_FreeSurface( gSaveSurface );
		gSaveSurface = SDL_DisplayFormat( gSurface );

		gFrame.x = max(gSurface->w - gFrame.w,0)/2;
		gFrame.y = max(gSurface->h - gFrame.h,0)/2;

		InitAnimation();
	}

	return ( Surface != NULL );
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
static void InitAnimation( void )
{
	gBackground = SDL_MapRGB( gSurface->format, gRGB.r, gRGB.g, gRGB.b );
	SDL_FillRect( gSurface, NULL, gBackground );
	SDL_UpdateRect( gSurface, 0, 0, 0, 0 );

	// Reset to and force first frame.
	giAG = 0;
	gTickMS = 0;

	RenderDisplay();
}



//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
static void RenderDisplay( void )
{
	if ( (int)GetTickCount() - gTickMS > gpAG[giAG].delay )
	{
		// Remember this (previous) frame.
		int iLast = giAG;

		// If not forcing frame (gTickMS==0), move to next frame.
		if ( gTickMS && ++giAG >= gnAG )
			giAG = 0;

		// Setup the update rectangle using the current frame size, copy to frame rectangle.
		SDL_Rect u = { gFrame.x + gpAG[giAG].x, gFrame.y + gpAG[giAG].y, gpAG[giAG].surface->w, gpAG[giAG].surface->h };
		SDL_Rect f = u;

		// If GIF disposal mode requires background paint or if frame zero, do it.
		if ( gpAG[iLast].disposal >= AG_DISPOSE_RESTORE_BACKGROUND || giAG == 0 )
		{
			SDL_Rect l = { gFrame.x + gpAG[iLast].x, gFrame.y + gpAG[iLast].y, gpAG[iLast].surface->w, gpAG[iLast].surface->h };
			if ( gpAG[iLast].disposal == AG_DISPOSE_RESTORE_PREVIOUS && gSaveSurface )
				SDL_BlitSurface( gSaveSurface, &l, gSurface, &l );
			else
				SDL_FillRect( gSurface, &l, gBackground );

			// Set update rectangle to smallest rectangle that bounds both last and frame rectangles.
			UnionRectangle( u, l, f );
		}

		// Save current background in frame rectangle if GIF disposal mode 3.
		if ( gpAG[giAG].disposal == AG_DISPOSE_RESTORE_PREVIOUS && gSaveSurface )
			SDL_BlitSurface( gSurface, &f, gSaveSurface, &f );

		// Draw the current frame using the frame rectangle.
		SDL_BlitSurface( gpAG[giAG].surface, NULL, gSurface, &f );

		// Update the display using the update rectangle.
		SDL_UpdateRects( gSurface, 1, &u );

		// Set frame start time (ms).
		gTickMS = GetTickCount();
	}
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
static void UnionRectangle( SDL_Rect& d, const SDL_Rect& s1, const SDL_Rect& s2 )
{
	d.x	= (Sint16)min( s1.x, s2.x );
	d.w = (Sint16)max( s1.x+s1.w, s2.x+s2.w ) - d.x;
	d.y = (Sint16)min( s1.y, s2.y );
	d.h = (Sint16)max( s1.y+s1.h, s2.y+s2.h ) - d.y;
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
static void SetWindowTitle( const char* pszSuffix )
{
	char szTitle[256];

	sprintf( szTitle, "%s %s", gszAppTitle, pszSuffix );
	SDL_WM_SetCaption( szTitle, gszAppName );
}

