#include<stdio.h>
#include "header.h"

int main()
{
	// Decalrations of arrays and variables
	int coo_value[15000] = {0}, coo_row_ind[15000] = {0}, coo_col_ind[15000] = {0};
	int csr_value[15000] = {0}, csr_row_ptr[151] = {0}, csr_col_ind[15000] = {0};
	int csc_value[15000] = {0}, csc_col_ptr[101] = {0}, csc_row_ind[15000] = {0};
	int A_value[15000] = {0}, A_row_ptr[151] = {0}, A_col_ind[15000] = {0}, B_value[15000] = {0}, B_col_ptr[101] = {0}, B_row_ind[15000] = {0};
	int res_value[15000] = {0}, res_col_ind[15000] = {0}, res_row_ind[15000] = {0};
	int An_value[15000] = {0}, An_row_ptr[151] = {0}, An_col_ind[15000] = {0}, Bn_value[15000] = {0}, Bn_col_ptr[101] = {0}, Bn_row_ind[15000] = {0};
	int Cn_value[15000] = {0}, Cn_row_ind[15000] = {0}, Cn_col_ind[15000] = {0};
	int r1, r2, k1, k2;
	int n_rows, n_cols;
	float nz,nz_neg;


	printf("\n\n\n************************************ Matrix generation ************************************************************\n");
	printf("Format to be inputed  - Rows, Columns, Density (Percentage) of non-zero entries, Percentage of negative numbers\n");
	scanf("%d %d %f %f", &n_rows, &n_cols, &nz, &nz_neg);
	mat_gen(coo_value, coo_row_ind, coo_col_ind, n_rows, n_cols, nz, nz_neg);


	
	printf("\n\n\n************************************ Matrix transformation ************************************************************\n");
	transform(coo_value, coo_row_ind, coo_col_ind, csr_value, csr_row_ptr, csr_col_ind, csc_value, csc_col_ptr, csc_row_ind, n_rows, n_cols);


	
	printf("\n\n\n************************************ Matrix multiplication ************************************************************\n");
	getdata(0, res_value ,res_row_ind, res_col_ind, A_value, A_row_ptr, A_col_ind, B_value, B_col_ptr, B_row_ind);
	multiply(A_value, A_row_ptr, A_col_ind, B_value, B_col_ptr, B_row_ind, res_value, res_col_ind, res_row_ind);


	
	printf("\n\n\n************************************ Row transformation ************************************************************\n");	
	printf("\nFormat to be inputed  - r1, r2, k1, k2\n");
	scanf("%d %d %d %d", &r1, &r2, &k1, &k2);
	row_transform(B_value, B_col_ptr, B_row_ind, r1, r2, k1, k2);


	
	printf("\n\n\n************************************ Print matrices ************************************************************\n");	
	getdata(1, Cn_value, Cn_row_ind, Cn_col_ind, An_value, An_row_ptr, An_col_ind, Bn_value, Bn_col_ptr, Bn_row_ind);
	print_matrix(Cn_value, Cn_row_ind, Cn_col_ind, An_value, An_row_ptr, An_col_ind, Bn_value, Bn_col_ptr, Bn_row_ind);


return 0;
}


