#ifndef TEXTEDITOR_H_INCLUDED
#define TEXTEDITOR_H_INCLUDED

#include <iostream>

using namespace std;

//kei
typedef char infotype;
typedef struct elmlist *address;


struct elmlist {
    infotype info;
    address next;
    address prev;
};

struct Check {
    address node;
    string type;
};


struct LinkedList {
    address first;
    address last;
    address cursor;
};

//azza
typedef struct LinkedList List;

const int MAX = 100;

struct Stack {
    Check info[MAX];
    int top;
};

struct textEditor { // menggabungkan linked list dan stack
    List dll;
    Stack undo;
    Stack redo;
};



void createList(List &L);
address createElement(infotype x);
void insertFirst(List &L, infotype x);
void insertLast(List &L, infotype x);
void deleteLast(List &L, address &x);
void deleteFirst(List &L, address &x);
void deleteAfter(List &L,address prec, address &p);
void cetakList(List &L);

//feli
void createStack(Stack &S);
void push(Stack &S, Check x);
void pop(Stack &S, Check &x);
bool isEmpty(Stack S);
bool isFull(Stack S);

void undoOperation(List &L, Stack &undoStack, Stack &redoStack);
void redoOperation(List &L, Stack &undoStack, Stack &redoStack);

void insertAtCursor(List &L, address &cursor, infotype x);
void deleteAtCursor(List &L, address &cursor, address &x);
void moveCursorLeft(List &L, address &cursor);
void moveCursorRight(List &L, address &cursor);



#endif // TEXTEDITOR_H_INCLUDED
