/*
*   @file       Responsi2_M0521009_Alfiki Diastama Afan Firdaus.c
*           
*   @title      PROGRAM SIMULASI PLAYLIST (VERSI LINUX)
*
*   @brief      Program ini dapat menyimulasikan playlist music player.
*               Program ini dapat mengelola playlist, dengan rincian sebagai berikut:
*               1. Menambah musik           4. Mengedit musik.             7. Mengimpor playlist dari file .dat     
*               2. Melihat playlist         5. Mencari data musik          8. Panduan program
*               3. Memutar musik teratas    6. Mengekspor playlist ke .dat
*               Program telah dicoba untuk dirun dengan Visual Studio Code dan berhasil tanpa error.
*               File .exe disertakan, dapat dijalankan tanpa membuka VSCode atau CodeBlock.
*           
*   @authors    Alfiki Diastama Afan Firdaus (M0521009)
*               
*
*   @date       29-11-2021
*/

//deklarasi header dan define
#include <stdio.h> //Untuk fungsi dasar
#include <stdlib.h> //Untuk fungsi malloc dan lain-lain
#include <string.h> //Untuk fungsi strcpy
#include <unistd.h> //Untuk fungsi Sleep()
#define namaFile "Musik.dat"
#define formatPenulisan "%d\t%50s\t%30s\t%20s\t%10s\n"

//deklarasi struktur data
typedef struct Musik {
    int urutan;
    char *Judul;
    char *Artis;
    char *Aliran;
    char *Tahun;
} Musik;

//deklarasi nama alias
typedef struct ElemenMusik {
    Musik *Musik;
    struct ElemenMusik *next;
} ElemenMusik;

//agar starting pointnya bisa dipindah
ElemenMusik *MusikPtr = NULL;

//prototipe fungsi yang menggunakan struktur Musik
Musik *tambahMusik(int, char *,char *,char *,char *);
Musik *cariMusik(ElemenMusik *, int);

//prototipe fungsi yang menggunakan struktur ElemenMusik
ElemenMusik *tambahElemenMusik(Musik *);
ElemenMusik *putarMusik(ElemenMusik **, int);

//prototipe fungsi utama program
void tambahMusikKePlaylist(ElemenMusik **, Musik *);
void tampilkanDetailMusik(Musik *);
void editMusik(Musik *, int, char *, char *,char *,char *);
void tampilkanSemua(ElemenMusik *);
void eksporPlaylist(ElemenMusik *musikPtr);
void imporPlaylist(ElemenMusik **musikPtr);

//prototipe fungsi panduan program
void panduanMenu();
void panduanTambahLagu();
void panduanTampilkanPlaylist();
void panduanPutarMusik();
void panduanEditMusik();
void panduanCariMusik();
void panduanEksporPlaylist();
void panduanImporPlaylist();
void panduanKeluar();

//prototipe fungsi yang digunakan dalam perpindahan menu/fungsi saat menjalankan program
int Jeda();
int Mengulangi();
int Spasi();

//fungsi untuk input pengguna saat menambahkan musik sekaligus mengalokasikan memorinya
char *alokasiMemori() {
    char *String;
    String = (char *)malloc(sizeof(char) * 100);
    scanf("%s", String);
    return String;
}

//agar urutan lagu bisa bertambah saat musik ditambahkan dan berkurang saat musik diputar
int urutanStrg = 0;
int *urutanPtr = &urutanStrg; //urutanPtr untuk mengakses urutan dan urutanStrg (storage) untuk tempat memori

