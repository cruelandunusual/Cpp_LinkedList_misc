#include <iostream>
using namespace std;

struct listNode {
    char letter;
    listNode * next;
};

typedef listNode * listString;

int length(listString s);
void lengthTester();
void printString(listString s);
void append(listString& s, char c);
void appendTester();
char characterAt(listString s, int pos);
void characterAtTester();
void concatenate(listString& s1, listString s2);
void concatenateTester();
void removeChars(listString& s, int startPos, int charsToRemove);
void removeCharsTester();
listString substring(listString s, int start, int len);
void substringTester();
listString createString(char* array);
void createStringTester();

int main()
{
    //appendTester();
    //characterAtTester();
    //concatenateTester();
    //removeCharsTester();
    //lengthTester();
    createStringTester();
    return 0;
}

int length(listString s)
{
    listNode* ptr_s = s;
    int counter = 0;
    while (ptr_s->next != NULL)
    {
	ptr_s = ptr_s->next;
	counter++;
    }
    return counter+1;
}

void lengthTester()
{
    cout << "------\n";
    cout << "Testing length(listString s)\n";

    listString testWord;
    listNode * node1 = new listNode;
    node1->letter = 't';
    listNode * node2 = new listNode;
    node2->letter = 'e';
    listNode * node3 = new listNode;
    node3->letter = 's';
    listNode * node4 = new listNode;
    node4->letter = 't';
    testWord = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;
    node1 = node2 = node3 = node4 = NULL;
    cout << "testWord is ";
    printString(testWord);
    cout << "\n";
    
    cout << "The length(testWord) of testWord is: " << length(testWord) << "\n";
    cout << "Appending a letter to testWord...\n";
    append(testWord, 's');
    cout << "testWord is now ";
    printString(testWord);
    cout << "\n";
    cout << "The length(testWord) of testWord is: " << length(testWord) << "\n";
    
}

void printString(listString s)
{
    listNode * ptr = s;
    while (ptr != NULL)
    {
	cout << ptr->letter;
	ptr = ptr->next;
    }
}

void append(listString& s, char c)
/*
  Appends char c to listString s.
 */
{
    listNode * ptr = s;
    do {
    	ptr = ptr->next;
    }	
    while (ptr->next != NULL);
    /*ptr->next is equal to NULL when loop terminates;
      ptr->next must be NULL for the condition to be
      tested (and NOT satisfied), thus ptr->next is NULL
      and we can set ptr->next to the newLetter node.
     */
    listNode * newLetter = new listNode;
    newLetter->letter = c;
    newLetter->next = NULL;
    ptr->next = newLetter;
    newLetter = NULL;
    ptr = NULL;        
}

void appendTester()
{
    cout << "------\n";
    cout << "Testing append(listString& s, char c)\n";

    listString listWord;
    listNode * node1 = new listNode;
    node1->letter = 't';
    listNode * node2 = new listNode;
    node2->letter = 'e';
    listNode * node3 = new listNode;
    node3->letter = 's';
    listNode * node4 = new listNode;
    node4->letter = 't';
    listWord = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;
    node1 = node2 = node3 = node4 = NULL;
    cout << "listWord is ";
    printString(listWord);
    cout << "\n";
 
    append(listWord, '!');
    append(listWord, '?');
    cout << "After two calls to append(listString& s, char c), listWord is:\n";
    printString(listWord);
    cout << "\n";
    
}

char characterAt(listString s, int pos)
/*
  Returns the character at pos,
  otherwise returns zero if pos is less
  than zero or not found within the bounds
  of the string.
 */
{
    if (pos < 0)
    {
	return '0';
    }
    listNode * ptr = s;
    int charAtPos = 0;
    while (ptr != NULL)
    {
	if (charAtPos == pos) {
	    return ptr->letter;
	}
	ptr = ptr->next;
	charAtPos++;
    }
    return '0';
}

