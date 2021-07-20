/** Jacob Sigman
 *  Programming Assignment 4
 *  Professor Sable
 *  isMerge.cpp
 *
 *  This file contains the recursive and dynamic
 *  implementation for determining if a string is a
 *  merge of two other strings from the isMerge.h file.
 */

#include <string>
#include "isMerge.h"

using namespace std;

bool isMergeRecursive(const string& str1, const string& str2, const string& str3) {

    /** Base case: If all the strings are empty return true.
     */

    if (str1.empty() && str2.empty() && str3.empty())
        return true;

    /** Case two: If the third string is empty, but the other two are not,
     *  return false.
     */

    if (str3.empty())
        return false;

    /** Recursive case: If the first characters of str1 and str3 are the same,
     *  then recursively call with the first character removed from str1 and str3.
     */

    if (str3.substr(0,1) == str1.substr(0,1))
        return isMergeRecursive(str1.substr(0,1), str2, str3.substr(0,1));

    /** Recursive case: If the first characters of str2 and str3 are the same,
     *  then recursively call with the first character removed from str2 and str3.
     */

    if (str3.substr(0,1) == str2.substr(0,1))
        return isMergeRecursive(str1, str2.substr(0,1), str3.substr(0,1));

    /** The code should never make it here, but just in case.
     */

    return false;
}


bool isMergeDynamic(string str1, string str2, string str3) {

}