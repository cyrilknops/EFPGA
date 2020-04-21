/*
 *                        encoded
 *        IC4 (74HC595)      |       IC5 (74HC595)
 * Q0 Q1 Q2 Q3   Q4 Q5 Q6 Q7 | Q0 Q1 Q2 Q3   Q4 Q5 Q6 Q7
 * r1 r2 k7 r8   k5 r3 r5 k8 | k4 k6 k3 r4   k1 r6 r7 k2
 *
 *                        decoded
 *        IC4 (74HC595)      |        IC5 (74HC595)
 * Q0 Q1 Q2 Q3   Q4 Q5 Q6 Q7 | Q0 Q1 Q2 Q3   Q4 Q5 Q6 Q7
 * r8 r7 r6 r5   r4 r3 r2 r1 | k8 k7 k6 k5   k4 k3 k2 k1
*/

#ifndef SHIFT_H
    #define SHIFT_H
    #define HIGH 1u
    #define LOW  0u
    #define CLOCKS_PER_SECOND 10000u

    #include "project.h"
    
    void writeMatrix(uint16 shiftBuf);
    void encodeMatrix(uint16* shiftBuf);
    uint16 encodeMatrixRet(uint16 matrix);
    void print9();
#endif
/* [] END OF FILE */
