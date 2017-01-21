//
//  Problem.cpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#include <iostream>
#include "Problem.hpp"
#include "math.h"
#include <chrono>
#include <vector>
#include <random>

#include "Formula.hpp"

using namespace std;

int randomWeightBetween(int a, int b) {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(a, b);
    
    return unif(rng);
}


Problem::Problem(const std::string & filename)
:
    formulas(vector<Formula>())
{
    loadData(filename);
}

void Problem::determineLiteralAndClauseCount(ifstream & infile) {
    string line;
    
    while (getline(infile, line)) {
        istringstream iss(line);
        
        char typeOfLine;
        iss >> typeOfLine;
        
        if (typeOfLine == 'c') { // it's a comment line, we can skip this
            continue;
        }
        
        string dummy;
        
        if (typeOfLine == 'p') { // it's problem's dimension
            iss >> dummy;
            iss >> variablesCount >> formulasCount;
        }
        
        if (typeOfLine == 'w') {
            int dummyInt = 0;
            for (int i = 0; i < variablesCount; i++) {
                iss >> dummyInt;
                weights.push_back(dummyInt);
            }
            
            // now we have finished parsing the problem info
            return;
        }
    }
}

void Problem::readFormulas(ifstream & infile) {
    string line;
    for (int i = 0; i < formulasCount; i++) {
        getline(infile, line);
        istringstream iss(line);
        
        Formula formula;
        
        int number;
        while (iss >> number) {
            if (number == 0) {
                break;
            }
            
            formula.variables.push_back(number);
        }
        
        formulas.push_back(formula);
    }
}


void Problem::loadData(const string & filename) {
    ifstream infile(filename);

    determineLiteralAndClauseCount(infile);
    readFormulas(infile);
}



