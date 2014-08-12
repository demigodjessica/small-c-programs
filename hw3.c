#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#define	ROWS	512
#define	COLS	512
#define thresh	50

void clear( unsigned char image[][COLS] );
void header( int row, int col, unsigned char head[32] );


// Jessica Ju 

int main( int argc, char **argv )
{
	int				i, j;
	int				x, y, a, X, Y;
	FILE			*fp;
	unsigned char	image[ROWS][COLS];
	char *ifile, *ofile;
	unsigned char head[32];
	
	// Input image file 
	ifile = "image1.raw";
	// Output image file
	ofile = "image1.ras";

	// Clear image buffer
	clear(image);

	// Read in a raw image
	// Open the file
	if (( fp = fopen( ifile, "rb" )) == NULL )
	{
		fprintf( stderr, "error: couldn't open %s\n", argv[1] );
		exit( 1 );
	}			

	// Read the file
	for ( i = 0; i < ROWS ; i++ )
		if ( fread( image[i], 1, COLS, fp ) != COLS )
		{
			fprintf( stderr, "error: couldn't read enough stuff\n" );
			exit( 1 );
		}

	// Close the file
	fclose( fp );
	
	// Create a header
	header(ROWS, COLS, head);

	//Threshold
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			if(image[i][j]>thresh)
			{
				image[i][j]=0;
				binary[i][j]=0;
			}
			else 
			{
				image[i][j]=255;
				binary[i][j]=1;
			}
		}
	}

	//Area, Center of Area
	a=0;
	x=0;
	y=0;
	for(i=0;i<ROWS;i++)
		{
			for(j=0;j<COLS;j++)
				{
					a=a+binary[i][j];
					x=x+binary[i][j]*i;
					y=y+binary[i][j]*j;
				}
		}
	printf("Area=%d\nCenter of Area: \nX=%d Y=%d\n", a, X, Y);

	//128 Gray Box
	X = x/a;
	Y = y/a;
	while(i==X && j==Y)
	{
		image[i][j]=128;
	}

	// Save it into a ras image
	// Open the file
	if (!( fp = fopen( ofile, "wb" )))
	  fprintf( stderr, "error: could not open %s\n", argv[1] ), exit(1);

	// Write the header
	fwrite( head, 4, 8, fp );

	// Write the image
	for ( i = 0; i < ROWS; i++ ) 
		fwrite( image[i], 1, COLS, fp );


	// Close the file
	fclose( fp );
 
	return 0;
}

void clear( unsigned char image[][COLS] )
{
	int	i,j;
	for ( i = 0 ; i < ROWS ; i++ )
		for ( j = 0 ; j < COLS ; j++ ) image[i][j] = 0;
}


void header( int row, int col, unsigned char head[32] )
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	// Choose little-endian or big-endian header depending on the machine. Don't modify this
	// Little-endian for PC
	
	*p = 0x956aa659;
	*(p + 3) = 0x08000000;
	*(p + 5) = 0x01000000;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8000000;

	ch = (char*)&col;
	head[7] = *ch;
	ch ++; 
	head[6] = *ch;
	ch ++;
	head[5] = *ch;
	ch ++;
	head[4] = *ch;

	ch = (char*)&row;
	head[11] = *ch;
	ch ++; 
	head[10] = *ch;
	ch ++;
	head[9] = *ch;
	ch ++;
	head[8] = *ch;
	
	ch = (char*)&num;
	head[19] = *ch;
	ch ++; 
	head[18] = *ch;
	ch ++;
	head[17] = *ch;
	ch ++;
	head[16] = *ch;
	
/*
	// Big-endian for unix
	*p = 0x59a66a95;
	*(p + 1) = col;
	*(p + 2) = row;
	*(p + 3) = 0x8;
	*(p + 4) = num;
	*(p + 5) = 0x1;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8;
*/
}