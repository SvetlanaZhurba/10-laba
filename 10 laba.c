#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NO  0
#define YES 1

int main() 
{
	FILE *fpin;  
	FILE *fpout; 

	char **lines;
	char *ptr;
	char *swap_str;
	char line[1000];
	int *arr;
	int swap;
	int str_cnt;
	int word_cnt;
	int symb_cnt;
	int flag;
	int i, j;

	swap = 0;
	str_cnt = 0;
	flag = NO;
	lines = (char**)malloc( str_cnt * sizeof(char*) );
	arr = (int*)malloc( str_cnt * sizeof(int) );
	swap_str = NULL;

	fpin = fopen( "test.txt", "rt" );
	if( !fpin )
		return 1;

	fpout = fopen( "result.txt", "wt" );
	if( !fpout )
		return 1;

	while( ptr = fgets( line, 1000, fpin ) ) // цикл до конца входного файла
	{
		symb_cnt = 0;
		word_cnt = 0;

		while( *ptr != '\0' )
		{
			if( *ptr >= 'a' && *ptr <= 'z' || *ptr >= 'A' && *ptr <= 'Z' )
			{
				if( !flag )
				{
					word_cnt++;
					flag = YES;
				}
			}
			else
				flag = NO;

			symb_cnt++;
			ptr++;
		}

		if( *(ptr - 1) != '\n' )
		{
			*ptr = '\n';
			*(ptr + 1) = '\0';
			symb_cnt++;
		}

		lines = (char**)realloc( lines, (str_cnt + 1) * sizeof(char*) );
		*(lines + str_cnt) = (char*)malloc( symb_cnt * sizeof(char) );
		strcpy( *(lines + str_cnt), line );

		arr = (int*)realloc( arr, (str_cnt + 1)  * sizeof(int) );
		*(arr + str_cnt) = word_cnt;

		str_cnt++;
	}

	for( i = str_cnt - 1; i >= 0; i-- )
	{
		for( j = 0; j < i; j++ ) 
		{
			if ( *(arr + j) > *(arr + j + 1) ) 
			{
				swap = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = swap;
			
				swap_str = *(lines + j);
				*(lines + j) = *(lines + j + 1);
				*(lines + j + 1) = swap_str;
			}
		}
	}

	for( i = 0; i < str_cnt; i++ )
		fputs( *(lines + i), fpout );

	free( arr );

	return 0;
}