#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> v;
class animal
{
	int height, weight, old;
public:
	static int cnt;
	animal(){
		height = weight = old = 0;
		++cnt;
		cout << "I am a cat\n" << endl;
	
	}

	animal(int x, int y){
		height = x;
		weight = y;
		++cnt;
	}
	
	void operator +(){
		++old;
	}

	void operator ->(){
		old -= 1;
	}

	void operator --(int){
		old-=1;
	}
	
	int get(){
		return old;
	}

	static void run(){
		cout << "I am running!\n" << endl;
	}
};
int animal::cnt = 0;

void f(char ){
	
}

int main(){
	animal cat;
}

