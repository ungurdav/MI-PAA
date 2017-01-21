//
//  main.cpp
//  paa_semestral_project
//
//  Created by David Ungurean on 30/12/2016.
//  Copyright © 2016 David Ungurean. All rights reserved.
//

#include <iostream>
#include "Problem.hpp"
#include "GASettings.hpp"
#include "GASolver.hpp"
#include <string> 
#include <algorithm>

using namespace std;

std::vector<Problem> loadData(GASettings settings = GASettings()) {
    vector<Problem> allProblems;
    
    for (int i = 1; i < 4; i++) {
        string filename = "/Users/davidungurean/Dropbox/FIT/mgr/sem1/PAA/report/5_semestralka/src/paa_semestral_project/paa_semestral_project/data/" + to_string(i) + ".txt";
        
        allProblems.push_back(Problem(filename));
    }
    
    return allProblems;
}

int main(int argc, const char * argv[]) {
    GASettings settings;
    
    settings.generationsCount = atoi(argv[1]);
    settings.populationSize = atoi(argv[2]);
    
    settings.mutationProb = atof(argv[3]) / 100.0;
    settings.crossoverProb = atof(argv[4]) / 100.0;
    
    settings.elitism = atoi(argv[5]);
    settings.elitistPercentage = atof(argv[6]) / 100.0;
    
    settings.deathSentence = atoi(argv[7]);
    
    settings.tournamentSize = atof(argv[8]) / 100.0;
    
    auto allProblems = loadData(settings);
    
    vector<double> fitnesses;
    
    for (auto it = allProblems.begin(); it != allProblems.end(); ++it) {
//        errors.push_back(1.0- it->solveGeneticAlgorithm());
        GASolver solver = GASolver(settings, *it);
        
        double val = solver.solveGeneticAlgorithm();
        fitnesses.push_back(val);
    }
    
    //    cout << "FINISHED" << endl;
    cout << settings.tournamentSize << " ";
    cout << *max_element(fitnesses.begin(), fitnesses.end()) << " ";

    double sum = 0;
    for (auto it = fitnesses.begin(); it != fitnesses.end(); ++it) {
        sum += *it;
    }
    
    cout << sum / fitnesses.size() << endl;
    
//    cout << accumulate(errors.begin(), errors.end(), 0.0)/errors.size() << endl;
    
    
    
    return 0;
}
