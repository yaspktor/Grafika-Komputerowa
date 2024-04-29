// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <QDebug>
// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <iostream>
#include <QTime>
#include <cmath>
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");    
    setMouseTracking(true);
    //Zmieniamy rozmiar okna
    resize(1500,700);
    // Ustawiamy wymiary obrazka i wspolrzedne jego 
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    szer2 = 600;
    wys2 = 600;
    poczX = 25;
    poczY = 25;
    poczX2 = szer + 2*poczX;
    poczY2 = poczY;
    pX = 0;
    pY = 0;
    podKursorem = false;
    odcinki = false;
    indexP = -1;
    interpolacja_status = false;
    obrazek = 0;
	n = 20; // ilosc linii z ilu sklada sie krzywa breziera
    licznik = 0;
    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(szer,wys,QImage::Format_RGB32);
    //drugi obrazek tym razem jakis obraz png z folderu projektu
    imgG = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/Morphing/flowers.jpg")); //tylko obrazek
    imgG2 = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/Morphing/railroad.jpg")); //tylko obrazek 2
    imgWybrany = imgG;
    img2 = new QImage(szer, wys, QImage::Format_RGB32); // plansza druga
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupa->setGeometry(QRect(poczX+szer+poczX+szer2+poczX,poczY,800-szer-2*poczX,poczY+150)); 
    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
    
    // Tworzymy 4 przyciski 
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
    animacja = new QPushButton("Animacja");

    //slider do zmiany obrazka
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 1);
    slider->setValue(0);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksBelow);
    label = new QLabel("0");


    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
    boxLayout->addWidget(slider);
    boxLayout->addWidget(label);
    boxLayout->addWidget(animacja);
    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje 
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    connect(animacja, SIGNAL(clicked()), this, SLOT(slot_animacja()));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slider_zmiana(int)));


   


	czysc();
}

void MyWindow::slider_zmiana(int value) {
    obrazek = value;
    //if (new_value < 1) new_value = 0.01;
    if (value > 0)
    {
        label->setText(QString("1"));
        imgWybrany = imgG2;
        refreshBoard1();
        refreshBoard2();

    }
    else
    {
        label->setText(QString("0"));
        imgWybrany = imgG;
        refreshBoard1();
        refreshBoard2();
    }
    
}

void MyWindow::slot_animacja() {
    animacjaTr();
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
    //czysc();
    p.drawImage(poczX,poczY,*img);
    p.drawImage(poczX2,poczY2,*img2);
	//wyzerowanie img przed rysowaniem memset
	//memset(img, 0, sizeof(img));
	
	
}

void MyWindow::wstawPiksel(int x, int y, QImage& sourceImage, QColor color) {
    unsigned char* ptr;
    ptr = sourceImage.bits();
    if (x >= 0 && x < szer && y >= 0 && y < wys)
    {
        ptr[szer * 4 * y + 4 * x] = color.blue();
        ptr[szer * 4 * y + 4 * x + 1] = color.green();
        ptr[szer * 4 * y + 4 * x + 2] = color.red();
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
    //czarny
    QColor color = QColor(0, 0 ,0);

    // Przechodzimy po wszystkich wierszach obrazu
    for(y=0; y<wys; y++)
    {
        for(x=0; x<szer; x++)
        {
            wstawPiksel(x, y, *img, color);
            //wstawPiksel(x, y, *img2, 0);
        }
    }
    *img2 = *imgWybrany;
    punkty.clear();
    PunktyTrojkataNaPustym.clear();
    punktyTrojkataObrazek1.clear();
    punktyTrojkataObrazek2.clear();
	
}

void MyWindow::czysc1(QImage& img)
{
    int y, x;
    QColor color = QColor(0, 0, 0);
    // Przechodzimy po wszystkich wierszach obrazu
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            wstawPiksel(x, y, img, color);
        }
    }

}


void MyWindow::czysc2(QImage& img)
{

    *img2 = *imgWybrany;
    // Przechodzimy po wszystkich wierszach obrazu


}

