#include <iostream>
using namespace std;

#define DEBUG(msg) std::cout << msg << std::endl
#define PRINT(msg) std::cout << msg << std::endl
const int ASCII_OFFSET = 48;

struct listNode {
    char sign;
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
listNode* getLastNode(listNode* p_curr);

listNumber subtractList(listNumber minuend, listNumber subtrahend);
void subtractListTester();
listNumber subtractList__old(listNumber minuend, listNumber subtrahend);
listNumber __subtractList(bool flipped, listNumber minuend, listNumber subtrahend);

listNumber createNumber(char* array)
{
    listNumber newNumber;
    listNode* p_previous = new listNode;
    int count = 0;
    while (array[count] != '\0') { // increment count variable to array length
	count++;
    }
    count--; // subtract 1 because array[count] == '\0' at end of while-loop
    int listEnd = count;
    while (count > 0) {
	listNode* p_current_num = new listNode;
	p_current_num->sign = '\0';
	p_current_num->digit = array[count] - ASCII_OFFSET;
	if (listEnd == count) {
	    p_current_num->next = NULL;
	}
	else {
	    p_current_num->next = p_previous;
	}
	p_previous = p_current_num;
	count--;
    }
    listNode* p_sign = new listNode;
    p_sign->sign = array[count];
    p_sign->digit = '\0';
    p_sign->next = p_previous;
    newNumber = p_sign;
    return newNumber;
}

void createNumberTester()
{
    cout << "------\n";
    cout << "Testing createNumber(char* array)\n";
    char number[] = "-12345";
    listNumber myNumber = createNumber(number);
    printNumber(myNumber);
    cout << "\n";
}

int main()
{
    printNumberTester();
    intToListTester();
    lengthTester();
    sumListsTester();
    subtractListTester();
    createNumberTester();
}

listNode* getPreviousNode(listNumber n, listNode* p_curr)
{
    listNode* p_prev = n;
    if (length(p_prev) == 2) {
	p_prev = p_prev->next;
	return p_prev;
    }
    else {
	while (p_prev->next != p_curr) {
	    p_prev = p_prev->next;
	}
    }
    return p_prev;
}

listNode* getLastNode(listNode* p_curr)
{
    listNode* p_last = p_curr;
    while (p_last->next != NULL) {
	p_last = p_last->next;
    }
    return p_last;
}
    

listNumber sumLists(listNumber n1, listNumber n2)
{
    /*
     Two numbers are summed together, least significant digits first, digit by digit.
     The result (after modulo 10) is stored in the 'digit' member variable
     of a new node of a listNumber.
     The resulting carry after the modulo (if any) is always 1, since
     the highest value digits that can be added together are 9+9
     E.g. 19 is added to 199 by adding 9+9,
     then by adding 9+1+carry,
     then by adding 1+carry.
     We always iterate backwards through our list numbers.
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

    char num1[] = "99";
    char num2[] = "19";
    listNumber listNum1 = createNumber(num1);
    listNumber listNum2 = createNumber(num2);
    
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

listNumber subtractList(listNumber minuend, listNumber subtrahend)
{
    listNumber subtraction_result;
    int minuend_length = length(minuend);
    int subtrahend_length = length(subtrahend);
    int case_decision = 0;
    
    if (minuend_length > subtrahend_length) {
	//call subtraction function with
	//minuend and subtrahend in reverse order
	case_decision = 0;
    }
    else if (minuend_length < subtrahend_length) {
	//call subtraction function with
	//minuend and subtrahend in normal order
	case_decision = 1;
    }
    else {//both same length
	DEBUG("both same length");
	//test digit-by-digit which is greater
	listNode* p_minuend_current = minuend;
	listNode* p_subtrahend_current = subtrahend;
	//skip the first node, which is the sign
	p_minuend_current = p_minuend_current->next;
	p_subtrahend_current = p_subtrahend_current->next;
	bool b_minuend_is_larger = false;
	while (p_minuend_current != NULL) {
	    if (p_minuend_current->digit > p_subtrahend_current->digit) {
		b_minuend_is_larger = true;
		break;
	    }
	    p_minuend_current = p_minuend_current->next;
	    p_subtrahend_current = p_subtrahend_current->next;
	}
	if (b_minuend_is_larger) {
	    //call subtraction function with
	    //minuend and subtrahend in reverse order
	    case_decision = 0;
	}
	else if (!b_minuend_is_larger) {
	    //call subtrahend function with
	    //minuend and subtrahend in normal order
	    case_decision = 1;
	}
	else {//both same value
	    //create a new list number with value
	    //zero and return that
	    case_decision = 2;
	}
    }
    //do case test here:
    switch (case_decision) {
    case 0:
	DEBUG("minuend is greater than subtrahend");
	subtraction_result = __subtractList(false, minuend, subtrahend);
	break;
    case 1:
	DEBUG("minuend is less than subtrahend");
	subtraction_result = __subtractList(true, subtrahend, minuend);
	break;
    case 2:
	//this should make a new listNumber set to zero and return that
	//but I've written below just to get something to compile and test
	subtraction_result = __subtractList(true, subtrahend, minuend);
	break;
    default:
	//not sure what default is yet... (the line below isn't it though)
	subtraction_result = __subtractList(true, subtrahend, minuend);
	break;
    }
    return subtraction_result;
}

listNumber __subtractList(bool flipped, listNumber minuend, listNumber subtrahend)
{
    listNode* p_minuend_current = minuend;
    listNode* p_minuend_previous = new listNode;
    listNode* p_subtrahend_current = subtrahend;
    listNode* p_subtrahend_previous = new listNode;
    listNode* p_result;
    listNode* p_result_previous = new listNode;
    listNumber result;

    int minuend_length = length(minuend);
    int subtrahend_length = length(subtrahend);
    
    //start with the least significant digit of each number
    p_minuend_current = getLastNode(p_minuend_current);
    p_subtrahend_current = getLastNode(p_subtrahend_current);

    int subtrahend_size_counter = subtrahend_length;
    const int LAST_NODE = subtrahend_size_counter;
    bool b_has_borrowed = false;
    bool borrow_extra = false;
    int temp_minuend;//stores temp calculations to not affect real minuend
    
    //use the subtrahend's length to guide the loop
    while (subtrahend_size_counter > 1) {	
	p_minuend_previous = getPreviousNode(minuend, p_minuend_current);
	p_subtrahend_previous = getPreviousNode(subtrahend, p_subtrahend_current);
	p_result = new listNode; //new listNode will store result
	//set the sign to null since we only store a meaningful value in
	//the very first node, which we'll create and deal with later
	p_result->sign = '\0';
	temp_minuend = p_minuend_current->digit;
	if (b_has_borrowed) {
	    if (p_minuend_current->digit == 0) {
		temp_minuend = 9;
	    }
	    else {
		temp_minuend -= 1;
	    }
	}
	if (temp_minuend < p_subtrahend_current->digit) {
	    b_has_borrowed = true;
	    temp_minuend += 10;
	}
	else {
	    b_has_borrowed = false;
	}
	p_result->digit = temp_minuend - p_subtrahend_current->digit;
	if (subtrahend_size_counter == LAST_NODE) {
	    p_result->next = NULL;
	}
	else {
	    p_result->next = p_result_previous;
	}
	p_result_previous = p_result;
	p_minuend_current = p_minuend_previous;
	p_subtrahend_current = p_subtrahend_previous;
	subtrahend_size_counter--;
    }
    DEBUG("reached the end of first while-loop");

    { // deal with the most significant digit of the subtrahend
	p_result = new listNode;
	p_result->sign = '\0';
	temp_minuend = p_minuend_previous->digit;

	if (b_has_borrowed) {
	    if (temp_minuend == 0) {
		//borrow_extra = true;
		temp_minuend = 9;
	    }
	    else {
		temp_minuend -= 1;
		//borrow_extra = false;
	    }
	}
	if (temp_minuend < p_subtrahend_current->digit) {
	    b_has_borrowed = true;
	    temp_minuend += 10;
	}
	else {
	    b_has_borrowed = false;
	}

	p_result->digit = temp_minuend - p_subtrahend_current->digit;
	p_result->next = p_result_previous;
	p_result_previous = p_result;
	p_minuend_current = p_minuend_previous;
	DEBUG("dealt with most significant digit of subtrahend");
    }
    
    int remaining_minuend_digits = minuend_length - subtrahend_length;
    DEBUG("remaining_minuend_digits: " << remaining_minuend_digits);
    while (remaining_minuend_digits > 1) {
	DEBUG("inside second while-loop");
	/*
	  this will terminate at the second most significant
	  digit of the minuend
	 */

	p_minuend_previous = getPreviousNode(minuend, p_minuend_current);
	temp_minuend = p_minuend_previous->digit;

	if (b_has_borrowed) {
	    if (temp_minuend == 0) {
		temp_minuend = 9;
		b_has_borrowed = true;
	    }
	    else {
		temp_minuend -= 1;
		b_has_borrowed = false;
	    }
	}

	p_result = new listNode;
	p_result->sign = '\0';
	p_result->digit = temp_minuend;
	p_result->next = p_result_previous;
	p_result_previous = p_result;
	p_minuend_current = p_minuend_previous;
        remaining_minuend_digits--;
    }
    DEBUG("at end of second while-loop");
    /* Now deal with the most significant digit of the minuend.
     */
    
