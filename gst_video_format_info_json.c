#include <stdio.h>
#include <gst/gst.h>
#include <gst/video/video-format.h>

#define MAX_FORMATS 512

static void print_video_format_info(const GstVideoFormat vf);
static void print_uint_array(const unsigned int array[], size_t len);
static const char *vf_flags2str(GstVideoFormatFlags flags);
static const char *v_tile_mode2str(GstVideoTileMode flags);

int main(int argc, char **argv)
{
	GstVideoFormat vfa[MAX_FORMATS];
	size_t n_formats = (argc-1) < MAX_FORMATS? argc-1 : MAX_FORMATS;

	if (argc > 1) {
		for (size_t i = 0; i < n_formats; i++)
			vfa[i] = gst_video_format_from_string(argv[i+1]);
	} else {
		// I couldn't find a better way to find out how many
		// GstVideoFormats are :'(
		size_t i = 0;
		for (; gst_video_format_get_info(i) && i < MAX_FORMATS; i++)
			vfa[i] = i;
		n_formats = i;
	}

	printf("[");
	for (size_t i = 0; i < n_formats; i++) {
		printf("\n\t{");
		print_video_format_info(vfa[i]);
		printf("\n\t}");
		if (i < n_formats-1)
			printf(",");
	}
	printf("\n]\n");

	return 0;
}

static void print_video_format_info(const GstVideoFormat vf)
{
	if (vf == GST_VIDEO_FORMAT_UNKNOWN) {
		printf("\n\t\t\"UNKNOWN\": {}");
		return;
	}

	const GstVideoFormatInfo *vfi = gst_video_format_get_info(vf);

	printf(
	       "\n\t\t\"name\":          \"%s\","
	       "\n\t\t\"description\":   \"%s\","
	       "\n\t\t\"flags\":         \"%s\","
	       "\n\t\t\"bits\":          %u,"
	       "\n\t\t\"n_components\":  %u,"

	       , vfi->name
	       , vfi->description
	       , vf_flags2str(vfi->flags)
	       , vfi->bits
	       , vfi->n_components
	);
	printf("\n\t\t\"shift\":         "); print_uint_array(vfi->shift, vfi->n_components); printf(",");
	printf("\n\t\t\"depth\":         "); print_uint_array(vfi->depth, vfi->n_components); printf(",");
	printf("\n\t\t\"pixel_stride\":  "); print_uint_array((const unsigned*)vfi->pixel_stride, vfi->n_components); printf(",");
	printf("\n\t\t\"n_planes\":      %u,", vfi->n_planes);
	printf("\n\t\t\"plane\":         "); print_uint_array(vfi->plane, vfi->n_planes); printf(",");
	printf("\n\t\t\"poffset\":       "); print_uint_array(vfi->poffset, vfi->n_planes); printf(",");
	printf("\n\t\t\"w_sub\":         "); print_uint_array(vfi->w_sub, vfi->n_components); printf(",");
	printf("\n\t\t\"h_sub\":         "); print_uint_array(vfi->h_sub, vfi->n_components); printf(",");
	printf(
	       "\n\t\t\"unpack_format\": \"%s\","
	       "\n\t\t\"pack_lines\":    %d,"
	       "\n\t\t\"tile_mode\":     \"%s\""
	       // TODO: tile_info
	       , gst_video_format_to_string(vfi->unpack_format)
	       , vfi->pack_lines
	       , v_tile_mode2str(vfi->tile_mode)
	);
}

static void print_uint_array(const unsigned int array[], size_t len)
{
	if (len == 0) {
		printf("[]");
		return;
	}

	printf("[ ");
	for (size_t i = 0; i < len-1; i++) {
		printf("%u, ", array[i]);
	}
	printf("%u ]", array[len-1]);
}

static const char *vf_flags2str(GstVideoFormatFlags flags)
{
	switch(flags) {
		case GST_VIDEO_FORMAT_FLAG_YUV:      return "yuv";
		case GST_VIDEO_FORMAT_FLAG_RGB:      return "rgb";
		case GST_VIDEO_FORMAT_FLAG_GRAY:     return "gray";
		case GST_VIDEO_FORMAT_FLAG_ALPHA:    return "alpha";
		case GST_VIDEO_FORMAT_FLAG_LE:       return "le";
		case GST_VIDEO_FORMAT_FLAG_PALETTE:  return "palette";
		case GST_VIDEO_FORMAT_FLAG_COMPLEX:  return "complex";
		case GST_VIDEO_FORMAT_FLAG_UNPACK:   return "unpack";
		case GST_VIDEO_FORMAT_FLAG_TILED:    return "tiled";
		case GST_VIDEO_FORMAT_FLAG_SUBTILES: return "subtiles";
		default:                             return "???";
	}
}

static const char *v_tile_mode2str(GstVideoTileMode tile_mode)
{
	switch(tile_mode) {
		case GST_VIDEO_TILE_MODE_ZFLIPZ_2X2: return "zflipz_2x2";
		case GST_VIDEO_TILE_MODE_LINEAR:     return "linear";
		case GST_VIDEO_TILE_MODE_UNKNOWN:
		default:
			return "???";
	}
}