//fungsi untuk penjelasan program
void panduanProgram() {
    printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PANDUAN PROGRAM >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("\nProgram ini adalah program untuk membuat, memutar, dan mengelola playlist, serta mengekspor dan mengimpornya dari file .dat.\n\n");
    printf("DISCLAIMER (PENAFIAN): JANGAN JALANKAN PROGRAM INI DENGAN MELAKUKAN BUILD AND RUN (F5) DI VSCODE!\nProgram tidak akan berjalan semestinya.\nSebagai gantinya buka di CodeBlock atau dirun saja (tombol segitiga di pojok kanan atas) di VSCode\n");
    printf("Solusi lain adalah dengan membuka file .exe hasil build code ini dan double click di Explorer atau dengan PowerShell.\n\n");
    printf("Program ini hanya bisa berjalan di Linux. Untuk versi Windows, gunakan program versi Windows yang telah disediakan.\n\n");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi panduan program
void panduanMenu() {
    char opsi;

    printf("\n<<<<<<<<<<<<<<<< PANDUAN MENU >>>>>>>>>>>>>>>>");
    printf("\n\nSilakan pilih menu panduan:\n");
    printf("1. CARA MENAMBAH MUSIK \n");
    printf("2. CARA MENAMPILKAN PLAYLIST \n");
    printf("3. CARA MEMUTAR MUSIK DI PLAYLIST\n");
    printf("4. CARA MENGEDIT MUSIK \n");
    printf("5. CARA MENCARI MUSIK \n");
    printf("6. CARA MENGEKSPOR DATA KE FILE \n");
    printf("7. CARA MENGIMPOR DATA DARI FILE \n");
    printf("8. CARA KELUAR DARI PROGRAM\n");
    printf("-----------------------------------------------\n");
    printf("9. MASUK KE PROGRAM\n");

    printf("Untuk membaca panduan setiap menu, ketik angka 1-8 sesuai menu di atas, lalu tekan enter.\n\n");
    printf("UNTUK MASUK KE MENU PROGRAM, KETIK 9 LALU ENTER.\n");
    scanf("%c", &opsi);

    //pemilihan menu panduan
    switch (opsi) {
        case '1':
            panduanTambahLagu();
            break;
            
        case '2':
            panduanTampilkanPlaylist();
            break;

        case '3':
            panduanPutarMusik();
            break;

        case '4':
            panduanEditMusik();
            break;

        case '5':
            panduanCariMusik();
            break;

        case '6':
            panduanEksporPlaylist();
            break;

        case '7':
            panduanImporPlaylist();
            break;

        case '8':
            panduanKeluar();
            break;

        case '9':
            puts("\nKamu akan masuk ke menu utama program.");
            puts("Selamat bersenang-senang!");
            sleep(1);//jeda 1 detik
            break;

        //jika user menginputkan nilai selain yang ditentukan
        default:
            printf("\nMasukan yang kamu berikan tidak valid!\n");
            printf(".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
            Spasi();
            Mengulangi();    
            panduanMenu();
            break;
    }
}

//fungsi untuk panduan menambah musik
void panduanTambahLagu() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENAMBAH MUSIK PADA PLAYLIST\n");
    puts("Jika kamu ingin menambah musik, ketik angka 1 di menu utama lalu enter, maka akan muncul tampilan seperti ini\n");
    puts("Urutan   :\nJudul    :\nArtis    :\nAliran   :\nTahun    :\n");
    puts("Kamu tinggal mengetikkan karakter di samping kolom yang diberikan, lalu enter. Ingat, jangan menulis lebih dari satu kata karena program ini tidak mendukung input lebih dari 1 kata.\n");
    puts("Setelah selesai menginput, kamu bisa tekan tombol enter.\n");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan menampilkan playlist
void panduanTampilkanPlaylist() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENAMPILKAN ISI PLAYLIST\n");
    puts("Jika kamu ingin melihat playlist dari musik yang sudah ditambahkan, ketik angka 2 di menu utama lalu enter.\n");
    puts("Akan muncul tampilan seperti berikut ini.\n");
    printf("Urutan  : \nJudul   : \nArtis   : \nAliran  : \nTahun   : \n");
    printf("===========================\n");
    puts("Musik akan ditampilkan urut dari atas ke bawah\n");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan memutar musik
void panduanPutarMusik() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MEMUTAR MUSIK\n");
    puts("Untuk memutar musik, ketik angka 3 lalu enter saat berada di menu utama. Musik yang diputar adalah musik yang berada di urutan pertama.");
    puts("Maka akan muncul tampilan seperti berikut ini:");
    printf("\nMusik berikut sedang diputar...\n");
    printf("Urutan  : 1\nJudul   : \nArtis   : \nAliran  : \nTahun   :");
    printf("\nHarap tunggu sampai musik selesai diputar. Selamat mendengarkan!\n\n");
    puts("Sebagai simulasi musik diputar, harap menunggu selama beberapa detik sebelum notifikasi berikutnya muncul.");
    puts("Setelah musik selesai diputar, maka urutan musik di bawahnya akan naik 1 tingkat.\n");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan mengedit musik
void panduanEditMusik() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENGEDIT MUSIK\n");
    puts("Untuk mengedit musik, ketik angka 4 lalu enter saat berada di menu utama.");
    puts("Maka kamu akan diminta memasukkan nomor urutan musik yang ingin diedit datanya.");
    puts("Jika nomor yang kamu masukkan ada di urutan playlist, maka akan muncul informasi musik yang kamu pilih dan di bawahnya ada tampilan seperti ini.");
    puts("Urutan   :\nJudul    :\nArtis    :\nAliran   :\nTahun    :\n");
    puts("Kamu tinggal mengisi data baru di bagian yang disediakan, setelah itu mengeklik enter.");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan mencari musik
void panduanCariMusik() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENCARI MUSIK\n");
    puts("Untuk mencari musik, ketik angka 5 lalu enter saat berada di menu utama.");
    puts("Maka kamu akan diminta memasukkan nomor urutan musik yang ingin dilihat datanya.");
    puts("Jika nomor yang kamu masukkan ada di urutan playlist, maka akan muncul informasi musik yang kamu pilih.");
    puts("setelah itu klik enter untuk kembali ke menu utama.");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan menyimpan playlist ke file .dat
void panduanEksporPlaylist() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENGEKSPOR PLAYLIST\n");
    puts("Untuk mengekspor playlist ke file .dat, ketik angka 6 saat berada di menu utama.");
    puts("Data playlist akan otomatis tersimpan di folder yang sama dengan program ini dengan nama Musik.dat");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan mengimpor playlist dari file .dat
void panduanImporPlaylist() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK MENGEKSPOR PLAYLIST\n");
    puts("Untuk mengimpor playlist ke file .dat, ketik angka 7 saat berada di menu utama.");
    puts("Sebelum mengimpor playlist, pastikan file Musik.dat sudah ada di folder yang sama dengan program.");
    puts("Data dari file akan otomatis tersimpan di dalam playlist, sehingga kamu bisa mengecek dan memutar musiknya");
    Spasi();
    Jeda();
    panduanMenu();
}

//fungsi untuk panduan keluar dari program
void panduanKeluar() {
    puts("\n_________________________________________________________________________________________________________________________________________");
    puts("\nPANDUAN UNTUK KELUAR DARI PROGRAM\n");
    puts("Untuk keluar dari program, ketik angka 9 saat berada di menu utama.");
    puts("Saat keluar, file playlist akan otomatis tersimpan di file Musik .dat di folder yang sama.");
    puts("Jika muncul tulisan:\nTerima kasih karena telah menggunakan ADAF Playlist!\n");
    puts("Maka kamu telah berhasil keluar dari program");
    Spasi();
    Jeda();
    panduanMenu();
}

//menu utama program
void menuUtama(ElemenMusik **L) {
    ElemenMusik *ptr;
    int i, nvId, c;
    char *JudulPtr;
    char *ArtisPtr;
    char *AliranPtr;
    char *TahunPtr;
    char pilihan, konfirmasi;

    printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< **PLAYLIST ADAF** >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Apakah kamu ingin membaca panduan sebelum memulai program?\n");
    printf("Ketikkan 'y' jika ingin membaca panduan. Ketikkan 't' jika ingin langsung menjalankan program.\n");
    scanf("%c", &konfirmasi);

    //Jika user tidak menginputkan t, maka akan masuk ke penjelasan program
    if(konfirmasi != 't') {
        panduanProgram();
    }
    
    do { //loop sampai user menginputkan '9' untuk keluar dari program
        Spasi();
        printf("\n\n<<<<<<<<<<<<<<< MENU UTAMA >>>>>>>>>>>>>>>\n\n");
        printf("1 -> TAMBAH MUSIK \n");
        printf("2 -> TAMPILKAN PLAYLIST \n");
        printf("3 -> PUTAR LAGU DI PLAYLIST\n");
        printf("4 -> EDIT MUSIK \n");
        printf("5 -> CARI MUSIK \n");
        printf("6 -> EKSPOR DATA KE FILE \n");
        printf("7 -> IMPOR DATA DARI FILE \n");
        printf("8 -> BACA PANDUAN\n");
        printf("9 -> KELUAR \n");
        printf("__________________________________________\n\n");
        printf("Hai! Ketikkan pilihan kamu: ");
        scanf("%c", &pilihan);

        //program handling
        switch (pilihan) {
            case '1':
                system("cls"); //clear screen
                char *Judul;
                char *Artis;
                char *Aliran;
                char *Tahun;
                //enqueue
                printf("\n------------- TAMBAH MUSIK -------------\n");
                //untuk menaikkan urutan musik
                *urutanPtr += 1;
                printf("Urutan  : %d\n", *urutanPtr);
                //menambahkan judul musik
                printf("Judul   : ");
                Judul=alokasiMemori();
                //menambahkan artis
                printf("Artis   : ");
                Artis=alokasiMemori();
                //menambahkan aliran (genre) musik
                printf("Aliran  : ");
                Aliran=alokasiMemori();
                //menambahkan tahun
                printf("Tahun   : ");
                Tahun=alokasiMemori();
                //memasukan musik ke playlist (pemanggilan fungsi)
                tambahMusikKePlaylist(L, tambahMusik(*urutanPtr, Judul, Artis, Aliran, Tahun));
                
                printf("\nMusik berhasil dimasukkan ke dalam playlist.");
                //jeda 7,5 detik sebelum lanjut ke menu utama
                sleep(1);
                break;
            
            case '2':
                printf("\n-------------- PLAYLIST --------------\n\n");
                tampilkanSemua(*L); //menampilkan playlist
                Jeda();
                break;

            case '3':
                system ("cls");
                Musik *p;
                if ((p = cariMusik(*L, 1)) != NULL) { //memanggil fungsi cariMusik untuk memastikan ada musik di urutan 1
                    putarMusik(L, 1); //memutar musik (dequeue)
                    Jeda();
                }
                else { //jika musik tidak ada, maka dimunculkan tampilan ini
                    printf("\nPlaylist belum ada!");
                    printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
                    Jeda();
                }
                break;

            case '4':
                printf("\n----------------- EDIT -----------------\n");
                printf("Masukkan urutan musik yang akan diedit: ");
                scanf("%d", &c); //input user untuk menentukan musik di urutan berapa yang akan diedit

                if ((p = cariMusik(*L, c)) != NULL) { //memanggil fungsi cariMusik untuk memastikan ada musik yang dicari
                    printf("\nData lama:\n"); //menampilkan data musik yang belum diubah
                    printf("Urutan  : %d\n", p->urutan);
                    printf("Judul   : %s\n", p->Judul);
                    printf("Artis   : %s\n", p->Artis);
                    printf("Aliran  : %s\n", p->Aliran);
                    printf("Tahun   : %s\n", p->Tahun);
                    
                    printf("\nMasukkan data baru:\n");
                    //memasukkan data baru untuk mengubah data musik yang lama
                    printf("Judul   : ");
                    JudulPtr = alokasiMemori();

                    printf("Artis   : ");
                    ArtisPtr = alokasiMemori();

                    printf("Aliran  : ");
                    AliranPtr = alokasiMemori();

                    printf("Tahun   : ");
                    TahunPtr = alokasiMemori();

                    ptr = *L; //L = ElemenMusik *daftarMusik
                    while (ptr != NULL) {
                        if (ptr->Musik->urutan == c) {
                            break;
                        }
                        ptr = ptr->next;
                    }
                    editMusik(ptr->Musik, c, JudulPtr, ArtisPtr, AliranPtr, TahunPtr); //memasukkan data baru ke playlist
                    Jeda();
                }
                else { //Jika musik dengan urutan yang dicari tidak ada
                    printf("\nMusik tidak ditemukan!");
                    printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
                    Jeda();
                }
                break;

            case '5':
                printf("\n----------------- CARI -----------------\n");
                printf("Masukkan urutan musik yang akan dicari : ");
                scanf("%d", &c); //user menginputkan urutan musik yang akan dicari

                if ((p = cariMusik(*L, c)) != NULL) { //memastikan musik yang dicari ada
                    printf("Musik ditemukan!\n"); //menampilkan data musik dengan urutan yang diinputkan
                    printf("Urutan : %d\n", p->urutan);
                    printf("Judul  : %s\n", p->Judul);
                    printf("Artis  : %s\n", p->Artis);
                    printf("Aliran : %s\n", p->Aliran);
                    printf("Tahun  : %s\n", p->Tahun);
                    Jeda();
                }
                else { //Jika musik yang dicari tidak ada
                    printf("\nMusik tidak ditemukan!");
                    printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
                    Jeda();
                }
                break;
            
            case '6':
                eksporPlaylist(*L); //mengekspor playlist
                Jeda();
                break;

            case '7':
                imporPlaylist(L); //mengimpor playlist
                Jeda();
                break;

            case '8':
                panduanProgram(); //penjelasan program dilanjutkan panduan menu program
                break;

            case '9':
                printf("\n"); //Untuk keluar dari program
                break;

            default: //Jika user memasukkan karakter yang tidak sesuai
                printf("\nMasukan yang kamu berikan tidak valid!");
                printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
                sleep(1);
                break;
        }
    }
    while (pilihan != '9'); //sambungan do-while

    eksporPlaylist(*L); //setiap keluar program, playlist otomatis tersimpan, bahkan jika user lupa mengekspornya
    printf("Terima kasih karena telah menggunakan ADAF Playlist!\n\n");
    sleep(2); //agar jika dibuka langsung dari file .exe, tulisan terima kasih dapat dibaca
}

Musik *tambahMusik(int urutan, char *Judul, char *Artis, char *Aliran, char *Tahun) {
    Musik *buatMusik;
    buatMusik = (Musik *)malloc(sizeof(Musik)); //alokasi memori

    buatMusik->urutan = *urutanPtr; //memasukkan data ke variabel
    buatMusik->Judul  = Judul;
    buatMusik->Artis  = Artis;
    buatMusik->Aliran = Aliran;
    buatMusik->Tahun  = Tahun;

    return buatMusik;
}

//membuat wadah untuk musik yang ditambahkan
ElemenMusik *tambahElemenMusik(Musik *Musik) {
    ElemenMusik *elemenBaru;
    elemenBaru = (ElemenMusik *)malloc(sizeof(ElemenMusik));
    elemenBaru->Musik = Musik;
    elemenBaru->next = NULL;
    return elemenBaru;
}

//menambahkan musik yang ditambahkan ke playlist
void tambahMusikKePlaylist(ElemenMusik **daftarMusik, Musik *Musik) {
    ElemenMusik *elemenBaru;

    //elemen musik dari fungsi di atas
    elemenBaru = tambahElemenMusik(Musik);

    //jika kosong
    if (*daftarMusik == NULL) {
        *daftarMusik = elemenBaru;
        return;
    }
    //jika tidak kosong
    ElemenMusik *last;
    last = *daftarMusik;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = elemenBaru;
}

//tampilan playlist
void tampilkanDetailMusik(Musik *Musik) {
    printf("Urutan  : %d \n", Musik->urutan);
    printf("Judul   : %s \n", Musik->Judul);
    printf("Artis   : %s \n", Musik->Artis);
    printf("Aliran  : %s \n", Musik->Aliran);
    printf("Tahun   : %s \n", Musik->Tahun);
    printf("===========================\n");
}

//untuk dequeue musik
ElemenMusik *putarMusik(ElemenMusik **daftarMusik, int urutan) {
    ElemenMusik *ptr;
    ptr = *daftarMusik;

    if ((*daftarMusik)->Musik->urutan == urutan) {
        MusikPtr = MusikPtr->next; //Memindahkan starting point langsung dari pointer asli
        printf("\n\n------------- PUTAR MUSIK --------------\n\nMusik berikut sedang diputar...\n");
        tampilkanDetailMusik(ptr->Musik); //Untuk memperlihatkan musik yang teratas (sedang didequeue)
        printf("\nHarap tunggu sampai musik selesai diputar. Selamat mendengarkan!\n");
        sleep(2);
        printf("Musik selesai diputar!\n");
        free(ptr); //membersihkan memori
        ptr = MusikPtr;
        *urutanPtr -= 1; //Untuk mengurangi urutan
    }
    else {
        ElemenMusik *tmp;
        while (ptr != NULL) {
            tmp = ptr;
            ptr = ptr->next;
            if (ptr->Musik->urutan == urutan) {
                tmp->next = ptr->next;
                free(ptr);
                ptr = tmp->next;
                *urutanPtr -= 1;
                //Untuk mengurangi urutan
                break;
            }
        }
    }
    //Untuk mengurangi urutan musik-musik setelahnya
    for(ptr = ptr; ptr != NULL; ptr = ptr->next) {
        ptr->Musik->urutan--;
    }
}

//Untuk mencari musik
Musik *cariMusik(ElemenMusik *daftarMusik, int urutan) {
    ElemenMusik *ptr;
    ptr = daftarMusik;
    while (ptr != NULL) {
        if (ptr->Musik->urutan == urutan) {
            return ptr->Musik;
        }
        ptr = ptr->next;
    }
    return NULL;
}

//menyalin teks yang telah dimasukkan ke variabel di structure
void editMusik(Musik *Musik, int nvId, char *JudulPtr, char *ArtisPtr, char *AliranPtr, char *TahunPtr) {
    strcpy(Musik->Judul, JudulPtr);
    strcpy(Musik->Artis, ArtisPtr);
    strcpy(Musik->Aliran, AliranPtr);
    strcpy(Musik->Tahun, TahunPtr);
    printf("\nData musik berhasil diedit!\n");
}

//untuk menampilkan semua musik di playlist
void tampilkanSemua(ElemenMusik *daftarMusik) {
    ElemenMusik *ptr;
    ptr = daftarMusik;

    if (ptr == NULL) { //Jika playlist kosong
        printf("\nPlaylist masih kosong!\n");
        printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
    }
    //menampilkan semua musik
    for (ptr = daftarMusik; ptr != NULL; ptr = ptr->next) {
        printf("===========================\n");
        tampilkanDetailMusik(ptr->Musik);
    }
}

//fungsi main
int main(int argc, char const *argv[]) {
    menuUtama(&MusikPtr);
    return 0;
}

//fungsi untuk mengekspor playlist
void eksporPlaylist(ElemenMusik *MusikPtr) {
    FILE *file = fopen(namaFile, "wb"); //namaFile = Musik.dat, wb berarti write in binary mode

    if (!file) { //Jika tidak bisa diekspor
        printf("\nFile tidak dapat diekspor!");
        printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
        return;
    }
    while (MusikPtr) { //mencetak ke file .dat
        fprintf(file, formatPenulisan, (MusikPtr->Musik->urutan), (MusikPtr->Musik->Judul), (MusikPtr->Musik->Artis), (MusikPtr->Musik->Aliran), (MusikPtr->Musik->Tahun));
        MusikPtr = MusikPtr->next;
    }
    fclose(file); //informasi penyelesaian ekspor file playlist
    printf("\nPlaylist berhasil diekspor ke file .dat!\n");
}

//fungsi untuk mengimpor playlist
void imporPlaylist(ElemenMusik **MusikPtr) {
    FILE *file = fopen(namaFile, "rb"); //rb berarti read in binary mode
    if (!file) { //jika file Musik.dat tidak ada
        printf("\nFile tidak dapat diimpor!");
        printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
        return;
    }
    //deklarasi
    ElemenMusik *row = NULL;
    *MusikPtr = NULL;
    ElemenMusik *tmp = NULL;

    int urutan;
    char *Judul=(char*) malloc(100*sizeof(char));
    char *Artis=(char*) malloc(100*sizeof(char));
    char *Aliran=(char*) malloc(100*sizeof(char));
    char *Tahun=(char*) malloc(100*sizeof(char));

    while (fscanf(file, formatPenulisan, &urutanStrg, Judul, Artis, Aliran, Tahun) != EOF) { //scan data
            row = tambahElemenMusik(tambahMusik(urutanStrg, Judul, Artis, Aliran, Tahun)); //Memasukkan data ke variabel

        //Jika playlist masih kosong
        if (*MusikPtr == NULL) {
            //Musik urutan teratas
            *MusikPtr = row;
            tmp = *MusikPtr;
        }
        else {
            tmp->next = row;
            tmp = tmp->next;
        }

        //Mengalokasikan memori
        Judul=(char*) malloc(100*sizeof(char));
        Artis=(char*) malloc(100*sizeof(char));
        Aliran=(char*) malloc(100*sizeof(char));
        Tahun=(char*) malloc(100*sizeof(char));
    }
    printf("\nPlaylist berhasil diimpor dari file .dat!\n");
}

//Untuk membuat program terjeda hingga user mengeklik enter
int Jeda() {
    printf("\nTekan tombol enter untuk melanjutkan!");
    while (getchar() != '\n');
    return 0;
}

//Sejenis fungsi jeda, hanya kalimat berbeda
int Mengulangi() {
    printf("\nTekan tombol enter untuk mengulangi!");
    while (getchar() != '\n');
    return 0;
}

//Fungsi jeda tanpa tulisan
int Spasi() {
    while (getchar() != '\n');
    return 0;
}