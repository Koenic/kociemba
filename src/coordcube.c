#include "coordcube.h"
#include "cubycube.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t coCoordMoveTable[2187][18] = {0};
uint8_t cpCoordMoveTable[40320][18] = {0};
uint8_t eoCoordMoveTable[2048][18] = {0};
// uint8_t epCoordMoveTable[479001600][18] = {0};
uint8_t UDSliceCoordMoveTable[495][18] = {0};
uint8_t UDSliceSortedCoordMoveTable[24][18] = {0};

coordcube_t *fromCubycube(cubycube_t *cubycube) {
  coordcube_t *res = calloc(1, sizeof(coordcube_t));

  res->coCoord = coCoord(cubycube);
  res->cpCoord = cpCoord(cubycube);
  res->UDSliceCoord = UDSliceCoord(cubycube);
  res->eoCoord = eoCoord(cubycube);
  res->epCoord = epCoord(cubycube);
  res->UDSliceSortedCoord = UDSliceSortedCoord(cubycube);

  assert(res->coCoord <= 2186);
  assert(res->cpCoord <= 40319);
  assert(res->eoCoord <= 2047);
  assert(res->epCoord <= 40320);
  assert(res->UDSliceCoord <= 494);
  assert(res->UDSliceSortedCoord <= 23);

  return res;
}

void initMoveTables() {
  for (int i = 0; i < 2187; i++) {
    cubycube_t *cubycube = setCoCoord(i);
    for (int j = 0; j < 18; j++) {
      for (int k = 0; k < 4; k++) {
        domove(cubycube, j);
        if (k != 3) {
          coCoordMoveTable[i][j] = coCoord(cubycube);
        }
      }
    }
  }
}
