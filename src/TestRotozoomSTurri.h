#ifndef SUPERTURR_TESTROTOZOOMSTURRI_H
#define SUPERTURR_TESTROTOZOOMSTURRI_H

// extern bool title_animation;

class TestRotozoomSTurri;

class TestRotozoomSTurri {

public:
  TestRotozoomSTurri();
  ~TestRotozoomSTurri();

	void HandleEvent();
	void ClearScreen(Surface *screen);
	void RotatePicture (SDL_Surface *screen, Surface *picture, int rotate, int flip, int smooth, int position, Surface *background, bool shot_background, bool cleartitle);
	void Draw (SDL_Surface *screen, int start, int end);
	int maint();
	
	

private:

};

#endif

/* Local Variables: */
/* mode:c++ */
/* End: */
