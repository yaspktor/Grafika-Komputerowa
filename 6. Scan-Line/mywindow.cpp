// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <QDebug>
// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <iostream>
#include <cmath>
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");
    setMouseTracking(true);
    //Zmieniamy rozmiar okna
    resize(800,700);
    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;
    pX = 0;
    pY = 0;
    podKursorem = false;
    odcinki = false;
    indexP = -1;
    n = 20; // ilosc linii z ilu sklada sie krzywa breziera
    licznik = 0;
    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(szer,wys,QImage::Format_RGB32);
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+150));
    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
 
    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);



    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

    czysc();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}

void MyWindow::updateNumberOfSides(int value) {
    n = value;
    //refreshBoard(punkty);

}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    //czysc();
    p.drawImage(poczX,poczY,*img);
    //wyzerowanie img przed rysowaniem memset
    //memset(img, 0, sizeof(img));


}

void MyWindow::wstawPiksel(int x, int y, QImage& sourceImage, int color = 255){
    unsigned char *ptr;
    ptr = sourceImage.bits();
    if (x>= 0 && x< szer && y>= 0 && y < wys)
    {
        ptr[szer*4*y + 4*x] = color * 2;
        ptr[szer*4*y + 4*x + 1] = color * 3;
        ptr[szer*4*y + 4*x + 2] = color;
    }

    //update();
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
    int y,x;

    // Przechodzimy po wszystkich wierszach obrazu
    for(y=0; y<wys; y++)
    {
        for(x=0; x<szer; x++)
        {
            wstawPiksel(x, y, *img, 0);
        }
    }
    punkty.clear();

}

void MyWindow::czysc2()
{
    int y,x;

    // Przechodzimy po wszystkich wierszach obrazu
    for(y=0; y<wys; y++)
    {
        for(x=0; x<szer; x++)
        {
            wstawPiksel(x, y, *img, 0);
        }
    }

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
            ptr2[szer*4*y + 4*x]        =   ptr[szer*4*y + 4*x];
            ptr2[szer*4*y + 4*x + 1]    =   ptr[szer*4*y + 4*x + 1];
            ptr2[szer*4*y + 4*x + 2]    =   ptr[szer*4*y + 4*x + 2];
        }
    }
    std::cout << "Skopiowano" <<std::endl;

}


void MyWindow::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//funkcja do znajdywania punktow przeciecia prostej y ze wszystkimi krawedziami wielokata zwraca wektor z punktami przeciecia
std::vector<int> MyWindow::ZnajdzPrzecieciaY(std::vector<std::pair<int, int> > punkty, int y)
{
    int x1,x2;

    std::vector<int> PunktyPrzeciecia;
    std::cout<<"y: "<<y<<std::endl;
    for (int i = 0; i < (int)punkty.size() -1 ; i++)
    {
        int y1 = punkty[i].second;
        int y2 = punkty[(i + 1)].second;
        if (y1 > y2)
        {
            swap(y1, y2);
            x2 = punkty[i].first;
            x1 = punkty[(i + 1)].first;
        }
        else
        {
            x1 = punkty[i].first;
            x2 = punkty[(i + 1)].first;
        }
        if (y >= y1 && y < y2 && y1 != y2)
        {
           

            int x =x1 + (y - y1) * (x2 - x1) / (y2 - y1);
            PunktyPrzeciecia.push_back(x);
            std::cout<<"punkt przeciecia x: "<<x<<std::endl;
            // wypisanie jaka to krawędz
            std::cout <<i <<  " Ax: " << x1 << " Ay: " << y1 << " Bx: " << x2 << " By: " << y2 << std::endl;

        }

    }

    return PunktyPrzeciecia;

}


//funkcja rysujaca wypelniony wielokat na podstawie wektora punktow algorytmem scan-line
void MyWindow::scanLine(std::vector<std::pair<int, int> > punkty)
{
    //min y i max y  z punktow
    int minY = punkty[0].second;
    int maxY = punkty[0].second;
    for (int i = 1; i < (int)punkty.size(); i++)
    {
        if (punkty[i].second < minY)
        {
            minY = punkty[i].second;
        }
        if (punkty[i].second > maxY)
        {
            maxY = punkty[i].second;
        }
    }

    //print max i min
    std::cout << "minY: " << minY << " maxY: " << maxY << std::endl;

    //petla od min do max
    for (int y = minY; y < maxY; y++)
    {
        //vector z punktami przeciecia prostej y ze wszystkimi krawedziami
        std::vector<int> punktyPrzeciecia;
        punktyPrzeciecia = ZnajdzPrzecieciaY(punkty, y);
        std::cout <<punktyPrzeciecia.size()<< std::endl;
        //sortowanie punktow przeciecia
        std::sort(punktyPrzeciecia.begin(), punktyPrzeciecia.end());
        //rysowanie lini miedzy punktami przeciecia
        for (int i = 0; i < (int)punktyPrzeciecia.size(); i += 2)
        {
            //
            for (int x = punktyPrzeciecia[i]; x < punktyPrzeciecia[i + 1]; x++)
            {
                wstawPiksel(x, y, *img, 255);
            }
            std::cout <<i << "x0:" << punktyPrzeciecia[i] << " x1: " << punktyPrzeciecia[i+1] << std::endl;
        }

    }

}


// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{


    if (event->buttons() & Qt::LeftButton)
    {


        // Pobieramy wspolrzedne punktu klikniecia
        // Sa to wspolrzedne wzgledem glownego okna
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;

        //start linii
        pX = x;
        pY = y;

        punkty.push_back(std::make_pair(pX, pY));
        qDebug() << "Dodano:" << pX << " " << pY;
        //wstawPiksel(pX, pY, *img, 255);
        //narysowanie tego punktu pogrubionego na planszy
        for (int i = -2; i < 3; i++)
        {
            for (int j = -2; j < 3; j++)
            {
                wstawPiksel(x + i, y + j, *img, 255);
            }
        }
        
        
    }
    else if (event->buttons() & Qt::RightButton)
    {
        //dodanie do vektora punktow jeszcze raz pierwszy punkt aby polaczyc wielokat
        punkty.push_back(std::make_pair(punkty[0].first, punkty[0].second));
        // funkcja do narysowania wypelnionego wielokata
        //wypelnij(punkty);

        //refreshBoard(punkty);
    }

    update();

}



void MyWindow::keyPressEvent(QKeyEvent* event)
{
//    punkty.push_back((std::make_pair(225, 506)));
//    punkty.push_back((std::make_pair(185, 505)));
//    punkty.push_back((std::make_pair(199, 493)));
    punkty.push_back(std::make_pair(punkty[0].first, punkty[0].second));
    if (event->key() == Qt::Key_M)
    {
        //wypisanie wszystkich punktow kontrolnych ich wspolrzednych
        for (int i = 0; i < (int)punkty.size(); i++) {
            qDebug() << punkty[i].first << ", " << punkty[i].second;
        }
    }
    scanLine(punkty);
    update();
}


