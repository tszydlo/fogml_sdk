#include "fogml_zscore.h"
#include "math.h"
#include "stdlib.h"


void tinyml_zscore_learn(float *vector,tinyml_zscore_config_t *config){
    for(int i =0;i<config->vector_size;i++){
        int n = config->n;
        float avg = config->avg[i];

        float q  =config->Q[i];
        config->Q[i] =  q + n/(n+1)*pow(vector[i] - avg, 2);

        config->avg[i] = avg + (vector[i] - avg)/(n+1);

        config->n = n+1;
    }

}


void tinyml_zscore_init(int vector_size,tinyml_zscore_config_t *config){

    config->vector_size = vector_size;
    config->avg = (float*) calloc(vector_size, sizeof(float));
    config->Q = (float*) calloc(vector_size, sizeof(float));
    config->n = 0;
}