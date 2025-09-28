#ifndef Cubycube_H
#define Cubycube_H

#include "facecube.h"
#include <stdint.h>

// cuby cube using the 'is replaced by' representation
struct cubycube {
  corner_t cp[CORNER_COUNT];

  // corner orientation
  // reference facelets are U1, U3, U5, U7, D1, D3, D5, D7. If the reference
  // facelet of the cuby matches the the facelet position it is 0. 1 for
  // clockwise 2 for counter clockwise rotation
  uint8_t co[CORNER_COUNT];

  // edge permutation
  edge_t ep[EDGE_COUNT];

  // edge orientation
  // reference facelets are U2, U4, U6, U8, D2, D4, D6, D8, F4, F6, B4, B6. If
  // the reference facelet of the cuby matches the reference facelet position
  // the orientation is 0. Otherwise 1
  uint8_t eo[EDGE_COUNT];
};
typedef struct cubycube cubycube_t;

extern const corner_t cornerOrder[CORNER_COUNT];
extern const edge_t edgeOrder[EDGE_COUNT];

cubycube_t *getMoves(void);
cubycube_t *fromFaceCube(facecube_t *facecube);
cubycube_t *getCubycube(void);

cubycube_t *setCoCoord(uint8_t co);
uint16_t coCoord(cubycube_t *cubycube);
uint16_t eoCoord(cubycube_t *cubycube);
uint16_t UDSliceCoord(cubycube_t *cubycube);

uint16_t cpCoord(cubycube_t *cubycube);
uint16_t epCoord(cubycube_t *cubycube);
uint16_t UDSliceSortedCoord(cubycube_t *cubycube);

void domove(cubycube_t *cubycube, faces_t move);

#endif
