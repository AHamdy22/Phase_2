#pragma once
#include <string>
using namespace std;
class Var_info
{
public:
    string VarName;
    double Value;
    bool IsDeclared;
    bool IsInitialized;

    Var_info();
};

