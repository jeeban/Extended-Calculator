/*####################################################################################################
#
#	Code Details :- 
#	Author :- miku<jeeban29@gmail.com>
#
####################################################################################################*/

#include<stdio.h>
#include<stdlib.h>



void initialize_memory( int, char** );
void destroy_memory( void );
void check_expression_for_error( int, char** );

int compare( char*, char* );
int string_length( char* );
int count_float(char *str);

void process_fact( void );
void process_mul( void );
void process_sign( void );
void process_addition( void );

void add_point( char *str, int point, char *target );
char* remove_point( char *str );
char* append_end(char ch, int count,char *str);
void trim_new(char *str, char *target);

void add_new( char *num1, char *num2, char *target );
void subtract_new( char *num1, char *num2, char *target );
void multiply_new( char *num1, char *num2, char *target );
void divide_new( char *num1, char *num2, char *target );
void remainder_new( char *num1, char *num2, char *target );
void factorial_new( char *num, char *target );

int argc, argc_backup;
char **argv;
char **temp_memory, **extra_memory;
char *final, *final_mul;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//testing functions

void factorial(char *str_copy);
int count_float( char *str);
char* trim(char *str);
int less( char *str1, char *str2);
void add( char *str_copy);
void multiply(char *str);
void subtract( char *str_copy);
void divide(char *str);
void remain(char *str);

///////////////////////////////////////////////////////////////////////////////////////////////////////


