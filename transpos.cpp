//Read in words from the dictionary
//Work out letter orders
//Work out repeats
//Work out the columns lengths
//Write the letters into the appropriate columns
//Re-sort the columns
//Read back into plaintext

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath> // for floor

using namespace std;

void getColOrder(string line, vector<int>& colOrders, vector<int>& colOrdersRepeats){

	for(int i = 0; i < colOrders.size(); i++){
		for(int j = 0; j < colOrders.size(); j++){
			if(line[i] > line[j] && i != j){
				colOrders[i]++;
			}
			if(line[i] == line[j] && i > j){
				colOrders[i]++;
			}
			if(line[i] == line[j] && i < j){
				colOrdersRepeats[i]++;
			}
		}	
	}

}

int main(){
	
	ifstream wordFile("words.txt");
	ifstream textFile("k4.txt");
	ofstream outfile("output.txt");
	string line, encText;

	getline(textFile,encText);
	//cout << encText.length() << endl;
	textFile.close();
	

	while(getline(wordFile,line)){ //main loop
		//declare variables
		vector<int> colOrder;
		vector<int> colOrderRepeats;
		vector<int> colOrderRepeatsAfter;
		vector<vector<char> > charCols;
		vector<vector<char> > charColsAfter;
		string finalText = "";

		vector<int> colLengths;
		vector<int> colLengthsAfter;
		int stdColLength = floor(encText.length()/line.length());
		int colsLonger = encText.length() % line.length();

		for(int i = 0; i < line.length(); i++){//Initialise variables
			colOrder.push_back(0);
			colOrderRepeats.push_back(0);
			colOrderRepeatsAfter.push_back(0);
			colLengths.push_back(stdColLength);
			colLengthsAfter.push_back(0);
			if(i < colsLonger) colLengths[i]++;
		}

		getColOrder(line,colOrder,colOrderRepeats); //get colOrder and colOrderRepeats
		
		for(int i = 0; i < colOrder.size(); i++){
			for(int j = 0; j < colOrder.size(); j++){
				if(colOrder[j] == i){
					colLengthsAfter[i] = colLengths[j];
					colOrderRepeatsAfter[i] = colOrderRepeats[j];
				}
			}
		}



		int charIter = 0;
		for(int i = 0; i < colOrder.size(); i++){
			if(colOrderRepeatsAfter[i] == 0){
				vector<char> tempVec;

				for(int j = 0; j < colLengthsAfter[i]; j++){
					tempVec.push_back(encText[charIter]);
					//charCols[i].push_back(encText[charIter+j]);
					charIter++;
				}
				charCols.push_back(tempVec);
			}
			else{

				int sum = 0;
				for(int j = i; j < i + colOrderRepeatsAfter[i]+1; j++){
					sum += colLengthsAfter[j];
				}

				for(int j = 0; j < colOrderRepeatsAfter[i]+1; j++){

					vector<char> tempVec;
					for(int k = charIter+j; k < charIter+sum; k=k+colOrderRepeatsAfter[i]+1){
						//cout << k << endl;
						tempVec.push_back(encText[k]);
					}
					charCols.push_back(tempVec);
				}
				charIter+=sum;
				i+=colOrderRepeatsAfter[i];
			}		
		}

		
		for(int i = 0; i < colOrder.size(); i++){
			charColsAfter.push_back(charCols[colOrder[i]]);
		}
		/*
		cout << "(";
		for(int i = 0; i < colOrder.size(); i++){
			cout << colOrder[i] << ", ";
		}
		cout << ")" << endl;

		cout << "(";
		for(int i = 0; i < colOrder.size(); i++){
			cout << colOrderRepeats[i] << ", ";
		}
		cout << ")" << endl;

		cout << "(";
		for(int i = 0; i < colOrder.size(); i++){
			cout << colOrderRepeatsAfter[i] << ", ";
		}
		cout << ")" << endl;
		
		cout << "(";
		for(int i = 0; i < colOrder.size(); i++){
			cout << colLengths[i] << ", ";
		}
		cout << ")" << endl;

		cout << "(";
		for(int i = 0; i < colOrder.size(); i++){
			cout << colLengthsAfter[i] << ", ";
		}
		cout << ")" << endl;

		cout << encText << endl;
		
		for(int i = 0; i < colOrder.size(); i++){
			for(int j = 0; j < charCols[i].size(); j++){
				cout << charCols[i][j];
			}
			cout << endl;
		}
		cout << endl;

		for(int i = 0; i < colOrder.size(); i++){
			for(int j = 0; j < charColsAfter[i].size(); j++){
				cout << charColsAfter[i][j];
			}
			cout << endl;
		}
		*/
		for(int i = 0; i < charColsAfter[0].size(); i++){
			for(int j = 0; j < colOrder.size(); j++){
				if(charColsAfter[j].size() > i)	finalText += charColsAfter[j][i];
			}
		}
		
		outfile << finalText << endl;
		
	}//end of while
	
	wordFile.close();
	outfile.close();
	return 0;
}
