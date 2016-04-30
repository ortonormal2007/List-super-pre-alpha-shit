#include <iostream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

ostream& operator<<(ostream& o, string& s)
{
	o << s.c_str();
	return o;
}

istream& operator>>(istream& i, string& s)
{
	char buf[256];
	i >> buf;
	string tmp(buf);
	s = tmp;

	return i;
}


template<typename T> class AbstractList
{
protected:
	T _default;
public:
	virtual void sort(bool(*f) (T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T data) = 0;
	virtual void insert(int index, T data) = 0;
	virtual T remove(int index) = 0;
	virtual int len() = 0;
	void push(T data)
	{
		insert(0, data);
	}
	virtual T pop()
	{
		if (empty())
			return _default;
		else
			return remove(0);
	}

	virtual bool empty()
	{
		return len() == 0;
	}

	virtual ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i++)
		{
			o << get(i) << endl;
		}
		return o;
	}

	virtual istream& read(istream& in)
	{
		int count;
		in >> count;
		for (int i = 0; i < count; i++)
		{
			T tmp;
			in >> tmp;
			insert(len(), tmp);
		}
		return in;
	}

};


//todo con ?copy, +assign, +dest

template<typename T> class MyList : public AbstractList<T>
{
	int listnumber;
	MyList* next;
	T data;
public:

	MyList(const MyList& A) {
		listnumber = A.listnumber + 1;
		next = A.next;
		data = A.data;
		this->_default = A._default;
		cout << "shit_cpy" << endl;
	}

	MyList() {
		listnumber = 0;
		next = NULL;
	}

	MyList(T def, T dat) {
		listnumber = 0;
		this->_default = def;
		data = dat;
		next = NULL;
		cout << "shit_constr" << endl;
	}

	T get(int index) {
		int ind = index + 1;
		if (ind > len()) {
			return this->_default;
		}
		MyList* tmp = this;
		MyList tmp1;
		while ((ind != 0))
		{
			tmp = tmp->next;
			ind--;
		}
		tmp1 = *tmp;
		return tmp1.data;
	}

	MyList& operator= (const MyList& A) {
		if (this == &A) {
			return *this;
		}
		listnumber = A.listnumber;
		this->_default = A._default;
		data = A.data;
		delete next;
		next = A.next;
		return *this;
		cout << "shit_assign" << endl;
	}

	virtual ~MyList() {
		next = NULL;
	}

	void sort(bool(*f) (T* first, T* second))
	{
		int total = 0;
		while (true) {
			total = 0;
			MyList<T>* current = this->next;
			while (current->next != nullptr) {
				if (f(&(current->next->data), &(current->data))) {
					T temp = current->data;
					current->data = current->next->data;
					current->next->data = temp;
					total++;
				}
				current = current->next;
			}
			if (total == 0) break;
		}
	}

	void set(int index, T dat)
	{
		int ind = index + 1;
		if (ind > len()){
			return;
		}
		MyList* tmp = this;
		while (ind != 0 && tmp->next != NULL)
		{
			tmp = tmp->next;
			ind--;
		}
		tmp->data = dat;
	}

	void insert(int ind, T data)
	{
		int index = ind;
		if (ind > len()){
			return;
		}
		MyList* tmp = this;
		while (index != 0 && tmp->next != NULL)
		{
			tmp = tmp->next;
			index--;
		}
		MyList* A = new MyList();
		A->next = tmp->next;
		tmp->next = A;
		set(ind, data);
	}

	T remove(int ind)
	{
		cout << "shit" << endl;
		int index = ind;
		if (index < 0) {
			return this->_default;
			cout << "shit_completely" << endl;
		}
		MyList* tmp = this->next;
		MyList* tmpprev = this;
		cout << "shit_completely1" << endl;
		while (index != 0 && tmp->next != NULL)
		{
			cout << "shit_cycle" << endl;
			tmpprev = tmp;
			tmp = tmp->next;
			index--;
		}

		if (index != 0) return this->_default;
                if (tmp == nullptr) return this->_default;
		cout << "shit_completely1" << endl;
		tmpprev->next = tmp->next;
		T old = tmp->data;
		cout << "shit_completely2" << endl;
		delete tmp;
		cout << "shit_completely3" << endl;
		return old;
	}


	int len()
	{
		int num = 0;
		MyList* tmp = this;
		while (tmp->next != NULL) {
			tmp = tmp->next;
			num++;
		}
		return num;
	}
};



MyList<string>* get_init()
{
	string e("EMPTY!");
	string d("Hello world!");
	MyList<string>* s = new MyList<string>(e, d);
	return s;
}



//bool f(int* fi, int* se) {
//	if (*fi < *se) return true;
//	else return false;
//}
//
//bool f2(string* str1, string* str2) {
//
//	if (strcmp(str1->c_str(), str2->c_str()) < 0) {
//
//		return true;
//	}
//	else {
//
//		return false;
//	}
//}


//int main()
//{

//	MyList<string>* ex = get_init();
//	for(int t = 0; t < 1000000; t++){
//	ex->remove(1);
//	}

//	ex->print(cout);


	//example->push("ops");

	//example->print(cout);

	//cout << example->get(0) << endl;



	//system("pause");


//	for (int i = 0; i < 1000000; i++)
//	{
//		int a = rand();
//		string s = to_string(a);
//		example->push(s);
//	}

//	cout << "Current length = " << example->len() << endl;

//	string randomString = example->remove(rand());

//	cout << "Random deleted element = " << randomString << endl;

//	cout << "New length = " << example->len() << endl;


	//example->print(cout);

//	return 0;
//}
