//#ifndef VALIDATE_H
//#define VALIDATE_H
//
//#include "Actions\Action.h"
//#include "Statements\Statement.h"
//#include "Conditional.h" 
//#include <string>
//using namespace std;
//
//class Validate : public Action
//{
//    enum { MaxStats = 200, MaxVars = 50, MaxIn = 5 };
//
//    struct State {
//        bool declared[MaxVars];
//        bool initialized[MaxVars];
//
//        State() {
//            for (int i = 0; i < MaxVars; ++i) {
//                declared[i] = false;
//                initialized[i] = false;
//            }
//        }
//
//        bool operator!=(const State& other) const {
//            for (int i = 0; i < MaxVars; ++i) {
//                if (declared[i] != other.declared[i]) return true;
//                if (initialized[i] != other.initialized[i]) return true;
//            }
//            return false;
//        }
//    };
//
//    // Symbol Table
//    string VarNames[MaxVars];
//    int VarCount;
//
//    // CFG (Using Indices 0..StatCount-1)
//    // Adjacency lists using fixed arrays
//    int Adj[MaxStats][2];     // Max out degree is 2 (Conditional)
//    int AdjCount[MaxStats];
//
//    int RevAdj[MaxStats][MaxIn];
//    int RevAdjCount[MaxStats];
//
//    // States
//    State inStates[MaxStats];
//    State outStates[MaxStats];
//
//public:
//    Validate(ApplicationManager* pAppManager);
//    virtual void ReadActionParameters();
//    virtual void Execute();
//
//private:
//    int GetVarIndex(string name);
//    int GetStatementIndex(Statement* pStat);
//    void BuildCFG();
//    void AnalyzeDataFlow();
//    bool CheckSemantics(Statement* pStat, string& errorMsg);
//
//    // Helpers
//    void SetAll(bool dest[], bool val);
//    void SetIntersection(bool dest[], const bool src[]);
//    void SetCopy(bool dest[], const bool src[]);
//};
//
//#endif
