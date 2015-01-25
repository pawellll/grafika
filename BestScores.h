#ifndef BESTSCORES_H
#define BESTSCORES_H

#include <fstream>
#include <string>
#include <vector>
#include <tuple> // c11
#include <map>
#include <list>
#include <iostream>
#include <sstream>

#include "GameTypesEnum.h"

class BestScores{
public:
    // enum for using get<NAME>(tuple);
    enum scorePart{
          NAME=0,
          TIME=1,
          TYPE=2
    };
    typedef std::tuple<std::string,int,GameTypesEnum> score; // typedef for score
    static bool scoreCompare(const BestScores::score &lhs, const BestScores::score &rhs); // score comparision function for sorting
    BestScores(); // default c-tor 
    ~BestScores(); // d-tor
    void addScore(const std::string& name,const int time,const GameTypesEnum type); // adii score with name of player, time in minutes, and GameType
    std::list<BestScores::score>* getScores(const GameTypesEnum type); // get score for particular gameType
    void print(); // print all scores - debug
private:
    std::map<GameTypesEnum, std::list<score>* > _allBestScores; // scores for all types
    const std::string _fileName; // name of file where scores are stored 
    std::fstream _file; // file with best scores
    bool _changed; // says if scores has been changed or not since creating BestScores to destructing it
};

#endif // BESTSCORES_H
