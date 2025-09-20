#include "coordcube.h"
#include "cubycube.h"
#include "facecube.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arrays_equal_uint8(const uint8_t *a, const uint8_t *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      printf("Array mismatch at index %zu: %d != %d\n", i, a[i], b[i]);
      return 0;
    }
  }
  return 1;
}

static int arrays_equal_corner(const corner_t *a, const corner_t *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      printf("Array mismatch at index %zu: %d != %d\n", i, a[i], b[i]);
      return 0;
    }
  }
  return 1;
}

static int arrays_equal_edge(const edge_t *a, const edge_t *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      printf("Array mismatch at index %zu: %d != %d\n", i, a[i], b[i]);
      return 0;
    }
  }
  return 1;
}

static void test_transform_to_cubycube() {
  cubycube_t *c = fromFaceCube(
      fromString("UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"));

  uint8_t solved_co[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  corner_t solved_cp[8] = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
  uint8_t solved_eo[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  edge_t solved_ep[12] = {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR};

  assert(arrays_equal_uint8(c->co, solved_co, 8));
  assert(arrays_equal_corner(c->cp, solved_cp, 8));
  assert(arrays_equal_uint8(c->eo, solved_eo, 12));
  assert(arrays_equal_edge(c->ep, solved_ep, 12));

  free(c);
}

static void test_transform_to_cubycube_2() {
  // FRBFUURUU
  // RRDRRDBBD
  // DFFDFFLRR
  // BDDBDDBLF
  // LLFLLFUUU
  // LBULBULBR
  cubycube_t *c = fromFaceCube(
      fromString("FRBFUURUURRDRRDBBDDFFDFFLRRBDDBDDBLFLLFLLFUUULBULBULBR"));

  uint8_t scrambled_co[8] = {0, 1, 2, 2, 0, 1, 2, 1};
  corner_t scrambled_cp[8] = {URF, DFR, UFL, DBL, DRB, ULB, UBR, DLF};
  uint8_t scrambled_eo[12] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1};
  edge_t scrambled_ep[12] = {UR, UF, FL, BR, DB, DR, UB, BL, FR, DF, UL, DL};

  assert(arrays_equal_uint8(c->co, scrambled_co, 8));
  assert(arrays_equal_corner(c->cp, scrambled_cp, 8));
  assert(arrays_equal_uint8(c->eo, scrambled_eo, 12));
  assert(arrays_equal_edge(c->ep, scrambled_ep, 12));

  free(c);
}

static void test_get_coord_cube_1() {
  cubycube_t *cube = getCubycube();
  coordcube_t *coordcube = fromCubycube(cube);

  assert(coordcube->coCoord == 0);
  assert(coordcube->cpCoord == 0);
  assert(coordcube->eoCoord == 0);
  assert(coordcube->epCoord == 0);
  assert(coordcube->UDSliceCoord == 0);
  assert(coordcube->UDSliceSortedCoord == 0);

  free(cube);
  free(coordcube);
}

static void test_get_coord_cube_2() {
  facecube_t *facecube =
      fromString("FRBFUURUURRDRRDBBDDFFDFFLRRBDDBDDBLFLLFLLFUUULBULBULBR");
  cubycube_t *cube = fromFaceCube(facecube);
  coordcube_t *coordcube = fromCubycube(cube);

  assert(coordcube->coCoord == 1393);
  assert(coordcube->cpCoord == 12602);
  assert(coordcube->eoCoord == 305);
  assert(coordcube->epCoord == 2440);
  assert(coordcube->UDSliceCoord == 219);
  assert(coordcube->UDSliceSortedCoord == 11);

  free(facecube);
  free(cube);
  free(coordcube);
}


static void test_domove() {
  cubycube_t *cube = getCubycube();
  cubycube_t cube2 = getMoves()[F];
  domove(cube, F);
  
  assert(arrays_equal_uint8(cube->co, cube2.co, 8));
  assert(arrays_equal_corner(cube->cp, cube2.cp, 8));
  assert(arrays_equal_uint8(cube->eo, cube2.eo, 12));
  assert(arrays_equal_edge(cube->ep, cube2.ep, 12));

  free(cube);
}

static void test_domove2() {
  cubycube_t *cube = getCubycube();
  domove(cube, R);
  domove(cube, R);
  
  uint8_t expected_co[8] = {0,0,0,0,0,0,0,0};
  uint8_t expected_eo[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  assert(arrays_equal_uint8(cube->co, expected_co, 8));
  assert(arrays_equal_uint8(cube->eo, expected_eo, 12));

  free(cube);
}

int main(void) {
  printf("Running cubycube tests...\n");

  test_transform_to_cubycube();
  test_transform_to_cubycube_2();
  test_get_coord_cube_1();
  test_get_coord_cube_2();
  test_domove();
  test_domove2();
  printf("All cubycube tests passed!\n");
  return 0;
}
