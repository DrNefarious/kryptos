#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include "analysisTools.h"

using namespace std;

int main(){
	string line = "";
	ifstream input("output.txt");
	ofstream output("output2.txt");
	int totalCount = 0;
	while(getline(input,line)){
		double freqProb = 0.0, freqProb2 = 0.0, freqProb3 = 0.0, freqProb4 = 0.0;
		int count = 0;
		for(int i = 1; i < 11; i++){
			freqProb = indexOfCoincidence(line, i);
			freqProb2 = indexOfCoincidence(line, 2*i);
			freqProb3 = indexOfCoincidence(line, 3*i);
			freqProb4 = indexOfCoincidence(line, 4*i);
			//cout << i << " - " << freqProb;
			if(fabs(freqProb-1.73) < 0.1 && fabs(freqProb2-1.73) < 0.1  && fabs(freqProb3-1.73) < 0.1 && fabs(freqProb4-1.73) < 0.1){
				count=1;
			}
			//cout << endl;
		}
		if(count == 1){output << line << endl;}
		totalCount+=count;
	}
	cout << totalCount << endl;
	input.close();
	output.close();
	return 0;
}
