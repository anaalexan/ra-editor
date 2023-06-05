#include "MenuKeywords.h"

using namespace std;

CMenuKeywords::CMenuKeywords(){
        m_menuText = string("Application keywords (Help)\n"
            "For return to main menu print 1.\n"
            "\n"
            "USEGE OF RA editor:\n"
            "EXIT will exit to the main menu from RA editor.\n\n"
            "IMPORT name_of_the_variable \"path_to_the_relation.csv\" \n"
            "will add name_of_the_variable to the variables and will save the path to it.\n\n"
            "PRINT name_of_the_variable or expression.\n"
            "will print result of evaluation of expression into console.\n\n"
            "EXPORT name_of_the_variable/or expression > path\n"
            "will export the variable or the result of evaluated expression into this path\n\n"
            "TRANSLATE name_of_the_variable/or expression\n"
            "will translate expression inside the variable or given expression into valid query in SQL.\n\n "
            
            "Expression in relational algebra (RA) should have the following format:\n"
            "path to the file with the relation inside the expression or while import should always be inside quotation marks \"path\"\n"
            "exception is keyword export: EXPORT name_of_the_variable/or expression > path (without quotation marks). \n\n"
            "SELECTION: (condition)\n"
             "where the condition is (name_of_the_column comparison_operator name_of_the_column)\n"
             "or (name_of_the_column comparison_operator 'konstant'). KOnstant can be a word or a number.\n\n"
            "Theta JOIN: ^(condition),\n"
            "where the condition is (name_of_the_column comparison_operator name_of_the_column)\n\n"

             "comparison_operator can be:\n"
             " '==' is equal to\n"
             " '!=' not equal to\n"
             " '>' is greater then\n"
             " '>=' is greater or equal then\n"
             " '<' is less then\n"
             " '<=' is less or equal then\n\n"

             "PROJECTION: [name_of_column1,...,name_of_columnN],\n"
             "where name_of_column can be 1 or N names of column, that you want to project\n\n"

             "RENAME: <old_name1,new_name1;...;old_nameN,new_nameN >,\n"
             "where old_name is the name of the column that you want to change\n"
             "and new_name is the name you want to change to\n\n"

             "NATURAL JOIN: variable1 * variable2.\n\n"

             "INTERSECTION: variable1 & variable2.\n\n"

             "UNION: variable1 + variable2.\n\n"

             "DIFFERENCE: variable1 - variable2.\n\n"

             "CROSS JOIN (or Cartesian product)): variable1 x variable2.\n\n"

             "Inside menu TRANSLATE to SQL:\n"
             "For expression applies the same regulation as above.\n"
        );
}

CMenuBase * CMenuKeywords::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase * nextMenu = 0;

        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
                isExitSelected = false;
                break;
            }
            default:{}

        }

        return nextMenu;
    }