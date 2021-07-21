/** Jacob Sigman
 *  Programming Assignment 4
 *  Professor Sable
 *  isMerge.h
 *
 *  This file contains functions for a recursive
 *  and dynamic implementation for determining if a string
 *  is a merge of two other strings. These functions are
 *  implemented in the isMerge.cpp file.
 */

#ifndef _ISMERGE_H
#define _ISMERGE_H

#include <string>

/** isMergeRecursive(): Determines if a string is a merge of two other strings recursively.
 *  This method does has exponential time complexity and therefore won't be effective.
 *
 *  @param {string} str1 - First string being merged.
 *  @param {string} str2 - Second string being merged.
 *  @param {string} str3 - The string to check if it's a merge of the first two strings.
 *  @return {bool} - Whether or not the third string is a merge of the first two strings.
 */

bool isMergeRecursive(const std::string& str1, const std::string& str2, const std::string& str3);

/** isMergeDynamic(): Determines if a string is a merge of two other strings using dynamic programming.
 *
 *  @param {string} str1 - First string being merged.
 *  @param {string} str2 - Second string being merged.
 *  @param {string} str3 - The string to check if it's a merge of the first two strings.
 *  @return {bool} - Whether or not the third string is a merge of the first two strings.
 */

bool isMergeDynamic(const std::string& str1, const std::string& str2, const std::string& str3);

#endif //_ISMERGE_H
