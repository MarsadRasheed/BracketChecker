#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class node {
public:
	char data;
	node* next;
};

class LinkedList {

	node* head;
	node* tail;

public:

	LinkedList() {
		head = NULL;
		tail = NULL;
	}

	void add(char word);
	char remove();
	void print();
	char top();

	bool empty() {
		if (!this->head) {
			return true;
		}
		return false;
	}
};

void LinkedList::add(char word) {

	node* ptr;
	ptr = head;

	node* temp = new node;
	temp->data = word;
	temp->next = NULL;

	if (head == NULL) {
		head = temp;
		tail = temp;
	}
	tail->next = temp;
	temp->next = NULL;
	tail = temp;
}

char LinkedList::remove() {

	node* previous;
	previous = head;

	node* current;
	current = head;

	char deleted;
	if (!empty()) {
		if (previous->next == NULL) {
			char deleted = previous->data;
			delete previous;
			head = NULL;
			return deleted;
		}
		else {
			while (current->next != NULL) {
				previous = current;
				current = current->next;
			}
			deleted = current->data;
			previous->next = NULL;
			tail = previous;
			delete current;
			return deleted;
		}
	}
	else
	{
		return 'd';
	}
}

void LinkedList::print() {
	node* temp;
	temp = head;

	if (temp == NULL) {
		cout << "\n list is empty\n ";
	}
	else {
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
}

char LinkedList::top() {
	if (!empty()) {
		return (tail->data);
	}
	return 't';
}

class Stack {
	LinkedList l;
public:

	bool emptyStack() {
		bool check;
		check = l.empty();
		return check;
	}

	void push(char a) {
		l.add(a);
	}

	char pop() {
		char deleted;
		deleted = l.remove();
		return deleted;
	}

	void print() {
		l.print();
	}

	char peek() {
		char word;
		word = l.top();
		return word;
	}

	bool equalPair(char opening, char closing) {

		if (opening == '(' && closing == ')') {
			return true;
		}
		else if (opening == '{' && closing == '}') {
			return true;
		}
		else if (opening == '[' && closing == ']') {
			return true;
		}
		else {
			return false;
		}
	}
	void checkBrackets(string test, int lineNo);
};


void Stack::checkBrackets(string test, int lineNo) {

	char top1, top2, top3;
	int stringLength = test.length();

	for (int i = 0; i < stringLength; i++) {
		if (test[i] == '{' || test[i] == '[' || test[i] == '('){
			push(test[i]);
		}
		else {
			switch (test[i]) {

			case ')':
				top1 = peek();
				if (equalPair(top1, test[i])) {
					pop();
				}
				else {
					if (top1 == '{' || top1 == '[' || top1 == 't') {
						cout << ") is missed at line " << lineNo << endl;
					}
				}
				break;

			case '}':
				top2 = peek();
				if (equalPair(top2, test[i])) {
					pop();
				}
				else {
					if (top2 == '(' || top2 == '[' || top2 == 't') {
						cout << "} is missed at line " << lineNo << endl;
					}
				}
				break;

			case ']':
				top3 = peek();
				if (equalPair(top3, test[i])) {
					pop();
				}
				else {
					if (top3 == '(' || top3 == '{' || top3 == 't') {
						cout << "] is missed at line " << lineNo << endl;
					}
				}
				break;
			}
		}
	}
}

int main() {

	Stack stack;

	int topOfCurly = -1;
	int topOfSquare = -1;
	int topOfSmall = -1;
	
	const int sizeOfSmall = 100;
	const int sizeOfSquare = 100;
	const int sizeOfCurly = 100;

	int smalll[sizeOfSmall];
	int curlyy[sizeOfCurly];
	int squaree[sizeOfSquare];

	string test;
	int lineNO = 0;
	ifstream fin;
	fin.open("barry.cpp");

	while (!fin.eof()) {
		
		lineNO++;
		getline(fin, test);

		int n = test.length();

		for (int i = 0; i < n; i++) {
			if (test[i] == '{') {
				curlyy[++topOfCurly] = lineNO;
			}
			else if (test[i] == '[') {
				squaree[++topOfSquare] = lineNO;
			}
			else if (test[i] == '(') {
				smalll[++topOfSmall] = lineNO;
			}
		}

		for (int i = 0; i < n; i++) {
			if (test[i] == '}') {
				curlyy[topOfCurly--];
			}
			else if (test[i] == ']') {
				squaree[topOfSquare--];
			}
			else if (test[i] == ')') {
				smalll[topOfSmall--];
			}
		}

		stack.checkBrackets(test, lineNO);
	}

	if (!stack.emptyStack()) {
		char toop = stack.peek();
		if (toop == '{') {
			cout << "{ is missing at line " << curlyy[topOfCurly];
		}
		else if (toop == '[') {
			cout << "[ is missing at line " << squaree[topOfSquare];
		}
		else if (toop == '(') {
			cout << "( is missing at line " << smalll[topOfSmall];
		}
	}

	system("pause");
}
