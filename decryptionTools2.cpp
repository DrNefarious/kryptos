#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstring> //for memset
#include<cmath> //for ceil, floor
#include "analysisTools.h"
#include "decryptionTools.h"
#include<vector>
#include<ctime>
#include<algorithm>
#include<chrono>
#include<thread>
#include <functional>

using namespace std;

struct outputs{
	string text;
	string key;
	double letterFreq;
	double wordFreq;
};

string keyTextGen(const string& str, int num, int len){
	string keyText = "";
	for(int i = 0; i < num; i++){
		keyText += str;
	}
	return keyText.substr(0,len);
}

void vignere(const string& cipherText, const string& alphabetDir, const string& keyFileName, vector<outputs>& stats, int start, int stop, int min_prob){ //, int min_prob
	ifstream keyFile(keyFileName);

	string alphabet[26];
	ifstream alphaFile(alphabetDir);
	for(int i = 0; i < 26; i++){
		getline(alphaFile, alphabet[i]);
	}
	alphaFile.close();

	
	string key, keyText;
	int tempCount = 0;
	double prob, wordProb;
	
	if(tempCount != start){
		while(getline(keyFile,key)){
			tempCount++;

			if(tempCount == start){
				break;
			}
		}	
	}
	
	while(getline(keyFile, key)){ //start keyread loop
		string plainText = "";
		keyText = keyTextGen(key, cipherText.length(), cipherText.length());
		
		for(int i = 0; i < cipherText.length(); i++){
			for(int j = 0; j < 26; j++){
				if(alphabet[j][0] == keyText[i]){
					for(int k = 0; k < alphabet[j].length(); k++){
						if(alphabet[j][k] == cipherText[i]){
							plainText += alphabet[0][k];
						}
					}
				}
			}
		}
		
		prob = frequencyAnalysis(plainText); //Do frequency analysis on the plaintext
		if(prob > min_prob){
			wordProb = wordAnalysis(plainText);
			stats.push_back({plainText, key, prob, wordProb});
			//if(wordProb < 10)
				//probWords.push_back("0" + to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
			//else
				//probWords.push_back(to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
		}
		tempCount++;
		if(tempCount == stop) break;
	}//end keyread loop
}


void threadCreator(int maxThreads, const string& keyFileName, const string& cipherText, const string& alphabet, vector<outputs>& stats, int& maxLines, int& minprob){//, int& minprob
	int startPoints[maxThreads], endPoints[maxThreads], lengths[maxThreads], section, maxLengths = 0, tempStart = 0;
	vector<thread> threads;

	for(int i = 0; i < maxThreads; i++){
		lengths[i] = floor(maxLines/maxThreads);
		maxLengths += lengths[i];
	}
	lengths[0] += (maxLines-maxLengths);
	
	for(int i = 0; i < maxThreads; i++){
		startPoints[i] = tempStart;
		tempStart += lengths[i];
		endPoints[i] = tempStart-1;
	}

	for(int i = 0; i < maxThreads; i++){
		threads.push_back(thread(vignere, ref(cipherText), ref(alphabet), ref(keyFileName), ref(stats), ref(startPoints[i]), ref(endPoints[i]), ref(minprob) ) ); //, ref(minprob)
	}

	for (auto& th : threads) th.join();
	
}

void vignereDec(string text, string words, string alphabet, int threads, int min_prob){
	
	//declare and initialise variables
	string cipherText, key;
	cipherText = text;
	vector<string> probWords;
	vector<double> letterFreqs;
	vector<double> wordFreqs;
	vector<outputs> stats;
	
	int maxLines = 0;
	
	ifstream keyFile(words);
	while(getline(keyFile, key)){
		maxLines++;	
	}
	keyFile.close();

	/* --- DEAL WITH THREADS --- */
	threadCreator(threads,words,cipherText,alphabet,stats,maxLines, min_prob); //min_prob
	
	/* --- Sort the List --- */
	sort(stats.begin(),stats.end(), [](auto const &a, auto const &b) { return a.letterFreq > b.letterFreq; });
	cout << "Top 5 letter frequencies: " << endl;
	for(int a = 0; a < 5; a++){
		//cout << probWords[a] << endl;
		cout << stats[a].letterFreq << " - " << stats[a].key << " - " << stats[a].text << endl;
	}
	
	sort(stats.begin(),stats.end(), [](auto const &a, auto const &b) { return a.wordFreq > b.wordFreq; });
	cout << "\nTop 5 word frequencies: " << endl;
	for(int a = 0; a < 5; a++){
		//cout << probWords[a] << endl;
		cout << stats[a].wordFreq << " - " << stats[a].key << " - " << stats[a].text << endl;
	}

}

void singleVignere(string text, string key, string alphabetDir){
	
	string alphabet[26], keyText, plainText = "";
	double prob;
	ifstream alphaFile(alphabetDir);
	for(int i = 0; i < 26; i++){
		getline(alphaFile, alphabet[i]);
	}
	alphaFile.close();

	keyText = keyTextGen(key, text.length(), text.length());
		
	for(int i = 0; i < text.length(); i++){
		for(int j = 0; j < 26; j++){
			if(alphabet[j][0] == keyText[i]){
				for(int k = 0; k < alphabet[j].length(); k++){
					if(alphabet[j][k] == text[i]){
						plainText += alphabet[0][k];
					}
				}
			}
		}
	}
	
	prob = frequencyAnalysis(plainText);

	cout << "\nEnglish probability = " << prob << endl;
	cout << plainText << endl;


}

void vignereEnc(string cipherText, string alphabetfilename, string key){
	string alphabet[26];
	string keyText;
	ifstream alphabetfile(alphabetfilename);
	
	if(key.find(".txt") < key.length()){
		ifstream keyfile(key);
		getline(keyfile,key);
		keyfile.close();
	}
		
	for(int i = 0; i < 26; i++){
		getline(alphabetfile, alphabet[i]);
	}
	alphabetfile.close();

	string plainText = "";
	keyText = keyTextGen(key, cipherText.length(), cipherText.length());
	
	for(int i = 0; i < cipherText.length(); i++){
		for(int j = 0; j < 26; j++){
			if(alphabet[j][0] == keyText[i]){
				for(int k = 0; k < alphabet[j].length(); k++){
					if(alphabet[0][k] == cipherText[i]){
						plainText += alphabet[j][k];
					}
				}
			}
		}
	}
	
	
	cout << plainText << endl;	
}

void transposSolver(string cipherText){
	//Convert string into 2D vector
	string tempText = cipherText;

	vector<vector<char> > vector2D;

	columns = cipherText.length();
	rows = 1;

	for(int i = 0; i < rows; i++){
		vector<char> tempVec;
		for(int j = 0; j < columns; j++){
			tempVec.push_back(' ');
		}
		vector2D.push_back(tempVec);
	}

	vector<char> tempVec;
	for(int i = 0; i < cipherText.length(); i++){
		tempVec.push_back(sample[i]);
	}
	vector2D[0] = tempVec;
	
	//Create an array of all possible actions
	vector<string> actions;
	actions.push_back("r");
	actions.push_back("l");
	//Create an array of all possible permutations of those actions up to a fixed length.
	
}
