// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <iostream>
#include <cmath>
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej

//struktura rgb


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

    R = 0;
    G = 0;
    B = 0;

    H = 0;
    V = 0;
    S = 0;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(szer,wys,QImage::Format_RGB32);
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupaRGB = new QGroupBox("Sterowanie RGB",this);
    grupaHSV = new QGroupBox("Sterowanie HSV",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupaRGB->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX-20,poczY+200));
    grupaHSV->setGeometry(QRect(poczX+szer+poczX,poczY+250,800-szer-2*poczX-20,poczY+200));
    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *boxLayout2 = new QVBoxLayout;
    // Tworzymy 4 przyciski 

    exitButton = new QPushButton("Wyjscie");
    // RED
    sliderR = new QSlider(Qt::Horizontal);
    sliderR->setMinimum(0); 
    sliderR->setMaximum(255); 
    sliderR->setValue(0); 
    sliderValueLabelR = new QLabel("0");

    // GREEN
    sliderG = new QSlider(Qt::Horizontal);
    sliderG->setMinimum(0); 
    sliderG->setMaximum(255); 
    sliderG->setValue(0); 
    sliderValueLabelG = new QLabel("0");

    // BLUE
    sliderB = new QSlider(Qt::Horizontal);
    sliderB->setMinimum(0);
    sliderB->setMaximum(255);
    sliderB->setValue(0);
    sliderValueLabelB = new QLabel("0");


    // HUE
    sliderH = new QSlider(Qt::Horizontal);
    sliderH->setMinimum(0);
    sliderH->setMaximum(360);
    sliderH->setValue(0);
    sliderValueLabelH = new QLabel("0");

    // SATURATION
    sliderS = new QSlider(Qt::Horizontal);
    sliderS->setMinimum(0);
    sliderS->setMaximum(100);
    sliderS->setValue(0);
    sliderValueLabelS = new QLabel("0");

    // VALUE
    sliderV = new QSlider(Qt::Horizontal);
    sliderV->setMinimum(0);
    sliderV->setMaximum(100);
    sliderV->setValue(0);
    sliderValueLabelV = new QLabel("0");




    // Dodajemy przyciski do layoutu

    boxLayout->addWidget(exitButton);
    
    boxLayout->addWidget(sliderR);
    boxLayout->addWidget(sliderValueLabelR);
    boxLayout->addWidget(sliderG);
    boxLayout->addWidget(sliderValueLabelG);
    boxLayout->addWidget(sliderB);
    boxLayout->addWidget(sliderValueLabelB);
    boxLayout2->addWidget(sliderH);
    boxLayout2->addWidget(sliderValueLabelH);
    boxLayout2->addWidget(sliderS);
    boxLayout2->addWidget(sliderValueLabelS);
    boxLayout2->addWidget(sliderV);
    boxLayout2->addWidget(sliderValueLabelV);
    // Dodajemy layout do grupy
    grupaRGB->setLayout(boxLayout);
    grupaHSV->setLayout(boxLayout2);

    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    // laczenie sliderow z funkcjami do mieniania wartosci zmiennych R, G , B
    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(setR(int)));
    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(updateLabelR(int)));
    connect(sliderG, SIGNAL(valueChanged(int)), this, SLOT(setG(int)));
    connect(sliderG, SIGNAL(valueChanged(int)), this, SLOT(updateLabelG(int)));
    connect(sliderB, SIGNAL(valueChanged(int)), this, SLOT(setB(int)));
    connect(sliderB, SIGNAL(valueChanged(int)), this, SLOT(updateLabelB(int)));
    connect(sliderH, SIGNAL(valueChanged(int)), this, SLOT(setH(int)));
    connect(sliderH, SIGNAL(valueChanged(int)), this, SLOT(updateLabelH(int)));
    connect(sliderS, SIGNAL(valueChanged(int)), this, SLOT(setS(int)));
    connect(sliderS, SIGNAL(valueChanged(int)), this, SLOT(updateLabelS(int)));
    connect(sliderV, SIGNAL(valueChanged(int)), this, SLOT(setV(int)));
    connect(sliderV, SIGNAL(valueChanged(int)), this, SLOT(updateLabelV(int)));
    czysc();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}
