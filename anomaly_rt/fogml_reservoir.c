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

#include "fogml_reservoir.h"

int tinyml_random_nextint(int min, int max) {
  return fogml_random(min, max);
}

void tinyml_reservoir_verbose(tinyml_reservoir_sampling_config_t *config) {
  fogml_printf("reservoir = [");
  for(int i=0; i<config->k; i++) {
    fogml_printf("[");
    for(int j=0; j<config->vector_size; j++){
      fogml_printf_float(config->reservoir[i*config->vector_size + j]);
      
      if (j<config->vector_size - 1) {
        fogml_printf(", ");
      }
    }
    fogml_printf("]");
      if (i < config->k - 1) {
        fogml_printf(",");
      } else {
        fogml_printf("\n");
      }

  }
  fogml_printf("]\n");
}

void tinyml_reservoir_sampling(float *vector, tinyml_reservoir_sampling_config_t *config) {
  if (config->k < config->n) {
    memcpy(config->reservoir + config->k * config->vector_size, vector, config->vector_size * sizeof(float));
    config->k++;
  } else {
    int i = tinyml_random_nextint(0, config->n);
    if (i < config->n) {
      memcpy(config->reservoir + i * config->vector_size, vector, config->vector_size * sizeof(float));
    }
  }
}
