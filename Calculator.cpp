#include <iostream>

using namespace std;

/*int main(){

}*/

double pow(double x, double power){ //return x^power w/o library functions
	double result = x;
	if (power >= 1){
		for (int i = 0; i < power; i++){
			result *= x;
		}
	}
	else{

	}
	return -1;
}