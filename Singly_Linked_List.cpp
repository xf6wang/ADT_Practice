#include <iostream>

using namespace std;

struct ll{
	int data;
	ll* next;
};

extern void print(ll *head);
extern ll* make_node(int value);
extern void push(ll** head_ref, ll* new_node);
extern ll* swap_by_two(ll* head);
extern void free_list(ll** head_ref);
extern bool is_cyclic(ll* head);

extern void merge_sort(ll** head_ref);
extern ll* middle_split(ll* head);
extern ll* merge(ll* a, ll* b);

extern void quick_sort(ll** head_ref, int first, int last);
extern ll* find_median(ll* pt, ll* middle, ll* end);
extern void swap(ll** head_ref, ll** a_ref, ll** b_ref);
extern void partition(ll* head, ll* piv, int fir, int las);


/*int main(){
	ll* root = make_node(3);
	ll* three = root;
	push(&root, make_node(4));
	ll* eight = make_node(8);
	push(&root, eight);

	push(&root, make_node(6));
	push(&root, make_node(2));
	ll* one = make_node(1);
	push(&root, one);
	push(&root, make_node(7));
//	push(&root, three);

//	print(root);
//	ll* pt = swap_by_two(root);
//	root = pt;
//	print(root);
	print(root);
	quick_sort(&root, 0, 6);

//	merge_sort(&root);
	print(root);

	system("pause");
}*/

/*QUICK SORT - MEDIAN OF THREE*/
void quick_sort(ll** head_ref, int first, int last){
	if (last <= first) return;
	if (head_ref == NULL) return;
	if ((*head_ref) == NULL) return;
	ll* pt = *head_ref;
	if (last - first == 0 || last - first == 1) return; // base case exit for recursion
	ll* middle = pt;
	int mid = 0;
	for (int i = 0; i < (last-first) / 2; i++){
		middle = middle->next;
		mid++;
	}
	ll* end = pt;
	for (int i = 0; i < last - first; i++){
		end = end->next;
	}

	ll* pivot = find_median(pt, middle, end);
	swap(head_ref, &pivot, &middle);
	partition(pt, pivot, first, last);

	//divide and conquer the two halves
	quick_sort(&pivot, 0, mid - 1 );
	quick_sort(&pivot, mid + 1, last);
}

//very bad implementation. quicksort should used with an array
//right now runtime is linear
void partition(ll* head, ll* piv, int fir, int las){
	ll* first = head;
	ll* last = head;
	for (int i = 0; i < fir; i++){
		first = first->next;
	}
	for (int i = 0; i < las; i++){
		last = last->next;
	}
	int total = las - fir;

	for (int n = 0; n < total; n++){
		if (first && last){
			if (first->data > piv->data && last->data < piv->data){
				swap(&head, &first, &last);
				first = first->next;
				last = first;
				fir--;
				las--;

				for (int i = 0; i < las - fir; i++){
					if (last)last = last->next;
				}
			}
		}
		if (first){
			if (first->data < piv->data){
				first = first->next;
			}
		}
		if (last){
			if (last->data > piv->data){
				last = first;
				las--;
				for (int i = 0; i < las - fir; i++){
					last = last->next;
				}
			}
		}
	}

}



ll* find_median(ll* pt, ll* middle, ll* end){
	ll* median;
	//determine median
	if (pt->data > middle->data){
		if (pt->data > end->data){
			if (end->data > middle->data){
				median = end;
			}
			else{
				median = middle;
			}
		}
		else{
			median = pt;
		}
	}
	else{
		if (middle->data > end->data){
			if (end->data > pt->data){
				median = end;
			}
			else{
				median = pt;
			}
		}
		else{
			median = middle;
		}
	}
	return median;
}

/*QUICK SORT END*/

/*MERGE SORT*/
void merge_sort(ll** head_ref){
	if (*head_ref == NULL) return;
	ll* pt = *head_ref;
	ll* mid_pt = middle_split(pt);

	if (mid_pt == NULL) return; //only one element, exit for recursion

	if(pt) merge_sort(&pt);
	if(mid_pt) merge_sort(&mid_pt);

	ll* new_head = merge(pt, mid_pt);
	*head_ref = new_head;
}

