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

bool matrix[1000][1000];

/** isMergeRecursive(): Determines if a string is a merge of two other strings recursively.
 *  This method does has exponential time complexity and therefore won't be effective.
 *
 *  @param {string} str1 - First string being merged.
 *  @param {string} str2 - Second string being merged.
 *  @param {string} str3 - The string to check if it's a merge of the first two strings.
 *  @return {bool} - Whether or not the third string is a merge of the first two strings.
 */

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

    /** First boolean: If the first characters of str1 and str3 are the same,
     *  and the recursive call with the first character removed from str1 and str3
     *  also returns true.
     */

    bool str1Match = !(str1.empty()) && (str3[0] == str1[0])
            && isMergeRecursive(str1.substr(1), str2, str3.substr(1));

    /** Second boolean: If the first characters of str2 and str3 are the same,
     *  and the recursive call with the first character removed from str2 and str3
     *  also returns true.
     */

    bool str2Match = !(str2.empty()) && (str3[0] == str2[0])
            && isMergeRecursive(str1, str2.substr(1), str3.substr(1));

    /** Return str1Match or str2Match to handle any common characters.
     */

    return str1Match || str2Match;
}

/** isMergeDynamic(): Determines if a string is a merge of two other strings using dynamic programming.
 *
 *  @param {string} str1 - First string being merged.
 *  @param {string} str2 - Second string being merged.
 *  @param {string} str3 - The string to check if it's a merge of the first two strings.
 *  @return {bool} - Whether or not the third string is a merge of the first two strings.
 */

bool isMergeDynamic(const string& str1, const string& str2, const string& str3) {

    /** Create two-dimensional array (1000 by 1000) of possible merges from each of the
     *  first two strings.
     */

    for (int i = 0;  i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {

            /** Case 1: If both strings are empty, set cell to true.
             *  Similar to the base case of the recursive solution.
             */

            if (i == 0 && j == 0)
                matrix[i][j] = true;

            /** Case 2: If str1 and str2 are not empty, and the current characters of
             *  str1, str2, and str3 are the same, set the cell to either the cell on the left,
             *  or the cell below. This is equivalent to the final line of the recursive
             *  solution, which is intended for handling any duplicate characters amongst
             *  the three strings.
             */

            else if (i != 0 && j != 0 && str1[i - 1] == str3[(i + j) - 1] && str2[j - 1] == str3[(i + j) - 1])
                matrix[i][j] = matrix[i][j - 1] || matrix[i - 1][j];

            /** Case 3: If str1 is not empty, and the current characters of
             *  str1 and str3 are the same, set the cell to the cell on the left.
             *  This is equivalent to removing one character in the recursive
             *  solution above.
             */

            else if (i != 0 && str1[i - 1] == str3[(i + j) - 1])
                matrix[i][j] = matrix[i - 1][j];

            /** Case 4: If str2 is not empty, and the current characters of
             *  str2 and str3 are the same, set the cell to the cell below.
             *  This is equivalent to removing one character in the recursive
             *  solution above.
             */

            else if (j != 0 && str2[j - 1] == str3[(i + j) - 1])
                matrix[i][j] = matrix[i][j - 1];
            
            /** If the code ever makes it here, just set the cell to false
             *  if it's not false already.
             */
            
            else
                matrix[i][j] = false;
        }
    }

    /** Simply access the value in the matrix at the size of str1 and str2 for
     *  the row and column respectively.
     */

    return matrix[str1.size()][str2.size()];
}