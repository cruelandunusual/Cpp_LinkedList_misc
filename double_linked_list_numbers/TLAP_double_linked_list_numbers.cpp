#include <iostream>
using namespace std;

#define PRINT(msg) std::cout << msg << std::endl;
#define DEBUG(msg) std::cout << msg << std::endl;

struct listNode {
	int digit;
	listNode* next_node;
	listNode* previous_node;
};

typedef listNode* listNumber;

void printNumber(listNumber n);
void printNumberTester();
int listLength(listNumber n);
void listLengthTester();
int listLengthReverse(listNumber n);
void listLengthReverseTester();
listNumber createNumber(char* array);
void createNumberTester();

int main()
{
	createNumberTester();
	listLengthTester();
	listLengthReverseTester();
}

listNumber createNumber(char* array)
{
	int ASCII_OFFSET = 48;
	listNode* p_num = new listNode;
	listNode* p_prev = new listNode;
	listNode* p_next = new listNode;
	listNumber newNumber;

	int i = 0;
	int listStart = i;
	while (array[i] != '\0') {
		p_num = new listNode;
		p_num->digit = array[i] - ASCII_OFFSET;
		if (i == listStart) {
			p_num->previous_node = NULL;
		}
		else {
			p_num->previous_node = p_prev;
		}
		p_prev = p_num;
		i++;
	}
	i--; // take back one kadam because at end of loop array[i] is '\0'

	while (i >= 0) {
		if (array[i + 1] == '\0') {
			p_num->next_node = NULL;
		}
		else {
			p_num->next_node = p_next;
		}
		p_next = p_num;
		p_num = p_num->previous_node;
		i--;
	}
	newNumber = p_next;
	return newNumber;
}

void createNumberTester()
{
	PRINT("------");
	PRINT("Testing createNumber(char* array)");
	char number[] = "123456789101112131415";
	int i = 0;
	PRINT("Created char array:");
	while (number[i] != '\0') { // '\0' is EOF
		cout << number[i] << " ";
		i++;
	}
	cout << "\n";
	PRINT("Passing array to createNumber, storing in listNumber myNumber");
	listNumber myNumber = createNumber(number);
	PRINT("Printing myNumber");
	printNumber(myNumber);
	cout << "\n";
}

int listLength(listNumber n)
{
	listNode* p_num = n;
	int length = 0;
	while (p_num != NULL) {
		length++;
		p_num = p_num->next_node;
	}
	return length;
}

int listLengthReverse(listNumber n)
{
	listNode* p_num = n;
	int length = 0;
	while (p_num->next_node != NULL) {
		p_num = p_num->next_node;
	}
	while (p_num != NULL) {
		p_num = p_num->previous_node;
		length++;
	}
	return length;
}

void listLengthTester()
{
	PRINT("------");
	PRINT("Testing listLength(listNumber n)");
	char number[] = "123456789101112131415";
	int count = 0;
	while (number[count] != '\0') {
		count++;
	}
	listNumber myNumber = createNumber(number);
	PRINT("myNumber is");
	printNumber(myNumber);
	cout << "\n";
	PRINT("Length of myNumber (array loop method): " << count);
	int length = listLength(myNumber);
	PRINT("Length of myNumber (listLength method): " << length);
}

void listLengthReverseTester()
{
	PRINT("------");
	PRINT("Testing listLengthReverse(listNumber n)");
	char number[] = "123456789101112131415";
	int count = 0;
	while (number[count] != '\0') {
		count++;
	}
	listNumber myNumber = createNumber(number);
	PRINT("myNumber is");
	printNumber(myNumber);
	cout << "\n";
	PRINT("Length of myNumber (array loop method): " << count);
	int length = listLengthReverse(myNumber);
	PRINT("Length of myNumber (listLength method): " << length);
}

void printNumber(listNumber n)
{
	listNode* p_node = n;
	while (p_node != NULL) {
		cout << p_node->digit;
		p_node = p_node->next_node;
	}
}
