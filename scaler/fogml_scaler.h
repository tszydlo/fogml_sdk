#ifndef __FOGML_NORMALIZER_H__
#define __FOGML_NORMALIZER_H__

#include "../ports/fogml_ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int vector_size; //dimension of each point
    float* mins;
    float* maxs;
} fogml_min_max_scaler_config_t;

void min_max_scaler(float *x, fogml_min_max_scaler_config_t *config);

#ifdef __cplusplus
} // extern "C"
#endif

#endif