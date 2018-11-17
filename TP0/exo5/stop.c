#include <unistd.h>
#include <stdio.h>
#include <signal.h>
int main(){
	puts("the calculate process is terminated");
	kill(getppid(),SIGINT);
}