    p_minuend_previous = getPreviousNode(minuend, p_minuend_current);
    temp_minuend = p_minuend_previous->digit;
    
    if (b_has_borrowed) {
	DEBUG("b_has_borrowed = " << b_has_borrowed);
	if (temp_minuend == 1) {
	    temp_minuend = 0;
	}
	else {
	    temp_minuend -= 1;
	}
    }
    p_result = new listNode;
    p_result->sign = '\0';
    if (temp_minuend == 0) {
	DEBUG("temp_minuend = " << temp_minuend);
	p_result->digit = 0;
    }
    else {
	p_result->digit = temp_minuend;
    }
    DEBUG("p_result->digit = " << p_result->digit);
    p_result->next = p_result_previous;
    p_result_previous = p_result;
    p_minuend_current = p_minuend_previous;

    p_result = new listNode;
    if (flipped) { p_result->sign = '-'; }
    else { p_result->sign = '+'; }
    p_result->digit = '\0';
    p_result->next = p_result_previous;
  
    return p_result;
}

void subtractListTester()
{
    cout << "------\n";
    cout << "Testing subtractList(listNumber minuend, listNumber subtrahend)\n";

    char num1[] = "+10012";
    char num2[] = "+992";
    listNumber listNum1 = createNumber(num1);
    listNumber listNum2 = createNumber(num2);
    
    PRINT("listNum1 is ");
    printNumber(listNum1);
    cout << "\n";
    PRINT("listNum2 is ");
    printNumber(listNum2);
    cout << "\n";
    //PRINT("listNum1 is " << length(listNum1) << " digits long");
    PRINT("The result of subtracting listNum2 from listNum1 is:");
    listNumber listResult = subtractList(listNum1, listNum2);
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
    size--; // subtract 1 because size doesn't include sign
    return size;
}

