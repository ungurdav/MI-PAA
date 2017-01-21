//
//  GASolver.cpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#include "GASolver.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>     /* qsort */
#include "Chromosome.hpp"

using namespace std;
// --------------------------------------------------------------------------------------------------------------
// HELPERS
// --------------------------------------------------------------------------------------------------------------
double randomNumberBetweenOneAndZero() {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);
    
    return unif(rng);
}

int randomTournamentSize() {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(2, 10);
    
    return unif(rng);
}

bool flipCoin(double probability = 0.5) {
    return randomNumberBetweenOneAndZero() < probability;
}

template <typename T>
T randomElement(vector<T> vec)
{
    std::random_device seed ;
    
    std::mt19937 engine( seed( ) ) ;
    
    std::uniform_int_distribution<int> choose(0, vec.size() - 1);
    return vec[choose(engine)];
}


int compare(const void * a, const void * b) {
    return ( ((Chromosome*)a)->evaluateFitness() - ((Chromosome*)b)->evaluateFitness() );
}




// --------------------------------------------------------------------------------------------------------------
// GA SOLVER
// --------------------------------------------------------------------------------------------------------------
GASolver::GASolver(GASettings settings, Problem problem)
:
    settings(settings),
    problem(problem)

{
}


void GASolver::initPopulation() {
    population = vector<Chromosome>();
    
    for (int i = 0; i < settings.populationSize; i++) {
        auto chromosome = Chromosome(&problem);
        population.push_back(chromosome);
    }
}

double GASolver::solveGeneticAlgorithm() {
    initPopulation();
    sort(population.begin(), population.end());
    
    for (int i = 0; i < settings.generationsCount; i++) {
        printPopulation(i);
        
        vector<Chromosome> newPopulation;
        
        if (settings.elitism) {
            keepElitists(newPopulation);
        }
        
        crossOver(newPopulation);
        
        mutation(newPopulation);
        
        sort(newPopulation.begin(), newPopulation.end());

        population = newPopulation;
        
        if (population[0].evaluateFitness() == 1.0) {
//            cout << "====FOUND====" << endl;
//            cout << population[0];
            return 1.0;
        }
    }
    return population[0].evaluateFitness();
}

void GASolver::keepElitists(vector<Chromosome> & newPopulation) {
    for (int i = 0; i < settings.elitistPercentage * population.size(); i++) {
        newPopulation.push_back(population[i]);
    }
}

// SELECTION
// --------------------------------------------------------------------------------------------------------------

Chromosome GASolver::tournamentSelection(int participantsCount) {
    vector<Chromosome> participants;
    
    double maxFitness = 0.0;
    int indexOfTopParticipant = 0;
    
    for (int i = 0; i < participantsCount; i++) {
        auto randomParticipant = randomElement(population);
        
        participants.push_back(randomParticipant);
        
        auto fitness = randomParticipant.evaluateFitness();
        
        if (fitness > maxFitness) {
            maxFitness = fitness;
            indexOfTopParticipant = i;
        }
    }
    
    return participants[indexOfTopParticipant];
}

// todo
Chromosome GASolver::rouletteSelection(int participantsCount) {
    return population[0];  // todo
}
Chromosome GASolver::rankBasedSelection(int participantsCount) {
    return population[0]; // todo
}

// CROSSOVER
// --------------------------------------------------------------------------------------------------------------
void GASolver::crossOver(vector<Chromosome> & newPopulation) {
    for (size_t i = newPopulation.size(); i < population.size(); i++) {
        Chromosome parent1 = tournamentSelection(settings.tournamentSize * population.size());//randomTournamentSize());
        Chromosome parent2 = tournamentSelection(settings.tournamentSize * population.size());//randomTournamentSize());
        
        Chromosome child = flipCoin(settings.crossoverProb) ? singlePointCrossover(parent1, parent2) : parent1;
                                //singlePointCrossover(parent1, parent2);
        
        newPopulation.push_back(child);
    }
}

Chromosome GASolver::uniformCrossover(const Chromosome & a, const Chromosome &b) {
    return a; // todo
}

Chromosome GASolver::randomCrossover(const Chromosome & a, const Chromosome &b) {
    Chromosome child = a;
    
    for (int i = 0; i < a.data.size(); i++) {
        child.data[i] = flipCoin() ? a.data[i] : b.data[i];
    }
    
    
    return child;
}

Chromosome GASolver::singlePointCrossover(const Chromosome & a, const Chromosome &b) {
    Chromosome child = a;
    
    int pointOfCut = a.data.size() * randomNumberBetweenOneAndZero();
    
    for (int i = 0; i < pointOfCut; i++) {
        child.data[i] = b.data[i];
    }
    
    return child;
}

// MUTATION
// --------------------------------------------------------------------------------------------------------------
void GASolver::mutation(vector<Chromosome> & newPopulation) {
    for (int i = settings.elitistPercentage * population.size() + 1; i < newPopulation.size(); i++) {
        if (flipCoin(settings.mutationProb)) {
            newPopulation[i].mutate();
        }
    }
}

void GASolver::printPopulation(int generation) {
    double avg = averageFitness();
    double max = maxFitness();
    
    cout << generation << " " << avg << " " << max << endl;
    
    for (auto it = population.begin(); it != population.end(); ++it) {
        cout << *it;
    }
}


double GASolver::averageFitness() const {
    double totalFitnes = 0.0;
    
    for (int i = 0; i < population.size(); i++) {
        totalFitnes += population[i].evaluateFitness();
    }

    return totalFitnes/population.size();
}

double GASolver::maxFitness() const {
    return population[0].evaluateFitness();
}







