// SPDX-License-Identifier: GPL-2.0-or-later

// This file is a part of Cinelerra-CVE
// Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>

#ifndef FILEPNG_H
#define FILEPNG_H

#include "datatype.h"
#include "file.inc"
#include "filebase.h"
#include "filelist.h"
#include "vframe.inc"

class FilePNG : public FileList
{
public:
	FilePNG(Asset *asset, File *file);

	static int check_sig(Asset *asset);
	static void get_parameters(BC_WindowBase *parent_window, 
		Asset *asset, 
		BC_WindowBase* &format_window,
		int options);
	int colormodel_supported(int colormodel);
	int read_frame(VFrame *frame, VFrame *data);
	int write_frame(VFrame *frame, VFrame *data, FrameWriterUnit *unit);
	FrameWriterUnit* new_writer_unit(FrameWriter *writer);

	int read_frame_header(const char *path);

	int native_cmodel;
};


class PNGUnit : public FrameWriterUnit
{
public:
	PNGUnit(FilePNG *file, FrameWriter *writer);
	~PNGUnit();

	FilePNG *file;
	VFrame *temp_frame;
};

class PNGConfigVideo : public BC_Window
{
public:
	PNGConfigVideo(BC_WindowBase *parent_window, Asset *asset, int absx, int absy);

	Asset *asset;
};


class PNGUseAlpha : public BC_CheckBox
{
public:
	PNGUseAlpha(PNGConfigVideo *gui, int x, int y);

	int handle_event();
	PNGConfigVideo *gui;
};

#endif
