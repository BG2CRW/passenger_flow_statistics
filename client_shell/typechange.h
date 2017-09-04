#ifndef TYPECHANGE_H
#define TYPECHANGE_H
#include <QString>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
using namespace::std;
class TypeChange
{
    public:
    char* stringToChar(string s,int size);
    string itos(unsigned int i); // 将int 转换成string

};

#endif // TYPECHANGE_H
