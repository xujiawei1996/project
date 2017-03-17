#define _CRT_SECURE_NO_WARNINGS 1

#include "AnnotationConversion.h"

int main()
{
	FILE *pfIn;
	FILE *pfOut;
	pfIn = fopen(INNAME,"r");
	if (pfIn == NULL)
	{
		perror("pfIn");
		return 0;
	}
	pfOut = fopen(OUTNAME,"w");
	if (pfOut == NULL)
	{
		fclose(pfIn);
		perror("pfout");
		return 0;
	}
	AnnotationConversion(pfIn,pfOut);
	printf("×ª»»Íê³É\n");
	system("pause");
	return 0;
}