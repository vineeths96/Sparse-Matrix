#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void mat_gen(int coo_value[15000], int coo_row_ind[150], int coo_col_ind[100], int m, int n, float density_percent, float negative_percent)
{
	int temp[150][100] = {0}, neg = 0, ind = 0;
	int total_num = m*n;
	int num_nz = total_num * density_percent/100;
	int neg_nz = total_num * negative_percent/100;
	int pos_nz = num_nz - neg_nz;
	
	srand(time(0));
 
	// Random matrix generation
	for(int i = 0; i < num_nz; i++)
	{
		int row = rand()%m;
		int col = rand()%n;
		if(temp[row][col] != 0)						// If already element present find new indices
		{
			i = i-1;
			continue;	
		}
		else
		{
			if(neg < neg_nz)
			{			
				temp[row][col] =(-1) * (rand()%100 + 1);
				neg++;
			}
			else
				temp[row][col] = (rand()%100 + 1);
			
		}
	}

	// Transform matrix to COO format
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(temp[i][j] == 0)	continue;
			coo_value[ind] = temp[i][j];
			coo_row_ind[ind] = i+1;
			coo_col_ind[ind] = j+1;
			ind++;
		}	

	}

	// Printing generated random matrix
	printf("\n\nRandom matrix generated\n");
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
			printf("%d \t", temp[i][j]);
		printf("\n");
	}

	// Printing COO format
	printf("\nCOO format matrices");

	printf("\nCOO Value matrix          : [\t");
	for(int i = 0; coo_value[i] != 0; i++)		printf("%d\t", coo_value[i]);
	
	printf("]\nCOO Row index matrix      : [\t");
	for(int i = 0; coo_row_ind[i] != 0; i++)	printf("%d\t", coo_row_ind[i]);
	
	printf("]\nCOO Column index matrix   : [\t");
	for(int i = 0; coo_col_ind[i] != 0; i++)	printf("%d\t", coo_col_ind[i]);
	printf("]\n");
}


void transform(int coo_value[15000], int coo_row_ind[15000], int coo_col_ind[15000], int csr_value[15000],int csr_row_ptr[151], int csr_col_ind[15000], int csc_value[15000], int csc_col_ptr[101], int csc_row_ind[15000], int m, int n)
{
	// Transforming COO format to CSR format
	int csr_ind = 0, prev_row = 0, curr_row = 0, j = 0;
	for(int i = 0; coo_value[i] != 0; i++)
	{
		if(csr_row_ptr[0] == 0)	csr_row_ptr[0] = prev_row = curr_row = coo_row_ind[i];
		csr_value[csr_ind] = coo_value[i];
		csr_col_ind[csr_ind] = coo_col_ind[i];
		curr_row = coo_row_ind[i];
		csr_ind++;

		if(prev_row != curr_row)
		{	
			csr_row_ptr[j+1] = csr_ind;
			prev_row = curr_row;
			j++;
		}
	}
	csr_row_ptr[j+1] = csr_ind + 1;


	// Duplicating the COO format matrices
	int coo_sort_value[15000] = {0}, coo_sort_row_ind[15000] = {0}, coo_sort_col_ind[15000] = {0};
	for(int i = 0; coo_value[i] != 0; i++)
	{
		coo_sort_value[i] = coo_value[i];
		coo_sort_row_ind[i] = coo_row_ind[i];
		coo_sort_col_ind[i] = coo_col_ind[i];
	}

	// Sorting the COO copy matrices to order by columns
	bubblesort(coo_sort_value, coo_sort_row_ind, coo_sort_col_ind);


	// Transforming COO format to CSC format
	int csc_ind = 0, prev_col = 0, curr_col = 0, k = 0;
	for(int i = 0; coo_sort_value[i] != 0; i++)
	{
		if(csc_col_ptr[0] == 0)	csc_col_ptr[0] = prev_col = curr_col = coo_sort_col_ind[i];
		csc_value[csc_ind] = coo_sort_value[i];
		csc_row_ind[csc_ind] = coo_sort_row_ind[i];
		curr_col = coo_sort_col_ind[i];
		csc_ind++;
		
		if(prev_col != curr_col)
		{	
			csc_col_ptr[k+1] = csc_ind;
			prev_col = curr_col;
			k++;
		}
	}
	csc_col_ptr[k+1] = csc_ind + 1;

	
	// Printing CSR matrices
	printf("\nCSR format matrices");

	printf("\nCSR Value matrix          : [\t");
	for(int i=0; csr_value[i] != 0; i++)	printf("%d\t", csr_value[i]);

	printf("]\nCSR Row pointer matrix    : [\t");
	for(int i=0; csr_row_ptr[i] != 0; i++)	printf("%d\t", csr_row_ptr[i]);

	printf("]\nCSR Column index matrix   : [\t");	
	for(int i=0; csr_col_ind[i] != 0; i++)	printf("%d\t", csr_col_ind[i]);
	printf("]\n");


	// Printing CSC matrices
	printf("\nCSC format matrices");

	printf("\nCSC Value matrix          : [\t");
	for(int i=0; csc_value[i] != 0; i++) printf("%d\t", csc_value[i]);

	printf("]\nCSC Column pointer matrix : [\t");
	for(int i=0; csc_col_ptr[i] != 0; i++) printf("%d\t", csc_col_ptr[i]);

	printf("]\nCSC Row index matrix      : [\t");	
	for(int i=0; csc_row_ind[i] != 0; i++) printf("%d\t", csc_row_ind[i]);
	printf("]\n");


}

