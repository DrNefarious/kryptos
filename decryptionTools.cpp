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

struct commands{
	string command;
	string variable;
};

string keyTextGen(const string& str, int num, int len){
	string keyText = "";
	for(int i = 0; i < num; i++){
		keyText += str;
	}
	return keyText.substr(0,len);
}

void rotateLeft(vector<vector<char> >& myArray, int& columns, int& rows){
	vector<vector<char> > tempVector2D;
	//cout << "=>Rotating left!" << endl;

	for(int i = columns-1; i > -1; i--){
		vector<char> tempVec;
		for(int j = 0; j < rows; j++){

			tempVec.push_back(myArray[j][i]);
		}
		tempVector2D.push_back(tempVec);
	}

	myArray = tempVector2D;
	int tempInt;
	tempInt = rows;
	rows = columns;
	columns = tempInt;
}

void rotateRight(vector<vector<char> >& myArray, int& columns, int& rows){	
	vector<vector<char> > tempVector2D;
	//cout << "=>Rotating right!" << endl;
	for(int i = 0; i < columns; i++){
		vector<char> tempVec;
		for(int j = rows-1; j > -1; j--){
			tempVec.push_back(myArray[j][i]);
		}
		tempVector2D.push_back(tempVec);
	}

	myArray = tempVector2D;
	int tempInt;
	tempInt = rows;
	rows = columns;
	columns = tempInt;
}

void changeColumns(vector<vector<char> >& myArray, int colsToSet, int& columns, int& rows){
	//cout << "Columns: " << colsToSet << endl;
	vector<vector<char> > tempVector2D;
	vector<char> tempVec;
	int iter = 0, breaks = 0;
	//breaks++;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			tempVec.push_back(myArray[i][j]);
			iter++;
			if(iter == colsToSet){
				iter = 0;
				tempVector2D.push_back(tempVec);
				tempVec.clear();
				breaks++;
			}
		}	
	}

	//cout << iter << endl;
	if(iter != 0){
		breaks++;
	}
	int rem = tempVec.size();
	if(rem < colsToSet){
		for(int i = 0; i < colsToSet - rem; i++){
			tempVec.push_back(' ');
		}
	}
	tempVector2D.push_back(tempVec);

	myArray = tempVector2D;
	columns = colsToSet;
	rows = breaks;
	
}

void vignere(const string& cipherText, const string& alphabetDir, const string& keyFileName, vector<outputs>& stats, int start, int stop, int min_prob, int wordLength){ //, int min_prob
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
		if(prob > min_prob){//min_prob
			wordProb = wordAnalysis(plainText, wordLength);
			if(wordProb > 0) stats.push_back({plainText, key, prob, wordProb});
			//if(wordProb < 10)
				//probWords.push_back("0" + to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
			//else
				//probWords.push_back(to_string(wordProb) + " - " + to_string(prob) + " - " + key + " - " + plainText);
		}
		tempCount++;
		if(tempCount == stop) break;
	}//end keyread loop
}


void threadCreator(int maxThreads, const string& keyFileName, const string& cipherText, const string& alphabet, vector<outputs>& stats, int& maxLines, int& minprob, int& wordLength){//, int& minprob
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
		threads.push_back(thread(vignere, ref(cipherText), ref(alphabet), ref(keyFileName), ref(stats), ref(startPoints[i]), ref(endPoints[i]), ref(minprob),  ref(wordLength) ) ); //, ref(minprob)
	}

	for (auto& th : threads) th.join();
	
}

