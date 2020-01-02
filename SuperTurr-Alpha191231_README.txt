                       --= Super Turr alpha version =--
                    sources + Windows 19-12-31 compilation



-------------------------------------------------------------------------------

--- GAME CONTENTS ---

the SuperTurr Alpha 19.12.31 distribution contains:
1. SuperTurr-Alpha191231.tar.gz archive:
	- game source code (src\ directory)
	- gfx/sfx/music/game data (data\ directory)
	- Windows game binary (superturr.exe)
	- SDL 1.2.14 library (SDL.dll)
	- SDL_mixer 1.2.4 library (SDL_mixer.dll)
	- SDL_image 1.2.3 distribution libraries (SDL_image.dll, jpeg.dll,
	  libpng1.dll, zlib.dll)
        - SDL_gfx 2.0.25 library (libSDL_gfx-15.dll) and its sources for
          compiling additional GFX functions
	- the original Super Tux 0.1.3 readme files
        - other files and directories contained in the original Super Tux 0.1.3
	  distribution and required for running the game or compiling the
	  sources
2. the file you're reading (SuperTurr-Alpha191231_README.txt)



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- SYSTEM REQUIREMENTS ---

Following additional libraries are required to run this compilation on Windows:
	libgcc_s_dw2-1.dll (i386 version)
	libstdc++-6.dll (i386 version)
	libwinpthread-1.dll (i386 version)
suitable versions of the libraries can be found in MinGW development
environment (https://sourceforge.net/projects/mingw/). Put them in the
directory containing the game binary and it should launch without any errors by
running superturr.exe file.

the included binary was succesfully tested with the above libraries on
different PCs running:
	Windows 10 (64-bit)
	Windows 7 Home Premium SP1 (32-bit)
	Windows 7 Professional SP1 (64-bit)
	Windows XP SP3 (32-bit)
in general, it should run on any Windows version that supports Super Tux 0.1.3.



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- STORYLINE --- 

after defeating The Machine, the hero flies back through the outer space.
Suddenly an unknown force begins to bend the flight trajectory, leading him
straight towards an unknown planet. His spaceship gets damaged, as well as the
armor. Thankfully he manages to land safely on the water, but there is no way
back from the planet, as the strong magnetic field surrounds it. Now he must
turn it off, which appears to be a difficult task due to an evil dragon
guarding all of the machinery (and the fact that the planet is populated by
walkers)...



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- GAME RULES ---

general game rules are much like in any Super Mario Bros. clone.

* you begin the game in ball mode. The ball steering is similar to the one in
  Turrican II, except that:
  1. it doesn't bounce after falling to the ground (I've decided not to
     implement that feature, as the game would be too difficult then)
  2. it's NOT invulnerable to enemies
  3. it can jump just like in normal mode and change movement direction when
     above the ground
* bump the blocks to get diamonds and other bonuses
* collect bonuses to get from Ball to Normal mode, gain a 1UP, activate
  shooting ability or temporary shield
* since the hero's armor is malfunctioning, fired shots behaviour is also
  different than in original Turricans
* for the same reason - there is only one weapon type available and a limit of
  2 shots on a screen at a time
* when hit by an enemy, the player is downgraded by one level to the previous
  mode or loses a life
* collecting 100 diamonds gives you 1UP
* most of the enemies can be destroyed by shooting them off
* you can also jump on some enemies (i.e. walkers). They react differently
  depending on the actual type of enemy, though: a T1 walker is destroyed right
  after jumping on it, while T3 walker explodes after a short delay and it's
  highly adviced not to stand in the range of that explosion (the T2 one acts
  somewhat similar to the original, except that it doesn't explode when hitting
  a wall, but it does after jumping on it 5 times)
* swimming slows down player and enemies movement
* default key bindings are set as follows:
	move right : right arrow
	move left : left arrow
	jump : up arrow
	duck : down arrow
	fire/run : right CTRL
* when running, the player can jump higher. Note that when you're in ball mode
  holding or releasing the "run" key has no effect on your speed
* you have a specified amount of time to finish a level. When the time is up,
  you lose a life
* search for hidden wall secrets :)



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- LEVELS EDITOR ---

you can edit the game levels by using the built-in editor. It isn't very 
comfortable at this point, though, as the number of tiles you can choose from 
is limited to about 20 which is quite insufficient when the Super Turr levels
are built of hundreds of them...

the map tiles are specified in:
	data\images\worldmap\antarctica.stwt
sprite animation frames are specified in:
	data\supertux.strf
level tilesets are specified in:
	data\images\tilesets\supertux.stgt
        data\images\tilesets\main.stgt
        data\images\tilesets\[others].stgt

edit appropriate ones of the above to change the set used in levels editor.



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- CURRENT BUILD STATE ---

Alpha 19.12.31:
- added game intro
- added screen fade effect 
- added gameover track
- added several Turrican-sounds
- added version number info (displayed on title screen)
- added "walker bumped from underneath" sprites
- adjusted sounds volume level
- fixed Super Tux 0.1.3 bug: after selecting CREDITS and returning back to
  title screen the music played back even if it was turned off in options menu
- fixed Super Tux 0.1.3 bug: menu background transparency didn't work on
  several OS-es (replaced SDL_MapRGB() function with SDL_MapRGBA() in
  screen.cpp)
- fixed Super Tux 0.1.3 bug: menu background rectangle in Key Settings was too
  wide
