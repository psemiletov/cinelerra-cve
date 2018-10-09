/*
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 
 * USA
 */
 
 
#ifndef COLORMODELS_H
#define COLORMODELS_H

#include "bcbitmap.inc"
#include "colormodels.inc"
#include "vframe.inc"

#define DUMP_FRAME_AVG 1
#define DUMP_FRAME_MIN 2
#define DUMP_FRAME_MAX 3

#define DUMP_FRAME_COMB 0x10  // Combine nibbels
#define DUMP_FRAME_MASK 7     // Value type

extern "C"
{
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
}

struct cm_names {
    int value;
    const char *name;
};

struct intp_types
{
	int value;
	int libvalue;
};

class ColorModels
{
public:
	ColorModels();

	static int calculate_pixelsize(int colormodel);
	static int calculate_datasize(int w, int h,
		int bytes_per_line, int color_model);
	static int calculate_max(int colormodel);
	static int components(int colormodel);
	static int is_yuv(int colormodel);
	static int has_alpha(int colormodel);

	// Tell when to use plane arguments or row pointer arguments to functions
	static int is_planar(int color_model);
	static void to_text(char *string, int cmodel);
	static const char *name(int cmodel);
	static int from_text(char *text);
	static void transfer_sws(unsigned char *output,
		unsigned char *input,
		unsigned char *out_y_plane,
		unsigned char *out_u_plane,
		unsigned char *out_v_plane,
		unsigned char *in_y_plane,
		unsigned char *in_u_plane,
		unsigned char *in_v_plane,
		int in_w,
		int in_h,
		int out_w,
		int out_h,
		int in_colormodel,
		int out_colormodel,
		int in_rowspan,
		int out_rowspan);
	static void rgba2transparency(int w, int h,
		unsigned char *output, unsigned char *input,
		int out_rowspan, int in_rowspan);
	static void transfer_frame(unsigned char *output,
		VFrame *frame,
		unsigned char *out_y_plane,
		unsigned char *out_u_plane,
		unsigned char *out_v_plane,
		int out_w,           // output width
		int out_h,           // output height
		int out_colormodel,
		int out_rowspan);

	static AVPixelFormat color_model_to_pix_fmt(int color_model);
	static int inter_color_model(int color_model);

	static void fill_linesizes(int colormodel, int rowspan,
		int w, int *linesizes);
	static void fill_data(int colormodel, unsigned char **data,
		unsigned char *xbuf, unsigned char *y, unsigned char *u,
		unsigned char *v);
	static void copy_colors(int w, int h,
		unsigned char *output, int out_colormodel, int out_rowspan,
		unsigned char *input, int in_cmodel, int in_rowspan);
	static void slow_transfer(int out_w, int out_h,
		unsigned char *output, int out_cmodel, int out_rowspan,
		int in_w, int in_h,
		unsigned char *input, int in_cmodel, int in_rowspan);
	static int libinterpolate(int value);
	static int libinterpolate();
	static void dump_frame(BC_Bitmap *frame, int opts = DUMP_FRAME_AVG);
	static void dump_frame(VFrame *frame, int opts = DUMP_FRAME_AVG);
	static void dump_frame(unsigned char *data, int width, int height,
		int bytes_per_line, int colormodel, int opts = DUMP_FRAME_AVG);

private:
	static void transfer_details(struct SwsContext *sws_ctx, int srange);
	static struct cm_names color_model_names[];
	static struct intp_types interpolation_types[];
};

#endif
