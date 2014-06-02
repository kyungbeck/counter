#include "csapp.h"

void *thread(void *vargp);

volatile int cnt = 0;

int main(int argc, char **argv)
{
	clock_t start_point, end_point;
	int niters = atoi(argv[1]);
	pthread_t tid1, tid2;

	start_point = clock();
	Pthread_create(&tid1, NULL, thread, &niters);
	Pthread_create(&tid2, NULL, thread, &niters);
	Pthread_join(tid1, NULL);
	Pthread_join(tid2, NULL);

	/* Check result */
	if (cnt != (2 * niters))
		printf("BOOM! cnt=%d\n", cnt);
	else
		printf("OK cnt=%d\n", cnt);
	end_point = clock();

	printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));

	exit(0);
}

void *thread(void *vargp)
{
	int i, niters = *((int *)vargp);
	for (i=0;i<niters;i++) {
		__sync_fetch_and_add(&cnt, 1);
	}
	return NULL;
}
