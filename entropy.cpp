#include<iostream>
#include<string>
#include<cmath>
#include<fstream>

using namespace std;

int main(int argc, char *argv[]){

	string str = "";

	ifstream inputFile(argv[1]);	
	getline(inputFile,str);
	inputFile.close();

	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	double letterCounts[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double entropy = 0.0;

	for(int a = 0; a < str.length(); a++){
		for(int b = 0; b < 26; b++){
			if(str[a] == alphabet[b]){
				letterCounts[b]++;
			}
		}
	}

	double charAvg = str.length()/26.0;

	for(int i = 0; i < 26; i++){
		entropy += fabs(letterCounts[i]-charAvg);
		//cout << encSum << endl;
	}

	//cout << str.length()/26.0 << endl;
	//cout << encSum << endl;
	
	double entMax = ((25)*charAvg) + str.length() - charAvg;

	cout << "CharAvg  = " << charAvg << endl;
	cout << "Entropy Max = " << entMax << endl;
	cout << "Entropy = " << entropy << endl;
	cout << "Entropy Percent = " << 1-(entropy/entMax) << endl;
	
	return 0;
}
