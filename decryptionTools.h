#include<string>
#include<vector>
#ifndef DECRYPTIONTOOLS_H
#define DECRYPTIONTOOLS_H
using namespace std;

void vignereDec(string text, string words, string alphabet, int threads, int min_prob, int wordLength);
void singleVignere(string text, string key, string alphabetDir);
void vignereEnc(string cipherText, string alphabetfilename, string keyfilename);
void transposSolver(string cipherText, int length);
void rotateRight(vector<vector<char> >& myArray, int& columns, int& rows);
void rotateLeft(vector<vector<char> >& myArray, int& columns, int& rows);
void changeColumns(vector<vector<char> >& myArray, int colsToSet, int& columns, int& rows);

#endif // ADD_H_INCLUDED 
