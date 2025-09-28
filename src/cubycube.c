#include "cubycube.h"
#include "facecube.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

cubycube_t *getMoves(void) {
  static cubycube_t moves[FACE_COUNT] = {0};
  static int moveCuveInited = 0;

  // moves is 'is replaced by' notation as described by kociemba's algorithm
  // orientations are noted as the change in orientation after the permutation
  // is made.
  static const corner_t cpU[CORNER_COUNT] = {UBR, URF, UFL, ULB,
                                             DFR, DLF, DBL, DRB};
  static const uint8_t coU[CORNER_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0};
  static const edge_t epU[EDGE_COUNT] = {UB, UR, UF, UL, DR, DF,
                                         DL, DB, FR, FL, BL, BR};
  static const uint8_t eoU[EDGE_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // typedef enum { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB } corner_t;
  static const corner_t cpR[CORNER_COUNT] = {DFR, UFL, ULB, URF,
                                             DRB, DLF, DBL, UBR};
  static const uint8_t coR[CORNER_COUNT] = {2, 0, 0, 1, 1, 0, 0, 2};
  static const edge_t epR[EDGE_COUNT] = {FR, UF, UL, UB, BR, DF,
                                         DL, DB, DR, FL, BL, UR};
  static const uint8_t eoR[EDGE_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpF[CORNER_COUNT] = {UFL, DLF, ULB, UBR,
                                             URF, DFR, DBL, DRB};
  static const uint8_t coF[CORNER_COUNT] = {1, 2, 0, 0, 2, 1, 0, 0};
  static const edge_t epF[EDGE_COUNT] = {UR, FL, UL, UB, DR, FR,
                                         DL, DB, UF, DF, BL, BR};
  static const uint8_t eoF[EDGE_COUNT] = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};
  static const corner_t cpD[CORNER_COUNT] = {URF, UFL, ULB, UBR,
                                             DLF, DBL, DRB, DFR};
  static const uint8_t coD[CORNER_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0};
  static const edge_t epD[EDGE_COUNT] = {UR, UF, UL, UB, DF, DL,
                                         DB, DR, FR, FL, BL, BR};
  static const uint8_t eoD[EDGE_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpL[CORNER_COUNT] = {URF, ULB, DBL, UBR,
                                             DFR, UFL, DLF, DRB};
  static const uint8_t coL[CORNER_COUNT] = {0, 1, 2, 0, 0, 2, 1, 0};
  static const edge_t epL[EDGE_COUNT] = {UR, UF, BL, UB, DR, DF,
                                         FL, DB, FR, UL, DL, BR};
  static const uint8_t eoL[EDGE_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const corner_t cpB[CORNER_COUNT] = {URF, UFL, UBR, DRB,
                                             DFR, DLF, ULB, DBL};
  static const uint8_t coB[CORNER_COUNT] = {0, 0, 1, 2, 0, 0, 2, 1};
  static const edge_t epB[EDGE_COUNT] = {UR, UF, UL, BR, DR, DF,
                                         DL, BL, FR, FL, UB, DB};
  static const uint8_t eoB[EDGE_COUNT] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};

  if (moveCuveInited == 0) {
    memcpy(moves[U].co, coU, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[U].eo, eoU, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[U].cp, cpU, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[U].ep, epU, sizeof(edge_t) * EDGE_COUNT);

    memcpy(moves[R].co, coR, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[R].eo, eoR, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[R].cp, cpR, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[R].ep, epR, sizeof(edge_t) * EDGE_COUNT);

    memcpy(moves[F].co, coF, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[F].eo, eoF, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[F].cp, cpF, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[F].ep, epF, sizeof(edge_t) * EDGE_COUNT);

    memcpy(moves[D].co, coD, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[D].eo, eoD, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[D].cp, cpD, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[D].ep, epD, sizeof(edge_t) * EDGE_COUNT);

    memcpy(moves[L].co, coL, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[L].eo, eoL, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[L].cp, cpL, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[L].ep, epL, sizeof(edge_t) * EDGE_COUNT);

    memcpy(moves[B].co, coB, sizeof(uint8_t) * CORNER_COUNT);
    memcpy(moves[B].eo, eoB, sizeof(uint8_t) * EDGE_COUNT);
    memcpy(moves[B].cp, cpB, sizeof(corner_t) * CORNER_COUNT);
    memcpy(moves[B].ep, epB, sizeof(edge_t) * EDGE_COUNT);
    moveCuveInited = 1;
  }

  return moves;
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

cubycube_t *setCoCoord(uint8_t co) {
    cubycube_t *result = getCubycube();
    for(int i = CORNER_COUNT -1 ; i >= 0; --i) {
        corner_t corner = co % 3;
        co /= 3;
        result->co[i] = corner;
    }
    return result;
}

uint16_t coCoord(cubycube_t *cubycube) {
  uint16_t coord = 0;
  for (int i = 0; i < CORNER_COUNT; ++i) {
    coord = coord * 3 + cubycube->co[i];
  }
  return coord;
}

cubycube_t *setEoCoord(uint8_t eo){
    cubycube_t *result = getCubycube();
    for(int i = EDGE_COUNT -1 ; i >= 0; --i) {
        edge_t edge = eo % 12;
        eo /= 12;
        result->ep[i] = edge;
    }
    return result;
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

void domove(cubycube_t *cubycube, faces_t move) {
  cubycube_t moves = getMoves()[move];

  corner_t cpTemp[CORNER_COUNT] = {0};
  uint8_t coTemp[CORNER_COUNT] = {0};
  for (int i = 0; i < CORNER_COUNT; i++) {
    cpTemp[i] = cubycube->cp[moves.cp[i]];
    coTemp[i] = cubycube->co[moves.cp[i]];
  }

  edge_t epTemp[EDGE_COUNT] = {0};
  uint8_t eoTemp[EDGE_COUNT] = {0};
  for (int i = 0; i < EDGE_COUNT; i++) {
    epTemp[i] = cubycube->ep[moves.ep[i]];
    eoTemp[i] = cubycube->eo[moves.ep[i]];
  }

  // update state
  for (int i = 0; i < CORNER_COUNT; i++) {
    cubycube->cp[i] = cpTemp[i];
    cubycube->co[i] = (coTemp[i] + moves.co[i]) % 3;
  }
  for (int i = 0; i < EDGE_COUNT; i++) {
    cubycube->ep[i] = epTemp[i];
    cubycube->eo[i] = (eoTemp[i] + moves.eo[i]) % 2;
  }
}
