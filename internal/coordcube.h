#ifndef COORDCUBE_H
#define COORDCUBE_H

#include "cubycube.h"
#include <stdint.h>

struct coordcube {
  // phase 1
  // twist
  uint16_t coCoord;
  // flip
  uint16_t eoCoord;
  // ud slice
  uint16_t UDSliceCoord;

  // phase 2
  //
  uint16_t cpCoord;
  uint16_t epCoord;
  uint16_t UDSliceSortedCoord;
};
typedef struct coordcube coordcube_t;

coordcube_t *fromCubycube(cubycube_t *cubycube);

#endif