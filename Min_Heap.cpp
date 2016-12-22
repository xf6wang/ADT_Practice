#include <iostream>

extern int pop(int heap[], int &size);
extern void print(int heap[], int size);
extern void swap(int heap_list[], int location1, int location2);
extern void push(int heap[], int &size, int value);
extern void percolate_down(int heap[], int k, int heap_max);
extern void percolate_up(int heap[], int k);
extern void min_heapify(int heap[], int size);
extern void heap_sort(int heap[], int size);

using namespace std;

/*
int main(){
	int heap[16];
	int heap_size = 11; //12 elements in the current heap

	heap[0] = NULL;
	heap[1] = 3;
	heap[2] = 6;
	heap[3] = 12;
	heap[4] = 9;
	heap[5] = 14;
	heap[6] = 23;
	heap[7] = 29;
	heap[8] = 10;
	heap[9] = 25;
	heap[10] = 19;
	heap[11] = 15;

	print(heap, heap_size);
	heap_sort(heap, heap_size);
	print(heap, heap_size);

	system("pause");
} */

//Implementation all for a min heap!!!

void min_heapify(int heap[], int size){
	for (int i = size / 2; i > 0; i--){
		percolate_down(heap, i, size);
	}
}

void heap_sort(int heap[], int size){
	min_heapify(heap, size);
	int* tmp = (int*)malloc(sizeof(int)*(size + 1));
	int tmp_size = size;
	for (int i = 1; i <= size; i++){
		tmp[i] = pop(heap, tmp_size);
	}
	for (int i = 1; i <= size; i++){
		heap[i] = tmp[i];
	}
	free(tmp);
}

void print(int heap[], int size){
	for (int i = 1; i <= size; i++){
		cout << heap[i] << " ";
	}
	cout << endl;
}

int pop(int heap[], int &size){
	int to_pop = heap[1]; // 0 always empty in the heap

	heap[1] = heap[size]; //pop top with last element

	size--;

	percolate_down(heap, 1, size); //percolating from root

	return to_pop;
}

void push(int heap[], int &size, int value){
	size++;
	heap[size] = value;
	percolate_up(heap, size);
}

void swap(int heap_list[], int location1, int location2){
	int tmp = heap_list[location1];
	heap_list[location1] = heap_list[location2];
	heap_list[location2] = tmp;
}

void percolate_down(int heap[], int k, int heap_max){ //percolate down for min heap, if max heap similar but different comparison logic
	if (2 * k > heap_max){
		return; //cant go further or else array overflow 
	}
	if (heap[k] <= heap[2 * k] && heap[k] <= heap[2 * k + 1]){
		return; // min element done
	}
	else if (heap[k] <= heap[2 * k] && heap[k] > heap[2 * k + 1]){
		swap(heap, k, 2 * k + 1);
		percolate_down(heap, 2 * k + 1, heap_max);
	}
	else if (heap[k] <= heap[2 * k+1] && heap[k] > heap[2 * k]){
		swap(heap, k, 2 * k);
		percolate_down(heap, 2 * k, heap_max);
	}
	else{
		//swap with the smaller of the two children
		if (heap[2 * k] > heap[2 * k + 1]){
			swap(heap, k, 2 * k + 1);
			percolate_down(heap, 2 * k + 1, heap_max);
		}
		else{
			swap(heap, k, 2 * k);
			percolate_down(heap, 2 * k, heap_max);
		}
	}
}

void percolate_up(int heap[], int k){
	int parent = k / 2;
	if (parent == 0){
		return; //at root cannot percolate higher
	}
	if (heap[k] < heap[parent]){
		swap(heap, k, parent);
		percolate_up(heap, parent);
	}
}

//3 6 12 9 14 23 29 10 25 19 15 26