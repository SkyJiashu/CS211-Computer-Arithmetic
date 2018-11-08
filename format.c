#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "format.h"

int validateBinaryData(char *data)
{
	int i, n = 32;
	if(strlen(data) != n)
	{
		return FALSE;
	}

	for( i = 0; i < n; i++)
	{
		if(data[i] != '0' && data[i] != '1')
		{
			return FALSE;
		}
	}

	return TRUE;
}


double getFractionValue(char *data)
{
	double ret = 0;
	int i;
	int n = strlen(data);
	for(i = n-1; i >= 0; i--)
	{
		ret *= 0.5;
		if(data[i] == '1')
		{
			ret += 0.5;
		}
	}

	return ret;
}

int getDecimalValue(char *data)
{
	int i, n = 0;
	for(i = 1; i < 32; i++)
	{
		if(data[i] == '1')
		{
			n += (1 << (31-i));
		}
	}

	if(data[0] == '1')
	{
		i = (1 << 30);
		n -= i;
		n -= i;
	}

	return n;
}

int getExponent(char *arg)
{
	int i = 1;
	int ret = 0;
	for(i = 1; i < 9; i++)
	{
		ret *= 2;
		if(arg[i] == '1')
		{
			ret += 1;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	int exp;
	double frac;
	double val;

	if(argc != 3)
	{
		printf("=> ERROR\n");
		return 0;
	}

	if(validateBinaryData(argv[1]) == FALSE)
	{
		printf("=> ERROR\n");
		return 0;
	}

	if(strcmp(argv[2], "int") == 0)
	{
		printf("=> %d\n", getDecimalValue(argv[1]));
	}
	else if(strcmp(argv[2], "float") == 0)
	{
		exp = getExponent(argv[1]);
		frac = getFractionValue(&argv[1][9]);


		if(exp == 255)
		{
			if(frac != 0)
			{
				printf("=> NaN\n");
			}
			else
			{
				if(argv[1][0] == '0')
				{
					printf("=> pinf\n");
				}
				else
				{
					printf("=> ninf\n");
				}
			}
		}
		else
		{
			if(exp == 0)
			{
				exp = -126;  // 1 - (2^7-1)
				frac = getFractionValue(&argv[1][9]);
			}
			else
			{
				exp -= 127;
				frac += 1;
			}

			val = (1 << exp);
			if(exp < 0)
			{
				exp *= -1;
				val = 1.0 / (1 << exp);
			}

			if(argv[1][0] == '0')
				printf("=> %f\n", val * frac);
			else
				printf("=> -%f\n", val * frac);
		}
	}
	else
	{
		printf("=> ERROR\n");
	}

	return 0;
}
