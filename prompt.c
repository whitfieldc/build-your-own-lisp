#include <stdio.h>

/*declare buffer for user input of size 2048*/

static char input[2048];

int main(int argc, char** argv){

	/*print versino and exit info*/
	puts ("Lisp Clone v 0.0.0.0.1");
	puts ("Press Ctrl+c to Exit\n");

	/*never-ending loop*/
	while (1){
		
		/*output prompt*/
		fputs("lisp clone> ", stdout);

		/* read a line of user input max size 2048*/
		fgets(input, 2048, stdin);

		/*echo in put back to user*/
		printf("no you're a %s", input);
	}

	return 0;
}

