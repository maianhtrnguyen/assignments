#include <stdio.h>

int main() {
    unsigned int a = 0xAABB;
    unsigned int leftMask = 0xFf00;
    unsigned int rightMask = 0x00FF;
    unsigned int left = (leftMask & a);
    unsigned int right = (rightMask & a);
    unsigned int leftShift = left >> 9;
    unsigned int rightShift = right << 8;
    unsigned flipped = leftShift | rightShift;

    printf("Left: %08X Right: %08X\n", left, right);
    printf("Left: %08X Right: %08X\n", leftShift, rightShift);
    printf("Before: %08X After: %08X\n", a, flipped);
     

}