//Decryption analysis tools
#include<string>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cmath> //for fabs
#include "analysisTools.h"

using namespace std;

double frequencyAnalysis(const string& str){
	double prob = 0.0;
	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	double letterCounts[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double expectedAlphabetProbs[26] = {8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074};

	for(int a = 0; a < str.length(); a++){
		for(int b = 0; b < 26; b++){
			if(str[a] == alphabet[b]){
				letterCounts[b]++;
			}
		}
	}

	for(int a = 0; a < 26; a++){
		double expLetterCounts = round(expectedAlphabetProbs[a]*(str.length()/100.0));
		double dif = fabs(expLetterCounts - letterCounts[a]);
		prob += dif;
			
	}
	prob = 100.0-((prob/str.length())*100.0);
	
	return prob;
}



double vowelRatio(const string& str){
	double prob = 0.0;
	double vowels = 0.0;

	for(int i = 0; i < str.length(); i++){
		if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U'){
			vowels++;
		}
	}
	prob = vowels/str.length();
	return prob;
}

double wordAnalysis(const string& str, int length){
	double prob = 0.0;
	string word;

	ifstream dictionary("words.txt");
	
	if(!dictionary.good()){
		cout << "Could not open words.txt. Exiting..." << endl;
		exit(1);
	}	

	while(getline(dictionary,word)){
		if(word.length() > length){
			if(str.find(word) != -1) prob = prob + 1.0;
		}
	}

	return prob;
}

double indexOfCoincidence(const string& str, int cols){
	double prob = 0.0;
	double tempProb = 0.0;
	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	double letterCounts[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	string columns[cols];

	for(int a = 0; a < cols; a++){
		columns[a] = "";
		for(int b = a; b < str.length(); b = b + cols){
			columns[a] += str[b];
		}	

		for(int b = 0; b < 26; b++){
			letterCounts[b] = 0;
		}
		

		for(int b = 0; b < columns[a].length(); b++){
			for(int c = 0; c < 26; c++){
				if(columns[a][b] == alphabet[c]){
					letterCounts[c]++;
				}
			}
		}
		
		tempProb = 0.0;

		for(int b = 0; b < 26; b++){
			tempProb += (letterCounts[b])*(letterCounts[b]-1);
		}

		tempProb /= ((columns[a].length())*(columns[a].length()-1))/26.0;
		prob += tempProb;
	
	}

	prob /= cols;

	return prob;
}

double encStrength(const string& str){

	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	double letterCounts[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double expAvg = str.length()/26.0;
	double actAvg = 0.0;
		
	for(int a = 0; a < str.length(); a++){
		for(int b = 0; b < 26; b++){
			if(str[a] == alphabet[b]){
				letterCounts[b]++;
			}
		}
	}

	for(int a = 0; a < 26; a++){
		actAvg+=fabs(letterCounts[a]-expAvg);
	}
	actAvg/=26.0;
	actAvg/=str.length();
	actAvg*=100.0;
	return actAvg;
}


