# <h1 align="center">Laporan Praktikum Modul Tipe Data</h1>
<p align="center">Egi Rizkiyansyah</p>

## Dasar Teori
a.	Pengertian Hash Table
      Hash Table adalah struktur data yang mengorganisir data ke dalam pasangan kunci-nilai. Hash table biasanya terdiri dari dua komponen utama: array (atau vektor) dan fungsi hash. Hashing adalah teknik untuk mengubah rentang nilai kunci menjadi rentang indeks array.
      Array menyimpan data dalam slot-slot yang disebut bucket. Setiap bucket dapat menampung satu atau beberapa item data. Fungsi hash digunakan untuk menghasilkan nilai unik dari setiap item data, yang digunakan sebagai indeks array. Dengan cara ini, hash table memungkinkan pencarian data dalam waktu yang konstan (O(1)) dalam kasus terbaik.
      Sistem hash table bekerja dengan cara mengambil input kunci dan memetakkannya ke nilai indeks array menggunakan fungsi hash. Kemudian, data disimpan pada posisi indeks array yang dihasilkan oleh fungsi hash. Ketika data perlu dicari, input kunci dijadikan sebagai parameter untuk fungsi hash, dan posisi indeks array yang dihasilkan digunakan untuk mencari data. Dalam kasus hash collision, di mana dua atau lebih data memiliki nilai hash yang sama, hash table menyimpan data tersebut dalam slot yang sama dengan Teknik yang disebut chaining.

b.	Fungsi Hash Table 
Fungsi hash membuat pemetaan antara kunci dan nilai, hal ini dilakukan melalui penggunaan rumus matematika yang dikenal sebagai fungsi hash. Hasil dari fungsi hash disebut sebagai nilai hash atau hash. Nilai hash adalah representasi dari string karakter asli tetapi biasanya lebih kecil dari aslinya.

c.	Operasi Hash Table
1.	Insertion:
Memasukkan data baru ke dalam hash table dengan memanggil fungsi hash untuk menentukan posisi bucket yang tepat, dan kemudian menambahkan data ke bucket tersebut.
2.	Deletion:
Menghapus data dari hash table dengan mencari data menggunakan fungsi hash, dan kemudian menghapusnya dari bucket yang sesuai.
3.	Searching:
Mencari data dalam hash table dengan memasukkan input kunci ke fungsi hash untuk menentukan posisi bucket, dan kemudian mencari data di dalam bucket yang sesuai.
4.	Update:
Memperbarui data dalam hash table dengan mencari data menggunakan fungsi hash, dan kemudian memperbarui data yang ditemukan.
5.	Traversal:
Melalui seluruh hash table untuk memproses semua data yang ada dalam tabel.

d.	Collision Resolution
Keterbatasan tabel hash adalah jika dua angka dimasukkan ke dalam fungsi hash menghasilkan nilai yang sama. Hal ini disebut dengan collision. Ada dua teknik untuk menyelesaikan masalah ini diantaranya :

1.	Open Hashing (Chaining)
Metode chaining mengatasi collision dengan cara menyimpan semua item data dengan nilai indeks yang sama ke dalam sebuah linked list. Setiap node pada linked list merepresentasikan satu item data. Ketika ada pencarian atau penambahan item data, pencarian atau penambahan dilakukan pada linked list yang sesuai dengan indeks yang telah dihitung dari kunci yang di hash. Ketika linked list memiliki banyak node, pencarian atau penambahan item data menjadi lambat, karena harus mencari di seluruh linked list. Namun, chaining dapat mengatasi jumlah item data yang besar dengan efektif, karena keterbatasan array dihindari.
2.	Closed Hashing
●	Linear Probing
Pada saat terjadi collision, maka akan mencari posisi yang kosong di bawah tempat terjadinya collision, jika masih penuh terus ke bawah, hingga ketemu tempat yang kosong. Jika tidak ada tempat yang kosong berarti HashTable sudah penuh.
●	Quadratic Probing
Penanganannya hampir sama dengan metode linear, hanya lompatannya tidak satu-satu, tetapi quadratic ( 12, 22, 32, 42, ... )
●	Double Hashing
Pada saat terjadi collision, terdapat fungsi hash yang kedua untuk menentukan posisinya kembali.

