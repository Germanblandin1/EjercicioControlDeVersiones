#include "File.h"

class FileTree{
    private:
        File *root;
        map<string,File*> fileDicc; 

        File* find(string path){
            map<string,File*>::iterator response = fileDicc.find(path);
            if( response != fileDicc.end()) return response->second;
            return NULL;
        }

        void addNewFile(string path,File* father,tm * timestap){
            File * newFile= new File(FILEE,path,splitPath(path,'/').second);
            newFile->addVersion(timestap,0);
            father->addSon(newFile);
            fileDicc[path]=newFile;
        }

        void addNewFolder(string path,File* father,tm * timestap){
            File * newFile= new File(FOLDER,path,splitPath(path,'/').second);
            newFile->addVersion(timestap,0);
            if(father!=NULL) father->addSon(newFile);
            else root=newFile;
            fileDicc[path]=newFile;
        }

        void addNewVersionFromFile(File* file,tm * timestap ){
            file->addVersion(timestap,file->getLastVersionNumber()+1);
        }

        bool existsFile(File * file, tm * timestap){
            if(file==NULL) return false;
            return file->existVersion(timestap);
        }

        void preorden(File * current,tm * timestap,vector<string> &fileList){
            if(current->isFile()){
                Version *version=current->findVersion(timestap);
                if(version!=NULL) fileList.push_back(current->getPath()+"V"+intToString(version->getNumber()));
            }else{
                vector<File*> childs= current->getChilds();
                for(int i=0;i<childs.size();i++){
                    preorden(childs[i],timestap,fileList);
                }
            }
        }

        void preordenDelete(File * current,tm * timestap){
            if(current->isFile()){
                current->deleteVersion(timestap);
            }else{
                vector<File*> childs= current->getChilds();
                for(int i=0;i<childs.size();i++){
                    preordenDelete(childs[i],timestap);
                }
            }
        }


    public:

        FileTree(){
            root = NULL;
        }

        void addFile(string path,tm * timestap){
            string father=splitPath(path,'/').first;
            File * fatherFile = find(father);
            File * sonFile = find(path);
            fatherFile = fatherFile == NULL ? root: fatherFile;
            if(sonFile==NULL) addNewFile(path,fatherFile,timestap);
            else addNewVersionFromFile(sonFile,timestap);
        }

        bool addFolder(string path, tm * timestap){
            string father=splitPath(path,'/').first;
            File * fatherFile = find(father);
            File * sonFile = find(path);
            fatherFile = fatherFile == NULL ? root : fatherFile;
            if(sonFile==NULL){
                addNewFolder(path,fatherFile,timestap);
                return true;
            }
            return false;
        }

        bool deleteFile(string path, tm * timestap){
            File * file = find(path);
            if(file==NULL) return false;
            return file->deleteVersion(timestap);
        }

        bool deleteFolder(string path, tm * timestap){
            File * file = find(path);
            if(file==NULL) return false;
            preordenDelete(file,timestap);
            return true;
        }

        bool exists(string path, tm * timestap){
            File * file = find(path);
            if(file==NULL) return false;
            return existsFile(file,timestap);
        }

        vector<string> listDir(string path, tm * timestap){
            File * file = find(path);
            vector<string> fileList;
            if(file==NULL) return fileList;
            preorden(file,timestap,fileList);
            sort(fileList.begin(),fileList.end());
            return fileList;
        }

        vector<Version*> versionList(string path, tm * start,tm * end){
            File * file = find(path);
            vector<Version*> versionList;
            if(file==NULL) return versionList;
            return file->getRangeVersion(start,end);
        }
};