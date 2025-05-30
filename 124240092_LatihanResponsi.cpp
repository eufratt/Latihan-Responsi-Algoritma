#include <iostream>
#include <cstring>
using namespace std;

struct buku
{
    char judul[50];
    char pengarang[50];
    int tahunTerbit;
    buku *right;
    buku *left;
};

struct undo
{
    int aksi;
    buku data;
    undo *next;
};

buku *root = nullptr, *bantu = nullptr;
undo *top = nullptr;

const int tambah = 1;
const int hapus = 2;

void tambahBuku();
void pushUndo(int aksi, buku *b);
void tampil(buku *node);
void hapusBuku();
void undoAksi();
bool hapusNode(char judul[]);

int main()
{
    int pilih;
    do
    {
        system("cls");
        cout << "Menu" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Tampilkan Data" << endl;
        cout << "3. Hapus Buku" << endl;
        cout << "4. Undo" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> pilih;
        switch (pilih)
        {
        case 1:
            tambahBuku();
            system("pause");
            break;
        case 2:
            if (root == nullptr)
            {
                cout << "Data Kosong" << endl;
            }else{
                tampil(root);
            }
            system("pause");
            break;
        case 3:
            hapusBuku();
            system("pause");
            break;
        case 4:
            undoAksi();
            system("pause");
            break;
        case 5:
            exit(0);
            break;

        default:
            cout << "Pilihan tidak valid.\n";
            system("pause");
            break;
        }

    } while (pilih != 5);
}

void tambahBuku()
{
    buku *baru = new buku();
    baru->left = nullptr;
    baru->right = nullptr;
    cin.ignore();
    cout << "Masukkan Judul Buku        : ";
    cin.getline(baru->judul, 50);
    cout << "Masukkan Pengarang Buku    : ";
    cin.getline(baru->pengarang, 50);
    cout << "Masukkan Tahun Terbit Buku : ";
    cin >> baru->tahunTerbit;

    if (root == nullptr)
    {
        root = baru;
        pushUndo(tambah, baru);
        cout << "Buku berhasil disimpan" << endl;
        return;
    }
    bantu = root;
    while (true)
    {
        if (strcmp(baru->judul, bantu->judul) < 0)
        {
            if (bantu->left == nullptr)
            {
                bantu->left = baru;
                pushUndo(tambah, baru);
                cout << "Buku berhasil disimpan" << endl;
                return;
            }
            bantu = bantu->left;
        }
        else if (strcmp(baru->judul, bantu->judul) > 0)
        {
            if (bantu->right == nullptr)
            {
                bantu->right = baru;
                pushUndo(tambah, baru);
                cout << "Buku berhasil disimpan" << endl;
                return;
            }
            bantu = bantu->right;
        }
        else
        {
            cout << "Buku sudah ada" << endl;
            delete baru;
            return;
        }
    }
}

void pushUndo(int aksi, buku *b)
{
    undo *baru = new undo();
    baru->aksi = aksi;
    baru->data = *b;
    baru->next = top;
    top = baru;
}

void tampil(buku *node)
{
    if (node == nullptr)
    {
        return;
    }
    tampil(node->right);
    cout << "[" << node->judul << "] - ";
    cout << "[" << node->pengarang << "] - ";
    cout << "[" << node->tahunTerbit << "]" << endl;
    tampil(node->left);
}

void hapusBuku()
{
    if (root == nullptr)
    {
        cout << "Data buku kosong.\n";
        return;
    }

    char judulHapus[50];
    cin.ignore();
    cout << "Masukkan judul buku yang ingin dihapus: ";
    cin.getline(judulHapus, 50);

    // Cari node untuk simpan ke undo
    buku *current = root;
    while (current != nullptr && strcmp(judulHapus, current->judul) != 0)
    {
        if (strcmp(judulHapus, current->judul) < 0)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr)
    {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    pushUndo(hapus, current);
    bool berhasil = hapusNode(judulHapus);
    if (berhasil)
        cout << "Buku berhasil dihapus.\n";
    else
        cout << "Gagal menghapus buku.\n";
}

void undoAksi()
{
    if (top == nullptr)
    {
        cout << "Tidak ada aksi yang bisa di-undo.\n";
        return;
    }

    undo *aksiUndo = top;
    top = top->next;

    if (aksiUndo->aksi == tambah)
    {
        if (hapusNode(aksiUndo->data.judul))
            cout << "Undo berhasil: tambah buku dibatalkan.\n";
        else
            cout << "Gagal undo tambah: buku tidak ditemukan.\n";
    }

    else if (aksiUndo->aksi == hapus)
    {
        // Undo penghapusan: tambahkan kembali buku
        buku *baru = new buku();
        *baru = aksiUndo->data;
        baru->left = nullptr;
        baru->right = nullptr;

        // Masukkan kembali ke BST
        if (root == nullptr)
        {
            root = baru;
        }
        else
        {
            bantu = root;
            while (true)
            {
                if (strcmp(baru->judul, bantu->judul) < 0)
                {
                    if (bantu->left == nullptr)
                    {
                        bantu->left = baru;
                        break;
                    }
                    bantu = bantu->left;
                }
                else
                {
                    if (bantu->right == nullptr)
                    {
                        bantu->right = baru;
                        break;
                    }
                    bantu = bantu->right;
                }
            }
        }
        cout << "Undo berhasil: buku dikembalikan.\n";
    }

    delete aksiUndo;
}

bool hapusNode(char judul[])
{
    buku *current = root;
    buku *parent = nullptr;

    while (current != nullptr && strcmp(judul, current->judul) != 0)
    {
        parent = current;
        if (strcmp(judul, current->judul) < 0)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr)
        return false;

    // 1. Tidak ada anak
    if (current->left == nullptr && current->right == nullptr)
    {
        if (current == root)
            root = nullptr;
        else if (parent->left == current)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete current;
    }

    // 2. Satu anak (kanan)
    else if (current->left == nullptr)
    {
        if (current == root)
            root = current->right;
        else if (parent->left == current)
            parent->left = current->right;
        else
            parent->right = current->right;
        delete current;
    }

    // 3. Satu anak (kiri)
    else if (current->right == nullptr)
    {
        if (current == root)
            root = current->left;
        else if (parent->left == current)
            parent->left = current->left;
        else
            parent->right = current->left;
        delete current;
    }

    // 4. Dua anak
    else
    {
        buku *successorParent = current;
        buku *successor = current->right;
        while (successor->left != nullptr)
        {
            successorParent = successor;
            successor = successor->left;
        }

        strcpy(current->judul, successor->judul);
        strcpy(current->pengarang, successor->pengarang);
        current->tahunTerbit = successor->tahunTerbit;

        if (successorParent == current)
            successorParent->right = successor->right;
        else
            successorParent->left = successor->right;

        delete successor;
    }

    return true;
}
