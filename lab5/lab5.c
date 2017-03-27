#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define A 864

#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_procs()
{
	return 1;
}

int omp_get_thread_num()
{
	return 1;
}

void omp_set_num_threads(int thrds)
{
	return;
}

double omp_get_wtime()
{
	struct timeval T;
	double time_ms;

	gettimeofday(&T, NULL);
	time_ms = ((double) T.tv_sec) + ((double)T.tv_usec) / 1000000;
	return (double)time_ms;
}
#endif

static unsigned int seed;

int gnome_sort(double *arr, unsigned int a, unsigned int b)
{
	unsigned int i = a + 1; // counter

	while (i < b) {
		if (i == a) {
			i = a + 1;
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
	unsigned int i;
	
#if defined(CHUNK) && defined(SCHEDULE)
#pragma omp parallel for default(none) shared(size, arr, min, max) private(i, seed) schedule(SCHEDULE, CHUNK)
#else
#pragma omp parallel for default(none) shared(size, arr, min, max) private(i, seed)
#endif
	for (i = 0; i < size; i++)
	{
		seed = i * i * i;
		arr[i] = ((double) (rand_r(&seed)%(100*(max-min)))/100) + min;
	}

	return arr;
}

int map(double *arr_m1, size_t size1, double *arr_m2, size_t size2)
{
	int i;
#if defined(CHUNK) && defined(SCHEDULE)
#pragma omp parallel for default(none) shared(size1, arr_m1) private(i) schedule(SCHEDULE, CHUNK)
#else
#pragma omp parallel for default(none) shared(size1, arr_m1) private(i)
#endif
	for (i = 0; i < size1; i++)
	{
		arr_m1[i] = pow((arr_m1[i] / M_PI), 3);
	}
	
// not parralleled as here is dependensies between arr_m2[] items 
	for (i = size2 - 1; i > 0; i--)
	{
		arr_m2[i] = abs(tan(arr_m2[i] + arr_m2[i-1])); 
	}
	arr_m2[0] = abs(tan(arr_m2[0]));
	
	return 0;
}

int merge(double *arr_m1, double *arr_m2, size_t size2)
{
	int i;
#if defined(CHUNK) && defined(SCHEDULE)
#pragma omp parallel for default(none) shared(arr_m1, arr_m2, size2) private(i) schedule(SCHEDULE, CHUNK)
#else
#pragma omp parallel for default(none) shared(arr_m1, arr_m2, size2) private(i)
#endif
	for (i = 0; i < size2; i++)
	{
		arr_m2[i] = pow(arr_m1[i], arr_m2[i]); 
	}

	return 0;	
}

/* New array should be initialized */
void merge_arrays(double *array_old, double *array_new, unsigned int n, int num, int chunk) {
	unsigned int i, m;
	unsigned int *arr_i = calloc(num, (sizeof(unsigned int)));
	unsigned int min;

	for (i = 0; i < n; i++) {
		min = 0;
		for (m = 0; m < num; m++) {
			if (arr_i[m] < chunk) {
				array_new[i] = array_old[m*chunk + arr_i[m]];
				min = m;
				break;
			}
		}
		for (m = 0; m < num; m++) {
			if((m*chunk + arr_i[m] < n) && (arr_i[m] < chunk) && array_old[m*chunk + arr_i[m]] < array_new[i]) {
				array_new[i] = array_old[m*chunk + arr_i[m]];
				min = m;
			}
		}
		arr_i[min]++;
	}
}

void sort(double **array, unsigned int n)
{
	int num, a, b;
	int num_procs = omp_get_num_procs();
	int curr_chunk = n % num_procs ? n / num_procs + 1 : n / num_procs;
	unsigned int i;
	double *array_new = malloc(sizeof(double) * n);

#pragma omp parallel for default(none) shared(array, n, curr_chunk, num_procs) private(i, num, a, b)
	for (i = 0; i < num_procs; i++) {
		num = omp_get_thread_num();
		a = num * curr_chunk;
		b = num * curr_chunk  + curr_chunk - 1;
		gnome_sort(*array, a < n - 1 ? a : n - 1, b < n - 1 ? b : n - 1);
	}

	merge_arrays(*array, array_new, n, num_procs, curr_chunk);
	free(*array);
	*array = array_new;
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
#if defined(CHUNK) && defined(SCHEDULE)
#pragma omp parallel for default(none) shared(arr, size, min) private(i) reduction(+: res) schedule(SCHEDULE, CHUNK)
#else
#pragma omp parallel for default(none) shared(arr, size, min) private(i) reduction(+: res)
#endif
	for (i = 0; i < size; i++) 
	{
    		if ((int)(arr[i] / min) % 2 == 0)
		{
      			res += sin(arr[i]);
  		}
	}
  
	return res;
}

int main(int argc, char *argv[])
{
	double dtime_ms, dminimal_time_ms = -1.0, gen_time = -1.0, map_time = -1.0, mer_time = -1.0, sor_time = -1.0;
	double *arr_m1, *arr_m2, x, start_time, end_time;
	unsigned int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
	char cpu[1024];
	double load[5];
	unsigned long long old[5];
	unsigned long long old_idle[5];
	unsigned long long new;
	unsigned long long new_idle;
	int n, i, j, thrds;
	char flag = 1;
	char filename[1024];
	FILE *cpu_file;
	FILE *stat_file;

	if(argc > 1)
		n = atoi(argv[1]); /* инициализировать число N первым параметром командной строки */
	else n = 20;

	sprintf(filename, "cpu_file_%d.log", n);

	if (argc > 2)
		thrds = atoi(argv[2]); /* инициализировать число thrds 2nd параметром командной строки */
	else thrds = 2;

	omp_set_num_threads(thrds + 1);
	cpu_file = fopen(filename, "w");
	
#pragma omp parallel shared(i)
#pragma omp sections
	{
#pragma omp section
		{
			for (i = 0; i < 10; ++i) {

				start_time = omp_get_wtime();
				arr_m1 = generate(n, 1, A);
				arr_m2 = generate(n/2, A, 10*A);
				end_time = omp_get_wtime();
				dtime_ms = (end_time - start_time) * 1000;
				if ((gen_time == -1.0) || (dtime_ms < gen_time)) gen_time = dtime_ms;
				
				start_time = omp_get_wtime();
				map(arr_m1, n, arr_m2, n/2);
				end_time = omp_get_wtime();
				dtime_ms = (end_time - start_time) * 1000;
				if ((map_time == -1.0) || (dtime_ms < map_time)) map_time = dtime_ms;
				
				start_time = omp_get_wtime();
				merge(arr_m1, arr_m2, n/2);
				end_time = omp_get_wtime();
				dtime_ms = (end_time - start_time) * 1000;
				if ((mer_time == -1.0) || (dtime_ms < mer_time)) mer_time = dtime_ms;
				
				start_time = omp_get_wtime();
				sort(&arr_m2, n/2);
				end_time = omp_get_wtime();
				dtime_ms = (end_time - start_time) * 1000;
				if ((sor_time == -1.0) || (dtime_ms < sor_time)) sor_time = dtime_ms;
				x = reduce(arr_m2, n/2);

				dminimal_time_ms = gen_time + map_time + mer_time + sor_time;
				free(arr_m1);
				free(arr_m2);
			}
			flag = 0;
		}

#pragma omp section
 		{
			stat_file = fopen("/proc/stat", "r");
			for (j = 0; j < 5; j++) {
				fscanf(stat_file, "%s %u %u %u %u %u %u %u %u %u %u\n", cpu, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10); 
				old[j] = c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10;
				old_idle[j] = c4;
			}
			fclose(stat_file);
  			usleep(100);

  			while(flag) {
				stat_file = fopen("/proc/stat", "r");
				for (j = 0; j < 5; j++) {
					fscanf(stat_file, "%s %u %u %u %u %u %u %u %u %u %u\n", cpu, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10); 
					new = c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 - old[j];
					new_idle = c4 - old_idle[j];
					old_idle[j] = c4;
					old[j] = new + old[j];
					load[j] = ((double) new - (double) new_idle) / (double) new;
					fprintf(cpu_file, "%f,", load[j]);
				}
				fprintf(cpu_file, "\n");

				fclose(stat_file);
  				usleep(100000);
  			}

  			printf("\n");
 		}
	}

	
	printf("%lf\n", gen_time); /* затраченное время */
	printf("%lf\n", map_time); /* затраченное время */
	printf("%lf\n", mer_time); /* затраченное время */
	printf("%lf\n", sor_time); /* затраченное время */
	printf("%lf\n", dminimal_time_ms); /* затраченное время */
	printf("%f\n", x);	

	return 0;
}
