#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(){

	string sample = "FTSMBBDXXSK";

	string input = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFDVFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKKDQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVHDWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZFKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETGENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW";
	vector<vector<int> > positions;
	vector<int> tempVec;
	for(int i = 0; i < 5; i++){
		positions.push_back(tempVec);
	}
	
	vector<vector<int> > difs;
	for(int i = 0; i < 4; i++){
		difs.push_back(tempVec);
	}


	for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < 5; j++){
			if(input[i] == sample[j]){
				positions[j].push_back(i);
			}
		}
	}

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < positions[i].size(); j++){
			for(int k = 0; k < positions[i+1].size(); k++){
				int x = positions[i+1][k] - positions[i][j];
				if(x < 0) x+= 768;
				difs[i].push_back(x);
			}
		}
	}

	cout << difs[0][0] << endl;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < difs[i].size(); j++){
			cout << difs[i][j] << " ";		
		}
		cout << endl;
	}

	return 0;
}
