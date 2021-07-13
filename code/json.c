#include <stdio.h>
#include <math.h>

float ConvertNumberToFloat(unsigned long number, int isDoublePrecision)
{
    int mantissaShift = isDoublePrecision ? 52 : 23;
    unsigned long exponentMask = isDoublePrecision ? 0x7FF0000000000000 : 0x7f800000;
    int bias = isDoublePrecision ? 1023 : 127;
    int signShift = isDoublePrecision ? 63 : 31;

    int sign = (number >> signShift) & 0x01;
    int exponent = ((number & exponentMask) >> mantissaShift) - bias;

    int power = -1;
    float total = 0.0;
    for ( int i = 0; i < mantissaShift; i++ )
    {
        int calc = (number >> (mantissaShift-i-1)) & 0x01;
        total += calc * pow(2.0, power);
        power--;
    }
    float value = (sign ? -1 : 1) * pow(2.0, exponent) * (total + 1.0);

    return value;
}

int main()
{
    // Single Precision
    unsigned int singleValue = 0x40490FDB; // 3.141592...
    float singlePrecision = (float)ConvertNumberToFloat(singleValue, 0);
    printf("IEEE754 Single (from 32bit 0x%08X): %.2f\n",singleValue,singlePrecision);
}