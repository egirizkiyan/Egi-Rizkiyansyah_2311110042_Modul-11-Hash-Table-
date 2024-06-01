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
