#include "org_apache_ignite_examples_datagrid_CachePutGetComplexExample.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
class Person {
public:
	Person(jstring name, jdouble balance) {
		this->name = name;
		this->balance = balance;
	}
	jdouble getBalance() {
		return balance;
	}

private:
	jstring name;
	jdouble balance;
};

jdouble average(std::vector<Person> vp) {
	jdouble total = 0;
	for (auto p : vp) {
		total += p.getBalance();
	}
	return total /= vp.size();
};


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
	
	jobject result = env->CallObjectMethod(cache, methodIdget, obIndex0);

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
	
	jstring name0 = (jstring)env->GetObjectField(Person0, fidname);
	jdouble balance0 = env->GetDoubleField(Person0, fidbalance);

	jstring name1 = (jstring)env->GetObjectField(Person1, fidname);
	jdouble balance1 = env->GetDoubleField(Person1, fidbalance);
	
	Person p0(name0, balance0);
	Person p1(name1, balance1);
	std::vector<Person> vp{ p0, p1 };

	return average(vp);
};