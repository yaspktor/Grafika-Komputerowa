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
    rysujOdcinki = new QPushButton("Pokaż odcinki");
    QSlider* slider;
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(1); // minimalna liczba boków (trójkąt)
    slider->setMaximum(40); // maksymalna liczba boków
    slider->setValue(20); // wartość początkowa
    sliderValueLabel = new QLabel("20 odcinków");
    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
    boxLayout->addWidget(rysujOdcinki);
    boxLayout->addWidget(slider);
    boxLayout->addWidget(sliderValueLabel);
    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje 
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateNumberOfSides(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateSliderValueLabel(int)));
    connect(rysujOdcinki,SIGNAL(clicked()),this,SLOT(slot_rysujOdcinki()));
	czysc();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}
void MyWindow::updateSliderValueLabel(int value)
{
    qDebug() << "Wywolano updateSliderValueLabel, value:" << value;
    if (sliderValueLabel)
    {
        qDebug() << "istnieje";
        if (value == 1)
        {
            sliderValueLabel->setText(QString("%1 odcinek").arg(value));
        }
        else if (value < 5)
        {
            sliderValueLabel->setText(QString("%1 odcinki").arg(value));
        }
        else
        {
            sliderValueLabel->setText(QString("%1 odcinków").arg(value));
        }
        
    }
    else
    {
        qDebug() << "???";
    }
}
void MyWindow::updateNumberOfSides(int value) {
    n = value;
    refreshBoard(punkty);

}

void MyWindow::slot_rysujOdcinki() {
    odcinki = !odcinki;
    refreshBoard(punkty);

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
	punktyDoKrzywej.clear();
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

void MyWindow::rysujLinie(int x1, int y1, int x2, int y2, int color){

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
        wstawPiksel(x1, y1, *img, color);
    }
    // rysowanie pionowej i poziomej linii
    else if (y1 == y2) {
        for (x = x1; x <= x2; x++) {
            wstawPiksel(x, y1, *img, color);
        }

    }
    else if (x1 == x2) {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            //std::cout << "Swapped " << std::endl;
        }
        for (y = y1; y <= y2; y++) {
            wstawPiksel(x1, y, *img,color);
        }

    }
    else if (abs(a) <= 1){
        //iterowanie po szerokosci
        //std::cout << "Po X: " << std::endl;

        for (x = x1; x <= x2; x++) {
            float yn = a * x + (y1 - a*x1);
            wstawPiksel(x, (int)floor(yn+0.5), *img,color);

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
            wstawPiksel((int)floor(xn+0.5), y, *img,color);

        }
    }

    update();
}
void MyWindow::rysujKrzywa(std::vector<std::pair<int, int> > punkty, int n, bool odcinki)
{

    if (odcinki)
    {
        for (int i = 0; i < (int)punkty.size() - 1; i++)
        {
            if (i % 2 == 0)
            {
                rysujLinie(punkty[i].first, punkty[i].second, punkty[i + 1].first, punkty[i + 1].second, 30);
            } 
        }
    }
   float t, t2;
   int Px,Py, Qx, Qy;
   for (int i = 0; i < n; i++)
   {
        t = (float)i / n;
        t2 = t + 1/(float)n;
        Px = pow((1-t), 3)*punkty[0].first + 3*pow((1-t),2)*t*punkty[1].first + 3*(1-t)*t*t*punkty[2].first + t*t*t*punkty[3].first;
        Py = pow((1-t), 3)*punkty[0].second + 3*pow((1-t),2)*t*punkty[1].second + 3*(1-t)*t*t*punkty[2].second + t*t*t*punkty[3].second;
        Qx = pow((1-t2), 3)*punkty[0].first + 3*pow((1-t2),2)*t2*punkty[1].first + 3*(1-t2)*t2*t2*punkty[2].first + t2*t2*t2*punkty[3].first;
        Qy = pow((1-t2), 3)*punkty[0].second + 3*pow((1-t2),2)*t2*punkty[1].second + 3*(1-t2)*t2*t2*punkty[2].second + t2*t2*t2*punkty[3].second;
        rysujLinie(Px, Py, Qx, Qy, 255);
   }

}

