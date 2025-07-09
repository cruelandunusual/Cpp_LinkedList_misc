#include <iostream>
using namespace std;

#define DEBUG(msg) std::cout << msg << std::endl
#define PRINT(msg) std::cout << msg << std::endl

struct listNode {
    int digit;
    listNode* next;
};
typedef listNode* listNumber;

void printNumber(listNumber n);
void printNumberTester();
listNumber intToList(int number);
void intToListTester();
int length(listNumber n);
void lengthTester();
listNumber sumLists(listNumber n1, listNumber n2);
void sumListsTester();
listNode* getPreviousNode(listNumber n, listNode* p_curr);
listNumber createNumber(char* array);
void createNumberTester();

listNumber subtractLists(listNumber minuend, listNumber subtrahend);
void subtractListsTester();

listNumber createNumber(char* array)
{
    listNumber newNumber;
    listNode* p_prev = new listNode;
    int ASCII_OFFSET = 48;
    int i = 0;
    while (array[i] != '\0') {
	i++;
    }
    i--;
    int listEnd = i;
    while (i >= 0) {
	listNode* p_curr = new listNode;
	p_curr->digit = array[i] - ASCII_OFFSET;
	if (listEnd == i) {
	    p_curr->next = NULL;
	}
	else {
	    p_curr->next = p_prev;
	}
	p_prev = p_curr;
	i--;
    }
    newNumber = p_prev;
    return newNumber;
}

void createNumberTester()
{
    cout << "------\n";
    cout << "Testing createNumber(char* array)\n";
    char word[] = "12345";
    listNumber myNumber = createNumber(word);
    printNumber(myNumber);
    cout << "\n";
}

int main()
{
    //printNumberTester();
    //intToListTester();
    //lengthTester();
    //sumListsTester();
    subtractListsTester();
    //createNumberTester();
}

listNode* getPreviousNode(listNumber n, listNode* p_curr)
{
    listNode* p_prev = n;

    while (p_prev->next != p_curr) {
	p_prev = p_prev->next;
    }
    return p_prev;
}

void getLastNode(listNode* p_curr)
{
    while (p_curr != NULL) {
	p_curr = p_curr->next;
    }
}
    

listNumber sumLists(listNumber n1, listNumber n2)
{
    /*
     Two numbers are summed together in reverse order, digit by digit.
     The result (after mod 10) is stored in the 'digit' member variable
     of a new node of a listNumber.
     The carry bit (if required) is always 1, since the highest value
     digits that can be added together are 9+9
     E.g. 19 is added to 199 by adding 9+9,
     then by adding 9+1+carry,
     then by adding 1+carry.
     So we always iterate backwards through our list numbers.
     Each node is pointed forward to its neighbour.
     */
    listNode* p1_curr = n1;
    listNode* p1_prev = n1;
    listNode* p2_curr = n2;
    listNode* p2_prev = n2;
    listNode* newNumberPrev = new listNode; // for iterating list backwards
    listNode* p_remainder = new listNode;
    listNode* p_prev = new listNode;

    int n1_length = 0;
    while (p1_curr->next != NULL) {
	p1_curr = p1_curr->next;
	n1_length++;
    }
    n1_length++;
    
    int n2_length = 0;
    while (p2_curr->next != NULL) {
	p2_curr = p2_curr->next;
	n2_length++;
    }
    n2_length++;

    int longestAddend = (n1_length > n2_length) ? n1_length : n2_length;
    int shortestAddend = (n1_length < n2_length) ? n1_length : n2_length;
    int carry = 0;

    if (shortestAddend == 1) {
	int sum = p1_curr->digit + p2_curr->digit;
	listNode* newNumber = new listNode;
	newNumber->digit = sum % 10 + carry;
	carry = (sum >= 10) ? 1 : 0;
	newNumberPrev = newNumber;
    }
    else {
	
	for (int i = shortestAddend; i>1; i--) {
	    //increment p1_prev to node *before* p1_curr
	    p1_prev = getPreviousNode(n1, p1_curr);
	    //increment p2_prev to node *before* p2_curr
	    p2_prev = getPreviousNode(n2, p2_curr);
	    
	    int sum = p1_curr->digit + p2_curr->digit;
	    listNode* newNumber = new listNode;
	    newNumber->digit = sum % 10 + carry;
	    carry = (sum >= 10) ? 1 : 0;
	    if (i == shortestAddend) {//last node special case
		newNumber->next = NULL;
	    }
	    else {
		newNumber->next = newNumberPrev;
	    }//end last node special case
	    newNumberPrev = newNumber;
	    
	    if (i == 1+1){
		/*
		  We switch to using p1_prev and p2_prev
		  when p1_curr or p2_curr reaches the
		  second node of shortestAddend because
		  p_prev references the first node of the
		  list at this point
		*/
		int sum = p1_prev->digit + p2_prev->digit;
		listNode* newNumber = new listNode;
		newNumber->digit = (sum % 10) + carry;
		carry = (sum >= 10) ? 1 : 0;
		newNumber->next = newNumberPrev;
		newNumberPrev = newNumber;

	    }//end first node special case
	    
	    p1_curr = p1_prev;
	    p1_prev = n1;
	    p2_curr = p2_prev;
	    p2_prev = n2;
	}//end for-loop
    }//end else
    
    if (n1_length > n2_length) {
	p_remainder = p1_curr;
	p_prev = n1;
    }
    else {
	p_remainder = p2_curr;
	p_prev = n2;
    }
    
    /*
      Add the remaining digits from the longest
      addend together with any carry from previous
      additions.
    */
    if (longestAddend-shortestAddend == 1) {
	int sum = p_prev->digit + carry;
	listNode* newNumber = new listNode;
	newNumber->digit = sum % 10;
	carry = (sum >= 10) ? 1 : 0;
	newNumber->next = newNumberPrev;
	newNumberPrev = newNumber;
    }
    
    else {
	for (int i = longestAddend-shortestAddend; i > 1; i--) {
	    while (p_prev->next != p_remainder) {
		p_prev = p_prev->next;
	    }
	    
	    int sum = p_remainder->digit + carry;
	    listNode* newNumber = new listNode;
	    newNumber->digit = sum % 10;
	    carry = (sum >= 10) ? 1 : 0;
	    newNumber->next = newNumberPrev;
	    newNumberPrev = newNumber;
	    
	    if (i == 1+1) {
		/*
		  We switch to using p_prev
		  when p_remainder reaches the
		  second node of longestAddend because
		  p_prev references the first node of the
		  list at this point
		*/
		int sum = p_prev->digit + carry;
		listNode* newNumber = new listNode;
		newNumber->digit = sum % 10;
		carry = (sum >= 10) ? 1 : 0;
		newNumber->next = newNumberPrev;
		newNumberPrev = newNumber;
		break;
	    }//end first node special case
	    
	    p_remainder = p_prev;
	    if (n1_length > n2_length) {
		p_prev = n1;
	    }
	    else {
		p_prev = n2;
	    }
	}// end for-loop
    }// end else
    if (carry == 1) {
	listNode* newNumber = new listNode;
	newNumber->digit = carry;
	newNumber->next = newNumberPrev;
	newNumberPrev = newNumber;
    }
    return newNumberPrev;
}