void MyWindow::SetR(int value) {
    R = value;
    //kolorowanie
//    rysujSzescian(R);
//    update();
    //sliderValueLabelR->setText(QString("%1 ").arg(value));
}
void MyWindow::updateLabelR(int value)
{
    rysujSzescianR(value);
    update();
    sliderValueLabelR->setText(QString("%1 ").arg(value));
 
}
void MyWindow::SetG(int value) {
	G = value;
}
void MyWindow::updateLabelG(int value)
{
    rysujSzescianG(value);
    update();
	sliderValueLabelG->setText(QString("%1 ").arg(value));
}
void MyWindow::SetB(int value) {
	B = value;
}
void MyWindow::updateLabelB(int value)
{   
    rysujSzescianB(value);
	update();
	sliderValueLabelB->setText(QString("%1 ").arg(value));
}
void MyWindow::SetH(int value) {
	H = value;
}
void MyWindow::updateLabelH(int value)
{
	rysujSzescianH(value);
	update();
	sliderValueLabelH->setText(QString("%1 ").arg(value));
}
void MyWindow::SetS(int value) {
	S = value;
}
void MyWindow::updateLabelS(int value)
{
	rysujSzescianS(value / (float)100);
    float new_value = value / (float)100;
	update();
	sliderValueLabelS->setText(QString("%1 ").arg(new_value));
}
void MyWindow::SetV(int value) {
	V = value;
}
void MyWindow::updateLabelV(int value)
{
	rysujSzescianV(value / (float)100);
    float new_value = value/(float)100;
	update();
	sliderValueLabelV->setText(QString("%1 ").arg(new_value));
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
    ptr[szer*4*y + 4*x] = color;
    ptr[szer*4*y + 4*x + 1] = color;
    ptr[szer*4*y + 4*x + 2] = color;
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


//kolorujaca obrazek jako przekroj szescianu RGB w zaleznosci od wartosci suwaka R i tylko R, wartosci G i B zaleza od wysokosci i szerokosci czyli x,y w ktorym znajduje sie dany piskel
void MyWindow::rysujSzescianR(int R) {
	unsigned char *ptr;
    ptr = img->bits();
    czysc();
    std::cout << "called " << std::endl;
    std::cout << R << std::endl;
    //petla po calej planszy
    int x, y;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            //wartosc R zalezy od suwaka
            //wartosc G  ze wzoru x/(szer-1) * 255
            //wartosc B  ze wzoru y/(wys-1) * 255
            float G = (float)x/(szer-1) * 255;
            float B = (float)y/(wys-1) * 255;
            ptr[szer * 4 * y + 4 * x] = R;
            ptr[szer * 4 * y + 4 * x + 1] = G;
            ptr[szer * 4 * y + 4 * x + 2] = B;
        }
    }

}

//to samo dla G
void MyWindow::rysujSzescianG(int G) 
{
	unsigned char *ptr;
	czysc();
	std::cout << G << std::endl;
	ptr = img->bits();
	std::cout << "called " << std::endl;
	//petla po calej planszy
	int x, y;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
			//wartosc R ze wzoru y/(wys-1) * 255
			//wartosc G  zalezy od suwaka
			//wartosc B  ze wzoru x/(szer-1) * 255
			float R = (float)y/(wys-1) * 255;
			float B = (float)x/(szer-1) * 255;
            ptr[szer * 4 * y + 4 * x] = R;
            ptr[szer * 4 * y + 4 * x + 1] = G;
            ptr[szer * 4 * y + 4 * x + 2] = B;
		}
	}
}   
//to samo dla B
void MyWindow::rysujSzescianB(int B)
{
	unsigned char *ptr;
	czysc();
	std::cout << B << std::endl;
	ptr = img->bits();
	std::cout << "called " << std::endl;
	//petla po calej planszy
	int x, y;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
			//wartosc R ze wzoru x/(szer-1) * 255
			//wartosc G  ze wzoru y/(wys-1) * 255
			//wartosc B  zalezy od suwaka
			float R = (float)x/(szer-1) * 255;
			float G = (float)y/(wys-1) * 255;
			ptr[szer * 4 * y + 4 * x] = R;
			ptr[szer * 4 * y + 4 * x + 1] = G;
			ptr[szer * 4 * y + 4 * x + 2] = B;
		}
	}
}

