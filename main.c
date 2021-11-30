#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#define pmutex pthread_mutex_t

static pmutex mtx = PTHREAD_MUTEX_INITIALIZER;
useconds_t tts = 1000000;

void* take_turn(void* arg){

  pthread_t my_id = pthread_self();
  
  printf("\n\tThread %x is up and running!\n", my_id);
  size_t i = 4;
  while(i--){
    usleep(1000);//
    if (!pthread_mutex_lock(&mtx)){
      printf("\n\n\tThread %x succesfully captured the mutex!\n\tWorking...\n", my_id);
    }
    printf("\tTrying to unlock mutex: ");
    if(!pthread_mutex_unlock(&mtx)){
      printf(" unlocked!\n");
    }
    else {
      printf("Something went wrong while unlocking the mutex. Exiting the thread!\n");
      pthread_exit(NULL);

    }
    printf("\tThread %x is going to sleep!\n", my_id);
    usleep(tts);
  }
  printf("---->Thread %x is exiting with no errors!\n", my_id);
  pthread_exit(NULL);
}

void main (){
 puts("HELLO"); 
  int a = 2; 
 pthread_t thr1;
 pthread_t thr2;
  pthread_mutex_lock(&mtx); 
errno = 0;
printf("Creating threads ...\n");  
if (!pthread_create(&thr1, NULL, &take_turn, NULL) && !pthread_create(&thr2, NULL, &take_turn, &a)){
  printf("Threads created!\nWaiting for them!\n");
} else {
  printf("Failed to create threads! Errno is %x\nExiting...", errno);
  
  exit(-1);
}

  pthread_mutex_unlock(&mtx);
errno = 0;
if (!pthread_join(thr1, NULL) && !pthread_join(thr2, NULL)){
  printf("threads join succeeded!\n");
} else {
  printf("threads join failed! Errno is %x\nExiting...", errno);
}
 
}
