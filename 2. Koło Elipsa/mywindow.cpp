// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

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

    srElipsyX =0;
    srElipsyY = 0;
    knElipsyX = 0;
    knElipsyY = 0;
    n = 6;


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

    QSlider *slider;
    QLabel *sliderValueLabel;
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(3); // minimalna liczba boków (trójkąt)
    slider->setMaximum(100); // maksymalna liczba boków
    slider->setValue(6); // wartość początkowa
    sliderValueLabel = new QLabel("0");

    // Dodajemy przyciski do layoutu

    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);

    boxLayout->addWidget(slider);
    boxLayout->addWidget(sliderValueLabel);
    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    
    sliderValueLabel->setText("Test");
    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje 
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    
    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateNumberOfSides(int)));
    //connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateSliderValueLabel(int)));
    
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}

void MyWindow::updateSliderValueLabel(int value)
{
    qDebug() << "Slot updateSliderValueLabel called, value:" << value;
    if (sliderValueLabel)
    {
        qDebug() << "istnieje";
        sliderValueLabel->setText(QString("%1%").arg(value));
    }
    else
    {
         qDebug() << "???";
    }
}
void MyWindow::updateNumberOfSides(int value) {
    n = value;

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
        ptr[szer*4*y + 4*x] = color;
        ptr[szer*4*y + 4*x + 1] = color;
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

void MyWindow::wstawSegmenty(std::vector<std::pair<int, int> > punkty)
{
    for (int i = 0; i < (int)punkty.size(); i++){
        // sprawdzenie czy po przesunieciu nie wyszliśmy poza obszar

            wstawPiksel(punkty[i].first + srKolaX, punkty[i].second + srKolaY, *img);


    }
}

void MyWindow::rysujKolo(int x1, int y1, int x2, int y2){

    int x, r;
    float y;
    r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    std::cout << "r = " << r << std::endl;
    // vector punktow do pomalowania z pierwszej osemki kola
    std::vector<std::pair<int, int> > punkty;
    for(x = 0; x <= (r/(sqrt(2))) +1; x++)
    {
        y = sqrt(r*r-x*x);
        y = (int)floor(y+0.5);

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
void MyWindow::rysujLinie(int x1, int y1, int x2, int y2){

    int x, y, dx, dy;
    float a;
    // zabezpieczenia
//    if (x1 < 0) x1 = 0;
//    if (y1 < 0) y1 = 0;
//    if (x2 < 0) x2 = 0;
//    if (y2 < 0) y2 = 0;
//    if (x1 >= szer) x1 = szer - 1;
//    if (y1 >= wys) y1 = wys - 1;
//    if (x2 >= szer) x2 = szer - 1;
//    if (y2 >= wys) y2 = wys - 1;


    // obliczenie różnic
    dx = x2 - x1;
    dy = y2 - y1;
    // obliczenie wartości współczynnika kierunkowego
    a = (float) dy / dx;
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
        //std::cout << "Swapped " << std::endl;
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
            //std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            wstawPiksel(x1, y, *img);
        }

    }
    else if (abs(a) <= 1){
        //iterowanie po szerokosci
        //std::cout << "Po X: " << std::endl;

        for (x = x1; x <= x2; x++) {
            float yn = a * x + (y1 - a*x1);
            wstawPiksel(x, (int)floor(yn+0.5), *img);

        }
    }
    else
    {
        //std::cout << "Po Y: " << std::endl;
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            //std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            float xn  = (y - y1 + a*x1)/a;
            wstawPiksel((int)floor(xn+0.5), y, *img);

        }
    }

    update();
}
void MyWindow::rysujElipse(int x1, int y1, int x2, int y2, int n)
{

    int a = abs(x2 - x1);
    int b = abs(y2 - y1);
    // Obliczanie kąta między wierzchołkami
    double kat = 2 * M_PI / n;

    // Rysowanie linii między kolejnymi wierzchołkami
    for (int i = 0; i < n; ++i)
    {
        // Obliczanie współrzędnych wierzchołków
        double t1 = i * kat;
        double t2 = (i + 1) * kat;
        // x = a cos t
        // y = b sin t
        // gdzie t <0, 2PI>
        int x1_vertex = a * cos(t1);
        int y1_vertex = b * sin(t1);
        int x2_vertex = a * cos(t2);
        int y2_vertex = b * sin(t2);

        // Rysowanie linii między wierzchołkami
        rysujLinie(x1_vertex + x1, y1_vertex +y1, x2_vertex+ x1, y2_vertex+y1);
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
            ptr2[szer*4*y + 4*x]     =   ptr[szer*4*y + 4*x];
            ptr2[szer*4*y + 4*x + 1] =   ptr[szer*4*y + 4*x + 1];
            ptr2[szer*4*y + 4*x + 2] =   ptr[szer*4*y + 4*x + 2];
        }
    }
    //std::cout << "Skopiowano" <<std::endl;

}

void MyWindow::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        isPressedL = true;
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
    else if (event->buttons() & Qt::RightButton)
    {
        isPressedR = true;
        // Pobieramy wspolrzedne punktu klikniecia
        // Sa to wspolrzedne wzgledem glownego okna
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;

        //start linii
        srElipsyX =x;
        srElipsyY = y;


        //std::cout << "Start: "<<x << " "<< y<< std::endl;
        //std::cout << "Start: "<<srElipsyX << " "<< srElipsyY<< std::endl;

        kopiujDo(*img, *temp);


        // Odswiezamy komponent
        update();

    }


}



void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if (isPressedL)
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
    else if (event->buttons() & Qt::RightButton)
    {
        if (isPressedR)
        {
            int x = event->x();
            int y = event->y();


            x = x - poczX;
            y = y - poczY;

            knElipsyX =x;
            knElipsyY = y;

            kopiujDo(*temp, *img);

            //rysujLinie(srElipsyX, srElipsyY, knElipsyX, knElipsyY);
            rysujElipse(srElipsyX, srElipsyY, knElipsyX, knElipsyY, n);
            update();

        }
    }


}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
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
    else if (event->buttons() & Qt::RightButton)
    {
        int x = event->x();
        int y = event->y();


        x = x - poczX;
        y = y - poczY;

        knElipsyX =x;
        knElipsyY = y;

        std::cout << "Koniecc: "<<knElipsyX << " "<< knElipsyY<< std::endl;
        std::cout << "Start: "<<srElipsyX << " "<< srElipsyY<< std::endl;
        isPressedR = false;
        rysujElipse(srElipsyX, srElipsyY, knElipsyX, knElipsyY, n);
    }
}


