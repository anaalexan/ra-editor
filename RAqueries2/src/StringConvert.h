#pragma once

#include <string>
#include <variant>



using namespace std;

/** Class for operation with input string to indicate what type it is  */
class CStringConvert{
    public:
        /** @var class template std::variant  contains float, int, double and string
         */
        typedef variant<float, int, double, string> m_variant;

        /**
	 * Method determine if the input string is a float type
	 * @param[in] str string input from a user
     * @param[in,out] floatCheck value of the float input
     * @returns true if an input is a float
	 */
        bool isFloat(string str, float & floatCheck);

        /**
        * Method determine if the input string is an int type
	 * @param[in] str string input from a user
     * @param[in,out] floatCheck value of the int input
     * @returns true if an input is an int
	 */
        bool isInt(string str, int & intCheck);

        /**
        * Method determine if the input string is a double type
	 * @param[in] str string input from a user
     * @param[in,out] floatCheck value of the double input
     * @returns true if an input is a double
	 */
        bool isDouble(string str, double & doubleCheck);

        /**
	 * Method detect what type has an input from the user
	 * @param[in] str string input from a user
     * @returns one of the variant of types
	 */
        m_variant whatType(string str);

        

};