- fixed Super Tux 0.1.3 bug in texture.cpp: SurfaceOpenGL::draw_stretched(float
  x, float y, int sw, int sh, Uint8 alpha, bool update) method
- fixed Super Tux 0.1.3 bug in texture.cpp: Surface::CaptureScreen() (it didn't
  check the endianess)
- fixed: after losing last life the game continued with lives counter showing
  -1
- the title fade-in animation now makes use of SDL_gfx libraries (in previous
  releases it was just a set of bitmaps displayed and didn't work on
  MorphOS/AmigaOS)
- many others :)

Alpha 19.05.26:
- changed world name displayed in game save slots (worldmap.cpp)
- changed the Credits screen background image (specified in title.cpp)
- changed the Intro background image (specified in intro.cpp)
- changed the game name and version in configure.ac to the correct values
- fix: after quitting the Credits screen the game crashed, not finding the
  music file specified in title.cpp

Alpha 19.05.25:
- several levels has been initially edited (replaced background, music, enemies
  and most tiles):
	Welcome to Walkers Island
	The Journey Begins
	Via Nostalgica
	The Cave
	Living in a Fridge
	Dragon's Castle (part of the level still awaits editing)
- replaced the worldmap tileset
- changed player/enemies sprite frames and edited game data files to suit the
  game needs
- some new enemies have been added (swimming walker and flying walker - the
  T2-style one)
- added a few sprite animation frames (to make walkers movement look more
  naturally)
- most of SFX have been changed and also added a few music modules (mostly 
  Turrican remixes, details in the credits section below)
- replaced game title screen, also applied something that could be considered
  as a title gfx fade-in effect (which is actually a sequence of PNGs
  displayed)
- some of the game fonts have been changed
- parts of the source code have been edited to suit the game needs (player and
  enemies behaviour, added some sfx, looping in-game music etc.)
- note that the game is in early --> *ALPHA* <-- version! Do not be surprised
  if the sources appear to be messed up. This release is intended to give just
  a preview of what the gameplay looks like in its current state (and also to
  show that the project is not dead yet ;))



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- BUILDING YOUR OWN COMPILATION ---

the sources compile succesfully using gcc 7.2.0 on MinGW (other gcc versions
have not been checked).
compiling the game may require some other additional libraries. Detailed
instructions on building your own Super Tux 0.1.3 compilation are not available
on the Internet anymore, though they can be found at https://web.archive.org by
searching for "http://supertux.lethargik.org/wiki/Building_on_Windows",
2007-11-08 snapshot (you may also check the INSTALL file contained in game
directory).
with all of the required libraries present, running the following commands
under MinGW should create the Windows game binary in /src directory:
	./autogen.sh
	./configure
	make
then just place it in the main game directory.



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- CREDITS ---

Super Turr is a fan-made remake based on Super Tux 0.1.3 source code:
	https://sourceforge.net/projects/super-tux/files/supertux/0.1.3/

the main game character is based on Turrican character created by Manfred Trenz

the remake uses additional gfx from the following games:
	- Gods (original Amiga game graphics designed by Bitmbap Brothers, 
          Super Turr tiles taken from Windows remake by JOTD:
          http://jotd.pagesperso-orange.fr/gods/)
	- Turrican (Amiga version by Factor 5)
	- Turrican II: The Final Fight (Amiga version by Factor 5)
	- Turrican 3: The Payment Day (Amiga version by Factor 5)
	- Super Turrican (SNES version by Factor 5)
	- Turrican 2005 (Mobile version by THQ)

map tiles by Buch:
	https://opengameart.org/users/buch

title screen background image:
	https://meowx.com/
	https://opengameart.org/content/magma-spacescapes

using additional sfx from the following games:
	- Turrican (Amiga version by Factor 5)
	- Turrican II: The Final Fight (Amiga version by Factor 5)
	- Turrican 3: The Payment Day (Amiga version by Factor 5)

this distribution contains following music modules:
	- Gods Title Remix (godsremix91.mod) by Barry Leitch
	- Turrican Chip RMX (turrican_chip_rmx.xm) by Malibu

the remake idea, music (except the moThe remake idea, music (except the
modules mentioned above), gfx modifications, additional sprite frames, sfx
ripping, source code modifications and putting it all together by Krystian
Hikiert



-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- KNOWN BUGS ---


[ MOS ] pressing right Ctrl in keyboard settings actually sets the bind to left
        Ctrl... You can change the key bindings manually by editing
        .supertux/config file contents, but it won't work anyway
[ MOS ] sometimes the game hangs up on quitting (which has probably something
        to do with the screen fade effect)
[ MOS ] the game may hang up after finishing the last level
[ general ] the water splash sounds tend to overlap each other, causing the
            volume to be annoyingly high
FIXED [MOS / Windows ] after losing life #0 the game continues with lives
                            counter showing -1...
FIXED [MOS] displaying title gfx animation doesn't work
FIXED [MOS] no menu background transparency (although it's probably the powerSDL libs
            issue)


-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--- COPYING & LICENSE ---

the game is distributed under the GNU GPL 2.0 license. For details, see the
COPYING file.

SDL, SDL_mixer, SDL_image and SDL_GFX libraries are distributed under the terms
of GNU LGPL license (http://www.gnu.org/copyleft/lesser.html). The libraries
and its source code can be downloaded from http://www.libsdl.org/



-------------------------------------------------------------------------------