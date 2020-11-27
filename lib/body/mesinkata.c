/* File: mesinkata.c */
/* Realisasi Mesin Kata: Model Akuisisi Versi I */
/* Josep Marcello
 * 13519164
 * 30 September 2020 */

#include "../header/mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank() {
    while (CC == BLANK || CC == CR || CC == LF) ADV();
}

void STARTKATA() {
    START(stdin);
    IgnoreBlank();

    if (CC == MARK) {
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA() {
    if (CC == MARK) {
        EndKata = true;
    } else {
        SalinKata();
    }
}

void SalinKata() {
    int i;

    i = 0;

    while(i < NMax && CC != MARK && CC != CR && CC != LF) {
        CKata.TabKata[i++] = CC;
        ADV();
    }

    CKata.TabKata[i] = '\0';
    CKata.Length = i;
}

void SalinKataKe(Kata *K1){
	SalinKataDariKe(CKata, K1);
}

void SalinKataDariKe(Kata K1, Kata *K2){
	int i;

	for(i = 0; i < K1.Length; i++){
		K2->TabKata[i] = K1.TabKata[i];
	}
	K2->Length = K1.Length;
}

boolean IsKataSama(Kata K1, Kata K2){
	int i;
	boolean sama;

	i = 0;
	sama = K1.Length == K2.Length;
	while(sama && i < K1.Length){
		sama = K1.TabKata[i] == K2.TabKata[i];
		i++;
	}
	return sama;
}

void TulisKataKe(Kata K, FILE* f){
	int i;
	for(i = 0; i < K.Length; i++){
		printf("%c", K.TabKata[i]);
	}
}
