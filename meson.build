project('gst_video_format_info_json', 'C')

add_project_arguments([
  '-Wall',
  '-Wextra',
  '-Werror',
], language: 'C')

dependencies = [
  dependency('gstreamer-1.0'),
  dependency('gstreamer-video-1.0'),
]

executable(
  'gst_video_format_info_json',
  'gst_video_format_info_json.c',
  dependencies: dependencies,
  install : true,
)
