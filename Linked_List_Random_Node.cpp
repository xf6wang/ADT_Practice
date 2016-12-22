#include <iostream>

using namespace std;

struct linkl{
	int data;
	//one points to the next node, the other points to a random node, but we dont know which ones which
	linkl* pt1; 
	linkl* pt2;
};

extern linkl* deep_copy(linkl* head, linkl* visited[], int num_elements, int &num_visited);
extern linkl* make_node(int val);


/*int main(){
	linkl* one = make_node(1);
	linkl* three = make_node(3);
	linkl* two = make_node(2);
	linkl* five = make_node(5);
	linkl* seven = make_node(7);

	//chain for the linked list -- how it should be traversed
	one->pt1 = three;
	three->pt1 = two;
	two->pt2 = five;
	five->pt1 = seven;
	seven->pt2 = NULL;

	//random pt set now
	one->pt2 = two;
	three->pt2 = seven;
	two->pt1 = one;
	five->pt2 = three;
	seven->pt1 = five;

	const int list_size = 5;

	linkl* visited[list_size];
	int has_visited = 0;
	linkl* copy = deep_copy(one, visited, list_size, has_visited);

	system("pause");
}*/


//returns deep copy of linked list
linkl* deep_copy(linkl* head, linkl* visited[], int num_elements, int &num_visited){
	if (head == NULL) {
		return NULL;
	}
	if (num_visited > num_elements){
		cerr << "Error: Bad array access" << endl;
		return NULL;
	}
	int i = 0;
	bool cycle = false;
	int tmp = head->data;

	for (; i < num_visited; i++){
		if (tmp == (visited[i])->data){
			cycle = true;
			break;
		}
	}
	if (cycle){
		return visited[i];
	}
	else{
		//copy node
		linkl* copy = make_node(tmp);
		visited[num_visited] = copy;
		num_visited++;
		//recursively link node to rest of list
		copy->pt1 = deep_copy(head->pt1, visited, num_elements, num_visited);
		copy->pt2 = deep_copy(head->pt2, visited, num_elements, num_visited);
		return copy;
	}
}

linkl* make_node(int val){
	linkl* my_node = (linkl*)malloc(sizeof(linkl));
	my_node->data = val;
	my_node->pt1 = NULL;
	my_node->pt2 = NULL;

	return my_node;
}