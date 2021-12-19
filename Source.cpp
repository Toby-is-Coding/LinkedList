#include <iostream>
#include "LinkedList.h"

using namespace std;

int buildLL(Node** head1, Node** head2);
void printLL(Node* it);
void floodLL(Node* it, int data, unsigned end);
void deleteLL(Node* head);
int question2(Node** head, int* min_, int* max_);

int buildLL(Node** head1, Node** head2)
{
    *head1 = NULL;
    *head2 = NULL;

    Node* it1 = NULL, * it2 = NULL, * tmp = NULL;
    int data = -1, i = -1; bool quit = false;

    do {
        i++; //counter
        bool valid = false;
        while (!valid) { //getting input
            valid = true;
            cout << "Enter new node data (positive) below, end by entering -1" << endl;
            cin >> data;
            if (data < -1) {
                valid = false;
                cout << "Invalid! < -1" << endl;
            }
        }
        //checking if quit
        if (data == -1) {
            quit = true;
        }
        else {
            //building linked lists
            if (data % 2 == 0) { //EVEN
                if (*head1 == NULL) {//if first object
                    it1 = new Node;
                    *head1 = it1;
                    it1->data = data; //saving data to tmp node
                    it1->ptr = NULL;//setting pointer to NULL
                }
                else {
                    tmp = new Node; //creating next node
                    tmp->data = data; //saving data to tmp node
                    it1->ptr = tmp; //setting iterator's node's ptr to point to next node
                    tmp->ptr = NULL;//setting next node's pointer to NULL
                    it1 = tmp;//set iterator node to next node
                }
            }
            else { //ODD
                if (*head2 == NULL) {//if first object
                    it2 = new Node;
                    *head2 = it2;
                    it2->data = data; //saving data to tmp node
                    it2->ptr = NULL;//setting pointer to NULL
                }
                else {
                    tmp = new Node; //creating next node
                    tmp->data = data; //saving data to tmp node
                    it2->ptr = tmp; //setting iterator's node's ptr to point to next node
                    tmp->ptr = NULL;//setting next node's pointer to NULL
                    it2 = tmp;//set iterator node to next node
                }
            }
        }
    } while (!quit);

    return i;
}

void printLL(Node* it)
{
    while (it != NULL) {
        cout << it->data;
        if (it->ptr != NULL) cout << ", ";
        it = it->ptr;
    }
    cout << endl;
}

void floodLL(Node* it, int data, unsigned end = 0)
{
    bool stop = end != 0;
    int i = stop ? 1 : 0;
    while (it != NULL && i <= end) {
        it->data = data;
        it = it->ptr;
        if (stop) ++i;
    }
}

int main()
{
    /*Node* headEve = NULL, * headOdd = NULL;
    int totalNodes = buildLL(&headEve, &headOdd);

    printLL(headEve);
    printLL(headOdd);
    cout << totalNodes << endl;

    int minEve = NULL, maxEve = NULL;
    cout << "sum of even linked list: " << question2(&headEve, &minEve, &maxEve) << endl;
    cout << "min: " << minEve << endl;
    cout << "max: " << maxEve << endl;

    deleteLL(headEve);
    deleteLL(headOdd);*/

    LL ll, ll2(4);
    ll.insert(ll2);
    ll.print();
    //error with destructor
}

void deleteLL(Node* head) {
    Node* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->ptr;
        delete tmp;
    }
}

int question2(Node** head, int* min_, int* max_)
{
    Node* it = *head;
    bool it_null = it == NULL;
    int min = it_null ? 0 : it->data;
    int max = it_null ? 0 : it->data;
    int sum = 0;
    while (!it_null) {
        if (it->data < min) min = it->data;
        if (it->data > max) max = it->data;
        sum += it->data;
        it = it->ptr;
    }
    *min_ = min;
    *max_ = max;
    return sum;
}
