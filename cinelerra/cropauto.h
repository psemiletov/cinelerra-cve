// SPDX-License-Identifier: GPL-2.0-or-later

// This file is a part of Cinelerra-CVE
// Copyright (C) 2019 Einar Rünkaru <einarrunkaru@gmail dot com>

#ifndef CROPAUTO_H
#define CROPAUTO_H

#include "auto.h"
#include "edl.inc"
#include "filexml.inc"
#include "cropauto.inc"
#include "cropautos.inc"

class CropAuto : public Auto
{
public:
	CropAuto(EDL *edl, CropAutos *autos);

	void copy_from(Auto *that);
	void copy_from(CropAuto *that);

	void load(FileXML *file);
	void save_xml(FileXML *file);
	void copy(Auto *that, ptstime start, ptstime end);
	size_t get_size();
	void dump(int indent = 0);

	int left;
	int right;
	int top;
	int bottom;
	int apply_before_plugins;
};

#endif
