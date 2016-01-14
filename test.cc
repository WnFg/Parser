#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
#include "hashSet.h"

hashMap<int> hMap(103);

int main()
{
	int n, m;
	cin >> n >> m;
	while(n -- )
	{
		string key;
		int val;
		cin >> key >> val;
		hMap.insert(key, new int(val));
	}
	
	while(m--){
		string key;
		cin >> key;
		int *p = hMap[key];
		if(p == NULL){
			cout << key << "不在hMap中" << endl;
		}else{
			cout << *p << endl;
		}
	}
	return 0;
}
