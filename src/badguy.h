//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
/////////////////////////////////////////
//  $Id$
// 
//  SuperTux
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//  Copyright (C) 2004 Tobias Glaesser <tobi.web@gmx.de>
//  Copyright (C) 2004 Matthias Braun <matze@braunis.de>
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#ifndef SUPERTURR_BADGUY_H
#define SUPERTURR_BADGUY_H

#include "SDL.h"
#include "defines.h"
#include "bitmask.h"
#include "type.h"
#include "timer.h"
#include "texture.h"
#include "physic.h"
#include "collision.h"
#include "sprite.h"

/* Bad guy kinds: */
enum BadGuyKind {
  BAD_WALKER2,
  BAD_LARGESPIKYBALL,
  BAD_WALKER3,
  BAD_WALKER3_COUNTDOWN,
  BAD_STALACTITE,
  BAD_SMALLSPIKYBALL,
  BAD_FISH,				// <------- zmien
  BAD_JUMPINGCREATURE,
  BAD_FLYWALKER3,
  BAD_CRAB,
  BAD_WALKER1,
  BAD_EXPLOSION,
  BAD_FLYWALKER2,
  BAD_SWIMWALKER2,
  BAD_GODSMONSTER,
  BAD_BIRD,
  BAD_BUMPED_WALKER1_LEFT,
  BAD_BUMPED_WALKER1_RIGHT,
  BAD_BUMPED_WALKER2_LEFT,
  BAD_BUMPED_WALKER2_RIGHT,
  BAD_BUMPED_WALKER3_LEFT,
  BAD_BUMPED_WALKER3_RIGHT,
  NUM_BadGuyKinds
};

BadGuyKind  badguykind_from_string(const std::string& str);
std::string badguykind_to_string(BadGuyKind kind);
void load_badguy_gfx();
void free_badguy_gfx();

class Player;

/* Badguy type: */
class BadGuy : public GameObject
{
public:
  /* Enemy modes: */
  enum BadGuyMode {
    NORMAL=0,
    FLAT,
    KICK,
    HELD,

    JUMPY_JUMP,

    BOMB_TICKING,
    BOMB_EXPLODE,

    STALACTITE_SHAKING,
    STALACTITE_FALL,

    FISH_WAIT,

    FLY_UP,
    FLY_DOWN,
    FLY_DOWN1,
        FLY_DOWN2,
            FLY_DOWN3,    
    STAY_UP,
    STAY_DOWN,

    SWIM_UPLEFT,
    SWIM_DOWNLEFT,
    SWIM_UPRIGHT,
    SWIM_DOWNRIGHT

  };
public:
  DyingType  dying;
  BadGuyKind kind;
  BadGuyMode mode;

  /** If true the enemy will stay on its current platform, ie. if he
      reaches the edge he will turn around and walk into the other
      direction, if false the enemy will jump or walk of the edge */
  bool stay_on_platform;

  Direction dir;

private:
  bool removable;
  bool seen;
  int squishcount; /// number of times this enemy was squiched
  Timer timer;
  Physic physic;

  Sprite*   sprite_left;
  Sprite*   sprite_right;

  int animation_offset;

public:
  BadGuy(float x, float y, BadGuyKind kind, bool stay_on_platform);

  void action(double frame_ratio);
  void draw();
  std::string type() { return "BadGuy"; };

  void explode(BadGuy* badguy);

  void collision(void* p_c_object, int c_object,
                 CollisionType type = COLLISION_NORMAL);

  /** this functions tries to kill the badguy and lets him fall off the
   * screen. Some badguys like the flame might ignore this.
   */
  void kill_me(int score);
  void kill_me2(int score);

  /** remove ourself from the list of badguys. WARNING! This function will
   * invalidate all members. So don't do anything else with member after calling
   * this.
   */
  void remove_me();  
  bool is_removable() const { return removable; }
 
private:
  void action_walker2(double frame_ratio);
  void action_largespikyball(double frame_ratio); 
  void action_walker3_countdown(double frame_ratio);					// <---- do zmiany
  void action_walker3(double frame_ratio);
  void action_stalactite(double frame_ratio);				// <--- do sprawdzenia
  void action_smallspikyball(double frame_ratio);
  void action_fish(double frame_ratio);					// <--- do zmiany
  void action_jumpingcreature(double frame_ratio);
  void action_flywalker3(double frame_ratio);
  void action_crab(double frame_ratio);
  void action_walker1(double frame_ratio);
  void action_explosion(double frame_ratio);				// <-- do sprawdzenia
  void action_flywalker2(double frame_ratio);
  void action_swimwalker2(double frame_ratio);
  void action_godsmonster(double frame_ratio);
  void action_bird(double frame_ratio);
  void action_bumped_walker1(double frame_ratio);
  void action_bumped_walker2(double frame_ratio);
  void action_bumped_walker3(double frame_ratio);

  /** handles falling down. disables gravity calculation when we're back on
   * ground */
  void fall();

  /** let the player jump a bit (used when you hit a badguy) */
  void make_player_jump(Player* player);

  /** check if we're running left or right in a wall and eventually change
   * direction
   */
  void check_horizontal_bump(bool checkcliff = false);
  /** called when we're bumped from below with a block */
  void bump();
  /** called when a player jumped on the badguy from above */
  void squish(Player* player);
  /** squish ourself, give player score and set dying to DYING_SQICHED */
  void squish_me(Player* player);
  /** set image of the badguy */
  void set_sprite(Sprite* left, Sprite* right);

  void check_horizontal_bump_swimwalker(bool checkcliff = false);
  void check_horizontal_bump_bird(bool checkcliff = false);
};

struct BadGuyData
{
  BadGuyKind kind;
  int x;
  int y;
  bool stay_on_platform;

  BadGuyData(BadGuy* pbadguy) : kind(pbadguy->kind), x((int)pbadguy->base.x), y((int)pbadguy->base.y), stay_on_platform(pbadguy->stay_on_platform)  {};
  BadGuyData(BadGuyKind kind_, int x_, int y_, bool stay_on_platform_) 
    : kind(kind_), x(x_), y(y_), stay_on_platform(stay_on_platform_) {}

  BadGuyData()
    : kind(BAD_WALKER1), x(0), y(0), stay_on_platform(false) {}
};

#endif /*SUPERTURR_BADGUY_H*/

/* Local Variables: */
/* mode:c++ */
/* End: */

