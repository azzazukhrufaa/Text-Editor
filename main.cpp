#include <iostream>
#include "texteditor.h"
#include <conio.h>
using namespace std;

int main() {
    //feli
    textEditor editor;

    // Membuat list untuk teks (dll) dan stack untuk undo/redo
    createList(editor.dll);
    createStack(editor.undo);
    createStack(editor.redo);
    Check cek;

    // Membuat node awal sebagai kursor dengan info simbol '|'
    address cur = new elmlist;
    cur->info = '|';  // Menandakan posisi kursor
    cur->next = nullptr;
    cur->prev = nullptr;

    // Menetapkan kursor ke posisi awal
    editor.dll.cursor = cur;
    editor.dll.first = cur;
    editor.dll.last = cur;

    char input;

    cout << "Text Editor Sederhana\n";
    cout << "ESC: Keluar, Backspace: Hapus, Ctrl+Z: Undo, Ctrl+Y: Redo\n\n";

    while (true) {
        input = getch(); // Membaca input dari user tanpa perlu menekan Enter

        // Program keluar jika menekan tombol ESC
        if (input == 27) {
            cout << "\nProgram selesai. Hasil akhir teks:\n";
            cetakList(editor.dll);  // Menampilkan teks yang sudah diketik
            break;
        }
        //azza
        // Jika menekan Backspace, hapus karakter sebelum kursor
        else if (input == 8) {
            address x;
            deleteAtCursor(editor.dll, editor.dll.cursor->prev, x);  // Menghapus karakter di posisi sebelumnya
            cek.node = x;
            cek.type = "delete"; // Menandakan bahwa operasi ini adalah penghapusan
            push(editor.undo, cek); // Menyimpan operasi di stack undo
            createStack(editor.redo); // Reset stack redo
            cout << "\rTeks: ";
        }
        // Jika menekan Ctrl+Z, lakukan undo
        else if (input == 26) {
            undoOperation(editor.dll, editor.undo, editor.redo);  // Membatalkan operasi terakhir
            cout << "\rTeks: ";
            cetakList(editor.dll);  // Menampilkan teks setelah undo
        }
        // Jika menekan Ctrl+Y, lakukan redo
        else if (input == 25) {
            redoOperation(editor.dll, editor.undo, editor.redo);  // Mengulangi operasi yang dibatalkan
            cout << "\rTeks: ";
            cetakList(editor.dll); // Menampilkan teks setelah redo
        }
        // Jika input adalah karakter biasa, sisipkan ke posisi kursor
        else if (input >= 32 && input <= 126) {
            address x = createElement(input); // Membuat node baru dengan karakter input
            insertAtCursor(editor.dll, editor.dll.cursor, input);  // Menyisipkan karakter di posisi kursor
            cek.node = x;
            cek.type = "insert";  // Menandakan bahwa operasi ini adalah penyisipan
            push(editor.undo, cek);  // Menyimpan operasi di stack undo
            createStack(editor.redo); // Reset stack redo
            cout << "\rTeks: ";
        }
        //kei
        // Jika menekan tombol arah, gerakkan kursor
        else if (input == -32) {
            input = getch(); // Mengambil kode tombol arah
            if (input == 75) { // Tombol panah kiri
                moveCursorLeft(editor.dll, editor.dll.cursor);
            } else if (input == 77) { // Tombol panah kanan
                moveCursorRight(editor.dll, editor.dll.cursor);
            }
        }

        system("cls");  // Membersihkan layar untuk memperbarui teks
        cetakList(editor.dll);  // Menampilkan teks yang sudah diketik
        // Menampilkan posisi kursor atau 'null' jika tidak ada kursor
        if (editor.dll.cursor != nullptr) {
            if (editor.dll.cursor->prev == nullptr) {
                cout  << editor.dll.cursor->info  << endl;  // Menampilkan karakter kursor
            } else {
                cout  << editor.dll.cursor->prev->info  << endl;  // Menampilkan karakter sebelum kursor
            }
        } else {
            cout << "null" << endl;
        }
    }

    return 0; // Mengakhiri program
}
