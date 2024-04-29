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
#include <QFileDialog>






// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");    
    setMouseTracking(true);
    //Zmieniamy rozmiar okna
    resize(1505,800);

    activePic = 0;
    // Ustawiamy wymiary obrazka i wspolrzedne jego 
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 1280;
    wys = 720;
    poczX = 25;
    poczY = 25;

    startLineX = 0;
    startLineY = 0;
    endLineX = 0;
    endLineY = 0;
    alphac = 0;
    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    std::vector<std::string> nazwy(5);
    nazwy[0] = "C:/Users/Piotr/Desktop/Studia/PGK/alphablending/dog.jpg";
    nazwy[1] = "C:/Users/Piotr/Desktop/Studia/PGK/alphablending/sakuraflowers.jpg";
    nazwy[2] = "C:/Users/Piotr/Desktop/Studia/PGK/alphablending/railroad.jpg";
    nazwy[3] = "C:/Users/Piotr/Desktop/Studia/PGK/alphablending/dark.jpg";
    nazwy[4] = "C:/Users/Piotr/Desktop/Studia/PGK/alphablending/station.jpg";
    //lista ze strukturami/ obrazami 
    //std::vector<Layer> layers;

    img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(szer,wys,QImage::Format_RGB32);
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);
    grupaLista = new QGroupBox("Lista warstw",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY, 1505 -szer-2*poczX-20,poczY+100));
    grupaLista->setGeometry(QRect(poczX+szer+poczX,poczY+150, 1505 -szer-2*poczX-20,poczY+250));
    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *boxLayoutLista = new QVBoxLayout;
    // Tworzymy 4 przyciski 



    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");

    // Menu 
    blendMode = new QComboBox();
    blendMode->addItem("Normal");
    blendMode->addItem("Multiply");
    blendMode->addItem("Screen");
    blendMode->addItem("Overlay");
    blendMode->addItem("Darken");
    
    imageListWidget = new QListWidget();
    //zapelnienie listy i dodanie do vektora obrazkow 
    for (int i = 0; i < 5; i++) {
		QListWidgetItem* item = new QListWidgetItem();
        // wyodrebnienie tylko nazwy pliku do wyswietlenia w liscie

        std::string nazwa = nazwy[i];
        std::string sciezka = nazwy[i];
        int pozycja = nazwa.find_last_of("/");
        nazwa = nazwa.substr(pozycja + 1, nazwa.length() - pozycja);
        item->setText(QString::fromStdString(nazwa));
		//item->setText(QString::fromStdString(nazwy[i]));
		
		//item->setCheckState(Qt::Unchecked);
		imageListWidget->addItem(item);
		Layer layer;
        //original size is 1920x1080 but we need to resize it to 1280x720
        QImage *img2 = new QImage(QString::fromStdString(sciezka));
        QImage *img3 = new QImage(img2->scaled(1280, 720));
        layer.im = *img3;	
        layer.alpha = 100;
		layer.mode = 0;
		layer.name = QString::fromStdString(nazwy[i]);
		layers.push_back(layer);
	}

    //dodanie szarego obrazka na koniec listy
    QImage *img2 = new QImage(1280, 720, QImage::Format_RGB32);
    for (int i = 0; i < 1280; i++) {
        for (int j = 0; j < 720; j++) {
			img2->setPixel(i, j, qRgb(128, 128, 128));
		}
	}
    Layer layer;
    layer.im = *img2;
    layer.alpha = 100;
    layer.mode = 0;
    layer.name = "Szary";
    layers.push_back(layer);



    //ustawienie obrazka poczatkowego na pierwszy z listy
    if (!layers.empty()) {
        //delete img; // Usun obecny obiekt img, jesli istnieje
        //img = new QImage(layers[0].im);
        kopiujDo(layers[0].im, *img);
    }
    


    sliderAlpha = new QSlider(Qt::Horizontal);
    sliderAlpha->setMinimum(0);
    sliderAlpha->setMaximum(100);
    sliderAlpha->setValue(100);
    labelAlpha = new QLabel("1");
    
    boxLayoutLista->addWidget(blendMode);

    boxLayoutLista->addWidget(sliderAlpha);
    boxLayoutLista->addWidget(labelAlpha);
    boxLayoutLista->addWidget(imageListWidget);
    
    


    // Dodajemy przyciski do layoutu
   
    boxLayout->addWidget(cleanButton);

    boxLayout->addWidget(exitButton);

    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    grupaLista->setLayout(boxLayoutLista);
    
    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje 
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    
    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    //connect(sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(setA(int)));
    connect(sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(updateLabelAlpha(int)));

    // laczymy liste z obrazkami z funkcja rysujaca dany obrazek

    connect(imageListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_rysujObrazek(QListWidgetItem*)));


    //laczenie blendmode z funkcja zmieniajaca blendmode
    connect(blendMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_blendMode(int)));

   // slot_czysc();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}

void MyWindow::slot_blendMode(int index)
{
    //zmiana blend mode w active pic 
    //mainAlphaBlending();
    int v = index;
    layers[activePic].mode = v;
    std::cout << "Wybrano opcje:" << v << std::endl;
    mainAlphaBlending();

}


