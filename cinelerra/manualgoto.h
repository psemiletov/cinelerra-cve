
/*
 * CINELERRA
 * Copyright (C) 2004 Andraz Tori
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */

#ifndef MANUALGOTO_H
#define MANUALGOTO_H

#include "awindow.inc"
#include "edl.inc"
#include "guicast.h"
#include "mwindow.inc"
#include "thread.h"
#include "vwindow.inc"
#include "editpanel.inc"

class ManualGotoWindow;
class ManualGotoNumber;

class ManualGoto : public Thread
{
public:
	ManualGoto(MWindow *mwindow, BC_WindowBase *masterwindow);

	void run();

// If it is being created or edited
	MWindow *mwindow;
	BC_WindowBase *masterwindow;
	void open_window();

	ptstime position;
	VFrame *icon_image;
	ManualGotoWindow *window;
};


class ManualGotoWindow : public BC_Window
{
public:
	ManualGotoWindow(MWindow *mwindow, ManualGoto *thread);

	void activate();
	ptstime get_entered_position_sec();
	void set_entered_position_sec(ptstime position);
	int split_timestr(char *timestr);

// Use this copy of the pointer in ManualGoto since multiple windows are possible
	BC_Title *signtitle;
	ManualGotoNumber *boxes[5];
	int numboxes;
	MWindow *mwindow;
	ManualGoto *thread;
	int timeformat;
	char timestring[64];
	char *timeparts[5];
};


class ManualGotoNumber : public BC_TextBox
{
public:
	ManualGotoNumber(ManualGotoWindow *window, int x, int y, int w, int chars);

	int handle_event();
	int keypress_event();
	void activate();
	void deactivate();
	void reshape_update(char *nums);

	ManualGotoWindow *window;
	int min_num;
	int max_num;
	int chars;
};
#endif
