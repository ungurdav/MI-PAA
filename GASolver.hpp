//
//  GASolver.hpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#ifndef GAProblem_hpp
#define GAProblem_hpp

#include <stdio.h>
#include "Problem.hpp"
#include "Chromosome.hpp"
#include "GASettings.hpp"

class Chromosome;

class GASolver {
public:
    GASolver(GASettings settings, Problem problem);
    
    // main
    double solveGeneticAlgorithm();
    
    // process
    void initPopulation();
    void crossOver(std::vector<Chromosome> & newPopulation);
    void mutation(std::vector<Chromosome> & newPopulation);
    void keepElitists(std::vector<Chromosome> & newPopulation);
    
    // selection
    Chromosome tournamentSelection(int tournamentSize);
    Chromosome rouletteSelection(int participantsCount);
    Chromosome rankBasedSelection(int participantsCount);
    
    // crossover
    Chromosome uniformCrossover(const Chromosome & a, const Chromosome &b);
    Chromosome randomCrossover(const Chromosome & a, const Chromosome &b);
    Chromosome singlePointCrossover(const Chromosome & a, const Chromosome &b);
    
    
    // info
    double maxFitness() const;
    double averageFitness() const;
    
private:
    const GASettings settings;
    const Problem problem;
    
    std::vector<Chromosome> population;
    
    // debugging helpers
public:
    void printPopulation(int generation);
};

#endif /* GAProblem_hpp */