void vignereDec(string text, string words, string alphabet, int threads, int min_prob, int wordLength){
	
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
	threadCreator(threads,words,cipherText,alphabet,stats,maxLines, min_prob, wordLength); //min_prob
	
	/* --- Sort the List --- */
	if(stats.size() > 1) sort(stats.begin(),stats.end(), [](auto const &a, auto const &b) { return a.letterFreq > b.letterFreq; });
	int maxShow = 10;
	if(stats.size() < 10) maxShow = stats.size();
	cout << "Top 5 letter frequencies: " << endl;
	for(int a = 0; a < maxShow; a++){
		//cout << probWords[a] << endl;
		cout << stats[a].letterFreq << " - " << stats[a].key << " - " << stats[a].text << endl;
	}
	
	if(stats.size() > 1) sort(stats.begin(),stats.end(), [](auto const &a, auto const &b) { return a.wordFreq > b.wordFreq; });
	maxShow = 10;
	if(stats.size() < 10) maxShow = stats.size();
	cout << "\nTop 5 word frequencies: " << endl;
	for(int a = 0; a < maxShow; a++){
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

void transposSolver(string cipherText, int length){
	srand(time(0));
	int columns, rows;
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
		tempVec.push_back(cipherText[i]);
	}
	vector2D[0] = tempVec;
	
	//Create an array of all possible actions
	vector<commands> actions;
	actions.push_back({"rotate","r"});
	actions.push_back({"rotate","l"});

	for(int i = 1; i < cipherText.length()+1; i++){
		if(cipherText.length() % i == 0 && i >= 8 && i <= 45) actions.push_back({"columns", to_string(i)});
	}

	for(int i = 0; i < actions.size(); i++){
		cout << actions[i].command << " - " << actions[i].variable << endl;
	}

	vector<vector<int> > numArrays;
	vector<int> numArray;

	int forVals[length+1];
	int maxVals[length+1];
	int iterator = 0;
	for(int i = 0; i < length; i++){
		if(i % 2 == 0){
			forVals[i] = 2;
			maxVals[i] = actions.size()+1;
		}
		else{
			forVals[i] = 0;
			maxVals[i] = 2;	
		}
	}
	forVals[length] = 0;
	while(forVals[length] == 0){
		numArray.clear();
		for(int i = 0; i < length; i++){
			numArray.push_back(forVals[i]);
		}
		/*
		numArray.push_back(forVals[0]);
		numArray.push_back(forVals[1]);
		numArray.push_back(forVals[2]);
		numArray.push_back(forVals[3]);
		*/
		numArrays.push_back(numArray);

		forVals[0]++;

		while(forVals[iterator] == maxVals[iterator]){
			forVals[iterator] = 0;
			forVals[++iterator]++;
			if(forVals[iterator] != maxVals[iterator]) iterator=0;
		}

	}
	
	vector<vector<char> > tempVector;
	for(int a = 0; a < numArrays.size(); a++){
		//This is the loop that reads and executes each command, needs to be contained in a for loop
		tempVector = vector2D;
		columns = cipherText.length();
		rows = 1;
		for(int i = 0; i < length; i++){
			if(actions[numArrays[a][i]].command == "rotate"){
				if(actions[numArrays[a][i]].variable == "r")
					rotateRight(tempVector, columns, rows);
				else
					rotateLeft(tempVector, columns, rows);
			}
			else if(actions[numArrays[a][i]].command == "columns"){
				changeColumns(tempVector, stoi(actions[numArrays[a][i]].variable), columns, rows);
			}

			double prob;
			string tempString = "";
			for(int j = 0; j < rows; j++){
				for(int k = 0; k < columns; k++){
					if(tempVector[j][k] != ' ') tempString+=tempVector[j][k];
				}
			}
			//cout << tempString << endl;
			prob = wordAnalysis(tempString,5);
			if(prob > 10){
				cout << "Commands: " << endl;
				for(int c = 0; c < length; c++){
					cout << actions[numArrays[a][c]].command << " " << actions[numArrays[a][c]].variable << endl;
				}
				cout << tempString << endl;
				cout << "---" << endl;
			}
			//if(numArrays[a][0] == 7 && numArrays[a][1] == 0 && numArrays[a][2] == 2 && numArrays[a][3] == 0) cout << tempString << endl;
		}

	}
	//Create an array of all possible permutations of those actions up to a fixed length.
	
}
