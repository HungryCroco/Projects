#pragma once
#include <iostream>
#include "Card.h"
#include "Hand.h"
#include "ComputeOdds.h"
#include <chrono>




int main()
{
    
    auto start = std::chrono::high_resolution_clock::now();

    std::string myHandasString1 = "Jd2h";
    std::string myHandasString2 = "3c2c";

    Hand myHand1(myHandasString1);
    Hand myHand2(myHandasString2);
    
    float odds = ComputeOdds(myHand1, myHand2);
    //long allCombos 
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    //std::cout << myHand1 << " | " << myHand2 << std::endl;
    std::cout << odds << std::endl;
    std::cout << duration.count() << std::endl;

   
     return 0;
}