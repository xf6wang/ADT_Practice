#include <iostream>
#include <string>

using namespace std;

extern char* compress(char* str);

/*int main(){
	char* str = "abbbcc";
	char* res = compress(str);
	cout << str << endl;
	cout << res << endl;
	system("pause");
}*/

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

//compression aaaabbbcc into a4b3c2 and aaabcc into a3bc2