void MyWindow::hover(std::vector<std::pair<int, int> > punkty, int x, int y)
{
    for (int i = 0; i < (int)punkty.size(); i++) {
        if (abs(punkty[i].first - x) < 4 && abs(punkty[i].second - y) < 4) {
            podKursorem = true;
            for (int j = -3; j <= 3; j++) {
                for (int k = -3; k <= 3; k++) {
                    wstawPiksel(punkty[i].first + j, punkty[i].second + k, *img, 190);
                }
            }
            break;
        }
        else {
            if (podKursorem) {
                for (int j = -3; j <= 3; j++) {
                    for (int k = -3; k <= 3; k++) {
                        if (j == -3 || j == 3 || k == -3 || k == 3 || j == -2 || j == 2 || k == -2 || k == 2)
                            wstawPiksel(punkty[i].first + j, punkty[i].second + k, *img, 0);
                    }
                }
				podKursorem = false;
                
				refreshBoard(punkty);
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


void MyWindow::fragmentKrzywej(std::vector<std::pair<int, int> > punkty)
{
    int licznik = 0;
    for (int i = 0; i < (int)punkty.size(); i++)
    {
        punktyDoKrzywej.push_back(punkty[i]);
        qDebug() << "dodano " << i;
        if (i == 3)
        {
            qDebug() << "narysowano " << i;
            rysujKrzywa(punktyDoKrzywej, n, odcinki);
            punktyDoKrzywej.clear();
            punktyDoKrzywej.push_back(punkty[i]);
        }
        else if (i > 3)
        {
            licznik++;
            if (licznik == 3)
            {
                qDebug() << "narysowano " << i;
                rysujKrzywa(punktyDoKrzywej, n, odcinki);
                punktyDoKrzywej.clear();
                punktyDoKrzywej.push_back(punkty[i]);
                licznik = 0;
            }

        }
    }
}

void MyWindow::rysujPunkty(std::vector<std::pair<int, int> > punkty)
{
	for (int i = 0; i < (int)punkty.size(); i++)
	{
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                wstawPiksel(punkty[i].first + k, punkty[i].second + j, *img, 190);
            }
        }
	}
}

void MyWindow::refreshBoard(std::vector<std::pair<int, int> > punkty)
{
    punktyDoKrzywej.clear();
    czysc2();
    rysujPunkty(punkty);
    fragmentKrzywej(punkty);
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

        //start linii
        pX = x;
        pY = y;

        punkty.push_back(std::make_pair(pX, pY));
        qDebug() << "Dodano:" << pX << " " << pY;
        refreshBoard(punkty);
    }
    if (event->buttons() & Qt::RightButton)
    {

            int x = event->x();
            int y = event->y();

            // Przesuwamy je zeby nie rysowac od brzegu
            x = x - poczX;
            y = y - poczY;
            qDebug() << "right  ";
            //zabezpieczenie gdy 0 punktow
            
            if (punkty.empty())
            {
				qDebug() << "puste";
				return;
            }
			//wykrycie najblizszego punktu kontrolnego pod kursorem 

            double minDist = 100000; 
            int index = 0;
            for (int i = 0; i < (int)punkty.size(); i++) {
                double dist = sqrt(pow(punkty[i].first - x, 2) + pow(punkty[i].second - y, 2));
                if (dist < minDist) {
                    minDist = dist;
                    index = i;
                    qDebug() << "minDist: " << minDist << "index: " << i;
                }
            }
            // 
            //sprawdzenie czy usuwany punkt jest w odleglosci przynajmniej 10 px od kursora
            if (abs(punkty[index].first - x) < 10 && abs(punkty[index].second - y) < 10) {
                punkty.erase(punkty.begin() + index);
                qDebug() << "usunieto punkt";
                refreshBoard(punkty);
            }
            else {
                qDebug() << "nie mozna usunac punktu";
            }
			
        }
	//if event dla srodkowego przycisku myszy
    if (event->buttons() & Qt::MiddleButton)
    {
        isPressed = true;
        int x = event->x();
        int y = event->y();

        // Przesuwamy je zeby nie rysowac od brzegu
        x = x - poczX;
        y = y - poczY;
		qDebug() << "pX: " << x << " pY: " << y;
        if (punkty.empty())
        {
            qDebug() << "puste";
            return;
        }
        //wykrycie najblizszego punktu pod myszką z dokladnoscia do 5 px i przypisanie indeksu do indexP
        //wykrycie najblizszego punktu kontrolnego pod kursorem 
        int min = 100000;
        int index = 0;
        for (int i = 0; i < (int)punkty.size(); i++) {
            if (abs(punkty[i].first - x) < min && abs(punkty[i].second - y) < min) {
                min = abs(punkty[i].first - x);
                index = i;
                qDebug() << "min:  " << i;
            }
        }
        //sprawdzenie czy usuwany punkt jest w odleglosci przynajmniej 10 px od kursora
        if (abs(punkty[index].first - x) < 5 && abs(punkty[index].second - y) < 5) {
            indexP = index;
        }
        else
        {
            indexP = -1;
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
    if (event->buttons() & Qt::MiddleButton)
    {
        if (isPressed)
        {
            if (indexP != -1)
            {
                punkty[indexP].first = x;
                punkty[indexP].second = y;
                punktyDoKrzywej.clear();
                refreshBoard(punkty);

            }

        }
    }
    hover(punkty, x, y);
    update();
    
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x = x - poczX;
    y = y - poczY;

    if (event->buttons() & Qt::MiddleButton)
    {
        isPressed = false;
    }
    //kopiujDo(*temp, *img);
}
// funkcja do przechwycenia czy klikneto klawisz M
void MyWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_M)
    {
		//wypisanie wszystkich punktow kontrolnych ich wspolrzednych
        for (int i = 0; i < (int)punkty.size(); i++) {
			qDebug() << punkty[i].first << ", " << punkty[i].second;
		}
    }
}


