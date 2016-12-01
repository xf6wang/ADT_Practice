#include <iostream>
//linked list node
struct digit{
	int num;
	digit *next;
	digit *prev;
};

extern void push(digit *node, digit ** headRef);
extern digit* make_node(int data);
extern void print(digit *head);
extern digit* sum(digit* num1, digit* num2);
extern digit* get_tail(digit* head);
extern void swap(digit** head_ref, digit* num1, digit* num2);
extern void smart_swap(digit* a_ref, digit* b_ref);

using namespace std;
/*
int main(){
	digit* num1 = make_node(5);
	push(make_node(3), &num1);
	push(make_node(2), &num1);

	digit* nine = make_node(9);
	push(nine , &num1);
	push(make_node(9), &num1);
	push(make_node(1), &num1);
	digit* three = make_node(3);
	push(three, &num1);
	push(make_node(1), &num1);
	push(make_node(2), &num1);

	digit* num2 = make_node(5);
	push(make_node(9), &num2);
	push(make_node(9), &num2);
	push(make_node(1), &num2);
	push(make_node(3), &num2);
	push(make_node(1), &num2);
	push(make_node(2), &num2);

	print(num1);
	print(num2);
	print(sum(num1, num2));//test 

	system("pause");
}
*/

digit* sum(digit* num_1, digit* num_2){
	digit* t1 = get_tail(num_1);
	digit* t2 = get_tail(num_2);
	if (t1 == NULL){
		return num_2;
	}
	else if (t2 == NULL){
		return num_1;
	}

	bool has_carry = false;
	int sum = 0;

	//create initial node
	sum = t1->num + t2->num;
	if (sum >= 10){
		has_carry = true;
	}
	t1 = t1->prev;
	t2 = t2->prev;
	sum = 0;
	digit* result = make_node(sum % 10);

	//bulk of the addition
	while (t1 || t2){
		sum = 0;
		if (t1 && t2){
			sum = t1->num + t2->num;
		}
		else if (t1){
			sum = t1->num;
		}
		else{
			sum = t2->num;
		}

		if (has_carry) sum = sum + 1;

		if (sum >= 10){
			has_carry = true;
		}
		else{
			has_carry = false;
		}

		push(make_node(sum % 10), &result);

		if (t1) t1 = t1->prev;
		if (t2) t2 = t2->prev;
	}
	if (has_carry) push(make_node(1), &result);

	return result;
}


void swap(digit** head_ref, digit* num1, digit* num2){
	digit* pt = *head_ref;
	if (pt == NULL){
		cout << "empty list" << endl;
		return;
	} 
	while (pt->next != num1 && pt->next != NULL){
		if (pt == num1) break;
		pt = pt->next;
	}
	//error check
	if (pt->next == NULL && pt != num1){
		cout << "num1 first param not found in list" << endl;
		return;
	}

	pt->next = num2;

	pt = num2->next;

	num2->next = num1->next;
	
	num1->next = pt;

	pt = num2->next;


	while (pt->next != num2 && pt->next != NULL){
		if (pt == num2) break;
		pt = pt->next;
	}

	if (pt->next == NULL && pt != num2){
		cout << "num2 second param not found in list" << endl;
		return;
	}

	pt->next = num1;
	if (*head_ref == num1){
		*head_ref = num2;
		cout << "cant swap head ref right now" << endl;
		return;
	}
}

digit* get_tail(digit* head){
	digit* pt = head;
	while (pt->next != NULL){
		pt = pt->next;
	}
	return pt;
}


void push(digit *node, digit ** headRef){
	(*headRef)->prev = node;
	node->next = *headRef;
	*headRef = node;
}

digit* make_node(int data){
	digit* node = (digit*)malloc(sizeof(digit));
	node->next = NULL;
	node->prev = NULL;
	node->num = data;
	return node;
}

void print(digit *head){
	digit* pt = head;
	while (pt){
		cout << pt->num << " ";
		pt = pt->next;
	}
	cout << endl;
}


//write a program that adds two numbers (each given as linked list of digits) and return sum of numbers as linked list
//eg. 235 145