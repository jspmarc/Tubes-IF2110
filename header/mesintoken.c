/* File: mesintoken.c */
/* Definisi Mesin Token: Model Akuisisi Versi I */

#include "mesintoken.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndToken;
Token CToken;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    /*puts("IGNORE");*/
    while (CC == BLANK)
    {
        ADV();
    }
}

void STARTTOKEN()
/* I.S. : CC sembarang
   F.S. : EndToken = true, dan CC = MARK;
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */
{
    /*puts("START");*/
    START();
    IgnoreBlank();
    if (CC == MARK)
    {
        EndToken = true;
    }
    else
    {
        EndToken = false;
        SalinToken();
    }
}

void ADVTOKEN()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    /*puts("ADV");*/
    IgnoreBlank();
    if (CC == MARK)
    {
        EndToken = true;
    }
    else
    {
        SalinToken();
    }
}

void SalinToken()
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i = 0;

    CToken.val = 0;
    while (i < NMax && CC != BLANK && CC != MARK)
    {
        if (CC == '+' || CC == '-'
            || CC == '*' || CC == '/'
            || CC == '^')
        {
            CToken.tkn = CC;
            CToken.val = -1;
        }
        else if ('0' <= CC && CC <= '9')
        {
            CToken.val *= 10;
            CToken.val += (CC - '0');
            CToken.tkn = 'b';
        }
        ADV();
        i++;
    }
    /*printf("CToken.val = %d\n", CToken.val);*/
    /*printf("CToken.tkn = %d\n", CToken.tkn);*/
}

/*
int main()
{
    STARTTOKEN();
    while(!EndToken)
    {
        printf("<'%c',%d>\n", CToken.tkn, CToken.val);
        ADVTOKEN();
    }
}
*/


void bruh()
{
    /*puts("SALIN");*/
    for (int i = 0; i < NMax && CC != BLANK && CC != MARK; ++i)
    {
        if (CC == '+' || CC == '-' || CC == '*'
            || CC == '/' || CC == '^')
        {
            /*puts("SIMB");*/
            CToken.tkn = CC;
            CToken.val = -1;
            /*printf("<'%c', %d>\n", CToken.tkn, CToken.val);*/
        }
        else if (48 <= CC && CC <= 58)
        {
            /*puts("NUM");*/
            int nums[NMax],
                j = 0,
                val = 0;

            while (CC != MARK && CC != BLANK)
            {
                int CN = CC-48;
                nums[j++] = CN;
                ADV();
                if (CC == MARK)
                {
                    EndToken = true;
                }
            }

            for (int k = 0; k < j; ++k)
            {
                /*printf("nums[%d]: %d\n", k, nums[k]);*/
                val *= k >= j-1 ? 1 : 10;
                if (nums[k] != 0)
                {
                    val += nums[k] * (k >= j-1 ? 1 : 10);
                }
            }
            CToken.val = val;
            CToken.tkn = 'b';
            printf("<'%c', %d>\n", CToken.tkn, CToken.val);
        }
        ADV();
    }
}
