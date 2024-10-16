# How to use it

With no arguments -> all formats
```sh
$ gst_video_format_info_json | less
```

With arguments -> list of formats
```sh
$ gst_video_format_info_json RGBA I420
[
	{
		"name":          "RGBA",
		"description":   "raw video",
		"flags":         "???",
		"bits":          8,
		"n_components":  4,
		"shift":         [ 0, 0, 0, 0 ],
		"depth":         [ 8, 8, 8, 8 ],
		"pixel_stride":  [ 4, 4, 4, 4 ],
		"n_planes":      1,
		"plane":         [ 0 ],
		"poffset":       [ 0 ],
		"w_sub":         [ 0, 0, 0, 0 ],
		"h_sub":         [ 0, 0, 0, 0 ],
		"unpack_format": "ARGB",
		"pack_lines":    1,
		"tile_mode":     "???"
	},
	{
		"name":          "I420",
		"description":   "raw video",
		"flags":         "yuv",
		"bits":          8,
		"n_components":  3,
		"shift":         [ 0, 0, 0 ],
		"depth":         [ 8, 8, 8 ],
		"pixel_stride":  [ 1, 1, 1 ],
		"n_planes":      3,
		"plane":         [ 0, 1, 2 ],
		"poffset":       [ 0, 0, 0 ],
		"w_sub":         [ 0, 1, 1 ],
		"h_sub":         [ 0, 1, 1 ],
		"unpack_format": "AYUV",
		"pack_lines":    1,
		"tile_mode":     "???"
	}
]
```

# How to build/install

```sh
$ meson setup builddir 
$ meson compile -C builddir 
$ meson install -C builddir
```
