#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#pragma once
#include <iostream>
#include <cstdio>
#include<queue>
#include <vector>
using namespace std;



namespace MyName
{
	/*used in the Aho-Corasik algorithm, the value must be greater than the sum 
	of the length of all words, the occurrence of which is to be found*/
	constexpr int cMaxS = 500;
	/* used in the aho korsik algorithm, the value is equal to the number of characters in
	the alphabet in which the search is performed*/
	constexpr int cMaxC = 26;

	/*used in Buer Moore's algorithm, equal to the size of the shift table*/
	constexpr unsigned int cSizeTable = 256;

	/*the number of characters after the decimal point -1 that will
	be written to the string when writing a float variable*/
	constexpr unsigned int cAfterPoint = 4;
}





class MyString
{
	
public:

	MyString();
	MyString(const MyString &str);
	MyString(const unsigned int count, const char symbol);
	MyString(const char *str);
	MyString(const initializer_list<char> &str);
	MyString(const std::string &str);
	MyString(const char *str, unsigned int count);



	

	unsigned int Length() const;
	bool Empty() const;
	void Clear();
	char* CStr() const;
	char* Data() const;
	unsigned int Size() const;
	unsigned int Capacity() const;
	void ShrinkToFit();


	MyString& operator=(const char* str);
	MyString& operator=(const MyString &string);
	MyString& operator=(const std::string &str);
	MyString& operator=(const char symbol);
	
	MyString& operator+=(const MyString &right_string);
	MyString operator+(const MyString& right) const;
	MyString operator+(const char* string) const;
	MyString operator+(const std::string &string) const;



	MyString& operator+=(const char* string);
	MyString& operator+=(const std::string &string);
	char& operator[](const unsigned int count);

	bool operator<(const MyString& string_object) const;
	bool operator<=(const MyString& string_object) const;
	bool operator>(const MyString& string_object) const;
	bool operator>=(const MyString& string_object) const;
	bool operator==(const MyString& string_object) const;
	bool operator!=(const MyString& string_object) const;

	friend ostream& operator<<(ostream &os, const MyString &string);
	friend istream& operator >> (istream &is, MyString &string);

	void Insert(const unsigned int index, const unsigned int count, const char symbol);
	void Insert(const unsigned int index, const char *string);
	void Insert(const unsigned int index, const char *string, const unsigned int count);
	void Insert(const unsigned int index, const std::string& string);
	void Insert(const unsigned int index, const std::string& string, const unsigned int count);

	void Erase(const unsigned int index, const unsigned int count);

	void AppEnd(const char *string);
	void AppEnd(const unsigned int count, const char symbol);
	void AppEnd(const char *string, const unsigned int index, unsigned int count);
	void AppEnd(const std::string& string);
	void AppEnd(const std::string& string, const unsigned int index, unsigned int count);

	void Replace(const unsigned int index, const unsigned int count, const char *string);
	void Replace(const unsigned int index, const unsigned int count, const std::string& string);


	MyString Substr(const unsigned int index) const;
	MyString Substr(const unsigned int index, const unsigned int count) const;

	int Find(const char *substring) const;
	int Find(const char *substring, unsigned int index) const;
	int Find(const std::string& substring) const;
	int Find(const std::string& string, const unsigned int index) const;
	~MyString();

protected:
	char *string_;
	unsigned int capacity_;
	unsigned int MemoryReAllocation(const unsigned int size_string);
};

class PythString : public MyString
{
public:



	PythString() {};
	PythString(const MyString& string) : MyString(string) {};
	PythString(const PythString& string) : MyString(string) {};
	PythString(const char* const string) : MyString(string) { };
	PythString(const std::string& std_string) : MyString(std_string) { };
	PythString(const size_t count, const char symbol) : MyString(count, symbol) {};
	PythString(const char* const cchar_array, const size_t count) : MyString(cchar_array, count) { };

	using MyString::operator=;
	using MyString::operator+;
	using MyString::operator<;
	using MyString::operator>;
	using MyString::operator<=;
	using MyString::operator>=;
	using MyString::operator==;
	using MyString::operator!=;
	using MyString::operator+=;

	~PythString() {};

	//for Python
	char* __str__();
	void __setitem__(unsigned int i, char symbol);
	char __getitem__(unsigned int i);
};




#endif // __MYSTRING_H_