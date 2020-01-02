//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
/////////////////////////////////////////
//  $Id$
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//  Copyright (C) 2004 Duong-Khang NGUYEN <neoneurone@users.sf.net>
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

#ifndef SUPERTURR_SOUND_H
#define SUPERTURR_SOUND_H

#include "defines.h"     /* get YES/NO defines */

/*global variable*/
extern bool use_sound;           /* handle sound on/off menu and command-line option */
extern bool use_music;           /* handle music on/off menu and command-line */
extern bool audio_device;        /* != 0: available and initialized */

/* enum of different internal music types */
enum Music_Type {
  NO_MUSIC,
  LEVEL_MUSIC,
  HURRYUP_MUSIC
//OSLONKA  HERRING_MUSIC
};

/* panning effects: terrible :-) ! */
enum Sound_Speaker {
  SOUND_LEFT_SPEAKER = 0,
  SOUND_RIGHT_SPEAKER = 1,
  SOUND_RESERVED_CHANNELS = 2, // 2 channels reserved for left/right speaker
  SOUND_CENTER_SPEAKER = -1
};

/* Sound files: */
enum {
  SND_SKID,
  SND_DIAMOND,
  SND_HERRING,
  SND_BRICK,
  SND_SQUISH,
  SND_FALL,
  SND_RICOCHET,
  SND_BUMP_UPGRADE,
  SND_UPGRADE,
  SND_EXCELLENT,
  SND_COFFEE,
  SND_SHOOT,
  SND_LIFEUP,
  SND_STOMP,
  SND_KICK,
  SND_EXPLODE,
  SND_TELEPORT,
  SND_FALL_ON_GROUND,
  SND_MENU_SELECT_OPT,
  SND_FALL_OFF_SCREEN,
  SND_LEVEL_RESTART,
  SND_BOMB_EXPLODE,
  SND_FALL_ON_GROUND_SMALL,
  SND_WALKER3_FLATTEN,
  SND_IN_WATER,
  SND_BULLET_BOUNCING,
  SND_MENU_SELECT_OPT2,
  NUM_SOUNDS
};

extern char* soundfilenames[NUM_SOUNDS];

#include <string>
#include <SDL_mixer.h>

/* variables for stocking the sound and music */
extern Mix_Chunk* sounds[NUM_SOUNDS];

/* functions handling the sound and music */
int open_audio(int frequency, Uint16 format, int channels, int chunksize);
void close_audio( void );

Mix_Chunk * load_sound(const std::string& file);
void free_chunk(Mix_Chunk*chunk);
void play_sound(Mix_Chunk * snd, enum Sound_Speaker whichSpeaker);

#endif /*SUPERTURR_SOUND_H*/
