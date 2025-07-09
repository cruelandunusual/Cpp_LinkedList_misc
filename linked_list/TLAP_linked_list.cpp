#include <iostream>
using namespace std;

struct listNode {
    int studentNum;
    int grade;
    listNode * next;
};

typedef listNode * studentCollection;

void addRecord(studentCollection& sc, int studentNum, int grade);
void removeRecord(studentCollection& sc, int stuNum);
int numStudents(studentCollection sc);
double averageRecord(studentCollection sc);
void printStudents(studentCollection sc);

int main()
{
    studentCollection sc;
    listNode * node1 = new listNode;
    node1->studentNum = 1001;
    node1->grade = 78;
    listNode * node2 = new listNode;
    node2->studentNum = 1012;
    node2->grade = 93;
    listNode * node3 = new listNode;
    node3->studentNum = 1076;
    node3->grade = 85;
    sc = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    node1 = node2 = node3 = NULL;

    addRecord(sc, 1274, 91);
    addRecord(sc, 1432, 86);
    addRecord(sc, 1002, 45);
    addRecord(sc, 1956, 67);
    addRecord(sc, 1045, 77);
    cout << "number of students: " << numStudents(sc) << "\n";
    printStudents(sc);
    //double average = averageRecord(sc);
    //cout << "average grade of all students: " << average << "\n";
    removeRecord(sc, 1045);
    cout << "number of students: " << numStudents(sc) << "\n";
    printStudents(sc);
    removeRecord(sc, 1076);
    cout << "number of students: " << numStudents(sc) << "\n";
    printStudents(sc);
    removeRecord(sc, 1274);
    cout << "number of students: " << numStudents(sc) << "\n";
    printStudents(sc);

    return 0;
}


void addRecord(studentCollection& sc, int stuNum, int gr)
{
    listNode * newNode = new listNode;
    newNode->studentNum = stuNum;
    newNode->grade = gr;
    newNode->next = sc;
    sc = newNode;
}

void removeRecord(studentCollection& sc, int stuNum)
{
    listNode * currentPtr = sc;
    listNode * nextNode = sc->next;
    if (currentPtr->studentNum == stuNum) {
	sc = nextNode;
	delete currentPtr;
	nextNode = NULL;
    }
    else {
	while (nextNode != NULL)
	{
	    if (nextNode->studentNum == stuNum) {
		currentPtr->next = nextNode->next;
		delete nextNode;
		currentPtr = NULL;
		break;
	    }
	    currentPtr = currentPtr->next;
	    nextNode = nextNode->next;
	}
    }
}

int numStudents(studentCollection sc)
{
    int count = 0;
    listNode * loopPtr = sc;
    while (loopPtr != NULL)
    {
	count++;
	loopPtr = loopPtr->next;
    }
    return count;
}

double averageRecord(studentCollection sc)
{
    if (sc == NULL) return 0;
    int count = 0;
    double sum = 0;
    listNode * loopPtr = sc;
    while (loopPtr != NULL)
    {
	sum += loopPtr->grade;
	count++;
	loopPtr = loopPtr->next;
    }
    double average = sum / count;
    return average;
}


void printStudents(studentCollection sc)
{
    listNode * loopPtr = sc;
    while (loopPtr != NULL)
    {
	cout << loopPtr->studentNum << ", " << loopPtr->grade << "\n";
	loopPtr = loopPtr->next;
    }
}
