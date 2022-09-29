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
//no throw

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (BitLen >= 0) delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}
//ok

TBitField::~TBitField()
{
    delete[]pMem;
}
//ok

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return MemLen - (n >> 5) - 1; // n >> sizeof(int) + 1;
}
//ok

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int ind = n - (n >> 5 << 5);
    TELEM mask = 1 << ind;
    return mask;
}
//ok

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}
//ok

void TBitField::SetBit(const int n) // установить бит
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}
//ok

void TBitField::ClrBit(const int n) // очистить бит
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n));
}
//ok

int TBitField::GetBit(const int n) const // получить значение бита
{
        if (n < 0) throw "negative index";
        if (n >= BitLen) throw "too large index";
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n - (n >> 5 << 5));
}
//ok

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}
//ok

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) return 0;
  return 1;
}
//ok

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) return 1;
    return 0;
}
//ok

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField a(0);
    int i;
    if (BitLen >= bf.BitLen) {
        a = *this;
        for (i = 0; i < bf.MemLen; i++)
            a.pMem[a.MemLen - i - 1] = pMem[MemLen - i - 1] | bf.pMem[bf.MemLen - i - 1];
        for (; i < MemLen; i++)
            a.pMem[a.MemLen - i - 1] = pMem[MemLen - i - 1];
    }
    else {
        a = bf;
        for (i = 0; i < MemLen; i++)
            a.pMem[a.MemLen - i - 1] = pMem[MemLen - i - 1] | bf.pMem[bf.MemLen - i - 1];
        for (; i < MemLen; i++)
            a.pMem[a.MemLen - i - 1] = bf.pMem[bf.MemLen - i - 1];
    }
    return a;
}
//ok

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField a(0), b(0);
    if (BitLen >= bf.BitLen) {
        a = *this;
        for (int i = 0; i < bf.MemLen; i++)
            a.pMem[a.MemLen - i - 1] = pMem[MemLen - i - 1] & bf.pMem[bf.MemLen - i - 1];
    }
    else {
        a = bf;
        for (int i = 0; i < MemLen; i++)
            a.pMem[a.MemLen - i - 1] = pMem[MemLen - i - 1] & bf.pMem[bf.MemLen - i - 1];
    }
    return a;
}
//ok

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 1; i < MemLen; i++)
        pMem[i] = ~(pMem[i]);
    int n = 32 - BitLen + MemLen * 32;
    pMem[0] = ~(pMem[0] << n) >> n;
    return *this;
}
//ok

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    TELEM k;
    char f;
    char* s = "enter your BitField";
    cout << s << endl;;
    for (int i = 0; i < bf.MemLen; i++) {
        k = 0;
        for (int j = 0; j < 32; j++) {
            istr >> f;
            if (f == ' ') { j--; continue; }
            k = (k << 1) | (f - 48) & 1;
        }
        bf.pMem[i] = k;
    }
    return istr;
}
//ok

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    TELEM k, f;
    for (int i = 0; i < bf.MemLen; i++) {
        k = bf.pMem[i];
        f = 0;
        for (int j = 0; j < 32; j++) {
            f = (f << 1);
            f = f | (k & 1);
            k = k >> 1;
        }
        for (int j = 0; j < 32; j++) {
            ostr << (f & 1);
            f = f >> 1;
        }
        ostr << " ";
    }
    ostr << endl;
    return ostr;
}
//ok
