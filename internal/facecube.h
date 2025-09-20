#ifndef FACECUBE_H
#define FACECUBE_H

// https://kociemba.org/cube.htm
/**
 * The names of the facelet positions of the cube
 *             |************|
 *             |*U1**U2**U3*|
 *             |************|
 *             |*U4**U5**U6*|
 *             |************|
 *             |*U7**U8**U9*|
 *             |************|
 * ************|************|************|************|
 * *L1**L2**L3*|*F1**F2**F3*|*R1**R2**F3*|*B1**B2**B3*|
 * ************|************|************|************|
 * *L4**L5**L6*|*F4**F5**F6*|*R4**R5**R6*|*B4**B5**B6*|
 * ************|************|************|************|
 * *L7**L8**L9*|*F7**F8**F9*|*R7**R8**R9*|*B7**B8**B9*|
 * ************|************|************|************|
 *             |************|
 *             |*D1**D2**D3*|
 *             |************|
 *             |*D4**D5**D6*|
 *             |************|
 *             |*D7**D8**D9*|
 *             |************|
 * The order of the facelet is defined as:
 * U1,U2,U3,U4,U5,U6,U7,U8,U9,R1,R2,R3,R4,R5,R6,R7,R8,R9,F1,F2,F3,F4,F5,F6,F7,F8,F9,
 * D1,D2,D3,D4,D5,D6,D7,D8,D9,L1,L2,L3,L4,L5,L6,L7,L8,L9,B1,B2,B3,B4,B5,B6,B7,B8,B9
 */

#define FACE_COUNT 6
typedef enum { U, R, F, D, L, B } faces_t;
extern const faces_t faces[FACE_COUNT];

typedef enum {
  U1,
  U2,
  U3,
  U4,
  U5,
  U6,
  U7,
  U8,
  U9,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  D1,
  D2,
  D3,
  D4,
  D5,
  D6,
  D7,
  D8,
  D9,
  L1,
  L2,
  L3,
  L4,
  L5,
  L6,
  L7,
  L8,
  L9,
  B1,
  B2,
  B3,
  B4,
  B5,
  B6,
  B7,
  B8,
  B9
} facelet_t;
#define FACELET_COUNT 54

struct facecube {
  // Faces in the order defined by facelet_t enum
  faces_t f[FACELET_COUNT];
};
typedef struct facecube facecube_t;

typedef enum { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB } corner_t;
#define CORNER_COUNT 8
extern const facelet_t cornerFacelet[CORNER_COUNT][3];
extern const faces_t cornerColor[CORNER_COUNT][3];

typedef enum { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR } edge_t;
#define EDGE_COUNT 12
extern const facelet_t edgeFacelet[EDGE_COUNT][2];
extern const faces_t edgeColor[EDGE_COUNT][2];

facecube_t *fromString(char *facestring);

#endif