## Guided 
### 1. [ Soal Guided 1 ]

```C++
#include <iostream>
using namespace std;
const int MAX_SIZE = 10;

// Fungsi hash sederhana
int hash_func(int key) {
    return key % MAX_SIZE;
}

// Struktur data untuk setiap node
struct Node {
    int key;
    int value;
    Node* next;
    Node(int key, int value) : key(key), value(value), next(nullptr) {}
};

// Class hash table
class HashTable {
private:
    Node** table;
public:
    HashTable() {
        table = new Node*[MAX_SIZE]();
    }
    ~HashTable() {
        for (int i = 0; i < MAX_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Insertion
    void insert(int key, int value) {
        int index = hash_func(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        Node* node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
    }

    // Searching
    int get(int key) {
        int index = hash_func(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return -1;
    }

    // Deletion
    void remove(int key) {
        int index = hash_func(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Traversal
    void traverse() {
        for (int i = 0; i < MAX_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                cout << current->key << ": " << current->value << endl;
                current = current->next;
            }
        }
    }
};

int main() {
    HashTable ht;
    // Insertion
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);

    // Searching
    cout << "Get key 1: " << ht.get(1) << endl;
    cout << "Get key 4: " << ht.get(4) << endl;
   
    // Deletion
    ht.remove(4);
   
    // Traversal
    ht.traverse();
   
    return 0;
}

```
#### Full code Screenshot:
![Screenshot 2024-06-01 233610](https://github.com/egirizkiyan/egi-30/assets/162097461/228afef1-ae55-4e00-8bda-a8aada9e4cf2)

#### Output:
![Screenshot 2024-06-01 233825](https://github.com/egirizkiyan/egi-30/assets/162097461/d9454c1c-e972-4ebb-a4e1-4bc1aadc0464)


Kesimpulan
Pada implementasi hash table ini, setiap data mahasiswa yang mencakup nama, NIM, dan nilai, disimpan dalam struktur data berbasis array dinamis yang menggunakan linked list untuk setiap bucketnya. Setiap bucket dapat menyimpan beberapa mahasiswa yang mungkin memiliki hash yang sama, sehingga mengatasi kemungkinan terjadinya collision dalam hash table.

Struktur Hash Table:

  -Array dinamis "table" digunakan untuk menyimpan bucket.
  - Setiap bucket diwakili oleh linked list, di mana setiap node merepresentasikan satu item data (mahasiswa).

Fungsi Hash:

  - Fungsi hash sederhana menggunakan modulus (nim % size) untuk memetakan setiap NIM ke indeks dalam array. Ini memastikan distribusi yang relatif merata dari data dalam array berdasarkan ukuran hash table yang telah ditentukan.

Operasi yang Didukung:

 1. Menambahkan Data (add):

   - Data mahasiswa ditambahkan ke bucket yang sesuai berdasarkan hasil fungsi hash.
   - Jika bucket sudah ada, data mahasiswa baru ditambahkan ke linked list di bucket tersebut.

2. Menghapus Data (remove):

  - Data mahasiswa dihapus dari bucket yang sesuai dengan NIM yang diberikan.
  - ika ditemukan, data dihapus dari linked list dalam bucket tersebut.

3. Mencari Data Berdasarkan NIM (searchByNim):

  - Pencarian dilakukan di bucket yang sesuai berdasarkan hasil fungsi hash.
  - Jika ditemukan, data mahasiswa ditampilkan.

4. Mencari Data Berdasarkan Rentang Nilai (searchByNilaiRange):

  - Seluruh hash table diiterasi untuk mencari mahasiswa dengan nilai dalam rentang yang diberikan (80-90).
  - Setiap mahasiswa yang memenuhi kriteria ditampilkan.

Keunggulan:

  - Implementasi ini memungkinkan penyimpanan dan pengelolaan data mahasiswa secara efisien.
  - Penanganan collision menggunakan linked list memastikan tidak ada data yang hilang atau tertimpa ketika terjadi collision.
  - Fungsi hash sederhana namun efektif untuk memetakan NIM ke indeks array.

Kelemahan:

  - Penggunaan linked list untuk setiap bucket mungkin menyebabkan overhead tambahan dalam hal memori dan waktu pencarian jika banyak collision terjadi.
  - Fungsi hash yang sederhana mungkin tidak selalu memberikan distribusi yang optimal, terutama jika data NIM memiliki pola tertentu.

Secara keseluruhan, implementasi hash table ini memberikan solusi yang efisien untuk penyimpanan dan pengelolaan data mahasiswa, serta menyediakan operasi dasar yang diperlukan untuk menambahkan, menghapus, dan mencari data mahasiswa berdasarkan NIM dan nilai.

### 2. [soal guided 2 ]

```C++
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int TABLE_SIZE = 11;

string name;
string phone_number;

class HashNode {
public:
    string name;
    string phone_number;

    HashNode(string name, string phone_number) {
        this->name = name;
        this->phone_number = phone_number;
    }
};

class HashMap {
private:
    vector<HashNode*> table[TABLE_SIZE];
public:
    int hashFunc(string key) {
        int hash_val = 0;
        for (char c : key) {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

    void insert(string name, string phone_number) {
        int hash_val = hashFunc(name);

        for (auto node : table[hash_val]) {
            if (node->name == name) {
                node->phone_number = phone_number;
                return;
            }
        }
        table[hash_val].push_back(new HashNode(name, phone_number));
    }

    void remove(string name) {
        int hash_val = hashFunc(name);

        for (auto it = table[hash_val].begin(); it != table[hash_val].end(); it++) {
            if ((*it)->name == name) {
                table[hash_val].erase(it);
                return;
            }
        }
    }

    string searchByName(string name) {
        int hash_val = hashFunc(name);
        for (auto node : table[hash_val]) {
            if (node->name == name) {
                return node->phone_number;
            }
        }
        return "";
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            for (auto pair : table[i]) {
                if (pair != nullptr) {
                    cout << "[" << pair->name << ", " << pair->phone_number << "]";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    HashMap employee_map;

    employee_map.insert("Mistah", "1234");
    employee_map.insert("Pastah", "5678");
    employee_map.insert("Ghana", "91011");

    cout << "Nomer Hp Mistah : " << employee_map.searchByName("Mistah") << endl;
    cout << "Phone Hp Pastah : " << employee_map.searchByName("Pastah") << endl;

    employee_map.remove("Mistah");

    cout << "Nomer Hp Mistah setelah dihapus : " << employee_map.searchByName("Mistah") << endl << endl;

    cout << "Hash Table : " << endl;

    employee_map.print();

    return 0;
}

```
#### Full code Screenshot:
![Screenshot 2024-06-02 003744](https://github.com/egirizkiyan/egi-30/assets/162097461/128f1f17-a924-43de-b041-d779b1e854fc)

#### Output:
![Screenshot 2024-06-02 003844](https://github.com/egirizkiyan/egi-30/assets/162097461/98947d09-d7ef-43db-931b-b0c3b736eb68)

Pada program di atas, class HashNode merepresentasikan setiap node dalam hash table, yang terdiri dari nama dan nomor telepon karyawan. Class HashMap digunakan untuk mengimplementasikan struktur hash table dengan menggunakan vector yang menampung pointer ke HashNode. Fungsi hashFunc digunakan untuk menghitung nilai hash dari nama karyawan yang diberikan, dan fungsi insert digunakan untuk menambahkan data baru ke dalam hash table. Fungsi remove digunakan untuk menghapus data dari hash table, dan fungsi searchByName digunakan untuk mencari nomor telepon dari karyawan dengan nama yang diberikan.


## Unguided 
### 1. [Hash Table]

```C++
#include <iostream>
#include <vector>

using namespace std;

struct Mahasiswa {
    string nim;
    float nilai;
};

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<Mahasiswa> table[TABLE_SIZE];

    int hashFunction(string nim) {
        int sum = 0;
        for (char c : nim) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

public:
    void add(string nim, float nilai) {
        int index = hashFunction(nim);
        for (Mahasiswa &mhs : table[index]) {
            if (mhs.nim == nim) {
                mhs.nilai = nilai;
                return;
            }
        }
        table[index].push_back({nim, nilai});
    }

    void remove(string nim) {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->nim == nim) {
                table[index].erase(it);
                return;
            }
        }
    }

    Mahasiswa* searchByNIM(string nim) {
        int index = hashFunction(nim);
        for (Mahasiswa &mhs : table[index]) {
            if (mhs.nim == nim) {
                return &mhs;
            }
        }
        return nullptr;
    }

    vector<Mahasiswa*> searchByValueRange(float min_value, float max_value) {
        vector<Mahasiswa*> result;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (Mahasiswa &mhs : table[i]) {
                if (mhs.nilai >= min_value && mhs.nilai <= max_value) {
                    result.push_back(&mhs);
                }
            }
        }
        return result;
    }

    void displayMenu() {
        cout << "Menu:" << endl;
        cout << "1. Tambah Data Mahasiswa" << endl;
        cout << "2. Hapus Data Mahasiswa" << endl;
        cout << "3. Cari Data Berdasarkan NIM" << endl;
        cout << "4. Cari Data Berdasarkan Rentang Nilai (80-90)" << endl;
        cout << "5. Tampilkan Semua Data Mahasiswa" << endl;
        cout << "6. Keluar" << endl;
    }

    void run() {
        int choice;
        string nim;
        float nilai;
        while (true) {
            displayMenu();
            cout << "Pilih opsi: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Masukkan NIM: ";
                    cin >> nim;
                    cout << "Masukkan Nilai: ";
                    cin >> nilai;
                    add(nim, nilai);
                    cout << "Data mahasiswa ditambahkan." << endl;
                    break;
                case 2:
                    cout << "Masukkan NIM yang akan dihapus: ";
                    cin >> nim;
                    remove(nim);
                    cout << "Data mahasiswa dihapus." << endl;
                    break;
                case 3:
                    cout << "Masukkan NIM yang dicari: ";
                    cin >> nim;
                    {
                        Mahasiswa* mhs = searchByNIM(nim);
                        if (mhs) {
                            cout << "NIM: " << mhs->nim << ", Nilai: " << mhs->nilai << endl;
                        } else {
                            cout << "Data mahasiswa tidak ditemukan." << endl;
                        }
                    }
                    break;
                case 4:
                    {
                        float min_value = 80.0, max_value = 90.0;
                        vector<Mahasiswa*> result = searchByValueRange(min_value, max_value);
                        if (!result.empty()) {
                            cout << "Mahasiswa dengan nilai antara 80-90:" << endl;
                            for (Mahasiswa* mhs : result) {
                                cout << "NIM: " << mhs->nim << ", Nilai: " << mhs->nilai << endl;
                            }
                        } else {
                            cout << "Tidak ada mahasiswa dengan nilai dalam rentang tersebut." << endl;
                        }
                    }
                    break;
                case 5:
                    cout << "Semua Data Mahasiswa:" << endl;
                    for (int i = 0; i < TABLE_SIZE; ++i) {
                        for (Mahasiswa &mhs : table[i]) {
                            cout << "NIM: " << mhs.nim << ", Nilai: " << mhs.nilai << endl;
                        }
                    }
                    break;
                case 6:
                    cout << "Keluar dari program." << endl;
                    return;
                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                    break;
            }
        }
    }
};

int main() {
    HashTable hashTable;
    hashTable.run();
    return 0;
}

```
#### Output:
![Screenshot 2024-06-02 004342](https://github.com/egirizkiyan/egi-30/assets/162097461/0a2354fb-3409-4660-90ff-b08e41485edc)


#### Full code Screenshot:
![Screenshot 2024-06-02 004233](https://github.com/egirizkiyan/egi-30/assets/162097461/d6d43920-46cc-4637-8d62-48e492c27ded)

Penjelasan:

1. Class Mahasiswa:

   - Menyimpan nama, NIM, dan nilai mahasiswa.

2. Class HashTable:

   - hashFunction: Fungsi hash sederhana menggunakan modulus.
   - add: Menambahkan data mahasiswa ke dalam hash table.
   - remove: Menghapus data mahasiswa berdasarkan NIM.
   - searchByNim: Mencari mahasiswa berdasarkan NIM.
   - searchByNilaiRange: Mencari mahasiswa yang memiliki nilai dalam rentang tertentu (80-90).

3. Function displayMenu:

  - Menampilkan menu pilihan untuk pengguna.

4. Function main:

   - Menangani input pengguna untuk mengelola mahasiswa dengan nama, NIM, dan nilai.

Program ini menyediakan antarmuka menu yang mudah digunakan untuk berinteraksi dengan hash table mahasiswa.

## Kesimpulan
Kesimpulan:
  Pada implementasi kode di atas, kami menggunakan struktur data hash table untuk menyimpan dan mengelola data mahasiswa dengan memanfaatkan linked list untuk menangani collision. Berikut adalah rincian dan kesimpulan dari setiap bagian kode:

Bagian 1: Implementasi Hash Table dengan Linked List untuk Menyimpan Kunci dan Nilai
  
  - Struktur Node: Setiap node menyimpan kunci (key), nilai (value), dan pointer ke node berikutnya (next). Ini memungkinkan penanganan collision dengan linked list.

  - Fungsi hash sederhana: Menggunakan modulus (key % MAX_SIZE) untuk memetakan kunci ke indeks array.

  - Operasi yang Didukung:
    - insert: Menambahkan node baru atau memperbarui nilai jika kunci sudah ada.
    - get: Mencari nilai berdasarkan kunci.
    - remove: Menghapus node berdasarkan kunci.
    - traverse: Menampilkan semua elemen dalam hash table.

Bagian 2: Implementasi Hash Table untuk Data Mahasiswa dengan Rentang Nilai
  - Struktur Mahasiswa: Menyimpan NIM dan nilai.
  - Hash Function: Menghasilkan indeks berdasarkan jumlah karakter dalam NIM.
  - Operasi yang Didukung:
    - add: Menambahkan data mahasiswa.
    - remove: Menghapus data mahasiswa berdasarkan NIM.
    - searchByNIM: Mencari mahasiswa berdasarkan NIM.
    - searchByValueRange: Mencari mahasiswa dalam rentang nilai tertentu (80-90).
    - displayMenu dan run: Menyediakan antarmuka menu interaktif untuk pengguna.

Bagian 3: Implementasi Hash Table untuk Menyimpan Nama dan Nomor Telepon
  
  - Struktur HashNode: Menyimpan nama dan nomor telepon.
  - Hash Function: Menghasilkan nilai hash berdasarkan jumlah karakter dalam nama.
  - Operasi yang Didukung:
    - insert: Menambahkan atau memperbarui nomor telepon berdasarkan nama.
    - remove: Menghapus data berdasarkan nama.
    - searchByName: Mencari nomor telepon berdasarkan nama.
    - print: Menampilkan semua data dalam hash table.

Keunggulan:
  - Efisiensi: Hash table memungkinkan pencarian, penambahan, dan penghapusan data dengan waktu yang relatif cepat.
  - Penanganan Collision: Penggunaan linked list dalam bucket menangani collision secara efektif.
  - Struktur Data yang Sederhana: Implementasi ini cukup mudah dipahami dan diimplementasikan.

Kelemahan:

   - Penggunaan Memori: Linked list dalam setiap bucket dapat meningkatkan penggunaan memori.
   - Hash Function Sederhana: Fungsi hash yang sederhana mungkin tidak selalu menghasilkan distribusi hash yang optimal, terutama jika terdapat pola dalam data input.
   - Kompleksitas Kode: Penanganan linked list dapat meningkatkan kompleksitas kode, terutama untuk operasi penghapusan dan pencarian.

Kesimpulan Akhir:
   Implementasi hash table dalam berbagai konteks menunjukkan fleksibilitas dan efisiensi struktur data ini untuk menyimpan dan mengelola data. Meskipun terdapat beberapa kelemahan, seperti penggunaan memori yang lebih tinggi dan kebutuhan untuk penanganan collision, hash table tetap menjadi pilihan yang kuat untuk operasi pencarian cepat dan pengelolaan data yang efisien.

## Referensi
[1] "Introduction to Algorithms" oleh Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, dan Clifford Stein
Tahun Terbit: 1990 (Edisi Pertama)
[2] Data Structures and Algorithm Analysis in C++" oleh Mark Allen Weiss
Tahun Terbit: 1994 (Edisi Pertama)
[3] "The Art of Computer Programming" oleh Donald E. Knuth
Tahun Terbit: 1968 (Volume 1, Edisi Pertama)