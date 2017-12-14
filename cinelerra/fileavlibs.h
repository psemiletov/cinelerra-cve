
/*
 * CINELERRA
 * Copyright (C) 2015 Einar Rünkaru <einarrunkaru@gmail dot com>
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

#ifndef FILEAVLIBS_H
#define FILEAVLIBS_H


#include "asset.inc"
#include "avlibsconfig.h"
#include "aframe.inc"
#include "cinelerra.h"
#include "file.inc"
#include "filebase.h"
#include "fileavlibs.inc"
#include "mutex.inc"
#include "paramlist.inc"
#include "pipe.inc"
#include "vframe.inc"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}

struct avlib_formattable
{
	int fileformat;
	const char *decoder;
	const char *encoder;
	int supports;
};

struct avlib_encparams
{
	const char *name;
	const char *prompt;
	int type;
};

class FileAVlibs : public FileBase
{
public:
	FileAVlibs(Asset *asset, File *file);
	~FileAVlibs();

	friend class AVlibsConfig;

	// Get format string for ffmpeg
	static int check_sig(Asset *asset);
	// Probe file and fill asset
	static int probe_input(Asset *asset);
	// Supported streams of format
	static int supports(int format, int deoding = 0);

	int open_file(int rd, int wr);
	void close_file();

	int get_best_colormodel(Asset *asset, int driver);
	int read_frame(VFrame *frame);
	int read_aframe(AFrame *frame);
	int write_frames(VFrame ***frames, int len);
	int colormodel_supported(int colormodel);
	int converts_frame();
	static void versionifo(int indent);
	int write_aframes(AFrame **frames);
	static void get_parameters(BC_WindowBase *parent_window,
		Asset *asset, BC_WindowBase* &format_window, int options);
	static void restore_codec_options(Paramlist *codecs);
	static void get_render_defaults(Asset *asset);
	static void get_format_params(Asset *asset, int options);
	static void set_format_params(Asset *asset);
	static void save_render_options(Asset *asset);
	static int update_codeclist(Asset *asset, Paramlist *codecs, int options);
	static const char *encoder_formatname(int fileformat);

// Callbacks of FileTOC
	int get_streamcount();
	stream_params* get_track_data(int trackindex);
	static const char *enc_prompt(const char *enc_name);
	static struct avlib_encparams encoder_params[];

private:
	int media_seek(int stream_index, int64_t rqpos, AVPacket *pkt, int64_t pktpos);
	int convert_cmodel(AVPicture *picture_in, PixelFormat pix_fmt_in,
		int width_in, int height_in, VFrame *frame_out);
	int convert_cmodel(VFrame *frame_in, AVPixelFormat pix_fmt_out,
		int width_out, int height_out, AVFrame *frame_out);
	int decode_samples(int64_t rqpos, int length);
	int fill_buffer(AVFrame *avaframe, int ibytes = 0, int bps = 0, int planar = 0);
	int write_samples(int resampled_length, AVCodecContext *audio_ctx, ptstime pts = -1);
	AVDictionary *create_dictionary(int options);
	void list2dictionary(AVDictionary **dict, Paramlist *params);
	static int streamformat(AVFormatContext *context);
	static void liberror(int code, const char *prefix);
	static Paramlist *scan_global_options(int options);
	static AVOutputFormat *output_format(int format);
	static Paramlist *scan_format_options(int format, int options);
	static Paramlist *scan_options(const AVClass *avclass, int options,
		const char *listname);
	static void fill_encoder_params(Paramlist *codecs, AVCodecID codec_id,
		Asset *asset, int options);
	static Paramlist *scan_codecs(AVOutputFormat *oformat, Asset *asset, int options);
	static Paramlist *scan_encoder_opts(AVCodecID codec, int options);
	static Paramlist *scan_encoder_private_opts(AVCodecID codec, int options);
	static Paramlist *clean_list(Paramlist *list);
	static Param *opt2param(Paramlist *list, const AVOption *opt);
	static int skip_avoption(const AVOption *opt, int typefl);
	static int encoder_exists(AVOutputFormat *oformat,
		const char *encstr, int support);
	static void dump_AVFormatContext(AVFormatContext *ctx, int indent = 0);
	static void dump_AVStream(AVStream *stm, int indent = 0);
	static void dump_AVCodecContext(AVCodecContext *ctx, int indent = 0);
	static void dump_AVFrame(AVFrame *avf, int indent = 0);
	static void dump_AVPacket(AVPacket *pkt, int indent = 0);
	static void dump_AVProgram(AVProgram *prg, int indent = 0);
	static const char *dump_ts(int64_t ts, char *obuf = 0);
	static const char *dump_AVRational(const AVRational *r, char *obuf = 0);
	static const char *dump_avfmt_flag(int flags, char *obuf);
	static const char *dump_fourcc(unsigned int tag);
	static void dump_AVCodecDescriptor(const AVCodecDescriptor *avdsc, int indent = 0);
	static void dump_AVOutputFormat(const AVOutputFormat *ofmt, int indent = 0);
	static void dump_AVInputFormat(const AVInputFormat *ifmt, int indent = 0);
	static void dump_AVOption(const AVOption *opt,
		const AVClass *avclass = 0, int indent = 0);
	static void dump_AVOptions(const AVClass *avclass, int indent = 0);
	static const char *dump_AVOptionType(enum AVOptionType type);
	static char *dump_AVOptionFlags(int flags);
	static void dump_AVCodec(const AVCodec *codec, int indent = 0);
	static const char *dump_AVMediaType(enum AVMediaType type);

	static struct avlib_formattable known_formats[];
	AVFormatContext *context;
	AVFrame *avvframe;
	AVFrame *avaframe;
	struct SwsContext *sws_ctx;
	SwrContext *swr_ctx;
	FileTOC *tocfile;

	int reading;
	int writing;
	int headers_written;
	ptstime pts_base;
	// Streams to decode
	int audio_index;
	int video_index;
	// Next video read position
	int64_t video_pos;
	int64_t vpkt_pos;
	int video_eof;
	// Audio positsions
	int64_t audio_pos;
	int64_t apkt_pos;
	int apkt_duration;
	static Mutex *avlibs_lock;
	stream_params track_data;

	// decoding audio
	int input_channels;
	int num_buffers;
	int buffer_len;
	int buffer_pos;
	int64_t audio_delay;
	int64_t buffer_start;
	int64_t buffer_end;
	int audio_eof;
	double *abuffer[MAXCHANNELS];

	// rendering audio
	uint8_t *resampled_data[MAXCHANNELS];
	int resampled_alloc; // allocated buffer size in samples
	int resample_fill;   // filled length in samples
	int resample_size;   // base size in input samples
	int sample_bytes;    // output sample bytes

	// IO context for pipe
	AVIOContext *avio_ctx;
	uint8_t *avio_buffer;
	int avio_fd;
	Pipe *stream_pipe;

	static const char *ignored[];
	static const uint64_t internal_layouts[];
};

#endif
