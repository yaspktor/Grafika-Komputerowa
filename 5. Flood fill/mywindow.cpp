// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <iostream>
#include <cmath>
#include <stack>
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

    startLineX = 0;
    startLineY = 0;
    endLineX = 0;
    endLineY = 0;


    srKolaX = 0;
    srKolaY = 0;
    knKolaX = 0;
    knKolaY = 0;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(szer,wys,QImage::Format_RGB32);
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);
    
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));
    
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
    
    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    czysc();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
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
}


void MyWindow::rysujLinie(int x1, int y1, int x2, int y2){

    int x, y, dx, dy;
    float a;
    // zabezpieczenia
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 < 0) x2 = 0;
    if (y2 < 0) y2 = 0;
    if (x1 >= szer) x1 = szer - 1;
    if (y1 >= wys) y1 = wys - 1;
    if (x2 >= szer) x2 = szer - 1;
    if (y2 >= wys) y2 = wys - 1;


    // obliczenie różnic
    dx = x2 - x1;
    dy = y2 - y1;
    // obliczenie wartości współczynnika kierunkowego
    a = (float) dy / dx;
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
        std::cout << "Swapped " << std::endl;
    }
    // rysowanie pojedynczej kropki, jeśli punkty są takie same
    if (dx == 0 && dy == 0) {
        wstawPiksel(x1, y1, *img);
    }
    // rysowanie pionowej i poziomej linii
    else if (y1 == y2) {
        for (x = x1; x <= x2; x++) {
            wstawPiksel(x, y1, *img);
        }

    }
    else if (x1 == x2) {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            wstawPiksel(x1, y, *img);
        }

    }
    else if (abs(a) <= 1){
        //iterowanie po szerokosci
        std::cout << "Po X: " << std::endl;

        for (x = x1; x <= x2; x++) {
            float yn = a * x + (y1 - a*x1);
            wstawPiksel(x, (int)floor(yn+0.5), *img);

        }
    }
    else
    {
        std::cout << "Po Y: " << std::endl;
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            float xn  = (y - y1 + a*x1)/a;
            wstawPiksel((int)floor(xn+0.5), y, *img);

        }
    }

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

void MyWindow::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
void MyWindow::wstawSegmenty(std::vector<std::pair<int, int> > punkty)
{
    for (int i = 0; i < (int)punkty.size(); i++) {
        // sprawdzenie czy po przesunieciu nie wyszliśmy poza obszar

        wstawPiksel(punkty[i].first + srKolaX, punkty[i].second + srKolaY, *img);


    }
}

void MyWindow::rysujKolo(int x1, int y1, int x2, int y2) {

    int x, r;
    float y;
    r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    std::cout << "r = " << r << std::endl;
    // vector punktow do pomalowania z pierwszej osemki kola
    std::vector<std::pair<int, int> > punkty;
    for (x = 0; x <= (r / (sqrt(2))) + 1; x++)
    {
        y = sqrt(r * r - x * x);
        y = (int)floor(y + 0.5);

        //std::cout << y << std::endl;
        // dodanie do wektora punktow ze wszystkich osemek
        punkty.push_back(std::make_pair(x, y));
        punkty.push_back(std::make_pair(y, x));
        punkty.push_back(std::make_pair(-x, y));
        punkty.push_back(std::make_pair(-y, x));
        punkty.push_back(std::make_pair(x, -y));
        punkty.push_back(std::make_pair(y, -x));
        punkty.push_back(std::make_pair(-x, -y));
        punkty.push_back(std::make_pair(-y, -x));
    }
    wstawSegmenty(punkty);
    update();
}
//funkcja do wypełniania kolorem obszaru flood(x,y)