ll* merge(ll* a, ll* b){
	//assumption is that both sublists are sorted
	if (a == NULL) return b;
	if (b == NULL) return a;

	//set head of list
	ll* res;

	if (a->data < b->data){
		res = a;
		a = a->next;
	}
	else{
		res = b;
		b = b->next;
	}
	res->next = NULL;

	ll* tmp; //used as tmp pointer to help seperate from list
	ll* pt = res; //moving pointer
	while (a && b){
		if (a->data < b->data){
			pt->next = a;
			pt = pt->next;
			tmp = a;
			a = a->next;
			tmp->next = NULL;
		}
		else{
			pt->next = b;
			pt = pt->next;
			tmp = b;
			b = b->next;
			tmp->next = NULL;
		}
	}

	if (a){
		pt->next = a;
	}
	else if (b){
		pt->next = b;
	}
	return res;
}

//find the middle element in the linked list and seperate from rest of list
ll* middle_split(ll* head){
	if (head == NULL) return NULL;
	if (head->next == NULL) return NULL;
	ll* pt = head;
	ll* pt_fast = head->next;
	ll* prev = pt;

	while (pt_fast){
		prev = pt;
		pt = pt->next;
		pt_fast = pt_fast->next;
		if (pt_fast) pt_fast = pt_fast->next;
	}
	prev->next = NULL; //split the list in two
	return pt;
}
/*MERGE SORT END*/


//swap two elements in a linked list
void swap(ll** head_ref, ll** a_ref, ll** b_ref){
	if (*head_ref == NULL || *a_ref == NULL || *b_ref == NULL) return;
	if (*a_ref == *b_ref) return;
	ll* pt = *head_ref; //moving pointer
	ll* prev = pt; //previous

	bool is_head = false;

	ll* first = NULL;
	ll* second = NULL;

	ll* f_prev = NULL; //pointer before first
	ll* s_prev = NULL; //pointer before second

	while (pt){
		if (first == NULL){

			if (pt->data == (*a_ref)->data){
				if (pt == prev) is_head = true;
				first = *a_ref;
				f_prev = prev;
			}
			if (pt->data == (*b_ref)->data){
				if (pt == prev) is_head = true;
				first = *b_ref;
				f_prev = prev;
			}
		}
		else if (second == NULL){
			if (pt->data == (*a_ref)->data){
				second = *a_ref;
				s_prev = prev;
				break;
			}
			if (pt->data == (*b_ref)->data){
				second = *b_ref;
				s_prev = prev;
				break;
			}
		}
		prev = pt;
		pt = pt->next;
	}
	if (pt == NULL){
		cout << "Error: either a or b could not be found" << endl;
		return;
	}
	if (f_prev == NULL || s_prev == NULL){
		cout << "you messed up coding somewhere" << endl;
		return;
	}

	ll* tmp = second->next;

	if (is_head){
		second->next = first->next;
		first->next = tmp;
		s_prev->next = first;
		*head_ref = second;
	}
	else{
		f_prev->next = second;
		second->next = first->next;
		first->next = tmp;
		s_prev->next = first;
	}
}

//determine if the list is circular or linear
bool is_cyclic(ll* head){
	if (head == NULL) return false;
	ll* slow_pt = head;
	ll* fast_pt = head->next;

	while (slow_pt && fast_pt){
		if (slow_pt == fast_pt)return true;

		slow_pt = slow_pt->next;

		fast_pt = fast_pt->next;
		if (fast_pt) fast_pt = fast_pt->next;
	}
	return false; //if either slow or fast is NULL, then we know the list cannot be circular
}

//cleanup - memory deallocation
void free_list(ll** head_ref){
	if (*head_ref == NULL) return;
	if ((*head_ref)->next != NULL) free_list(&((*head_ref)->next));
	free(*head_ref);
	*head_ref = NULL;
}

void print(ll* head){
	ll* pt = head;
	while (pt){
		cout << pt->data << " ";
		pt = pt->next;
	}
	cout << endl;
}

ll* make_node(int value){
	ll* new_node = (ll*)malloc(sizeof(ll));
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}

void push(ll** head_ref, ll* new_node){
	new_node->next = *head_ref;
	*head_ref = new_node;
}

//problem: write a function that swaps every two nodes
// ie. a->b->c->d becomes b->a->d->c
ll* swap_by_two(ll* head){
	if (head == NULL) return NULL;
	if (head->next == NULL) return head; //two exits for recursion

	ll* a = head;
	ll* b = head->next;
	ll* c = NULL;
	if (b->next != NULL){
		c = b->next;
	}

	b->next = a;

	if (c){
		a->next = swap_by_two(c); // recursively swap the rest of the list
	}
	else{
		a->next = NULL;
	}

	return b;
}
