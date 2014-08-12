#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define ROWS   		 		 400
#define COLS				 400


// Jessica Ju 
// 46483660 
// HW7 EECS101 

void writeFile(char *outfile);
void clear( unsigned char image[ROWS][COLS] );
void header( int row, int col, unsigned char head[32] );
unsigned char	image[ROWS][COLS];
unsigned char head[32];
FILE			*fp;
void clearL( double L[ROWS][COLS] );
void createImage(double s[3], double r, double a, double m, char *filename);


int main( int argc, char **argv )
{	
	// Set the Source direction
	double s[3]={0,0,1}; 
	// Set the source direction 
	// Set the r(object size), a (weight used in combining the Lambertian and specular reflection)
	// m (surface roughness), and also the what you want your output file to be named. 
	createImage(s, 50, 0.5, 1, "imageA.ras");
	return 0;
}

// Input S vector, r, a, m double values 
void createImage(double s[3], double r, double a, double m, char *filename)
{
	double L[ROWS][COLS];
	double normalX, normalY, normalZ;
	double hX, hY, hZ;
	double Ll, Ls;
	double max = 0;
	double alpha;
	int y,x;
	clear(image);
	clearL(L);

	// Create proper pixel values for our 400 by 400 image 
	for(y=0; y<ROWS; y++)
	{
		for(x=0; x<COLS; x++)
		{
			if((pow(x-COLS/2,2)+pow(y-ROWS/2,2))<(pow(r,2)))
			{

				// In order to derive the surface normal 
				// N = (-p, -q, 1) / sqrt(p^2 + q^2 + 1)
				normalX = (x-COLS/2)/r;
				normalY = (y-ROWS/2)/r;
				normalZ = sqrt(pow(r,2)-(pow((x-COLS/2),2)+pow((y-ROWS/2),2)))/r;
				
				// H = (V + S) / |V+S| 
				hX = (0+s[0])/sqrt(pow(0+s[0],2)+pow(0+s[1],2)+pow(1+s[2],2));
				hY = (0+s[1])/sqrt(pow(0+s[0],2)+pow(0+s[1],2)+pow(1+s[2],2));
				hZ = (1+s[2])/sqrt(pow(0+s[0],2)+pow(0+s[1],2)+pow(1+s[2],2));
				
				// alpha is angle in radians beteen the normal and H 
				alpha = acos((normalX*hX)+(normalY*hY)+(normalZ*hZ));

				// Specular component
				// Ls = exp(-(alpha/m)^2) 
				Ls = pow(M_E, (-1.0*(pow((alpha/m),2))));

				// Lambertian component = cos(theta) = use dot product 
				// theta is the angle between surface and normal 
				Ll = (s[0]*normalX+s[1]*normalY+s[2]*normalZ);

				// Throw away results 
				if(acos(Ll)>M_PI/2)
					Ll=0;
				
				// Formula for irradiance L = a*Ll + (1-a)*Ls
				L[y][x]= a*Ll+(1-a)*Ls;

				if(L[y][x]>max) 
					max =L[y][x]; // used to normalize later 
			}
		}
	}
	
	for(y=0; y<ROWS; y++)
	{
		for(x=0; x<COLS; x++)
		{
		   image[y][x]= ((L[y][x]/max)*255); // use L for value of each pixel (normalized)
		}
	}
	writeFile(filename);
	clearL(L);
	clear(image);

}

void writeFile(char *outfile)
{
	int i;
	/* Create a header */
	header(ROWS, COLS, head);
	/*write out*/
	if (!( fp = fopen( outfile, "wb" )))
        fprintf( stderr, "error: could not open %s\n", outfile ), exit(1);
	
	fwrite( head, 4, 8, fp );
    
	// Write the image
	for ( i = 0; i < ROWS; i++ )
		fwrite( image[i], 1, COLS, fp );
	// Close the file
	fclose( fp );
}

	
void clear( unsigned char image[ROWS][COLS] )
{
	int	i,j;
	for ( i = 0 ; i < ROWS ; i++ )
		for ( j = 0 ; j < COLS ; j++ ) image[i][j] = 0;
}

void clearL( double L[ROWS][COLS] )
{
	int	i,j;
	for ( i = 0 ; i < ROWS ; i++ )
		for ( j = 0 ; j < COLS ; j++ ) L[ROWS][COLS] = 0;
}

void header( int row, int col, unsigned char head[32] )
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	/* Choose little-endian or big-endian header depending on the machine. Don't modify this */
	/* Little-endian for PC */
	
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
	
		



