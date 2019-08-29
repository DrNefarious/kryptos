#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstring> //for memset
#include<cmath> //for ceil, floor
#include "analysisTools.h"
#include<vector>
#include<ctime>
#include<algorithm>
#include<chrono>
#include<thread>

using namespace std;

string keyTextGen(const string& str, int len){
	string keyText = "";
	int mult = ceil(len*1.0/str.length()*1.0);
	for(int i = 0; i < mult; i++){
		keyText += str;
	}
	return keyText.substr(0,len);
}

void vignere(const string& cipherText, const char* alphabetDir, const char* keyFileName, vector<string>& probWords, int start, int stop, int min_prob){
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
		keyText = keyTextGen(key, cipherText.length());
		
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
		//wordProb = wordAnalysis(plainText, "words.txt", 4);
		if(prob > min_prob){
			wordProb = wordAnalysis(plainText);
			if(wordProb < 10)
				probWords.push_back("0" + to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
			else
				probWords.push_back(to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
		}
		tempCount++;
		if(tempCount == stop) break;
	}//end keyread loop
}

void threadCreator(int maxThreads, const char* keyFileName, const string& cipherText, const char* alphabet, vector<string>& probWords, int& maxLines, int& minprob){
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
		threads.push_back(thread(vignere, ref(cipherText), ref(alphabet), ref(keyFileName), ref(probWords), ref(startPoints[i]), ref(endPoints[i]), ref(minprob) ) );
	}

	for (auto& th : threads) th.join();

}

int main(int argc, char *argv[]){
	
	//declare and initialise variables
	string cipherText, key;
	vector<string> probWords;
	auto ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	if((int)(argv[4][0] - '0') < 1 || (int)(argv[4][0] - '0') > 8){
		cout << "invalid number of threads specified. Enter a number between 1 and 8." << endl;
		exit(1);
	}
	
	//error checking
	if(argc < 6){
		cout << "Incorrect number of arguments. Correct syntax is ./vignere <cipher file> <alphabet file> <key file> <numThreads> <min prob>" << endl;
		exit(1);
	}

	ifstream cipherFile(argv[1]);
	if(!cipherFile.good()){
		cout << argv[1];
		cout << " cannot be found. Exiting..." << endl;
		exit(1);
	}
	getline(cipherFile,cipherText);
	cipherFile.close();

	ifstream alphaFile(argv[2]);
	if(!alphaFile.good()){
		cout << argv[2];
		cout << " cannot be found. Exiting..." << endl;
		exit(1);
	}
	alphaFile.close();

	ifstream keyFile(argv[3]);
	if(!keyFile.good()){
		cout << argv[3];
		cout << " cannot be found. Exiting..." << endl;
		exit(1);
	}

	int maxLines = 0, maxThreads = (int)(argv[4][0] - '0');
	int min_prob1 = (int)(argv[5][0] - '0');
	int min_prob2 = (int)(argv[5][1] - '0');
	
	int min_prob = (min_prob1 * 10) + min_prob2;
	
	while(getline(keyFile, key)){
		maxLines++;	
	}
	keyFile.close();
	
	/* --- DEAL WITH THREADS --- */
	threadCreator(maxThreads,argv[3],cipherText,argv[2],probWords,maxLines,min_prob);
	
	cout << "Time in Milliseconds = " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count() - ms << endl;
	/* --- Sort the List --- */
	sort(probWords.begin(),probWords.end(), greater<string>());

	int maxShow = 0;
	if(probWords.size() < 10) maxShow = probWords.size();
	for(int a = 0; a < maxShow; a++){
		cout << probWords[a] << endl;
	}

	cout << "Time in Milliseconds = " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count() - ms << endl;
	
	return 0;
}
