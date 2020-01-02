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

#include <iostream>
#include <math.h>

#include "globals.h"
#include "defines.h"
#include "badguy.h"
#include "scene.h"
#include "screen.h"
#include "world.h"
#include "tile.h"
#include "resources.h"
#include "sprite_manager.h"

Sprite* img_walker2_flatten_left;			// walker2 stojacy po naskoczeniu, walker2-walk-left
Sprite* img_walker2_flatten_right;			// wlaker2 stojacy po naskoczeniu, walker2-walk-right
Sprite* img_walker2_running_left;		// walker2 biegnacy po naskoczeniu, walker2-flat-left
Sprite* img_walker2_running_right;		// walker2 biegnacy po naskoczeniu, walker2-flat-right
Sprite* img_walker2_walking_left;				// walker2 idacy, walker2-flat-left
Sprite* img_walker2_walking_right;				// walker2 idacy, walker2-flat-right
Sprite* img_largespikyball_up;						// kolczasta kula skaczaca, ball.png
Sprite* img_largespikyball_down;					// kolczasta kula skaczaca, ball.png
Sprite* img_largespikyball_middle;					// kolczasta kula skaczaca, ball.png
Sprite* img_walker3_walking_left;				// walker3 idacy, walker3-walk-left-x
Sprite* img_walker3_walking_right;				// walker3 idacy, walker3-walk-right-x
Sprite* img_walker3_countdown_left;			// walker3 po naskoczniu, walker3-flat-left
Sprite* img_walker3_countdown_right;		// walker3 po naskoczeniu, walker3-flat-right
Sprite* img_walker3_exploding;					// walker3 wybuchajacy, walker_explosion2-x
Sprite* img_stalactite;								// stalaktyt wiszacy
Sprite* img_stalactite_broken;						// stalaktyt po upadku
Sprite* img_smallspikyball;						// kolczasta kula wirujaca wokol, turriflame-0
Sprite* img_fish;							// 
Sprite* img_fish_down;						// 
Sprite* img_jumpingcreature_left;				// grzybek skaczacy, grzybek-left-x
Sprite* img_jumpingcreature_right;				// grzybek skaczacy, grzybek-right-x
//Sprite* img_jumpingcreature_exploding;			// grzybek skaczacy zniszczony, st-explosion-x
Sprite* img_flywalker3_flying;					// walker t3 latajacy, flywalker-x
//Sprite* img_flywalker3_exploding;					// walker t3 latajacy zniszczony, st-explosion-x
Sprite* img_crab_walking_left;					// krab, krab-left-x
Sprite* img_crab_walking_right;					// krab, krab-right-x
Sprite* img_walker1_walking_left;					// walker idacy, walker1-walk-left-x
Sprite* img_walker1_walking_right;					// walker idacy, walker1-walk-right-x
Sprite* img_explosion;						// 
Sprite* img_flywalker2_flying_left;				// walker latajacy t2, flying_walker-left
Sprite* img_flywalker2_flying_right;			// walker latajacy t2, flying_walker-right
Sprite* img_swimwalker2_swimming_left;				// walker plywajacy, swimwalker-left-x
Sprite* img_swimwalker2_swimming_right;				// walker plywajacy, swimwalker-right-x
Sprite* img_godsmonster_walking_left;					// potworek z Godsow, gods-monster1-left-x
Sprite* img_godsmonster_walking_right;					// potworek z Godsow, gods-monster1-right-x
// Sprite* img_explosion_right;
Sprite* img_bird_flying;
Sprite* img_bumped_walker1_left;
Sprite* img_bumped_walker1_right;
Sprite* img_bumped_walker2_left;
Sprite* img_bumped_walker2_right;
Sprite* img_bumped_walker3_left;
Sprite* img_bumped_walker3_right;

#define BADGUY_WALK_SPEED .8f

BadGuyKind  badguykind_from_string(const std::string& str)
{
  if (str == "money" || str == "largespikyball") // was money in old maps
    return BAD_LARGESPIKYBALL;
  else if (str == "walker2" || str == "laptop" || str == "mriceblock") // was laptop in old maps
    return BAD_WALKER2;
  else if (str == "walker3" || str == "mrbomb")
    return BAD_WALKER3;
  else if (str == "stalactite")
    return BAD_STALACTITE;
  else if (str == "smallspikyball" || str == "flame")
    return BAD_SMALLSPIKYBALL;
  else if (str == "fish")
    return BAD_FISH;
  else if (str == "jumpingcreature" || str == "bouncingsnowball")
    return BAD_JUMPINGCREATURE;
  else if (str == "flywalker3" || str == "flyingsnowball")
    return BAD_FLYWALKER3;
  else if (str == "crab" || str == "spiky")
    return BAD_CRAB;
  else if (str == "walker1" || str == "bsod" || str == "snowball") // was bsod in old maps
    return BAD_WALKER1;
  else if (str == "flywalker2")
    return BAD_FLYWALKER2;
  else if (str == "swimwalker2")
    return BAD_SWIMWALKER2;
  else if (str == "godsmonster")
    return BAD_GODSMONSTER;
  else if (str == "bird")
  	return BAD_BIRD;
  else if (str == "bumped_walker1_left")
    return BAD_BUMPED_WALKER1_LEFT;
  else if (str == "bumped_walker1_right")
    return BAD_BUMPED_WALKER1_RIGHT;
  else if (str == "bumped_walker2_left")
    return BAD_BUMPED_WALKER2_LEFT;
  else if (str == "bumped_walker2_right")
    return BAD_BUMPED_WALKER2_RIGHT;
  else if (str == "bumped_walker3_left")
    return BAD_BUMPED_WALKER3_LEFT;
  else if (str == "bumped_walker3_right")
    return BAD_BUMPED_WALKER3_RIGHT;
  else
    {
      printf("Couldn't convert badguy: '%s'\n", str.c_str());
      return BAD_WALKER1;
    }
}

std::string badguykind_to_string(BadGuyKind kind)
{
  switch(kind)
    {
    case BAD_LARGESPIKYBALL:
      return "largespikyball";
      break;
    case BAD_WALKER2:
      return "walker2";
      break;
    case BAD_WALKER3:
      return "walker3";
      break;
    case BAD_STALACTITE:
      return "stalactite";
      break;
    case BAD_SMALLSPIKYBALL:
      return "smallspikyball";
      break;
    case BAD_FISH:
      return "fish";
      break;
    case BAD_JUMPINGCREATURE:
      return "jumpingcreature";
      break;
    case BAD_FLYWALKER3:
      return "flywalker3";
      break;
    case BAD_CRAB:
      return "crab";
      break;
    case BAD_WALKER1:
      return "walker1";
      break;
    case BAD_FLYWALKER2:
      return "flywalker2";
      break;
    case BAD_SWIMWALKER2:
      return "swimwalker2";
      break;
    case BAD_GODSMONSTER:
      return "godsmonster";
      break;
  	case BAD_BIRD:
  	    return "bird";
  	case BAD_BUMPED_WALKER1_LEFT:
        return "bumped_walker1_left";
  	case BAD_BUMPED_WALKER1_RIGHT:
        return "bumped_walker1_right";
  	case BAD_BUMPED_WALKER2_LEFT:
        return "bumped_walker2_left";
  	case BAD_BUMPED_WALKER2_RIGHT:
        return "bumped_walker2_right";
  	case BAD_BUMPED_WALKER3_LEFT:
        return "bumped_walker3_left";
  	case BAD_BUMPED_WALKER3_RIGHT:
        return "bumped_walker3_right";
    default:
      return "walker1";
    }
}

