#ifndef SUPERTURR_TESTROTOZOOMSTURRI_H
#define SUPERTURR_TESTROTOZOOMSTURRI_H

class TestRotozoomSTurri;

class TestRotozoomSTurri {

public:
  TestRotozoomSTurri();
  ~TestRotozoomSTurri();

	void HandleEvent();
	void ClearScreen(SDL_Surface *screen);
	void RotatePicture (SDL_Surface *screen, SDL_Surface *picture, int rotate, int flip, int smooth, int position, SDL_Surface *background);
	void Draw (SDL_Surface *screen, int start, int end);
	int maint();
	
	

private:

};

#endif

/* Local Variables: */
/* mode:c++ */
/* End: */
