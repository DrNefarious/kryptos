#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
	
	ifstream dictionary("words.txt");
	ofstream output("words_4.txt");
	string line;
	
	while(getline(dictionary,line)){
		if(line.length() == 4){
			output << line << endl;
		}
	}
	
	dictionary.close();
	output.close();	
	
	return 0;
}
