#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

map<char, int> charToint = {{'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9}};
map<int, string> intTostring = {{0,"0"},{1,"1"},{2,"2"},{3,"3"},{4,"4"},{5,"5"},{6,"6"},{7,"7"},{8,"8"},{9,"9"}};


string& completeWithEmptyStrings(string& str, int lenght){
	
	int i = lenght - str.length();
	while(i>0){
		str = str.insert(0," ");
		--i;
	}
	return str;
}

string addition(const string& left, const string& right){
	
	int i = left.length()-1;
	int j = right.length()-1;
	int carry = 0;
	string sum;
	while(i>=0 || j>=0){
		int adigit = 0;
		int bdigit = 0;
		if(i>=0) adigit = charToint[left[i]];
		if(j>=0) bdigit = charToint[right[j]];
		int s = adigit + bdigit + carry;
		sum = sum.insert(0,intTostring[s%10]);
		--i;
		--j;
		carry = s/10;
	}
	if(carry!=0) sum = sum.insert(0,intTostring[carry]);
	return sum;
}

string substraction(const string& left, const string& right){
	
	int i = left.length()-1;
	int j = right.length()-1;
	int carry = 0;
	string diff;
	while(i>=0 || j>=0){
		int adigit = 0;
		int bdigit = 0;
		if(i>=0) adigit = charToint[left[i]];
		if(j>=0) bdigit = charToint[right[j]];
		int s = adigit - bdigit + carry;
		if(s<0){
			s += 10;
			carry = -1;
		}
		else carry = 0; 
		diff = diff.insert(0,intTostring[s]);
		--i;
		--j;
	}
	
	char digit = diff[0];
	while(digit=='0'){
		diff = diff.erase(0,1);
		digit = diff[0];
	}
	
	return diff;
}

vector<string> factors(const string& left, const string& right){
	
	int i = left.length()-1;
	int j = right.length()-1;
	vector<string> prods;
	string subprod;
	int adigit, bdigit, p, carry;
	for(int k = right.length()-1; k>=0; --k){
		adigit = charToint[right[k]];
		if(adigit==0){
			prods.push_back("0");
			continue;
		} 
		carry = 0;
		subprod = "";
		for(int l = left.length()-1; l>=0; --l){
			bdigit = charToint[left[l]];
			p = adigit * bdigit + carry;
			subprod = subprod.insert(0,intTostring[p%10]);
			--i;
			--j;
			carry = p/10;
		}
		if(carry!=0) subprod = subprod.insert(0,intTostring[carry%10]);
		prods.push_back(subprod);
	}
	return prods;
}

void display(string& left, string& operation, string& right, string& result){
	
	right = right.insert(0,operation);
	
	int dashLenght = right.length() > result.length() ? right.length() : result.length();
	int maxLenght = dashLenght > left.length() ? dashLenght : left.length();
	string dashes = string(dashLenght,'-');
	
	left = completeWithEmptyStrings(left,maxLenght);
	right = completeWithEmptyStrings(right,maxLenght);	
	dashes = completeWithEmptyStrings(dashes,maxLenght);
	result = completeWithEmptyStrings(result,maxLenght);
				
	cout<<left<<endl;
	cout<<right<<endl;
	cout<<dashes<<endl;
	cout<<result<<endl;
}

void display(string& left, string&  operation, string& right, vector<string> factors, string& sumfactors){
	
	right = right.insert(0,"*");
	
	int maxLength1 = sumfactors.length() > right.length() ? sumfactors.length() : right.length();
	int dashLenght0 = right.size() > factors[0].length() ? right.size() : factors[0].length();
	string dashes = string(dashLenght0,'-');
	
	cout<<completeWithEmptyStrings(left,maxLength1)<<endl;
	cout<<completeWithEmptyStrings(right,maxLength1)<<endl;
	cout<<completeWithEmptyStrings(dashes,maxLength1)<<endl;
	
	int lastProdLenght;
	for(int p = 0; p<factors.size(); ++p){
		string prod = factors[p];
		prod = factors[p]+string(p,' ');
		if(p==factors.size()-1) lastProdLenght = prod.length();
		cout<<completeWithEmptyStrings(prod,maxLength1)<<endl;
	}
	if(factors.size()>1){
		int dashLenght1 = lastProdLenght > sumfactors.length() ? lastProdLenght : sumfactors.length();
		dashes = string(dashLenght1,'-');
		cout<<completeWithEmptyStrings(dashes,maxLength1)<<endl;
		cout<<completeWithEmptyStrings(sumfactors,maxLength1)<<endl;	
	}
}

int main(){
	
	int n;
	string expression;
	cin>>n;
	while(n>0){
		cin>>expression;
		
		size_t ss = expression.find("+");
		size_t dd = expression.find("-");
		size_t pp = expression.find("*");
		
		size_t i = 0;
		int operation=0;
		if(ss!=string::npos){
			i = ss;
			string left = expression.substr(0,i);
			string right = expression.substr(i+1,expression.length()-i);
			string sum = addition(left,right);
			string operation = "+";
			display(left,operation,right,sum);
			cout<<endl;
		}
		if(dd!=string::npos){
			i = dd;
			string left = expression.substr(0,i);
			string right = expression.substr(i+1,expression.length()-i);
			string diff = substraction(left, right);
			string operation = "-";
			display(left,operation,right,diff);
			cout<<endl;
		}
		if(pp!=string::npos){
			i = pp;
			string left = expression.substr(0,i);
			string right = expression.substr(i+1,expression.length()-i);
			vector<string> prods = factors(left, right);
			
			string sum = prods[0];
			string subprod;
			for(int m = 1; m<prods.size(); ++m){
				subprod = prods[m]+string(m,'0');
				sum = addition(sum,subprod);
			}		
			string operation = "*";
			display(left,operation,right,prods,sum);
			cout<<endl;
		}
		--n;
	}
}
