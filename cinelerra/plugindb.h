// SPDX-License-Identifier: GPL-2.0-or-later

// This file is a part of Cinelerra-CVE
// Copyright (C) 2019 Einar Rünkaru <einarrunkaru@gmail dot com>

#ifndef PLUGINDB_H
#define PLUGINDB_H

#include "arraylist.h"
#include "bcprogress.h"
#include "filesystem.inc"
#include "plugindb.inc"
#include "pluginserver.inc"
#include "splashgui.inc"


class PluginDB : ArrayList<PluginServer*>
{
public:
	PluginDB();
	~PluginDB();

	void init_plugin_path(FileSystem *fs,
		SplashGUI *splash_window,
		int *counter);
	void init_plugins(SplashGUI *splash_window);
	void fill_plugindb(int strdsc,
		int is_realtime,
		int is_transition,
		int is_theme,
		ArrayList<PluginServer*> &plugindb);
	PluginServer *get_pluginserver(int strdsc, const char *title, int transition);
	PluginServer *get_theme(const char *title);
	const char *translate_pluginname(const char *oldname, int strdsc);
	int count();

	void dump(int indent = 0, int strdsc = 0);
};

#endif
