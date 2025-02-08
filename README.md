# CoreFinCpp

CoreFinCpp adalah aplikasi manajemen keuangan sederhana yang ditulis dalam bahasa C++. Aplikasi ini memungkinkan pengguna untuk menambahkan, melihat, mengedit, dan menghapus transaksi keuangan mereka. Aplikasi ini juga menyediakan fitur untuk menyimpan dan memuat data transaksi dari file.

## Fitur

- **Tambah Transaksi**: Pengguna dapat menambahkan transaksi baru dengan nama, kategori, jumlah, dan tanggal.
- **Lihat Laporan**: Pengguna dapat melihat laporan transaksi mereka.
- **Edit Transaksi**: Pengguna dapat mengedit transaksi yang sudah ada.
- **Hapus Transaksi**: Pengguna dapat menghapus transaksi yang sudah ada.
- **Simpan Laporan**: Pengguna dapat menyimpan laporan transaksi ke file.
- **Muat Data Pengguna**: Aplikasi dapat memuat data pengguna dari file.

## Persyaratan Minimum

- **CMake** versi 3.10 atau lebih baru
- **Compiler** yang mendukung C++11
- **Make** utility
- **Sistem Operasi** `MacOS` , `Linux` (recommended) , atau `Windows(WSL)`
- **Support Ansi Color** Terminal 

Untuk memeriksa apakah persyaratan minimum sudah dipenuhi, jalankan perintah berikut:

# Periksa versi CMake 

```sh
    cmake --version
```

# Periksa versi g++

```sh
    g++ --version 
```

# Periksa versi Make

```sh
    make --version
```
# Support ANSI color **pastikan teks ini berubah warna menjadi merah**

```sh
   printf "\e[31mThis text should be red.\e[0m\n"
```

Jika semua perintah di atas menunjukkan versi yang sesuai atau lebih baru, maka persyaratan minimum sudah dipenuhi.

## Struktur Proyek

```
corefincpp/
├── build/                  # Direktori build
├── include/                # Direktori header
│   ├── extlib/             # Header eksternal
│   └── headers/            # Header internal
├── src/                    # Direktori sumber
│   ├── modules/            # Modul aplikasi
│   └── main.cpp            # File utama
├── CMakeLists.txt          # Konfigurasi CMake
└── README.md               # Dokumentasi proyek
```

## Instalasi

1. Clone repositori ini:
    ```sh
    git clone https://github.com/TudeOrangBiasa/corefincpp.git
    cd corefincpp
    ```

2. Buat direktori build dan navigasikan ke dalamnya:
    ```sh
    mkdir build
    cd build
    ```

3. Jalankan CMake untuk menghasilkan makefile:
    ```sh
    cmake ..
    ```

4. Kompilasi proyek:
    ```sh
    make
    ```

## Penggunaan

Setelah kompilasi selesai, Anda dapat menjalankan aplikasi dengan perintah berikut:
```sh
./corefincpp
```

## Kontribusi

Kontribusi sangat diterima! Silakan fork repositori ini dan buat pull request dengan perubahan Anda.

