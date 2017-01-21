//
//  Chromosome.hpp
//  uloha1
//
//  Created by David Ungurean on 28/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#ifndef Chromosome_hpp
#define Chromosome_hpp

#include <stdio.h>
#include "Problem.hpp"

class GAProblem;

class Chromosome {
public:
    Chromosome(const Problem *);
    
    std::vector<bool> data;
    
    double evaluateFitness() const;
    bool isPossible(int & possibleCount) const;
    bool isFormulaPossible(Formula formula) const;
    const Problem * parentProblem;
    
    void mutate();
    void mutate_2();
    
    friend std::ostream & operator<< (std::ostream & os, const Chromosome & problem);
    
    bool operator < (const Chromosome& b) const;
};

#endif /* Chromosome_hpp */
