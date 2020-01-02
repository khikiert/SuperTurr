#include "SDL.h"
#include "SDL_opengl.h"

static GLuint global_texture = 0;
static GLfloat texMinX, texMinY;
static GLfloat texMaxX, texMaxY;
static int x = 0;
static int y = 0;
static int w, h;
static int delta_x = 1;
static int delta_y = 1;

class SDL_Surface_to_GL;
class SDL_Surface_to_GL {
	public:
		SDL_Surface_to_GL();
		~SDL_Surface_to_GL();

		void SDL_GL_Enter2DMode(int alpha);
		void SDL_GL_Leave2DMode();
		int power_of_two(int input);
		GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
		void create_image(SDL_Surface * surfing);
		void show_image(int alpha);
		int maint();
};
