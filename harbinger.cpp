#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<vector>
#include "analysisTools.h"
#include "decryptionTools.h"
#include<cmath>

using namespace std;

/*void rotateLeft(vector<vector<char> >& myArray,int len, int& columns, int& rows){
	vector<vector<char> > tempVector2D;
	cout << "=>Rotating left!" << endl;

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

void rotateRight(vector<vector<char> >& myArray,int len, int& columns, int& rows){	
	vector<vector<char> > tempVector2D;
	cout << "=>Rotating right!" << endl;
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

	cout << breaks << endl;
	myArray = tempVector2D;
	columns = colsToSet;
	rows = breaks;
	
}*/

void reverse(vector<vector<char> >& myArray, int& columns, int& rows){
	string tempString = "";
	string tempString2 = "";
	int colNos = columns;
	
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(myArray[i][j] != ' ') tempString+=myArray[i][j];
		}
	}
	
	tempString2 = tempString;
	vector<vector<char> > tempVector;
	vector<char> tempVec;
	
	for(int i = 0; i < tempString.length(); i++){
		tempString2[i] = tempString[tempString.length() - 1 - i];
		tempVec.push_back(tempString2[i]);
	}
	
	tempVector.push_back(tempVec);
	
	columns = tempString.length();
	rows = 1;
	
	changeColumns(tempVector,colNos,columns,rows);
	
	myArray = tempVector;
	
}

void fixv(vector<vector<char> >& myArray, int& columns, int& rows){
	string tempString = "";
	string tempString2 = "";
	
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			if(myArray[j][i] != ' ') tempString+=myArray[j][i];
		}
	}
	
	tempString2 = tempString;
	vector<vector<char> > tempVector;
	vector<char> tempVec;
	
	for(int i = 0; i < tempString.length(); i++){
		tempVec.push_back(tempString[i]);
	}
	
	tempVector.push_back(tempVec);
	
	columns = tempString.length();
	rows = 1;
	
	myArray = tempVector;
	
}

void fixh(vector<vector<char> >& myArray, int& columns, int& rows){
	string tempString = "";
	string tempString2 = "";
	
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(myArray[i][j] != ' ') tempString+=myArray[i][j];
		}
	}
	
	tempString2 = tempString;
	vector<vector<char> > tempVector;
	vector<char> tempVec;
	
	for(int i = 0; i < tempString.length(); i++){
		tempVec.push_back(tempString[i]);
	}
	
	tempVector.push_back(tempVec);
	
	columns = tempString.length();
	rows = 1;
	
	myArray = tempVector;
	
}

void load(vector<vector<char> >& myArray, string newSample, int& columns, int& rows){
	if(newSample.find(".txt") < newSample.length()){
		ifstream input(newSample);
		getline(input,newSample);
		input.close();		
	}
	
	vector<vector<char> > tempVector;
	vector<char> tempVec;
	
	for(int i = 0; i < newSample.length(); i++){
		tempVec.push_back(newSample[i]);
	}
	
	tempVector.push_back(tempVec);
	
	columns = newSample.length();
	rows = 1;
	
	myArray = tempVector;

}