BadGuy::BadGuy(float x, float y, BadGuyKind kind_, bool stay_on_platform_)
  : removable(false), squishcount(0)
{
  base.x   = x;
  base.y   = y;    
  base.width  = 0;
  base.height = 0;
  base.xm  = 0;
  base.ym  = 0;

  stay_on_platform = stay_on_platform_;
  mode     = NORMAL;
  dying    = DYING_NOT;
  kind     = kind_;
  old_base = base;
  dir      = LEFT;
  seen     = false;
  animation_offset = 0;
  sprite_left = sprite_right = 0;
  physic.reset();
  timer.init(true);

  if(kind == BAD_WALKER3) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_walker3_walking_left, img_walker3_walking_right);
  } else if (kind == BAD_WALKER2) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_walker2_walking_left, img_walker2_walking_right);
  } else if(kind == BAD_LARGESPIKYBALL) {
    set_sprite(img_largespikyball_up, img_largespikyball_up);
  } else if(kind == BAD_WALKER3_COUNTDOWN) {
    set_sprite(img_walker3_countdown_left, img_walker3_countdown_right);
    // hack so that the bomb doesn't hurt until it expldes...
    dying = DYING_SQUISHED;
  } else if(kind == BAD_EXPLOSION) {
    physic.set_velocity(0, 0);
    set_sprite(img_explosion, img_explosion);
    // hack so that the bomb doesn't hurt until it expldes...
    dying = DYING_SQUISHED;
  } else if(kind == BAD_SMALLSPIKYBALL) {
    base.ym = 0; // we misuse base.ym as angle for the flame
    physic.enable_gravity(false);
    set_sprite(img_smallspikyball, img_smallspikyball);
  } else if(kind == BAD_JUMPINGCREATURE) {
    physic.set_velocity(-1.3, 0);
    set_sprite(img_jumpingcreature_left, img_jumpingcreature_right);
  } else if(kind == BAD_STALACTITE) {
    physic.enable_gravity(false);
    set_sprite(img_stalactite, img_stalactite);
  } else if(kind == BAD_FISH) {
    set_sprite(img_fish, img_fish);
    physic.enable_gravity(true);
  } else if(kind == BAD_FLYWALKER3) {
    set_sprite(img_flywalker3_flying, img_flywalker3_flying);
    physic.enable_gravity(false);
  } else if(kind == BAD_CRAB) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_crab_walking_left, img_crab_walking_right);
  } else if(kind == BAD_WALKER1) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_walker1_walking_left, img_walker1_walking_right);
  } else if(kind == BAD_FLYWALKER2) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_flywalker2_flying_left, img_flywalker2_flying_right);
    physic.enable_gravity(false);
  } else if(kind == BAD_SWIMWALKER2) {
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_swimwalker2_swimming_left, img_swimwalker2_swimming_right);
    physic.enable_gravity(false);
  } else if(kind == BAD_GODSMONSTER) {
    physic.set_velocity(-0.5, 0);
    set_sprite(img_godsmonster_walking_left, img_godsmonster_walking_right);
  }
  else if (kind == BAD_BIRD) {
//  	physic.set_velocity(-1.0, 0);
//  	set_sprite(img_bird_flying_left, img_bird_flying_right);
    physic.set_velocity(-BADGUY_WALK_SPEED, 0);
    set_sprite(img_bird_flying, img_bird_flying);
    physic.enable_gravity(false);
  }
  else if (kind == BAD_BUMPED_WALKER1_LEFT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker1_left, img_bumped_walker1_left);
  }
  else if (kind == BAD_BUMPED_WALKER1_RIGHT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker1_right, img_bumped_walker1_right);
  }
  else if (kind == BAD_BUMPED_WALKER2_LEFT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker2_left, img_bumped_walker2_left);
  }
  else if (kind == BAD_BUMPED_WALKER2_RIGHT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker2_right, img_bumped_walker2_right);
  }
  else if (kind == BAD_BUMPED_WALKER3_LEFT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker3_left, img_bumped_walker3_left);
  }
  else if (kind == BAD_BUMPED_WALKER3_RIGHT) {
  	physic.set_velocity(0, 0);
  	set_sprite(img_bumped_walker3_right, img_bumped_walker3_right);
  }


  // if we're in a solid tile at start correct that now
  if(kind != BAD_SMALLSPIKYBALL && kind != BAD_FISH && collision_object_map(base)) 
    {
      std::cout << "Warning: badguy started in wall: kind: " << badguykind_to_string(kind) 
                << " pos: (" << base.x << ", " << base.y << ")" << std::endl;
      while(collision_object_map(base))
        --base.y;
    }
}

 void
 BadGuy::action_walker2(double frame_ratio)
 {
   Player& turr = *World::current()->get_turr();

  if(mode != HELD)
    fall();
  
  /* Move left/right: */
  if (mode != HELD)
    {
      // move
      physic.apply(frame_ratio, base.x, base.y);
      if (dying != DYING_FALLING)
        collision_swept_object_map(&old_base,&base);
    }
  else if (mode == HELD)
    { /* FIXME: The pbad object shouldn't know about pplayer objects. */
      /* If we're holding the iceblock */
      dir = turr.dir;
      if(dir==RIGHT)
        {
          base.x = turr.base.x + 16;
          base.y = turr.base.y + turr.base.height/1.5 - base.height;
        }
      else /* facing left */
        {
          base.x = turr.base.x - 16;
          base.y = turr.base.y + turr.base.height/1.5 - base.height;
        }
      if(collision_object_map(base))
        {
          base.x = turr.base.x;
          base.y = turr.base.y + turr.base.height/1.5 - base.height;
        }

      if(turr.input.fire != DOWN) /* SHOOT! */
        {
          if(dir == LEFT)
            base.x -= 24;
          else
            base.x += 24;
          old_base = base;

          mode=KICK;
          turr.kick_timer.start(KICKING_TIME);
          set_sprite(img_walker2_flatten_left, img_walker2_flatten_right);
          physic.set_velocity_x((dir == LEFT) ? -3.5 : 3.5);
          play_sound(sounds[SND_KICK], SOUND_CENTER_SPEAKER);
        }
    }

  if (!dying)
    {
      int changed = dir;
      check_horizontal_bump();
      if(mode == KICK && changed != dir)
        {
          /* handle stereo sound (number 10 should be tweaked...)*/
          if (base.x < scroll_x + screen->w/2 - 10)
            play_sound(sounds[SND_RICOCHET], SOUND_LEFT_SPEAKER);
          else if (base.x > scroll_x + screen->w/2 + 10)
            play_sound(sounds[SND_RICOCHET], SOUND_RIGHT_SPEAKER);
          else
            play_sound(sounds[SND_RICOCHET], SOUND_CENTER_SPEAKER);
        }
    }

  /* Handle mode timer: */
  if (mode == FLAT)
    {
      if(!timer.check())
        {
          mode = NORMAL;
          set_sprite(img_walker2_walking_left, img_walker2_walking_right);
          physic.set_velocity( (dir == LEFT) ? -.8 : .8, 0);
        }
    }
 }

