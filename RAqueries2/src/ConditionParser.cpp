#include "ConditionParser.h"

using namespace std;


vector<string> CConditionParser::parse(const string & condition){
    vector<string> vec;

    for(size_t i = 0; i < condition.size(); i++){
        string word;
        while(condition[i] != '>' && condition[i] != ' ' && condition[i] !=  '<' && condition[i] != '=' && condition[i] != '!'){
            word.push_back(condition[i]);
            i++;
        }
        if(condition[i] == '>' || condition[i] ==  '<' || condition[i] == '=' || condition[i] == '!'){
            vec.push_back(word);
            word.clear();
            while(condition[i] == '>' || condition[i] ==  '<' || condition[i] == '=' || condition[i] == '!'){
                word.push_back(condition[i]);
                i++;
            }
            vec.push_back(word);
            word.clear();
        }

    }
    return vec;
}