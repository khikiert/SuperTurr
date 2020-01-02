//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
/////////////////////////////////////////
//  $Id$
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2003 Tobias Glaesser <tobi.web@gmx.de>
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

#ifndef SUPERTURR_RESOURCES_H
#define SUPERTURR_RESOURCES_H

#include "musicref.h"

class SpriteManager;
class MusicManager;

extern Surface* img_waves[3]; 
extern Surface* img_water;
extern Surface* img_pole;
extern Surface* img_poletop;
extern Surface* img_flag[2];
extern Surface* img_cloud[2][4];

extern Surface* img_super_bkgd;

//OSLONKA extern MusicRef herring_song;
extern MusicRef level_end_song;
extern MusicRef gameover_song;

extern SpriteManager* sprite_manager;
extern MusicManager* music_manager;

void loadshared();
void unloadshared();

#endif

/* EOF */

