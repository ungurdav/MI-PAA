//
//  GASettings.hpp
//  uloha1
//
//  Created by David Ungurean on 29/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#ifndef GASettings_hpp
#define GASettings_hpp

#include <stdio.h>

struct GASettings {
    GASettings();
    
    int generationsCount;
    int populationSize;
    
    double mutationProb;
    double crossoverProb;
    
    bool elitism;
    double elitistPercentage;
    
    bool deathSentence;
    
    double tournamentSize; // in percentage of population
};

#endif /* GASettings_hpp */
