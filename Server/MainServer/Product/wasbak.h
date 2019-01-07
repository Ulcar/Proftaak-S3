#include <string>
#include <vector>
#include "was.h"

#define MAX_WEIGHT 5000

class Wasbak
{
    private:
    std::string usedClientId;
    bool busy = false;
    bool done = false;

    //weight in grams
    int weightLimit;
    int currentWeight;



   

    public:
    std::vector<Was> wasVector;
    std::vector<Type> tasks;

    std::string GetMacAdress();

    bool GetBusy();
    bool GetDone();

    int GetCurrentWeight();
    Wasbak(std::vector<Type> machines);

    void OnWashFinish(std::vector<Was>& wasToRemove);
    bool AddWasToWasbak(Was was);
  


   

 

};