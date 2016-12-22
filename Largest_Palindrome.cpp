#include <iostream>
#include <string>

using namespace std;

struct letter{
	char let;
	letter* next;
};

extern void print(letter* head);
extern letter* add_letter(char new_letter);
extern void push(letter** head_ref, letter* new_node);
extern letter* make_word(char* str);
extern char* largest_palin(letter* head);
extern char* make_char(letter* start, int end);
extern bool is_palindrome(letter* start, int end);
extern bool move_next(letter* lett, int &loc);


/*int main(){
	//kraracecarp
	letter* my_word = make_word("kraracecarp"); 

	print(my_word);		
	cout << largest_palin(my_word) << endl; // should be racecar

	system("pause");
}*/

//write a function that returns the largest palindrome given a singly linked list
//ie. kraracecarp returns racecar
char* largest_palin(letter* head){
	letter* pt = head;
	int longest = 0;
	char* palindrome = "";
	while (pt){
		int next = 0;
		while (move_next(pt, next)){
			if (is_palindrome(pt, next)){
				if (next > longest){
					longest = next;
					palindrome = make_char(pt, next + 1);
				}
			}
		}
		pt = pt->next;
	}
	return palindrome;
}

char* make_char(letter* start, int end){
	char* word = (char*)malloc(sizeof(char) * end);
	word[end] = '\0';

	letter* pt = start;
	for (int i = 0; i < end; i++){
		word[i] = pt->let;
		pt = pt->next;
	}
	return word;
}

bool is_palindrome(letter* start, int end){
	if (end <= 0) return true;
	if (start == NULL) return false;

	letter* pt = start;
	for (int i = 0; i < end; i++){
		if(pt) pt = pt->next;
	}
	if (pt == NULL) return false;
	if (start->let == pt->let){
		return is_palindrome(start->next, end - 2);
	}
	else{
		return false;
	}
}

bool move_next(letter* lett, int &loc){
	letter* pt = lett;
	for (int i = 0; i < loc; i++){
		if(pt) pt = pt->next;
	}
	if (pt == NULL) return false;
	char my_letter = lett->let;
	pt = pt->next;
	loc++;
	while (pt){
		if (pt->let == my_letter){
			return true;
		}
		pt = pt->next;
		loc++;
	}
	return false;
}

//helper functions for linked list maintaince
letter* make_word(char* str){
	letter* head = add_letter(str[strlen(str) - 1]);
	for (int i = strlen(str) - 2; i >= 0; i--){
		push(&head, add_letter(str[i]));
	}
	return head;
}

void print(letter* head){
	letter* pt = head;
	while (pt){
		cout << pt->let;
		pt = pt->next;
	}
	cout << endl;
}

letter* add_letter(char new_letter){
	letter* new_node = (letter*)malloc(sizeof(letter));
	new_node->let = new_letter;
	new_node->next = NULL;
	return new_node;
}

void push(letter** head_ref, letter* new_node){
	new_node->next = *head_ref;
	*head_ref = new_node;
}