#include<iostream>
#include<string>
#include<vector>
#include"passvecjni.h"

JNIEXPORT void JNICALL Java_passvecjni_passvec
  (JNIEnv * env, jobject cls, jobject obj, jint size){
    jclass listClass = env->FindClass("java/util/ArrayList");
    if(listClass==NULL)
        return;
    jmethodID getMethodID = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if(getMethodID==NULL)
        return;

    std::vector<std::string> columnNames;
    for(int i=0; i<size; i++){
        jstring s = (jstring)env->CallObjectMethod(obj, getMethodID, i);
        std::string stdstring = env->GetStringUTFChars(s, NULL);
        columnNames.push_back(stdstring);
    }
    std::cout<<"vector func finshed successfully, constructed columnNames vector in C++"<<std::endl;
    std::cout<<"Elements are: ";
    for(int i=0; i<size; i++){
        std::cout<<columnNames[i]<<" ";
    }
}
JNIEXPORT void JNICALL Java_passvecjni_passmatrix
  (JNIEnv *env, jobject cls, jobject obj, jint rsz, jint csz){
    jclass listClass = env->FindClass("java/util/ArrayList");
    if(listClass==NULL)
        return;
    jmethodID getMethodID = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if(getMethodID==NULL)
        return;

    std::vector<std::vector<std::string>> rowVecs;
    for(int i=0; i<csz; i++){
        std::vector<std::string> row;
        for(int j=0; j<rsz; j++){
            jobject vec = env->CallObjectMethod(obj, getMethodID, i);
            jstring s = (jstring)env->CallObjectMethod(vec, getMethodID, j);
            std::string stdstring = env->GetStringUTFChars(s, NULL);
            row.push_back(stdstring);
        }
        rowVecs.push_back(row);
    }
    std::cout<<"vector func finshed successfully, constructed columnNames vector in C++"<<std::endl;
    std::cout<<"Elements are: ";
    for(int i=0; i<csz; i++)
        for(int j=0; j<rsz; j++){
        std::cout<<rowVecs[i][j]<<" ";
    }
  }