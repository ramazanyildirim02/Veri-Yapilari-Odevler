#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Musteri 
{
    int musteriNo;
    int islemSuresi;
    Musteri(int _x, int _y): musteriNo(_x),islemSuresi(_y){}
};

struct MusteriIslem
{
    int musteriNo;
    int islemSuresi;
    struct MusteriIslem* next; 
};
struct MusteriIslem* first = NULL;

struct MusteriIslem_Sirali 
{
    int musteriNo;
    int islemSuresi;
    struct MusteriIslem_Sirali* next_sirali; 
};
struct MusteriIslem_Sirali* first_sirali = NULL;

//1.adım: List ile stack oluşturma
void push(int _musteriNo) 
{
    struct MusteriIslem* musterii = new MusteriIslem;
    musterii -> musteriNo = _musteriNo;
    musterii -> next = first;
    first = musterii;
};

// 2.adım: MusteriIslem_Sirali ters çevirme(stack ile stack oluşturma)
void Musteri_StacktoStack() 
{
    struct MusteriIslem* musterii;

    if(first == NULL)
    {
        cout << "Yığında boş";
    }
    else 
    {
        musterii = first;
        while (musterii != NULL)
        {
           struct MusteriIslem_Sirali* musterii_Sirali = new MusteriIslem_Sirali;
           musterii_Sirali -> musteriNo = musterii -> musteriNo;
           musterii_Sirali -> islemSuresi = musterii -> islemSuresi;
           musterii_Sirali -> next_sirali = first_sirali;
           first_sirali = musterii_Sirali;
           musterii = musterii -> next;
        }
    }
}

void MusteriIslemListele()
{
    struct MusteriIslem* musterii;

    if(first == NULL)
    {
        cout << "Yığın boş";

    }
    else
    {
        musterii = first;
        cout <<"1.yığın"<< endl;
        while(musterii != NULL)
        {
            cout << musterii -> musteriNo << ".kişi " << endl;
            musterii = musterii ->next;
        }
    }
    cout << endl;
}

void MusteriIslemListeleSirali() 
{
    struct MusteriIslem_Sirali* musterii;

    if(first == NULL)
    {
        cout << "Yığın boş";
    }
    else
    {
        musterii = first_sirali;
        cout <<"2.yığın"<< endl;
        while(musterii != NULL)
        {
            cout << musterii -> musteriNo << ".kişi " << endl;
            musterii = musterii ->next_sirali;
        }
    }
    cout << endl;
}

//3. Adım: Stack ile kuyruk oluşturma
void CreateQueue()
{
    queue<Musteri> musteriler;
    struct MusteriIslem_Sirali* musterii;

    if(first_sirali == NULL)
    {
        cout << "Yığın boş";
    }
    else
    {
        musterii = first_sirali;
        while(musterii != NULL)
        {
            musteriler.push(Musteri(musterii -> musteriNo,(30 + (rand() % 270))));
            musterii = musterii -> next_sirali;
        }

        int toplamSure = 0, genelToplam = 0, kisi = 0;
        while(!musteriler.empty())
        {
            toplamSure += musteriler.front().islemSuresi;
            cout << endl;
            cout << musteriler.front().musteriNo << " nolu müşterinin işlemi " << musteriler.front().islemSuresi <<
            " saniye, toplam işlem süresi ise "<< toplamSure << " saniyedir." << endl;
            kisi ++;
            musteriler.pop(); 
            genelToplam += toplamSure;
        }
        cout << "\nOrtalama işlem süresi : " << genelToplam / kisi << " saniyedir.";
        cout << "\n" << endl;
    }
}

int main(){
    MusteriIslem* musterii = new MusteriIslem;

    int kisi;
    cout << "Kuyrukta kaç kişi var? : ";
    cin >> kisi;
    for(int i =1; i <=kisi ; i++)
    {
        push(i);    
    }

    Musteri_StacktoStack();
    MusteriIslemListele();
    MusteriIslemListeleSirali();
    CreateQueue();

    return 0;
}
