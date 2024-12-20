#include "texteditor.h"

//feli
void createList(List &L) {
    L.first = NULL;
    L.last = NULL;
    L.cursor = NULL;
}

address createElement(infotype x) {
    address newNode = new elmlist;
    newNode->info = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertFirst(List &L, infotype x) {
    address newNode = createElement(x);
    if (L.first == NULL) {
        L.first = newNode;
        L.last = newNode;
        L.cursor = newNode;
    } else {
        newNode->next = L.first;
        L.first -> prev = newNode;
        L.first = newNode;
        L.cursor = newNode->next;
    }
}

void insertLast(List &L, infotype x) {
    address newNode = createElement(x);
    if (L.first == NULL) {
        L.first = newNode;
        L.last = newNode;
        L.cursor = newNode;
    } else {
        L.last->next = newNode;
        newNode->prev = L.last;
        L.last = newNode;
        L.cursor = newNode;
    }
}

void deleteFirst(List &L, address &x) {
    if (L.first != NULL) {
        x =  L.first;
        if (L.first == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else {
            L.first = L.first-> next;
            L.first-> prev = NULL;
        }
    }
}

//kei
void deleteLast(List &L, address &x) {
    if (L.last != NULL) {
            x = L.last;
        if (L.first == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else {
            L.last = L.last->prev;
            L.last->next = NULL;
        }
    }
}

void deleteAfter(List &L,address prec,  address &p){
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next; //p jadi setelah prec
        if (L.cursor == p) {
            L.cursor = L.cursor->prev->prev; //kalo cursor ada di kursor berarti kursor jadi ke sebelum sebelumnya
        }
        prec->next = p->next; //p jadi hilang

        if (p->next != nullptr) {
            p->next->prev = prec; //buat ngilangin p
        }
        p->prev = nullptr; //mutus list p
        p->next = nullptr;
    }
}

void cetakList(List &L) {
    address temp = L.first;
    while (temp != NULL) {
        cout << temp->info << " ";
        temp = temp->next;
    }
    cout << endl;
}

void createStack(Stack &S) {
    S.top = 0;
}

//azza
void push(Stack &S, Check x) {
    if (S.top != MAX) {
        S.info[S.top] = x;
        S.top++;
    } else {
        cout << "Penuh!";
    }
}

void pop(Stack &S, Check &x) {
    if (S.top > 0) {
        S.top--;
        x = S.info[S.top];
    } else {
        cout << "Kosong!";
    }
}

bool isEmpty(Stack S) {
    return S.top == 0;
}

bool isFull(Stack S) {
    return S.top == MAX;
}

//feli
void undoOperation(List &L, Stack &undoStack, Stack &redoStack) {
    // Mengecek apakah stack undo tidak kosong
    if (!isEmpty(undoStack)) {
        Check cek; // Objek untuk menyimpan data yang dikeluarkan dari stack
        pop(undoStack, cek); // Mengeluarkan data terakhir dari stack undo
        push(redoStack, cek); // Menyimpan data tersebut ke stack redo

        // Mengecek tipe operasi yang dilakukan
        if (cek.type == "insert") {
            address deletedNode = cek.node; // Menyimpan node yang diinsert
            // Menghapus node yang diinsert tadi
            deleteAtCursor(L, L.cursor->prev, deletedNode);
        } else if (cek.type == "delete") {
            // Jika operasi sebelumnya adalah delete, maka insert kembali node tersebut
            insertAtCursor(L, L.cursor, cek.node->info);
        }
    } else {
        cout << "Stack Undo Kosong" << endl; // Jika stack undo kosong, tampilkan pesan
    }
}



void redoOperation(List &L, Stack &undoStack, Stack &redoStack) {
    // Mengecek apakah stack redo tidak kosong
    if (!isEmpty(redoStack)) {
        Check cek; // Objek untuk menyimpan data yang dikeluarkan dari stack
        pop(redoStack, cek); // Mengeluarkan data terakhir dari stack redo
        push(undoStack, cek); // Menyimpan data tersebut ke stack undo

        // Mengecek tipe operasi yang dilakukan
        if (cek.type == "insert") {
            // Jika operasi redo adalah "insert", sisipkan node tersebut kembali ke list
            insertAtCursor(L, L.cursor, cek.node->info);
        } else if (cek.type == "delete") {
            address deletedNode = cek.node; // Menyimpan node yang dihapus
            // Jika operasi redo adalah "delete", hapus kembali node tersebut dari list
            deleteAtCursor(L, L.cursor->prev, deletedNode);
        }
    } else {
        cout << "Stack Redo Kosong" << endl; // Jika stack redo kosong, tampilkan pesan
    }
}

//kei
void insertAtCursor(List &L, address &cursor, infotype x) {
    // Membuat node baru
    address newNode = new elmlist;

    // Mengisi informasi pada node baru
    newNode->info = x;

    // Menentukan hubungan node baru dengan posisi cursor
    newNode->next = L.cursor;               // Node baru menunjuk ke node yang sedang ditunjuk oleh cursor
    newNode->prev = L.cursor->prev;         // Node baru menunjuk ke node sebelumnya dari cursor

    // Jika node sebelum cursor ada, perbarui hubungan antara node sebelumnya dan node baru
    if (L.cursor->prev != nullptr) {
        L.cursor->prev->next = newNode;     // Node sebelumnya menunjuk ke node baru
    } else {
        L.first = newNode;                  // Jika tidak ada node sebelumnya, node baru menjadi node pertama
    }

    // Perbarui hubungan antara cursor dan node baru
    L.cursor->prev = newNode;               // Node cursor sekarang menunjuk kembali ke node baru
}


void deleteAtCursor(List &L, address &cursor, address &x) {
    // Jika tidak ada elemen sebelum posisi cursor, fungsi langsung keluar
    if (L.cursor->prev == NULL) {
        return; // Tidak ada elemen yang bisa dihapus
    }
    // Jika cursor menunjuk ke elemen valid
    else if (cursor != nullptr) {
        x = cursor; // Simpan alamat elemen yang akan dihapus dalam variabel x

        // Jika elemen yang dihapus adalah elemen pertama
        if (cursor == L.first) {
            deleteFirst(L, x);    // Panggil fungsi deleteFirst untuk menghapus elemen pertama
            L.cursor = L.first;   // Atur cursor ke elemen pertama yang baru
        }
        // Jika elemen yang dihapus adalah elemen terakhir
        else if (cursor == L.last) {
            deleteLast(L, x);     // Panggil fungsi deleteLast untuk menghapus elemen terakhir
            L.cursor = L.last;    // Atur cursor ke elemen terakhir yang baru
        }
        // Jika elemen yang dihapus berada di tengah
        else {
            deleteAfter(L, cursor->prev, x); // Hapus elemen setelah elemen sebelumnya (prev)
            L.cursor = cursor->next;         // Pindahkan cursor ke elemen berikutnya
        }
    }
    // Jika cursor tidak menunjuk elemen valid
    else {
        L.cursor = nullptr; // Atur cursor menjadi null
    }
}

//azza
void moveCursorLeft(List &L, address &cursor) {
    // Mengecek jika kursor tidak berada di awal list
    if (L.cursor->prev != nullptr) {
        address prevNode = L.cursor->prev;  // Mendapatkan node sebelumnya

        // Jika node sebelumnya memiliki node sebelumnya lagi
        if (prevNode->prev != nullptr) {
            prevNode->prev->next = L.cursor;  // Menetapkan next node sebelumnya untuk menunjuk ke kursor
        } else {
            L.first = L.cursor;  // Jika sebelumnya adalah node pertama, maka set first ke kursor
        }
        L.cursor->prev = prevNode->prev;  // Memindahkan kursor ke node sebelumnya

        prevNode->next = L.cursor->next;  // Memindahkan prevNode untuk menunjuk ke next kursor
        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = prevNode;  // Jika ada next node, atur prev dari next node untuk menunjuk ke prevNode
        }
        L.cursor->next = prevNode;  // Menetapkan next kursor ke prevNode
        prevNode->prev = L.cursor;  // Menetapkan prevNode untuk menunjuk ke kursor
    } else {
        cout << "Cursor sudah di awal list!\n";  // Menampilkan pesan jika kursor sudah di awal list
    }
}

void moveCursorRight(List &L, address &cursor) {
    // Mengecek jika kursor tidak berada di akhir list
    if (L.cursor->next != nullptr) {
        address nextNode = L.cursor->next;  // Mendapatkan node berikutnya

        // Jika nextNode memiliki node setelahnya
        if (nextNode->next != nullptr) {
            nextNode->next->prev = L.cursor;  // Menetapkan prev dari nextNode berikutnya untuk menunjuk ke kursor
        } else {
            L.last = L.cursor;  // Jika nextNode adalah node terakhir, set last ke kursor
        }
        L.cursor->next = nextNode->next;  // Memindahkan kursor ke next node
        nextNode->prev = L.cursor->prev;  // Menetapkan prevNode untuk menunjuk ke prev dari kursor
        if (L.cursor->prev != nullptr) {
            L.cursor->prev->next = nextNode;  // Jika ada prevNode, set next-nya untuk menunjuk ke nextNode
        } else {
            L.first = nextNode;  // Jika prevNode adalah node pertama, set first ke nextNode
        }
        L.cursor->prev = nextNode;  // Menetapkan prev kursor ke nextNode
        nextNode->next = L.cursor;  // Menetapkan nextNode untuk menunjuk ke kursor
    } else {
        cout << "Cursor sudah di akhir list!\n";  // Menampilkan pesan jika kursor sudah di akhir list
    }
}
