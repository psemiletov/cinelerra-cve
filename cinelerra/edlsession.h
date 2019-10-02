
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

#ifndef EDLSESSION_H
#define EDLSESSION_H

#include "autoconf.inc"
#include "bcwindowbase.inc"
#include "bchash.inc"
#include "datatype.h"
#include "cinelerra.h"
#include "edl.inc"
#include "edlsession.inc"
#include "filexml.inc"
#include "playbackconfig.inc"

// Session shared between all clips
class EDLSession
{
public:
	EDLSession();
	~EDLSession();

	void load_xml(FileXML *xml);
	void save_xml(FileXML *xml);
	void copy(EDLSession *session);
	void load_audio_config(FileXML *file);
	void save_audio_config(FileXML *xml);
	void load_video_config(FileXML *file);
	void save_video_config(FileXML *xml);
	void clear();
	void load_defaults(BC_Hash *defaults);
	void save_defaults(BC_Hash *defaults);
// Used by CWindowGUI during initialization.
	char* get_cwindow_display();
	void boundaries();

// Compose path of coniguration file
	char *configuration_path(const char *filename, char *outbuf);

// Called by PreferencesThread to determine if preference changes need to be
// rendered.
	int need_rerender(EDLSession *ptr);
// Called by BRender to determine if any background rendered frames are valid.
	void equivalent_output(EDLSession *session, double *result);
	void dump(int indent = 0);

// calculates the frame offset for programme timecode
	ptstime get_frame_offset();

// Duration of one frame
	ptstime frame_duration();

// Convert pts to text in current formet
	void ptstotext(char *string, ptstime pts);
// Size in bytes
	size_t get_size();

// Audio
	int achannel_positions[MAXCHANNELS];
	AudioOutConfig *aconfig_duplex;
// AWindow format
	int assetlist_format;
// AWindow column widths
	int asset_columns[ASSET_COLUMNS];
	AutoConf *auto_conf;
// Statistics
	float actual_frame_rate;
	int frame_count;
	int frames_late;
	int avg_delay;
// Video sample aspect ratio
	double sample_aspect_ratio;
	int audio_channels;
	int audio_tracks;
// Generate keyframes for every tweek
	int auto_keyframes;
// Where to start background rendering
	ptstime brender_start;
// Length of clipboard if pasting
	double clipboard_length;
// Colormodel for intermediate frames
	int color_model;
// Interlace Mode for entire project
	int interlace_mode;
// Ruler points relative to the output frame.
	double ruler_x1, ruler_y1;
	double ruler_x2, ruler_y2;
// Current folder in resource window
	int awindow_folder;
// align cursor on frame boundaries
	int cursor_on_frames;
// Current submask being edited in CWindow
	int cwindow_mask;
// Use the cwindow or not
	int cwindow_meter;
// CWindow tool currently selected
	int cwindow_operation;
// Use scrollbars in the CWindow
	int cwindow_scrollbars;
// Scrollbar positions
	int cwindow_xscroll;
	int cwindow_yscroll;
	double cwindow_zoom;
// Transition
	char default_atransition[BCTEXTLEN];
	char default_vtransition[BCTEXTLEN];
// Length in seconds
	ptstime default_transition_length;
// Edit mode to use for each mouse button
	int edit_handle_mode[3];
// Editing mode
	int editing_mode;
// AWindow format
	int folderlist_format;
	double frame_rate;
	float frames_per_foot;
// labels follow edits during editing
	int labels_follow_edits;
	float meter_over_delay;
	float meter_peak_delay;
	int min_meter_db;
	int max_meter_db;
	int output_w;
	int output_h;
	int playback_cursor_visible;
	int playback_software_position;
// Show title and action safe regions in CWindow
	int safe_regions;
	int sample_rate;
// Load files as a duration
	int si_useduration;
	float si_duration;
// Show assets in track canvas
	int show_assets;
// Show titles in resources
	int show_titles;
// Format to display times in
	int time_format;
// Offset for timecode
	int timecode_offset[4];
// Show tool window in CWindow
	int tool_window;
// play every frame
	int video_every_frame;
	int video_tracks;
	int view_follows_playback;
// show avlibs messages on console
	int show_avlibsmsgs;
// allow experimental codecs
	int experimental_codecs;
// Show another menu of encoders
	int encoders_menu;
// metadata for output file
	char metadata_author[BCTEXTLEN];
	char metadata_title[BCTEXTLEN];
	char metadata_copyright[BCTEXTLEN];
// Use the vwindow meter or not
	int vwindow_meter;
	float vwindow_zoom;
// Global ID counter
	static int current_id;
	PlaybackConfig* playback_config;
// Directory of plugin configurations
	char plugin_configuration_directory[BCTEXTLEN];
// Do automatic backups
	int automatic_backups;
// Interval of automatic backups (seconds)
	int backup_interval;
// Shrink plugin tracks
	int shrink_plugin_tracks;

private:
	int defaults_loaded;
};


#endif
