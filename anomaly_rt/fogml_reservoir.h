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

#ifndef _FOGML_RESERVOIR
#define _FOGML_RESERVOIR

#include "../ports/fogml_ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  {
  int n;  //size of reservoir
  int k;  //number of elements in reservoir
  int vector_size;  //number of elements in the vector
  float *reservoir; //pointer to the reservoir
} tinyml_reservoir_sampling_config_t;

void tinyml_reservoir_sampling(float *vector, tinyml_reservoir_sampling_config_t *config);

#ifdef __cplusplus
}
#endif

#endif
