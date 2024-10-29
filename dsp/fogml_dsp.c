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

#include "fogml_dsp.h"

int tinyml_dsp_processing_base(float *time_series_data, float *vector, int offset, tinyml_block_base_config_t *base_config, tinyml_dsp_config_t *config ) {
    float *sum = (float*)malloc(sizeof(float) * config->axis_n);
    float *min = (float*)malloc(sizeof(float) * config->axis_n);
    float *max = (float*)malloc(sizeof(float) * config->axis_n);

    for(int j=0; j<config->axis_n; j++) {
        min[j] =  999999;
        max[j] = -999999;
        sum[j] = 0.0;

        for(int i=0; i<config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];

            if (v<min[j]) {
                min[j] = v;
            };

            if (v>max[j]) {
                max[j] = v;
            }

            sum[j] += v;
        }

        vector[offset++] = max[j] - min[j];
        vector[offset++] = sum[j] / config->time_ticks;
    }

    free(sum);
    free(min);
    free(max);

    return config->axis_n * 2; // (max - min), mean
}

int tinyml_dsp_processing_crossings(float *time_series_data, float *vector, int offset, tinyml_block_crossings_config_t *crossings_config, tinyml_dsp_config_t *config ) {
    float *sum = (float*)malloc(sizeof(float) * config->axis_n);
    float *cross = (float*)malloc(sizeof(float) * config->axis_n);

    for(int j=0; j<config->axis_n; j++) {
        cross[j] = 0.0;
        sum[j] = 0.0;

        for(int i=0; i<config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];
            sum[j] += v;
        }

        float mean = sum[j] / config->time_ticks;

        for(int i=0; i<config->time_ticks-1; i++) {
            float v = time_series_data[i * config->axis_n + j];
            float v1 = time_series_data[(i+1) * config->axis_n + j];

            if ( ( v<(mean-crossings_config->threshold) && v1>(mean-crossings_config->threshold) ) || 
               ( v>(mean+crossings_config->threshold) && v1<(mean+crossings_config->threshold) ) ) {
                cross[j] += 1;
            }
        }

        vector[offset++] = cross[j];
    }

    free(sum);
    free(cross);

    return config->axis_n * 1; // crossings
}

int tinyml_dsp_processing_minmax(float *time_series_data, float *vector, int offset, tinyml_block_minmax_config_t *minmax_config, tinyml_dsp_config_t *config ) {
    float *min = (float*)malloc(sizeof(float) * config->axis_n);
    float *max = (float*)malloc(sizeof(float) * config->axis_n);

    for(int j=0; j<config->axis_n; j++) {
        min[j] =  999999;
        max[j] = -999999;

        for(int i=0; i < config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];

            if (v<min[j]) {
                min[j] = v;
            };

            if (v>max[j]) {
                max[j] = v;
            }

        }

        vector[offset++] = min[j];
        vector[offset++] = max[j];
    }

    free(min);
    free(max);

    return config->axis_n * 2; // min, max
}


int tinyml_dsp_processing_energy(float *time_series_data, float *vector, int offset, tinyml_block_energy_config_t *base_config, tinyml_dsp_config_t *config ) {
    int int_offset = offset;

    float *energy = (float*)malloc(sizeof(float) * config->axis_n);

    float mean;

    for(int j=0; j<config->axis_n; j++) {
        energy[j] =  0.0;

        mean = 0;

        for(int i = 0; i < config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];
            mean += v;
        }

        mean = mean / config->time_ticks;


        for(int i=0; i<config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];
            energy[j] += pow(v-mean, 2);
        }

        vector[int_offset++] = energy[j];
    }

    free(energy);

    return int_offset - offset;
}

int tinyml_dsp_processing_variance(float *time_series_data, float *vector, int offset, tinyml_block_variance_config_t *base_config, tinyml_dsp_config_t *config ) {
    int int_offset = offset;

    float *sum = (float*)malloc(sizeof(float) * config->axis_n);
    float *sum2 = (float*)malloc(sizeof(float) * config->axis_n);

    for(int j=0; j<config->axis_n; j++) {
        sum[j] =  0.0;
        sum2[j] =  0.0;

        for(int i = 0; i < config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];
            sum[j] += v;
            sum2[j] += v*v;
        }

        vector[int_offset++] = sum2[j] / config->time_ticks - pow(sum[j] / config->time_ticks, 2);
    }

    free(sum);
    free(sum2);
    return int_offset - offset;
}

int tinyml_dsp_processing_passthrought(float *time_series_data, float *vector, int offset, tinyml_block_passthrought_config_t *passthrought_config, tinyml_dsp_config_t *config ) {

    for(int j=0; j<config->axis_n; j++) {
        float v = time_series_data[config->time_ticks * config->axis_n + j];
        vector[offset++] = v;
    }

    return config->axis_n;
}

