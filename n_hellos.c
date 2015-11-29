#include <stdio.h>

int n_hellos(int n);

int main(){

	int times = 7;

	n_hellos(times);

	return 0;

}

int n_hellos(int num){

	for (int i = 0; i < num; i++){
		puts("Hello world");
	}
	return 0;
}