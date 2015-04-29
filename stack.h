
#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>

const double FAIL = 13.666;
const double FAIL_POP = 13.666;
const int    POISON = -99;
const int    NULL_ARGUMENT = -1;
template <typename T>
class stack
{
public:
	struct stackt
	{
		int Count = POISON;
		T* value = NULL;
	};
	stackt st;
	stack()
	{
		st.Count = 0;
		st.value = (T*)calloc(1, sizeof(T));
		assert(st.value);
	}
	//~stack();

	stack plus()
	{
		return *this;
	}

	int stack_push(T value)
	{
		if (!st.value)return NULL_ARGUMENT;
		if (stack_ok() == 1)
			return 1;

		st.value = (T*)realloc(st.value, sizeof(T)* (st.Count + 1));
		assert(st.value);
		st.value[st.Count++] = value;

		if (!st.Count)return NULL_ARGUMENT;
		if (stack_ok() == 1)
			return 1;

		return 0;
	}

	int add()
	{

		if (stack_ok() == 1)
			return 1;

		double a = st.value[--st.Count];
		double b = st.value[--st.Count];
		st.value[st.Count++] = a + b;
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		if (stack_ok() == 1)
			return 1;
		return 0;
	}

	T stack_pop()
	{
		if (stack_ok() == 1)
			return 1;

		if (st.Count > 0)
			return st.value[--st.Count];
		else
		{
			return FAIL_POP;
		}
	}
	int div()
	{
		if (stack_ok() == 1)
			return 1;

		double a = st.value[--st.Count];
		double b = st.value[--st.Count];

		if (a != 0)
		{
			st.value[st.Count++] = b / a;
			if (st.value[st.Count] == -0.0)
				st.value[st.Count] = 0.0;
			if (stack_ok() == 1)
				return 1;
			return 0;
		}

		return 1;

	}
	int mul()
	{
		if (stack_ok() == 1)
			return 1;
		double a = st.value[--st.Count];
		double b = st.value[--st.Count];
		st.value[st.Count++] = a * b;
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		if (stack_ok() == 1)
			return 1;
		return 0;
	}
	int sqrt()
	{
		if (stack_ok() == 1)
			return 1;

		double a = st.value[--st.Count];

		st.value[st.Count++] = sqrtf(a);
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		if (stack_ok() == 1)
			return 1;
		return 0;
	}
	int stack_ok()
	{
		if ((st.Count >= 0) && (st.value != NULL))
			return 0;
		return 1;
	}


};

template <typename T, typename T2>
stack<T> operator +(stack<T> st, T2 value)
{
	st.stack_push(value);
	return st;
}

struct stackt
{
	int Count = POISON;
	double* value = NULL;
};


int stack_ok(stackt *st);

int stack_push(stackt *st, double value);

double stack_pop(stackt *st);

int add(stackt *st);

int sqrt(stackt *st);

int mul(stackt *st);

int div(stackt *st);//a*b

int stack_ctor(stackt *st);

int stack_dtor(stackt *st);

int stack_print(stackt *st);
