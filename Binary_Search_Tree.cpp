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

extern void free_tree(node** root_ref);

extern void p_outside_cc(node* root);
extern void out_left(node* parent);
extern void out_right(node* parent);

extern bool is_same_lvl_leaves(node* parent);
extern bool same_depth(node* parent, int fin_depth, int cur_depth);
extern int leaf_depth(node* parent);

using namespace std;

//Q1.Given a node in a binary tree, find the leftmost node in the same level.
//Q2.Find the nth largest number in a binary tree.

int main(){
	node* root = make_node(4);
	insert(root, make_node(7));
	node* three = make_node(3);
	insert(root, three);
	insert(root, make_node(2));
	insert(root, make_node(6));
	node* five = make_node(5);
	insert(root, five);
	insert(root, make_node(1));

	//			4
	//		3		7
	//	2		 5

	/*print_tree(root);
	cout << endl;
	cout << find_nth(root, 2) << endl; 
	free_tree(&root);
	print_tree(root);*/

	p_outside_cc(root);

	if (is_same_lvl_leaves(root)){
		cout << "same level" << endl;
	}
	else{
		cout << "different levels" << endl;
	}
	system("pause");
}

//write a function to see if all the leaves are on the same level
bool is_same_lvl_leaves(node* root){
	if (root == NULL) return NULL;

	int leaf_dis = leaf_depth(root);

	cout << "THIS IS LEAF DIS: " << leaf_dis << endl;
	return same_depth(root, leaf_dis, 0);
}

bool same_depth(node* parent, int fin_depth, int cur_depth){
	if (parent == NULL) return false; //error, shouldnt be happening

	if (parent->left){
		bool left = false;
		left = same_depth(parent->left, fin_depth, cur_depth + 1);
		if (left == false) return false;
	}
	if (parent->right){
		bool right = false;
		right = same_depth(parent->right, fin_depth, cur_depth + 1);
		if (right == false) return false;
	}

	if (parent->left == NULL && parent->right == NULL){
		return (cur_depth == fin_depth) ? true : false;
	}
	return true;
}

int leaf_depth(node* parent){
	if (parent == NULL) return 0;

	if (parent->left) return 1 + leaf_depth(parent->left);
	if (parent->right) return 1 + leaf_depth(parent->right);

	//both children null, must be leaf
	return 0;
}

void p_outside_cc(node* root){ //print the outside nodes counter clockwise -- print largest to smallest essentailly
	if (root == NULL) return;
	out_right(root->right);

	cout << root->data << " ";

	out_left(root->left);
}

//print the left hand side of the tree
void out_left(node* parent){
	if (parent == NULL) return;
	cout << parent->data << " ";
	node* pt = parent;
	if (pt->left != NULL){
		out_left(pt->left);
	}
	else{
		out_left(pt->right);
	}
}

//print the right hand side of the tree
void out_right(node* parent){
	if (parent == NULL) return;
	node* pt = parent;
	if (pt->right != NULL){
		out_right(pt->right);
	}
	else{
		out_right(pt->left);
	}
	cout << parent->data << " ";
}

void free_tree(node** root_ref){
	if (*root_ref == NULL) return;
 	if ((*root_ref)->left) free_tree(&((*root_ref)->left));
	if ((*root_ref)->right) free_tree(&((*root_ref)->right));
	free(*root_ref);
	*root_ref = NULL;
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
