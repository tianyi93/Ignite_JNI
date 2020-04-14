#include "org_apache_ignite_examples_datagrid_CachePutGetComplexExample.h"
#include "domain.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>


JNIEXPORT jobject JNICALL Java_org_apache_ignite_examples_datagrid_CachePutGetComplexExample_cppget
  (JNIEnv *env, jobject, jobject cache, jobject index){
	jclass cacheclass=env->GetObjectClass(cache);
	assert(cacheclass != nullptr);

	jmethodID methodIdget = env->GetMethodID(cacheclass, "get","(Ljava/lang/Object;)Ljava/lang/Object;");
	assert(methodIdget  != 0);
	
	jclass integerclass = env->FindClass("java/lang/Integer");
	jmethodID methodIdconstructor = env->GetMethodID(integerclass, "<init>", "(I)V");
	jint index_0 = 1;
	jobject obIndex0 = env->NewObject(integerclass, methodIdconstructor, index_0);
	
	jobject result = env->CallObjectMethod(cache, methodIdget, index);

	jclass PersonClass=env->GetObjectClass(result);
	
	jmethodID methodIdadd = env->GetMethodID(PersonClass, "addbalance","(I)V");

	jint amount = 100;
	env->CallVoidMethod(result , methodIdadd, amount);

	return result;
};

JNIEXPORT jdouble JNICALL Java_org_apache_ignite_examples_datagrid_CachePutGetComplexExample_avg
(JNIEnv* env, jobject, jobject cache) {
	jclass cacheclass = env->GetObjectClass(cache);
	assert(cacheclass != nullptr);

	jmethodID methodIdget = env->GetMethodID(cacheclass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
	assert(methodIdget != 0);

	jclass integerclass = env->FindClass("java/lang/Integer");
	jmethodID methodIdconstructor = env->GetMethodID(integerclass, "<init>", "(I)V");
	jint index_0 = 0;
	jint index_1 = 1;
	jobject obIndex0 = env->NewObject(integerclass, methodIdconstructor, index_0);
	jobject obIndex1 = env->NewObject(integerclass, methodIdconstructor, index_1);
	jobject Person0 = env->CallObjectMethod(cache, methodIdget, obIndex0);
	jobject Person1 = env->CallObjectMethod(cache, methodIdget, obIndex1);

	jclass PersonClass = env->GetObjectClass(Person0);
	jfieldID fidname = env->GetFieldID(PersonClass, "name", "Ljava/lang/String;");
	jfieldID fidbalance = env->GetFieldID(PersonClass, "balance", "D");
	jfieldID fidaddress = env->GetFieldID(PersonClass, "address", "Lorg/apache/ignite/examples/datagrid/Address;");
	
	jstring name0 = (jstring)env->GetObjectField(Person0, fidname);
	std::string name0s = env->GetStringUTFChars(name0, NULL);
	jdouble balance0 = env->GetDoubleField(Person0, fidbalance);
	jobject address0 = env->GetObjectField(Person0, fidaddress);
	jclass AddressClass = env->GetObjectClass(address0);
	jfieldID fidzipcode = env->GetFieldID(AddressClass, "zipcode", "I");
	jint zipcode0 = env->GetIntField(address0, fidzipcode);

	jstring name1 = (jstring)env->GetObjectField(Person1, fidname);
	std::string name1s = env->GetStringUTFChars(name1, NULL);
	jdouble balance1 = env->GetDoubleField(Person1, fidbalance);
	
	Person p0(name0s, balance0, zipcode0);
	Person p1(name1s, balance1, 89169);
	std::vector<Person> vp{ p0, p1 };

	return average(vp);
};

JNIEXPORT jint JNICALL Java_org_apache_ignite_examples_datagrid_CachePutGetComplexExample_zipcount
(JNIEnv* env, jobject, jobject cache, jint zipcode, jint size) {
	jclass cacheclass = env->GetObjectClass(cache);
	assert(cacheclass != nullptr);

	jmethodID methodIdget = env->GetMethodID(cacheclass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
	assert(methodIdget != 0);

	jclass integerclass = env->FindClass("java/lang/Integer");
	jmethodID methodIdconstructor = env->GetMethodID(integerclass, "<init>", "(I)V");

	std::vector<jobject> IndexArray;
	for (int i = 0; i < size; i++) {
		jobject obIndex = env->NewObject(integerclass, methodIdconstructor, i);
		IndexArray.push_back(obIndex);
	}

	std::vector<jobject> PersonArray;
	for (int i = 0; i < size; i++) {
		jobject person = env->CallObjectMethod(cache, methodIdget, IndexArray[i]);
		PersonArray.push_back(person);
	}

	jclass PersonClass = env->GetObjectClass(PersonArray[0]);
	jfieldID fidname = env->GetFieldID(PersonClass, "name", "Ljava/lang/String;");
	jfieldID fidbalance = env->GetFieldID(PersonClass, "balance", "D");
	jfieldID fidaddress = env->GetFieldID(PersonClass, "address", "Lorg/apache/ignite/examples/datagrid/Address;");

	std::vector<Person> CppPersonArray;
	for (int i = 0; i < size; i++) {
		jstring name = (jstring)env->GetObjectField(PersonArray[i], fidname);
		std::string names = env->GetStringUTFChars(name, NULL);
		jdouble balance = env->GetDoubleField(PersonArray[i], fidbalance);
		jobject address = env->GetObjectField(PersonArray[i], fidaddress);
		jclass AddressClass = env->GetObjectClass(address);
		jfieldID fidzipcode = env->GetFieldID(AddressClass, "zipcode", "I");
		jint zipcode = env->GetIntField(address, fidzipcode);
		Person person(names, balance, zipcode);
		CppPersonArray.push_back(person);
	}

	return numzip(CppPersonArray,zipcode);
};