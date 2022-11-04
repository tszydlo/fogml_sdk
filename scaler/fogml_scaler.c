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

#include "fogml_scaler.h"

void min_max_scaler(float *x, fogml_min_max_scaler_config_t *config) {
    for(int i=0; i<config->vector_size; i++) {
        x[i] = (x[i]-config->mins[i]) / (config->maxs[i] - config->mins[i]);
    }
}
