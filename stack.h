
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

class exception_parent
{
public: 
	 virtual char* WhatIsIt()
	{
		char* answer = new char[10];
		sprintf(answer, "Unknown exception");
		return answer;
	}
};

class damaged_class_exception : public exception_parent
{
public:
	 virtual char* WhatIsIt()
	{
		char* answer = new char[10];
		sprintf(answer, "Stack is damaged!");
		return answer;
	}
};

class division_by_zero_exception : public exception_parent
{
public:
	virtual char* WhatIsIt()
	{
		char* answer = new char[10];
		sprintf(answer, "Division by zero!");
		return answer;
	}
};

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
		if (st.value == NULL) throw(new damaged_class_exception);
		//assert(st.value);
	}
	//~stack();

	stack plus()
	{
		return *this;
	}

	int stack_push(T value)
	{
		if (!st.value)throw(new damaged_class_exception);
		stack_ok();
		assert(st.value);
		st.value = (T*)realloc(st.value, sizeof(T)* (st.Count + 1));
		assert(st.value);
		st.value[st.Count++] = value;

		if (!st.Count)return NULL_ARGUMENT;
		stack_ok();

		return 0;
	}

	int add()
	{

		stack_ok();

		double a = st.value[--st.Count];
		double b = st.value[--st.Count];
		st.value[st.Count++] = a + b;
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		stack_ok();
		return 0;
	}

	T stack_pop()
	{
		stack_ok();
			

		if (st.Count > 0)
			return st.value[--st.Count];
		else
		{
			return FAIL_POP;
		}
	}
 int div()
	{
		stack_ok();
		T a = st.value[--st.Count];
		T b = st.value[--st.Count];
		try
		{
			

			if (a != 0)
			{
				st.value[st.Count++] = b / a;
				if (st.value[st.Count] == -0.0)
					st.value[st.Count] = 0.0;
				stack_ok();
				return 0;
			}
			else throw new division_by_zero_exception;
		}
		catch (division_by_zero_exception* er)
		{
			//this* = this* + b
			//this* = this* + a;
			stack_push(b);
			stack_push(a);
			printf("%s", er->WhatIsIt());
		}
		catch (...)
		{
			printf("SMTH WENT WRONG!");
		}

		return 1;

	}
	int mul()
	{
		stack_ok();
		double a = st.value[--st.Count];
		double b = st.value[--st.Count];
		st.value[st.Count++] = a * b;
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		stack_ok();
		return 0;
	}
	int sqrt()
	{
		stack_ok();

		double a = st.value[--st.Count];

		st.value[st.Count++] = sqrtf(a);
		if (st.value[st.Count - 1] == -0.0)
			st.value[st.Count - 1] = 0.0;

		stack_ok();
		return 0;
	}
	void stack_ok()
	{
		if ((st.Count >= 0) && (st.value != NULL))
			return ;
		throw(new damaged_class_exception);
	}


};

template <typename T, typename T2>
stack<T> operator +(stack<T> st, T2 value)
{
	st.stack_push(value);
	return st;
}


//next lines are for deprecated functions that used in my other projects



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

int div(stackt *st);

int stack_ctor(stackt *st);

int stack_dtor(stackt *st);

int stack_print(stackt *st);
