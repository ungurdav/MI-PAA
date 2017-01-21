//
//  Chromosome.cpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#include "Chromosome.hpp"
#include <iostream>

using namespace std;

double randomNumberBetweenOneAndZero();
bool flipCoin(double probability = 0.5);

// --------------------------------------------------------------------------------------------------------------
// CHROMOSOME
// --------------------------------------------------------------------------------------------------------------
Chromosome::Chromosome(const Problem * problem)
:
parentProblem(problem)
{
    int chromLength = problem->variableCount();
    // init randomly the bool vector
    data = vector<bool>();
    
    for (int i = 0; i < chromLength; i++) {
        data.push_back(flipCoin());
    }
}



void swap(Chromosome& lhs, Chromosome& rhs){
    std::swap(lhs.data, rhs.data);
    std::swap(lhs.parentProblem, rhs.parentProblem);
}

double Chromosome::evaluateFitness() const {
    int maxPossibleSum = 0;
    int trueVariablesSum = 0;
    
    for (int i = 0; i < data.size(); i++) {
        int weight = parentProblem->weightAt(i); // todoo uncomment
        
        maxPossibleSum += weight;
        
        if (data[i]) {
            trueVariablesSum += weight;
        }
    }
    
    
    int trueFormulas;
    bool isEntireFormulaPossible = isPossible(trueFormulas);
    
    double percentageOfPossibleFormulas = (double)trueFormulas / parentProblem->formulaCount();
    
    double fitness = 0;
    
    double isPossibleCoefficient = isEntireFormulaPossible ? 3.0 : percentageOfPossibleFormulas;
    
    fitness = trueVariablesSum * isPossibleCoefficient;
    
    return fitness;
}

bool Chromosome::isPossible(int & possibleCount) const {
    bool totalPossible = true;
    possibleCount = 0;
    
    for (int i = 0; i < parentProblem->formulaCount(); i++) {
        auto formula = parentProblem->formulaAt(i);
        auto isThisFormulaPossible = isFormulaPossible(formula);
        
        totalPossible &= isThisFormulaPossible;
        
        if (isThisFormulaPossible) {
            possibleCount++;
        }
    }
            
    return totalPossible;
}

bool Chromosome::isFormulaPossible(Formula formula) const {
    bool totalFormulaValue = false;
    for (int i = 0; i < formula.variables.size(); i++) {
        int variablePosition = abs(formula.variables[i]) - 1;
        
        totalFormulaValue |= data[variablePosition] == (formula.variables[i] > 0);
    }
    
    return totalFormulaValue;
}


void Chromosome::mutate() {
    for (int i = 0; i < data.size(); i++) {
        if (flipCoin(0.5)) {
            data[i] = !data[i];
        }
    }
}

void Chromosome::mutate_2() {
    int a = data.size() * randomNumberBetweenOneAndZero() - 1;
    int pointOfFlip = min(0 , a);
    
    data[pointOfFlip] = !data[pointOfFlip];
}

bool Chromosome::operator< (const Chromosome & other) const {
    return evaluateFitness() > other.evaluateFitness();
}


ostream & operator<< (ostream & os, const Chromosome & chromosome) {
    for (auto it = chromosome.data.begin(); it != chromosome.data.end(); ++it) {
        os << *it;
    }
    
    os << " fitness: " << chromosome.evaluateFitness() << endl;
    
    return os;
}

