#include "shiftReg.h"

void writeMatrix(uint16 shiftBuf) {
    latchPin_Write(LOW);
    for(int8 i=0;i<16;i++) {
        clockPin_Write(HIGH); 
        dataPin_Write(((shiftBuf >> i) & 0x0001));
        clockPin_Write(LOW); 
    }  
    clockPin_Write(HIGH); 
    latchPin_Write(HIGH);
    latchPin_Write(LOW);
    clockPin_Write(LOW); 
}

void encodeMatrix(uint16_t* shiftBuf)
{
    uint16_t tmpBuf = *shiftBuf;
    *shiftBuf = 0;
    
    // first octet
    *shiftBuf |= ((tmpBuf << 7)  & 0x8000); // r1
    *shiftBuf |= ((tmpBuf << 5)  & 0x4000); // r2
    *shiftBuf |= ((tmpBuf << 7)  & 0x2000); // k7
    *shiftBuf |= ((tmpBuf >> 3)  & 0x1000); // r8
    *shiftBuf |= ((tmpBuf << 7)  & 0x0800); // k5
    *shiftBuf |= ( tmpBuf        & 0x0400); // r3
    *shiftBuf |= ((tmpBuf >> 3)  & 0x0200); // r5
    *shiftBuf |= ((tmpBuf << 1)  & 0x0100); // k8
    // second octet
    *shiftBuf |= ((tmpBuf << 4)  & 0x0080); // k4
    *shiftBuf |= ((tmpBuf << 1)  & 0x0040); // k6
    *shiftBuf |= ((tmpBuf << 3)  & 0x0020); // k3
    *shiftBuf |= ((tmpBuf >> 7)  & 0x0010); // r4
    *shiftBuf |= ((tmpBuf << 3)  & 0x0008); // k1
    *shiftBuf |= ((tmpBuf >> 11) & 0x0004); // r6
    *shiftBuf |= ((tmpBuf >> 13) & 0x0002); // r7
    *shiftBuf |= ((tmpBuf >> 1)  & 0x0001); // k2
}

uint16 encodeMatrixRet(uint16 matrix) {
    uint16_t encodedMatrix = 0x0000;
    
    // first octet
    encodedMatrix |= ((matrix << 7)  & 0x8000); // r1
    encodedMatrix |= ((matrix << 5)  & 0x4000); // r2
    encodedMatrix |= ((matrix << 7)  & 0x2000); // k7
    encodedMatrix |= ((matrix >> 3)  & 0x1000); // r8
    encodedMatrix |= ((matrix << 7)  & 0x0800); // k5
    encodedMatrix |= ( matrix        & 0x0400); // r3
    encodedMatrix |= ((matrix >> 3)  & 0x0200); // r5
    encodedMatrix |= ((matrix << 1)  & 0x0100); // k8
    // second octet
    encodedMatrix |= ((matrix << 4)  & 0x0080); // k4
    encodedMatrix |= ((matrix << 1)  & 0x0040); // k6
    encodedMatrix |= ((matrix << 3)  & 0x0020); // k3
    encodedMatrix |= ((matrix >> 7)  & 0x0010); // r4
    encodedMatrix |= ((matrix << 3)  & 0x0008); // k1
    encodedMatrix |= ((matrix >> 11) & 0x0004); // r6
    encodedMatrix |= ((matrix >> 13) & 0x0002); // r7
    encodedMatrix |= ((matrix >> 1)  & 0x0001); // k2
    
    return encodedMatrix;
}

void print9() {
    writeMatrix(encodeMatrixRet(0xFE3C));
    writeMatrix(encodeMatrixRet(0xFD24));
    writeMatrix(encodeMatrixRet(0xFB24));
    writeMatrix(encodeMatrixRet(0xF73C));
    writeMatrix(encodeMatrixRet(0xEF04));
    writeMatrix(encodeMatrixRet(0xDF04));
    writeMatrix(encodeMatrixRet(0xBF04));
    writeMatrix(encodeMatrixRet(0x7F3C));
    
    return;
}


void matrixOn(uint16* shiftBuf) {
    *shiftBuf = 0b1001011110010100;
}

void matrixOff(uint16* shiftBuf) {
    *shiftBuf = 0b0110100001101011;
}

void flushBuf(uint16* shiftBuf) {
    *shiftBuf = 0;
}

void row1Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0001000000000000;
}
void row2Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b1000000000000000;
}
void row3Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000010000000000;
}
void row4Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000000100000000;
}
void row5Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000000000010000;
}
void row6Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000001000000000;
}
void row7Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000000000000100;
}
void row8Toggle(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf ^ 0b0000000010000000;
}

void row1On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0001000000000000;
}
void row2On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b1000000000000000;
}
void row3On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000010000000000;
}
void row4On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000100000000;
}
void row5On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000010000;
}
void row6On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000001000000000;
}
void row7On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000000100;
}
void row8On(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000010000000;
}

void column1Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000000001;
}
void column2Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000000010;
}
void column3Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000100000;
}
void column4Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000100000000000;
}
void column5Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000001000000;
}
void column6Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0010000000000000;
}
void column7Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0100000000000000;
}
void column8Off(uint16* shiftBuf) {
    *shiftBuf = *shiftBuf | 0b0000000000001000;
}

/* [] END OF FILE */
