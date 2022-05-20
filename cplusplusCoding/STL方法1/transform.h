#pragma once
#include "vector_base.h"
using namespace std;

void transform_test0() {
	vector<int>v1,target;
	constructVectorWithSize(v1, 5);
	target.resize(v1.size());
	for_each(v1.begin(), v1.end(), PrintInt_functor());
	transform(v1.begin(), v1.end(), target.begin(), Transform());
	for_each(target.begin(), target.end(), PrintInt_functor());
}