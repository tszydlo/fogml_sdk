#include "knn_classifier.h"

float distance(float *xs, int n, float *ys) {
  float d = 0;
  for (int i = 0; i < n; ++i) {
    float x_minus_y = xs[i] - ys[i];
    d += x_minus_y * x_minus_y;
  }

  return d;
}

void push_into_ordered_list(int *classes, float *distances, int list_size,
                            int class_index, float dist) {
  int can_fast_path_exit = 1;
  for (int i = 0; i < list_size; ++i) {
    if (classes[i] == -1) {
      can_fast_path_exit = 0;
      break;
    }

    if (dist < distances[i]) {
      can_fast_path_exit = 0;
      break;
    }
  }

  if (can_fast_path_exit) {
    return;
  }

  for (int i = 0; i < list_size; ++i) {
    if (classes[i] == -1) {
      classes[i] = class_index;
      distances[i] = dist;
      return;
    }

    if (dist < distances[i]) {
      int popped_class = classes[i];
      float popped_distance = distances[i];

      classes[i] = class_index;
      distances[i] = dist;

      if (i != list_size - 1) {
        push_into_ordered_list(classes, distances, list_size, popped_class,
                               popped_distance);
      }
    }
  }
}

float knn_classify(float *x, fogml_knn_classifier_config_t *config) {
  for (int *c = config->nearest_classes_buffer;
       c != config->nearest_classes_buffer + config->n_neighbors; ++c) {
    *c = -1;
  }

  for (int j = 0; j < config->n_data_points; ++j) {
    float d = distance(x, config->n_features,
                       config->data_features + j * config->n_features);
    push_into_ordered_list(config->nearest_classes_buffer, config->nearest_distances_buffer,
                           config->n_neighbors, config->data_classes[j], d);
  }

  for (int *c = config->nn_class_counts_buffer;
       c != config->nn_class_counts_buffer + config->n_neighbors; ++c) {
    *c = 0;
  }

  for (int j = 0; j < config->n_neighbors; ++j) {
    for (int k = 0; k < config->n_neighbors; ++k) {
      if (k != j && config->nearest_classes_buffer[j] == config->nearest_classes_buffer[k]) {
        config->nn_class_counts_buffer[j]++;
      }
    }
  }

  int most_popular_index = 0;
  for (int j = 1; j < config->n_neighbors; ++j) {
    if (config->nn_class_counts_buffer[j] >
        config->nn_class_counts_buffer[most_popular_index]) {
      most_popular_index = j;
    }
  }

  float res = config->nearest_classes_buffer[most_popular_index];

  return res;
}

void knn_predict(float *xs, int n, int *ys,
                 fogml_knn_classifier_config_t *config) {
  for (int i = 0; i < n; ++i) {
    float *x = xs + i * config->n_features;

    ys[i] = knn_classify(x, config);
  }
}
