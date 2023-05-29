#include "ThetaJoin.h"

using namespace std;

shared_ptr<CRelation> CThetaJoin::evaluate(vector<shared_ptr<CRelation>> & relations){
     shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
     shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
     CRelation res;
     bool isHere = false;


     
     return nullptr;
}