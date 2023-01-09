#ifndef _FOGML_ZSCORE
#define _FOGML_ZSCORE

#include "../ports/fogml_ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tinyml_zscore_config {
  float *Q;  //table of Qs for each of dimension points
  float *avg; //Average for each of dimension points
  int n; //number of points in data
  int vector_size; //dimension of each points
} tinyml_zscore_config_t;



void tinyml_zscore_init(tinyml_zscore_config_t *config);

float* tinyml_zscore_score(float *vector, tinyml_zscore_config_t *config);

void tinyml_zscore_learn(float *vector,tinyml_zscore_config_t *config);

#ifdef __cplusplus
}
#endif

#endif
