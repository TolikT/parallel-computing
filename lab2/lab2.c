#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <fwBase.h>
#include <fwSignal.h>

#define A 864
#define SEED 1234

int gnome_sort(double *arr, size_t size)
{
	size_t i = 1; // counter

	while (i < size) {
		if (i == 0) {
			i = 1;
		}
		if (arr[i-1] <= arr[i]) {
			++i; // go forward
		} else {
			// swap
			double tmp = arr[i];
			arr[i] = arr[i-1];
			arr[i-1] = tmp;
			// and go back
			--i;
		}
	}

	return 0;
}

double* generate(size_t size, unsigned int min, unsigned int max)
{
	double *arr = malloc(sizeof(double) * size);
	unsigned int seed = SEED;
	int i;

	for (i = 0; i < size; i++)
	{
		arr[i] = ((double) (rand_r(&seed)%(100*(max-min)))/100) + min;
	}

	
	return arr;
}

int map(double *arr_m1, size_t size1, double *arr_m2, size_t size2)
{
	/*double *array_dest = malloc(size1 * sizeof(double));

	fwsDivC_64f(arr_m1, M_PI, array_dest, size1);
	fwsPowx_64f_A50(array_dest, 3, arr_m1, size1);

	array_dest[0] = arr_m2[0];
	fwsAdd_64f(arr_m2, (arr_m2 + 1), (array_dest + 1), size2 - 1);
	fwsTan_64f_A50(array_dest, arr_m2, size2);
	fwsCopy_64f(arr_m2, array_dest, size2);
	fwsAbs_64f(array_dest, arr_m2, size2);

	free(array_dest);*/

	return 0;
}

int merge(double *arr_m1, double *arr_m2, size_t size2)
{
	//double *array_dest = malloc(size2 * sizeof(double));

	//fwsPow_64f_A50(arr_m2, arr_m1, array_dest, size2);
	//free(arr_m2);
	//fwsCopy_64f(array_dest, arr_m2, size2);

	return 0;	
}

double reduce(double *arr, size_t size) 
{
	double res=0, min = 0;
  	int i = 0;
  
	while (arr[i] == 0) 
	{
    		i++;
	}
  	
	min = arr[i];
  
	for (i = 0; i < size; i++) 
	{
    		if ((int)(arr[i] / min) % 2 == 0)
		{
      			res += sin(arr[i]);
  		}
	}
  
	return res;
}

int main(int argc, char **argv)
{
	fprintf(stderr, "%s\n", "hui-start");
	struct timeval T1, T2;
	long time_ms, minimal_time_ms = -1;
	double *arr_m1, *arr_m2, x;
	int n, i, threads;

	
	if(argc > 1)
		n = atoi(argv[1]); /* инициализировать число N первым параметром командной строки */
	else n = 20;

	if (argc > 2)
		threads = atoi(argv[2]); /* Get number of threads */
	else threads = 2;
	fwSetNumThreads(threads);

	for (i = 0; i < 100; ++i) {
		gettimeofday(&T1, NULL); /* запомнить текущее время T1 */
		arr_m1 = generate(n, 1, A);
		arr_m2 = generate(n/2, A, 10*A);
		printf("%s\n", "hui-map");
		map(arr_m1, n, arr_m2, n/2);
		printf("%s\n", "hui");
		merge(arr_m1, arr_m2, n/2);
		gnome_sort(arr_m2, n/2);
		x = reduce(arr_m2, n/2);
		gettimeofday(&T2, NULL); /* запомнить текущее время T2 */
		time_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
		if ((minimal_time_ms == -1) || (time_ms < minimal_time_ms)) minimal_time_ms = time_ms;
		free(arr_m1);
		free(arr_m2);
	}
	
	printf("%f\n", x);
	printf("%ld\n", minimal_time_ms); /* затраченное время */

	return 0;
}
