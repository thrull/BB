/*
 * pipeline.h
 *
 *  Created on: 19. 1. 2021
 *      Author: horinek
 */

#ifndef MAIN_PIPELINE_PIPELINE_H_
#define MAIN_PIPELINE_PIPELINE_H_

#include "../common.h"

#include "esp_peripherals.h"

#include "audio_element.h"
#include "audio_pipeline.h"

#include "a2dp_stream.h"
#include "filter_resample.h"
#include "raw_stream.h"
#include "downmix.h"


#define NUMBER_OF_SOURCES		2

#define	SOURCE_SOUND_INDEX		0
#define	SOURCE_BT_INDEX			1

#define OUTPUT_SAMPLERATE		48000
#define OUTPUT_CHANNELS			1

typedef struct
{
	audio_pipeline_handle_t pipe;

	audio_element_handle_t mix;
	audio_element_handle_t i2s_writer;
} output_pipe_t;

typedef struct
{
	audio_pipeline_handle_t pipe;

	audio_element_handle_t a2dp;
	audio_element_handle_t filter;
	audio_element_handle_t raw;

} bluetooth_pipe_t;

typedef struct
{
	audio_pipeline_handle_t pipe;

	audio_element_handle_t stream;
	audio_element_handle_t decoder;
	audio_element_handle_t filter;
	audio_element_handle_t raw;

	SemaphoreHandle_t lock;

	uint8_t id;
	uint32_t total_len;
	uint32_t pos;
	bool request;

} sound_pipe_t;

typedef struct
{
//	audio_pipeline_handle_t music; 		//music files from stm32
//	audio_pipeline_handle_t sound; 		//sound effect/alerts from stm32
//	audio_pipeline_handle_t vario; 		//vario output from esp32

	bluetooth_pipe_t bluetooth;			//bt audio
	sound_pipe_t sound;			//sound effect/alerts from stm32

	output_pipe_t output;

	audio_event_iface_handle_t events;	//events queue

} pipelines_t;

extern pipelines_t pipes;

void pipeline_init();
void pipeline_loop();

#endif /* MAIN_PIPELINE_PIPELINE_H_ */