#include <iostream>
#include <string>

using namespace std;

extern char* compress(char* str);
extern char* reverse_str(char* p);
extern string in_both_NxN(string a, string b);
extern string in_both_N(string a, string b);
extern bool is_prem(string arr[], int elements, string my_str);
extern string most_common(string lst[], int size);
extern void reverse_ip(char* str);
extern void reverse(string &str);
extern void rev_arry(int arry[], int size);
extern void sort_alpha(string arry[]);
extern bool is_anagram(string str1, string str2);

/*int main(){
	system("pause");
}*/

//sort an array of strings alpha-numerically
void sort_alpha(string arry[]){
	//for simplicity just bubble sort the arry
}


//Determine if two strings are anagrams of one another in O(n + m) runtime and O(1) space
bool is_anagram(string str1, string str2){

	return false;
}


/*
char* word = (char*)malloc(sizeof(char) * 6);
word[0] = 'h';
word[1] = 'e';
word[2] = 'l';
word[3] = 'l';
word[4] = 'o';
word[5] = '\0';

reverse_ip(word);
*/
//reverse a string in place using char arry
void reverse_ip(char* str){
	int len = strlen(str);
	char* end_pt = str + len - 1;
	char* pt = str;

	for (int i = 0; i < len / 2; i++){
		char tmp = *end_pt;
		*end_pt = *pt;
		*pt = tmp;
		pt++;
		end_pt--;
	}
}


//given arry of strings return the one that appears the most
//test: 	string arry[] = { "bob", "bob", "alice", "bob", "dog" };
//			const int ARRY_SZE = 5;
//			cout << most_common(arry, ARRY_SZE) << endl;
string most_common(string lst[], int size){
	string most = "";
	int occur = 0;

	for (int i = 0; i < size; i++){
		const char* tmp = lst[i].c_str();
		int app = 0;

		for (int n = i + 1; n < size; n++){
			const char* cur = lst[n].c_str();
			if (strcmp(tmp, cur) == 0){
				app++;
			}
		}

		if (app > occur){
			most = tmp;
			occur = app;
		}
	}

	return most;
}

//determine if the string is a premutation of the array of strings provided
bool is_prem(string arr[], int elements, string my_str){
	for (int i = 0; i < elements; i++){
		size_t found = my_str.find(arr[i]);
		if (found != string::npos){
			my_str.erase(found, arr[i].length());
		}
		else{
			return false;
		}
	}
	return (my_str.length() > 0) ? false : true;
}

string in_both_NxN(string a, string b){
	if (a.empty() || b.empty()) return NULL;
	string res;

	for (int n = 0; n < a.length(); n++){
		for (int m = 0; m < b.length(); m++){
			if (a[n] == b[m]){
				res += a[n];
				b.erase(m, 1);
			}
		}
		if (b.length() == 0) break;
	}

	return res;
}

string in_both_N(string a, string b){
	return NULL;
}

char* reverse_str(char* p){
	int len = strlen(p);
	char* rev = (char*)malloc(sizeof(char) * len);
	rev[len] = '\0';
	for (int i = 0; i < len; i++){
		rev[i] = p[len - 1 - i];
	}
	return rev;
}

//compression aaaabbbcc into a4b3c2 and aaabcc into a3bc2
char* compress(char* str){
	int i = 0;
	int size = 0;
	char* result = (char*)malloc(sizeof(char) * strlen(str)); //allocate same memory as result more space than needed for compression

	while (str[i] != '\0'){
		int recur = 1; //num times recurring
			
		while (str[i] == str[i + 1]){
			i++;
			recur++;
		}
		if (recur == 1){
			result[size] = str[i];
		}
		else{
			result[size] = str[i];
			result[++size] = recur + '0';
		}
		i++;
		size++;
	}
	result[size] = '\0'; //terminate string
	return result;
}

/*
int m[] = { 6, 7, 8, 9, 10 };
rev_arry(m, 5);
for (int i = 0; i < 5; i++){
cout << m[i];
}
cout << endl;
*/
void rev_arry(int arry[], int size){
	for (int i = 0; i < size / 2; i++){
		int tmp = arry[i];
		arry[i] = arry[size - 1 - i];
		arry[size - 1 - i] = tmp;
	}
}

/* -- reverse a string
string my_str = "hello world";
reverse(my_str);
cout << my_str << endl;
*/
void reverse(string &str){
	for (int i = 0; i < str.length() / 2; i++){
		char tmp = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = tmp;
	}
}