kiss_fft_scalar *in = NULL;
kiss_fft_cpx *out = NULL;
kiss_fftr_cfg cfg = NULL;
float *fft_amp = NULL;

int tinyml_dsp_processing_fft(float *time_series_data, float *vector, int offset, tinyml_block_fft_config_t *fft_config, tinyml_dsp_config_t *config ) {
    //kiss_fft_scalar in[N];
    //kiss_fft_cpx out[N / 2 + 1];

    if (in ==  NULL) {
        in = (kiss_fft_scalar*)malloc(sizeof(kiss_fft_scalar) * config->time_ticks);
        out = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx) * config->time_ticks);
        cfg = kiss_fftr_alloc(config->time_ticks, 0, NULL, NULL);
        fft_amp = (float*)malloc(sizeof(float) * (config->time_ticks / 2 + 1));

    }

    //https://stackoverflow.com/questions/14536950/applying-kiss-fft-on-audio-samples-and-getting-nan-output
    float max_amp = -1;
    int max_amp_i = -1;

    for(int j=0; j<config->axis_n; j++) {

        //fogml_printf("\n[");
        for(int i=0; i<config->time_ticks; i++) {
            float v = time_series_data[i * config->axis_n + j];
            in[i] = v;
            //fogml_printf_float(v);
            //fogml_printf(" ");
        }
        //fogml_printf("]\n");
        if (cfg != NULL)
        {
            kiss_fftr(cfg, in, out);

            //fogml_printf("\n>");
            for(int l = 0; l < config->time_ticks / 2 + 1; l++) {
                float amp = sqrtf(out[l].r*out[l].r+out[l].i*out[l].i) / config->time_ticks;
                fft_amp[l] = amp;
                
                //fogml_printf_float(amp);
                //fogml_printf(" ");
            }
            
            //fogml_printf("<\n");

            //finding 1st peak
            max_amp = -1;
            max_amp_i = -1;
            //DC component should not be included
            for(int l = 1; l < config->time_ticks / 2 + 1; l++) {
                if (fft_amp[l]>max_amp){
                    max_amp = fft_amp[l];
                    max_amp_i = l;
                }
            }

        } else {
            fogml_printf("FFT NO MEMORY\n");
        }

        if (max_amp<fft_config->treshold){
            vector[offset++] = 0;
            vector[offset++] = max_amp;
        } else {
            vector[offset++] = (fft_config->freq / 2 / (config->time_ticks / 2)) * max_amp_i;
            vector[offset++] = max_amp;
        }
    }

    // free(cfg);

    return config->axis_n;
}

//t1_x, t1_y, t1_z, t2_x, t2_y, t2_z
void tinyml_dsp(float *time_series_data, float *vector, tinyml_dsp_config_t *config) {
    //Serial.print("DSP BLOCKS = ");
    int blocks_num =config->blocks_num;
    //Serial.println(blocks_num);
    int offset = 0;
    for(int b=0; b<blocks_num; b++) {
        switch (config->blocks[b]->type){
            case TINYML_DSP_BASE:
                //Serial.println("DSP BASE BLOCK");
                offset += tinyml_dsp_processing_base(time_series_data, vector, offset, (tinyml_block_base_config_t*) config->blocks[b]->config, config);
                break;
            case TINYML_DSP_ENERGY:
                //Serial.println("DSP ENERGY BLOCK");
                offset += tinyml_dsp_processing_energy(time_series_data, vector, offset, (tinyml_block_energy_config_t*) config->blocks[b]->config, config);
                break;
            case TINYML_DSP_VARIANCE:
                //Serial.println("DSP VARIANCE BLOCK");
                offset += tinyml_dsp_processing_variance(time_series_data, vector, offset, (tinyml_block_variance_config_t*) config->blocks[b]->config, config);
                break;
            case TINYML_DSP_MINMAX:
                //Serial.println("DSP MINMAX BLOCK");
                offset += tinyml_dsp_processing_minmax(time_series_data, vector, offset, (tinyml_block_minmax_config_t*) config->blocks[b]->config, config);
                break;
            case TINYML_DSP_CROSSINGS:
                //Serial.println("DSP CROSSINGS BLOCK");
                offset += tinyml_dsp_processing_crossings(time_series_data, vector, offset, (tinyml_block_crossings_config_t*) config->blocks[b]->config, config);
                break;
            case TINYML_DSP_FFT:
                //Serial.println("FFT BLOCK");
                offset += tinyml_dsp_processing_fft(time_series_data, vector, offset, (tinyml_block_fft_config_t*) config->blocks[b]->config, config);
                break;
            default:
                break;
        }
    }
} 
