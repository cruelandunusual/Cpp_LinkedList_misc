#include <iostream>
using namespace std;

struct listNode {
    char letter;
    listNode* next;
};

typedef listNode* listString;

int length(listString s);
char characterAt(listString s, int pos);
void printString(listString s);
void removeChars(listString& s, int startPos, int charsToRemove);
void removeCharsTester();

int main()
{
    //removeCharsTester();
    //lengthTester();

    listString testWord;
    listNode* node1 = new listNode;
    node1->letter = 't';
    listNode* node2 = new listNode;
    node2->letter = 'e';
    listNode* node3 = new listNode;
    node3->letter = 's';
    listNode* node4 = new listNode;
    node4->letter = 't';
    listNode* node5 = new listNode;
    node5->letter = 'i';
    listNode* node6 = new listNode;
    node6->letter = 'n';
    listNode* node7 = new listNode;
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
    cout << "deleting some nodes...\n";
    
    listNode* ptr_curr = testWord;
    cout << ptr_curr->letter << "\n";
    listNode* ptr_prev = ptr_curr;
    listNode* ptr_deleteMe = ptr_curr;
    ptr_curr = ptr_curr->next;
    delete[] ptr_deleteMe;
    //ptr_deleteMe = NULL;
    cout << ptr_prev->letter << "\n";
    cout << ptr_curr->letter << "\n";
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

void printString(listString s)
{
    listNode * ptr = s;
    while (ptr != NULL)
    {
	cout << ptr->letter;
	ptr = ptr->next;
    }
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
