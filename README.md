
# Sistem Manajemen Buku - Binary Search Tree dengan Undo

Program ini adalah aplikasi berbasis **C++** untuk mengelola data buku menggunakan **Binary Search Tree (BST)**.
Aplikasi mendukung operasi tambah, tampil, hapus data buku, serta fitur **undo** untuk membatalkan aksi terakhir.

## Deskripsi Program

Data buku disimpan dalam struktur **Binary Search Tree** berdasarkan **judul buku** sebagai key.
Setiap perubahan data (tambah atau hapus) dicatat ke dalam **stack undo**, sehingga pengguna dapat mengembalikan kondisi sebelumnya.

### Struktur Data yang Digunakan

* **Binary Search Tree (BST)** untuk penyimpanan data buku
* **Stack (linked list)** untuk fitur undo

## Fitur Program

1. **Tambah Buku**

   * Input judul, pengarang, dan tahun terbit
   * Data dimasukkan ke BST berdasarkan judul
   * Aksi disimpan ke stack undo

2. **Tampilkan Data Buku**

   * Menampilkan seluruh buku dalam BST
   * Traversal dilakukan secara inorder terbalik (kanan - root - kiri)

3. **Hapus Buku**

   * Menghapus buku berdasarkan judul
   * Mendukung semua kondisi BST:

     * Node tanpa anak
     * Node dengan satu anak
     * Node dengan dua anak
   * Data yang dihapus disimpan ke undo

4. **Undo**

   * Membatalkan aksi terakhir
   * Undo tambah - buku yang ditambahkan akan dihapus
   * Undo hapus - buku yang dihapus akan dikembalikan ke BST

5. **Keluar Program**

## Struktur Program

```
/
├─ 124240092_LatihanResponsi.cpp        # Program utama
└─ README.md       # Dokumentasi
```

### Struktur Struct

* **struct buku**

  * judul
  * pengarang
  * tahunTerbit
  * left
  * right

* **struct undo**

  * aksi (tambah atau hapus)
  * data buku
  * next

## Alur Program Singkat

1. User memilih menu
2. Program menjalankan fungsi sesuai pilihan
3. Setiap aksi tambah atau hapus dicatat ke stack undo
4. Undo mengambil data terakhir dari stack dan mengembalikan kondisi BST

## Cara Menjalankan Program

1. Pastikan compiler C++ tersedia (misalnya g++)
2. Compile program:

   ```
   g++ main.cpp -o bst_buku
   ```
3. Jalankan program:

   ```
   ./bst_buku
   ```

## Catatan Penting

* Judul buku harus unik
* Undo hanya berlaku satu per satu sesuai urutan terakhir
* Program menggunakan `system("cls")` dan `system("pause")` sehingga direkomendasikan dijalankan di Windows

## Tujuan Pembelajaran

* Memahami implementasi Binary Search Tree
* Menerapkan operasi insert, delete, dan traversal BST
* Menggabungkan BST dengan struktur data stack
* Melatih logika undo dalam program

## License

Program ini dibuat untuk **keperluan pembelajaran dan tugas kuliah**.