void MyWindow::rysujLinie(int x1, int y1, int x2, int y2, int color, QImage& img){

    int x, y, dx, dy;
    float a;

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
        wstawPiksel(x1, y1, img, color);
    }
    // rysowanie pionowej i poziomej linii
    else if (y1 == y2) {
        for (x = x1; x <= x2; x++) {
            wstawPiksel(x, y1, img, color);
        }

    }
    else if (x1 == x2) {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            //std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            wstawPiksel(x1, y, img,color);
        }

    }
    else if (abs(a) <= 1){
        //iterowanie po szerokosci
        //std::cout << "Po X: " << std::endl;

        for (x = x1; x <= x2; x++) {
            float yn = a * x + (y1 - a*x1);
            wstawPiksel(x, (int)floor(yn+0.5), img,color);

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
            wstawPiksel((int)floor(xn+0.5), y, img,color);

        }
    }

    update();
}

void MyWindow::hover(std::vector<std::pair<int, int> > punkty, int x, int y, QImage& img, int mode)
{
    //kolor czerwony
    QColor color = QColor(255, 0, 0);
    //bialy
    QColor color2 = QColor(255, 255, 255);
    for (int i = 0; i < (int)punkty.size(); i++) {
        if (abs(punkty[i].first - x) < 4 && abs(punkty[i].second - y) < 4) {
            podKursorem = true;
            for (int j = -3; j <= 3; j++) {
                for (int k = -3; k <= 3; k++) {
                    wstawPiksel(punkty[i].first + j, punkty[i].second + k, img, color);
                }
            }
            break;
        }
        else {
            if (podKursorem) {
                for (int j = -3; j <= 3; j++) {
                    for (int k = -3; k <= 3; k++) {
                        if (j == -3 || j == 3 || k == -3 || k == 3 || j == -2 || j == 2 || k == -2 || k == 2)
                            wstawPiksel(punkty[i].first + j, punkty[i].second + k, img, color2);
                    }
                }
				podKursorem = false;

                if (mode ==1)
                {
                    refreshBoard1();
                }
                else refreshBoard2();
            }
            
            
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


void MyWindow::rysujTrojkat(std::vector<std::pair<int, int> > punkty, QImage& img)
{
    if (punkty.size() == 3)
    {
        std::cout << "rysowanie T" << std::endl;
        rysujLinie(punkty[0].first, punkty[0].second, punkty[1].first, punkty[1].second, 255, img);
        rysujLinie(punkty[1].first, punkty[1].second, punkty[2].first, punkty[2].second, 255, img);
        rysujLinie(punkty[2].first, punkty[2].second, punkty[0].first, punkty[0].second, 255, img);
    }
}

void MyWindow::rysujPunkty(std::vector<std::pair<int, int> > punkty, QImage& source)
{
	for (int i = 0; i < (int)punkty.size(); i++)
	{
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                wstawPiksel(punkty[i].first + k, punkty[i].second + j, source, 190);
            }
        }
	}
}





void MyWindow::WypelnijTrojkat(std::vector<std::pair<int, int> > punkty, double t)
{
    //sprawdzene czy punkt lezy w trojkacie wyznaczonym przez punkty z punktyTrojkata2 i pobranie jego koloru z img
    //wstawienie koloru do img2

    //petla po pikselach w img2 zaczynajac od punktu najbardziej na lewo i najnizej 

    //znajdz najnizszy i najwyzej punkt trojkata
    //std::vector<std::pair<int, int> > punkty; //t1 czyli ten na pustym obrazie
    //std::vector<std::pair<int, int> > punkty2 = punktyTrojkataObrazek1; //trojkat na obrazku z ktorego kopiujemy kolor
    //std::vector<std::pair<int, int> > punkty2;
    //std::vector<std::pair<int, int> > punkty2;
    //
    //QImage* imgLocal2;
    //QImage* imgLocal1;
 

    //potrzebne do zrobienia animacji w obie strony, 
    //if (obrazek == 0)
    //{
    //    imgLocal2 = imgG;
    //    imgLocal1 = imgG2;
    //    punkty2 = punktyTrojkataObrazek1;

    //}
    //else
    //{
    //    imgLocal1 = imgG;
    //    imgLocal2 = imgG2;
    //    
    //   
    //    
    //}

    
        //if (obrazek == 0)
        //{
        //    punkty2 = punktyTrojkataObrazek1;
        //}
        //else
        //{
        //    punkty2 = punktyTrojkataObrazek2;
        //}
   



    
        
    
    int najnizszy = punkty[0].second;
    int najwyzej = punkty[0].second;
    for (int i = 1; i < (int)punkty.size(); i++)
    {
		if (punkty[i].second < najnizszy)
			najnizszy = punkty[i].second;
		if (punkty[i].second > najwyzej)
			najwyzej = punkty[i].second;
	}

    //znajdz najbardziej na lewo i prawo punkt trojkata

    int najbardziejNaLewo = punkty[0].first;
    int najbardziejNaPrawo = punkty[0].first;
    for (int i = 1; i < (int)punkty.size(); i++)
    {

        if (punkty[i].first < najbardziejNaLewo)
			najbardziejNaLewo = punkty[i].first;
		if (punkty[i].first > najbardziejNaPrawo)
			najbardziejNaPrawo = punkty[i].first;

    }


    //wyznacznik wz na podstawie punktow w trojkacie (poza petla bo nie jest zalezny od x i y)

    double wz = (punkty[1].first - punkty[0].first) * (punkty[2].second - punkty[0].second) - (punkty[1].second - punkty[0].second) * (punkty[2].first - punkty[0].first);

    for (int y = najnizszy; y < najwyzej; y++)
    {
        for (int x = najbardziejNaLewo; x < najbardziejNaPrawo; x++)
        {


           

            

            //wyznaczenie wspolrzednych barycentrycznych

            double u = ((punkty[1].second - punkty[2].second) * (x - punkty[2].first) + (punkty[2].first - punkty[1].first) * (y - punkty[2].second)) / wz;
            double v = ((punkty[2].second - punkty[0].second) * (x - punkty[2].first) + (punkty[0].first - punkty[2].first) * (y - punkty[2].second)) / wz;
            double w = 1.0 - u - v;

            //sprawdzenie czy punkt lezy w trojkacie czylu u,v,w są <= 1 i >=0

            if (u >= 0 && u < 1 && v >= 0 && v < 1 && w >= 0 && w < 1)
            //if (u + v + w == 1 && u >= 0 && v >= 0 && w >= 0)
            //if (czyPunktWtrojkacie(x, y, punktyTrojkata1))
            {
               
                //obliczenie wspolrzednych punktu p prim  dla pierwszego trojkata/obrazka

                double Ppx1 = u * punktyTrojkataObrazek1[0].first + v * punktyTrojkataObrazek1[1].first + w * punktyTrojkataObrazek1[2].first;

                double Ppy1 = u * punktyTrojkataObrazek1[0].second + v * punktyTrojkataObrazek1[1].second + w * punktyTrojkataObrazek1[2].second;


                //dla drugiego obrazka/trojkata

                double Ppx2 = u * punktyTrojkataObrazek2[0].first + v * punktyTrojkataObrazek2[1].first + w * punktyTrojkataObrazek2[2].first;

                double Ppy2 = u * punktyTrojkataObrazek2[0].second + v * punktyTrojkataObrazek2[1].second + w * punktyTrojkataObrazek2[2].second;




                //pobranie koloru z img
                //jesli jest to klatka kluczowa
                if (t == 1)
                {
                    QColor color;
                    if (obrazek == 0)
                    {
                        color = imgG->pixelColor(Ppx1, Ppy1);
                    }
                    else
                    {
                        color = imgG2->pixelColor(Ppx2, Ppy2);
                    
                    }
                    
					
					wstawPiksel(x, y, *img, color);
					update();
                }
                //jesli jest to klatka z animacji
                else {

                QColor color;
                
                 color = imgG->pixelColor(Ppx1, Ppy1);
                 QColor color2;
                 color2 = imgG2->pixelColor(Ppx2, Ppy2);


                 //kolor z obu obrazkow w zaleznosci od t 

                 int r = (1 - t) * color.red() + t * color2.red();
                 int g = (1 - t) * color.green() + t * color2.green();
                 int b = (1 - t) * color.blue() + t * color2.blue();
                

                 color.setRgb(r, g, b);


                
                //wstawienie koloru do img - wypelnienie trojkata na czarnej planszy 
                wstawPiksel(x, y, *img, color);
                update();
                }
            }
      //  }
		}
	}
}


void MyWindow::animacjaTr() 
{
    int n = 40; //ilosc klatek
    std::vector<std::pair<int, int> > punkty;

    //dla kazdego trojkata z n trojkatow
    for (int i = 0; i < n; i++)
    {
        //obliczamy wspolrzedne wierzcholkow itego trojkata na podsrtawie trojkata1 i trojkata2 
        

        for (int j = 0; j < 3; j++)
        {
 
                int x = (1 - (double)i / n) * punktyTrojkataObrazek1[j].first + (double)i / n * punktyTrojkataObrazek2[j].first;
                int y = (1 - (double)i / n) * punktyTrojkataObrazek1[j].second + (double)i / n * punktyTrojkataObrazek2[j].second;
                punkty.push_back(std::make_pair(x, y));			
		}

        //teraz rysujemy ten trojkat na pustym polu
        czysc1(*img);
        //rysujPunkty(punkty, *img);
        //rysujTrojkat(punkty, *img);
        WypelnijTrojkat(punkty, (double)i / n);
        update();


        //delay 10 ms bo bez tego nie dzialalo
        
        QTime dieTime = QTime::currentTime().addMSecs(1);
        while (QTime::currentTime() < dieTime){
			QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
        }

        punkty.clear();


    }

}


void MyWindow::refreshBoard1()
{
    std::vector<std::pair<int, int> > punkty;
    if (obrazek == 0)
    {
        punkty = punktyTrojkataObrazek1;
    }
    else
    {
        punkty = punktyTrojkataObrazek2;
    }
    
    czysc1(*img);
    //rysujPunkty(punkty, *img);
    //rysujTrojkat(punkty, *img);
    if (punkty.size() == 3 && punktyTrojkataObrazek1.size() == 3 && punktyTrojkataObrazek2.size() == 3)
    {
        WypelnijTrojkat(punkty, 1);
       // refreshBoard2(punktyTrojkata2, *img2);
    }
    update();
}
void MyWindow::refreshBoard2( )
{
    std::vector<std::pair<int, int> > punkty;
    if (obrazek == 0)
    {
         punkty = punktyTrojkataObrazek1;
    }
    else
    {
        punkty = punktyTrojkataObrazek2;
    }
    //std::vector<std::pair<int, int> > punkty = punktyTrojkataObrazek1;
    czysc2(*img2);
    rysujPunkty(punkty, *img2);
    rysujTrojkat(punkty, *img2);
    std::cout << "R2" <<std::endl;
    if (PunktyTrojkataNaPustym.size() == 3 && punktyTrojkataObrazek1.size() == 3 && punktyTrojkataObrazek2.size() == 3)
    {
        //WypelnijTrojkat();
        // refreshBoard2(punktyTrojkata2, *img2);
    }
    update();
    
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
       
        //sprawdzenie czy kliknięcie mialo miejsce nad img czy nad img2 szer2 wys2 poczx2 poczy2
        
        if (x >= poczX2 && x < poczX2 + szer2 && y > 0 && y < wys2)
        {
            //wskaznik na punkty trojkata 1 lub 2 w zaleznosci od wartosci obrazek
            
            std::vector<std::pair<int, int>>* punktyTrojkata = nullptr; // deklaracja wskaźnika na wektor punktów trójkąta

            if (obrazek == 0)
            {
                punktyTrojkata = &punktyTrojkataObrazek1;
            }
            else
            {
                punktyTrojkata = &punktyTrojkataObrazek2;
            }


            if (punktyTrojkata->size() < 3)
            {
                x = x - poczX2 + poczX;
                //y = y - poczY2;
                qDebug() << "img2";
                //dodajemy punkt do wektora
                punktyTrojkata->push_back(std::make_pair(x, y));
                qDebug() << "Dodano:" << x << " " << y;
                if (punktyTrojkata->size() == 3)
                {
                    qDebug() << "3 punkty";
                    refreshBoard2();
                    refreshBoard1();
                    //wstawPiksel(x, y, *img2, 255);
                }
            }
        }
        else
        {
            qDebug() << "Nie dodano";
        }



            
    }

    if (event->buttons() & Qt::RightButton)
    {
        isPressed = true;
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;

       
        if (x >= poczX2 && x < poczX2 + szer2 && y > 0 && y < wys2)
        {

            if (obrazek == 0)
            {
                x = x - poczX2 + poczX;
                qDebug() << "pX: " << x << " pY: " << y;
                if (punktyTrojkataObrazek1.empty())
                {
                    qDebug() << "puste";
                    return;
                }
                //wykrycie najblizszego punktu pod myszką z dokladnoscia do 5 px i przypisanie indeksu do indexP
                //wykrycie najblizszego punktu kontrolnego pod kursorem 
                int min = 100000;
                int index = 0;
                for (int i = 0; i < (int)punktyTrojkataObrazek1.size(); i++) {
                    if (abs(punktyTrojkataObrazek1[i].first - x) < min && abs(punktyTrojkataObrazek1[i].second - y) < min) {
                        min = abs(punktyTrojkataObrazek1[i].first - x);
                        index = i;
                        qDebug() << "min:  " << i;
                    }
                }
                //sprawdzenie czy usuwany punkt jest w odleglosci przynajmniej 10 px od kursora
                if (abs(punktyTrojkataObrazek1[index].first - x) < 5 && abs(punktyTrojkataObrazek1[index].second - y) < 5) {
                    indexP = index;
                }
                else
                {
                    indexP = -1;
                }
            }
            else
            {
                x = x - poczX2 + poczX;
                qDebug() << "pX: " << x << " pY: " << y;
                if (punktyTrojkataObrazek2.empty())
                {
                    qDebug() << "puste";
                    return;
                }
                //wykrycie najblizszego punktu pod myszką z dokladnoscia do 5 px i przypisanie indeksu do indexP
                //wykrycie najblizszego punktu kontrolnego pod kursorem 
                int min = 100000;
                int index = 0;
                for (int i = 0; i < (int)punktyTrojkataObrazek2.size(); i++) {
                    if (abs(punktyTrojkataObrazek2[i].first - x) < min && abs(punktyTrojkataObrazek2[i].second - y) < min) {
                        min = abs(punktyTrojkataObrazek2[i].first - x);
                        index = i;
                        qDebug() << "min:  " << i;
                    }
                }
                //sprawdzenie czy usuwany punkt jest w odleglosci przynajmniej 10 px od kursora
                if (abs(punktyTrojkataObrazek2[index].first - x) < 5 && abs(punktyTrojkataObrazek2[index].second - y) < 5) {
                    indexP = index;
                }
                else
                {
                    indexP = -1;
                }
            }   
            refreshBoard1();
        }
    }

    update();

}



