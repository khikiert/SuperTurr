//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
///////////////////////////////////////////  $Id$
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

#include "globals.h"
#include "scene.h"
#include "player.h"
#include "badguy.h"
#include "gameobjs.h"
#include "special.h"
#include "resources.h"
#include "sprite_manager.h"
#include "setup.h"
#include "level.h"
#include "world.h"


Surface* img_waves[3]; 
Surface* img_water;
Surface* img_pole;
Surface* img_poletop;
Surface* img_flag[2];
Surface* img_cloud[2][4];

//OSLONKA MusicRef herring_song;
MusicRef level_end_song;

SpriteManager* sprite_manager = 0;
MusicManager* music_manager = 0;

/* Load graphics/sounds shared between all levels: */
void loadshared()
{
  int i;

  sprite_manager = new SpriteManager(datadir + "/superturr.strf");
  music_manager = new MusicManager();
  music_manager->enable_music(use_music);

  /* Turris: */
  turriball_shield = sprite_manager->load("turriball-shield");
  turrican_shield = sprite_manager->load("turrican-shield");
  turriball_gameover = sprite_manager->load("turriball-gameover");

  turriball.stand_left  = sprite_manager->load("turriball-stop-left");
  turriball.stand_right = sprite_manager->load("turriball-stop-right");
  turriball.walk_left   = sprite_manager->load("turriball-move-left");
  turriball.walk_right  = sprite_manager->load("turriball-move-right");
  turriball.jump_left   = sprite_manager->load("turriball-jump-left");
  turriball.jump_right  = sprite_manager->load("turriball-jump-right");
  turriball.kick_left   = sprite_manager->load("turriball-kick-left");
  turriball.kick_right  = sprite_manager->load("turriball-kick-right");
  turriball.skid_left   = sprite_manager->load("turriball-skid-left");
  turriball.skid_right  = sprite_manager->load("turriball-skid-right");
  turriball.grab_left   = sprite_manager->load("turriball-grab-left");
  turriball.grab_right  = sprite_manager->load("turriball-grab-right");

  turrican.stand_left  = sprite_manager->load("turrican-stand-left");
  turrican.stand_right = sprite_manager->load("turrican-stand-right");
  turrican.walk_left   = sprite_manager->load("turrican-walk-left");
  turrican.walk_right  = sprite_manager->load("turrican-walk-right");
  turrican.jump_left   = sprite_manager->load("turrican-jump-left");
  turrican.jump_right  = sprite_manager->load("turrican-jump-right");
  turrican.kick_left   = sprite_manager->load("turrican-kick-left");
  turrican.kick_right  = sprite_manager->load("turrican-kick-right");
  turrican.skid_right  = sprite_manager->load("turrican-skid-right");
  turrican.skid_left   = sprite_manager->load("turrican-skid-left");
  turrican.grab_left   = sprite_manager->load("turrican-grab-left");
  turrican.grab_right  = sprite_manager->load("turrican-grab-right");
  turrican.duck_left   = sprite_manager->load("turrican-duck-left");
  turrican.duck_right  = sprite_manager->load("turrican-duck-right");

  turricanUpgrade.stand_left  = sprite_manager->load("turricanUpgrade-stand-left");
  turricanUpgrade.stand_right = sprite_manager->load("turricanUpgrade-stand-right");
  turricanUpgrade.walk_left   = sprite_manager->load("turricanUpgrade-walk-left");
  turricanUpgrade.walk_right  = sprite_manager->load("turricanUpgrade-walk-right");
  turricanUpgrade.jump_left   = sprite_manager->load("turricanUpgrade-jump-left");
  turricanUpgrade.jump_right  = sprite_manager->load("turricanUpgrade-jump-right");
  turricanUpgrade.kick_left   = sprite_manager->load("turricanUpgrade-kick-left");
  turricanUpgrade.kick_right  = sprite_manager->load("turricanUpgrade-kick-right");
  turricanUpgrade.skid_right  = sprite_manager->load("turricanUpgrade-skid-right");
  turricanUpgrade.skid_left   = sprite_manager->load("turricanUpgrade-skid-left");
  turricanUpgrade.grab_left   = sprite_manager->load("turricanUpgrade-grab-left");
  turricanUpgrade.grab_right  = sprite_manager->load("turricanUpgrade-grab-right");
  turricanUpgrade.duck_left   = sprite_manager->load("turricanUpgrade-duck-left");
  turricanUpgrade.duck_right  = sprite_manager->load("turricanUpgrade-duck-right");

  /* Water: */
  img_water = new Surface(datadir + "/images/shared/water.png", IGNORE_ALPHA);

  img_waves[0] = new Surface(datadir + "/images/shared/waves-0.png",
               USE_ALPHA);

  img_waves[1] = new Surface(datadir + "/images/shared/waves-1.png",
               USE_ALPHA);

  img_waves[2] = new Surface(datadir + "/images/shared/waves-2.png",
               USE_ALPHA);


  /* Pole: */

  img_pole = new Surface(datadir + "/images/shared/pole.png", USE_ALPHA);
  img_poletop = new Surface(datadir + "/images/shared/poletop.png",
               USE_ALPHA);


  /* Flag: */

  img_flag[0] = new Surface(datadir + "/images/shared/flag-0.png",
               USE_ALPHA);
  img_flag[1] = new Surface(datadir + "/images/shared/flag-1.png",
               USE_ALPHA);


  /* Cloud: */

  img_cloud[0][0] = new Surface(datadir + "/images/shared/cloud-00.png",
               USE_ALPHA);

  img_cloud[0][1] = new Surface(datadir + "/images/shared/cloud-01.png",
               USE_ALPHA);

  img_cloud[0][2] = new Surface(datadir + "/images/shared/cloud-02.png",
               USE_ALPHA);

  img_cloud[0][3] = new Surface(datadir + "/images/shared/cloud-03.png",
               USE_ALPHA);


  img_cloud[1][0] = new Surface(datadir + "/images/shared/cloud-10.png",
               USE_ALPHA);

  img_cloud[1][1] = new Surface(datadir + "/images/shared/cloud-11.png",
               USE_ALPHA);

  img_cloud[1][2] = new Surface(datadir + "/images/shared/cloud-12.png",
               USE_ALPHA);

  img_cloud[1][3] = new Surface(datadir + "/images/shared/cloud-13.png",
               USE_ALPHA);


  /* Bad guys: */
  load_badguy_gfx();

  /* Upgrades: */
  load_special_gfx();

  /* Diamonds: */
  img_diamond[0] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-1.png",
               USE_ALPHA);

  img_diamond[1] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-2.png",
               USE_ALPHA);

  img_diamond[2] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-3.png",
               USE_ALPHA);

  img_diamond[3] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-4.png",
               USE_ALPHA);

  img_diamond[4] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-5.png",
               USE_ALPHA);

  img_diamond[5] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-6.png",
               USE_ALPHA);

  img_diamond[6] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-5.png",
               USE_ALPHA);

  img_diamond[7] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-4.png",
               USE_ALPHA);

  img_diamond[8] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-3.png",
               USE_ALPHA);

  img_diamond[9] = new Surface(datadir + "/images/tilesets/superturr/diamond/diamond-2.png",
               USE_ALPHA);



  /* Tux life: */

