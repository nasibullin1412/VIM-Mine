#include "mystring.h"


//default constructor
MyString::MyString()
{
	string_ = new char[1];
	if (string_)
	{
		string_[0] = '\0';
		capacity_ = 1;
	}
	else
	{
		string_ = nullptr;
		capacity_ = 0;
	}
}

//copy constructor 
MyString::MyString(const MyString &str)
{
	if (str.Capacity() != 0)
	{
		unsigned int size = str.capacity_ - 1;
		this->string_ = new char[size + 1];
		if (string_)
		{
			this->capacity_ = size + 1;
			for (unsigned int i = 0; i < size; i++)
			{
				this->string_[i] = str.string_[i];
			}
			this->string_[size] = '\0';
		}
		else
		{
			this->string_ = nullptr;
			this->capacity_ = 0;
		}
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}

MyString::MyString(const char *str)
{
	if (str != nullptr)
	{
		unsigned int str_size = 0;
		while (str[str_size] != '\0')
		{
			++str_size;
		}
		string_ = new char[str_size+1];
		if (string_)
		{
			capacity_ = str_size+1;
			for (unsigned int i = 0; i < str_size; ++i)
			{
				string_[i] = str[i];
			}
			this->string_[str_size] = '\0';
		}
		else
		{
			this->string_ = nullptr;
			this->capacity_ = 0;
		}
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}



//initializer list constructor
MyString::MyString(const initializer_list<char> &str)
{
	int size = 0;
	size = str.size();
	string_ = new char[size+1];
	if (string_)
	{
		capacity_ = size+1;
		int i = 0;
		for (char symbol : str)
		{
			string_[i] = symbol;
			++i;
		}
		string_[i] = '\0';
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}


// std::string constructor
MyString::MyString(const std::string &str)
{
	if (!str.empty())
	{
		int number = str.length();
		string_ = new char[number + 1];
		if (string_)
		{
			capacity_ = number + 1;
			for (int i = 0; i < number; ++i)
			{
				string_[i] = str[i];
			}
			string_[number] = '\0';
		}
		else
		{
			this->string_ = nullptr;
			this->capacity_ = 0;
		}
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}


//init class with count characters of  “char string”, Constructor(“hello”, 4)
MyString::MyString(const char *str, unsigned int count)
{
	if (str != nullptr)
	{
		unsigned int number = 0;
		while (str[number] != 0)
		{
			++number;
		}
		if (number < count)
		{
			count = number;
		}
		this->string_ = new char[count + 1];
		if (this->string_)
		{
			this->capacity_ = count + 1;
			unsigned int i = 0;
			for (i = 0; i < count; ++i)
			{
				this->string_[i] = str[i];
			}
			this->string_[i] = '\0';
		}
		else
		{
			this->string_ = nullptr;
			this->capacity_ = 0;
		}
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}


MyString::MyString(const unsigned int count, const char symbol)
{
	if (count != 0)
	{
		this->string_ = new char[count + 1];
		if (this->string_)
		{
			this->capacity_ = count + 1;
			for (unsigned int i = 0; i < count; i++)
			{
				this->string_[i] = symbol;
			}
			this->string_[count] = '\0';
		}
		else
		{
			this->string_ = nullptr;
			this->capacity_ = 0;
		}
	}
	else
	{
		this->string_ = nullptr;
		this->capacity_ = 0;
	}
}



MyString & MyString::operator=(const MyString &string)
{
	unsigned int cur_capacity = this->capacity_;
	if (this->capacity_ > 1)
	{
		this->Clear();
	}
	if (string.string_ != nullptr)
	{
		unsigned int size_string = string.Length();
		if (cur_capacity <= size_string + 1)
		{
			cur_capacity = MemoryReAllocation(size_string);
		}
		if (this->string_)
		{
			for (unsigned int i = 0; i < size_string; ++i)
			{
				this->string_[i] = string.string_[i];
			}
			this->string_[size_string] = '\0';
			this->capacity_ = cur_capacity;
		}
	}
	return *this;
}


MyString& MyString::operator=(const char* string)
{
	unsigned int cur_capacity = this->capacity_;
	if (cur_capacity > 1)
	{
		this->Clear();
	}
	unsigned int size_string = 0;
	if (string != nullptr)
	{
		while (string[size_string] != '\0')
		{
			++size_string;
		}
		if (cur_capacity <= size_string + 1)
		{
			cur_capacity = MemoryReAllocation(size_string);
		}
		if (this->string_)
		{
			for (unsigned int i = 0; i < size_string; ++i)
			{
				this->string_[i] = string[i];
			}
			this->string_[size_string] = '\0';
			this->capacity_ = cur_capacity;
			return *this;
		}
	}
	this->Clear();

	return *this;
}

// std::string assignment
MyString& MyString::operator=(const std::string &string)
{
	unsigned int cur_capacity = this->capacity_;
	if (!this->Empty())
	{
		this->Clear();
	}
	unsigned int size_string = string.size();
	if (cur_capacity <= size_string + 1)
	{
		cur_capacity = MemoryReAllocation(size_string);
	}
	if (this->string_)
	{
		for (unsigned int i = 0; i < size_string; ++i)
		{
			this->string_[i] = string[i];
		}
		this->string_[size_string] = '\0';
		this->capacity_ = cur_capacity;
	}
	else
	{
		this->Clear();
	}
	return *this;
}


// char assignment
MyString& MyString::operator=(const char symbol)
{
	unsigned int cur_capacity = this->capacity_;
	if (!this->Empty())
	{
		this->Clear();
	}
	if (cur_capacity < 2)
	{
		cur_capacity = MemoryReAllocation(1);
	}
	this->capacity_ = cur_capacity;
	this->string_[0] = symbol;
	this->string_[1] = '\0';
	return *this;
}


MyString& MyString::operator+=(const MyString &right_string)
{
	this->AppEnd(right_string.string_);
	return *this;
}


MyString MyString::operator+(const MyString& right) const
{
	MyString new_obj;
	if (this->Empty())
	{
		new_obj = right.string_;
	}
	else
	{
		unsigned int size = this->Length();
		unsigned int size_string = right.Length();
		unsigned int new_string = size + size_string;
		char *temp = new char[new_string+1];
		if (temp)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				temp[i] = this->string_[i];
			}
			unsigned int count_str = 0;
			for (unsigned int i = size; i < new_string; ++i)
			{
				temp[i] = right.string_[count_str];
				++count_str;
			}
			temp[new_string] = '\0';
			new_obj = temp;
			delete[] temp;
		}
	}
	return new_obj;
}

//concatenate with char array
MyString MyString::operator+(const char *string) const
{
	MyString new_object;
	if (this->Empty())
	{
		new_object = string;
	}
	else
	{
		if (string != nullptr)
		{
			unsigned int size_first_string = this->Length();
			unsigned int size_second_string = 0;
			while (string[size_second_string] != '\0')
			{
				++size_second_string;
			}
			char *temp = new char[size_first_string + size_second_string + 1];
			if (temp)
			{
				size_first_string;
				for (unsigned int i = 0; i < size_first_string; ++i)
				{
					temp[i] = this->string_[i];
				}
				for (unsigned int i = 0; i < size_second_string; ++i)
				{
					temp[size_first_string + i] = string[i];
				}
				temp[size_first_string + size_second_string] = '\0';
				new_object = temp;
				delete[] temp;
			}
		}
		else
		{
			new_object = this->string_;
		}
	}
	return new_object;
}

//concatenate with std::string
MyString MyString::operator+(const std::string &string) const
{
	MyString new_object;
	if (this->Empty())
	{
		new_object = string;
	}
	else
	{
		unsigned int size_first_string = this->Length();
		unsigned int size_second_string = string.length();
		char *temp = new char[size_first_string + size_second_string + 1];
		if (temp)
		{
			size_first_string;
			for (unsigned int i = 0; i < size_first_string; ++i)
			{
				temp[i] = this->string_[i];
			}
			for (unsigned int i = 0; i < size_second_string; ++i)
			{
				temp[size_first_string + i] = string[i];
			}
			temp[size_first_string + size_second_string] = '\0';
			new_object = temp;
			delete[] temp;
		}
	}
	return new_object;
}

//assignment concatenate with char array
MyString& MyString::operator+=(const char* string)
{
	if (this->capacity_ == 0)
	{
		*this = string;
	}
	else
	{
		unsigned int size_first_string = this->Length();
		unsigned int size_second_string = 0;
		if (string != nullptr)
		{
			while (string[size_second_string] != '\0')
			{
				++size_second_string;
			}
			unsigned int size_new_string = size_first_string + size_second_string + 1;
			if (this->capacity_ <= size_new_string)
			{
				char *temp = new char[size_new_string];		
				if (temp)
				{
					for (unsigned int i = 0; i < size_first_string; ++i)
					{
						temp[i] = this->string_[i];
					}
					for (unsigned int i = 0; i < size_second_string; ++i)
					{
						temp[size_first_string + i] = string[i];
					}
					temp[size_first_string + size_second_string] = '\0';
					*this = temp;
					delete []temp;
				}
			}
			else
			{
				for (unsigned int i = 0; i < size_second_string; ++i)
				{
					this->string_[size_first_string + i] = string[i];
				}
				this->string_[size_first_string + size_second_string] = '\0';
			}
		}
	}
	return *this;
}

// assignment concatenate with std::string
MyString& MyString::operator+=(const std::string &string)
{
	if (this->capacity_ == 0)
	{
		*this = string;
	}
	else
	{
		unsigned int size_first_string = this->Length();
		unsigned int size_second_string = string.length();
		unsigned int size_new_string = size_first_string + size_second_string + 1;
		if (this->capacity_ <= size_new_string)
		{
			char *temp = new char[size_first_string + size_second_string + 1];
			if (temp)
			{
				for (unsigned int i = 0; i < size_first_string; ++i)
				{
					temp[i] = this->string_[i];
				}
				for (unsigned int i = 0; i < size_second_string; ++i)
				{
					temp[size_first_string + i] = string[i];
				}
				temp[size_first_string + size_second_string] = '\0';
				*this = temp;
				delete[] temp;
			}
		}
		else
		{
			for (unsigned int i = 0; i < size_second_string; ++i)
			{
				this->string_[size_first_string + i] = string[i];
			}
			this->string_[size_first_string + size_second_string] = '\0';
		}
	}
	return *this;
}


//index operator
char& MyString::operator[](const unsigned int count)
{
	unsigned int length = this->Length();
	if (count <= length || count < 0)
	{
		return this->string_[count];
	}
	return this->string_[length];
}

// lexicographically comparing

bool MyString ::operator<(const MyString& string_object) const
{
	if (string_object.Empty())
	{
		return false;
	}
	else
	{
		if (this->Empty())
		{
			return true;
		}
		int count = 0;
		int size_first = this->Length() - 1;
		int size_second = string_object.Length() - 1;
		if (size_first < size_second)
		{
			return true;
		}
		else
		{
			if (size_first > size_second)
			{
				return false;
			}
			while (count < size_first && this->string_[count] == string_object.string_[count])
			{
				++count;
			}
			if (this->string_[count] < string_object.string_[count])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool MyString ::operator<=(const MyString& string_object) const
{
	if (string_object.Empty() && this->Empty())
	{
		return true;
	}
	else
	{
		if (this->Empty())
		{
			return true;
		}
		else
		{
			if (string_object.Empty())
			{
				return false;
			}
		}
		unsigned int count = 0;
		unsigned int size_first = this->Length() - 1;
		unsigned int size_second = string_object.Length() - 1;
		if (size_first < size_second)
		{
			return true;
		}
		else
		{
			if (size_first > size_second)
			{
				return false;
			}
			while (count < size_first && this->string_[count] == string_object.string_[count])
			{
				++count;
			}
			if (this->string_[count] <= string_object.string_[count] )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool MyString ::operator>(const MyString& string_object) const
{
	return !(*this <= string_object);
}

bool MyString ::operator>=(const MyString& string_object) const
{
	return !(*this < string_object);
}

bool MyString::operator==(const MyString& string_object) const
{
	if (*this > string_object || *this < string_object)
	{
		return false;
	}
	return true;
}

bool MyString::operator!=(const MyString& string_object) const
{
	return !(*this == string_object);
}


//return number of symbols in string
unsigned int MyString::Length()const
{

	if (this->capacity_ > 1)
	{
		unsigned int left_size = 0;
		unsigned int right_size = this->capacity_ -1;
		// bad idea
		while (this->string_[left_size] != '\0' && this->string_[right_size] == '\0')
		{
			++left_size;
			--right_size;
		}
		if (this->string_[left_size] == '\0')
		{
			return left_size;
		}
		return right_size+1;
	}
	return 0;
}

unsigned int MyString::Size()const
{
	return Length();
}

bool MyString::Empty()const
{
	/*if (this->capacity_ != 0)
	{
		if (this->string_ != nullptr)
		{
			if (this->string_[0] != '\0')
			{
				return false;
			}
		}
	}*/
	if (this->Length() == 0)
	{
		return true;
	}
	return false;
}

// remove all char element in string
void MyString::Clear()
{
	if (this->capacity_ != 1)
	{
		/*delete this->string_;
		this->capacity_ = 0;
		this->string_ = nullptr;*/
		for (size_t i = 0; i < this->capacity_; ++i)
		{
			this->string_[i] = '\0';
		}
	}
}

// return a pointer to null-terminated character array
char* MyString::CStr()const
{
	/*if (!this->Empty())
	{
		unsigned int size = this->Size();
		char *temp = new char[size + 1];
		if (temp)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				temp[i] = this->string_[i];
			}
			temp[size] = '\0';
		}
		return temp;
	}
	return nullptr;*/
	return this->string_;
}

// return a pointer to array data that not required to be 
char* MyString::Data()const
{
	/*unsigned int size = this->Length();
	char *temp = new char[size];
	if (temp)
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			temp[i] = this->string_[i];
		}
	}
	return temp;*/
	return this->string_;
}

// return the current amount of allocated memory for array
unsigned int MyString::Capacity()const
{
	return this->capacity_;
}

// reduce the capacity to size
void MyString::ShrinkToFit()
{
	if (this->Capacity() != this->Size())
	{
		unsigned int size = this->Size();
		char *temp = new char[size + 1];
		if (temp)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				temp[i] = this->string_[i];
			}
			temp[size] = '\0';
		}
		if (!this->Empty())
		{
			this->~MyString();
		}
		*this = temp;
		delete[] temp;
	}
}

ostream& operator<<(ostream &os, const MyString &string_obj)
{
	if (string_obj.capacity_ != 0)
	{
		os << string_obj.string_;
	}
	return os;
}

istream & operator >> (istream & is, MyString &string_obj)
{
	char buffer[4096] = { '\0' };
	is >> buffer;
	if (string_obj.string_)
	{
		string_obj.Clear();
	}

	string_obj.AppEnd(buffer);
	return is;
}


void MyString::Insert(const unsigned int index, const unsigned int count, const char symbol)
{
	if (count != 0)
	{
		char *temp = new char[count + 1];
		if (temp == nullptr)
		{
			return;
		}
		for (unsigned int i = 0; i < count; ++i)
		{
			temp[i] = symbol;
		}
		temp[count] = '\0';
		this->Insert(index, temp);
		delete[] temp;
	}
}
// insert null-terminated char string at index position
void MyString::Insert(const unsigned int index, const char *string)
{
	if (this->Empty())
	{
		if (index == 0)
		{
			this->AppEnd(string);
		}
	}
	else
	{
		unsigned int size = this->Length();
		if (string == nullptr || size < index)
		{
			return;
		}
		unsigned int size_string = 0;
		while (string[size_string] != '\0')
		{
			++size_string;
		}
		unsigned int new_size_string = size + size_string + 1;

		char* temp = new char[new_size_string];
		for (unsigned int i = 0; i < index; ++i)
		{
			temp[i] = this->string_[i];
		}
		for (unsigned int i = 0; i < size_string; ++i)
		{
			temp[index + i] = string[i];
		}
		unsigned int sum = index + size_string;
		unsigned int count_string = index;
		unsigned int delta = size - index;
		for (unsigned int i = 0; i < delta; ++i)
		{
			temp[sum + i] = this->string_[count_string + i];
		}
		temp[size + size_string] = '\0';
		*this = temp;
		delete[] temp;
	}
}

// insert count of null-terminated char string at index position
void MyString::Insert(const unsigned int index, const char *string, const unsigned int count)
{
	unsigned int size_string = 0;
	if (string == nullptr)
	{
		return;
	}
	while (string[size_string] != '\0')
	{
		++size_string;
	}
	unsigned int last_index = 0;
	if (count > size_string)
	{
		last_index = size_string;
	}
	else
	{
		last_index = count;
	}
	char *temp = new char[last_index + 1];
	if (temp == nullptr)
	{
		return;
	}
	for (unsigned int i = 0; i < last_index; ++i)
	{
		temp[i] = string[i];
	}
	temp[last_index] = '\0';
	this->Insert(index, temp);
	delete[] temp;
}

// insert std::string at index position
void MyString::Insert(const unsigned int index, const std::string& string)
{
	unsigned int size = this->Size();
	unsigned int size_string = string.length();
	if (size < index || size_string == 0)
	{
		return;
	}
	char *temp = new char[size_string + 1];
	if (temp == nullptr)
	{
		return;
	}
	for (unsigned int i = 0; i < size_string; ++i)
	{
		temp[i] = string[i];
	}
	temp[size_string] = '\0';
	this->Insert(index, temp);
	delete[] temp;
}

// insert count of std::string at index position
void MyString::Insert(const unsigned int index, const std::string& string,const unsigned int count)
{
	unsigned int size_string = string.length();
	unsigned int last_index = 0;
	if (count > size_string)
	{
		last_index = size_string;
	}
	else
	{
		last_index = count;
	}
	char *temp = new char[last_index + 1];
	if (temp == nullptr)
	{
		return;
	}
	for (unsigned int i = 0; i < last_index; ++i)
	{
		temp[i] = string[i];
	}
	temp[last_index] = '\0';
	this->Insert(index, temp);
	delete[] temp;
}


// erase count of char at index position
void MyString::Erase(const unsigned int index, const unsigned int count)
{
	unsigned int size = this->Size()+1;
	unsigned int last_index = index + count;
	if (size > last_index)
	{
		size -= count;
		for (unsigned int i = index; i < last_index; ++i)
		{
			this->string_[i] = this->string_[i + count];
		}
		for (unsigned int i = last_index; i < size; ++i)
		{
			this->string_[i] = this->string_[i + count];
		}
	}
}

void MyString::AppEnd(const char *string)
{
	unsigned int size = this->Length();
	unsigned int size_string = 0;
	if (string != nullptr)
	{
		while (string[size_string] != '\0')
		{
			++size_string;
		}
	}
	if (size_string != 0)
	{
		unsigned int size_new_string = size + size_string + 1;
		if (this->capacity_ <= size_new_string)
		{
			char *temp = new char[size_new_string];
			if (temp)
			{
				for (unsigned int i = 0; i < size; ++i)
				{
					temp[i] = this->string_[i];
				}
				unsigned int count_string = 0;
				for (unsigned int i = size; i < size_new_string; ++i)
				{
					temp[i] = string[count_string];
					++count_string;
				}
				*this = temp;
				delete[] temp;
			}
		}
		else
		{
			unsigned int count_string = 0;
			for (unsigned int i = size; i < size_new_string; ++i)
			{
				this->string_[i] = string[count_string];
				++count_string;
			}
		}
	}
}

// append count of char
void MyString::AppEnd(const unsigned int count, char symbol)
{
	char *temp = new char[count+1];
	if (temp)
	{
		for (unsigned int i = 0; i < count; ++i)
		{
			temp[i] = symbol;
		}
		temp[count] = '\0';
		this->AppEnd(temp);
		delete[] temp;
	}
}

// append a count of null-terminated char string by index position
void MyString::AppEnd(const char *string,const unsigned int index, unsigned int count)
{

	unsigned int size_string = 0;
	if (string == nullptr)
	{
		return;
	}
	while (string[size_string] != '\0')
	{
		++size_string;
	}
	if (count+index > size_string)
	{
		count = size_string - index;
	}
	char *temp = new char[count + 1];
	if (temp)
	{
		for (unsigned int i = 0; i < count; ++i)
		{
			temp[i] = string[i+index];
		}
		temp[count] = '\0';
	}
	this->AppEnd(temp);
	delete[] temp;
}

// append std:: string
void MyString::AppEnd(const std::string& string)
{
	unsigned int size_string = string.length();
	if (size_string == 0)
	{
		return;
	}
	char *temp = new char[size_string+1];
	if (temp)
	{
		for (unsigned int i = 0; i < size_string; ++i)
		{
			temp[i] = string[i];
		}
		temp[size_string] = '\0';
		AppEnd(temp);
		delete[] temp;
	}
}

// append a count of std:: string by index position
void MyString::AppEnd(const std::string& string, const unsigned int index, unsigned int count)
{
	unsigned int size_string = string.length();
	if (index > size_string)
	{
		return;
	}
	if (count + index > size_string)
	{
		count = size_string - index;
	}
	char *temp = new char[count + 1];
	if (temp)
	{
		unsigned int sum = index + count;
		for (unsigned int i = index; i < sum; ++i)
		{
			temp[i - index] = string[i];
		}
		temp[count] = '\0';
		AppEnd(temp);
		delete[] temp;
	}
}

// replace a count of char at index by “string”
void MyString::Replace(const unsigned int index,const unsigned int count, const char *string)
{
	unsigned int size = this->Size();
	unsigned int size_string = 0;
	if (string == nullptr)
	{
		return;
	}
	while (string[size_string] != '\0')
	{
		++size_string;
	}
	unsigned int last_index = index + count;
	if (size >= last_index)
	{
		unsigned int new_string_size = size + size_string - count;
		unsigned int change_size = 0;
		if (count <= size_string)
		{
			new_string_size = size + size_string - count;
			change_size = size_string;
		}
		else
		{
			new_string_size = size;
			change_size = count;
		}
		if (this->capacity_ <= new_string_size)
		{
			char *temp = new char[new_string_size + 1];
			if (temp)
			{
				for (unsigned int i = 0; i < index; ++i)
				{
					temp[i] = this->string_[i];
				}
				unsigned int sum = change_size + index;
				for (unsigned int i = index; i < sum; ++i)
				{
					temp[i] = string[(i - index) % size_string];
				}
				unsigned int string_count = index + count;
				for (unsigned int i = sum; i < new_string_size; ++i)
				{
					temp[i] = this->string_[string_count];
					++string_count;
				}
				temp[new_string_size] = '\0';
				*this = temp;
				delete[] temp;
			}
		}
		else
		{
			unsigned int sum = change_size + index;
			for (unsigned int i = index; i < sum; ++i)
			{
				this->string_[i] = string[(i - index) % size_string];
			}

		}
	}
}

// replace a count of char at index by std::string
void MyString::Replace(const unsigned int index,const unsigned int count, const std::string& string)
{
	unsigned int size_string = string.size();
	if (size_string != 0)
	{
		char *temp = new char[size_string + 1];
		if (temp)
		{
			for (unsigned int i = 0; i < size_string; ++i)
			{
				temp[i] = string[i];
			}
			temp[size_string] = '\0';
			this->Replace(index, count, temp);
			delete[] temp;
		}
	}
}


//return nullptr if index > size of string and return substring if all good
MyString MyString::Substr(const unsigned int index) const
{
	MyString object;
	if (index < this->Size())
	{
		unsigned int size = this->Size();
		char *temp = new char[size - index + 1];
		if (temp)
		{
			for (unsigned int i = index; i < size; ++i)
			{
				temp[i - index] = this->string_[i];
			}
			temp[size - index] = '\0';
		}
		
		object = temp;
		delete[] temp;
	}
	return object;
}

//return a count of substring’s char starts with index position and return nullptr if index+count > size of string
MyString MyString::Substr(const unsigned int index,const unsigned int count) const
{
	unsigned int last_index = index + count;
	unsigned int size = this->Size();
	MyString object;
	if (last_index <= size)
	{
		char *temp = new char[count+1];
		if (temp)
		{
			unsigned int count_temp = 0;
			for (unsigned int i = index; i < last_index; ++i)
			{
				temp[count_temp] = this->string_[i];
				++count_temp;
			}
			temp[count_temp] = '\0';
			object = temp;
			delete[] temp;
		}
	}
	return object;
}

//if founded return the index of substring, else return -1
int MyString::Find(const char *substring) const
{
	unsigned int shift_table[MyName::cSizeTable] = { '\0' };
	unsigned int size = this->Size();
	unsigned int string_size = 0;
	if (substring == nullptr)
	{
		return -1;
	}
	while (substring[string_size] != '\0')
	{
		++string_size;
	}
	if (string_size > size || string_size==0 || size == 0)
	{
		return -1;
	}
	unsigned int idx = 0;
	int j = 0;
	unsigned int cur_idx_in_string = 0, k = 0;
	// Formation of the table of shifts :
	for (idx = 0; idx < MyName::cSizeTable; ++idx) shift_table[idx] = string_size; // initially, all elements are assigned a shift equal to the length of the substring
	for (idx = 0; idx < string_size - 1; ++idx)
	{
		shift_table[substring[idx]] = string_size - 1 - idx;
	} // forming a shift for each character, taking into account its number in the substring
	cur_idx_in_string = string_size;
	do
	{
		j = string_size; k = cur_idx_in_string;
		do
		{
			--k;
			--j;
		} while (j >= 0 && substring[j] == this->string_[k]);
		if (j >= 0)
		{
			cur_idx_in_string += shift_table[this->string_[cur_idx_in_string - 1]]; // Shift a substring to check further if the substring was not found
		}
	} while (j >= 0 && cur_idx_in_string <= size);
	cur_idx_in_string -= string_size;
	if (size - cur_idx_in_string < string_size)
	{
		return -1;
	}
	return cur_idx_in_string;
}

// same as find(“string”) but search starts from index position
int MyString::Find(const char *substring, unsigned int index) const
{
	if (index < this->Size())
	{
		MyString temp_object = &this->string_[index];
		int idx = temp_object.Find(substring);
		if (idx != -1)
		{
			return idx + index;
		}
	}
	return -1;
}

// if founded return the index of substring
int MyString::Find(const std::string& substring) const
{
	unsigned int size_string = substring.size();
	char *temp = new char[size_string + 1];
	for (unsigned int i = 0; i < size_string; ++i)
	{
		temp[i] = substring[i];
	}
	temp[size_string] = '\0';
	int result = this->Find(temp);
	delete[] temp;
	return result;
}

// same as find(“string”) but search starts from index position
int MyString::Find(const std::string& substring, const unsigned int index) const
{
	if (index < this->Size())
	{
		MyString temp_object = &this->string_[index];
		int idx = temp_object.Find(substring);
		if (idx != -1)
		{
			return idx + index;
		}
	}
	return -1;
}


unsigned int MyString::MemoryReAllocation(const unsigned int size_string)
{
	delete this->string_;
	this->string_ = new char[size_string + 1];
	if (this->string_)
	{
		return size_string + 1;
	}
	return 0;
}


MyString::~MyString()
{
	delete this->string_;
	this->string_ = new char[1];
	this->string_[0] = '\0';
	this->capacity_ = 1;
}


void PythString::__setitem__(unsigned int i, char symbol)
{
	if (i <= this->Length() && i >= 0)
		this->CStr()[i] = symbol;
}

char PythString::__getitem__(unsigned int i)
{
	char error = '\0';
	if (i > this->Length() || i < 0)
	{
		return error;
	}
	char* temp = this->CStr();
	return temp[i];
}

char* PythString::__str__()
{
	return this->CStr();
}
