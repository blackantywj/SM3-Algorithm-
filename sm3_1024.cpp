#include<iostream>
#include <string>
#include <cmath>
using namespace std;
//bin to dec
int BTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		d += (s[i] - '0')*pow(2, s.size() - i - 1);
	}
	return d;
}

//dec to bin
string DTB(int s) {
	string b = "";
	while (s >= 1) {
		b = to_string(s % 2) + b;
		s = s / 2;
	}
	return b;
}
//hex to dec
int HTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A'&&s[i] <= 'F') {
			d += (s[i] - 'A' + 10)*pow(16, s.size() - i - 1);
		}
		else {
			d += (s[i] - '0')*pow(16, s.size() - i - 1);
		}
	}
	return d;
}
//dec to hex
string DTH(int s) {
	string h = "";
	int t = 0;
	while (s >= 1) {
		t = s % 16;
		if (t < 10 && t >= 0) {
			h = to_string(t) + h;
		}
		else {
			h += ('A' + (t - 10));
		}
		s = s / 16;
	}
	return h;
}
//bin to hex
string BTH(string s){ 
    string h = "";
    int t = 0;
    while(s.size() % 4 != 0) {
        s = "0" + s;
    }
    for (int i = 0; i < s.size(); i += 4) {
        t = (s[i] - '0') * 8 + (s[i + 1] - '0') * 4 + (s[i + 2] - '0') * 2 + (s[i + 3] - '0') * 1;
        if(t < 10) {
            h += to_string(t);
        }
        else {
            h += 'A' + (t - 10);
        }
    }
    return h;
}

//hex to bin
string HTB(string s) {
	string b = "";
	string transTab[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A'&&s[i] <= 'F') {
			b += transTab[s[i] - 'A' + 10];
		}
		else {
			b += transTab[s[i] - '0'];
		}
	}
	return b;
}
//Padding
string padding(string s) {
	string r_s = "";
	for (int i = 0; i < s.size(); i++) {
		r_s += DTH((int)s[i]);
	}
	cout << "The ASCII of input string can be represent as :" << endl;
	for (int i = 0; i < r_s.size(); i++) {
		cout << r_s[i];
		if ((i + 1) % 8 == 0) {
			cout << "  ";
		}
		if ((i + 1) % 64 == 0 || (i + 1) == r_s.size()) {
			cout << endl;
		}
	}
	cout << endl;
	int res_length = r_s.size() * 4;
	r_s += "8";
	while (r_s.size() % 128 != 112) {
		r_s += "0";
	}
	string res_len = DTH(res_length);
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	r_s += res_len;
	return r_s;
}

string LeftShift(string str, int len) {//实现循环左移len位功能
	string res = HTB(str);
	res = res.substr(len) + res.substr(0, len);
	return BTH(res);
}

string XOR(string str1, string str2) {//实现异或操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string AND(string str1, string str2) {//实现与操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}

string OR(string str1, string str2) {//实现或操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string NOT(string str) {//实现非操作
	string res1 = HTB(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}
char binXor (char str1, char str2) {//实现单比特的异或操作
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//实现单比特的与操作
	return (str1 == '1'&&str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32运算的函数实现
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BTH(res);
}

string P1(string str) {//实现置换功能P1（X）
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//实现置换功能P0（X）
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//返回Tj常量值的函数实现
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//实现布尔函数FF功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//实现布尔函数GG功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) {//消息扩展函数
	string res = str;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i++) {//根据公式生成第17位到第68位的W值
		res += XOR(XOR(P1(XOR(XOR(res.substr((i-16)*8,8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	cout << "扩展后的消息：" << endl;
	cout << "W0,W1,……,W67的消息：" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << res.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << res.substr(512, 8) << "  " << res.substr(520, 8) << "  " << res.substr(528, 8) << "  " << res.substr(536, 8) << endl;
	cout << endl;
	for (int i = 0; i < 64; i++) {//根据公式生成64位W'值
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	cout << "W0',W1',……,W63'的消息：" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << res.substr(544+i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	return res;
}

string compress(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	cout << "迭代压缩中间值: " << endl;
	cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j%32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string iteration(string str) {
	int num = str.size() / 128;
	cout << "The number of message groups after padding is" + to_string(num) << endl;
	cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		cout << "No. " << to_string(i+1) << " message group：" << endl;
		cout << endl;
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main() {
	string str[2];
	str[0] = "abc";
	str[1] = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
	for (int num = 0; num < 2; num++) {
		cout << "Example " + to_string(num + 1) + " ：The input message is string: " + str[num] << endl;
		cout << endl;
		string paddingValue = padding(str[num]);
		cout << "Message after padding：" << endl;
		for (int i = 0; i < paddingValue.size() / 64; i++) {
			for (int j = 0; j < 8; j++) {
				cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
			}
			cout << endl;
		}
		cout << endl;
		string result = iteration(paddingValue);
		cout << "The value of hash ：" << endl;
		for (int i = 0; i < 8; i++) {
			cout << result.substr(i * 8, 8) << "  ";
		}
		cout << endl;
		cout << endl;
	}
}