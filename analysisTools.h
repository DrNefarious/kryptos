#include<string>
#ifndef ANALYSISTOOLS_H
#define ANALYSISTOOLS_H

double frequencyAnalysis(const std::string& str);
double vowelRatio(const std::string& str);
double wordAnalysis(const std::string& str, int length);
double indexOfCoincidence(const std::string& str, int cols);
double encStrength(const std::string& str);
#endif // ADD_H_INCLUDED 
