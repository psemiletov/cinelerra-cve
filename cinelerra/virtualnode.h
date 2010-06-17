
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

#ifndef VIRTUALNODE_H
#define VIRTUALNODE_H

#include "arraylist.h"
#include "auto.inc"
#include "autos.inc"
#include "floatauto.inc"
#include "floatautos.inc"
#include "mwindow.inc"
#include "maxbuffers.h"
#include "patch.h"
#include "plugin.inc"
#include "pluginserver.inc"
#include "track.inc"
#include "transition.inc"
#include "virtualconsole.inc"

// The virtual node makes up the virtual console.
// It can be either a virtual module or a virtual plugin.


class VirtualNode
{
public:
	VirtualNode(RenderEngine *renderengine, 
		VirtualConsole *vconsole, 
		Module *real_module, 
		Plugin *real_plugin, 
		Track *track, 
		VirtualNode *parent_node);

	friend class VirtualConsole;

	virtual ~VirtualNode();
	void dump(int indent);


// expand plugins
	int expand(int persistent_plugins, posnum current_position);
// create convenience pointers to shared memory depending on the data type
	virtual int create_buffer_ptrs() {};
// create a node for a module and expand it
	int attach_virtual_module(Plugin *plugin, 
		int plugin_number, 
		int duplicate, 
		posnum current_position);
// create a node for a plugin and expand it
	int attach_virtual_plugin(Plugin *plugin, 
		int plugin_number, 
		int duplicate, 
		posnum current_position);
	virtual VirtualNode* create_module(Plugin *real_plugin, 
						Module *real_module, 
						Track *track) { return 0; };
	virtual VirtualNode* create_plugin(Plugin *real_plugin) { return 0; };


// Called by read_data to get the previous plugin in a parent node's subnode
// table.
	VirtualNode* get_previous_plugin(VirtualNode *current_plugin);

// subnodes this node owns
// was vplugins
	ArrayList<VirtualNode*> subnodes;
// Attachment point in Module if this is a virtual plugin
	AttachmentPoint *attachment;

	VirtualConsole *vconsole;
// node which created this node.
	VirtualNode *parent_node;
// use these to determine if this node is a plugin or module
// Top level virtual node of module
	Module *real_module;
// When this node is a plugin.  Redirected to the shared plugin in expansion.
	Plugin *real_plugin;


	Track *track;
	RenderEngine *renderengine;

// for rendering need to know if the buffer is a master or copy
// These are set in expand()
	int input_is_master;
	int output_is_master;
	int ring_buffers;       // number of buffers for master buffers
	int plugin_type;          // type of plugin in case user changes it
	int render_count;         // times this plugin has been added to the render list
	int waiting_real_plugin;  //  real plugin tests this to see if virtual plugin is waiting on it when sorting
// attachment point needs to know what buffer to put data into from 
// a multichannel plugin
	int plugin_buffer_number;

// Mute automation.
// Return whether the next samples are muted and store the duration
// of the next status in fragment_len
	void get_mute_fragment(posnum input_position,
				int &mute_constant, 
				int &fragment_len, 
				Autos *autos,
				int direction,
				int use_nudge);

private:
	int sort_as_module(ArrayList<VirtualNode*>*render_list, int &result, int &total_result);
	int sort_as_plugin(ArrayList<VirtualNode*>*render_list, int &result, int &total_result);
	int expand_as_module(int duplicate, posnum current_position);
	int expand_as_plugin(int duplicate);
	int is_exit;
};



#endif
