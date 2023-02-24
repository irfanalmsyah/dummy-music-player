# Dummy Music Player
Dummy Music Player adalah sebuah program dummy sederhana yang menjalankan musik. Program ini dibuat untuk memenuhi tugas mata kuliah Struktur Data.

## Anggota Kelompok
|Nama|NIM|
|--|--|
|[Rifqi Fauzan Azzam](https://github.com/rifqifazzam)|G6401211008|
|[Irfan Alamsyah](https://github.com/irfanalmsyah)|G6401211029|
|[Daffa Nofiansyah](https://github.com/DaffaNofiansyah)|G6401211098|


## Struktur Data yang diaplikasikan
### Hash Table
Hash Table yang digunakan dalam program ini adalah implementasi dari struktur data hash table yang menggunakan chaining untuk menangani collision. Hash Table ini digunakan untuk menyimpan data musik yang diinputkan oleh user. Setiap elemen di dalam hash table adalah vector yang berisi pointer ke objek-objek Music.

Untuk menentukan indeks dari sebuah elemen di dalam hash table, digunakan fungsi hash yang mengambil parameter judul lagu. Fungsi hash ini mengembalikan sebuah bilangan bulat yang merepresentasikan indeks di dalam hash table. Proses hashing menggunakan teknik modular hashing, dimana setiap karakter dari judul lagu akan dijumlahkan dan dikalikan dengan 31 pangkat urutan karakter dari kanan ke kiri, kemudian diambil modulus dari ukuran hash table untuk mendapatkan indeks.

Jika terjadi collision, yaitu ketika dua atau lebih elemen memiliki indeks yang sama, maka objek-objek Music yang memiliki judul lagu yang sama akan disimpan dalam satu vector yang sama di indeks tersebut (chaining). Proses pencarian dilakukan dengan mencari elemen di dalam vector dengan menggunakan judul lagu sebagai kunci pencarian. Jika ditemukan, maka pointer ke objek Music tersebut akan di-return. Untuk menghapus elemen dari hash table, akan dilakukan pencarian terlebih dahulu menggunakan judul lagu sebagai kunci pencarian. Jika ditemukan, maka elemen tersebut akan dihapus dari vector di indeks yang sesuai.

Selain itu, program ini juga memiliki fitur untuk mencetak 10 musik teratas di dalam hash table, yang dilakukan dengan mengiterasi seluruh elemen di dalam hash table dan mengeluarkan data musik menggunakan method print() yang terdapat pada kelas Music.

### Doubly Linked List
Dalam program ini, struktur data Doubly Linked List digunakan untuk merepresentasikan playlist. Doubly Linked List adalah struktur data linear yang terdiri dari beberapa node yang saling terhubung dengan dua pointer yaitu prev dan next. Prev pointer menunjuk ke node sebelumnya dan next pointer menunjuk ke node setelahnya. Pada playlist, setiap node merepresentasikan satu lagu dan memiliki pointer prev dan next yang menunjuk ke node sebelum dan setelahnya dalam playlist. Dengan menggunakan Doubly Linked List, kita dapat dengan mudah menambahkan atau menghapus lagu dari playlist, serta menavigasi ke depan dan belakang dalam playlist.

### Stack

### Queue
