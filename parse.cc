#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <string>
#include <map>
using namespace std;
#include "need.h"
#include "mylist.h"


struct CFG
{	
	string S;    //起始符
	vector<string> NT, T;    // 非终结符， 终结符
	vector<string> P, spt;	 // 表达式
	map< string, vector<my_List<string> > > exp;
	map< string, vector<vector<string> > > mp;
	CFG(){
		cout << "输入非结束符,以0结束：" << endl;
		string str;
		while(cin >> str && str != "0"){
			NT.push_back(str);	
		}

		cout << "输入结束符，以0结束：" << endl;
		while(cin>> str && str != "0"){
			T.push_back(str);
		}

		cout << "输入开始符，以0结束：" << endl;
		while(cin >> str && str != "0"){
			S = str;
		}

		cout << "输入表达式，每行为一条表达式，以0结束：" << endl;
		while(cin >> str && str != "0"){
			P.push_back(str);
		}
	}
    void split(const string& str);   

	void analysis_P(){      // 把一个表达式分解为： 一a个非终结符  -> 终结符或非终结符的串
		my_List<string> *lst = new my_List<string>;
		lst->head = new Node<string>;
		for(int i = 0; i < (int)P.size(); i++){
			split(P[i]);		
		}
		
		for(int i = 0; i < (int)NT.size(); i++){
			for(int j = 0; j < mp[NT[i]].size(); j++){
				for(int k = 0; k < mp[NT[i]][j].size(); j++)
					lst->add(new Node<string>(mp[NT[i]][j][k]), 1);
				exp[NT[i]].push_back(*lst);
			}
		}
	}
};


void CFG::split(const string& str){
	int mark;
	bool ok;
	for(mark = 0; mark < (int)NT.size(); mark++){
		if( comp(NT[mark], str, 0) ){
			mp[NT[mark]].push_back(spt);	
			break;
		}
	}
	int size = mp[NT[mark]].size() - 1;
	for(int i = (int)NT[mark].size(); i < (int)str.size(); i++)
	{
		ok = false;
		for(int j = 0; !ok && j < (int)NT.size(); j++)
		{
			if( comp(NT[j], str, i) )
			{
				//	cout << "dsfgwer" << endl;
					mp[NT[mark]][size].push_back(NT[j] + "`");
					ok = true;
					i += NT[j].size() - 1;
			}	
		}
	//	cout << "sdfwer" << endl;
		for(int j = 0; !ok && j < (int)T.size(); j++)
		{
			if( comp(T[j], str, i) ){
			//	cout << "sdfee" << endl;
				mp[NT[mark]][size].push_back(T[j]);
				ok = true;
				i += T[j].size() - 1;
			}
		}
	}
}

CFG *cfg = new CFG;
int main()
{
//	init();
	cfg->analysis_P();
//	cout << "sdfsdf" << endl;
/*	for(int i = 0; i < cfg->NT.size(); i++){
		vector<string> &tt = cfg->mp[ cfg->NT[i] ][0];
		for(int j = 0; j < tt.size(); j++){
			cout << tt[j] << endl;
		}
	}
*/	
	return 0;
}
