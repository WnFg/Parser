
#include "need.h"

struct CFG
{
	string S;    //起始符
	vector<string> NT, T;    // 非终结符， 终结符
	vector<string> P, spt;	 // 表达式
	map< string, vector<string> > mp;
	
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

	void split(const string& str){
		int mark;
		bool ok;
		for(mark = 0; mark < NT.size(); mark++){
			if( comp(NT[mark], str, 0) ){
				mp[NT[mark]] = spt;	
				break;
			}
		}

		for(int i = NT[mark].size(); i < str.size(); i++)
		{
			ok = false;
			for(int j = 0; !ok && j < NT.size(); j++)
			{
				if( comp(NT[j], str, i) )
				{
				//	cout << "dsfgwer" << endl;
					mp[NT[mark]].push_back(NT[j] + "`");
					ok = true;
					i += NT[j].size() - 1;
				}	
			}
	//		cout << "sdfwer" << endl;
			for(int j = 0; !ok && j < T.size(); j++)
			{
				if( comp(T[j], str, i) ){
				//	cout << "sdfee" << endl;
					mp[NT[mark]].push_back(T[j]);
					ok = true;
					i += T[j].size() - 1;
				}
			}
		}
	}

	void analysis_P(){
		for(int i = 0; i < P.size(); i++){
			split(P[i]);		
		}
	}
	
};

