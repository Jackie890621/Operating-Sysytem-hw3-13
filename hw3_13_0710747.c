#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>

int main(int argc, char *argv[])
{
	//判斷使用者是否只輸入一個數字
	if (argc == 1) {
                printf("You need to input a number\n");
		return 1;
        } else if (argc > 2) {
                printf("You only need to input one number\n");
		return 1;
        }

	int arg = atoi(argv[1]);
	int status;
	long long int fib[100];
	fib[0] = 0;
	fib[1] = 1;
	pid_t parent_pid, child_pid;
	
	if (arg <= 0) { //確認使用者輸入數字大於零
		printf("You need to input a number > 0\n");
		return 1;
	} else {
		//不超過30
		if (arg > 30) {
			printf("That's out of range.\n");
			return 0;
		}

		parent_pid = fork();
		if (parent_pid == 0) { //child process
			printf("Child process-start, pid = %d\n", child_pid);
			//產生費式數列並印出
			if (arg == 1) {
				printf("%lld \n", fib[0]);
			} else if (arg == 2) {
				printf("%lld %lld \n", fib[0], fib[1]);
			} else {
				printf("%lld %lld ", fib[0], fib[1]);
				for (int i = 2; i < arg; i++) {
					fib[i] = fib[i - 1] + fib[i - 2];
					printf("%lld ", fib[i]);
				}
				printf("\n");
			}

			printf("Child process-end, pid = %d\n", child_pid);
			exit(0);
		} else if (parent_pid > 0) { //parent process
			printf("Parent process-start, pid = %d\n", parent_pid);
			child_pid = wait(&status);
			printf("Parent process-end, pid = %d\n", parent_pid);
		} else {
			printf("fork error\n");
			return 1;
		}
	}
	return 0;
}
