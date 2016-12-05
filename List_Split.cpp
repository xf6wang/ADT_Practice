#include <iostream>

using namespace std;

extern bool even_split(int arry[], int arry_size);
extern bool try_permut(int arry[], int select, int k);
extern bool generate_sums(int arry[], int arry_size, int k, int prev_sum);

//function returns true if list can be split into two list with equal sum

int main(){
	const int list_sz = 7;
	int list[list_sz];
	list[0] = 4;
	list[1] = 5;
	list[2] = 6;
	list[3] = 7;
	list[4] = 4;
	list[5] = 3;
	list[6] = 1;

	if (even_split(list, list_sz)){
		cout << "can be split" << endl;
	}
	else{
		cout << "can't be split" << endl;
	}
	system("pause");
}

//example: list can be split: 4, 5, 6, | 7, 4, 3, 1

bool even_split(int arry[], int arry_size){
	//first optimization, can't split if total is odd EVEN + EVEN = EVEN, ODD + ODD = ODD
	int total = 0;
	for (int i = 0; i < arry_size; i++){
		total += arry[i];
	}
	if (total % 2 != 0){
		return false;
	}

	//must be even continue with brute force 
	//since we attempt all permutations calling function with 1 is equivalent to calling it with arry_size - 1
	//thus, only need to try for half arry_size
	for (int i = 1; i < arry_size/2 + 1; i++){
		//num elements selected, first 1, then 2, then three etc
		//select all permutations of i
		if (try_permut(arry, arry_size, i)) return true;
	}
	return false;
}

//dont really need this. due to old design structure
bool try_permut(int arry[], int arry_size, int select){
	return generate_sums(arry, arry_size, select, 0); // calls recursive function
}

bool generate_sums(int arry[], int arry_size, int k, int prev_sum){ 
	//at each iteration, we decreased k by 1, therefore, when k is 0 we have split the list with one half the desired length
	if (k == 0){
		//compare against the other half to see if list can be split
		int half = 0;
		for (int i = 0; i < arry_size; i++){
			half += arry[i];
		}
		return (half == prev_sum) ? true : false;
	}

	//recursive back-tracking 
	for (int i = 0; i < arry_size; i++){
		if (arry[i] != 0){
			// each time we add an element to prev_sum and 0 it in the arry, effectively splitting the list. 
			// we dont care about the individual elements in each sub_list, just the sum
			int tmp = arry[i];
			arry[i] = 0;
			if (generate_sums(arry, arry_size, k - 1, prev_sum + tmp)){
				return true;
			}
			//backtrack
			arry[i] = tmp;
		}
	}
	return false;
}