#ifndef FOGML_KNN_CLASSIFIER
#define FOGML_KNN_CLASSIFIER

typedef struct {
  int n_neighbors;
  int n_features;
  float *data_features;
  int *data_classes;
  int n_data_points;
  int *nearest_classes_buffer;
  float *nearest_distances_buffer;
  int *nn_class_counts_buffer;
} fogml_knn_classifier_config_t;

float distance(float *xs, int n, float *ys);

void knn_predict(float *xs, int n, int *ys,
                 fogml_knn_classifier_config_t *config);

#endif
