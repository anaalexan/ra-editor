#include "MenuRAeditor.h"
#include <memory>
#include "CrossJoin.h"
#include "Difference.h"
#include "Intersection.h"
#include "Union.h"
#include "Rename.h"
#include "Projection.h"
#include "NaturalJoin.h"


using namespace std;

CMenuRAeditor::CMenuRAeditor(){
        m_menuText = string("Main RA editor\n"
            "Select 1 for return to Main enu\n" 
            "Your selection: ");
}

CMenuBase * CMenuRAeditor::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase *nextMenu = 0;


//testing if file service works properly

        /*CRelation relation("/home/progtest/Downloads/testInput.csv");
        CFileService file;
        shared_ptr<CRelation> sptr = make_shared<CRelation>(relation);
        file.importFromFile(sptr);

        relation.setPath("/home/progtest/Downloads/testOutput.csv");
        file.exportToFile(sptr);*/

// end of test
//**************************************

// testing if crossJoin work
CRelation rel1("/home/progtest/Downloads/rel1.csv");
CRelation rel2("/home/progtest/Downloads/rel2.csv");
CFileService file;
shared_ptr<CRelation> sptr1 = make_shared<CRelation>(rel1);
file.importFromFile(sptr1);
shared_ptr<CRelation> sptr2 = make_shared<CRelation>(rel2);
file.importFromFile(sptr2);

/*CCrossJoin spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CDifference rozdil;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = rozdil.evaluate(vec);
file.exportToFile(sptr);*/

/*CIntersection spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CUnion spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CRename rename("name,jmeno;surname,primeni");
vector<shared_ptr<CRelation>> vec = {sptr1};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = rename.evaluate(vec);
file.exportToFile(sptr);*/

/*CProjection project("name,tel,fam");
vector<shared_ptr<CRelation>> vec = {sptr1};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = project.evaluate(vec);
file.exportToFile(sptr);*/

CNaturalJoin spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);

//end of test


        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
            }

        }

        return nextMenu;
    }