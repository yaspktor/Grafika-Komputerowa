// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include<windows.h>
// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <QMouseEvent>
#include <QPainter>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>
#include <QThread>
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");
    setMouseTracking(true);
    //Zmieniamy rozmiar okna
    resize(800, 700);


    // Ustawiamy wymiary obrazka i wspolrzedne jego 
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;

    startLineX = 0;
    startLineY = 0;
    endLineX = 0;
    endLineY = 0;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer, wys, QImage::Format_RGB32);
    //pobranie obrazka z folderu
    temp = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/o_morfologiczne/test2.jpg"));
    //scale image to 600x600
    //*temp = temp->scaled(szer, wys, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie", this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupa->setGeometry(QRect(poczX + szer + poczX, poczY, 800 - szer - 2 * poczX, poczY + 200));

    // Tworzymy nowy layout pionowy
    QVBoxLayout* boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski 

    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
    dylatacjaButton = new QPushButton("Dylatacja");
    erozjaButton = new QPushButton("Erozja");
    domkniecieButton = new QPushButton("Domkniecie");
    otwarcieButton = new QPushButton("Otwarcie");

    // Dodajemy przyciski do layoutu

    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(dylatacjaButton);
    boxLayout->addWidget(erozjaButton);
    boxLayout->addWidget(domkniecieButton);
    boxLayout->addWidget(otwarcieButton);
    boxLayout->addWidget(exitButton);


    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje 
    connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton, SIGNAL(clicked()), this, SLOT(slot_czysc()));
    connect(dylatacjaButton, SIGNAL(clicked()), this, SLOT(slot_dylatacja()));
    connect(erozjaButton, SIGNAL(clicked()), this, SLOT(slot_erozja()));
    connect(domkniecieButton, SIGNAL(clicked()), this, SLOT(slot_domkniecie()));
    connect(otwarcieButton, SIGNAL(clicked()), this, SLOT(slot_otwarcie()));

    slot_czysc();
    kopiujDo(*temp, *img);
    //na czarno bialo
   // toBlackAndWhite(*img);
    //toBlackAndWhite(*temp);
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}

//slot start - rysuje temp obrazek na ekranie

void MyWindow::slot_dylatacja() {
    //kopiuje obrazek do img
    
    //dylatacja
    DylatacjaErozja(*img, 255);
    //kopiowanie do img
    kopiujDo(*temp, *img);
    update();
}

//slot erozja

void MyWindow::slot_erozja() {
	//kopiuje obrazek do img
	//kopiujDo(*temp, *img);
    //erozja - na img sprawdza kolory pikseli i modyfikuje temp
	DylatacjaErozja(*img, 0);
    //kopiowanie do img, ktory jest wyswietlany, temp jest modyfikowany
	kopiujDo(*temp, *img);

	update();
}

//slot domkniecie

void MyWindow::slot_domkniecie() {

    domkniecie();
}

//slot otwarcie

void MyWindow::slot_otwarcie() {
	otwarcie();
}

// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX, poczY, *img);
}



void MyWindow::wstawPiksel(int x, int y, QImage& sourceImage, int color = 255) {
    unsigned char* ptr;
    ptr = sourceImage.bits();
    ptr[szer * 4 * y + 4 * x] = color;
    ptr[szer * 4 * y + 4 * x + 1] = color;
    ptr[szer * 4 * y + 4 * x + 2] = color;
    //update();
}

//funkcja zamienia obraz temp na czarno bialy 



//funkcja odpowiedzialna za dylatacje/erozje if mode == 255 to dylatacja else erozja

