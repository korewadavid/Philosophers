#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void*	routine(){
	printf("Hello from the thread\n");
	sleep(3);
	printf("Ending Thread\n");
	return NULL;
}

int main(int argc, char **argv){
	pthread_t p1, p2; // thread identifiers
	if (pthread_create(&p1, NULL, &routine, NULL) != 0){
		return 1; // error calling routine() function
	}
	if (pthread_create(&p2, NULL, &routine, NULL) != 0){
		return 1;
	}
	if (pthread_join(p1, NULL) != 0){
		return 1;
	}
	if (pthread_join(p2, NULL) != 0){
		return 1;
	}
	return 0;
}
