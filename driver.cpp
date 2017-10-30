#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/*
char* argcat(char* command, char*argument)
{
	command =(char*) realloc(command, strlen(command) + 1 + strlen(argument));
	strcat(command, " ");
	strcat(command, argument);
	return command;
}*/

//int main(int argc, char **argv)
int main() {
	/* code */
	/*read rgen_command line arguments*/
	//char* rgen_command =(char*) malloc(strlen("./rgen") * sizeof(char));
	//strcpy(rgen_command,"./rgen");
	/*int i;
	for (i = 1; i < argc; i++)
	{
		rgen_command = argcat(rgen_command, argv[i]);
	}*/

	/*parent start fork rgen*/
	int pid_rgen, pipe_r_rgen[2];
	pipe(pipe_r_rgen);
	switch (pid_rgen = fork())
	{
	case -1:
		exit(EXIT_FAILURE);
	case 0://child process - rgen
		close(pipe_r_rgen[0]);
		dup2(pipe_r_rgen[1], STDOUT_FILENO);
		close(pipe_r_rgen[1]);
		execl("./rgen", "./rgen", nullptr);
	}
	//free(rgen_command);
	close(pipe_r_rgen[1]);
	/*parent finish rgen fork*/

	/*parent start fork a1*/
	int pid_a1, pipe_r_a1[2];
	pipe(pipe_r_a1);
	char* argq[3];
	argq[0] = (char*)"python";
	argq[1] = (char*)"ece650-a1.py";
	argq[2] = nullptr;
	switch (pid_a1 = fork())
	{
	case -1:
		exit(EXIT_FAILURE);
	case 0: //pid_a1
		dup2(pipe_r_rgen[0], STDIN_FILENO);
		close(pipe_r_rgen[0]);
		close(pipe_r_a1[0]);
		dup2(pipe_r_a1[1], STDOUT_FILENO);
		close(pipe_r_a1[1]);
		execvp("python", argq);
	}
  
	close(pipe_r_rgen[0]);
	close(pipe_r_a1[1]);
	/*parent finish a1 fork*/

	/*parent fork a2 using popen*/
	FILE* write_to_a2 = popen("./ece650-a2", "w");//a2-process 

									   /*parent start fork a1 reader*/
	int pid_a1_reader;
	switch (pid_a1_reader = fork())
	{
	case -1:
		exit(EXIT_FAILURE);
	case 0://pid_a1_reader
	{
		FILE* read_from_a1 = fdopen(pipe_r_a1[0], "r");
		char* line = NULL;
		size_t bytes = 0;
		while (getline(&line, &bytes, read_from_a1) != -1)
		{
			printf("%s", line);
			fputs(line, write_to_a2);
			fflush(write_to_a2);
		}
		fclose(read_from_a1);
		fclose(write_to_a2);
		kill(getppid(), SIGTERM);
		exit(EXIT_SUCCESS);
	}
	}
	//parent, read from stdin, fputs to a2
	close(pipe_r_a1[0]);//does not read a1 at stdin reader
	char* line = NULL;
	size_t bytes = 0;
	while (getline(&line, &bytes, stdin) != -1)
	{
		fputs(line, write_to_a2);
		fflush(write_to_a2);
	}
        
	kill(pid_rgen, SIGTERM);
	pclose(write_to_a2); //send EOF to a2
	return EXIT_SUCCESS;
}
