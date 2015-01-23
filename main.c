/*####################################################################################################
#
#	Code Details :- Calculator program start point
#	Author :- miku<jeeban29@gmail.com>
#
####################################################################################################*/

/*///////////////////////////////////////////////////////////////////////////////////////////////////
changes to be done.

-> add_point() syntax has been changed.
	char* add_point( char*, int ) --> void add_point( char*, int )

-> review all the function declaration



*//////////////////////////////////////////////////////////////////////////////////////////////////////

#include"headers.c"
//#include"sample.c"
//#include"test.c"

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
































































/*	int i,counter0=0,counter1=0,counter2=0,counter3=0,counter4=0;
	
	//step 1 of the process :- error checking in the expression.
	check(argc,argv);
	//error checking is completed. 
	
	//report the input numbers sizes.
	for( i=1; i<argc; i+=2 )
	{
		if( *(argv[i]) == '-')
		{
			printf("argv[%d] = %d\t-ve\n",i,string_length(argv[i]) - 1);
		}
		else
		{
			printf("argv[%d] = %d\t+ve\n",i,string_length(argv[i]));
		}		
	}
	//sizes have been reported.
	
	//report the total no of signs used in the syntax.
	for( i=2; i<argc; i+=2 )
	{
		if( less( argv[i],"+" ) == 0 )
		{
			counter0++;
		}
		else if( less( argv[i],"-" ) == 0 )
		{
			counter1++;
		}
		else if( less( argv[i],"x" ) == 0 )
		{
			counter2++;
		}
		else if( less( argv[i],"/" ) == 0 )
		{
			counter3++;
		}
		else if( less( argv[i],"%" ) == 0 )
		{
			counter4++;
		}			
	}
	
	printf("\n\naddition 	:= %d\nsubtraction 	:= %d\nmultiplication 	:= %d\ndivision	:= %d\nmod division 	:= %d\nfactorial	:= %d\n\n\n",counter0,counter1,counter2,counter3,counter4,fact_count);		
	//sign count completed.
		
	//step 2 of process :- analyze any factorial part in the expression.	
	process_fact(argc,argv);
	//step 2 completed.
	
	//reinitialize the final_mul and sum as it is changed by the factorial calculation phase.
	final_mul = "1";
	final = "0";
	
	//step 3 of process :- perform multiplication and division works.
	if(argc > 2)
	{
		process_mul(argc,fact_array);
		free( fact_array );
	}
	else
	{
		final_mul_array = fact_array;
		fact_array = NULL;
	}
	//multiplication complited.
	
	//step 4 of process :- sign analysis part
	process_sign();
	//done now the final addition and subtraction are to be done.
		
	if( argc == 2)
	{
		final = final_mul_array[1];
	}
	else
	{	
		//evaluate the expression
		
		final = final_mul_array[1];
		for( i=3; i<final_mul_array_pointer; i+=2 )
		{
			if( compare( final_mul_array[i-1], "+" ) == 0 )
			{
				add( final_mul_array[i] );
			}
			else
			{
				subtract( final_mul_array[i] );
			}
		}
	
	}
	
	//expression evaluated successfully . time to display the result.
	printf("\n\nfinal calculation 	:= %s\n\n",final);
	
	printf("length = %d\n\n",string_length(final));
	
	free(final_mul_array);	
*/
//	return 0;
//}
