//----- SUPER TURR Alpha 19.12.31 -----//
// based on SuperTux 0.1.3 source code //
///////////////////////////////////////////  $Id$
// 
//  SuperTux
//  Copyright (C) 2003 Ricardo Cruz <rick2@aeiou.pt>
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

/* leveleditor.h - A built-in level editor for Super Turr */

#ifndef SUPERTURR_LEVELEDITOR_H
#define SUPERTURR_LEVELEDITOR_H

#include <menu.h>

struct square
{
  int x1, y1, x2, y2;
};

/* selection modes */
enum {
  SM_CURSOR,
  SM_SQUARE,
  SM_NONE
};

int leveleditor(char* filename = NULL);
void newlevel(void);
void selectlevel(void);
void le_savelevel();
void editlevel(void);
void testlevel(void);
int le_init(void);
void le_checkevents(void);
void le_quit(void);

extern int le_level_loaded;
extern int quit_level_editor;
Menu* get_leveleditor_menu(void);

#endif /*SUPERTURR_LEVELEDITOR_H*/
