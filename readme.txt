================================================================
ASSIGNMENT 1 - README.TXT
================================================================


FILES INCLUDES WITH THIS PROJECT:
================================================================

	client.c	header.h	implement.c
	readme.txt	testcase.txt	makefile


PROGRAM
================================================================

INTRODUCTION
-------------

	This program deals with the compressed row/column format of sparse matrices and its manipulation.
Compressed sparse matrix formars stores the sparse matrixes in much more efficient way with reduced space
requirements. The theory in detail has been provided along with the assignamnet sheet.The entire program 
is written in three files. Comments have been added frequently to help in understanding the logic behind 
implementation. The program has five functions pertaining one to each question and
two additional functions to sort and input data to matrices. Refer problem statement file for detailed information.


OPERATING SYSTEM AND SOFTWARE REQUIRMENTS
------------------------------------------

	The entire program was developed in Ubuntu operating system using C language. It is highly recommeneded 
to use the Ubuntu system to execute the program. The program requires gcc compiler to compile, build and 
execute the program. The OS and compiler version used for developing the code are :
		Operating system 	: Ubuntu 18.04.1 
		gcc compiler verison	: gcc version 7.4.0

FAQ
----

Q. What is the need for sorting function in the program?
A. Sorting the matrices by order of rows/columns reduces the complexity of code to a great extent. 
Sorting by order of column is used for transforming COO format matrix to CSC format matric ( in transform() ). 
Sorting by order of rows is essential in printing out the COO format matrix when the indices are not in 
ascending order ( in print_matrix() ).

Q. Which CSC matrix is used in row_transform() ?
A. The CSC format matrix inputted for multiplying is used as the CSC matrix in row_transform(). 
The code could be slighlty modified to receive new inputs if necessary.

Q. What is the logic used in implementing multiplication function?
A. The logic used here follows the rules of multiplication in matrix theory. The function first determines
 the number of rows and columns (of say matrixes A and B) and tests if they are multipliable. If they are 
multipliable, for each row in the matrix A, dot product with the each column B are calculated. Here neither 
A nor B are reconstruted to full matrices. The value, pointer, and index matrices of CSR and CSC are used 
to identify the location of an element in a matrix and do the computations.

Q. What is the logic used in implementing row transformation function?
A. During row transformation, three cases can ocuur.
	1. Element present at the row				- For this case we can directly proceed with 
								  replacing the element with new computed value
	2. Element not present at the row			- For this case we have to calculate the value 
								  and then we have to create an empty slot ( by 
								  shifting the array to right ) for storing that 
								  element at desired loaction.
	3. Element present, but becomes 0 after computing	- For this case we should remove the entry 
								  corresponding to 0 from value, pointer, and 
								  index matrices ( by shifting array to left ).


TEST CASES
----------

	The "testcode.txt" contains the 5 test cases. Comments have been added to guide through the test case 
file to identify where to input data. 


INSTRUCTIONS TO RUN
--------------------

	Open the terminal, make the program and run it. Enter the values from the file (or custom values) 
as requested during exectuion of the program.


CONTACT
========
Developed by
Name	 : Vineeth S


