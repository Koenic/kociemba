#include "coordcube.h"
#include "cubycube.h"
#include <assert.h>
#include <stdlib.h>

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