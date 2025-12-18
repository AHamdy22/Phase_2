#ifndef VAR_INFO_H
#define VAR_INFO_H

#include <string>

class Var_info
{
public:
    std::string VarName;
    double Value;
    bool IsDeclared;
    bool IsInitialized;

    Var_info();
};

#endif