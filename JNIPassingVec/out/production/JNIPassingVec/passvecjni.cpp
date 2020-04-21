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