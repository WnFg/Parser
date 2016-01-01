#ifndef __HASHSET_H
#define __HASHSET_H

struct hashSet
{
	bool *hash_value1, *hash_value2;	 
	int size, loadSize;  // hash表大小和装载了多少
	
	hashSet(int a){
		size = a;
		hash_value1 = new bool[size]; 
		hash_value2 = new bool[size];
	}
	
	unsigned int hash(string& str, unsigned int seed){
		int len = str.size();
		unsigned int ans = 0;
		for(int i = 0; i < len; i++){
			ans = (ans * seed) + str[i];
			ans %= size;
		}
		return ans;
	}

	void insert(string& str){
		//int len = str.size();
		hash_value1[hash(str, 31)] = true;
		hash_value2[hash(str, 131)] = true;
		loadSize++;		
	}

	bool hasEmpty(string& str){
		if(hash_value1[hash(str, 31)] && hash_value2[hash(str, 131)])
			return true;
		return false;
	}
};

#endif