void sumListsTester()
{
    cout << "------\n";
    cout << "Testing sumLists(listNumber n1, listNumber n2)\n";

    listNumber listNum1 = createNumber("99");
    listNumber listNum2 = createNumber("19");
    
    PRINT("listNum1 is ");
    printNumber(listNum1);
    cout << "\n";
    PRINT("listNum2 is ");
    printNumber(listNum2);
    cout << "\n";
    PRINT("The sum of listNum1 and listNum2 is:");
    listNumber listSum = sumLists(listNum2, listNum1);
    printNumber(listSum);
    cout << "\n";
}

listNumber subtractLists(listNumber minuend, listNumber subtrahend)
{
    listNode* p_minuend_curr = minuend;
    listNode* p_minuend_prev = p_minuend_curr;
    listNode* p_subtrahend_curr = subtrahend;
    listNode* p_subtrahend_prev = p_subtrahend_curr;
    listNumber result;

    getLastNode(p_minuend_curr);
    p_minuend_prev = getPreviousNode(minuend, p_minuend_curr);
    
}

void subtractListsTester()
{
    cout << "------\n";
    cout << "Testing subtractLists(listNumber minuend, listNumber subtrahend)\n";

    listNumber listNum1 = createNumber("99");
    listNumber listNum2 = createNumber("19");
    
    PRINT("listNum1 is ");
    printNumber(listNum1);
    cout << "\n";
    PRINT("listNum2 is ");
    printNumber(listNum2);
    cout << "\n";
    PRINT("The result of subtracting listNum2 from listNum1 is:");
    listNumber listResult = subtractLists(listNum1, listNum2);
    printNumber(listResult);
    cout << "\n";
    
}

int length(listNumber n)
{
    int size = 0;
    listNode* ptr_n = n;
    while (ptr_n != NULL) {
	ptr_n = ptr_n->next;
	size++;
    }
    return size;
}

void lengthTester()
{
    listNumber listNum;
    listNode* node1 = new listNode;
    node1->digit = 1;
    listNode* node2 = new listNode;
    node2->digit = 2;
    listNode* node3 = new listNode;
    node3->digit = 3;
    listNum = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    node1 = node2 = node3 = NULL;
    int size = length(listNum);
    cout << "listNum has " << size << " nodes\n";
}

listNumber intToList(int number)
{
    listNumber num;
    listNode* ptr_prev = new listNode;
    int counter = 0;
    while (number > 0) {
	listNode* ptr_curr = new listNode;
	ptr_curr->digit = number % 10;
	if (counter == 0) {
	    ptr_curr->next = NULL;
	    ptr_prev = ptr_curr;
	}
	else {
	    ptr_curr->next = ptr_prev;
	    ptr_prev = ptr_curr;
	}
	number = number / 10;
	counter++;
    }
    num = ptr_prev;
    return num;
}

void intToListTester()
{
    listNumber number = intToList(123);
    printNumber(number);
    cout << "\n";
}

void printNumber(listNumber num)
{
    listNode* ptr_n = num;
    while (ptr_n != NULL) {
	cout << ptr_n->digit;
	ptr_n = ptr_n->next;
    }
}

void printNumberTester()
{
    listNumber myNumber;
    listNode* node1 = new listNode;
    node1->digit = 1;
    listNode* node2 = new listNode;
    node2->digit = 2;
    listNode* node3 = new listNode;
    node3->digit = 3;
    myNumber = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    node1 = node2 = node3 = NULL;
    printNumber(myNumber);
    cout << "\n";
}
