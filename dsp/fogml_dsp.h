/*
   Copyright 2021 FogML
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef _FOGML_DSP
#define _FOGML_DSP

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <math.h>
#include "kissfft/kiss_fftr.h"
#include "../ports/fogml_ports.h"

#define TINYML_DSP_FFT  1 //FFT 1 peak
#define TINYML_DSP_BASE  2 // (max-min), mean
#define TINYML_DSP_VARIANCE  3 //variance
#define TINYML_DSP_ENERGY  4 //energy
#define TINYML_DSP_CROSSINGS  5 //crossing through mean
#define TINYML_DSP_MINMAX  6 //min, max

#define TINYML_DSP_FFT_LEN  2 // amp, freq
#define TINYML_DSP_BASE_LEN  2 // (max-min), mean
#define TINYML_DSP_VARIANCE_LEN  1 //variance
#define TINYML_DSP_ENERGY_LEN  1 //energy
#define TINYML_DSP_CROSSINGS_LEN  1 //crossing through mean
#define TINYML_DSP_MINMAX_LEN  2 //min, max


//#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))

typedef struct {
    float freq;
    float treshold;
} tinyml_block_fft_config_t;

typedef struct {
} tinyml_block_base_config_t;

typedef struct {
} tinyml_block_stat_config_t;

typedef struct {
} tinyml_block_passthrought_config_t;

typedef struct {
    float threshold;
} tinyml_block_crossings_config_t;

typedef struct {
} tinyml_block_energy_config_t;

typedef struct {
} tinyml_block_variance_config_t;

typedef struct {
} tinyml_block_minmax_config_t;

typedef struct {
    int type;
    void *config;
} tinyml_dsp_block_t;

typedef struct {
    int time_ticks;
    int axis_n;
    int blocks_num;
    tinyml_dsp_block_t **blocks;
} tinyml_dsp_config_t;

void tinyml_dsp(float *time_series_data, float *vector, tinyml_dsp_config_t *config); 

#ifdef __cplusplus
} // extern "C"
#endif

#endif
