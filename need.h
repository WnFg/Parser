#ifndef NEED
#define NEED
bool comp(const string& s1, const string& s2, int ii){      // 检查s1是否为字符串s2[ii]~s2[s2.size()]的前缀
	int i, j;
	if(ii + s1.size() > s2.size()) return false;
	//cout << "sdfgwert" << endl;
	for(i = 0, j = ii; i < s1.size(); i++, j++){
		if(s1[i] != s2[j])
			return false;
	}
	return true;
}
#endif

