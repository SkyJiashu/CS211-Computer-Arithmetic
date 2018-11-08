#ifndef _CALC_H
#define _CALC_H

#define TRUE 1
#define FALSE 0

//convert binary string to decimal value
int birnaryToDecimal(char *data);

//convert octal string to decimal value
int octalToDecimal(char *data);

//convert hexadecimal string to decimal value
int hexToDecimal(char *data);

//convert decimal value to binary string
char *decimalToBinary(int n);

//convert decimal value to octal string
char *decimalToOctal(int n);

//convert decimal value to hexadecimal string
char *decimalToHex(int n);

//validate binary string, can only contain 0 and 1
int validateBinaryData(char *data);

//validate octal string, can only contain number 0-7
int validateOctalData(char *data);

//validate string represent decimal value, for the use of atoi();
int validateDecimalData(char *data);

//valiedate hexadecimal string, can only have digit 0-9, and a-f or A-F
int validateHexData(char *data);

//validate string represent number
int validateData(char *arg);

//validate operation character
int validateOperation(char *arg);

//validate all data types
int validateType(char *arg);

//get value in a string
int getValue(char *arg);

#endif
