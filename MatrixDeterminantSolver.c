#include <stdio.h>
#include <stdlib.h>
#define COL_SIZE 3
#define ROW_SIZE 3

/* Jessica Ju
prelab3.c */

int DetMat(int mat[][COL_SIZE], int row_size, int col_size);

void CofAdjMat(int mat[][COL_SIZE], int row_size, int col_size,
               int &cof[][COL_SIZE], int &adj[][COL_SIZE]);


int main()
{
    FILE * myfile;
    myfile = fopen ("input_prelab3.txt", "r");  /* open the file for reading */
    int i, j = 0;
    int matrice[3][3];

    if (myfile != NULL)
    {

        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                fscanf(myfile,"%d", &matrice[i][j]);
                printf("value is %d\n", matrice[i][j]);
            }
        }

        int det = DetMat(matrice, 3, 3);

        if (det != 0)
        {
            printf("determinant of the matrix is %d\n", det);
        }
        else
        {
            printf("The matrix is invertible.");
        }


        int coFactorMatrix[3][3];
        int adjOfCoFactorMatrix[3][3];

        CofAdjMat(matrice, 3, 3, coFactorMatrix, adjOfCoFactorMatrix);

        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                printf("cof_value is %d\n", coFactorMatrix[i][j]);


            }
        }
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                 printf("adj_value is %d\n", adjOfCoFactorMatrix[i][j]);


            }
        }





    }
    else
    {
       printf("FILE NOT AVAILABLE");
    }

}


int DetMat(int mat[][COL_SIZE], int row_size, int col_size)
{
    // in order to get determinant we have to be working with a square
    int a = 0;
    int b = 0;

    for(a = 0; a < 3; a++)
    {
        for(b = 0; b < 3; b++)
        {
                //fscanf(myfile,"%d", &matrice[i][j]);
                printf("mat_value is %d\n", mat[a][b]);
        }
    }

    if (row_size == col_size)
    {
        if (row_size == 1)
        {
            printf("1 x1 solving... ");
            return mat[0][0];
        }
        else if(row_size ==2)
        {
            printf("2 x2 solving... ");
            return (mat[0][0]*mat[1][1]) + (mat[0][1]*mat[1][0]);
        }
        else if(row_size == 3)
        {
            printf("3 x3 solving...\n ");
            int mat00 = printf("(0, 0) = %d\n", mat[0][0]);

            int aei = (mat[0][0]*mat[1][1]*mat[2][2]);

            printf("aei = %d\n", aei);
            int bfg = (mat[0][1]*mat[1][2]*mat[2][0]);

             printf("bfg = %d\n", bfg);
            int cdh = (mat[0][2]*mat[1][0]*mat[2][1]);
             printf("cdh = %d\n", cdh);
            int ceg = (mat[0][2]*mat[1][1]*mat[2][0]);
             printf("ceg = %d\n", ceg);
            int bdi = (mat[0][1]*mat[1][0]*mat[2][2]);
             printf("bdi = %d\n", bdi);
            int afh = (mat[0][0]*mat[1][2]*mat[2][1]);
             printf("afh = %d\n", afh);

            return (aei + bfg + cdh - ceg - bdi - afh);
        }
        else if(row_size > 3)
        {
            printf("Idk how to solve an array greater than 3 by 3 bro.\n ");
            return 0;
        }

    }
    else
    {
        return 0;
    }
}



void CofAdjMat(int mat[][COL_SIZE], int row_size, int col_size,int &cof[][COL_SIZE], int &adj[][COL_SIZE])
{
     // Calculate cofactor matrix first
     if (COL_SIZE != 3 || ROW_SIZE != 3)
       printf("Array is incorrect dimensions. ");
     else {
         int tempMatrix[3][3];

         tempMatrix[0][0] = mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1]; // ei - fh

         tempMatrix[1][0] = -(mat[0][1]*mat[2][2] - mat[0][2]*mat[2][1]); // -(bi - ch)

         tempMatrix[2][0] = mat[0][1]*mat[1][2] - mat[0][2]*mat[1][1]; //bf – ce

         tempMatrix[0][1] = -(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0]); // -(di - fg)

         tempMatrix[1][1] = mat[0][0]*mat[2][2] - mat[0][2]*mat[2][0]; //ai - cg

         tempMatrix[2][1] = -(mat[0][0]*mat[1][2] - mat[0][2]*mat[1][0]); // -(af – cd)

         tempMatrix[0][2] = mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]; //dh - eg

         tempMatrix[1][2] = -(mat[0][0]*mat[2][1] - mat[0][1]*mat[2][0]); //-(ah – bg)

         tempMatrix[2][2] = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]; //ae – bd

         &cof = tempMatrix;

         int n = 0;
         int m = 0;

         for (n = 0; n < 3; n++)
         {
            for (m = 0; m < 3; m++)
            {
                &adj[m][n] = &cof[n][m];

            }
         }

        for (n = 0; n < 3; n++)
         {
            for (m = 0; m < 3; m++)
            {
                 printf("BOTTOM: cof_value is %d\n", cof[n][m]);


            }
         }

         for (n = 0; n < 3; n++)
         {
            for (m = 0; m < 3; m++)
            {
                 printf("BOTTOM: adj_value is %d\n", adj[n][m]);


            }
         }

    }
}
