#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"

int birnaryToDecimal(char *data)
{
	int ret = 0;
	int n = strlen(data);
	int i;
	for(i = 0; i < n; i++)
	{
		ret *= 2;
		if(data[i] == '1')
		{
			ret += 1;
		}
	}

	return ret;
}


int octalToDecimal(char *data)
{
	int ret = 0;
	int n = strlen(data);
	int i;
	for(i = 0; i < n; i++)
	{
		ret *= 8;
		ret += (data[i] - '0');
	}

	return ret;
}

int hexToDecimal(char *data)
{
	int ret = 0;
	int n = strlen(data);
	int i;
	char c;
	for(i = 0; i < n; i++)
	{
		ret *= 16;
		c = data[i];
		if('0' <= c && '9' >= c)
		{
			ret += (c - '0');
		}
		else if('A' <= c && 'F' >= c)
		{
			ret += (c - 'A' + 10);
		}
		else
		{
			ret += (c - 'a' + 10);
		}
	}

	return ret;
}

char *decimalToBinary(int n)
{
	int data[32];
	char *ret;
	int i = 0, j;

	while(n > 0)
	{
		data[i++] = n % 2;
		n /= 2;
	}

	ret = (char*)malloc( (i+1) * sizeof(char));
	for(j = 0; j < i; j++)
	{
		ret[j] = data[i-j-1] + '0';
	}
	ret[i] = 0;

	return ret;
}


char *decimalToOctal(int n)
{
	int data[32];
	char *ret;
	int i = 0, j;

	while(n > 0)
	{
		data[i++] = n % 8;
		n /= 8;
	}

	ret = (char*)malloc( (i+1) * sizeof(char));
	for(j = 0; j < i; j++)
	{
		ret[j] = data[i-j-1] + '0';
	}
	ret[i] = 0;

	return ret;
}

char *decimalToHex(int n)
{
	int data[32];
	char *ret;
	int i = 0, j, k;

	while(n > 0)
	{
		data[i++] = n % 16;
		n /= 16;
	}

	ret = (char*)malloc( (i+1) * sizeof(char));
	for(j = 0; j < i; j++)
	{
		k = data[i-j-1];
		if(k < 10)
			ret[j] = k + '0';
		else
			ret[j] = k - 10 + 'A';
	}
	ret[i] = 0;

	return ret;
}

int validateBinaryData(char *data)
{
	int n = strlen(data);
	int i = 0;
	for( ;  i < n; i++)
	{
		if(data[i] != '1' && data[i] != '0')
		{
			return FALSE;
		}
	}

	return TRUE;
}

int validateOctalData(char *data)
{
	int n = strlen(data);
	int i = 0;
	for( ;  i < n; i++)
	{
		if(data[i] < '0' || data[i] > '7')
		{
			return FALSE;
		}
	}

	return TRUE;
}

int validateDecimalData(char *data)
{
	int n = strlen(data);
	int i = 0;
	for( ;  i < n; i++)
	{
		if(data[i] < '0' || data[i] > '9')
		{
			return FALSE;
		}
	}

	return TRUE;
}

int validateHexData(char *data)
{
	int i = 0;
	int n = strlen(data);
	if( n < 1)
	{
		return FALSE;
	}

	for( ;  i < n; i++)
	{
		if(data[i] >= '0' && data[i] <= '9')
		{
			continue;
		}
		else if(data[i] >= 'A' && data[i] <= 'F')
		{
			continue;
		}
		else if(data[i] >= 'a' && data[i] <= 'f')
		{
			continue;
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

int validateData(char *arg)
{
	char *data = arg;
	char type;
	if(data[0] == '-')
	{
		data = &arg[1];
	}

	type = data[0];
	if(type == 'd')
	{
		return validateDecimalData(&data[1]);
	}
	else if(type == 'b')
	{
		return validateBinaryData(&data[1]);
	}
	else if(type == 'o')
	{
		return validateOctalData(&data[1]);
	}
	else if(type == 'x')
	{
		return validateHexData(&data[1]);
	}
	else
	{
		return FALSE;
	}
}

int validateOperation(char *arg)
{
	if(strlen(arg) != 1)
	{
		return FALSE;
	}

	if(arg[0] == '+' || arg[0] == '-')
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int validateType(char *arg)
{
	if(strlen(arg) != 1)
	{
		return FALSE;
	}

	if(arg[0] == 'o' || arg[0] == 'd' || arg[0] == 'b' || arg[0] == 'x')
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int getValue(char *arg)
{
	char *data = arg;
	int k = 1, ret;
	if(arg[0] == '-')
	{
		data = &arg[1];
		k = -1;
	}

	switch(data[0])
	{
	case 'd':
		ret = atoi(&data[1]);
		break;
	case 'b':
		ret = birnaryToDecimal(&data[1]);
		break;
	case 'o':
		ret = octalToDecimal(&data[1]);
		break;
	case 'x':
		ret = hexToDecimal(&data[1]);
		break;
	default:
		break;
	}

	return ret * k;
}

int main(int argc, char *argv[])
{
	int decimalVal;
	char *resultData;

	if(argc != 5)
	{
		//printf("calc <op> <number1> <number2> <output base>\n");
		printf("=> ERROR\n");
		return 0;
	}

	if(validateOperation(argv[1]) == FALSE || validateData(argv[2]) == FALSE
		|| validateData(argv[3]) == FALSE || validateType(argv[4]) == FALSE)
	{
		printf("=> ERROR\n");
		return 0;
	}
	else
	{
		if(argv[1][0] == '+')
		{
			decimalVal = getValue(argv[2]) + getValue(argv[3]);
		}
		else if(argv[1][0] == '-')
		{
			decimalVal = getValue(argv[2]) - getValue(argv[3]);
		}

		printf("=> ");
		if(decimalVal < 0)
		{
			printf("-");
			decimalVal *= -1;
		}

		switch(argv[4][0])
		{
		case 'd':
			printf("%c%d\n", argv[4][0], decimalVal);
			return 0;
		case 'b':
			resultData = decimalToBinary(decimalVal);
			break;
		case 'o':
			resultData = decimalToOctal(decimalVal);
			break;
		case 'x':
			resultData = decimalToHex(decimalVal);
			break;
		default:
			break;
		}

		printf("%c%s\n", argv[4][0], resultData);
		free(resultData);
	}

	return 0;
}
