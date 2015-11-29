#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer [2048];

/* fake readline function*/
char* readline(char* prompt){
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy
}

/* fake add_history function*/
void add_history(char* unused){}

/*otherwise include editline */
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv){

	/*print versino and exit info*/
	puts ("Lisp Clone v 0.0.0.0.1");
	puts ("Press Ctrl+c to Exit\n");

	/*never-ending loop*/
	while (1){

		/*output prompt and get input*/
		char* input = readline("lisp clone> ");

		/* read a line of user input max size 2048*/
		add_history(input);

		/*echo in put back to user*/
		printf("no you're a %s\n", input);

		/*free retrieved input*/
		free(input);
	}

	return 0;
}