void divide_new( char *num1, char *num2, char *target );


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialize_memory( int main_argc, char **main_argv )
{
	int i;
	
	//temporary memory created.
	if( (temp_memory = (char**)malloc( 20 * sizeof(char*) ) ) == NULL )
	{
		fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
		exit(0);
	}
	for( i=0; i<20; i++ )
	{
		if( (temp_memory[i] = (char*)malloc( 65535 * sizeof(char) )) == NULL )
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
	}
	
	if( (extra_memory = (char**)malloc( 20 * sizeof(char*) )) == NULL  )
	{
		fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
		exit(0);
	}
	for( i=0; i<20; i++ )
	{
		if( (extra_memory[i] = (char*)malloc( 65535 * sizeof(char) ) ) == NULL )	//add 4 zero
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
	}
	
	printf("memory allocation done.\n");
	
	final = extra_memory[0];
	final_mul = extra_memory[1];
	
	sprintf( final, "0" );
	sprintf( final_mul, "1" );
	
	//prepare a copy of the input data.
	argc = main_argc;
	argc_backup = argc;
	
	if( (argv = (char**)malloc( argc * sizeof(char*) ) ) == NULL )
	{
		fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
		exit(0);
	}
	for( i=0; i<argc; i++ )
	{
		if( (argv[i] = (char*)malloc( (string_length(main_argv[i])+2) * sizeof(char) )) == NULL )
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
		sprintf( argv[i],"%s", main_argv[i]);
	}
	
	printf("Data backup done.\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_memory( void )
{
	int i;
	
	for( i=0; i<20; i++ )
	{
		free( temp_memory[i] );
	}
	free( temp_memory );
	
	for( i=0; i<20; i++ )
	{
		free( extra_memory[i] );
	}
	free( extra_memory );
	
	for( i=1; i<argc; i++ )
	{
		free( argv[i] );
	}
	free( argv );
	
	printf("memory deleted.\n");

	exit(0);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//find out the errors in the expression syntax
void check_expression_for_error(int argc, char **argv)
{
	int i, status=0, point_count =0;
	char *ptr;
	
	if(argc == 1)
	{
		printf("Input error : Please enter some expression in the commandline.\n");
		exit(0);
	}	
	
	//expression should not start or end with a sign
	if( ( compare( argv[1],"+" ) == 0 )  ||  ( compare( argv[1],"-" ) == 0 )  ||  ( compare( argv[1],"x" ) == 0 )  ||  ( compare( argv[1],"/" ) == 0 ) ||  ( compare( argv[1],"%" ) == 0 )  )
	{
		printf("Input error : A number is expected at the begining of the expression.\n");
		exit(0);
	}
	if( ( compare( argv[ argc-1 ],"+" ) == 0 )  ||  ( compare( argv[ argc-1 ],"-" ) == 0 )  ||  ( compare( argv[ argc-1 ],"x" ) == 0 )  ||  ( compare( argv[ argc-1 ],"/" ) == 0 )  ||  ( compare( argv[ argc-1 ],"%" ) == 0 ))
	{
		printf("Input error : A number is expected at the end of the expression.\n");
		exit(0);
	}
	
	
	//all even position must be a sign
	for( i=2; i<argc; i+=2 )
	{
		if( ( compare( argv[i],"+" ) != 0 )  &&  ( compare( argv[i],"-" ) != 0 ) &&  (compare( argv[i],"x" ) != 0 )  &&  ( compare( argv[i],"/" ) != 0 )  &&  ( compare( argv[i],"%" ) != 0 ))
		{
			printf("Input error : Location[%d] : %s : Any mathematical operator is expected. But found something else.\n",i,argv[i]);
			exit(0);
		}
	}
	
	//odd positions should not be sign
	for( i=1; i<argc; i+=2 )
	{
		if( ( compare( argv[i],"+" ) == 0 )  ||  ( compare( argv[i],"-" ) == 0 ) ||  ( compare( argv[i],"x" ) == 0 )  ||  ( compare( argv[i],"/" ) == 0 )  ||  ( compare( argv[i],"%" ) == 0 ))
		{
			printf("Input error : Location[%d] : %s : A number is expected. But found a mathematical operator.\n",i,argv[i]);
			exit(0);
		}
	}
	
	//the expression format is ok...
	//check the numbers for digit error

	for(i=1 ; i<argc ; i+=2)
	{
		ptr = argv[i];
		point_count =0;
		
		if( (*ptr == '^' ) || ( *ptr == '-' ) )
		{
			ptr++;
		}

		for(   ; *ptr!='\0' ; ptr++)
		{
			if( (*ptr < 48) || (*ptr > 57) )
			{
				if( *ptr == '-' )
				{
					printf("Input error : Location[%d] : %s : - sign is placed incorrectly. Remove the - sign or put two space around the - sign.\n",i,argv[i]);
					status = 1;
					break;
				}
				else if( *ptr == '^' )
				{
					printf("Input error : Location[%d] : %s : Factorial sign can't be used here. Remove the ^ sign.\n",i,argv[i]);
					status = 1;
					break;
				}	
				else if(*ptr == '.')
				{
					if( ++point_count > 1 )
					{
						printf("Input error : Location[%d] : %s : A floating number can't have two points in it. Remove any one point.\n",i,argv[i]);
						status = 1;
						break;
					}
					continue;
				}
				else
				{		
					printf("Input error : Location[%d] : %s : Invalid number. A numbers should't have any symobols other then digits.\n",i,argv[i]);
					status = 1;
					break;
				}		
			}
		}
	}
	
	if(status == 1)
	{
		exit(0);
	}
	else
	{
		printf("actual expression 	:= ");
		for( i=1; i<argc; i++ )
		{
			printf("%s ",argv[i]);
		}	
		printf("\n");
	}
	
		
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//comparision between two strings
int compare( char *str1, char *str2)
{
	char *ptr1, *ptr2;
	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\0') || (*(ptr2) != '\0');  ptr1++, ptr2++  )
	{
		if( *(ptr1) != *(ptr2) )
		{
			return 1;
		}
	}
	return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//find the length of the string
int string_length( char *str)
{
	int i;
	char *ptr;
	for( i=0, ptr=str ; *(ptr) != '\0' ; i++, ptr++){}
	
	return i;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void process_fact( void )
{

	int i;
	
	for( i=1; i<argc; i++ )
	{
		if( *(argv[i]) == '^' )
		{
			factorial_new( argv[i]+1, extra_memory[7] );
			free( argv[i] );
			if( (argv[i] = (char*)malloc( (string_length(extra_memory[7])+1) * sizeof(char) )) == NULL )
			{
				fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
				exit(0);
			}
			sprintf(argv[i],"%s",extra_memory[7]);
			
		}
	}
	
	printf("factorial analysis 	:= ");
	for( i=1; i<argc; i++ )
	{
		printf("%s ",argv[i]);
	}
	
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_mul( void )
{

	int i=2, new_argc;
	
	while( (i<argc) && ((compare(argv[i],"+") == 0) || (compare(argv[i],"-") == 0)) )
	{
		i+=2;
	}
	new_argc = i-1;
	
	while( i<argc )
	{
		sprintf( final_mul, "%s", argv[new_argc] );

		while( (i<argc) && ((compare(argv[i],"+") != 0) && (compare(argv[i],"-") != 0)) )
		{
			if( compare(argv[i],"x") == 0 )
			{
				multiply_new( final_mul, argv[i+1], final_mul );
			}
			else if( compare(argv[i],"/") == 0 )
			{
				divide_new( final_mul, argv[i+1], final_mul );
			}
			else
			{
				remainder_new( final_mul, argv[i+1], final_mul);
			}	
			i+=2;
		}
		free( argv[new_argc] );
		if( (argv[new_argc] = (char*)malloc( (string_length(final_mul)+2) * sizeof(char) )) == NULL )
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
		sprintf(argv[new_argc],"%s",final_mul);
		new_argc++;
		
		
		while( (i<argc) && ((compare(argv[i],"+") == 0) || (compare(argv[i],"-") == 0)) )
		{
			free( argv[new_argc] );
			if( (argv[new_argc] = (char*)malloc( (string_length(final_mul)+2) * sizeof(char) )) == NULL )
			{
				fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
				exit(0);
			}
			sprintf(argv[new_argc],"%s",argv[i]);
			new_argc++;
			i++;
			
			
			free( argv[new_argc] );
			if( (argv[new_argc] = (char*)malloc( (string_length(final_mul)+2) * sizeof(char) )) == NULL )
			{
				fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
				exit(0);
			}
			sprintf(argv[new_argc],"%s",argv[i]);
			new_argc++;
			i++;
		}
		new_argc--;
	}
	
	argc = new_argc+1;
	
	printf("\nmultiplication analysis := ");
	for( i=1; i<argc; i++ )
	{
		printf("%s ", argv[i]);
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_sign( void )
{
	int i;
	char **ptr;
	
	if( (ptr = (char**)malloc( argc * sizeof(char*) ) ) == NULL )
	{
		fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
		exit(0);
	}
	
	if( (ptr[1] = (char*)malloc( (string_length(argv[1])+2) * sizeof(char) )) == NULL )
	{
		fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
		exit(0);
	}
	sprintf(ptr[1],"%s",argv[1]);
	
	for( i=3; i<argc; i+=2 )
	{
		if( (ptr[i] = (char*)malloc( (string_length(argv[i])+2) * sizeof(char) )) == NULL )
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
		if( (ptr[i-1] = (char*)malloc( 3 * sizeof(char) )) == NULL )
		{
			fprintf( stderr, "Memory allocation Failed. Exiting...\n" );
			exit(0);
		}
		
		if( *(argv[i]) == '-' )
		{
			sprintf(ptr[i],"%s",argv[i]+1);
			if( compare( argv[i-1] , "+" ) == 0 )
			{
				sprintf(ptr[i-1],"-");
			}
			else
			{
				sprintf(ptr[i-1],"+");
			}
		}
		else
		{
			sprintf(ptr[i],"%s",argv[i]);
			sprintf(ptr[i-1],"%s",argv[i-1]);
		}
	}
	
	
	for( i=0; i<argc_backup; i++ )
	{
		free( argv[i] );
	}
	argv = ptr;
	ptr = NULL;
	
	printf("\nsign analysis 		:= ");
	for( i=1; i<argc; i++ )
	{
		printf("%s ",argv[i]);
	}
	
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void process_addition( void )
{
	int i;
	
	final = argv[1];
	for( i=2; i<argc; i+=2 )
	{
		if( compare( argv[i], "+" ) == 0 )
		{
			add_new( final, argv[i+1], final );
		}
		else
		{
			subtract_new( final, argv[i+1], final );
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_point( char *str, int point, char *target )
{
	int i;

	point = string_length(str) - point;
	
	if( point < 0 )
	{
		point = -point;
		
		*target = '0';
		target++;
		*target = '.';
		target++;
		
		for( i=0; i<point; i++ )
		{
			*target = '0';
			target++;
		}
		for( ; *str != '\0'; str++ )
		{
			*target = *str;
			target++;
		}
	}
	else
	{
		for( i=0; i<point; i++ )
		{
			*target = *str;
			target++;
			str++;
		}
		*target = '.';
		target++;
		
		for( ; *str != '\0'; str++ )
		{
			*target = *str;
			target++;
		}
	}
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* remove_point( char *str )
{
	char *target, *temp=str;
	while( (*str!='.') && (*str!='\0') )
	{
		str++;
	}
	if( *str == '.' )
	{
		target = str;
		str++;
		while( *str != '\0' )
		{
			*target = *str;
			target++;
			str++;
		}
		*target = '\0';
	}
	return temp;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* append_end(char ch, int count,char *str)
{
	char *temp = str;
	int i;
	
	for( ; *str!='\0'; str++ );
	for( i=0; i<count; i++ )
	{
		*str = ch;
		str++;
	}
	*str = '\0';
	
	return temp;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void trim_new(char *str, char *target)
{
	for( ; *str=='0'; str++ );
	for( ; *str!='\0'; str++ )
	{
		*target = *str;
		target++;
	}
	*target='\0';
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_float(char *str)
{
	int count=0;
	
	for( ; (*str!='.') && (*str!='\0'); str++ );
	if( *str == '.' )
	{
		for( str++; *str!='\0'; str++, count++ );
		return count;
	}
	else
	{
		return -1;
	}
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_new( char *num1, char *num2, char *target )
{
	
	int num1_length, num2_length, big_num_size, small_num_size, i, j ,m , n, num1_float_size, num2_float_size, float_size;
	unsigned short int sum=0, carry=0;
	char *big_number, *small_number, *stack, *ptr1, *ptr2, *stack_ptr;
	
//	printf("     add() :=\t final = %s\t\tstr = %s\n",num1,num2);

	trim_new( num2, num2 );
	
	if( *(num1) == '-' )
	{
		subtract_new( num2, num1+1, target );
	}
	else
	{
		//process the floating point if necessery
		num1_float_size = count_float( num1 );
		num2_float_size = count_float( num2 );
		
		if( (num1_float_size != -1)  ||  (num2_float_size != -1) )
		{
			num1 = remove_point( num1);
			num2 = remove_point( num2);
		
			if( num1_float_size > num2_float_size )
			{
				float_size = num1_float_size;
				if( num2_float_size == -1 )
				{
					num2_float_size = 0;
				}
				num2 = append_end( '0', num1_float_size - num2_float_size, num2 );
			}
			else
			{
				float_size = num2_float_size;
				if( num1_float_size == -1 )
				{
					num1_float_size = 0;
				}
				num1 = append_end( '0', num2_float_size - num1_float_size, num1 );
			}
		}
		else
		{
			float_size = 0;
		}			
				
		
		//find the bignumber and smallnumber details.
		num1_length = string_length(num1);
		num2_length = string_length(num2);
		if( ((num1_length >= num2_length) ? 0 : 1) == 0)
		{
			big_number = num1;
			small_number = num2;
			big_num_size = num1_length;
			small_num_size = num2_length;
		}
		else
		{
			big_number = num2;
			small_number = num1;
			big_num_size = num2_length;
			small_num_size = num1_length;
		}
		
		//create a buffer to store the sum with length = bignumsize + 1
		stack = extra_memory[3];
		*(stack + big_num_size + 1) = '\0';
		stack_ptr = (stack + big_num_size);
		
		//begin the calculation
		for( i = (big_num_size - 1) , j = (small_num_size -1), ptr1=(big_number + i), ptr2=(small_number + j) ; j >= 0 ; i-- , j--, ptr1--, ptr2-- )
		{
			m = *(ptr1) - 48;	//convert char to int
			n = *(ptr2) - 48;
			sum = m + n + carry;
			if( sum > 9 )
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			
			*(stack_ptr--) = (char)(sum + 48);
		}
		
		for( ; i >= 0 ; i--, ptr1-- )
		{
			m = *(ptr1) - 48;	//convert char to int
			sum = m + carry;
			if( sum > 9 )
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			
			*(stack_ptr--) = (char)(sum + 48);
		}
	
		
		if( carry == 1)
		{
			*( stack_ptr ) = '1';
		}
		else
		{
			stack = stack + 1;
		}
		
		if( float_size != 0 )
		{
			add_point( stack, float_size, target);
		}
		else
		{
			sprintf(target, "%s",stack);
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void subtract_new( char *num1, char *num2, char *target )
{
	
	int num1_length, num2_length, big_num_length, small_num_length, i, j, m, n, num1_float_size, num2_float_size, float_size;
	unsigned short int sub;
	char *big_number, *small_number, *stack, *ptr1, *ptr2, *stack_ptr;
	char sign = '+';
	
//	printf("subtract() :=\t num1 = %s\t\tnum2 = %s\n",num1,num2);
	
//	trim_new( num1, num1 );
	trim_new( num2, num2 );
		
	if( *(num1) == '-' )
	{
		add_new( num1+1, num2, target );
		sprintf(temp_memory[0], "%s",target);
		sprintf(target,"-%s",temp_memory[0]);
	}
	else	
	{
		//process the floating point if necessery
		num1_float_size = count_float( num1 );
		num2_float_size = count_float( num2 );
		
		if( (num1_float_size != -1)  ||  (num2_float_size != -1) )
		{
			num1 = remove_point( num1);
			num2 = remove_point( num2);
		
			if( num1_float_size > num2_float_size )
			{
				float_size = num1_float_size;
				if( num2_float_size == -1 )
				{
					num2_float_size = 0;
				}
				num2 = append_end( '0', num1_float_size - num2_float_size, num2 );
			}
			else
			{
				float_size = num2_float_size;
				if( num1_float_size == -1 )
				{
					num1_float_size = 0;
				}
				num1 = append_end( '0', num2_float_size - num1_float_size, num1 );
			}
		}
		else
		{
			float_size = 0;
		}
		
		
		//find the big and small number
		num1_length = string_length( num1 );
		num2_length = string_length( num2 );
		
		if( num1_length > num2_length )
		{
			big_number = num1;
			small_number = num2;
			big_num_length = num1_length;
			small_num_length = num2_length;
		}
		else if( num1_length < num2_length )
		{
			big_number = num2;
			small_number = num1;
			big_num_length = num2_length;
			small_num_length = num1_length;
			sign = '-';
		}
		else
		{
			big_number = num1;
			small_number = num2;
			big_num_length = num1_length;
			small_num_length = num2_length;
			
			for(  ptr1=num1, ptr2=num2;  *(ptr1) != '\0';  ptr1++, ptr2++ )
			{
				if( *(ptr1) > *(ptr2) )
				{
					big_number = num1;
					small_number = num2;
					break;
				}
				else if( *(ptr1) < *(ptr2) )
				{
					big_number = num2;
					small_number = num1;
					sign = '-';
					break;
				}
				else
				{
					continue;
				}
			}
		}
		
		
		//create a space to store the subtraction
		stack = extra_memory[2];
		*(stack + big_num_length) = '\0';
		stack_ptr = (stack + big_num_length - 1);
		
		//analyze the digits
		for( i=big_num_length-1, j=small_num_length-1, ptr1=(big_number + i), ptr2=(small_number + j);   j>=0;   i--,j--, ptr1--, ptr2-- )
		{
			m = *(ptr1) - 48;
			n = *(ptr2) - 48;
			
			if( m < n )
			{
				if( m < 0 )
				{
					m =9;
				}
				else
				{
					m += 10;
				}
				
				if( *(ptr1 - 1) == '0' )
				{
					*(ptr1 -1) = '#';
				}
				else
				{
					*(ptr1 - 1) = *(ptr1 - 1) - 1;
				}
			}
			sub = m - n;
			*(stack_ptr--) = sub + 48;
		}
		
		for(	; i>=0; i--,ptr1-- )
		{
			m = *(ptr1) - 48;
			if( m < 0 )
			{
				m = 9;
				if( *(ptr1 - 1) == '0' )
				{
					*(ptr1 - 1) = '#';
				}
				else
				{
					*(ptr1 - 1) = *(ptr1 - 1) - 1;
				}
			}
			*(stack_ptr--) = m + 48;
		}	
		trim_new( stack, stack );
		if( compare( stack,"" ) == 0 )
		{
			sprintf(stack,"0");
		}
	
		
		if( float_size != 0 )
		{
			add_point( stack, float_size, temp_memory[0]);
		}
		else
		{
			sprintf(temp_memory[0], "%s",stack);
		}
		
		
		if( sign == '+')
		{
			sprintf(target,"%s",temp_memory[0]);
		}
		else
		{
			sprintf(target,"-%s",temp_memory[0]);
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void multiply_new( char *num1, char *num2, char *target )
{
	
	int num1_length, num2_length, i, j, m ,n, mul_pointer, num1_float_size, num2_float_size, float_size;
	unsigned short int multiple_bit, carry, temp_num;
	char *temp, *temp_ptr, *ptr1, *ptr2;
	char sign1,sign2,sign;

//	printf("multiply() :=\t num1 = %s\t\tnum2 = %s\n",num1,num2);
	
	//sign prediction
	if( *(num1) == '-' )
	{
		num1++;
		sign1 = '-';
	}
	else
	{
		sign1 = '+';
	}
	
	if( *(num2) == '-' )
	{
		num2++;
		sign2 = '-';
	}
	else
	{
		sign2 = '+';
	}
	
	if( ( sign1 == sign2 )	&& ( (sign1 == '+') || (sign1 == '-') ) )
	{
		sign = '+';
	}
	else
	{
		sign = '-';
	}
	
	num1_float_size = count_float( num1 );
	num2_float_size = count_float( num2 );
		
	if( (num1_float_size != -1)  ||  (num2_float_size != -1) )
	{
		num1 = remove_point( num1);
		num2 = remove_point( num2);
			
		if( num2_float_size == -1 )
		{
			num2_float_size = 0;
		}
		if( num1_float_size == -1 )
		{
			num1_float_size = 0;
		}
		float_size = num1_float_size + num2_float_size;
	}
	else
	{
		float_size = 0;
	}
	
	trim_new( num1, num1 );
	trim_new( num2, num2 );
	
	num1_length = string_length( num1 );
	num2_length = string_length( num2 );
	
	sprintf( temp_memory[1],"0" );
	
	carry = 0;
	for( i=num2_length-1, ptr1=(num2 + i), mul_pointer=0; i>=0; i--, mul_pointer++, ptr1-- )
	{
		m = *(ptr1) - 48;
		
		temp = extra_memory[4];
		*(temp + num1_length + 1) = '\0';
		temp_ptr = (temp + num1_length);
		
		
		for( j=num1_length-1, ptr2=(num1 + j) ; j>=0; j--, ptr2-- )
		{
			n = *(ptr2) - 48;
			temp_num = (m * n) + carry;
			
			if( temp_num > 9 )
			{
				multiple_bit = temp_num % 10;
				carry = temp_num / 10;
			}
			else
			{
				multiple_bit = temp_num;
				carry = 0;
			}
		
			*(temp_ptr--) = (multiple_bit + 48);
			
			if( (j==0) && (carry != 0) )
			{
				*(temp_ptr--) = (carry + 48);
				carry = 0;
			}	
	
		}


		if( temp_ptr == temp )
		{
			temp = temp + 1;
		}
		temp = append_end( '0', mul_pointer, temp );
		
		add_new( temp_memory[1], temp, temp_memory[1] );
	}
	
	if( float_size > 0 )
	{
		add_point( temp_memory[1], float_size, extra_memory[3]);
		sprintf(temp_memory[1], "%s",extra_memory[3]);
	}


	if( sign == '+')
	{
		sprintf(target,"%s",temp_memory[1]);
	}
	else
	{
		sprintf(target,"-%s",temp_memory[1]);
	}

}		



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void divide_new( char *num1, char *num2, char *target )
{

	char *dividend, *temp, *ans, *value_just_less_than_temp, *below_temp_history, *ans_pointer;
	int num2_length, i, float_counter, num1_float_size, num2_float_size, answer_zero=0, bit;
	char sign1, sign2, sign;
	
	
//	printf("  divide() :=\t final_mul = %s\t\tstr = %s\n",final_mul,str);
	
	trim_new( num2, num2 );
	if( compare( num2, "") == 0 )	//num2 is still zero. but due to trim it is set null.
	{
		printf("\nerror : cannot divide by zero\n");
		exit(0);
	}
	else if( compare(num1,"0")== 0 )
	{
		sprintf( target,"0" );
		goto end;
	}
	else
	{
	
		//sign prediction
		if( *(num1 + 0) == '-' )
		{
			num1++;
			sign1 = '-';
		}
		else
		{
			sign1 = '+';
		}
		
		
		if( *(num2 + 0) == '-' )
		{
			num2++;
			sign2 = '-';
		}
		else
		{
			sign2 = '+';
		}
		
		
		if( ( sign1 == sign2 )	&& ( (sign1 == '+') || (sign1 == '-') ) )
		{
			sign = '+';
		}
		else
		{
			sign = '-';
		}

		trim_new( num1, num1 );
		trim_new( num2, num2 );
		
		num1_float_size = count_float( num1 );
		num2_float_size = count_float( num2 );
		
		if( (num1_float_size != -1)  ||  (num2_float_size != -1) )
		{
			num1 = remove_point( num1);
			num2 = remove_point( num2);
			
			if( num2_float_size == -1 )
			{
				num2_float_size = 0;
			}
	
			if( num1_float_size == -1 )
			{
				num1_float_size = 0;
			}
			
			if( num1_float_size > num2_float_size )
			{
				num2 = append_end( '0', num1_float_size - num2_float_size , num2);
			}
			else if( num1_float_size < num2_float_size )
			{
				num1 = append_end( '0', num2_float_size - num1_float_size , num1);
			}
		}
		
		
		
		if( compare(num2,"0") == 0 )
		{
			printf("\nException during division : cannot divide by zero\n");
			exit(0);
		}
		else if( compare(num1,"0")== 0 )
		{
			answer_zero = 1;
			goto end;
		}
		else		
		{
			ans = extra_memory[5];
			ans_pointer = ans;
			temp = temp_memory[2];
			
			dividend = num1;
			num2_length = string_length( num2 );
			
			for( i=0; i<num2_length; i++ )
			{
				*(temp + i) = *dividend;
				dividend++;
			}
			*(temp + i) = '\0';
			
			if( less( temp, num2) == 1 )
			{
				temp = append_end( *dividend, 1, temp);
				dividend++;
			}
			
			printf("temp = %s\n", temp);	//debug
			
	//change from here. final mul shud be changed
			
			value_just_less_than_temp = temp_memory[3];
			below_temp_history = temp_memory[4];
			sprintf( value_just_less_than_temp, "0" );
			sprintf( below_temp_history, "0" );
			bit=-1;
			//while( (status = less( value_just_less_than_temp, temp )) && ( (status == 1) || (status == 0) ) ) // while( value_just_less_than_temp <= temp )
			while( less( value_just_less_than_temp, temp  )!= 2 ) 
			{
				bit++;
				sprintf(below_temp_history,"%s", value_just_less_than_temp );
				add_new( value_just_less_than_temp, num2, value_just_less_than_temp );
			}
			printf("history value just less than temp = %s\n", below_temp_history);
			printf("bit recieved = %d\n", bit );
			
			*ans_pointer = (bit+48);
			ans_pointer++;
			
			subtract_new( temp, below_temp_history, temp );
		//	trim_new( temp, temp );
			printf("diff = %s\n", temp);
			
			
			while( *dividend != '\0' )
			{
				temp = append_end( *dividend, 1, temp);
				printf("\nnew digit added = %c\ntemp = %s\n", *dividend, temp );
				dividend++;
				
				sprintf( value_just_less_than_temp, "0" );
				sprintf( below_temp_history, "0" );
				bit=-1;
				//while( (status = less( value_just_less_than_temp, temp )) && (status == 1) || (status == 0) ) // while( value_just_less_than_temp <= temp )
				while( less( value_just_less_than_temp, temp  )!= 2 ) 
				{
					bit++;
					sprintf(below_temp_history,"%s", value_just_less_than_temp );
					add_new( value_just_less_than_temp, num2, value_just_less_than_temp );
				}
				printf("history value just less than temp = %s\n", below_temp_history);
				printf("bit recieved = %d\n", bit );
				
				*ans_pointer = (bit+48);
				ans_pointer++;
				
				subtract_new( temp, below_temp_history, temp );
				trim_new( temp, temp );
				printf("diff = %s\n", temp);
			}
				
			*ans_pointer = '\0';

			printf("division answer = %s\n\n\n", ans );

		
			//calculate the float part if remainder is not equal to zero
			if( compare( temp , "0") != 0 )
			{
				*ans_pointer++ = '.';
				
				float_counter =0;	
				while(  (float_counter < 30) && ( compare( temp, "0") != 0) )
				{
					temp = append_end( '0', 1, temp);

					printf("\ntemp = %s\n", temp );
				
					sprintf( value_just_less_than_temp, "0" );
					sprintf( below_temp_history, "0" );
					bit=-1;
					//while( (status = less( value_just_less_than_temp, temp )) && (status == 1) || (status == 0) ) // while( value_just_less_than_temp <= temp )
					while( less( value_just_less_than_temp, temp  )!= 2 ) 
					{
						bit++;
						sprintf(below_temp_history,"%s", value_just_less_than_temp );
						add_new( value_just_less_than_temp, num2, value_just_less_than_temp );
					}
					printf("history value just less than temp = %s\n", below_temp_history);
					printf("bit recieved = %d\n", bit );
					
					*ans_pointer = (bit+48);
					ans_pointer++;
					
					subtract_new( temp, below_temp_history, temp );
			//		trim_new( temp, temp );
					printf("diff = %s\n", temp);
						
					float_counter++;
				}	
			}
			*ans_pointer = '\0';
		}			
	}
	
	printf("division answer = %s\n", ans );
	
	
	if( sign == '+')
	{
		sprintf( target, "%s", ans );
	}
	else
	{
		sprintf( target, "-%s", ans );
	}
end:
	if( answer_zero == 1 )
	{
		sprintf( target, "0" );
	}
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void remainder_new( char *num1, char *num2, char *target )
{

	char *dividend, *temp, *ans, *value_just_less_than_temp, *below_temp_history, *ans_pointer;
	int num2_length, i, float_counter, num1_float_size, num2_float_size, answer_zero=0, bit;
	char sign1, sign2, sign;
	
	
//	printf("  divide() :=\t final_mul = %s\t\tstr = %s\n",final_mul,str);
	
	trim_new( num2, num2 );
	if( compare( num2, "") == 0 )	//num2 is still zero. but due to trim it is set null.
	{
		printf("\nerror : cannot divide by zero\n");
		exit(0);
	}
	else if( compare(num1,"0")== 0 )
	{
		sprintf( target,"0" );
		goto end;
	}
	else
	{
	
		//sign prediction
		if( *(num1 + 0) == '-' )
		{
			num1++;
			sign1 = '-';
		}
		else
		{
			sign1 = '+';
		}
		
		
		if( *(num2 + 0) == '-' )
		{
			num2++;
			sign2 = '-';
		}
		else
		{
			sign2 = '+';
		}
		
		
		if( ( sign1 == sign2 )	&& ( (sign1 == '+') || (sign1 == '-') ) )
		{
			sign = '+';
		}
		else
		{
			sign = '-';
		}

		trim_new( num1, num1 );
		trim_new( num2, num2 );
		
		num1_float_size = count_float( num1 );
		num2_float_size = count_float( num2 );
		
		if( (num1_float_size != -1)  ||  (num2_float_size != -1) )
		{
			num1 = remove_point( num1);
			num2 = remove_point( num2);
			
			if( num2_float_size == -1 )
			{
				num2_float_size = 0;
			}
	
			if( num1_float_size == -1 )
			{
				num1_float_size = 0;
			}
			
			if( num1_float_size > num2_float_size )
			{
				num2 = append_end( '0', num1_float_size - num2_float_size , num2);
			}
			else if( num1_float_size < num2_float_size )
			{
				num1 = append_end( '0', num2_float_size - num1_float_size , num1);
			}
		}
		
		
		
		if( compare(num2,"0") == 0 )
		{
			printf("\nException during division : cannot divide by zero\n");
			exit(0);
		}
		else if( compare(num1,"0")== 0 )
		{
			answer_zero = 1;
			goto end;
		}
		else		
		{
			ans = extra_memory[5];
			ans_pointer = ans;
			temp = temp_memory[2];
			
			dividend = num1;
			num2_length = string_length( num2 );
			
			for( i=0; i<num2_length; i++ )
			{
				*(temp + i) = *dividend;
				dividend++;
			}
			*(temp + i) = '\0';
			
			if( less( temp, num2) == 1 )
			{
				temp = append_end( *dividend, 1, temp);
				dividend++;
			}
			
			printf("temp = %s\n", temp);	//debug
			
	//change from here. final mul shud be changed
			
			value_just_less_than_temp = temp_memory[3];
			below_temp_history = temp_memory[4];
			sprintf( value_just_less_than_temp, "0" );
			sprintf( below_temp_history, "0" );
			bit=-1;
			//while( (status = less( value_just_less_than_temp, temp )) && ( (status == 1) || (status == 0) ) ) // while( value_just_less_than_temp <= temp )
			while( less( value_just_less_than_temp, temp  )!= 2 ) 
			{
				bit++;
				sprintf(below_temp_history,"%s", value_just_less_than_temp );
				add_new( value_just_less_than_temp, num2, value_just_less_than_temp );
			}
			printf("history value just less than temp = %s\n", below_temp_history);
			printf("bit recieved = %d\n", bit );
			
			*ans_pointer = (bit+48);
			ans_pointer++;
			
			subtract_new( temp, below_temp_history, temp );
		//	trim_new( temp, temp );
			printf("diff = %s\n", temp);
			
			
			while( *dividend != '\0' )
			{
				temp = append_end( *dividend, 1, temp);
				printf("\nnew digit added = %c\ntemp = %s\n", *dividend, temp );
				dividend++;
				
				sprintf( value_just_less_than_temp, "0" );
				sprintf( below_temp_history, "0" );
				bit=-1;
				//while( (status = less( value_just_less_than_temp, temp )) && (status == 1) || (status == 0) ) // while( value_just_less_than_temp <= temp )
				while( less( value_just_less_than_temp, temp  )!= 2 ) 
				{
					bit++;
					sprintf(below_temp_history,"%s", value_just_less_than_temp );
					add_new( value_just_less_than_temp, num2, value_just_less_than_temp );
				}
				printf("history value just less than temp = %s\n", below_temp_history);
				printf("bit recieved = %d\n", bit );
				
				*ans_pointer = (bit+48);
				ans_pointer++;
				
				subtract_new( temp, below_temp_history, temp );
				trim_new( temp, temp );
				printf("diff = %s\n", temp);
			}
				
			*ans_pointer = '\0';

			printf("division answer = %s\n\n\n", ans );

		}			
	}
	
	printf("division answer = %s\n", ans );
	
	
	if( sign == '+')
	{
		sprintf( target, "%s", ans );
	}
	else
	{
		sprintf( target, "-%s", ans );
	}
end:
	if( answer_zero == 1 )
	{
		sprintf( target, "0" );
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void factorial_new(char *num, char *target)
{
	char *fact, *next_number, *char_value_one, *char_value_hundred;
	
	if( count_float( num ) > -1 )
	{
		printf("error : cannot find the factorial of floating point numbers.\n\n");
		exit(0);
	}
	
	if( *num == '-' )
	{
		printf("\nerror : negetive numbers does not have any factorial.\n\n");
		exit(0);
	}	

	next_number = extra_memory[6];
	fact = temp_memory[5];
	char_value_one = temp_memory[6];
	char_value_hundred = temp_memory[7];
	
	sprintf( char_value_one,"1" );
	sprintf( char_value_hundred,"100" );
/*	
	if( less( num, char_value_hundred ) == 2 )
	{
		printf("\nerror : factorial range exceeds...\n\n");
		exit(0);
	}
*/	
	sprintf( fact,"1" );
	sprintf( next_number, "2" );
	
	while(  less( next_number, num ) != 2 )
	{
		multiply_new( fact, next_number, fact );		
		add_new( next_number, char_value_one, next_number );
	}
	
	sprintf( target, "%s", fact );
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int less( char *str1, char *str2)
{
	int str1_length, str2_length, i;
	char *ptr1, *ptr2;
	
	trim_new( str1, str1 );
	trim_new( str2, str2 );
	
	str1_length = string_length( str1 );
	str2_length = string_length( str2 );
	
	if( str1_length > str2_length )
	{
		return 2;
	}
	else if( str1_length < str2_length )
	{
		return 1;
	}
	else
	{
		for( i=0, ptr1=str1, ptr2=str2; i<str1_length; i++, ptr1++, ptr2++  )
		{
			if( *(ptr1) > *(ptr2) )
			{
				return 2;
			}
			else if( *(ptr1) < *(ptr2) )
			{
				return 1;
			}
			else
			{
				continue;
			}
		}
	}
	return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
