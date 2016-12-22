#include <iostream>

#define MAX(a,b) a>b ? a : b
#define M_PI 3.14159265358979323846
using namespace std;

struct point{
	int x;
	int y;
};
extern double distance(point* a, point* b);
extern bool is_square(point* arr[], int size);
extern point* make_point(int x_val, int y_val);

int main(){
	point* p1 = make_point(0, 0);
	point* p2 = make_point(0, 1);
	point* p3 = make_point(1, 1);
	point* p4 = make_point(1, 0);

	point* arr_pt[4];
	arr_pt[0] = p1;
	arr_pt[1] = p2;
	arr_pt[2] = p3;
	arr_pt[3] = p4;

	if (is_square(arr_pt, 4)){
		cout << "is a square" << endl;
	}
	else{
		cout << "not a square" << endl;
	}
	system("pause");
}

double distance(point* a, point* b){
	int rise = a->y - b->y;
	if (rise < 0) rise = rise * -1;

	int run = a->x - b->x;
	if (run < 0) run = run * -1;

	double res = sqrt(rise * rise + run * run);
	return res;
}

bool is_square(point* arr[], int size){
	if (size != 4) return false;
	
	for (int i = 0; i < size; i++){
		double a, b, c, d = 0;
		a = distance(arr[i], arr[0]);
		b = distance(arr[i], arr[1]);
		c = distance(arr[i], arr[2]);
		d = distance(arr[i], arr[3]);
		double hyp, opp = 0;
		double tmp1, tmp2 = 0;
		tmp1 = MAX(a, b);
		tmp2 = MAX(c, d);
		if (tmp1 > tmp2){
			hyp = tmp1;
			opp = tmp2;
		}
		else{
			hyp = tmp2;
			opp = tmp1;
		}

		const double angle = 45 * M_PI / 180;
		double SOH = hyp*sin(angle);

		cout << SOH << " " << opp << endl;
		if (SOH != opp) return false;
	}
	return true;
}

point* make_point(int x_val, int y_val){
	point* pt = (point*) malloc(sizeof(point));
	pt->x = x_val;
	pt->y = y_val;
	return pt;
}