void bubblesort(int coo_sort_value[15000], int coo_sort_row_ind[15000], int coo_sort_col_ind[15000])
{
	int temp = 0;

	for(int i = 0; coo_sort_col_ind[i] != 0; i++)
	{
		for(int j = 0; coo_sort_col_ind[i+j+1] != 0; j++)
		{
			if(coo_sort_col_ind[j] >= coo_sort_col_ind[j+1])
			{
				// Sort by rows if columns are same
				if(coo_sort_col_ind[j] == coo_sort_col_ind[j+1])	if(coo_sort_row_ind[j] < coo_sort_row_ind[j+1])	continue;
				
				temp = coo_sort_col_ind[j];
				coo_sort_col_ind[j] = coo_sort_col_ind[j+1];
				coo_sort_col_ind[j+1] = temp;

				temp = coo_sort_row_ind[j];
				coo_sort_row_ind[j] = coo_sort_row_ind[j+1];
				coo_sort_row_ind[j+1] = temp;

				temp = coo_sort_value[j];
				coo_sort_value[j] = coo_sort_value[j+1];
				coo_sort_value[j+1] = temp;
			}
		}
	}
}


void multiply(int A_value[15000], int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000], int res_value[15000], int res_col_ind[15000], int res_row_ind[15000])
{
	int idx=0;

	// Finding number of rows and columns of CSR matrix and CSC matrix which are inputted
	int A_row = 0, A_col = 0, B_row = 0, B_col = 0;
	
	for(int i = 0; A_row_ptr[i+1] !=0 ; i++)
		A_row++;
	
	for(int i = 0; A_col_ind[i] !=0 ; i++)
		if(A_col_ind[i] > A_col)	A_col = A_col_ind[i];

	for(int i = 0; B_row_ind[i] !=0 ; i++)
		if(B_row_ind[i] > B_row)	B_row = B_row_ind[i];

	for(int i = 0; B_col_ptr[i+1] !=0 ; i++)
		B_col++;


	// Checking if multipliable 
	if(A_col != B_row)
	{
		printf("\nMatrices A and B cannot be multiplied");
			
	}
	else
	{
		for(int i = 0; A_row_ptr[i+1] != 0; i++)
		{
			for(int j = 0; B_col_ptr[j+1] != 0; j++)
			{	
				int res = 0;
				for(int k = (A_row_ptr[i]-1), p = (B_col_ptr[j]-1);  (k != (A_row_ptr[i+1]-1) && p != (B_col_ptr[j+1]-1)); )
				{
					// Multiplying if indices match as per matrix multiplication rules 
					if(A_col_ind[k] != B_row_ind[p])	
					{ 
						if(A_col_ind[k] < B_row_ind[p])	k++;
						if(A_col_ind[k] > B_row_ind[p]) p++;
						continue;
					}
				
					res += A_value[k] * B_value[p];
					k++; p++;
					
				}
				
				// Save into COO result matrices if the product is non zero
				if(res != 0)
				{
					res_value[idx] = res;
					res_row_ind[idx] = i+1;
					res_col_ind[idx] = j+1;
					
					idx++;
				}
			}
		
	
		}
	}

	printf("\nResult in COO format");

	printf("\nCOO Value matrix          : [\t");
	for(int i = 0; res_value[i] != 0; i++)		printf("%d\t", res_value[i]);

	printf("]\nCOO Row index matrix      : [\t");
	for(int i = 0; res_row_ind[i] != 0; i++)	printf("%d\t", res_row_ind[i]);

	printf("]\nCOO Column index matrix   : [\t");
	for(int i = 0; res_col_ind[i] != 0; i++)	printf("%d\t", res_col_ind[i]);
	printf("]\n");
}


