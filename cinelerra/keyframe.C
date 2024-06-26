// SPDX-License-Identifier: GPL-2.0-or-later

// This file is a part of Cinelerra-CVE
// Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>

#include "bcsignals.h"
#include "filexml.h"
#include "keyframe.h"

#include <stdio.h>
#include <string.h>

KeyFrame::KeyFrame()
 : Auto()
{
	data = 0;
	drawn_x = -1;
}

KeyFrame::KeyFrame(KeyFrames *autos)
 : Auto((Autos*)autos)
{
	data = 0;
	drawn_x = -1;
}

KeyFrame::~KeyFrame()
{
	free(data);
}

void KeyFrame::load(FileXML *file)
{
	size_t txt_size;

	free(data);
	data = 0;

	if(txt_size = file->text_length_until("/KEYFRAME"))
	{
		data = (char*)malloc(txt_size + 1);
		file->read_text_until("/KEYFRAME", data, txt_size + 1);
	}
}

char *KeyFrame::get_data()
{
	return data;
}

size_t KeyFrame::data_size()
{
	if(data)
		return strlen(data);
	return 0;
}

void KeyFrame::set_data(const char *string)
{
	if(string && string[0])
	{
		if(data)
		{
			if(strcmp(string, data))
			{
				free(data);
				data = strdup(string);
			}
		}
		else
			data = strdup(string);
	}
	else
	{
		free(data);
		data = 0;
	}
}

void KeyFrame::save_xml(FileXML *file)
{
	file->tag.set_title("KEYFRAME");
	file->tag.set_property("POSTIME", pos_time);
	file->append_tag();

	if(data)
		file->append_text(data);

	file->tag.set_title("/KEYFRAME");
	file->append_tag();
	file->append_newline();
}

void KeyFrame::copy(Auto *src, ptstime start, ptstime end)
{
	KeyFrame *that = (KeyFrame*)src;

	if(this == that)
		return;

	pos_time = that->pos_time - start;
	free(data);
	data = 0;
	if(that->data)
		data = strdup(that->data);
}

void KeyFrame::copy_from(Auto *that)
{
	copy_from((KeyFrame*)that);
}

void KeyFrame::copy_from(KeyFrame *that)
{
	if(this == that)
		return;

	Auto::copy_from(that);
	free(data);
	data = 0;
	if(that->data)
		data = strdup(that->data);
}

int KeyFrame::identical(KeyFrame *src)
{
	if(!src)
		return 0;
	if(this == src)
		return 1;
	if(data && src->data)
		return !strcmp(src->data, data);
	return !data && !src->data;
}

int KeyFrame::operator==(Auto &that)
{
	return identical((KeyFrame*)&that);
}

int KeyFrame::operator==(KeyFrame &that)
{
	return identical(&that);
}

void KeyFrame::drawing(int pos_x)
{
	drawn_x = pos_x;
}

size_t KeyFrame::get_size()
{
	size_t size = sizeof(*this);

	if(data)
		size += strlen(data);
	return size;
}

void KeyFrame::dump(int indent)
{
	printf("%*sKeyFrame %p: pos_time %.3f", indent, "", this, pos_time);
	if(drawn_x >= 0)
		printf(" drawn %d", drawn_x);
	putchar('\n');
	if(data)
		printf("%*sdata: %s\n", indent + 2, "", data);
}
