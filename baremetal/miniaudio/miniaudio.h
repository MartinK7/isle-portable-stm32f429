#ifndef MXMINIAUDIO_STUB_H
#define MXMINIAUDIO_STUB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <string.h>

extern ssize_t _write(int fd, const void *buf, size_t count);
#define MA_STUB_ENTRY \
	do { \
		const char *prefix = "[STUB] miniaudio "; \
		const char *suffix = "() is not implemented!\r\n"; \
		_write(1, prefix, strlen(prefix)); \
		_write(1, __func__, strlen(__func__)); \
		_write(1, suffix, strlen(suffix)); \
	} while(0);

// ----- Basic Types -----
typedef int           ma_result, ma_int32;
typedef unsigned int  ma_uint32;
typedef unsigned long long ma_uint64;
typedef int           ma_bool32;
typedef unsigned char ma_uint8;

#define MA_SUCCESS    0
#define MA_ERROR     -1
#define MA_TRUE       1
#define MA_FALSE      0

// ----- Audio Format -----
typedef enum
{
	/*
	I like to keep these explicitly defined because they're used as a key into a lookup table. When items are
	added to this, make sure there are no gaps and that they're added to the lookup table in ma_get_bytes_per_sample().
	*/
	ma_format_unknown = 0,
	ma_format_u8      = 1,
	ma_format_s16     = 2,
	ma_format_s24     = 3,
	ma_format_s32     = 4,
	ma_format_f32     = 5,
	ma_format_count
} ma_format;

// ----- Engine Types -----
typedef struct ma_engine_config
{
	int dummy;
	int noDevice;
	int channels;
	int sampleRate;
} ma_engine_config;

typedef struct ma_engine_config ma_audio_buffer_config;

typedef struct ma_engine
{
	int dummy;
	ma_uint32 sampleRate;
	ma_uint32 channels;
	int format;
} ma_engine;

// ----- Dummy Structs for Compatibility -----
typedef struct ma_sound        { int dummy; } ma_sound;
typedef struct ma_audio_buffer { int dummy; } ma_audio_buffer;
typedef void ma_data_source;
typedef struct ma_allocation_callbacks { int dummy; } ma_allocation_callbacks;
typedef struct ma_sound_group  { int dummy; } ma_sound_group;
typedef struct ma_engine ma_pcm_rb;

static inline ma_engine_config ma_engine_config_init()
{
	MA_STUB_ENTRY
	
	ma_engine_config cfg = { 0 };
	return cfg;
}

static inline ma_result ma_engine_init(const ma_engine_config* pConfig, ma_engine* pEngine)
{
	MA_STUB_ENTRY
	
	if (pEngine)
	{
		pEngine->sampleRate = 48000;
		pEngine->channels = 2;
		pEngine->format = ma_format_f32;
	}
	(void)pConfig;
	return MA_SUCCESS;
}

static inline void ma_engine_uninit(ma_engine* pEngine)
{
	MA_STUB_ENTRY
	
	(void)pEngine;
}

static inline ma_uint32 ma_engine_get_sample_rate(ma_engine* pEngine)
{
	MA_STUB_ENTRY
	
	return pEngine ? pEngine->sampleRate : 0;
}

static inline ma_uint32 ma_engine_get_channels(ma_engine* pEngine)
{
	MA_STUB_ENTRY
	
	return pEngine ? pEngine->channels : 0;
}

static inline ma_result ma_engine_read_pcm_frames(ma_engine* pEngine, void* pFramesOut, ma_uint64 frameCount, ma_uint64* pFramesRead)
{
	MA_STUB_ENTRY
	
	if (pFramesRead) *pFramesRead = 0;
	(void)pEngine; (void)pFramesOut; (void)frameCount;
	return MA_SUCCESS;
}

static inline float ma_volume_db_to_linear(float db)
{
	MA_STUB_ENTRY
	
	(void)db;
	return 1.0f;
}

static inline void ma_sound_uninit(ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	(void)pSound;
}

static inline void ma_pcm_rb_uninit(ma_pcm_rb* pRB)
{
	MA_STUB_ENTRY
	
	(void)pRB;
}

static inline void ma_audio_buffer_uninit(ma_audio_buffer* pAudioBuffer)
{
	MA_STUB_ENTRY
	
	(void)pAudioBuffer;
}

static inline ma_audio_buffer_config ma_audio_buffer_config_init(ma_format format, ma_uint32 channels, ma_uint64 sizeInFrames, const void* pData, const ma_allocation_callbacks* pAllocationCallbacks)
{
	MA_STUB_ENTRY
}

