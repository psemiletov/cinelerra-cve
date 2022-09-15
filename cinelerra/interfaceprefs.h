// SPDX-License-Identifier: GPL-2.0-or-later

// This file is a part of Cinelerra-CVE
// Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>

#ifndef INTERFACEPREFS_H
#define INTERFACEPREFS_H

class IndexCount;
class TimeFormatHMS;
class TimeFormatHMSF;
class TimeFormatSamples;
class TimeFormatFrames;
class TimeFormatHex;
class TimeFormatFeet;
class TimeFormatSeconds;
class MeterMinDB;
class MeterMaxDB;

#include "bcpopupmenu.h"
#include "browsebutton.h"
#include "deleteallindexes.inc"
#include "preferencesthread.h"
#include "selection.h"


class InterfacePrefs : public PreferencesDialog
{
public:
	InterfacePrefs(PreferencesWindow *pwindow);
	~InterfacePrefs();

	void show();
	void update(int new_value);

	BrowseButton *ipath;
	IndexCount *icount;
	DeleteAllIndexes *deleteall;

	TimeFormatHMS *hms;
	TimeFormatHMSF *hmsf;
	TimeFormatSamples *samples;
	TimeFormatFrames *frames;
	TimeFormatFeet *feet;
	TimeFormatSeconds *seconds;

	MeterMinDB *min_db;
	MeterMaxDB *max_db;
};


class IndexCount : public BC_TextBox
{
public:
	IndexCount(int x, int y, PreferencesWindow *pwindow, const char *text);

	int handle_event();

	PreferencesWindow *pwindow;
};


class TimeFormatHMS : public BC_Radial
{
public:
	TimeFormatHMS(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatHMSF : public BC_Radial
{
public:
	TimeFormatHMSF(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatSamples : public BC_Radial
{
public:
	TimeFormatSamples(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatFrames : public BC_Radial
{
public:
	TimeFormatFrames(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatFeet : public BC_Radial
{
public:
	TimeFormatFeet(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatSeconds : public BC_Radial
{
public:
	TimeFormatSeconds(InterfacePrefs *tfwindow, int value, int x, int y);

	int handle_event();

	InterfacePrefs *tfwindow;
};


class TimeFormatFeetSetting : public BC_TextBox
{
public:
	TimeFormatFeetSetting(PreferencesWindow *pwindow, int x, int y, const char *string);

	int handle_event();

	PreferencesWindow *pwindow;
};


class MeterMinDB : public BC_TextBox
{
public:
	MeterMinDB(PreferencesWindow *pwindow, const char *text, int x, int y);

	int handle_event();

	PreferencesWindow *pwindow;
};


class MeterMaxDB : public BC_TextBox
{
public:
	MeterMaxDB(PreferencesWindow *pwindow, const char *text, int x, int y);

	int handle_event();

	PreferencesWindow *pwindow;
};


class ViewBehaviourSelection : public Selection
{
public:
	ViewBehaviourSelection(int x, int y, BC_WindowBase *window,
		int *value);

	void update(int value);
	static const char *name(int value);
private:
	static const struct selection_int viewbehaviour[];
};

class ViewTheme : public BC_PopupMenu
{
public:
	ViewTheme(int x, int y, PreferencesWindow *pwindow);

	PreferencesWindow *pwindow;
};


class ViewThemeItem : public BC_MenuItem
{
public:
	ViewThemeItem(ViewTheme *popup, const char *text);

	int handle_event();

	ViewTheme *popup;
};

#endif
