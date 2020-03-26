#include "org_apache_ignite_examples_datagrid_CachePutGetComplexExample.h"
#include <iostream>
#include <cassert>

JNIEXPORT jobject JNICALL Java_org_apache_ignite_examples_datagrid_CachePutGetComplexExample_cppget
  (JNIEnv *env, jobject, jobject cache, jobject index){
	jclass cacheclass=env->GetObjectClass(cache);
	assert(cacheclass != nullptr);

	jmethodID methodIdget = env->GetMethodID(cacheclass, "get","(Ljava/lang/Object;)Ljava/lang/Object;");
	assert(methodIdget  != 0);
	
	jobject result = env->CallObjectMethod(cache, methodIdget, index);

	jclass PersonClass=env->GetObjectClass(result);
	
	jmethodID methodIdadd = env->GetMethodID(PersonClass, "addbalance","(I)V");

	jint amount = 100;
	env->CallVoidMethod(result , methodIdadd, amount);

	return result;
};