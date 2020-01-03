//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
///////////////////////////////////////////  $Id$
//
//  SuperTux
//  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
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
	
#include <assert.h>
#include "globals.h"
#include "music_manager.h"
#include "musicref.h"
#include "sound.h"
#include "setup.h"

MusicManager::MusicManager()
  : current_music(0), music_enabled(true)
{ }

MusicManager::~MusicManager()
{
  if(audio_device)
    Mix_HaltMusic();
}

MusicRef
MusicManager::load_music(const std::string& file)
{
  if(!audio_device)
    return MusicRef(0);

  if(!exists_music(file))
    st_abort("Couldn't load musicfile ", file.c_str());

  std::map<std::string, MusicResource>::iterator i = musics.find(file);
  assert(i != musics.end());
  return MusicRef(& (i->second));
}

bool
MusicManager::exists_music(const std::string& file)
{
  if(!audio_device)
    return true;
  
  // song already loaded?
  std::map<std::string, MusicResource>::iterator i = musics.find(file);
  if(i != musics.end()) {
    return true;                                      
  }
  
  Mix_Music* song = Mix_LoadMUS(file.c_str());
  if(song == 0)
    return false;

  // insert into music list
  std::pair<std::map<std::string, MusicResource>::iterator, bool> result = 
    musics.insert(
        std::make_pair<std::string, MusicResource> (std::string(file), MusicResource()));
  MusicResource& resource = result.first->second;
  resource.manager = this;
  resource.music = song;

  return true;
}

void
MusicManager::free_music(MusicResource* )
{
  // TODO free music, currently we can't do this since SDL_mixer seems to have
  // some bugs if you load/free alot of mod files.  
}

void
MusicManager::play_music(const MusicRef& musicref, int loops)
{
// std::cout << "MusicManager::play_music() call" << "\n";
  if(!audio_device)
    return;

  if(musicref.music == 0 || current_music == musicref.music) {
//  std::cout << "return2 , musicref.music = " << musicref.music << "\n";
    return;
    }

  if(current_music) {
//std::cout << "if(current_music)..." << "\n";
    current_music->refcount--;
    }
  
  current_music = musicref.music;
  current_music->refcount++;
  
  if(music_enabled) {
// std::cout << "calling Mix_PlayMusic() from play_music() function in music_manager.cpp" << "\n";
	if (loops) {
    Mix_PlayMusic(current_music->music, loops);
    }
    
    }
}

void
MusicManager::halt_music()
{
  if(!audio_device)
    return;
  
  Mix_HaltMusic();
  
  if(current_music) {
    current_music->refcount--;
    if(current_music->refcount == 0)
      free_music(current_music);
    current_music = 0;
  }
}

void
MusicManager::enable_music(bool enable)
{
  if(!audio_device)
    return;

  if(enable == music_enabled)
    return;
  
  music_enabled = enable;
  if(music_enabled == false) {
    Mix_HaltMusic();
  } else {
    Mix_PlayMusic(current_music->music, -1);
  }
}

Uint32 MusicManager::music_length(const std::string& file)
{




//Mix_Chunk * mixchunk = Mix_LoadOGG(datadir + file);





//Uint32 points = 0;
//Uint32 frames = 0;
//int freq = 0;
//Uint16 fmt = 0;
//int chans = 0;
/* Chunks are converted to audio device format� */
//if (!Mix_QuerySpec(&freq, &fmt, &chans))
//return 0; /* never called Mix_OpenAudio()?! */

 /* bytes / samplesize == sample points */
// points = (chunk->alen / ((fmt & 0xFF) / 8));

 /* sample points / channels == sample frames */
// frames = (points / chans);

 /* (sample frames * 1000) / frequency == play length in ms */
// return (frames * 1000) / freq;
return 1;

}

MusicManager::MusicResource::~MusicResource()
{
  // buggy SDL_mixer :-/
  // Mix_FreeMusic(music);
}

