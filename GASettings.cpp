//
//  GASettings.cpp
//  uloha1
//
//  Created by David Ungurean on 29/12/2016.
//  Copyright © 2016 ungurean. All rights reserved.
//

#include "GASettings.hpp"

GASettings::GASettings() :
    generationsCount(200),
    populationSize(50),
    mutationProb(0.05),
    crossoverProb(0.75),
    elitistPercentage(0.06),
    elitism(true),
    deathSentence(false),
    tournamentSize(20)
{
    
    
}
