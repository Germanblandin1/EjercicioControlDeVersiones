#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<time.h>
#include <algorithm>
#include<map>
#include <sstream>
#define FILEE true
#define FOLDER false
using namespace std;

pair<string,string> splitPath(string path,const char delimited){
    for(int i=path.size()-1;i>=0;i--){
        if(path[i]==delimited) return make_pair(path.substr(0,i),path.substr(i+1,path.size()));
    }
    return make_pair(path,path);
}

int timeCompare(tm* A, tm* B){
    time_t timeA,timeB;
    timeA=mktime(A);
    timeB=mktime(B);
    return timeA<timeB? -1 : (timeA==timeB? 0 : 1);

}

string intToString(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}

void printDate(tm *tmTemp){
     printf("Fecha: %d-%d-%d %d:%d:%d",tmTemp->tm_mday,tmTemp->tm_mon+1,tmTemp->tm_year+1900,tmTemp->tm_hour,tmTemp->tm_min,tmTemp->tm_sec);
}


