#include "neural.h"

struct Node {
  double *weights;
  double bias;
};

struct Network {
  struct Node *layers;
  int layer_size;
};

/*Network new_network(int *layers,int layer_size) {
  
}*/
