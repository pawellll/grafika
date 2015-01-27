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
          MOVES=2,
          TYPE=3
    };
    typedef std::tuple<std::string,int,int,GameTypesEnum> score; // typedef for score
    static bool scoreCompare(const BestScores::score &lhs, const BestScores::score &rhs); // score comparision function for sorting
    BestScores(); // default c-tor 
    ~BestScores(); // d-tor
    void addScore(const std::string& name,const int time,const int moves,const GameTypesEnum type); // adii score with name of player, time in minutes, and GameType and sort type
    std::list<BestScores::score>* getScores(const GameTypesEnum type); // get score for particular gameType
    bool isBestScore(const int time,const int moves,const GameTypesEnum type);
    void print(); // print all scores - debug
private:
    std::map<GameTypesEnum, std::list<score>* > _allBestScores; // scores for all types
    const std::string _fileName; // name of file where scores are stored 
    std::fstream _file; // file with best scores
    bool _changed; // says if scores has been changed or not since creating BestScores to destructing it
};

#endif // BESTSCORES_H
