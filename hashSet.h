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

template<class T>
struct hashMap
{
	struct Node
	{
		Node *next;
		T *value;
		string s;
		Node(){
			next = NULL;
			value = NULL;
			s = "";
		}
		Node(string str, T *val){
			s = str;
			value = val;
			next = NULL;
		}
	};

	int size;
	vector<Node> *v;
	
	hashMap(int a){
		size = a;
		v = new vector<Node>(a);
	}	

	unsigned int hash(const string& str, int seed){
		int len = str.size();
		unsigned int ans = 0;
		for(int i = 0; i < len; i++){
			ans = (ans * seed) + str[i];
			ans %= size;
		}
		return ans;
	}

	inline Node* find(int i, const string& str){
		Node *p = &(*v)[i];
		while(p != NULL){
			if(p->s == str)
				return p;
			p = p->next;
		}
		return p;
	}

	T* operator [](const string& str){
		unsigned int i = hash(str, 31);
		Node *p = find(i, str);
		return p == NULL ? NULL : p->value;
	}

	void insert(const string& key, T *value){
		unsigned int i = hash(key, 31);
		Node *p = &(*v)[i];
		if(p == NULL){
			(*v)[i] = *(new Node(key, value));
			return ;
		}
		while(p->next != NULL){
			p = p->next;
		}
		p->next = new Node(key, value);
	}
};
#endif