void MyWindow::rysujSzescianH(float H)
{
    unsigned char* ptr;
    czysc();
    ptr = img->bits();
    int x, y;
    RGB rgb;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {          
            float V = (float)y / (wys - 1);
            float S = (float)x / (szer - 1);
            rgb = HSVtRGB(H, S, V);
            ptr[szer * 4 * y + 4 * x] = rgb.R;
            ptr[szer * 4 * y + 4 * x + 1] = rgb.G;
            ptr[szer * 4 * y + 4 * x + 2] = rgb.B;

        }
    }
}

void MyWindow::rysujSzescianS(float S)
{
	unsigned char* ptr;
	czysc();
	std::cout << S << std::endl;
	ptr = img->bits();
	int x, y;
	RGB rgb;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            float V = (float)y / (wys - 1);
            float H = (float)x / (szer - 1) * 360;
			rgb = HSVtRGB(H, S, V);
			ptr[szer * 4 * y + 4 * x] = rgb.R;
			ptr[szer * 4 * y + 4 * x + 1] = rgb.G;
			ptr[szer * 4 * y + 4 * x + 2] = rgb.B;
		}
	}
}

void MyWindow::rysujSzescianV(float V)
{
	unsigned char* ptr;
	czysc();
	std::cout << V << std::endl;
	ptr = img->bits();
	int x, y;
	RGB rgb;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
			float S = (float)y / (wys - 1);
			float H = (float)x / (szer - 1) * 360;
			rgb = HSVtRGB(H, S, V);
            ptr[szer * 4 * y + 4 * x] = rgb.R ;
			ptr[szer * 4 * y + 4 * x + 1] = rgb.G;
            ptr[szer * 4 * y + 4 * x + 2] = rgb.B;

            //dla 200x300 wypisanie H S V i RGB
            if (x == 100 && y == 100)
            {
				std::cout << "H: " << H << " S: " << S << " V: " << V << std::endl;
				std::cout << "R: " << rgb.R << " G: " << rgb.G << " B: " << rgb.B << std::endl;
			}



		}
	}
}


//konwersja z RGB na HSV
RGB MyWindow::HSVtRGB(float H, float  S, float  V)
{
    //konwertowanie HSV na RGB
    float C = V * S;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1)); //jezeli H == 0 to X = 0...
    float m = V - C;
    float R = 0,G = 0,B = 0;
    //float R, G, B;
    if (S == 0 ) {
        // odcienie szarości
        R = G = B = V;
    }
    else {
        if (H >= 0 && H <= 60)
        {
            R = C;
            G = X;
            B = 0;
        }
        else if (H > 60 && H <= 120)
        {
            R = X;
            G = C;
            B = 0;
        }
        else if (H > 120 && H <= 180)
        {
            R = 0;
            G = C;
            B = X;
        }
        else if (H > 180 && H <= 240)
        {
            R = 0;
            G = X;
            B = C;
        }
        else if (H > 240 && H <= 300)
        {
            R = X;
            G = 0;
            B = C;
        }
        else if (H > 300 && H <= 360)
        {
            R = C;
            G = 0;
            B = X;
        }

        R += m;
        G += m;
        B += m;
    }
    RGB rgb;
       rgb.R = R * 255;
       rgb.G = G * 255;
       rgb.B = B * 255;
       return rgb;

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

