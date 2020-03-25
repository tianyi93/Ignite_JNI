#include "org_apache_ignite_examples_datagrid_CachePutGetExample.h"
#include <iostream>
#include <cassert>

JNIEXPORT jstring JNICALL Java_org_apache_ignite_examples_datagrid_CachePutGetExample_cppget
  (JNIEnv *env, jobject, jobject cache, jobject index){
	jclass cacheclass=env->GetObjectClass(cache);
	assert(cacheclass != nullptr);

	jmethodID methodIdget = env->GetMethodID(cacheclass, "get","(Ljava/lang/Object;)Ljava/lang/Object;");
	assert(methodIdget  != 0);
	
	jstring result = (jstring)env->CallObjectMethod(cache, methodIdget, index);

	return result;
};