void characterAtTester()
{
    cout << "------\n";
    cout << "Testing characterAt(listString s, int pos)\n";

    listString listWord;
    listNode * node1 = new listNode;
    node1->letter = 't';
    listNode * node2 = new listNode;
    node2->letter = 'e';
    listNode * node3 = new listNode;
    node3->letter = 's';
    listNode * node4 = new listNode;
    node4->letter = 't';
    listWord = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;
    node1 = node2 = node3 = node4 = NULL;
    cout << "listWord is ";
    printString(listWord);
    cout << "\n"; 
    int positionForTesting = 3;
    char c = characterAt(listWord, positionForTesting);
    cout << "character at position " << positionForTesting << " is:\n" << c << "\n";
}

void concatenate(listString& s1, listString s2)
{
    // get to the last node of the string s1
    listNode * ptr_s1 = s1;
    while (ptr_s1->next != NULL) {
	ptr_s1 = ptr_s1->next;
    }
    // ptr_s1 is the last node when loop terminates

    // initialise all the stack pointers needed
    listNode * ptr_s2 = s2;
    listNode * ptr_newS2 = new listNode;
    listNode * ptr_temp = new listNode;
    listString newWord;

    /*
      copy the first node of string s2
      to ptr_newS2; set ptr_temp to point to
      ptr_newS2. This is so that when we
      iterate through the rest of s2, ptr_temp
      is always one step behind
    */
    ptr_newS2->letter = ptr_s2->letter;
    ptr_newS2->next = ptr_s2->next;
    ptr_temp = ptr_newS2;
    newWord = ptr_temp;
    ptr_newS2 = NULL;
    ptr_temp = NULL;
    ptr_s2 = ptr_s2->next;

    /*
      iterate through source list
     */
    while (ptr_s2->next != NULL) {
	listNode * ptr_newS2 = new listNode;
	ptr_newS2->letter = ptr_s2->letter;
	ptr_newS2->next = ptr_s2->next;
	listNode * ptr_temp = new listNode;
	ptr_temp->next = ptr_newS2;
	ptr_temp = ptr_temp->next;
	ptr_newS2 = NULL;
	ptr_temp = NULL;
	ptr_s2 = ptr_s2->next;
    }

    ptr_s1->next = newWord;
    newWord = NULL;
    ptr_s2 = NULL;
    ptr_newS2 = NULL;
    ptr_temp = NULL;
}

void concatenateTester()
{
    cout << "------\n";
    cout << "Testing concatenate(listString& s1, listString s2)\n";

    // create first word
    listString firstWord;
    listNode * node1 = new listNode;
    node1->letter = 't';
    listNode * node2 = new listNode;
    node2->letter = 'e';
    listNode * node3 = new listNode;
    node3->letter = 's';
    listNode * node4 = new listNode;
    node4->letter = 't';
    firstWord = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;
    node1 = node2 = node3 = node4 = NULL;
    cout << "firstWord is ";
    printString(firstWord);
    cout << "\n";
    
    // create second word 
    listString secondWord;
    listNode * n1 = new listNode;
    n1->letter = 'i';
    listNode * n2 = new listNode;
    n2->letter = 'n';
    listNode * n3 = new listNode;
    n3->letter = 'g';
    secondWord = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    n1 = n2 = n3 = NULL;
    cout << "secondWord is ";
    printString(secondWord);
    cout << "\n";
    cout << "Calling concatenate(listString& s1, listString s2) with firstWord and secondWord\n";
    concatenate(firstWord, secondWord);
    cout << "firstWord is:\n";
    printString(firstWord);
    cout << "\n";
    cout << "secondWord is:\n";
    printString(secondWord);
    cout << "\n";    
}

