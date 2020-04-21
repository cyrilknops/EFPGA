#include "shiftReg.h"

volatile int matrixStateCnt = 11;

CY_ISR (isr_timer_Handler) {
    matrixStateCnt++;
    if(matrixStateCnt==12) {
        matrixStateCnt = 0;
    }
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH);
    
}

// Datapin:      DS
// Clockpin:     SH
// Latchpin:     ST
// Overflowpin:  Q7

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //uint16 shiftBuf = 0x9794;
    //uint16 shiftBuf = 0;
    timer_Start();
    isr_timer_StartEx(isr_timer_Handler);
    
    for(;;) {
        switch(matrixStateCnt) {
            case 0:
                writeMatrix(encodeMatrixRet(0xFD3C));
                writeMatrix(encodeMatrixRet(0xF324));
                writeMatrix(encodeMatrixRet(0xCF24));
                writeMatrix(encodeMatrixRet(0xBF3C));
                break;
            case 1:
                writeMatrix(encodeMatrixRet(0xF720));
                writeMatrix(encodeMatrixRet(0xFB10));
                writeMatrix(encodeMatrixRet(0xF108));
                writeMatrix(encodeMatrixRet(0xEF08));
                writeMatrix(encodeMatrixRet(0xDF08));
                writeMatrix(encodeMatrixRet(0xBF08));
                break;
            case 2:
                writeMatrix(encodeMatrixRet(0xFD18));
                writeMatrix(encodeMatrixRet(0xF324));
                writeMatrix(encodeMatrixRet(0xEF08));
                writeMatrix(encodeMatrixRet(0xDF10));
                writeMatrix(encodeMatrixRet(0xBF3C));
                break;
            case 3:
                writeMatrix(encodeMatrixRet(0xFE18));
                writeMatrix(encodeMatrixRet(0xFD24));
                writeMatrix(encodeMatrixRet(0xFB04));
                writeMatrix(encodeMatrixRet(0xF718));
                writeMatrix(encodeMatrixRet(0xCF04));
                writeMatrix(encodeMatrixRet(0xDF24));
                writeMatrix(encodeMatrixRet(0xBF18));
                break;
            case 4:
                writeMatrix(encodeMatrixRet(0xFD0C));
                writeMatrix(encodeMatrixRet(0xFB14));
                writeMatrix(encodeMatrixRet(0xF724));
                writeMatrix(encodeMatrixRet(0xEF3C));
                writeMatrix(encodeMatrixRet(0x9F04));
                break;
            case 5:
                writeMatrix(encodeMatrixRet(0xFD3C));
                writeMatrix(encodeMatrixRet(0xFB20));
                writeMatrix(encodeMatrixRet(0xF738));
                writeMatrix(encodeMatrixRet(0xEF04));
                writeMatrix(encodeMatrixRet(0xDF24));
                writeMatrix(encodeMatrixRet(0xBF18));
                break;
            case 6:
                writeMatrix(encodeMatrixRet(0xFD3C));
                writeMatrix(encodeMatrixRet(0xFB20));
                writeMatrix(encodeMatrixRet(0xF720));
                writeMatrix(encodeMatrixRet(0xEF3C));
                writeMatrix(encodeMatrixRet(0xDF24));
                writeMatrix(encodeMatrixRet(0xBF3C));
                break;
            case 7:
                writeMatrix(encodeMatrixRet(0xFD3E));
                writeMatrix(encodeMatrixRet(0xFB04));
                writeMatrix(encodeMatrixRet(0xF708));
                writeMatrix(encodeMatrixRet(0x8F08));
                break;
            case 8:
                writeMatrix(encodeMatrixRet(0xFE18));
                writeMatrix(encodeMatrixRet(0xFD24));
                writeMatrix(encodeMatrixRet(0xFB24));
                writeMatrix(encodeMatrixRet(0xF73C));
                writeMatrix(encodeMatrixRet(0xEF24));
                writeMatrix(encodeMatrixRet(0xDF24));
                writeMatrix(encodeMatrixRet(0xBF18));
                break;
            case 9:
                writeMatrix(encodeMatrixRet(0xFD18));
                writeMatrix(encodeMatrixRet(0xFB24));
                writeMatrix(encodeMatrixRet(0xF724));
                writeMatrix(encodeMatrixRet(0xEF1C));
                writeMatrix(encodeMatrixRet(0xDF04));
                writeMatrix(encodeMatrixRet(0xBF38));
            break;
                                     
            default:
                writeMatrix(encodeMatrixRet(0x0000));
            break;
        }
    }
    //writeMatrix(encodeMatrixRet(0x0000));   
}

/* [] END OF FILE */
