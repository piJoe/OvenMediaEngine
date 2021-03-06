//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Hyunjun Jang
//  Copyright (c) 2019 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once

#define DASH_MPD_VIDEO_SUFFIX "_video"
#define DASH_MPD_AUDIO_SUFFIX "_audio"
#define DASH_MPD_VIDEO_INIT_FILE_NAME "init_video"
#define DASH_MPD_AUDIO_INIT_FILE_NAME "init_audio"
#define DASH_PLAYLIST_FILE_NAME "manifest"
#define DASH_CORS_FILE_NAME "crossdomain.xml"

#define DASH_SEGMENT_EXT "m4s"
#define DASH_PLAYLIST_EXT "mpd"
#define DASH_LOW_LATENCY_SUFFIX "_ll"

#define DASH_MPD_VIDEO_FULL_SUFFIX DASH_MPD_VIDEO_SUFFIX "." DASH_SEGMENT_EXT
#define DASH_MPD_AUDIO_FULL_SUFFIX DASH_MPD_AUDIO_SUFFIX "." DASH_SEGMENT_EXT
#define DASH_MPD_VIDEO_FULL_INIT_FILE_NAME DASH_MPD_VIDEO_INIT_FILE_NAME "." DASH_SEGMENT_EXT
#define DASH_MPD_AUDIO_FULL_INIT_FILE_NAME DASH_MPD_AUDIO_INIT_FILE_NAME "." DASH_SEGMENT_EXT
#define DASH_PLAYLIST_FULL_FILE_NAME DASH_PLAYLIST_FILE_NAME "." DASH_PLAYLIST_EXT

#define CMAF_MPD_VIDEO_FULL_SUFFIX DASH_MPD_VIDEO_SUFFIX DASH_LOW_LATENCY_SUFFIX "." DASH_SEGMENT_EXT
#define CMAF_MPD_AUDIO_FULL_SUFFIX DASH_MPD_AUDIO_SUFFIX DASH_LOW_LATENCY_SUFFIX "." DASH_SEGMENT_EXT
#define CMAF_MPD_VIDEO_FULL_INIT_FILE_NAME DASH_MPD_VIDEO_INIT_FILE_NAME DASH_LOW_LATENCY_SUFFIX "." DASH_SEGMENT_EXT
#define CMAF_MPD_AUDIO_FULL_INIT_FILE_NAME DASH_MPD_AUDIO_INIT_FILE_NAME DASH_LOW_LATENCY_SUFFIX "." DASH_SEGMENT_EXT
#define CMAF_PLAYLIST_FULL_FILE_NAME DASH_PLAYLIST_FILE_NAME DASH_LOW_LATENCY_SUFFIX "." DASH_PLAYLIST_EXT