void MyWindow::DylatacjaErozja(QImage& img, int mode)
{
    // na czarno bialym juz obrazie sprawdzamy czy piksel jest czarny czyli wystarczy sprawdzic np tylko wartosc R 
    // jesli piksel jest czarny to sprawdzamy 4 sasiadow i jesli ktorys jest bialy to zamieniamy na bialy 
    // iteracja po wszystkich pikselach w obrazie
    int test;
    if (mode == 255)
    {
        test = 0;
    }
    else
    {
        test = 255;
    }

    int y, x;
    int color;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            unsigned char* ptr;
            ptr = img.bits();
            color = ptr[szer * 4 * y + 4 * x];

            // jesli piksel jest czarny to sprawdzamy 4 sasiadow i jesli ktorys jest bialy to zamieniamy na bialy

            if (color == test)
            {
                //sprawdzamy sasiadow
                //sprawdzamy sasiada z lewej
                if (x > 0)
                {
                    ptr = img.bits();
                    color = ptr[szer * 4 * y + 4 * (x - 1)];
                    if (color == mode)
                    {
                        wstawPiksel(x, y, *temp, mode);
                    }
                }
                //sprawdzamy sasiada z prawej
                if (x < szer - 1)
                {
                    ptr = img.bits();
                    color = ptr[szer * 4 * y + 4 * (x + 1)];
                    if (color == mode)
                    {
                        wstawPiksel(x, y, *temp, mode);
                    }
                }
                //sprawdzamy sasiada z gory
                if (y > 0)
                {
                    ptr = img.bits();
                    color = ptr[szer * 4 * (y - 1) + 4 * x];
                    if (color == mode)
                    {
                        wstawPiksel(x, y, *temp, mode);
                    }
                }
                //sprawdzamy sasiada z dolu
                if (y < wys - 1)
                {
                    ptr = img.bits();
                    color = ptr[szer * 4 * (y + 1) + 4 * x];
                    if (color == mode)
                    {
                        wstawPiksel(x, y, *temp, mode);
                    }
                }
            }

        }
    }
}


void MyWindow::domkniecie()
{
    //dylatacja bo 255, sprawdza kolory dla img, modyfikuje tmp
    DylatacjaErozja(*img, 255);
    // podmiana obrazu glownego
    kopiujDo(*temp, *img);
    // update();
    //erozja bo 0,
	DylatacjaErozja(*img, 0);
    kopiujDo(*temp, *img);
    update();
}

// otwarcie 

void MyWindow::otwarcie()
{
	//erozja
	DylatacjaErozja(*img, 0);
	kopiujDo(*temp, *img);
	//dylatacja
	DylatacjaErozja(*img, 255);
	kopiujDo(*temp, *img);
	update();
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::slot_czysc()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}



// Funkcja powoduje wyczyszczenie (zamalowanie na czarno)
// obszaru rysowania
void MyWindow::czysc()
{

   // powrot do poczatkowego obrazka czarno bialego
    temp = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/o_morfologiczne/test.jpg"));
    
    img = new QImage(szer, wys, QImage::Format_RGB32);
    kopiujDo(*temp, *img);
    toBlackAndWhite(*img);
    toBlackAndWhite(*temp);
    //temp->fill(qRgb(255, 255, 255));
    update();

}




//funkcja kopujaca obrazek
void MyWindow::kopiujDo(QImage& sourceImage, QImage& destinationImage)
{

    int y,x;
    unsigned char *ptr;
    unsigned char *ptr2;
    ptr = sourceImage.bits();
    ptr2 = destinationImage.bits();
    for(y=0; y<wys; y++)
    {
        for(x=0; x<szer; x++)
        {
            ptr2[szer*4*y + 4*x]     =   ptr[szer*4*y + 4*x];
            ptr2[szer*4*y + 4*x + 1] =   ptr[szer*4*y + 4*x + 1];
            ptr2[szer*4*y + 4*x + 2] =   ptr[szer*4*y + 4*x + 2];
        }
    }
    std::cout << "Skopiowano" <<std::endl;

}


void MyWindow::toBlackAndWhite(QImage& temp) {
    int y, x;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            unsigned char* ptr;
            ptr = temp.bits();
            int r = ptr[szer * 4 * y + 4 * x];
            int g = ptr[szer * 4 * y + 4 * x + 1];
            int b = ptr[szer * 4 * y + 4 * x + 2];
            int color = (r + g + b) / 3;
            if (color > 128) color = 255;
            else color = 0;
            wstawPiksel(x, y, temp, color);
        }
    }
}


