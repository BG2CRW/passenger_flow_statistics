#include "typechange.h"

char* TypeChange::stringToChar(string s,int size)
{
    char *p=new char[size];
    strcpy(p,s.c_str());
    return p;
}

string TypeChange::itos(unsigned int i) // 将int 转换成string
{
    stringstream s;
    s << i;
    return s.str();
}

