//
//  Problem.hpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Formula.hpp"

class Problem {

public:
    // creates new problem from input file
    Problem(const std::string & filename);
    
private:
    int problemId; 
    
    int variablesCount;
    int formulasCount;
    // array of clause in DIMACS CNF format -1 2 3  meaning ( !x1 || x2 || x3 )
    std::vector<Formula> formulas;
    // weights for each literal
    std::vector<int> weights;
    
// getters
public:
    int variableCount() const { return variablesCount; }
    int formulaCount() const { return formulasCount; }
    
    int weightAt(int at) const { return weights[at]; }
    Formula formulaAt(int at) const { return formulas[at]; }
private:
    void loadData(const std::string & filename);
    
    void determineLiteralAndClauseCount(std::ifstream & infile);
    void readFormulas(std::ifstream & infile);
};


#endif /* Problem_hpp */
