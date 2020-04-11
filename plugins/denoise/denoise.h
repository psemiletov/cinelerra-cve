
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

#ifndef DENOISE_H
#define DENOISE_H

#define PLUGIN_TITLE N_("Denoise")
#define PLUGIN_IS_AUDIO
#define PLUGIN_IS_REALTIME
#define PLUGIN_USES_TMPFRAME

#define PLUGIN_CLASS DenoiseEffect
#define PLUGIN_CONFIG_CLASS DenoiseConfig
#define PLUGIN_THREAD_CLASS DenoiseThread
#define PLUGIN_GUI_CLASS DenoiseWindow

#include "pluginmacros.h"

#include "bcpot.h"
#include "language.h"
#include "pluginaclient.h"
#include "pluginwindow.h"

typedef enum { DECOMP, RECON } wavetype;

class DenoiseLevel : public BC_FPot
{
public:
	DenoiseLevel(DenoiseEffect *plugin, int x, int y);
	int handle_event();

	DenoiseEffect *plugin;
};

class DenoiseWindow : public PluginWindow
{
public:
	DenoiseWindow(DenoiseEffect *plugin, int x, int y);
	void update();

	DenoiseLevel *scale;
	DenoiseEffect *plugin;
};

PLUGIN_THREAD_HEADER

class DenoiseConfig
{
public:
	DenoiseConfig();
	void copy_from(DenoiseConfig &that);
	int equivalent(DenoiseConfig &that);
	void interpolate(DenoiseConfig &prev, 
		DenoiseConfig &next, 
		ptstime prev_frame,
		ptstime next_frame,
		ptstime current_frame);
	double level;
	PLUGIN_CONFIG_CLASS_MEMBERS
};

class Tree
{
public:
	Tree(int input_length, int levels);
	~Tree();

	int input_length;
	int levels;
	double **values;
};

class WaveletCoeffs
{
public:
	WaveletCoeffs(double alpha, double beta);

	double values[6];
	int length;
};

class WaveletFilters
{
public:
	WaveletFilters(WaveletCoeffs *wave_coeffs, wavetype transform);

	double g[6], h[6];
	int length;
};

class DenoiseEffect : public PluginAClient
{
public:
	DenoiseEffect(PluginServer *server);
	~DenoiseEffect();

	AFrame *process_tmpframe(AFrame *input);
	void read_data(KeyFrame *keyframe);
	void save_data(KeyFrame *keyframe);

	void load_defaults();
	void save_defaults();

	void process_window();
	double dot_product(double *data, double *filter, char filtlen);
	void convolve_dec_2(double *input_sequence, 
		int length,
		double *filter, 
		int filtlen, 
		double *output_sequence);
	int decompose_branches(double *in_data, 
		int length,
		WaveletFilters *decomp_filter, 
		double *out_low, 
		double *out_high);
	void wavelet_decomposition(double *in_data, 
		int in_length,
		double **out_data);
	void tree_copy(double **output, 
		double **input, 
		int length, 
		int levels);
	void threshold(int window_size, double gammas, int levels);
	double dot_product_even(double *data, double *filter, int filtlen);
	double dot_product_odd(double *data, double *filter, int filtlen);
	void convolve_int_2(double *input_sequence, 
		int length,
		double *filter, 
		int filtlen, 
		int sum_output, 
		double *output_sequence);
	int reconstruct_branches(double *in_low, 
		double *in_high, 
		int in_length,
		WaveletFilters *recon_filter, 
		double *output);
	void wavelet_reconstruction(double **in_data, 
		int in_length,
		double *out_data);

	PLUGIN_CLASS_MEMBERS

// buffer for storing fragments until a complete window size is armed
	double *input_buffer;
	int input_size;
	int input_allocation;
// buffer for storing fragments until a fragment is ready to be read
	double *output_buffer;
	int output_size;
	int output_allocation;
	double *dsp_in;
	double *dsp_out;
// buffer for capturing output of a single iteration
	double *dsp_iteration;
	Tree *ex_coeff_d, *ex_coeff_r, *ex_coeff_rn;
	WaveletCoeffs *wave_coeff_d, *wave_coeff_r;
	WaveletFilters *decomp_filter, *recon_filter;
// scaling factor for transferring from input_buffer
	double in_scale;
// power converted to scaling factor
	double out_scale;

// depends on the type of music
	int levels;
// higher number reduces aliasing due to a high noise_level
// also increases high end
	int iterations;
// daub6 coeffs
	double alpha;
	double beta;
// power
	double output_level;
// higher number kills more noise at the expense of more aliasing
	double noise_level;
	int window_size;
	int first_window;
	int initialized;
};

#endif
