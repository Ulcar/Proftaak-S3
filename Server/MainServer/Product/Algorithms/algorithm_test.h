#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include "iAlgorithm.h"
#include "database.h"
#include "consoleHandler.h"
#include "client.h"

class Algorithm_test : public iAlgorithm
{
    public:
        Algorithm_test(Database* database);
        ~Algorithm_test();
        void Beat();

    private:
        Database* database;
};

#endif