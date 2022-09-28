// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    int k = sizeof(int);
    //if (len < 0) throw "negative len";
    BitLen = len;
    MemLen = (len + k * 8 - 1) >> k + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return MemLen - (n >> 5) - 1; // n >> sizeof(int) + 1;
    //return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int ind = n - (n >> 5 << 5);
    TELEM mask = 1 << ind;
    return mask;
    //return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); //ok
}

void TBitField::ClrBit(const int n) // очистить бит
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n)); //ok
}

int TBitField::GetBit(const int n) const // получить значение бита
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n - (n >> 5 << 5));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
