#include <iostream>
#include <string>
#include <limits> // Diperlukan untuk validasi input
#include <fstream> // Diperlukan untuk operasi file
#include <cstdlib> // Diperlukan untuk EOF dan system("pause")

using namespace std;

// Struktur data untuk representasi Pasien
struct Pasien {
    string namaPasien;
    int noRegistrasiPasien;
    string alamat;
    string penyakit;
    string kategori;
    string jenisKelamin;
    int usia;
};

// Konstanta untuk maksimum pasien yang dapat ditampung
const int MAX_PASIEN = 100;

// Konstanta untuk username dan password admin
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

// Nomor registrasi terakhir, digunakan untuk meng-generate nomor registrasi baru
static int nomorRegistrasiTerakhir = 1000;

// Deklarasi fungsi-fungsi
void tambahPasien(Pasien daftarPasien[], int& jumlahPasien);
void tampilkanPasien(const Pasien daftarPasien[], int jumlahPasien, const string& kategori);
void tampilkanSemuaPasien(const Pasien daftarPasien[], int jumlahPasien);
void hapusPasien(Pasien daftarPasien[], int& jumlahPasien);
void perbaruiPasien(Pasien daftarPasien[], int jumlahPasien);
void cariPasien(const Pasien daftarPasien[], int jumlahPasien);
void simpanDataPasien(const Pasien daftarPasien[], int jumlahPasien, const string& namaFile);
void muatDataPasien(Pasien daftarPasien[], int& jumlahPasien, const string& namaFile);
bool loginAdmin();

// Fungsi utama program
int main() {
    Pasien daftarPasien[MAX_PASIEN];
    int jumlahPasien = 0;

    // Melakukan login admin
    if (!loginAdmin()) {
        cout << "Login gagal. Program berhenti.\n";
        return 1;
    }

    int pilihan;
    do {
        // Menampilkan menu utama
        cout << "\n=== Manajemen Pasien ===\n";
        cout << "1. Tambah Pasien (UMUM/BPJS)\n";
        cout << "2. Tampilkan Pasien (UMUM)\n";
        cout << "3. Tampilkan Pasien (BPJS)\n";
        cout << "4. Tampilkan Semua Pasien\n";
        cout << "5. Hapus Pasien\n";
        cout << "6. Perbarui Pasien\n";
        cout << "7. Cari Pasien\n";
        cout << "8. Keluar\n";
        cout << "9. Simpan Data Pasien ke File\n";
        cout << "10. Muat Data Pasien dari File\n";
        cout << "Pilih menu (1-10): ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Coba lagi: ";
        }

        switch (pilihan) {
            case 1:
                tambahPasien(daftarPasien, jumlahPasien);
                break;
            case 2:
                tampilkanPasien(daftarPasien, jumlahPasien, "UMUM");
                break;
            case 3:
                tampilkanPasien(daftarPasien, jumlahPasien, "BPJS");
                break;
            case 4:
                tampilkanSemuaPasien(daftarPasien, jumlahPasien);
                break;
            case 5:
                hapusPasien(daftarPasien, jumlahPasien);
                break;
            case 6:
                perbaruiPasien(daftarPasien, jumlahPasien);
                break;
            case 7:
                cariPasien(daftarPasien, jumlahPasien);
                break;
            case 8:
                cout << "Program selesai.\n";
                break;
            case 9:
                simpanDataPasien(daftarPasien, jumlahPasien, "pasien.txt");
                break;
            case 10:
                muatDataPasien(daftarPasien, jumlahPasien, "pasien.txt");
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 8);

    return 0;
}

