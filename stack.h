
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
const int	 EXCEPTION_LENGTH = 50;
const int	 HALF_OF_MAX_STACK_SIZE = 8388609;
class exception_parent
{
public: 
	 virtual char* WhatIsIt()
	{
		char* answer = new char[EXCEPTION_LENGTH];
		sprintf(answer, "Unknown exception");
		return answer;
	}
};

class damaged_class_exception : public exception_parent
{
public:
	 virtual char* WhatIsIt()
	{
		char* answer = new char[EXCEPTION_LENGTH];
		sprintf(answer, "Stack is damaged!");
		return answer;
	}
};

class trying_to_pop_from_empty_stack : public exception_parent
{
public:
	virtual char* WhatIsIt()
	{
		char* answer = new char[EXCEPTION_LENGTH];
		sprintf(answer, "Stack is empty!Can't pop!");
		return answer;
	}
};

class stack_overflow : public exception_parent
{
public:
	virtual char* WhatIsIt()
	{
		char* answer = new char[EXCEPTION_LENGTH];
		sprintf(answer, "Stack overflow! Try to use less than 2^14(16777216) elements!");
		return answer;
	}
};


class division_by_zero_exception : public exception_parent
{
public:
	virtual char* WhatIsIt()
	{
		char* answer = new char[EXCEPTION_LENGTH];
		sprintf(answer, "Division by zero!");
		return answer;
	}
};

template <typename T>
class stack
{
public:
	int current_max_size = 1;
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
		
		stack_ok();
		if (st.Count + 1 >= current_max_size&&current_max_size<HALF_OF_MAX_STACK_SIZE) //double max size if it didnt reach cap
		{
			current_max_size *= 2;
			
			st.value = (T*)realloc(st.value, sizeof(T) * current_max_size);
		}
		stack_ok();
		st.value[st.Count] = value;
		st.Count++;
		stack_ok();
		if (!st.Count)return NULL_ARGUMENT;
		

		return 0;
	}

	int add()
	{

		stack_ok();

		double a = st.value[--st.Count];
		double b = st.value[--st.Count];
		st.value[st.Count++] = a + b;
		if (st.value[st.Count - 1] == -0.0)   //no more -0.0
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
			throw(new trying_to_pop_from_empty_stack);
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
			

			if (a != 0)     //catch exception division by 0
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
		if ((st.Count >= 0) && (st.value != NULL) && (st.Count+1 <= current_max_size))
			return;
		if (st.Count >= current_max_size) throw(new stack_overflow);
		//if (st.value == NULL)throw(new stack_overflow);
		throw(new damaged_class_exception);
	}


};

template <typename T, typename T2>
stack<T> operator +(stack<T> st, T2 value)
{
	st.stack_push(value);
	return st;
}