int main(int argc, char *argv[]){
	string sample;
	ifstream sampleFile(argv[1]);
	string command = "";
	int columns, rows;

	if(sampleFile.good()){
		getline(sampleFile,sample);
	}else{
		cout << argv[1] << " cannot be opened. Exiting..." << endl;
		exit(1);
	}

	char sampleText[sample.length()][sample.length()];
	vector<vector<char> > vector2D;
	
	columns = sample.length();
	rows = 1;

	for(int i = 0; i < rows; i++){
		vector<char> tempVec;
		for(int j = 0; j < columns; j++){
			tempVec.push_back(' ');
		}
		vector2D.push_back(tempVec);
	}
	
	vector<char> tempVec;
	for(int i = 0; i < sample.length(); i++){
		tempVec.push_back(sample[i]);
	}

	vector2D[0] = tempVec;
	

	do{
		cout << "---------------" << endl;


		for(int i = 0; i < rows; i++){
				for(int j = 0; j < columns; j++){
					cout << vector2D[i][j];
				}
				cout << endl;
		}
		cout << "Rows: " << rows << " \tColumns: " << columns << endl;

		cout << "\nCommand: ";
		cin >> command;

		if(command.find("rotate") < command.length()){
			cout << "Direction?: ";
			cin >> command;
			if(command.find("l") < command.length()) rotateLeft(vector2D,columns,rows);
			if(command.find("r") < command.length()) rotateRight(vector2D, columns, rows);
		}
		else if(command.find("column") < command.length()){
			cout << "Number of columns?: ";
			int cols;
			cin >> cols;
			changeColumns(vector2D, cols, columns, rows);
		}
		else if(command.find("reverse") < command.length()){
			cout << "=>Reversing columns" << endl;
			reverse(vector2D,columns,rows);
		}
		else if(command.find("fixv") < command.length()){
				cout << "=>Removing columns" << endl;
				fixv(vector2D, columns, rows);
		}
		else if(command.find("fixh") < command.length()){
				cout << "=>Removing columns" << endl;
				fixh(vector2D, columns, rows);
		}
		else if(command.find("vigdecbrute") < command.length()){
			
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			string dictionary = "words.txt";
			string alphabet = "ka.txt";
			int threads = 0;
			cout << "Number of threads: ";
			cin >> threads;
			int minProb;
			cout << "\nMinimum probability: ";
			cin >> minProb;
			int minWordProb = 0;
			cout << "\nMin word length: " << endl;
			cin >> minWordProb;
			cout << "\n\n=>Attempting vignere decryption" << endl;
			vignereDec(tempString, dictionary, alphabet, threads, minProb, minWordProb);
		}
		else if(command.find("vigdecword") < command.length()){
			
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			string key;
			cout << "Keyword: ";
			cin >> key;
			string alphabet = "ka.txt";
			cout << "=>Attempting vignere decryption" << endl;
			singleVignere(tempString, key, alphabet);
		}
		else if(command.find("charfreq") < command.length()){
			cout << "=>Alphabet frequency analysis" << endl;
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			double freqProb = 0.0;
			freqProb = frequencyAnalysis(tempString);
			cout << "English = " << freqProb << endl;
		}
		else if(command.find("wordfreq") < command.length()){
			cout << "Min word length: " << endl;
			int length = 0;
			cin >> length;
			cout << "=>Alphabet frequency analysis" << endl;
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			double freqProb = 0.0;
			freqProb = wordAnalysis(tempString, length);
			cout << "Words = " << freqProb << endl;
		}
		else if(command.find("ioc") < command.length()){
			cout << "Start column? " << endl;
			string tempString = "";
			int colsStart;
			int colsEnd;
			cin >> colsStart;
			cout << "End column? " << endl;
			cin >> colsEnd;
			cout << "=>Calculating iocs" << endl;
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			double freqProb = 0.0;
			for(int i = colsStart; i < colsEnd+1; i++){
				freqProb = indexOfCoincidence(tempString, i);
				cout << i << " - " << freqProb;
				if(fabs(freqProb-1.73) < 0.1) cout << " <=!!!";
				cout << endl;
			}
			
		}
		else if(command.find("vigenc") < command.length()){
			string alphabetFile, key;
			//cout << "Alphabet File?: " << endl;
			//cin >> alphabetFile;
			alphabetFile = "ka.txt";
			cout << "Key: " << endl;
			cin >> key;
			cout << "=>Starting vignere encryption..." << endl;
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			vignereEnc(tempString, alphabetFile, key);
		}
		else if(command.find("load") < command.length()){
			string fileName;
			cin >> fileName;

			load(vector2D, fileName, columns, rows);
		}
		else if(command.find("transposdec") < command.length()){
			int numCommands;
			cout << "Number of commands: ";
			cin >> numCommands;
			cout << "Starting transposition solver..." << endl;
			string tempString = "";
			for(int i = 0; i < columns; i++){
				for(int j = 0; j < rows; j++){
					if(vector2D[j][i] != ' ') tempString+=vector2D[j][i];
				}
			}
			transposSolver(tempString, numCommands);
		}
		else if(command.find("route") < command.length()){
			
		}
	}while(command.find("quit") > command.length());

	return 0;
}
