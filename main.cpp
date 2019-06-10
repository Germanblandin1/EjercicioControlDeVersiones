#include "Utilitys.h"
#include "FileTree.h"

char str[1000];

tm* createTimestap(int year,int mon,int day,int hour,int min,int sec){
    tm * timeinfo = new tm();
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = mon - 1;
    timeinfo->tm_mday = day;
    timeinfo->tm_sec = sec;
    timeinfo->tm_min = min;
    timeinfo->tm_hour = hour;
    return timeinfo;
}

void addFiles(FileTree * fileTree,FILE *file){
    int type;
    int count=0;
    int N;
    string path;
    fscanf(file,"%d",&N);
    for(int i=0;i<N;i++){
        fscanf(file,"%s %d",str,&type);
        path=str;
        tm * timeinfo = createTimestap(2019,6,6,14,34,count);
        if(count==0 || type==0){
            if(fileTree->addFolder(path,timeinfo)) printf("Directorio agregado con Exito\n");
            else printf("El directorio ya existe\n");
        }else{
            fileTree->addFile(path,timeinfo);
            printf("Version del archivo agregado con Exito\n");
        } 
        count+=1;
    }
}

void existQuery(string path,tm * timeinfo,FileTree *fileTree){
    bool res= fileTree->exists(path,timeinfo);
    printf("%s una version del archivo %s\n",res?"Existe":"No existe",path.c_str());
}

void listDirQuery(string path,tm * timeinfo,FileTree *fileTree){
    vector<string> res= fileTree->listDir(path,timeinfo);
    if(res.size()==0) printf("El directorio esta vacio\n");
    else{
        printf("El directorio %s contiene los siguientes archivos\n",path.c_str());
        for(int i=0;i<res.size();i++){
            printf("%s ",res[i].c_str());
        }
        printf("\n");
    }
}

void versionListQuery(string path,tm * timeinfo,tm * timeinfo2,FileTree *fileTree){
    vector<Version*> versionList= fileTree->versionList(path,timeinfo,timeinfo2);
    printf("Las versiones del archivo %s son: \n",path.c_str());
    for(int i=0;i<versionList.size();i++){
        tm * tmTemp=versionList[i]->getTimestap();
        printf("V%d ",versionList[i]->getNumber());
        printDate(tmTemp);
        printf("\n");
    }
}

void deleteFileQuery(string path,tm * timeinfo,FileTree *fileTree){
    if(fileTree->deletedFile(path,timeinfo)){ 
        printf("La version con ");
        printDate(timeinfo);
        printf(" del archivo %s fue borrada exitosamente\n",path.c_str());
    }else printf("EL archivo no existe\n");
}

void deleteFolderQuery(string path,tm * timeinfo,FileTree *fileTree){
    if(fileTree->deletedFolder(path,timeinfo)){
        printf("Las versiones con ");
        printDate(timeinfo);
        printf(" de los archivos del directorio %s fueron borrados exitosamente\n",path.c_str());
    }else printf("El archivo no existe\n");
}

void queryProcess(FileTree * fileTree,FILE *archivo){
    int Q;
    int t;
    int d1,m1,a1,h1,mi1,s1,d2,m2,a2,h2,mi2,s2;
    tm * timeinfo, *timeinfo2;
    fscanf(archivo,"%d",&Q);
    for(int i=0;i<Q;i++){
        string path;
        fscanf(archivo,"%d %s %d %d %d %d %d %d",&t,str,&d1,&m1,&a1,&h1,&mi1,&s1);
        if(t==2) fscanf(archivo,"%d %d %d %d %d %d",&d2,&m2,&a2,&h2,&mi2,&s2);
        path=str;
        timeinfo = createTimestap(a1,m1,d1,h1,mi1,s1);
        if(t==2) timeinfo2 = createTimestap(a2,m2,d2,h2,mi2,s2);
        printf("Query %d\n",i+1);
        if(t==0){
            existQuery(path,timeinfo,fileTree);
        }else if(t==1){
            listDirQuery(path,timeinfo,fileTree);
        }else if(t==2){
            versionListQuery(path,timeinfo,timeinfo2,fileTree);
        }else if(t==3){
            deleteFileQuery(path,timeinfo,fileTree);
        }else{
            deleteFolderQuery(path,timeinfo,fileTree);
        }
        printf("\n\n");
    }
}

int main(){
    FILE * file = fopen("entrada.in","r");
    FileTree * fileTree = new FileTree();
    if(file!=NULL){
        addFiles(fileTree,file);
        queryProcess(fileTree,file);
    }
    fclose(file);
}