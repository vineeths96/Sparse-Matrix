void mat_gen(int coo_value[15000], int coo_row_ind[150], int coo_col_ind[100], int m, int n, float density_percent, float negative_percent);				// Random matrix generation

void transform(int coo_value[15000], int coo_row_ind[15000], int coo_col_ind[15000], int csr_value[15000],int csr_row_ptr[151], int csr_col_ind[15000], int csc_value[15000], int csc_col_ptr[101], int csc_row_ind[15000], int m, int n);																	// Transforming to CSR,CSC	

void bubblesort(int coo_sort_value[15000], int coo_sort_row_ind[15000], int coo_sort_col_ind[15000]);									// Bubble sort

void getdata(int choice, int C_value[15000], int C_row_ind[15000], int C_col_ind[15000], int A_value[15000],int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000]);																			// Data collection

void multiply(int A_value[150100], int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000], int res_value[15000], int res_col_ind[15000], int res_row_ind[15000]);																			// Multiplying CSR & CSC

void row_transform(int B_value[15000], int B_col_ptr[101], int B_row_ind[15000], int r1, int r2, int k1, int k2);							// Row transformation

void print_matrix(int C_value[15000], int C_row_ind[15000], int C_col_ind[15000], int A_value[15000],int A_row_ptr[151], int A_col_ind[15000], int B_value[15000], int B_col_ptr[101], int B_row_ind[15000]);																			// Print matrices
