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

#include "fogml_anomaly.h"

float distance(float *a, float* b, int k){
    float distance = 0.0;
    for(int i=0; i<k; i++) {
        distance += pow(a[i] - b[i],2);
    }
    distance = sqrt(distance);
    return distance;
}

float anomaly_score(float *x, fogml_anomaly_config_t *config) {
    float dist = 99999;
    int nearest = -1;
    int offset = 0;

    float dist_tmp;
    //find nearest centroid
    for(int i = 0; i < config->clusters; i++) {
        dist_tmp = distance(x, config->centroids + offset, config->vector_size);

        if (dist_tmp < dist) {
            dist = dist_tmp;
            nearest = i;
        }
        offset += config->vector_size;
    }
    return dist - config->zscores[nearest];
}