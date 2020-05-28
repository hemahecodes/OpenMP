#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/time.h> 

int num_threads = 8;
unsigned long long int num_steps = 100000;

static double get_second (void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

void main (int argc, char* argv[])
{
   	unsigned long long int i; 
   	double x, pi, step, sum = 0.0;
   	char *endptr;
	double start,stop;
	
  	if (argc == 3 ){
        	num_steps = strtol(argv[1],&endptr,10);
        	num_threads = atoi(argv[2]);
  	}

  	start = get_second(); 
  	step = 1.0/(double) num_steps;
  	omp_set_num_threads(num_threads);
  	#pragma omp parallel
	{ 
		#pragma omp for reduction(+:sum) 
        	for (i=0; i < num_steps; i++){
        		x=(i+0.5)*step;
        		sum = sum + 4.0/(1.0+x*x);
		}
      	}
  	pi+=step*sum;
  	stop = get_second();
  
  	printf("# Pi: \t\t %16.14f\n", pi);       
  	printf("# Threads:\t %d \n", num_threads);
  	printf("# Iterations:\t %ld \n", num_steps);
  	printf("# Time(s):\t %f \n", stop-start);

  	return;
}





 
 
