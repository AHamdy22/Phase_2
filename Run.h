#ifndef RUN_H
#define RUN_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Validate.h"
#include <string>
using namespace std;

class Run : public Action
{
public:

    Run(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
    virtual void Execute();

};

#endif