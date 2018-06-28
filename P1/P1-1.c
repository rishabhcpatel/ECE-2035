/*            Diamond Sort


Due: 02/21/2018   	             Rishabh C. Patel

This program sorts a diamond array of disks of varying hues and
diameters. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int	Array[169];
   int	NumVals;
   int  Load_Mem(char *, int *);
   void	Print_Array(int *);

   if (argc != 2) {
     printf("usage: %s valuefile\n", argv[0]);
     exit(1);
   }
   NumVals = Load_Mem(*++argv, Array);
   if (NumVals != 85) {
      printf("not enough values in %s\n", argv[0]);
      exit(1);
   }

/* your code goes here */   
int dx = 0;	//Going through the arrray in x direction
int dy = 0; 	//Going through the array in y direction
int dim = 0;    //Since 2x2 Array, going
int dim2 = 0;   //through the array 2 times. 

int posd1;	//diameter 1 at position1
int posd2;	//diameter 2 at position2

int first;	//Placeholder variable used in bubble sort

int posh1;	//hue 1 at position1
int posh2;	//hue 2 at position2

for (dim2 = 0; dim2 < 13; dim2++)
{
	for(dim = 0; dim < 13; dim++) 
	{
		//DIAMETER Sorting
		for(dx = 0; dx < 169; dx += 13)
		{	
			for(dy = dx + 13; dy < 169; dy += 13)
			{
				posd1 = Array[dim + dx] / 64;
				posd2 = Array[dim + dy] / 64;
			
				if (posd1 > posd2 && Array[dim + dx] != -1 && Array[dim + dy] != -1) //bubble sort
				{
					first = Array[dim + dx];
					Array[dim + dx] = Array[dim + dy];
					Array[dim + dy] = first;  			
				}  	
			}	
		}//End Diameter

		//HUE Sorting
		for(dx = 0; dx < 13; dx++)
		{
			for(dy = dx + 1; dy < 13; dy++)
			{
				posh1 = Array[(dim * 13) + dx] % 64;
				posh2 = Array[(dim * 13) + dy] % 64;
				if (posh1 > posh2 && Array[(dim * 13) + dx] != -1 && Array[(dim * 13) + dy] != -1) //bubble sort   
				{
					first = Array[(dim * 13) + dx];
					Array[(dim * 13) + dx] = Array[(dim * 13) + dy];
					Array[(dim * 13) + dy] = first;		
				}
			
			}
		
		}//End Hue     	
	}//End Dim  
}//End sorting 2x2 Array  




   Print_Array(Array);
   exit(0);
}

/* This routine initializes a 13 x 13 array with zeros. Then it loads
85 memory elements from the input file. The values are loaded in
address: value tuples. The first value is loaded into position 6. All
other values are positioned relative to the address of the first word.
The number of loaded values are returned. */

int Load_Mem(char *InputFileName, int Array[]) {
   int	N, Addr, Value, Index, NumVals;
   int	Base = -1;
   FILE	*FP;

   for (N=0; N < 169; N++)
     Array[N] = -1;
   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 85; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals != 2)
            break;
         else
            if (Base == -1)
               Base = Addr - 24;
            Index = (Addr - Base) / 4;
            Array[Index] = Value;
      }
      fclose(FP);
      return N;
   }
}

/* This routine prints a diamond. The hue and diameter are unpacked before printing.
Empty array cells are printed as blanks. */

void Print_Array(int Array[]) {
   int	N, Value, Diameter, Hue;

   for (N=0; N < 169; N++) {
      Value = Array[N];
      if (Value == -1)
         printf("      ");
      else {
         Diameter = Value / 64;
         Hue = Value % 64;
         printf("%02d:%02d ", Diameter, Hue);
      }
      if ((N % 13) == 12)
         printf("\n");
   }
}
