
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

#ifndef VRENDER_H
#define VRENDER_H

#include "commonrender.h"
#include "edit.inc"
#include "guicast.h"
#include "mwindow.inc"
#include "overlayframe.inc"
#include "renderengine.inc"
#include "vframe.inc"


class VRender : public CommonRender
{
public:
	VRender(RenderEngine *renderengine);
	VRender(MWindow *mwindow, RenderEngine *renderengine);
	~VRender();

	VirtualConsole* new_vconsole_object();
	int get_total_tracks();
	Module* new_module(Track *track);

	void run();

	int start_playback();     // start the thread

// get data type for certain commonrender routines
	int get_datatype();

// process frames to put in buffer_out
	int process_buffer(VFrame *video_out, 
		ptstime input_postime,
		int last_buffer);
// load an array of buffers for each track to send to the thread
	int process_buffer(ptstime input_postime);
// Flash the output on the display
	int flash_output();

	int get_use_vconsole(Edit* &playable_edit, 
		ptstime position,
		int &get_use_vconsole);
	int get_colormodel(Edit* &playable_edit, 
		int use_vconsole,
		int use_brender);

	posnum tounits(double position, int round = 0);
	double fromunits(posnum position);

// frames since start of playback
	framenum session_frame;

// console dimensions
	int track_w, track_h;
// video device dimensions
	int output_w, output_h;

// Output frame
	VFrame *video_out;

// Temp frame for VModule loading
	VFrame *input_temp;
// Temp frame for VModule transitions
	VFrame *transition_temp;
// Engine for camera and projector automation
	OverlayFrame *overlayer;


// Flag first frame to unlock audio
	int first_frame;

private:
	int init_device_buffers();
	Timer timer;

// for getting actual framerate
	int framerate_counter;
	Timer framerate_timer;
	int render_strategy;
};




#endif
