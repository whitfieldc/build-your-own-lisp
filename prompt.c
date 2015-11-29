#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
/*declare buffer for user input of size 2048*/

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