// Fungsi untuk menambahkan pasien baru
void tambahPasien(Pasien daftarPasien[], int& jumlahPasien) {
    if (jumlahPasien < MAX_PASIEN) {
        Pasien pasienBaru;

        // Input nama pasien
        cout << "Nama Pasien: ";
        getline(cin >> ws, pasienBaru.namaPasien);

        // Generate nomor registrasi baru
        pasienBaru.noRegistrasiPasien = ++nomorRegistrasiTerakhir;

        // Input alamat, penyakit, kategori, jenis kelamin, dan usia
        cout << "Alamat: ";
        getline(cin >> ws, pasienBaru.alamat);
        cout << "Penyakit: ";
        getline(cin >> ws, pasienBaru.penyakit);

        do {
            // Validasi Kategori
            cout << "Kategori (BPJS/UMUM): ";
            cin >> pasienBaru.kategori;
            if (pasienBaru.kategori != "UMUM" && pasienBaru.kategori != "BPJS") {
                cout << "Kategori tidak valid. Harap masukkan 'UMUM' atau 'BPJS'.\n";
            }
        } while (pasienBaru.kategori != "UMUM" && pasienBaru.kategori != "BPJS");

        do {
            // Validasi Jenis Kelamin
            cout << "Jenis Kelamin (L/P): ";
            cin >> pasienBaru.jenisKelamin;
            if (pasienBaru.jenisKelamin != "L" && pasienBaru.jenisKelamin != "P") {
                cout << "Jenis Kelamin tidak valid. Harap masukkan 'L' untuk Laki-laki atau 'P' untuk Perempuan.\n";
            }
        } while (pasienBaru.jenisKelamin != "L" && pasienBaru.jenisKelamin != "P");

        do {
            // Validasi Usia
            cout << "Usia: ";
            cin >> pasienBaru.usia;
            if (pasienBaru.usia < 0 || pasienBaru.usia > 150) {
                cout << "Harap masukkan usia yang valid.\n";
            }
        } while (pasienBaru.usia < 0 || pasienBaru.usia > 150);

        // Tambahkan pasien ke dalam array
        daftarPasien[jumlahPasien++] = pasienBaru;

        cout << "Pasien berhasil ditambahkan. Nomor Registrasi: " << pasienBaru.noRegistrasiPasien << "\n";
    } else {
        cout << "Daftar pasien sudah penuh.\n";
    }
}

// Fungsi untuk menampilkan daftar pasien berdasarkan kategori
void tampilkanPasien(const Pasien daftarPasien[], int jumlahPasien, const string& kategori) {
    cout << "Daftar Pasien (" << kategori << "):\n";
    for (int i = 0; i < jumlahPasien; ++i) {
        if (daftarPasien[i].kategori == kategori) {
            // Menampilkan informasi pasien
            cout << "Nama: " << daftarPasien[i].namaPasien << "\n";
            cout << "Nomor Registrasi: " << daftarPasien[i].noRegistrasiPasien << "\n";
            cout << "Alamat: " << daftarPasien[i].alamat << "\n";
            cout << "Penyakit: " << daftarPasien[i].penyakit << "\n";
            cout << "Jenis Kelamin: " << daftarPasien[i].jenisKelamin << "\n";
            cout << "Usia: " << daftarPasien[i].usia << "\n";
        }
    }
}

// Fungsi untuk menampilkan daftar semua pasien
void tampilkanSemuaPasien(const Pasien daftarPasien[], int jumlahPasien) {
    cout << "Daftar Semua Pasien:\n";
    for (int i = 0; i < jumlahPasien; ++i) {
        // Menampilkan informasi pasien
        cout << "Nama: " << daftarPasien[i].namaPasien << "\n";
        cout << "Nomor Registrasi: " << daftarPasien[i].noRegistrasiPasien << "\n";
        cout << "Alamat: " << daftarPasien[i].alamat << "\n";
        cout << "Penyakit: " << daftarPasien[i].penyakit << "\n";
        cout << "Kategori: " << daftarPasien[i].kategori << "\n";
        cout << "Jenis Kelamin: " << daftarPasien[i].jenisKelamin << "\n";
        cout << "Usia: " << daftarPasien[i].usia << "\n";
    }
}

// Fungsi untuk menghapus pasien berdasarkan nomor registrasi
void hapusPasien(Pasien daftarPasien[], int& jumlahPasien) {
    int noRegistrasi;
    cout << "Masukkan Nomor Registrasi Pasien yang akan dihapus: ";
    cin >> noRegistrasi;

    for (int i = 0; i < jumlahPasien; ++i) {
        if (daftarPasien[i].noRegistrasiPasien == noRegistrasi) {
            // Geser elemen-elemen setelah pasien yang dihapus
            for (int j = i; j < jumlahPasien - 1; ++j) {
                daftarPasien[j] = daftarPasien[j + 1];
            }
            --jumlahPasien;

            cout << "Pasien berhasil dihapus.\n";
            return;
        }
    }

    cout << "Nomor Registrasi Pasien tidak ditemukan.\n";
}

