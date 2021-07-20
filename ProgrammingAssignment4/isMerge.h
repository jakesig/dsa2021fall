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

//int matrix[1000][1000];

bool isMergeRecursive(const std::string& str1, const std::string& str2, const std::string& str3);

bool isMergeDynamic(std::string str1, std::string str2, std::string str3);

#endif //_ISMERGE_H
