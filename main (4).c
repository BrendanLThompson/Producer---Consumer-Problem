#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *buffer = NULL;
int iterations = 0;
int bufferSize = 0;
int maxFill = 0;
int maxEmpty = 0;
int next_in;
int next_out;
int e;
int f;

/* Declare global variables, including a buffer as a dynamic array of integers */

/***************************************************************/
void option1()
{
	/* Declare local variables */
	/* Prompt for size of the buffer and allocate memory */
	printf("Enter size of the Buffer: \n");
	scanf("%d", &bufferSize);
	printf("Enter Maximum Fill size: \n");
	scanf("%d", &maxFill);
	printf("Enter Maximum Empty Size:\n");
	scanf("%d", &maxEmpty);
	printf("Enter Number of Iterations:\n");
	scanf("%d", &iterations);

	buffer = (int *)calloc(bufferSize, sizeof(int));

	return;
}

/******NOTE: replace "variable" with an actual variable*********/
int p(int var1)
{
	/* Decrement "variable" if non-negative */
	if (var1 > 0)
	{
		var1--;
	}
	return var1;
}

int v(int var2)
{
	/* Increment "variable" if it is less than the size of the buffer */
	if (var2 < bufferSize)
	{
		var2++;
	}
	return var2;
}

/***************************************************************/
void printer()
{
	/* Declare local variables */
	printf("Buffer = ");
	for (int i = 0; i < bufferSize; i++)
	{
		printf("%d", buffer[i]);
	}
	/* Print each element in a for-loop */
	return;
}

/***************************************************************/
void producer()
{
	clock_t k1 = clock() % maxFill + 1;
	/* Declare/initilize k1 of type clock_t to hold random value between 1 and max_fill_size, using function: clock() */
	/* Declare other local variables */
	int i;
	/* For each cell of the buffer to fill from 1 to k1 */
	for (i = 1; i < k1; i++)
	{
		/* if not full, decrement e semaphore */
		if (e > 0)
		{
			e = p(e);
			/* increment buffer cell referenced by next_in */
			buffer[next_in] = 1;
			/* increment value of next_in modulo n */
			next_in = (next_in + 1) % bufferSize;
			/* increment f semaphore */
			f = v(f);
		}
	}
	/* call procedure to print contents of buffer */
	printf("\nP[%ld]: ", k1);
	printer();
	return;
}

/***************************************************************/
void consumer()
{
	/* Declare/initilize k2 of type clock_t to hold random value between 1 and max_empty_size, using function: clock() */
	clock_t k2 = clock() % maxEmpty + 1;
	/* Declare other local variables */
	int i;
	/* For each cell of the buffer to empty from 1 to k2 */
	for (i = 1; i < k2; i++)
	{
		/* if not empty, decrement f semaphore */
		if (f > 0)
		{
			f = p(f);
			/* reset buffer cell referenced by next_out */
			buffer[next_out] = 0;
			/* increment value of next_out modulo n */
			next_out = (next_out + 1) % bufferSize;
			/* increment e semaphore */
			e = v(e);
		}
	}
	/* call procedure to print contents of buffer */
	printf("\nC[%ld]: ", k2);
	printer();
	return;
}

/**********************************************/
void simulater()
{
	clock_t pc;
	f = 0;
	e = bufferSize;
	next_in = 0;
	next_out = 0;

	for (int i = 0; i < iterations; i++)
	{
		pc = clock() % 2;
		if (pc == 0)
		{
			producer();
		}
		else
		{
			consumer();
		}
	}
	return;
}


int main()
{
	int choice = 0;
	do
	{
		printf("\n\nProducer - Consumer Problem\n"
			   "1) Enter Parameters\n"
			   "2) Simulate on a shared circular buffer\n"
			   "3) Exit\n\n"
			   "Enter Selection:\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			option1();
			break;
		case 2:
			simulater();
			break;
		case 3:
			printf("\nQuiting\n");
		default:
			printf("Invalid option\n");
		}
	} while (choice != 3);
	return 1;
}