// Fungsi untuk memperbarui informasi pasien berdasarkan nomor registrasi
void perbaruiPasien(Pasien daftarPasien[], int jumlahPasien) {
    int noRegistrasi;
    cout << "Masukkan Nomor Registrasi Pasien yang akan diperbarui: ";
    cin >> noRegistrasi;

    for (int i = 0; i < jumlahPasien; ++i) {
        if (daftarPasien[i].noRegistrasiPasien == noRegistrasi) {
            // Input informasi baru
            cout << "Nama Pasien: ";
            getline(cin >> ws, daftarPasien[i].namaPasien);
            cout << "Alamat: ";
            getline(cin >> ws, daftarPasien[i].alamat);
            cout << "Penyakit: ";
            getline(cin >> ws, daftarPasien[i].penyakit);

            cout << "Informasi Pasien berhasil diperbarui.\n";
            return;
        }
    }

    cout << "Nomor Registrasi Pasien tidak ditemukan.\n";
}

// Fungsi untuk mencari pasien berdasarkan nomor registrasi
void cariPasien(const Pasien daftarPasien[], int jumlahPasien) {
    int noRegistrasi;
    cout << "Masukkan Nomor Registrasi Pasien yang akan dicari: ";
    cin >> noRegistrasi;

    for (int i = 0; i < jumlahPasien; ++i) {
        if (daftarPasien[i].noRegistrasiPasien == noRegistrasi) {
            // Menampilkan informasi pasien
            cout << "Nama: " << daftarPasien[i].namaPasien << "\n";
            cout << "Nomor Registrasi: " << daftarPasien[i].noRegistrasiPasien << "\n";
            cout << "Alamat: " << daftarPasien[i].alamat << "\n";
            cout << "Penyakit: " << daftarPasien[i].penyakit << "\n";
            cout << "Kategori: " << daftarPasien[i].kategori << "\n";
            cout << "Usia: " << daftarPasien[i].usia << "\n";
            cout << "Jenis Kelamin: " << daftarPasien[i].jenisKelamin << "\n";
            return;
        }
    }

    cout << "Nomor Registrasi Pasien tidak ditemukan.\n";
}

// Fungsi untuk menyimpan data pasien ke dalam file
void simpanDataPasien(const Pasien daftarPasien[], int jumlahPasien, const string& namaFile) {
    ofstream fileOutput(namaFile);

    if (fileOutput.is_open()) {
        for (int i = 0; i < jumlahPasien; ++i) {
            fileOutput << daftarPasien[i].namaPasien << ","
                       << daftarPasien[i].noRegistrasiPasien << ","
                       << daftarPasien[i].alamat << ","
                       << daftarPasien[i].penyakit << ","
                       << daftarPasien[i].kategori << ","
                       << daftarPasien[i].jenisKelamin << ","
                       << daftarPasien[i].usia << "\n";
        }
        fileOutput.close();
        cout << "Data pasien berhasil disimpan ke dalam file.\n";
    } else {
        cout << "Gagal membuka file untuk penyimpanan data.\n";
    }
}

// Fungsi untuk memuat data pasien dari file
void muatDataPasien(Pasien daftarPasien[], int& jumlahPasien, const string& namaFile) {
    ifstream fileInput(namaFile);

    if (fileInput.is_open()) {
        while (fileInput.peek() != EOF) {
            Pasien pasienBaru;
            getline(fileInput, pasienBaru.namaPasien, ',');
            fileInput >> pasienBaru.noRegistrasiPasien;
            fileInput.ignore(); // Membuang karakter ',' yang tersisa
            getline(fileInput, pasienBaru.alamat, ',');
            getline(fileInput, pasienBaru.penyakit, ',');
            getline(fileInput, pasienBaru.kategori, ',');
            getline(fileInput, pasienBaru.jenisKelamin, ',');
            fileInput >> pasienBaru.usia;
            fileInput.ignore(); // Membuang karakter '\n' yang tersisa

            // Tambahkan pasien ke dalam array
            if (jumlahPasien < MAX_PASIEN) {
                daftarPasien[jumlahPasien++] = pasienBaru;
            } else {
                cout << "Daftar pasien sudah penuh.\n";
                break;
            }
        }
        fileInput.close();
        cout << "Data pasien berhasil dimuat dari file.\n";
    } else {
        cout << "Gagal membuka file untuk membaca data.\n";
    }
}


// Fungsi untuk melakukan login admin
bool loginAdmin() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}
