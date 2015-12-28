#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int t = 1;

struct ff
{
	int x, y;
	ff(int x, int y){
		this->x = x, this->y = y;
	}
	bool operator<(ff q) const 
	{
		cout << x << " sdfsdf " << " " << q.x << endl;
		return x > q.x;
	}
};

priority_queue<int> q;
struct qt
{
	bool operator()(const ff& x, const ff& y) const
	{
		return x < y;
	}
};
qt cmp;
void f(int x)
{
	cout << x << endl;
}

int main()
{
	//	f(1);
	//int x = 1, y = 2;
//	ff a, b;
//	a.x = b.y = 1;
//	a.y = b.x = 2;
//	cout << cmp(a, b) << endl;
//	b > a;
//	q.push(ff(1, 2));
//	q.push(ff(2, 3));
	q.push(1);
	q.push(2);
	
	cout << q.top() << "  "  << endl;
	return 0;
}