void getdata(int choice, int C_value[15000], int C_row_ind[15000], int C_col_ind[15000], int A_value[15000],int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000])
{
	// COO Data input when choice = 1
	if(choice == 1)
	{
		int r;
		printf("\nEnter size of value matrix for COO matrix\n");
		scanf("%d", &r);
		
		printf("Enter the value matrix\n");
		for(int i = 0; i < r; i++)	scanf("%d", &C_value[i]);
		printf("Enter the row index matrix\n");
		for(int i = 0; i < r; i++)	scanf("%d", &C_row_ind[i]);
		printf("Enter the col index matrix\n");
		for(int i = 0; i < r; i++)	scanf("%d", &C_col_ind[i]);
	}

	// CSR Data input
	int m, n;
	printf("\nEnter size of value matrix and row pointer matrix for CSR matrix\n");
	scanf("%d %d", &m, &n);

	printf("Enter the value matrix\n");
	for(int i = 0; i < m; i++)	scanf("%d", &A_value[i]);
	printf("Enter the row pointer matrix\n");
	for(int i = 0; i < n; i++)	scanf("%d", &A_row_ptr[i]);
	printf("Enter the column index matrix\n");
	for(int i = 0; i < m; i++)	scanf("%d", &A_col_ind[i]);


	// CSC Data input
	int p, q;
	printf("\nEnter size of value matrix and col pointer matrix for CSC matrix\n");
	scanf("%d %d", &p, &q);
	
	printf("Enter the value matrix\n");
	for(int i = 0; i < p; i++)	scanf("%d", &B_value[i]);
	printf("Enter the column pointer matrix\n");
	for(int i = 0; i < q; i++)	scanf("%d", &B_col_ptr[i]);
	printf("Enter the row index matrix\n");
	for(int i = 0; i < p; i++)	scanf("%d", &B_row_ind[i]);
}


void row_transform(int B_value[15000], int B_col_ptr[101], int B_row_ind[15000], int r1, int r2, int k1, int k2)
{

	// Row transformation
	for(int i = 0; B_col_ptr[i+1] != 0; i++)
	{
		// Finding length of CSC Value matrix
		int len = 0;
		for(len = 0; B_value[len] != 0; len++);

		int r1_ind = -1, r2_ind = -1, k = 0, loc = 0;

		// Checking if row indexes match with inputted r1 and r2 
		for(int j = (B_col_ptr[i]-1); j != (B_col_ptr[i+1]-1); j++)
		{
			if(B_row_ind[j] == r1)	r1_ind = j ;
 			if(B_row_ind[j] == r2)	r2_ind = j ;
			if(B_row_ind[j] < r2)	loc = j+1;
		} 
		
		// No match found
		if((r1_ind < 0) && (r2_ind < 0))	continue;

		// Proceed if match found
		if((r1_ind > 0) && (r2_ind > 0))
		{
			B_value[r2_ind] = k1*B_value[r1_ind] + k2*B_value[r2_ind];

			// Remove entry in CSC matrices in case the value entry becomes 0 after row transformation
			if(B_value[r2_ind] == 0)
			{
				for(k = r2_ind; B_value[k+1] != 0; k++)
				{
					B_value[k] = B_value[k+1];
					B_row_ind[k] = B_row_ind[k+1];
				}

				B_value[k] = 0;
				B_row_ind[k] = 0;

				for(int m = (i+1); B_col_ptr[m] != 0; m++)	B_col_ptr[m]--;	
			}


		}
		else if(r2_ind > 0)
		{
			B_value[r2_ind] = k2*B_value[r2_ind];
		}
		else
		{	
			// New entry in CSC matrices if a new non zero element is to be added
			for(k = len; k != loc; k--)
			{
				B_value[k] = B_value[k-1];
				B_row_ind[k] = B_row_ind[k-1];
			}

			B_value[k] = k1*B_value[r1_ind];
			B_row_ind[k] = r2;
			
			for(int m = (i+1); B_col_ptr[m] != 0; m++)	B_col_ptr[m]++;			
			
		}
	}

	printf("\nCSC format matrices after row transformation");

	printf("\nCSC Value matrix          : [\t");
	for(int i = 0; B_value[i] != 0; i++)		printf("%d\t", B_value[i]);

	printf("]\nCSC Column pointer matrix : [\t");
	for(int i = 0; B_col_ptr[i] != 0; i++)		printf("%d\t", B_col_ptr[i]);

	printf("]\nCSC Row index matrix      : [\t");	
	for(int i = 0; B_row_ind[i] != 0; i++)		printf("%d\t", B_row_ind[i]);
	printf("]\n");
}



