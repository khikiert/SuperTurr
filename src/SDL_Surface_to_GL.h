static GLfloat texMinX, texMinY;
static GLfloat texMaxX, texMaxY;
static int x = 0;
static int y = 0;
static int w, h;

class SDL_Surface_to_GL;
class SDL_Surface_to_GL {
	public:
		struct tex {
			GLuint texture;
		};

		void SDL_GL_Enter2DMode(int alpha);
		void SDL_GL_Leave2DMode();
		int power_of_two(int input);
		GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
		void create_GL_tex_from_file(char * png_file);
		void create_GL_tex_from_SDL_surface(SDL_Surface * sdl_surface);
		void create_GL_tex_from_display();
		void display_image(SDL_Surface_to_GL * object, int alpha);
		int noGL();
		void print_SDL_Surface_info(char * info, SDL_Surface * surff);

		SDL_Surface_to_GL();
		~SDL_Surface_to_GL();
};