void lengthTester()
{
    cout << "------\n";
    cout << "Testing length(listNumber n)\n";
    
    char number[] = "+12";
    listNumber myNumber = createNumber(number);
    int size = length(myNumber);
    PRINT("myNumber is ");
    printNumber(myNumber);
    cout << "\n";
    PRINT("myNumber has " << size << " nodes");
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
    cout << ptr_n->sign;
    ptr_n = ptr_n->next;
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



listNumber subtractLists__old(listNumber minuend, listNumber subtrahend)
{
    listNode* p_minuend_current = minuend;
    listNode* p_minuend_previous = new listNode;
    listNode* p_subtrahend_current = subtrahend;
    listNode* p_subtrahend_previous = new listNode;
    listNode* p_result;
    listNode* p_result_previous = new listNode;
    listNumber result;
    
    p_minuend_current = getLastNode(p_minuend_current);
    p_subtrahend_current = getLastNode(p_subtrahend_current);
    int count = length(minuend);
    const int MAX = count;

    while (count > 1) {
	p_minuend_previous = getPreviousNode(minuend, p_minuend_current);
	p_subtrahend_previous = getPreviousNode(subtrahend, p_subtrahend_current);
	p_result = new listNode;
	p_result->sign = '\0';
	p_result->digit = p_minuend_current->digit - p_subtrahend_current->digit;
	if (count == MAX) {
	    p_result->next = NULL;
	}
	else {
	    p_result->next = p_result_previous;
	}
	p_result_previous = p_result;
	p_minuend_current = p_minuend_previous;
	p_subtrahend_current = p_subtrahend_previous;
	count--;
    }
    p_result = new listNode;
    p_result->sign = '\0';
    p_result->digit = p_minuend_previous->digit - p_subtrahend_previous->digit;
    p_result->next = p_result_previous;
    p_result_previous = p_result;

    p_result = new listNode;
    p_result->sign = '+';
    p_result->digit = '\0';
    p_result->next = p_result_previous;
    
    result = p_result;
    return result;
}