void removeChars(listString& s, int startPos, int numChars)
{
    if (characterAt(s, (startPos+numChars)-1) == '0') {
	cerr << "error: number out of range\n";
    }
    else if (startPos == 0 && numChars == length(s)) {
	cerr << "error: can't remove all chars from string\n";
    }
    else {
	// initialise stack pointers
	listNode* ptr_curr = s;
	listNode* ptr_prev = ptr_curr;
	if (startPos == 0) {
	    /* deleting from start of list is special case:
	       we don't delete the first node, we overwrite
	       its contents with the first node we want to keep.
	       So if we want to delete nodes 1 and 2 from string s
	       we overwrite node 1 with node 3 and delete 2 and 3.
	     */
	    for (int i=0; i<numChars; i++) {
		if (i > 0) {
		    /* only delete current node if it's not the first
		     */
		    listNode* ptr_deleteMe = ptr_curr;
		    ptr_curr = ptr_curr->next;
		    delete[] ptr_deleteMe;
		}
		else {
		    // skip the first node without deleting
		    ptr_curr = ptr_curr->next;
		}
	    }
	    // copy first node we're keeping into first node
	    ptr_prev->letter = ptr_curr->letter;
	    ptr_prev->next = ptr_curr->next;
	    /* then delete node we've just copied -
	       it's been replaced by first node
	    */
	    delete[] ptr_curr;
	}
	else {
	    /*
	      if we're not removing the first node then
	      we increment ptr_curr to next node so that
	      ptr_prev is a step behind. We can then remove
	      the unwanted nodes and point ptr_prev to
	      new ptr_curr
	     */
	    int counter = 1;
	    ptr_curr = ptr_curr->next;
	    while (ptr_curr != NULL) {
		if (counter == startPos) {
		    // if we're at the first node to remove
		    for (int i=0; i<numChars; i++) {
			// create temp node to delete ptr_curr
			// immediately after we've incremented ptr_curr
			listNode* ptr_deleteMe = ptr_curr;
			ptr_curr = ptr_curr->next;
			delete[] ptr_deleteMe;
		    }
		    ptr_prev->next = ptr_curr;
		    break;
		}
		ptr_curr = ptr_curr->next;
		ptr_prev = ptr_prev->next; 
		counter++;
	    }
	}
    }
}


void removeCharsTester()
{
    cout << "------\n";
    cout << "Testing removeChars(listString& s, int startPos, int numChars)\n";

    // create testWord
    listString testWord;
    listNode * node1 = new listNode;
    node1->letter = 't';
    listNode * node2 = new listNode;
    node2->letter = 'e';
    listNode * node3 = new listNode;
    node3->letter = 's';
    listNode * node4 = new listNode;
    node4->letter = 't';
    listNode * node5 = new listNode;
    node5->letter = 'i';
    listNode * node6 = new listNode;
    node6->letter = 'n';
    listNode * node7 = new listNode;
    node7->letter = 'g';
    testWord = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = NULL;
    node1 = node2 = node3 = node4 = node5 = node6 = node7 = NULL;
    cout << "testWord is ";
    printString(testWord);
    cout << "\n";

    int startPos = 1;
    int numChars = 6;
    removeChars(testWord, startPos, numChars);

    cout << "After removeChars(testWord, " << startPos << ", " << numChars << ") testWord is:\n";
    printString(testWord);
    cout << "\n";
}

listString substring(listString s, int start, int len)
{
    
}

void substringTester()
{
    
}

listString createString(char* array)
{
    listString myString;
    listNode* p_prev = new listNode;
    int i = 0;
    while (array[i] != '\0') {
	i++;
    }
    i--;			// take back one kadam, etc
    int end = i;
    while (i >= 0) {
	listNode* p_string = new listNode;
	p_string->letter = array[i];
	if (i == end) {
	    p_string->next = NULL;
	}
	else {
	    p_string->next = p_prev;
	}
	p_prev = p_string;
	i--;
    }
    myString = p_prev;
    return myString;
}

void createStringTester()
{
    char myString[] = "testword";
    listString myListString = createString(myString);
    printString(myListString);
    cout << "\n";
}