void
BadGuy::check_horizontal_bump(bool checkcliff)
{
    float halfheight = base.height / 2;
    if (dir == LEFT && issolid( base.x, (int) base.y + halfheight))
    {
        if (kind == BAD_WALKER2 && mode == KICK)
            World::current()->trybreakbrick(base.x, base.y + halfheight, false, dir);
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if (dir == RIGHT && issolid( base.x + base.width, (int)base.y + halfheight))
    {
        if (kind == BAD_WALKER2 && mode == KICK)
            World::current()->trybreakbrick(base.x + base.width, (int) base.y + halfheight, false, dir);
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }

    // don't check for cliffs when we're falling
    if(!checkcliff)
        return;
    if(!issolid(base.x + base.width/2, base.y + base.height))
        return;
    
    if(dir == LEFT && !issolid(base.x, (int) base.y + base.height + halfheight))
    {
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if(dir == RIGHT && !issolid(base.x + base.width,
                (int) base.y + base.height + halfheight))
    {
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
}

void
BadGuy::check_horizontal_bump_swimwalker(bool checkcliff)
{
    float halfheight = base.height / 2;
    if (dir == LEFT && issolid( base.x, (int) base.y + halfheight))
    {
        if (mode == SWIM_UPLEFT) mode = SWIM_UPRIGHT;
        else if (mode == SWIM_DOWNLEFT) mode = SWIM_DOWNRIGHT;
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if (dir == RIGHT && issolid( base.x + 57, (int)base.y + halfheight))
    {
        if (mode == SWIM_UPRIGHT) mode = SWIM_UPLEFT;
        else if (mode == SWIM_DOWNRIGHT) mode = SWIM_DOWNLEFT;
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }

    // don't check for cliffs when we're falling
    if(!checkcliff)
        return;
    if(!issolid(base.x + 28, base.y + base.height))
        return;
    
    if(dir == LEFT && !issolid(base.x, (int) base.y + base.height + halfheight))
    {
        if (mode == SWIM_UPLEFT) mode = SWIM_UPRIGHT;
        else if (mode == SWIM_DOWNLEFT) mode = SWIM_DOWNRIGHT;
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if(dir == RIGHT && !issolid(base.x + 57,
                (int) base.y + base.height + halfheight))
    {
        if (mode == SWIM_UPRIGHT) mode = SWIM_UPLEFT;
        else if (mode == SWIM_DOWNRIGHT) mode = SWIM_DOWNLEFT;
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
}

void
BadGuy::check_horizontal_bump_bird(bool checkcliff)
{
    float halfheight = base.height / 2;
    if (dir == LEFT && issolid( base.x, (int) base.y + halfheight))
    {
//        if (mode == SWIMUPLEFT) mode = SWIM_UPRIGHT;
//        else if (mode == SWIM_DOWNLEFT) mode = SWIM_DOWNRIGHT;
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if (dir == RIGHT && issolid( base.x + 57, (int)base.y + halfheight))
    {
//        if (mode == SWIM_UPRIGHT) mode = SWIM_UPLEFT;
//        else if (mode == SWIM_DOWNRIGHT) mode = SWIM_DOWNLEFT;
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }

    // don't check for cliffs when we're falling
    if(!checkcliff)
        return;
    if(!issolid(base.x + 28, base.y + base.height))
        return;
    
    if(dir == LEFT && !issolid(base.x, (int) base.y + base.height + halfheight))
    {
  //      if (mode == SWIM_UPLEFT) mode = SWIM_UPRIGHT;
//        else if (mode == SWIM_DOWNLEFT) mode = SWIM_DOWNRIGHT;
        dir = RIGHT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
    if(dir == RIGHT && !issolid(base.x + 57,
                (int) base.y + base.height + halfheight))
    {
  //      if (mode == SWIM_UPRIGHT) mode = SWIM_UPLEFT;
//        else if (mode == SWIM_DOWNRIGHT) mode = SWIM_DOWNLEFT;
        dir = LEFT;
        physic.set_velocity(-physic.get_velocity_x(), physic.get_velocity_y());
        return;
    }
}

















void
BadGuy::fall()
{
  /* Fall if we get off the ground: */
  if (dying != DYING_FALLING)
    {
      if (!issolid(base.x+base.width/2, base.y + base.height))
        {
          if (isturriwater(base.x+base.width/2, base.y + base.height)) {
            physic.set_velocity_y(-0.5);
            if (physic.get_velocity_x() > 0) physic.set_velocity_x(0.5);
            else if (physic.get_velocity_x() < 0) physic.set_velocity_x(-0.5);
          }
          // not solid below us? enable gravity
          else physic.enable_gravity(true);
        }
      else
        {
          /* Land: */
          if (physic.get_velocity_y() < 0)
            {
              base.y = int((base.y + base.height)/32) * 32 - base.height;
              physic.set_velocity_y(0);
            }
          // no gravity anymore please
          physic.enable_gravity(false);

          if (stay_on_platform && mode == NORMAL)
            {
              if (!issolid(base.x + ((dir == LEFT) ? 0 : base.width),
                           base.y + base.height))
                {
                  if (dir == LEFT)
                  {
                    dir = RIGHT;
                    physic.set_velocity_x(fabsf(physic.get_velocity_x()));
                } 
                  else
                  {
                    dir = LEFT;
                    physic.set_velocity_x(-fabsf(physic.get_velocity_x()));
                  }
                }
            }
        }
    }
  else
    {
      physic.enable_gravity(true);
    }
}

void
BadGuy::remove_me()
{
  removable = true;
}

void
BadGuy::action_largespikyball(double frame_ratio)
{
  const float vy = physic.get_velocity_y();

  // XXX: These tests *should* use location from ground, not velocity
  if (fabsf(vy) > 5.6f)
    set_sprite(img_largespikyball_down, img_largespikyball_down);
  else if (fabsf(vy) > 5.3f)
    set_sprite(img_largespikyball_middle, img_largespikyball_middle);
  else
    set_sprite(img_largespikyball_up, img_largespikyball_up);

  Player& turr = *World::current()->get_turr();

  static const float JUMPV = 6;
    
  fall();
  // jump when on ground
  if(dying == DYING_NOT && issolid(base.x, base.y+32))
    {
      physic.set_velocity_y(JUMPV);
      physic.enable_gravity(true);

      mode = JUMPY_JUMP;
    }
  else if(mode == JUMPY_JUMP)
    {
      mode = NORMAL;
    }

  // set direction based on Turri
  if(turr.base.x > base.x)
    dir = RIGHT;
  else
    dir = LEFT;

  // move
  physic.apply(frame_ratio, base.x, base.y);
  if(dying == DYING_NOT)
    collision_swept_object_map(&old_base, &base);
}

void
BadGuy::action_walker3(double frame_ratio)
{
  if (dying == DYING_NOT)
    check_horizontal_bump(true);

  fall();

  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base); 
}

void
BadGuy::action_walker3_countdown(double frame_ratio)
{
  static const int TICKINGTIME = 1000;
  static const int EXPLODETIME = 1000;
    
  fall();

  if(mode == NORMAL) {
    mode = BOMB_TICKING;
    timer.start(TICKINGTIME);
  } else if(!timer.check()) {
    if(mode == BOMB_TICKING) {
      mode = BOMB_EXPLODE;
      set_sprite(img_walker3_exploding, img_walker3_exploding);
      dying = DYING_NOT; // now the bomb hurts
      timer.start(EXPLODETIME);

      /* play explosion sound */  // FIXME: is the stereo all right? maybe we should use player cordinates...
      if (base.x < scroll_x + screen->w/2 - 10)
        play_sound(sounds[SND_BOMB_EXPLODE], SOUND_LEFT_SPEAKER);
      else if (base.x > scroll_x + screen->w/2 + 10)
        play_sound(sounds[SND_BOMB_EXPLODE], SOUND_RIGHT_SPEAKER);
      else
        play_sound(sounds[SND_BOMB_EXPLODE], SOUND_CENTER_SPEAKER);

    } else if(mode == BOMB_EXPLODE) {
      remove_me();
      return;
    }
  }

  // move
  physic.apply(frame_ratio, base.x, base.y);                 
  collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_stalactite(double frame_ratio)
{
  Player& turr = *World::current()->get_turr();

  static const int SHAKETIME = 800;
  static const int RANGE = 40;
    
  if(mode == NORMAL) {
    // start shaking when turr is below the stalactite and at least 40 pixels
    // near
    if(turr.base.x + 32 > base.x - RANGE && turr.base.x < base.x + 32 + RANGE
            && turr.base.y + turr.base.height > base.y) {
      timer.start(SHAKETIME);
      mode = STALACTITE_SHAKING;
    }
  } if(mode == STALACTITE_SHAKING) {
    base.x = old_base.x + (rand() % 6) - 3; // TODO this could be done nicer...
    if(!timer.check()) {
      mode = STALACTITE_FALL;
    }
  } else if(mode == STALACTITE_FALL) {
    fall();
    /* Destroy if we collides with land */
    if(issolid(base.x+base.width/2, base.y+base.height))
    {
      timer.start(2000);
      dying = DYING_SQUISHED;
      mode = FLAT;
      set_sprite(img_stalactite_broken, img_stalactite_broken);
    }
  } else if(mode == FLAT) {
    fall();
  }

  // move
  physic.apply(frame_ratio, base.x, base.y);

//  if(dying == DYING_SQUISHED && !timer.check())
//    remove_me();
}

void
BadGuy::action_smallspikyball(double frame_ratio)
{
    static const float radius = 100;
    static const float speed = 0.02;
    base.x = old_base.x + cos(base.ym) * radius;
    base.y = old_base.y + sin(base.ym) * radius;

//    base.ym = fmodf(base.ym + frame_ratio * speed, 2*M_PI);
    base.ym = fmod(base.ym + frame_ratio * speed, 2*M_PI);
}

void
BadGuy::action_fish(double frame_ratio)
{
  static const float JUMPV = 6;
  static const int WAITTIME = 1000;
    
  // go in wait mode when back in water
  if(dying == DYING_NOT && gettile(base.x, base.y+ base.height)->water
        && physic.get_velocity_y() <= 0 && mode == NORMAL)
    {
      mode = FISH_WAIT;
      set_sprite(0, 0);
      physic.set_velocity(0, 0);
      physic.enable_gravity(false);
      timer.start(WAITTIME);
    }
  else if(mode == FISH_WAIT && !timer.check())
    {
      // jump again
      set_sprite(img_fish, img_fish);
      mode = NORMAL;
      physic.set_velocity(0, JUMPV);
      physic.enable_gravity(true);
    }

  physic.apply(frame_ratio, base.x, base.y);
  if(dying == DYING_NOT)
    collision_swept_object_map(&old_base, &base);

  if(physic.get_velocity_y() < 0)
    set_sprite(img_fish_down, img_fish_down);
}

void
BadGuy::action_jumpingcreature(double frame_ratio)
{
  static const float JUMPV = 4.5;
    
  fall();

  // jump when on ground
  if(dying == DYING_NOT && issolid(base.x, base.y+32))
    {
      physic.set_velocity_y(JUMPV);
      physic.enable_gravity(true);
    }                                                     
  else
    {
      mode = NORMAL;
    }

  // check for right/left collisions
  check_horizontal_bump();

  physic.apply(frame_ratio, base.x, base.y);
  if(dying == DYING_NOT)
    collision_swept_object_map(&old_base, &base);

  // Handle dying timer:
  if (dying == DYING_SQUISHED && !timer.check())
    {
      /* Remove it if time's up: */
      remove_me();
      return;
    }
}

void
BadGuy::action_flywalker3(double frame_ratio)
{
  static const float FLYINGSPEED = 1;
  static const int DIRCHANGETIME = 1000;
    
  // go into flyup mode if none specified yet
  if(dying == DYING_NOT && mode == NORMAL) {
    mode = FLY_UP;
    physic.set_velocity_y(FLYINGSPEED);
    timer.start(DIRCHANGETIME/2);
  }

  if(dying == DYING_NOT && !timer.check()) {
    if(mode == FLY_UP) {
      mode = FLY_DOWN;
      physic.set_velocity_y(-FLYINGSPEED);
    } else if(mode == FLY_DOWN) {
      mode = FLY_UP;
      physic.set_velocity_y(FLYINGSPEED);
    }
    timer.start(DIRCHANGETIME);
  }

  if(dying != DYING_NOT)
    physic.enable_gravity(true);

  physic.apply(frame_ratio, base.x, base.y);
  if(dying == DYING_NOT || dying == DYING_SQUISHED)
    collision_swept_object_map(&old_base, &base);

  // Handle dying timer:
  if (dying == DYING_SQUISHED && !timer.check())
    {
      /* Remove it if time's up: */
      remove_me();
      return;
    }                                                          
}

void
BadGuy::action_crab(double frame_ratio)
{
  if (dying == DYING_NOT)
    check_horizontal_bump();

  fall();
#if 0
  // jump when we're about to fall
  if (physic.get_velocity_y() == 0 && 
          !issolid(base.x+base.width/2, base.y + base.height)) {
    physic.enable_gravity(true);
    physic.set_velocity_y(2);
  }
#endif

  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);   
}





















void
BadGuy::action_walker1(double frame_ratio)
{
  if (dying == DYING_NOT)
    check_horizontal_bump();

  fall();

  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_flywalker2(double frame_ratio)
{
  static const float FLYINGSPEED = 0.5;
  static const int DIRCHANGETIME = 150;
  static const int DIRCHANGETIME2 = 75;
    
  // go into flyup mode if none specified yet
  if(dying == DYING_NOT && mode == NORMAL) {
    mode = FLY_UP;
    physic.set_velocity_y(FLYINGSPEED);
    timer.start(DIRCHANGETIME/2);
  }

  if(dying == DYING_NOT && !timer.check()) {
    if(mode == FLY_UP) {
      mode = STAY_UP;
      physic.set_velocity_y(0);
      timer.start(DIRCHANGETIME2);
    } else if (mode == FLY_DOWN) {
      mode = STAY_DOWN;
      physic.set_velocity_y(0);
      timer.start(DIRCHANGETIME2);
    } else if(mode == STAY_UP) {
      mode = FLY_DOWN;
      physic.set_velocity_y(-FLYINGSPEED);
      timer.start(DIRCHANGETIME);
    } else if(mode == STAY_DOWN) {
      mode = FLY_UP;
      physic.set_velocity_y(FLYINGSPEED);
      timer.start(DIRCHANGETIME);
    }
  }

  if (dying == DYING_NOT)
    check_horizontal_bump();


  fall();

  if(dying == DYING_NOT) {
//      physic.set_velocity_y(0);
      physic.enable_gravity(false);
    }                                                     


  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_swimwalker2(double frame_ratio)
{
  // go into flyup mode if none specified yet

  if (dying == DYING_NOT) {
    if (mode == NORMAL) mode = SWIM_UPLEFT;
  }

  if (dying == DYING_NOT && mode == SWIM_UPLEFT) {
    if (!isturriwater(base.x - 1,base.y - 1)) {
      physic.set_velocity_x(-0.5);
      physic.set_velocity_y(-0.5);
      mode = SWIM_DOWNLEFT;
    }
    else {
      physic.set_velocity_x(-0.5);
      physic.set_velocity_y(0.5);
    }
  }
  else if (dying == DYING_NOT && mode == SWIM_DOWNLEFT) {
    if (!isturriwater(base.x - 1,base.y + 45)) {
      physic.set_velocity_x(-0.5);
      physic.set_velocity_y(0.5);
      mode = SWIM_UPLEFT;
    }
    else {
      physic.set_velocity_x(-0.5);
      physic.set_velocity_y(-0.5);
    }
  }
  else if (dying == DYING_NOT && mode == SWIM_UPRIGHT) {
    if (!isturriwater(base.x + 57,base.y - 1)) {
      physic.set_velocity_x(0.5);
      physic.set_velocity_y(-0.5);
      mode = SWIM_DOWNRIGHT;
    }
    else {
      physic.set_velocity_x(0.5);
      physic.set_velocity_y(0.5);
    }
  }
  else if (dying == DYING_NOT && mode == SWIM_DOWNRIGHT) {
    if (!isturriwater(base.x + 57,base.y + 45)) {
      physic.set_velocity_x(0.5);
      physic.set_velocity_y(0.5);
      mode = SWIM_UPRIGHT;
    }
    else {
      physic.set_velocity_x(0.5);
      physic.set_velocity_y(-0.5);
    }
  }

  if (dying == DYING_NOT) check_horizontal_bump_swimwalker();

  if(dying == DYING_NOT) {
      physic.enable_gravity(false);
  }                                                     


  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_godsmonster(double frame_ratio)
{
  if (dying == DYING_NOT)
    check_horizontal_bump();

  fall();

  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_bird(double frame_ratio)
{
  static const float FLYINGSPEED = 1.0;
  static const int DIRCHANGETIME = 170;
  static const int DIRCHANGETIME2 = 340;
  static const int DIRCHANGETIME3 = 240;
    
  // go into flyup mode if none specified yet
  if(dying == DYING_NOT && mode == NORMAL) {
    mode = FLY_UP;
	physic.set_velocity_x(-1.3);
//		physic.set_velocity_x(0);
    physic.set_velocity_y(FLYINGSPEED / 2);
    timer.start(DIRCHANGETIME * 3);
  }

  if(dying == DYING_NOT && !timer.check()) {
    if(mode == FLY_UP) {
      mode = STAY_UP;
      physic.set_velocity_y(0);
      timer.start(DIRCHANGETIME2);
    } else if(mode == STAY_UP) {
      mode = FLY_DOWN1;
      physic.set_velocity_y(-FLYINGSPEED / 2);
      timer.start(DIRCHANGETIME);
    } else if (mode == FLY_DOWN1) {
      mode = FLY_DOWN2;
      physic.set_velocity_y(-FLYINGSPEED / 2);
      timer.start(DIRCHANGETIME);
    } else if (mode == FLY_DOWN2) {
      mode = FLY_DOWN3;
      physic.set_velocity_y(-FLYINGSPEED / 2);
      timer.start(DIRCHANGETIME);
    } else if (mode == FLY_DOWN3) {
      mode = STAY_DOWN;
      physic.set_velocity_y(0);
      timer.start(DIRCHANGETIME3);
    } else if(mode == STAY_DOWN) {
      mode = FLY_UP;
      physic.set_velocity_y(FLYINGSPEED / 2);
      timer.start(DIRCHANGETIME * 3);
    }
  }

  if (dying == DYING_NOT)
    check_horizontal_bump_bird();


  fall();

  if(dying == DYING_NOT) {
//      physic.set_velocity_y(0);
      physic.enable_gravity(false);
    }                                                     


  physic.apply(frame_ratio, base.x, base.y);
  if (dying != DYING_FALLING)
    collision_swept_object_map(&old_base,&base);
}














void
BadGuy::action_explosion(double frame_ratio)
{
								  static const int TICKINGTIME = 528;
  static const int EXPLODETIME = 0;
    
  fall();

  if(mode == NORMAL) {
    mode = BOMB_TICKING;
    timer.start(TICKINGTIME);
  } else if(!timer.check()) {
    if(mode == BOMB_TICKING) {
      mode = BOMB_EXPLODE;
      set_sprite(img_explosion, img_explosion);
      dying = DYING_SQUISHED; 
      timer.start(EXPLODETIME);

//      /* play explosion sound */  // FIXME: is the stereo all right? maybe we should use player cordinates...
//      if (base.x < scroll_x + screen->w/2 - 10)
//        play_sound(sounds[SND_EXPLODE], SOUND_LEFT_SPEAKER);
//      else if (base.x > scroll_x + screen->w/2 + 10)
//        play_sound(sounds[SND_EXPLODE], SOUND_RIGHT_SPEAKER);
//      else
//        play_sound(sounds[SND_EXPLODE], SOUND_CENTER_SPEAKER);

    } else if(mode == BOMB_EXPLODE) {
      remove_me();
      return;
    }
  }

  // move
  physic.set_velocity_y(0);
  physic.set_velocity(0, 0);  
  physic.apply(frame_ratio, base.x, base.y);                 
  collision_swept_object_map(&old_base,&base);
}

void
BadGuy::action_bumped_walker1(double frame_ratio)
{
	check_horizontal_bump();
	fall();
	physic.apply(frame_ratio, base.x, base.y);
}
void
BadGuy::action_bumped_walker2(double frame_ratio)
{
	check_horizontal_bump();
	fall();
	physic.apply(frame_ratio, base.x, base.y);
}
void
BadGuy::action_bumped_walker3(double frame_ratio)
{
	check_horizontal_bump();
	fall();
	physic.apply(frame_ratio, base.x, base.y);
}















void
BadGuy::action(double frame_ratio)
{
  // Remove if it's far off the screen:
  if (base.x < scroll_x - OFFSCREEN_DISTANCE)
    {
      remove_me();                                                
      return;
    }

  // BadGuy fall below the ground
  if (base.y > screen->h) {
    remove_me();
    return;
  }

  // Once it's on screen, it's activated!
  if (base.x <= scroll_x + screen->w + OFFSCREEN_DISTANCE)
    seen = true;

  if(!seen)
    return;

  switch (kind)
    {
    case BAD_WALKER2:
      action_walker2(frame_ratio);
      break;
  
    case BAD_LARGESPIKYBALL:
      action_largespikyball(frame_ratio);
      break;

    case BAD_WALKER3:
      action_walker3(frame_ratio);
      break;
    
    case BAD_WALKER3_COUNTDOWN:
      action_walker3_countdown(frame_ratio);
      break;

    case BAD_EXPLOSION:
      action_explosion(frame_ratio);
      break;

    case BAD_STALACTITE:
      action_stalactite(frame_ratio);
      break;

    case BAD_SMALLSPIKYBALL:
      action_smallspikyball(frame_ratio);
      break;

    case BAD_FISH:
      action_fish(frame_ratio);
      break;

    case BAD_JUMPINGCREATURE:
      action_jumpingcreature(frame_ratio);
      break;

    case BAD_FLYWALKER3:
      action_flywalker3(frame_ratio);
      break;

    case BAD_CRAB:
      action_crab(frame_ratio);
      break;

    case BAD_WALKER1:
      action_walker1(frame_ratio);
      break;

    case BAD_FLYWALKER2:
      action_flywalker2(frame_ratio);
      break;

    case BAD_SWIMWALKER2:
      action_swimwalker2(frame_ratio);
      break;
    case BAD_GODSMONSTER:
      action_godsmonster(frame_ratio);
      break;
    case BAD_BIRD:
    	action_bird(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER1_LEFT:
    	action_bumped_walker1(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER1_RIGHT:
    	action_bumped_walker1(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER2_LEFT:
    	action_bumped_walker2(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER2_RIGHT:
    	action_bumped_walker2(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER3_LEFT:
    	action_bumped_walker3(frame_ratio);
    	break;
    case BAD_BUMPED_WALKER3_RIGHT:
    	action_bumped_walker3(frame_ratio);
    	break;
    default:
      break;
    }
}

void
BadGuy::draw()
{
  // Don't try to draw stuff that is outside of the screen
  if(base.x <= scroll_x - base.width || base.x >= scroll_x + screen->w)
    return;
  
  if(sprite_left == 0 || sprite_right == 0)
    {
      return;
    }

  Sprite* sprite = (dir == LEFT) ? sprite_left : sprite_right;
  sprite->draw(base.x - scroll_x, base.y);

  if (debug_mode)
    fillrect(base.x - scroll_x, base.y, base.width, base.height, 75,0,75, 150);
}

void
BadGuy::set_sprite(Sprite* left, Sprite* right) 
{
  if (1)
    {
      base.width = 32;
      base.height = 32;
    }
  else
    {
      // FIXME: Using the image size for the physics and collision is
      // a bad idea, since images should always overlap there physical
      // representation
      if(left != 0) {
        if(base.width == 0 && base.height == 0) {
          base.width  = left->get_width();
          base.height = left->get_height();
        } else if(base.width != left->get_width() || base.height != left->get_height()) {
          base.x -= (left->get_width() - base.width) / 2;
          base.y -= left->get_height() - base.height;
          base.width = left->get_width();
          base.height = left->get_height();
          old_base = base;
        }
      } else {
        base.width = base.height = 0;
      }
    }

  animation_offset = 0;
  sprite_left  = left;
  sprite_right = right;
}

void
BadGuy::bump() {
	// these can't be bumped
	if ((kind == BAD_SMALLSPIKYBALL) || (kind == BAD_WALKER3_COUNTDOWN) || (kind == BAD_FISH) || (kind == BAD_EXPLOSION) || (kind == BAD_FLYWALKER3)) {
//       || (kind == BAD_BUMPED_WALKER1_LEFT) || (kind == BAD_BUMPED_WALKER1_RIGHT) 
//       || (kind == BAD_BUMPED_WALKER2_LEFT) || (kind == BAD_BUMPED_WALKER2_RIGHT) 
//       || (kind == BAD_BUMPED_WALKER3_LEFT) || (kind == BAD_BUMPED_WALKER3_RIGHT)) {
		return;
	}

	else if (kind == BAD_WALKER1) {

		// bumped walker1
		if (this->dir == LEFT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER1_LEFT);
		else if (this->dir == RIGHT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER1_RIGHT);
  		remove_me();
	  }
	else if (kind == BAD_WALKER2) {

		// bumped walker2
		if (this->dir == LEFT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER2_LEFT);
		else if (this->dir == RIGHT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER2_RIGHT);
  		remove_me();
	}
	else if (kind == BAD_WALKER3) {

		// bumped walker3
		if (this->dir == LEFT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER3_LEFT);
		else if (this->dir == RIGHT) World::current()->add_bad_guy(base.x, base.y, BAD_BUMPED_WALKER3_RIGHT);
		remove_me();
	}

	physic.set_velocity_y(3);
	kill_me2(25);
}


void
BadGuy::squish_me(Player* player)
{
  player->jump_of_badguy(this);
    
  World::current()->add_score(base.x - scroll_x,
                              base.y, 50 * player_status.score_multiplier);
  play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
  player_status.score_multiplier++;

  dying = DYING_SQUISHED;
  timer.start(2000);
  physic.set_velocity(0, 0);
}

void
BadGuy::squish(Player* player)
{
  static const int MAX_ICEBLOCK_SQUICHES = 10;
    
  if(kind == BAD_WALKER3) {
    // mrbomb transforms into a bomb now
    World::current()->add_bad_guy(base.x, base.y, BAD_WALKER3_COUNTDOWN);
   
    player->jump_of_badguy(this);
    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
    play_sound(sounds[SND_WALKER3_FLATTEN], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;

  } else if (kind == BAD_WALKER2) {
    if (mode == NORMAL || mode == KICK)
      {
        /* Flatten! */
        play_sound(sounds[SND_STOMP], SOUND_CENTER_SPEAKER);
        mode = FLAT;
        set_sprite(img_walker2_flatten_left, img_walker2_flatten_right);
        physic.set_velocity_x(0);

        timer.start(4000);
      } else if (mode == FLAT) {
        /* Kick! */
        if(squishcount < MAX_ICEBLOCK_SQUICHES - 1) {
          play_sound(sounds[SND_KICK], SOUND_CENTER_SPEAKER);
        }
        if (player->base.x < base.x + (base.width/2)) {
          physic.set_velocity_x(5);
          dir = RIGHT;
        } else {
          physic.set_velocity_x(-5);
          dir = LEFT;
        }

        mode = KICK;
        player->kick_timer.start(KICKING_TIME);
        set_sprite(img_walker2_running_left, img_walker2_running_right);
      }

    player->jump_of_badguy(this);

    player_status.score_multiplier++;

    // check for maximum number of squiches
    squishcount++;
    if(squishcount >= MAX_ICEBLOCK_SQUICHES) {
      kill_me(50);
      return;
    }
    
    return;
  } else if(kind == BAD_FISH) {
    // fish can only be killed when falling down
    if(physic.get_velocity_y() >= 0)
      return;
    
    player->jump_of_badguy(this);
	      
    World::current()->add_score(base.x - scroll_x, base.y, 25 * player_status.score_multiplier);
    player_status.score_multiplier++;
     
    // simply remove the fish...
    remove_me();
    return;
  } else if(kind == BAD_JUMPINGCREATURE) {
//    squish_me(player);
//    set_sprite(img_jumpingcreature_exploding,img_jumpingcreature_exploding);
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
//    physic.set_velocity_y(0);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;
  } else if(kind == BAD_FLYWALKER3) {
//    squish_me(player);
//    set_sprite(img_flywalker3_exploding,img_flywalker3_exploding);
//    return;


//    squish_me(player);
//    set_sprite(img_jumpingcreature_exploding,img_jumpingcreature_exploding);
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
//    physic.set_velocity_y(0);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;

  } else if(kind == BAD_WALKER1) {
    // mrbomb transforms into a bomb now
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;

  } else if(kind == BAD_FLYWALKER2) {
    // mrbomb transforms into a bomb now
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;

  }  else if(kind == BAD_SWIMWALKER2) {
    // mrbomb transforms into a bomb now
//    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
//    player->jump_of_badguy(this);
////    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
//    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
//    player_status.score_multiplier++;
//    remove_me();
//    return;

  } else if(kind == BAD_GODSMONSTER) {
    // mrbomb transforms into a bomb now
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;

    } else if(kind == BAD_BIRD) {
    // mrbomb transforms into a bomb now
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
   
    player->jump_of_badguy(this);
//    World::current()->add_score(base.x - scroll_x, base.y, 50 * player_status.score_multiplier);
    play_sound(sounds[SND_SQUISH], SOUND_CENTER_SPEAKER);
    player_status.score_multiplier++;
    remove_me();
    return;
	}





//else if(kind == BAD_WALKER1) {
//    squish_me(player);
//    set_sprite(img_walker1_walking_squished_left, img_walker1_walking_squished_right);
//    return;
//  }
}

void
BadGuy::kill_me(int score)
{
  if(kind == BAD_WALKER3_COUNTDOWN || kind == BAD_STALACTITE || kind == BAD_SMALLSPIKYBALL)
    return;

  dying = DYING_SQUISHED;
    World::current()->add_bad_guy(base.x, base.y, BAD_EXPLOSION);
//    set_sprite(img_walker1_walking_squished_left, img_walker1_walking_squished_right);
  if(kind == BAD_WALKER2) {
//    set_sprite(img_walker2_running_left, img_walker2_running_right);

    if(mode == HELD) {
      mode = NORMAL;
      Player& turr = *World::current()->get_turr();  
      turr.holding_something = false;
    }
  }
  
//  physic.enable_gravity(true);

  /* Gain some points: */
    World::current()->add_score(base.x - scroll_x, base.y,
                    score * player_status.score_multiplier);

  /* Play death sound: */
  physic.set_velocity_y(0);
  play_sound(sounds[SND_EXPLODE], SOUND_CENTER_SPEAKER);
      remove_me();
}


void
BadGuy::kill_me2(int score)
{
  if(kind == BAD_WALKER3_COUNTDOWN || kind == BAD_STALACTITE || kind == BAD_SMALLSPIKYBALL)
    return;

  dying = DYING_FALLING;
  if(kind == BAD_WALKER2) {
    set_sprite(img_walker2_flatten_left, img_walker2_flatten_right);

    if(mode == HELD) {
      mode = NORMAL;
      Player& turr = *World::current()->get_turr();  
      turr.holding_something = false;
    }
  }
  
  physic.enable_gravity(true);

  /* Gain some points: */
    World::current()->add_score(base.x - scroll_x, base.y,
                    score * player_status.score_multiplier);

  /* Play death sound: */
  if ((kind == BAD_BUMPED_WALKER1_LEFT) || (kind == BAD_BUMPED_WALKER1_RIGHT) 
       || (kind == BAD_BUMPED_WALKER2_LEFT) || (kind == BAD_BUMPED_WALKER2_RIGHT) 
       || (kind == BAD_BUMPED_WALKER3_LEFT) || (kind == BAD_BUMPED_WALKER3_RIGHT)) return;
  play_sound(sounds[SND_EXPLODE], SOUND_CENTER_SPEAKER);
}











void BadGuy::explode(BadGuy *badguy)
{
World::current()->add_bad_guy(badguy->base.x, badguy->base.y, BAD_WALKER3_COUNTDOWN);
badguy->remove_me();
}

void
BadGuy::collision(void *p_c_object, int c_object, CollisionType type)
{
  BadGuy* pbad_c    = NULL;

  if(type == COLLISION_BUMP) {
    bump();
    return;
  }

  if(type == COLLISION_SQUISH) {
    Player* player = static_cast<Player*>(p_c_object);
    squish(player);
    return;
  }

  /* COLLISION_NORMAL */
  switch (c_object)
    {
    case CO_BULLET:
      kill_me(10);
      break;

    case CO_BADGUY:
      pbad_c = (BadGuy*) p_c_object;

      /* If we're a running walker2, kill any badguys we hit */
      if(kind == BAD_WALKER2 && mode == KICK)
        {
          pbad_c->kill_me(25);
        }

      // a held walker2 gets kills the enemy too but falls to ground then
      else if(kind == BAD_WALKER2 && mode == HELD)
        {
          pbad_c->kill_me(25);
          kill_me(0);
        }

      /* Kill badguys that run into exploding bomb */
      else if (kind == BAD_WALKER3_COUNTDOWN && dying == DYING_NOT)
      {
        if (pbad_c->kind == BAD_WALKER3)
        {
          // mrbomb transforms into a bomb now
          explode(pbad_c);
          return;
        }
        else if (pbad_c->kind != BAD_WALKER3)
        {
          pbad_c->kill_me(50);
        }
      }

      /* Kill any badguys that get hit by stalactite */
      else if (kind == BAD_STALACTITE && dying == DYING_NOT)
      {
        if (pbad_c->kind == BAD_WALKER3)
        {
          // mrbomb transforms into a bomb now
          explode(pbad_c);
          return;
        }
        else
          pbad_c->kill_me(50);
      }

      /* When enemies run into eachother, make them change directions */
      else
      {
        // Jumpy, fish, flame, stalactites are exceptions
        if (pbad_c->kind == BAD_LARGESPIKYBALL || pbad_c->kind == BAD_SMALLSPIKYBALL
            || pbad_c->kind == BAD_STALACTITE || pbad_c->kind == BAD_FISH)
          break;

        // Bounce off of other badguy if we land on top of him
        if (base.y + base.height < pbad_c->base.y + pbad_c->base.height)
        {
          if (pbad_c->dir == LEFT)
          {
            dir = RIGHT;
            physic.set_velocity(fabsf(physic.get_velocity_x()), 2);
          }
          else if (pbad_c->dir == RIGHT)
          {
            dir = LEFT;
            physic.set_velocity(-fabsf(physic.get_velocity_x()), 2);
          }



          break;
        }
        else if (base.y + base.height > pbad_c->base.y + pbad_c->base.height)
          break;

        if (pbad_c->kind != BAD_SMALLSPIKYBALL)
          {
            if (dir == LEFT)
            {
              dir = RIGHT;
              physic.set_velocity_x(fabsf(physic.get_velocity_x()));
            }
            else if (dir == RIGHT)
            {
              dir = LEFT;
              physic.set_velocity_x(-fabsf(physic.get_velocity_x()));
            }

          }
      }
      
      break;

    case CO_PLAYER:
      Player* player = static_cast<Player*>(p_c_object);
      /* Get kicked if were flat */
      if (mode == FLAT && !dying)
      {
        play_sound(sounds[SND_KICK], SOUND_CENTER_SPEAKER);

        // Hit from left side
        if (player->base.x < base.x) {
          physic.set_velocity_x(5);
          dir = RIGHT;
        }
        // Hit from right side
        else {
          physic.set_velocity_x(-5);
          dir = LEFT;
        }

        mode = KICK;
        player->kick_timer.start(KICKING_TIME);
        set_sprite(img_walker2_flatten_left, img_walker2_flatten_right);
      }
      break;

    }
}


//---------------------------------------------------------------------------

void load_badguy_gfx()
{
  img_walker2_flatten_left = sprite_manager->load("walker2-flat-left");
  img_walker2_flatten_right = sprite_manager->load("walker2-flat-right");
  img_walker2_running_left = sprite_manager->load("walker2-run-left");
  img_walker2_running_right = sprite_manager->load("walker2-run-right");
  img_walker2_walking_left = sprite_manager->load("walker2-walk-left");
  img_walker2_walking_right = sprite_manager->load("walker2-walk-right");
  img_largespikyball_up = sprite_manager->load("largespikyball-up");
  img_largespikyball_down = sprite_manager->load("largespikyball-down");
  img_largespikyball_middle = sprite_manager->load("largespikyball-middle");
  img_walker3_walking_left = sprite_manager->load("walker3-walk-left");
  img_walker3_walking_right = sprite_manager->load("walker3-walk-right");
  img_walker3_countdown_left = sprite_manager->load("walker3-countdown-left");
  img_walker3_countdown_right = sprite_manager->load("walker3-countdown-right");
  img_walker3_exploding = sprite_manager->load("walker3-explode");
  img_stalactite = sprite_manager->load("stalactite");
  img_stalactite_broken = sprite_manager->load("stalactite-broken");
  img_smallspikyball = sprite_manager->load("smallspikyball");
  img_fish = sprite_manager->load("fish");
  img_fish_down = sprite_manager->load("fish-down");
  img_jumpingcreature_left = sprite_manager->load("jumpingcreature-left");
  img_jumpingcreature_right = sprite_manager->load("jumpingcreature-right");
//  img_jumpingcreature_exploding = sprite_manager->load("jumpingcreature-explode");
  img_flywalker3_flying = sprite_manager->load("flywalker3-fly");
//  img_flywalker3_exploding = sprite_manager->load("flywalker3-explode");
  img_crab_walking_left = sprite_manager->load("crab-walk-left");
  img_crab_walking_right = sprite_manager->load("crab-walk-right");
  img_walker1_walking_left = sprite_manager->load("walker1-walk-left");
  img_walker1_walking_right = sprite_manager->load("walker1-walk-right");
  img_explosion = sprite_manager->load("explosion");
  img_flywalker2_flying_left = sprite_manager->load("flywalker2-fly-left");
  img_flywalker2_flying_right = sprite_manager->load("flywalker2-fly-right");
  img_swimwalker2_swimming_left = sprite_manager->load("swimwalker2-swim-left");
  img_swimwalker2_swimming_right = sprite_manager->load("swimwalker2-swim-right");
  img_godsmonster_walking_left = sprite_manager->load("godsmonster-walk-left");
  img_godsmonster_walking_right = sprite_manager->load("godsmonster-walk-right");
//  img_explosion_right = sprite_manager->load("snowball-squished-right");
	img_bird_flying = sprite_manager->load("bird-flying");
	img_bumped_walker1_left = sprite_manager->load("bumped-walker1-left");
	img_bumped_walker1_right = sprite_manager->load("bumped-walker1-right");
	img_bumped_walker2_left = sprite_manager->load("bumped-walker2-left");
	img_bumped_walker2_right = sprite_manager->load("bumped-walker2-right");
	img_bumped_walker3_left = sprite_manager->load("bumped-walker3-left");
	img_bumped_walker3_right = sprite_manager->load("bumped-walker3-right");
}

void free_badguy_gfx()
{
}

// EOF //
