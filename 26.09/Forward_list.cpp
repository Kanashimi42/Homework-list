#include <iostream>
using namespace std;

struct Element
{
	int value;
	Element* next, * prev;
public:
	Element() = default;
	Element(int val) { value = val; }
};

class LinkedList
{
	Element* head, * tail;
	int count;

public:
	LinkedList();
	LinkedList(const LinkedList&);
	~LinkedList();

	int GetCount();
	Element* GetElement(int);

	void DeleteAll();
	void Delete(int position = 0);
	void Insert(int position = 0);

	void AddToTail(int val);
	void AddToHead(int val);

	void Print();
	void Print(int position);

	LinkedList& operator = (const LinkedList&);
	LinkedList operator + (const LinkedList&);

	bool operator == (const LinkedList&);
	bool operator != (const LinkedList&);
	bool operator <= (const LinkedList&);
	bool operator >= (const LinkedList&);
	bool operator < (const LinkedList&);
	bool operator > (const LinkedList&);

	LinkedList operator - ();
};

LinkedList::LinkedList()
{
	head = tail = NULL;
	count = 0;
}

LinkedList::LinkedList(const LinkedList& list)
{
	head = tail = NULL;
	count = 0;

	Element* temp = list.head;

	while (temp != 0)
	{
		AddToTail(temp->value);
		temp = temp->next;
	}
}

LinkedList::~LinkedList()
{
	DeleteAll();
}

void LinkedList::AddToHead(int val)
{
	Element* temp = new Element(val);

	temp->prev = 0;
	temp->next = head;

	if (head != 0)
		head->prev = temp;

	if (count == 0)
		head = tail = temp;
	else
		head = temp;

	count++;
}

void LinkedList::AddToTail(int val)
{
	Element* temp = new Element;
	temp->next = 0;
	temp->value = val;
	temp->prev = tail;

	if (tail != 0)
		tail->next = temp;

	if (count == 0)
		head = tail = temp;
	else
		tail = temp;

	count++;
}

void LinkedList::Insert(int position)
{
	if (position == 0)
	{
		cout << "Input position: ";
		cin >> position;
	}

	if (position < 1 || position > count + 1)
	{
		cout << "Incorrect position !!!\n";
		return;
	}

	if (position == count + 1)
	{
		int val;
		cout << "Input new number: ";
		cin >> val;
		AddToTail(val);
		return;
	}
	else if (position == 1)
	{
		int val;
		cout << "Input new number: ";
		cin >> val;
		AddToHead(val);
		return;
	}

	int i = 1;
	Element* insertElement = head;

	while (i < position)
	{
		insertElement = insertElement->next;
		i++;
	}

	Element* prevInsertElement = insertElement->prev;
	Element* newElement = new Element;

	cout << "Input new number: ";
	cin >> newElement->value;

	if (prevInsertElement != 0 && count != 1)
		prevInsertElement->next = newElement;

	newElement->next = insertElement;
	newElement->prev = prevInsertElement;
	insertElement->prev = newElement;

	count++;
}

void LinkedList::Delete(int position)
{
	if (position == 0)
	{
		cout << "Input position: ";
		cin >> position;
	}

	if (position < 1 || position > count)
	{
		cout << "Incorrect position !!!\n";
		return;
	}

	int i = 1;
	Element* deleteElement = head;

	while (i < position)
	{
		deleteElement = deleteElement->next;
		i++;
	}

	Element* prevDeleteElement = deleteElement->prev;
	Element* nextDeleteElement = deleteElement->next;

	if (prevDeleteElement != 0 && count != 1)
		prevDeleteElement->next = nextDeleteElement;

	if (nextDeleteElement != 0 && count != 1)
		nextDeleteElement->prev = prevDeleteElement;

	if (position == 1)
		head = nextDeleteElement;

	if (position == count)
		tail = prevDeleteElement;

	delete deleteElement;

	count--;
}

void LinkedList::Print(int position)
{
	if (position < 1 || position > count)
	{
		cout << "Incorrect position !!!\n";
		return;
	}

	Element* temp;

	if (position <= count / 2)
	{
		temp = head;
		int i = 1;

		while (i < position)
		{
			temp = temp->next;
			i++;
		}
	}
	else
	{
		temp = tail;
		int i = 1;

		while (i <= count - position)
		{
			temp = temp->prev;
			i++;
		}
	}

	cout << position << " element: ";
	cout << temp->value << endl;
}

void LinkedList::Print()
{
	if (count != 0)
	{
		Element* temp = head;
		cout << "( ";
		while (temp->next != 0)
		{
			cout << temp->value << ", ";
			temp = temp->next;
		}

		cout << temp->value << " )\n";
	}
}

void LinkedList::DeleteAll()
{
	while (count != 0)
		Delete(1);
}

int LinkedList::GetCount()
{
	return count;
}

Element* LinkedList::GetElement(int position)
{
	Element* temp = head;

	if (position < 1 || position > count)
	{
		cout << "Incorrect position !!!\n";
		return 0;
	}

	int i = 1;

	while (i < position && temp != 0)
	{
		temp = temp->next;
		i++;
	}

	if (temp == 0)
		return 0;
	else
		return temp;
}

LinkedList& LinkedList::operator=(const LinkedList& list)
{
	if (this == &list)
		return *this;

	this->~LinkedList();

	Element* temp = list.head;

	while (temp != 0)
	{
		AddToTail(temp->value);
		temp = temp->next;
	}

	return *this;
}

LinkedList LinkedList::operator+(const LinkedList& list)
{
	LinkedList result(*this);

	Element* temp = list.head;

	while (temp != 0)
	{
		result.AddToTail(temp->value);
		temp = temp->next;
	}

	return result;
}

bool LinkedList::operator==(const LinkedList& list)
{
	if (count != list.count)
		return false;

	Element* t1, * t2;

	t1 = head;
	t2 = list.head;

	while (t1 != 0)
	{
		if (t1->value != t2->value)
			return false;

		t1 = t1->next;
		t2 = t2->next;
	}

	return true;
}

bool LinkedList::operator!=(const LinkedList& list)
{
	return !(*this == list);
}

bool LinkedList::operator>=(const LinkedList& list)
{
	if (count > list.count)
		return true;

	if (*this == list)
		return true;

	return false;
}

bool LinkedList::operator<=(const LinkedList& list)
{
	if (count < list.count)
		return true;

	if (*this == list)
		return true;

	return false;
}

bool LinkedList::operator>(const LinkedList& list)
{
	if (count > list.count)
		return true;

	return false;
}

bool LinkedList::operator<(const LinkedList& list)
{
	if (count < list.count)
		return true;

	return false;
}

LinkedList LinkedList::operator-()
{
	LinkedList result;

	Element* temp = head;

	while (temp != 0)
	{
		result.AddToHead(temp->value);
		temp = temp->next;
	}

	return result;
}

int main()
{
	LinkedList list;

	const int n = 10;
	int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			list.AddToHead(a[i]);
		else
			list.AddToTail(a[i]);
	}

	cout << "List:\n";
	list.Print();

	cout << endl;

	list.Insert();
	cout << "List:\n";
	list.Print();

	list.Print(2);
	list.Print(8);

	LinkedList tempList;

	tempList = list;
	cout << "Temp List:\n";
	tempList.Print();

	cout << "Sum List:\n";
	LinkedList sumList = -list + tempList;
	sumList.Print();

	return 0;
}
