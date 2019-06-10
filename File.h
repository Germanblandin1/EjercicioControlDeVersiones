#include "Version.h"


class File{
    private: 
        bool file;
        Version* lastVersion;
        string path;
        string name;
        map<time_t,Version*> versionList;
        vector<File*> childs;

    public:
        File(){

        }

        File(bool p_file, string p_path, string p_name){
            file = p_file;
            path = p_path;
            name = p_name;
            lastVersion=0;
        }

        Version* findVersion(tm * timestap){
            if(versionList.size()==0) return NULL;
            map<time_t,Version*>::iterator it;
            time_t taux=mktime(timestap);
            it=versionList.lower_bound(taux);
            if(versionList.rbegin()->first<=taux){ return versionList.rbegin()->second;}
            if(it==versionList.end()) return NULL;
            if(it->first==taux) return it->second;
            it--;
            if(it->first<taux) return it->second;
            return NULL;
        }

        bool existVersion(tm * timestap){
            return findVersion(timestap)!=NULL;
        }

        void addVersion(tm * timestap,int number){
            Version * newVersion= new Version(timestap,number);
            versionList[mktime(timestap)]=newVersion;
            lastVersion=newVersion;
        }

        void addSon(File * son){
            childs.push_back(son);
        }

        int getLastVersionNumber(){
            return lastVersion->getNumber(); 
        }

        string getPath(){
            return path;
        }

        bool isFile(){
            return file;
        }
        
        tm * getTimestap(){
            return lastVersion->getTimestap();
        }

        vector<File*> getChilds(){
            return childs;
        }

        vector<Version*> getRangeVersion(tm * start,tm * end){
            vector<Version*> resVersionList;
            if(versionList.size()==0) return resVersionList;
            map<time_t,Version*>::iterator itStart,itEnd,it;
            itStart=versionList.lower_bound(mktime(start));
            itEnd=versionList.upper_bound(mktime(end));
            for(it=itStart;it!=itEnd;it++) resVersionList.push_back(it->second);
            reverse(resVersionList.begin(),resVersionList.end());
            return resVersionList;
        }

        bool deleteVersion(tm *timestap){
            Version* version;
            version=findVersion(timestap);
            if(version!=NULL){
                versionList.erase(mktime(version->getTimestap()));
                delete version;
                return true;
            }
            return false;
        }
};