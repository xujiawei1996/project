#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __ANNOTATION_CONVERSION_H__
#define __ANNOTATION_CONVERSION_H__

#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#define INNAME "input.c"
#define OUTNAME "output.c"

enum STATE 
{
	NULL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};

void AnnotationConversion(FILE *pfIn,FILE *pfOut);
void DO_NULL_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state);
void DO_C_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state);
void DO_CPP_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state);

#endif