void MyWindow::flood(int x, int y)
{
    std::cout << "funckja flood" <<std::endl;
    //deklaracja stosu dla punktow 
    std::stack <std::pair<int, int>> stos;
    //dodanie punktu startowego do stosu
    stos.push(std::make_pair(x, y));
    //kolor startowy czarny 
    //petla while wykonuje sie dopoki stos nie jest pusty
    while (!stos.empty())
    {
		//pobranie punktu z gory stosu
		std::pair<int, int> punkt = stos.top();
		//usuniecie go ze stosu
		stos.pop();
        unsigned char* ptr;
        ptr = img->bits();
		//sprawdzenie czy punkt nie jest poza obszarem rysowania
        if (punkt.first >= 0 && punkt.first < szer && punkt.second >= 0 && punkt.second < wys)
        {

            //sprawdzenie czy piksel
            /*ptr[szer * 4 * y + 4 * x] = 0;
            ptr[szer * 4 * y + 4 * x + 1] = 0;
            ptr[szer * 4 * y + 4 * x + 2] = 0;*/
            if (ptr[szer * 4 * punkt.second + 4 * punkt.first] == 0 ||
                ptr[szer * 4 * punkt.second + 4 * punkt.first + 1] == 0 ||
                ptr[szer * 4 * punkt.second + 4 * punkt.first + 2] == 0)
            {
                 //std::cout << "fokk" <<std::endl;
				//wstawienie piksela do obrazka
                wstawPiksel(punkt.first, punkt.second, *img, 120);
                update();
				//dodanie sasiadow do stosu
				stos.push(std::make_pair(punkt.first + 1, punkt.second));
				stos.push(std::make_pair(punkt.first - 1, punkt.second));
				stos.push(std::make_pair(punkt.first, punkt.second + 1));
				stos.push(std::make_pair(punkt.first, punkt.second - 1));
            }
            
		}
	}



    
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        isPressedL = true;
        // Pobieramy wspolrzedne punktu klikniecia
        // Sa to wspolrzedne wzgledem glownego okna
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;

        //start linii
        startLineX = x;
        startLineY = y;


        std::cout << "Start: " << x << " " << y << std::endl;
        std::cout << "Start: " << startLineX << " " << startLineY << std::endl;

        kopiujDo(*img, *temp);


        // Odswiezamy komponent
        update();
    
    }else if (event->buttons() & Qt::RightButton){
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;
        flood(x,y);
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        //rysowanie kola 
        isPressedM = true;
        // Pobieramy wspolrzedne punktu klikniecia
        // Sa to wspolrzedne wzgledem glownego okna
        int x = event->x();
        int y = event->y();
        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;

        //start kola

        srKolaX = x;
        srKolaY = y;

        //std::cout << "Start: "<<x << " "<< y<< std::endl;
        //std::cout << "Start: "<<startLineX << " "<< startLineY<< std::endl;

        kopiujDo(*img, *temp);
        // Odswiezamy komponent
        update();
    }

}



void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        if (isPressedL)
        {
            int x = event->x();
            int y = event->y();


            x = x - poczX;
            y = y - poczY;

            endLineX = x;
            endLineY = y;

            kopiujDo(*temp, *img);

            rysujLinie(startLineX, startLineY, endLineX, endLineY);
            update();

        }
    }
    else if (event->buttons() & Qt::MiddleButton) {
        if (isPressedM)
        {
            int x = event->x();
            int y = event->y();

            x = x - poczX;
            y = y - poczY;

            //koniec kola
            knKolaX = x;
            knKolaY = y;

            kopiujDo(*temp, *img);

            rysujKolo(srKolaX, srKolaY, knKolaX, knKolaY);
            update();

        }
    }
    
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
    int x = event->x();
    int y = event->y();


    x = x - poczX;
    y = y - poczY;

    endLineX =x;
    endLineY = y;

    std::cout << "Koniec: "<<endLineX << " "<< endLineY<< std::endl;
    std::cout << "Start: "<<startLineX << " "<< startLineY<< std::endl;
    isPressedL = false;
    rysujLinie(startLineX, startLineY, endLineX, endLineY);
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        int x = event->x();
        int y = event->y();

        x = x - poczX;
        y = y - poczY;

        //koniec kola
        knKolaX = x;
        knKolaY = y;

        //std::cout << "Koniec: "<<knKolaX << " "<< knKolaY<< std::endl;
        //std::cout << "Start: "<<srKolaX << " "<< srKolaY<< std::endl;
        isPressedL = false;
        rysujKolo(srKolaX, srKolaY, knKolaX, knKolaY);
    }
}


