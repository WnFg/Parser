#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
#include "need.h"
#include "mylist.h"
#include "hashSet.h"
#define VList vector<my_List<string> > 

struct CFG
{	
	string S;    //起始符
	vector<string> newNT, NT, T;    // 非终结符， 终结符
	vector<string> P, spt;	 // 表达式
	map< string, vector<my_List<string> > > exp;
	map< string, vector<vector<string> > > mp;
	hashSet *hSet;

	CFG(){
		hSet = new hashSet(1013);
		
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

	void analysis_P();      // 把一个表达式分解为： 一a个非终结符  -> 终结符或非终结符的串
		
	void emilite(string& nt);   // 消除直接左递归
	
	void replace();		//  消除左递归
	
	void markEmpty();   // 记录那些具有空串的非终结符

	void extractLeftFactor();   // 提取左因子 
	
	VList __replace(string& nt, my_List<string>& ls);
};

void CFG::extractLeftFactor()
{
	queue<string> Que;
	for(int i = 0; i < NT.size(); i++)
		Que.push(NT[i]);

	while(!Que.empty()){
		string &nt = Que.front();
		Que.pop();
		VList &ep = exp[nt];
		if(ep.size() == 1) continue;
		sort(ep.begin(), ep.end());
		
		my_List<string> sb;
		sb.add(new Node<string>("^!@(&"), 1);
		ep.push_back(sb);

		string newnt = nt + "!";
		int cnt = 0;
		bool isEmpty = false;
		VList vls1, vls2;
		
		for(int i = 1; i < ep.size(); i++){
			
			if(ep[i - 1].size == 0) {vls2.push_back(*(new my_List<string>)); continue;}

			Node<string> *p1 = ep[i - 1].head;
			Node<string> *p2 = ep[i].head;

			my_List<string> *ret = new my_List<string>(&ep[i - 1]);
			ret->del(ret->head->next);
			if(ret->size > 0)
				vls1.push_back(*ret);
			else
				isEmpty = true;
			
			if(p1->next->v == p2->next->v){
				cnt++;
			}else{
				if(cnt > 0){
					Que.push(newnt);
					newNT.push_back(newnt);
					if(isEmpty)
					{
						vls1.push_back(*(new my_List<string>));
						hSet->insert(newnt);
					}
					exp[newnt] = vls1;
					my_List<string> *tt = new my_List<string>;		
					tt->add(new Node<string>(p1->next->v), 1);
					tt->add(new Node<string>(newnt), 1);
					vls2.push_back(*tt);
					
					newnt += "!";
					cnt = 0;
				}else{
					vls2.push_back(new my_List<string>(&ep[i - 1]));
				}
				isEmpty = false;
				vls1.clear();
			}
		}
		exp[nt].clear();
		exp[nt] = vls2;
	}
	NT.insert(NT.end(), newNT.begin(), newNT.end());
	newNT.clear();
}

void CFG::markEmpty()
{
	for(int i = 0; i < NT.size(); i++){
		VList &ep = exp[NT[i]];
		for(int j = 0; j < ep.size(); j++)
			if(ep[j].size == 0){
				hSet->insert(NT[i]);
				break;
			}
	}
}

VList CFG::__replace(string& nt, my_List<string>& ls){
	VList ans;
	VList &ret = exp[nt];
	for(int i = 0; i < ret.size(); i++){
		my_List<string> *a = new my_List<string>(&ls);
	
		a->del(a->head->next);
	
		a->add(&ret[i], 0);
		
		ans.push_back(*a);
	}	
//	VList &a = exp[nt];
	delete_list(&ls);
	return ans;
}

void CFG::emilite(string& nt){
	vector<my_List<string> > &vc = exp[nt];
	VList ret;
	bool *isA = new bool[vc.size()];
	bool ok = false;
	for(int i = 0; i < vc.size(); i++){
		if(vc[i].head->next->v == nt)
			isA[i] = true;
		else
			isA[i] = false;
		ok |= isA[i];
	}
	if(!ok) return ;
	string A1 = nt + "!";
	newNT.push_back(A1);
	VList vls;
	for(int i = 0; i < vc.size(); i++){
		if(!isA[i]){
			my_List<string> ls;
		
			ls.add(&vc[i], 1);
			
			ls.add(new Node<string>(A1), 1);
			
			vls.push_back(ls);
		}else{
		    vc[i].del(vc[i].head->next);
			my_List<string> *p = new my_List<string>(&vc[i]);
			p->add(new Node<string>(A1), 1);
			exp[A1].push_back(*p);
		}
		delete_list(&vc[i]);
	}
	exp[A1].push_back(new my_List<string>);
	exp[nt] = vls;
}

void CFG::replace()
{
	for(int i = 0; i < NT.size(); i++){
		emilite(NT[i]);
		VList &a = exp[NT[0]];

		for(int j = i + 1; j < NT.size(); j++){
			vector<my_List<string> > &vc = exp[NT[j]];
			VList vls;
				
			for(int k = 0; k < vc.size(); k++){
				Node<string> *nd = vc[k].head->next;
				if(nd->v == NT[i]) {
					VList ret = __replace(NT[i], vc[k]);
					vls.insert(vls.end(), ret.begin(), ret.end());
				}else{
					vls.push_back(vc[k]);
				}
			}
			vc = vls;
		}	
	}
	NT.insert(NT.end(), newNT.begin(), newNT.end());
	newNT.clear();
}

void CFG::analysis_P(){      // 把一个表达式分解为： 一a个非终结符  -> 终结符或非终结符的串
	for(int i = 0; i < (int)P.size(); i++){
		split(P[i]);		
		}
	for(int i = 0; i < (int)NT.size(); i++){
		for(int j = 0; j < mp[NT[i]].size(); j++){
			my_List<string> *lst = new my_List<string>;
			for(int k = 0; k < mp[NT[i]][j].size(); k++)
			{
				lst->add(new Node<string>(mp[NT[i]][j][k]), 1);
			}
			exp[NT[i]].push_back(*lst);
		}
	}
	mp.clear();
}

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
				mp[NT[mark]][size].push_back(NT[j]);
				ok = true;
				i += NT[j].size() - 1;
			}	
		}
		for(int j = 0; !ok && j < (int)T.size(); j++)
		{
			if( comp(T[j], str, i) ){
				mp[NT[mark]][size].push_back(T[j] + "`");
				ok = true;
				i += T[j].size() - 1;
			}
		}
	}
}

CFG *cfg = new CFG;
int main()
{
//	test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cfg->analysis_P();
	cfg->replace();
	cfg->extractLeftFactor();
	cout << " ~~~~~~~~~~~~~~~~~~~~ " << endl;
	for(int i = 0; i < cfg->NT.size(); i++){
		VList &ret = cfg->exp[cfg->NT[i]];
		for(int j = 0; j < ret.size(); j++){
			Node<string> *p = ret[j].head;
			cout << cfg->NT[i] << "->";
			while(p->next != NULL){
				cout << p->next->v << " ";
				p = p->next;
			}
			cout << (bool)cfg->hSet->hasEmpty(cfg->NT[i]) << endl;
		}
	}
	return 0;
}