void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    x = x - poczX;
    y = y - poczY;

    if (x >= poczX2 && x < poczX2 + szer2 && y > 0 && y < wys2)
    {

        if (obrazek == 0)
        {
            x = x - poczX2 + poczX;
            if (event->buttons() & Qt::RightButton)
            {
                if (isPressed)
                {
                    if (indexP != -1)
                    {
                        punktyTrojkataObrazek1[indexP].first = x;
                        punktyTrojkataObrazek1[indexP].second = y;
                        refreshBoard2();
                        refreshBoard1();
                    }

                }
            }
            hover(punktyTrojkataObrazek1, x, y, *img2, 2);
            update();

        }
        else
        {
            x = x - poczX2 + poczX;
            if (event->buttons() & Qt::RightButton)
            {
                if (isPressed)
                {
                    if (indexP != -1)
                    {
                        punktyTrojkataObrazek2[indexP].first = x;
                        punktyTrojkataObrazek2[indexP].second = y;
                        refreshBoard2();
                        refreshBoard1();
                    }

                }
            }
            hover(punktyTrojkataObrazek2, x, y, *img2, 2);
            update();
        }

       
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x = x - poczX;
    y = y - poczY;

    if (event->buttons() & Qt::RightButton)
    {
        isPressed = false;
    }
    //kopiujDo(*temp, *img);
}


