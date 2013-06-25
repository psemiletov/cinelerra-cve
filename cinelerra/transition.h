
/*
 * CINELERRA
 * Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>
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

#ifndef TRANSITION_H
#define TRANSITION_H

#include "datatype.h"
#include "edit.inc"
#include "filexml.inc"
#include "mwindow.inc"
#include "plugin.h"
#include "sharedlocation.h"


class Transition : public Plugin
{
public:
	Transition(EDL *edl, Edit *edit, const char *title, ptstime length);
	Transition(Transition *that, Edit *edit);

	void save_xml(FileXML *file);
	void load_xml(FileXML *file);

	KeyFrame* get_keyframe();
	Transition& operator=(Transition &that);
	Plugin& operator=(Plugin &that);
	Edit& operator=(Edit &that);
	int operator==(Transition &that);
	int operator==(Plugin &that);
	int operator==(Edit &that);
	int identical(Transition *that);
	ptstime length(void);

	void dump(int indent = 0);

	Edit *edit;
	ptstime length_time;

private:
// Only used by operator= and copy constructor
	void copy_from(Transition *that);
};

#endif
