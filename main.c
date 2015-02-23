/*####################################################################################################
#
#	Code Details :- Calculator program start point
#	Author :- miku<jeeban29@gmail.com>
#
####################################################################################################*/


#include"headers.c"


int main(int main_argc,char **main_argv )
{

	int i;
	
	printf("argc = %d\n", main_argc);
	for(i=0; i<main_argc;i++)
	{
		printf("argv[ %d ] = %s\n", i, main_argv[i]);
	}
	
	check_expression_for_error( main_argc, main_argv );
	
	initialize_memory( main_argc, main_argv );

	process_fact();
	
	process_mul();

/*//////////////////////////////////////////////////////////////////////////////////////////
//* testing zone`( you can add your code here )



//	sprintf( temp_memory[1], "0000006589" );
//	sprintf( temp_memory[2], "6590" );

	sprintf( temp_memory[17], "10000" ); //finding factorial of 50000 
	sprintf( temp_memory[18], "7.5" );
//	sprintf( temp_memory[19], "value not set yet" );
	
//	printf("\n\nfinal calculation(before) 	:= %d\n",count_float("123"));
	
//	divide_new( temp_memory[17], temp_memory[18], temp_memory[19] );
//	factorial_new( temp_memory[17], temp_memory[19] );
	
	printf("final calculation := %s\n\n", temp_memory[19]);
	printf( "length = %d\n", string_length( temp_memory[19] ) );




/////////////////////////////////////////////////////////////////////////////////////////*/
	process_sign();
	
	process_addition();

	printf("\n\nfinal calculation 	:= %s\n\n", final);
		
	destroy_memory();
	
	return 0;
}























































