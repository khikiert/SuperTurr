//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
///////////////////////////////////////////  $Id$
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>

#include "defines.h"
#include "globals.h"
#include "intro.h"
#include "text.h"

#include "screen.h"

void draw_intro()
{
//if(debug_mode)
//  fade_file("./data/images/background/superturr/title.png", 30, "fadein", 1, false);
//display_text_file("intro.txt", "/images/background/superturr/title.png", SCROLL_SPEED_MESSAGE);


//  Surface * xxxxx = new Surface("./data/images/background/superturr/title.png", IGNORE_ALPHA);
//  fade_surface(xxxxx->impl->get_sdl_surface(), 15, "fadein", 1, false);
  fade_textfile("./data/intro.txt", "./data/images/background/superturr/title.png", 15, "fadein", 1, false);
  
  
  
  
//    fade_textfile("PROGDIR:data/intro.txt", "PROGDIR:data/images/background/superturr/title.png", 15, "fadein", 1, false);
}

