#include "facecube.h"
#include <stdlib.h>

const facelet_t cornerFacelet[CORNER_COUNT][3] = {
    {U9, R1, F3}, {U7, F1, L3}, {U1, L1, B3}, {U3, B1, R3},
    {D3, F9, R7}, {D1, L9, F7}, {D7, B9, L7}, {D9, R9, B7}};

const facelet_t edgeFacelet[EDGE_COUNT][2] = {
    {U6, R2}, {U8, F2}, {U4, L2}, {U2, B2}, {D6, R8}, {D2, F8},
    {D4, L8}, {D8, B8}, {F6, R4}, {F4, L6}, {B6, L4}, {B4, R6}};

const faces_t cornerColor[CORNER_COUNT][3] = {{U, R, F}, {U, F, L}, {U, L, B},
                                              {U, B, R}, {D, F, R}, {D, L, F},
                                              {D, B, L}, {D, R, B}};

const faces_t edgeColor[EDGE_COUNT][2] = {{U, R}, {U, F}, {U, L}, {U, B},
                                          {D, R}, {D, F}, {D, L}, {D, B},
                                          {F, R}, {F, L}, {B, L}, {B, R}};
const faces_t faces[FACE_COUNT] = {U, R, F, D, L, B};

facecube_t *fromString(char *facestring) {
  facecube_t *res = calloc(1, sizeof(facecube_t));

  for (int i = 0; facestring[i] != '\0'; ++i) {
    switch (facestring[i]) {
    case 'U':
      res->f[i] = U;
      break;
    case 'R':
      res->f[i] = R;
      break;
    case 'F':
      res->f[i] = F;
      break;
    case 'D':
      res->f[i] = D;
      break;
    case 'L':
      res->f[i] = L;
      break;
    case 'B':
      res->f[i] = B;
      break;
    }
  }

  return res;
}