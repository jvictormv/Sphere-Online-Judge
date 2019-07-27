#include <iostream>
#include <string>

using namespace std;

string initial_palindrome(string k){
	int ndigits = k.length();
	int stop = 0;
	if(ndigits%2==0) stop = ndigits/2;
	else stop = (ndigits-1)/2;
	for(int i=0;i<stop;++i){
		k[ndigits-1-i]=k[i];
	}	
	return k;
}

string next_palindrome(string palindrome){
	
	int ndigits = palindrome.length();
	
	string res;
	if(!palindrome.compare(string(ndigits,'9'))){
		res = string(ndigits+1,'0');
		res[0] = '1';
		res[ndigits] = '1';
		return res;
	}
	
	int i = 0;
	int j = 0;
	int p = 0;
	if(ndigits%2==0){
		i = ndigits/2;
		j = i-1;
		p = 1;
	}
	else{
		i = (ndigits-1)/2;
		j = i;
		p = 0;
	}
	char digit;
	while(true){
		digit = palindrome[i];
		if(digit=='9'){
			palindrome[i]='0';
			palindrome[j]='0';
			++i;
			--j;
			p = 1;
		}
		else{
			palindrome[i] = char(int(palindrome[i])+1);
			palindrome[j] = char(int(palindrome[j])+p);
			break;
		}
	}
	return palindrome;
}

bool GreaterThan(string a, string b){
	
	int alenght = a.length();
	int blenght = b.length();
	if(alenght>blenght) return true;	
	if(alenght<blenght) return false;
	if(!a.compare(b)) return false;

	int inta;
	int intb;
	for(int i=0; i<alenght; ++i){
		inta = a[i]-48;
		intb = b[i]-48;
		if(inta>intb) return true;
		if(inta<intb) return false;
	}
	return false;
}


int main(){
	int n;
	string number;
	cin>>n;
	while(n>0){
		cin>>number;
		string initial_guess = initial_palindrome(number);
		if(GreaterThan(initial_guess,number)) cout<<initial_guess<<endl;
		else cout<<next_palindrome(initial_guess)<<endl;
		--n;
	}
}

