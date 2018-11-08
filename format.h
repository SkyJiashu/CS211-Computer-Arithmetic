#ifndef _FORMAT_H
#define _FORMAT_H

#define TRUE 1
#define FALSE 0

//validate string represent binary number
int validateBinaryData(char *data);

//get the fraction part value, in a binary number
double getFractionValue(char *data);

//get decimal value of binary number
int getDecimalValue(char *data);

//get exponent part in binary string
int getExponent(char *arg);


#endif
