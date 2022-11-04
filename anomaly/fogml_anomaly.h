#ifndef __FOGML_ANOMALY_H__
#define __FOGML_ANOMALY_H__

#include "../ports/fogml_ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int clusters;
    int vector_size; //dimension of each point
    float* zscores;
    float* centroids;
} fogml_anomaly_config_t;

float anomaly_score(float *x, fogml_anomaly_config_t *config);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
