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

#ifndef _FOGML_LOF
#define _FOGML_LOF

#include "../ports/fogml_ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tinyml_lof_config {
  int parameter_k;  //k nearest neighbours are considered
  float *k_distance;  //table of k-distance for each of n points
  float *lrd; //Local Reachability Density for each of n points
  int n; //number of points in data
  int vector_size; //dimension of each points
  float *data; //set of points
} tinyml_lof_config_t;


void tinyml_lof_init(tinyml_lof_config_t *config);

float tinyml_lof_score(float *vector, tinyml_lof_config_t *config);

void tinyml_lof_learn(tinyml_lof_config_t *config);

#ifdef __cplusplus
}
#endif

#endif
