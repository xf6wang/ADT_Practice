#include <iostream>
struct node{
	int data;
	node* left;
	node* right;
};

extern void insert(node* parent, node* new_node);
extern void print_tree(node* root);
extern node* make_node(int value);
extern int leftest(node* root, node* my_node);
extern int find_depth(node* parent, node* my_node);
extern int find_nth(node* parent, int nth);
extern int count(node* parent);


using namespace std;

//Q1.Given a node in a binary tree, find the leftmost node in the same level.
//Q2.Find the nth largest number in a binary tree.

int main(){
	node* root = make_node(4);
	insert(root, make_node(7));
	node* three = make_node(3);
	insert(root, three);
	insert(root, make_node(2));
	node* five = make_node(5);
	insert(root, five);

	//			4
	//		3		7
	//	2		 5

	print_tree(root);
	cout << endl;
	cout << find_nth(root, 2) << endl; 
	system("pause");
}

int find_nth(node* parent, int nth){
	if (nth == 0) return -1;
	if (parent == NULL) return -1;
	int left = count(parent->left);

	if (left == nth - 1){
		return parent->data;
	}
	else if (left < nth - 1 && left != 0){
		return find_nth(parent->right, nth - left - 1);
	}
	else if(left > nth - 1 && left != 0){
		return find_nth(parent->left, nth ); // final -1 to account for the parent node
	}
}

int count(node* parent){
	if (parent == NULL)return 0;
	return 1 + count(parent->left) + count(parent->right);
}

int leftest(node* root, node* my_node){
	int depth = find_depth(root, my_node);
	if (depth == -1) return -1; //error case

	node* pt = root;
	for (int i = 0; i < depth - 1; i++){
		if (pt->left != NULL){
			pt = pt->left;
		}
		else if (pt->right != NULL){
			pt = pt->right;
		}
	}
	return pt->data;
}

int find_depth(node* parent, node* my_node){
	if (parent == NULL || my_node == NULL) return 0;
	if (parent->data == my_node->data){
		return 1;
	}
	else if (parent->data < my_node->data){
		return 1 + find_depth(parent->right, my_node);
	}
	else{
		return 1 + find_depth(parent->left, my_node);
	}
	return -1; //not found
}

void insert(node* parent, node* new_node){
	if (parent == NULL){
		return;
	}
	if (new_node->data < parent->data){
		if (parent->left == NULL){
			parent->left = new_node;
		}
		else{
			insert(parent->left, new_node);
		}
	}
	else if (new_node->data > parent->data){
		if (parent->right == NULL){
			parent->right = new_node;
		}
		else{
			insert(parent->right, new_node);
		}
	}
}

void print_tree(node* root){
	if (root == NULL) return;
	print_tree(root->left);
	cout << root->data << " ";
	print_tree(root->right);
}

node* make_node(int value){
	node* res = (node*)malloc(sizeof(node));
	res->data = value;
	res->left = NULL;
	res->right = NULL;
	return res;
}
