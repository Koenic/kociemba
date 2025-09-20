#include "cubycube.h"
#include "facecube.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

cubycube_t[FACE_COUNT] getMoves(void) {
  static cubycube_t moveCube[6];
  static const corner_t cpU[8] = {UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB};
  static const uint8_t coU[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  static const edge_t epU[12] = {UB, UR, UF, UL, DR, DF,
                                 DL, DB, FR, FL, BL, BR};
  static const uint8_t eoU[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpR[8] = {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR};
  static const uint8_t coR[8] = {2, 0, 0, 1, 1, 0, 0, 2};
  static const edge_t epR[12] = {FR, UF, UL, UB, BR, DF,
                                 DL, DB, DR, FL, BL, UR};
  static const uint8_t eoR[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpF[8] = {UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB};
  static const uint8_t coF[8] = {1, 2, 0, 0, 2, 1, 0, 0};
  static const edge_t epF[12] = {UR, FL, UL, UB, DR, FR,
                                 DL, DB, UF, DF, BL, BR};
  static const uint8_t eoF[12] = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};
  static const corner_t cpD[8] = {URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR};
  static const uint8_t coD[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  static const edge_t epD[12] = {UR, UF, UL, UB, DF, DL,
                                 DB, DR, FR, FL, BL, BR};
  static const uint8_t eoD[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpL[8] = {URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB};
  static const uint8_t coL[8] = {0, 1, 2, 0, 0, 2, 1, 0};
  static const edge_t epL[12] = {UR, UF, BL, UB, DR, DF,
                                 FL, DB, FR, UL, DL, BR};
  static const uint8_t eoL[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpB[8] = {URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL};
  static const uint8_t coB[8] = {0, 0, 1, 2, 0, 0, 2, 1};
  static const edge_t epB[12] = {UR, UF, UL, BR, DR, DF,
                                 DL, BL, FR, FL, UB, DB};
  static const uint8_t eoB[12] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};
}

cubycube_t *fromFaceCube(facecube_t *facecube) {
  cubycube_t *res = calloc(1, sizeof(cubycube_t));

  // determine corners
  for (int i = 0; i < CORNER_COUNT; ++i) {
    int orient = 0;
    for (orient = 0; orient < 3; ++orient) {
      // U and D are the reference faces
      if (facecube->f[cornerFacelet[i][orient]] == U ||
          facecube->f[cornerFacelet[i][orient]] == D) {
        break;
      }
    }

    // the two other faces of the cuby determine which cuby it is
    faces_t col1 = facecube->f[cornerFacelet[i][(orient + 1) % 3]];
    faces_t col2 = facecube->f[cornerFacelet[i][(orient + 2) % 3]];

    int perm = 0;
    for (perm = 0; perm < CORNER_COUNT; ++perm) {
      if (cornerColor[perm][1] == col1 && cornerColor[perm][2] == col2) {
        break;
      }
    }
    res->co[i] = orient;
    res->cp[i] = perm;
  }

  // determine edges
  for (int i = 0; i < EDGE_COUNT; ++i) {
    for (int perm = 0; perm < EDGE_COUNT; ++perm) {
      if (facecube->f[edgeFacelet[i][0]] == edgeColor[perm][0] &&
          facecube->f[edgeFacelet[i][1]] == edgeColor[perm][1]) {
        res->eo[i] = 0;
        res->ep[i] = perm;

        break;
      }
      if (facecube->f[edgeFacelet[i][0]] == edgeColor[perm][1] &&
          facecube->f[edgeFacelet[i][1]] == edgeColor[perm][0]) {
        res->eo[i] = 1;
        res->ep[i] = perm;

        break;
      }
    }
  }
  return res;
}

cubycube_t *getCubycube() {
  const static corner_t cp[CORNER_COUNT] = {URF, UFL, ULB, UBR,
                                            DFR, DLF, DBL, DRB};
  const static uint8_t co[CORNER_COUNT] = {
      0, 0, 0, 0, 0, 0, 0, 0,
  };

  const static edge_t ep[EDGE_COUNT] = {UR, UF, UL, UB, DR, DF,
                                        DL, DB, FR, FL, BL, BR};

  const static uint8_t eo[EDGE_COUNT] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  cubycube_t *result = calloc(1, sizeof(cubycube_t));
  memcpy(result->co, co, CORNER_COUNT * sizeof(uint8_t));
  memcpy(result->cp, cp, CORNER_COUNT * sizeof(corner_t));
  memcpy(result->eo, eo, EDGE_COUNT * sizeof(uint8_t));
  memcpy(result->ep, ep, EDGE_COUNT * sizeof(edge_t));

  return result;
}

uint16_t coCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = 0; i < CORNER_COUNT; ++i) {
    coord = coord * 3 + cubycube->co[i];
  }
  return coord;
}

uint16_t eoCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = 0; i < EDGE_COUNT; ++i) {
    coord = coord * 2 + cubycube->eo[i];
  }
  return coord;
}

uint16_t cnk(uint16_t n, uint16_t k) {
  if (k < 0 || k > n)
    return 0;
  if (k == 0 || k == n)
    return 1;

  if (k > n - k)
    k = n - k;

  uint16_t result = 1;
  for (int i = 1; i <= k; i++) {
    result *= (n - k + i);
    result /= i;
  }
  return result;
}

uint16_t UDSliceCoord(cubycube_t *cubycube) {
  uint16_t occupied = -1;
  uint16_t coord = 0;
  for (uint16_t n = 0; n < 11; n++) {
    if (cubycube->ep[n] >= FR) {
      occupied++;
    } else if (occupied >= 0) {
      coord += cnk(n, occupied);
    }
  }
  return coord;
}

uint16_t cpCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = CORNER_COUNT - 1; i > 0; --i) {
    uint16_t count = 0;
    for (int j = i - 1; j >= 0; --j) {
      if (cubycube->cp[j] > cubycube->cp[i]) {
        count++;
      }
    }
    coord = (coord + count) * i;
  }
  return coord;
}

uint16_t epCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = EDGE_COUNT - 1; i > 0; --i) {
    uint16_t count = 0;
    for (int j = i - 1; j >= 0; --j) {
      if (cubycube->ep[j] > cubycube->ep[i]) {
        count++;
      }
    }
    coord = (coord + count) * i;
  }
  return coord;
}

// simplified coord from the kociemba website. We do not care for an optimal
// solver
uint16_t UDSliceSortedCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = EDGE_COUNT - FR - 1; i > 0; --i) {
    uint16_t count = 0;
    for (int j = i - 1; j >= 0; --j) {
      if (cubycube->ep[j + FR] > cubycube->ep[i + FR]) {
        count++;
      }
    }
    coord = (coord + count) * i;
  }
  return coord;
}