static inline ma_result ma_audio_buffer_init(const ma_audio_buffer_config* pConfig, ma_audio_buffer* pAudioBuffer)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_result ma_audio_buffer_init_ex(const ma_audio_buffer_config* pConfig, ma_bool32 doCopy, ma_audio_buffer* pAudioBuffer)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_uint32 ma_calculate_buffer_size_in_frames_from_milliseconds(ma_uint32 bufferSizeInMilliseconds, ma_uint32 sampleRate)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_result ma_pcm_rb_acquire_write(ma_pcm_rb* pRB, ma_uint32* pSizeInFrames, void** ppBufferOut)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_result ma_pcm_rb_commit_write(ma_pcm_rb* pRB, ma_uint32 sizeInFrames)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_result ma_pcm_rb_init(ma_format format, ma_uint32 channels, ma_uint32 bufferSizeInFrames, void* pOptionalPreallocatedBuffer, const ma_allocation_callbacks* pAllocationCallbacks, ma_pcm_rb* pRB)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline ma_int32 ma_pcm_rb_pointer_distance(ma_pcm_rb* pRB)
{
	MA_STUB_ENTRY
	
	return 0;
}

static inline void ma_pcm_rb_set_sample_rate(ma_pcm_rb* pRB, ma_uint32 sampleRate)
{
	MA_STUB_ENTRY
}

static inline ma_result ma_sound_init_from_data_source(ma_engine* pEngine, ma_data_source* pDataSource, ma_uint32 flags, ma_sound_group* pGroup, ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	return 0;
}

#define MA_SOUND_FLAG_NO_SPATIALIZATION 0x01

static inline ma_result ma_sound_start(ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_stop(ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	return MA_SUCCESS;
}

static inline ma_bool32 ma_sound_is_playing(ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	return MA_FALSE;
}

static inline ma_result ma_sound_seek_to_pcm_frame(ma_sound* pSound, ma_uint64 frameIndex)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	(void)frameIndex;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_doppler_factor(ma_sound* pSound, float dopplerFactor)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	(void)dopplerFactor;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_looping(ma_sound* pSound, ma_bool32 isLooping)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	(void)isLooping;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_volume(ma_sound* pSound, float volume)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	(void)volume;
	return MA_SUCCESS;
}

static inline ma_bool32 ma_sound_at_end(ma_sound* pSound)
{
	MA_STUB_ENTRY
	
	(void)pSound;
	return MA_TRUE;
}

static inline ma_result ma_engine_listener_set_position(ma_engine* pEngine, ma_uint32 listenerIndex, float x, float y, float z)
{
	MA_STUB_ENTRY
	
	(void)pEngine; (void)listenerIndex; (void)x; (void)y; (void)z;
	return MA_SUCCESS;
}

static inline ma_result ma_engine_listener_set_direction(ma_engine* pEngine, ma_uint32 listenerIndex, float x, float y, float z)
{
	MA_STUB_ENTRY
	
	(void)pEngine; (void)listenerIndex; (void)x; (void)y; (void)z;
	return MA_SUCCESS;
}

static inline ma_result ma_engine_listener_set_world_up(ma_engine* pEngine, ma_uint32 listenerIndex, float x, float y, float z)
{
	MA_STUB_ENTRY
	
	(void)pEngine; (void)listenerIndex; (void)x; (void)y; (void)z;
	return MA_SUCCESS;
}

static inline ma_result ma_engine_listener_set_velocity(ma_engine* pEngine, ma_uint32 listenerIndex, float x, float y, float z)
{
	MA_STUB_ENTRY
	
	(void)pEngine; (void)listenerIndex; (void)x; (void)y; (void)z;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_position(ma_sound* pSound, float x, float y, float z)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)x; (void)y; (void)z;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_min_distance(ma_sound* pSound, float distance)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)distance;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_max_distance(ma_sound* pSound, float distance)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)distance;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_rolloff(ma_sound* pSound, float rolloff)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)rolloff;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_pitch(ma_sound* pSound, float pitch)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)pitch;
	return MA_SUCCESS;
}

static inline ma_result ma_sound_set_spatialization_enabled(ma_sound* pSound, ma_bool32 enabled)
{
	MA_STUB_ENTRY
	
	(void)pSound; (void)enabled;
	return MA_SUCCESS;
}

// ----- Utility: Get bytes per frame based on format and channels -----
static inline ma_uint32 ma_get_bytes_per_frame(ma_uint32 format, ma_uint32 channels)
{
	MA_STUB_ENTRY
	
	ma_uint32 bytesPerSample = 0;
	switch (format)
	{
		case ma_format_u8:   bytesPerSample = 1; break;
		case ma_format_s16:  bytesPerSample = 2; break;
		case ma_format_s24:  bytesPerSample = 3; break;
		case ma_format_s32:  bytesPerSample = 4; break;
		case ma_format_f32:  bytesPerSample = 4; break;
		default: return 0;
	}
	return bytesPerSample * channels;
}

#ifdef __cplusplus
}
#endif

#endif // MXMINIAUDIO_STUB_H

