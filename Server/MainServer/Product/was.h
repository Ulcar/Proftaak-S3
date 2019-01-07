#ifndef WASH_H
#define WASH_H
#include <vector>
#include "enums.h"
enum Color
{
    Red, Blue, White
};



class Was
{
    private:
    int weight;
    
    
    public:
    Color colorType;
    std::vector<Type> tasksToDo;

    //weight in grams
    int GetWeight();

    Was(int weight);


};


#endif


