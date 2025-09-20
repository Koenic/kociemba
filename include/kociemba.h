#ifndef KOCIEMBA_H
#define KOCIEMBA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Computes a solution to the rubiks cube using the kociemba algotihm
 * @param cube
 *   cube should be the rubiks cube in FaceCube notation
 * @param maxdepth
 *   the maximum lenght for the solution. Should be at least 20
 */
char *kociemba_solve(const char *cube, int maxDepth);

#ifdef __cplusplus
}
#endif

#endif