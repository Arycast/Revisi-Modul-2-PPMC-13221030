/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 2 Strings and External Files
 *   Hari dan Tanggal    : Jum'at, 17 Februari 2023
 *   Nama (NIM)          : Fauzan Ibrahim (13221030)
 *   Nama File           : main.c
 *   Deskripsi           : Program mencetak substring terpanjang pada setiap baris dalam file .txt eksternal. Substring terdiri atas 3 tipe, yaitu lowercase, uppercase, dan numerik
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char category (char c){
    // Fungsi untuk menentukan aktegori character
    if (c >= 'a' && c <= 'z') return '1';       // Lowercase
    else if (c >= 'A' && c <= 'Z') return '2';  // Uppercase
    else if (c >= '0' && c <= '9') return '3';  // Numbers
    else return '0';
}

int main(){
    char temp[200], actual[200];
    short sub_len = 0, sub_templen = 0;
    short len_length = 0, true_length;

    char filename[15];
    scanf("%s", filename);

    FILE *fs = fopen(filename, "r");

    if (fs != NULL){
        short length[3];
        char readChar, prevChar;
        while((readChar = fgetc(fs)) != '\n'){
            length[len_length] = (short)readChar - 48; // Dikurang 47 untuk mendapatkan representasi integer yang sesuai
            len_length++;
        }
        // Menghitung jumlah string yang perlu dibaca
        if (len_length == 3) true_length = length[0] * 100 + length[1] * 10 + length[2];
        else if(len_length == 2) true_length = length[0] * 10 + length[1];
        else true_length = length[0];

        short cnt = 0;
        // Isi array dengan nilai kosong
        memset(temp, '\0', 200);
        memset(actual, '\0', 200);
        
        do{
            readChar = fgetc(fs);
            // Cek perubahan kategori
            if (category(readChar) != category(prevChar) && category(prevChar) != '0'){
                temp[sub_templen + 1] = '\0';
                if (sub_templen > sub_len){
                    strcpy(actual, temp);
                    sub_len = sub_templen;
                }

                memset(temp, '\0', 200);
                sub_templen = 0;
            }
            // Tambah karakter pada array temp
            if (readChar != '\n'){
                temp[sub_templen] = readChar;
                sub_templen++;
            }
            // Output substring terpanjang
            if (readChar == '\n' || readChar == EOF){
                printf("%s\n", actual);
                memset(temp, '\0', 200);
                sub_len = 0;
                cnt++;
            }

            prevChar = readChar; // Menyimpan karakter yang dibaca sebelumnya
        }while (cnt < true_length && prevChar != EOF);
        fclose(fs);
    }
    else{
        printf("Error : file tidak ada");
    }
    
    return 0;
}