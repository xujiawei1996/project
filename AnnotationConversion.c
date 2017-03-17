#define _CRT_SECURE_NO_WARNINGS 1

#include "AnnotationConversion.h"

void AnnotationConversion(FILE *pfIn,FILE *pfOut)
{
	enum STATE state = NULL_STATE;
	while (state != END_STATE)
	{
		switch (state)
		{
		case NULL_STATE:
			DO_NULL_STATE(pfIn,pfOut,&state);
			break;
		case C_STATE:
			DO_C_STATE(pfIn,pfOut,&state);
			break;
		case CPP_STATE:
			DO_CPP_STATE(pfIn,pfOut,&state);
			break;
		default:
			break;
		}
	}
}

void DO_NULL_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfIn);
	switch (first)
	{
	case '/':
		{
			second = fgetc(pfIn);
			switch(second)
			{
			case '/':
				fputc(first,pfOut);						/*如果是两个/，是cpp状态,读两个/并进入CPP函数*/
				fputc(second,pfOut);
				*state = CPP_STATE;
				break;
			case'*':
				fputc(first,pfOut);
				fputc('/',pfOut);						//如果是/*是c状态 进入C换CPP函数
				*state = C_STATE;
				break;
			default:
				fputc(first,pfOut);						//如果第一个是，第二个不是，那就不是c/cpp状态，两个都输出
				fputc(second,pfOut);	
				break;
			}
		}	
		break;
	case EOF:											//遇到文件结尾，退出
		*state = END_STATE;
		break;
	default:											//如果两个都不是，见啥输出啥
		fputc(first,pfOut);
		break;
	}
}

void DO_C_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state)		//如果判断是C的注释，要转为CPP
{
	int first = 0;
	int second = 0;
	int third = 0;
	first = fgetc(pfIn);
	switch (first)
	{
	case '*':
		second = fgetc(pfIn);
		switch(second)
		{
		case '/':
			third = fgetc(pfIn);
			switch(third)
			{
			case '\n':
				ungetc(third,pfIn);							//这里要判断第三个，如果第三个是换行，则应该返回第三个，并且重新调用null_state
				*state = NULL_STATE;
				break;
			default:	
				fputc('\n',pfOut);							//如果后面有字符则县换行，再把字符换回去，调NULL_STATE
				ungetc(third,pfIn);
				*state = NULL_STATE;
				break;
			}
			break;
		default:
			fputc(first,pfOut);
			ungetc(second,pfIn);
			break;
		}
		break;
	case EOF:
		break;
	case '\n':												//如果是换行，那么换行并添加//
		fputc('\n',pfOut);
		fputc('/',pfOut);
		fputc('/',pfOut);	
		break;
	default:
		fputc(first,pfOut);
		break;
	}
}

void DO_CPP_STATE(FILE *pfIn,FILE *pfOut,enum STATE *state)			//cpp的函数，这里就只考虑是否为换行或者文件结束，
{	
	int first = 0;
	first = fgetc(pfIn);
	switch (first)
	{
	case '\n':														//若读取到换行，读一个输一个，注释结束，返回NULL_STATE，
		fputc(first,pfOut);
		*state = NULL_STATE;
		break;
	case EOF:
		*state = END_STATE;											//若读不到东西，直接结束。
		break;
	default:
		fputc(first, pfOut);										//读到除了换行任意东西，读啥输出啥
		break;
	}
}