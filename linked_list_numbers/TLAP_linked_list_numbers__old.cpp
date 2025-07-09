#include <iostream>
using namespace std;

#define print(msg) std::cout << msg << std::endl

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
void getPreviousNode(listNode* p1_prev, listNode* p1_curr);

void getPreviousNode(listNode* p1_prev, listNode* p1_curr){
    listNode* p_prev = p1_prev;
    listNode* p_curr = p1_curr;
    while (p_prev->next != p_curr) {
	p_prev = p_prev->next;
    }
}


int main()
{
    //printNumberTester();
    //intToListTester();
    //lengthTester();
    sumListsTester();
}

listNumber sumLists(listNumber n1, listNumber n2)
{
    listNode* p1_curr = n1;
    listNode* p1_prev = n1;
    listNode* p2_curr = n2;
    listNode* p2_prev = n2;
    listNode* newNumberPrev = new listNode; // for iterating list backwards

    int n1_length = 0;
    while (p1_curr->next != NULL) {
	p1_curr = p1_curr->next;
	n1_length++;
    }
    n1_length++; // increment n1_length once more because while-loop used
    // p1_curr->next as test condition, which stops one node *before* end,
    // so n1_length is one less than true length at end of while-loop
    int n2_length = 0;
    while (p2_curr->next != NULL) {
	p2_curr = p2_curr->next;
	n2_length++;
    }
    n2_length++; // same for n2_length
    
    int longestAddend = (n1_length > n2_length) ? n1_length : n2_length;
    int shortestAddend = (n1_length < n2_length) ? n1_length : n2_length;
    bool nextIsNULL = true;
    int carry = 0;
    bool isMoreToSum = true;

    while (isMoreToSum) {

    for (int i = shortestAddend; i>1; i--) {
	//increment p1_prev to node *before* p1_curr
	while (p1_prev->next != p1_curr) {
	    p1_prev = p1_prev->next;
	}
	//increment p2_prev to node *before* p2_curr
	while (p2_prev->next != p2_curr) {
	    p2_prev = p2_prev->next;
	}

	int sum = p1_curr->digit + p2_curr->digit;
	listNode* newNumber = new listNode;
	newNumber->digit = sum % 10 + carry;
	if (nextIsNULL) {
	    newNumber->next = NULL;
	    nextIsNULL = false;
	}
	else {
	    newNumber->next = newNumberPrev;
	}
	newNumberPrev = newNumber;
	carry = (sum >= 10) ? 1 : 0;

	if (i == 1+1){
	    /*
	      p1_prev or p2_prev are pointing
	      to the first node of the shortest addends
	      so add them together
	     */
	    int sum = p1_prev->digit + p2_prev->digit;
	    listNode* newNumber = new listNode;
	    newNumber->digit = (sum % 10) + carry;
	    newNumber->next = newNumberPrev;
	    newNumberPrev = newNumber;
	    carry = (sum >= 10) ? 1 : 0;
	    if (carry) {
		listNode* newNumber = new listNode;
		newNumber->digit = carry;
		newNumber->next = newNumberPrev;
		newNumberPrev = newNumber;
	    }
	}

	p1_curr = p1_prev;
	p1_prev = n1;
	p2_curr = p2_prev;
	p2_prev = n2;
    }//end for-loop
    }//end while-loop
    return newNumberPrev;
}

void sumListsTester()
{
    cout << "------\n";
    cout << "Testing sumLists(listNumber n1, listNumber n2)\n";
    
    listNumber listNum1;
    listNode* node1_1 = new listNode;
    node1_1->digit = 9;
    listNode* node2_1 = new listNode;
    node2_1->digit = 9;
    listNode* node3_1 = new listNode;
    node3_1->digit = 9;
    listNode* node4_1 = new listNode;
    node4_1->digit = 9;
    listNum1 = node1_1;
    node1_1->next = node2_1;
    node2_1->next = node3_1;
    node3_1->next = node4_1;
    node4_1->next = NULL;
    node1_1 = node2_1 = node3_1 = node4_1 = NULL;

    listNumber listNum2;
    listNode* node1_2 = new listNode;
    node1_2->digit = 9;
    // listNode* node2_2 = new listNode;
    // node2_2->digit = 9;
    // listNode* node3_2 = new listNode;
    // node3_2->digit = 9;
    // listNode* node4_2 = new listNode;
    // node4_2->digit = 9;
    listNum2 = node1_2;
    node1_2->next = NULL;
    // node2_2->next = node3_2;
    // node3_2->next = node4_2;
    // node4_2->next = NULL;
    // node1_2 = node2_2 = node3_2 = node4_2 = NULL;
    node1_2 = NULL;
    

    //int size = length(listNum);
    //cout << "listNum has " << size << " nodes\n";
    print("listNum1 is ");
    printNumber(listNum1);
    cout << "\n";
    print("listNum2 is ");
    printNumber(listNum2);
    cout << "\n";
    print("The sum of listNum1 and listNum2 is:");
    listNumber listSum = sumLists(listNum1, listNum2);
    printNumber(listSum);
    print("");
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