void print_matrix(int C_value[15000], int C_row_ind[15000], int C_col_ind[15000], int A_value[15000],int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000])
{
	int A_row = 0, A_col = 0, B_row = 0, B_col = 0, C_row = 0, C_col = 0;

	// Calculating rows and columns
	for(int i = 0; A_row_ptr[i+1] !=0 ; i++)
		A_row++;
	
	for(int i = 0; A_col_ind[i] !=0 ; i++)
		if(A_col_ind[i] > A_col)	A_col = A_col_ind[i];

	for(int i = 0; B_row_ind[i] !=0 ; i++)
		if(B_row_ind[i] > B_row)	B_row = B_row_ind[i];

	for(int i = 0; B_col_ptr[i+1] !=0 ; i++)
		B_col++;

	for(int i = 0; C_row_ind[i] !=0 ; i++)
		if(C_row_ind[i] > C_row)	C_row = C_row_ind[i];

	for(int i = 0; C_col_ind[i] !=0 ; i++)
		if(C_col_ind[i] > C_col)	C_col = C_col_ind[i];


	// Checking matrix limits specified
	if((A_row > 20) || (A_col > 20) || (B_row > 20) || (B_col > 20) || (C_row > 20) || (C_col > 20))
	{
		printf("Dimensions exceeds 20x20");
		return;
	}
	
	// Sorting the COO matrix by rows
	bubblesort(C_value, C_col_ind, C_row_ind);
	
	// Printing COO matrix
	printf("\n\nCOO matrix\n");
	for(int i = 0, j = 0; j < C_row; j++)
	{
		for(int k = 0; k < C_col; k++)
		{
			if((C_row_ind[i] == (j+1)) && (C_col_ind[i] == (k+1)))
			{
				printf("%d\t", C_value[i]);
				i++; 
			}
			else
				printf("0\t");
		
		}
		printf("\n");

	}

	// Printing CSR matrix
	printf("\n\nCSR matrix\n");
	int idx = 0;
	for(int i = 0; i < A_row; i++)
	{
		for(int j = 0; j < A_col; j++)
		{
			if((A_col_ind[idx] == (j+1)) && (A_row_ptr[i+1] != (idx+1)))
			{
				printf("%d\t", A_value[idx]);
				idx++; 
			}
			else
				printf("0\t");
		
		}
		printf("\n");

	}

	// Printing COO matrix
	printf("\n\nCSC matrix\n");
	for(int i = 0; i < B_row; i++)
	{
		for(int j = 0; j < B_col; j++)
		{
			int flag = 0;
			for(int k = (B_col_ptr[j]-1); k != (B_col_ptr[j+1]-1); k++)
			{
				if(B_row_ind[k] == (i+1))
				{
					printf("%d\t", B_value[k]);
					flag++; 
				}
			}
			if(!flag)	printf("0\t");
		}
		printf("\n");

	}
	
	printf("\n\n");
}