void MyWindow::slot_rysujObrazek(QListWidgetItem* item)
{
    int row = imageListWidget->row(item);
    std::cout<< row << std::endl;
    //podmiana obrazu glownego
    //*img = layers[row].im;
    //kopiujDo(layers[row].im, *img);
    //wypisanie wszystkich layers
    for (int i = 0; i < (int)layers.size(); i++) {
		std::cout << i <<  layers[i].name.toStdString() << " " << layers[i].alpha << " " <<  layers[i].mode <<std::endl;
	}
    activePic = row;
    //zmiana labelu z alfa
    labelAlpha->setText(QString("%1 ").arg(layers[row].alpha/100));
    //zmiana pozycji suwaka
    sliderAlpha->setValue(layers[row].alpha);
    //zmiana blend mode
    blendMode->setCurrentIndex(layers[row].mode);
    mainAlphaBlending();
    //update();
    
}
void MyWindow::updateLabelAlpha(int value) {

    //wywolanie blend

    float new_value = value / (float)100;
    labelAlpha->setText(QString("%1 ").arg(new_value));
	alphac = value;
    layers[activePic].alpha = alphac;
	//rysujSzescianR(value);
    //update();
    mainAlphaBlending();
	//sliderValueLabelR->setText(QString("%1 ").arg(value));
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

void MyWindow::blend(QImage& Bg, QImage& Fg, float alpha, int mode, QImage& out)
{
    //funkcja blendujaca dwie warstwy i zapisujaca wynik do out 

    //iteracja po pikselach obrazka 
    int x, y;
    unsigned char* background;
    unsigned char* foreground;
    unsigned char* out_im;
    int out_pixel;
    int cR, cG, cB, FR,FG,FB,BR,BG,BB;
    background = Bg.bits();
    foreground = Fg.bits();
    out_im = out.bits();
    alpha = alpha / 100.0;
    //std::cout << "out:" << alpha <<std::endl;
    for (y = 0; y < wys; y++)
    {
        for (x = 0; x < szer; x++)
        {
            
            //dla mode 0 czyli f(a,b) = a
            //uchar color =  (uchar) (alpha * foreground[szer*4*y + 4*x] + (1-alpha) * background[szer*4*y + 4*x]);
            //mode switch case

            //przypisanie kolorow do zmiennych 
            FR = foreground[szer*4*y + 4*x];
            FG = foreground[szer*4*y + 4*x + 1];
            FB = foreground[szer*4*y + 4*x + 2];
            //
            BR = background[szer*4*y + 4*x];
            BG = background[szer*4*y + 4*x + 1];
            BB = background[szer*4*y + 4*x + 2];
                

            switch (mode)
            {
            case 0: // normal mode 
                cR = FR;
                cG = FG;
                cB = FB;
                break;
            case 1: // multiply mode czyli c = (a*b) >>8
                cR = (FR * BR) >> 8;
                cG = (FG * BG) >> 8;
                cB = (FB * BB) >> 8;
                break;
            case 2: // screen mode czyli c = 255 - (255-a)*(255-b) >> 8
                cR = 255 - ((255 - FR) * (255 - BR) >> 8);
                cG = 255 - ((255 - FG) * (255 - BG) >> 8);
                cB = 255 - ((255 - FB) * (255 - BB) >> 8);
                break;
            case 3: // overlay mode czyli c = (a*b) >> 7 dla a < 128, c = 255 - (255-a)*(255-b) >> 7 dla a >= 128
                if (FR < 128) {
                    cR = (FR * BR) >> 7;
                }
                else {
                    cR = 255 - ((255 - FR) * (255 - BR) >> 7);
                }
                if (FG < 128) {
                    cG = (FG * BG) >> 7;
                }
                else {
                    cG = 255 - ((255 - FG) * (255 - BG) >> 7);
                }
                if (FB < 128) {
                    cB = (FB * BB) >> 7;
                }
                else {
                    cB = 255 - ((255 - FB) * (255 - BB) >> 7);
                }
                break;

            case 4: //darken mode
                if (FR < BR) {
					cR = FR;
				}
                else {
					cR = BR;
				}
                if (FG < BG) {
					cG = FG;
				}
                else {
					cG = BG;
				}
                if (FB < BB) {
					cB = FB;
				}
                else {
					cB = BB;
				}
				break;
            }


            //dla koloru czerwonego
            
            out_pixel =  alpha * cR + (1-alpha) * BR;
            out_im[szer * 4 * y + 4 * x] = out_pixel;

            //dla koloru zielonego
            
            out_pixel =  alpha * cG + (1-alpha) * BG;
            out_im[szer * 4 * y + 4 * x + 1] = out_pixel;


            //dla koloru niebieskiego
            
            out_pixel =  alpha * cB + (1-alpha) * BB;
            //std::cout << "out:" << out_pixel % 255 <<std::endl;
            out_im[szer * 4 * y + 4 * x + 2] = out_pixel;



            //wstawienie piksela do obrazka out
            
            
        }
    }


    
}

void MyWindow::mainAlphaBlending() {
    //iteracja po wszystkich warstwach i wywolanie funkcji blend
    for (int i = (int)layers.size() - 1; i >= 0; i--) {
		//blend(*img, layers[i].im, layers[i].alpha, layers[i].mode);
        blend(*img, layers[i].im, layers[i].alpha, layers[i].mode, *img);
        update();
        //wypisanie wszystkich layers 
        //std::cout << i << layers[i].name.toStdString() << " " << layers[i].alpha << " " << layers[i].mode << std::endl;
	}

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