//  tux_life = new Surface(datadir + "/images/shared/tux-life.png",
//                         USE_ALPHA);
  turri_lives = new Surface(datadir + "/images/shared/superturr/turri-lives.png",
                         USE_ALPHA);

  /* Sound effects: */

  /* if (use_sound) // this will introduce SERIOUS bugs here ! because "load_sound"
                    // initialize sounds[i] with the correct pointer's value:
                    // NULL or something else. And it will be dangerous to
                    // play with not-initialized pointers.
                    // This is also true with if (use_music)
                    Send a mail to me: neoneurone@users.sf.net, if you have another opinion. :)
  */
  for (i = 0; i < NUM_SOUNDS; i++)
    sounds[i] = load_sound(datadir + soundfilenames[i]);

  /* Herring song */
//OSLONKA  herring_song = music_manager->load_music(datadir + "/music/superturr/test.ogg");
//  level_end_song = music_manager->load_music(datadir + "/music/TURRICAN/turrican_chip_rmx.xm");
//  std::string muzyczka = World::get_level()->song_title.c_str();

//char str[100];
////  snprintf(str, sizeof(str), "%s", new_lev.song_title.c_str());
//  snprintf(str, sizeof(str), "%s", World::current()->get_level()->song_title.c_str());


//  level_end_song = music_manager->load_music(datadir + "/music/" + str);
//  level_end_song = music_manager->load_music(datadir + "/music/" + new_lev.song_title.c_str());
//  level_end_song = music_manager->load_music(datadir + "/music/" + Level().get_level_music());

//  level_end_song = music_manager->load_music(datadir + "/music/" + muzyczka);
}


/* Free shared data: */
void unloadshared(void)
{
  int i;

  free_special_gfx();
  free_badguy_gfx();

  delete img_water;
  for (i = 0; i < 3; i++)
    delete img_waves[i];

  delete img_pole;
  delete img_poletop;

  for (i = 0; i < 2; i++)
    delete img_flag[i];

  for (i = 0; i < 4; i++)
    {
      delete img_cloud[0][i];
      delete img_cloud[1][i];
    }

  for (i = 0; i < 10; i++)
    {
      delete img_diamond[i];
    }


  delete turri_lives;

  for (i = 0; i < NUM_SOUNDS; i++)
    free_chunk(sounds[i]);

  delete sprite_manager;
  sprite_manager = 0;
  delete music_manager;
  music_manager = 0;
}

/* EOF */
