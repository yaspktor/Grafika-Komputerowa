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

    Tx = 0.0;
    Ty = 0.0;
    alfa = 0.0;
    Sx = 1.0;
    Sy = 1.0;
    Shx = 0.0;
    Shy = 0.0;

    interpolacja_status = false;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    //img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/PrzeksztalceniaGeo2D/test.png"));
    img2 = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/PrzeksztalceniaGeo2D/test.png")); //tylko obrazek
    img = new QImage(szer, wys, QImage::Format_RGB32); //obraz po przeksztalceniu 
    //fill image with white color
    img -> fill(Qt::white);
    //*img2 = *img;
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupaTranslacja = new QGroupBox("Sterowanie Translacja",this);
    grupaRotacja = new QGroupBox("Sterowanie Rotacja",this);
    grupaSkalowanie = new QGroupBox("Sterowanie Skalowanie",this);
    grupaPochylenie = new QGroupBox("Sterowanie Pochylenie",this);
    grupaInne = new QGroupBox("Inne",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupaTranslacja->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX-20,poczY+100));
    grupaRotacja->setGeometry(QRect(poczX+szer+poczX,poczY+150,800-szer-2*poczX-20,poczY+50));
    grupaSkalowanie->setGeometry(QRect(poczX+szer+poczX,poczY+250,800-szer-2*poczX-20,poczY+100));
    grupaPochylenie->setGeometry(QRect(poczX+szer+poczX,poczY+400,800-szer-2*poczX-20,poczY+100));
    grupaInne->setGeometry(QRect(poczX + szer + poczX, poczY + 550, 800 - szer - 2 * poczX - 20, poczY + 80));
    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *boxLayout2 = new QVBoxLayout;
    QVBoxLayout *boxLayout3 = new QVBoxLayout;
    QVBoxLayout *boxLayout4 = new QVBoxLayout;
    QVBoxLayout *boxLayout5 = new QVBoxLayout;

    // Tworzymy 4 przyciski 

    // os X
    sliderX = new QSlider(Qt::Horizontal);
    sliderX->setMinimum(-wys/2);
    sliderX->setMaximum(wys/2);
    sliderX->setValue(0);
    sliderValueLabelX = new QLabel("0");

    // os Y
    sliderY = new QSlider(Qt::Horizontal);
    sliderY->setMinimum(-szer/2);
    sliderY->setMaximum(szer/2);
    sliderY->setValue(0);
    sliderValueLabelY = new QLabel("0");



    // Rotacja
    sliderR = new QSlider(Qt::Horizontal);
    sliderR->setMinimum(0);
    sliderR->setMaximum(360);
    sliderR->setValue(0);
    sliderValueLabelR = new QLabel("0");

    // Skalowanie sx
    sliderSx = new QSlider(Qt::Horizontal);
    sliderSx->setMinimum(1);
    sliderSx->setMaximum(1000);
    sliderSx->setValue(100);
    sliderValueLabelSx = new QLabel("1");


    //sy

    sliderSy = new QSlider(Qt::Horizontal);
    sliderSy->setMinimum(1);
    sliderSy->setMaximum(1000);
    sliderSy->setValue(100);
    sliderValueLabelSy = new QLabel("1");


    //pochylenie Shx

    sliderShx = new QSlider(Qt::Horizontal);
    sliderShx->setMinimum(-30);
    sliderShx->setMaximum(30);
    sliderShx->setValue(0);
    sliderValueLabelShx = new QLabel("0");

    //pochylenie Shy

    sliderShy = new QSlider(Qt::Horizontal);
    sliderShy->setMinimum(-30);
    sliderShy->setMaximum(30);
    sliderShy->setValue(0);
    sliderValueLabelShy = new QLabel("0");



    //reset button
    resetButton = new QPushButton("Reset");
    resetButton->setGeometry(QRect(poczX + szer + poczX, poczY + 550, 800 - szer - 2 * poczX - 20, poczY + 50));
    boxLayout5->addWidget(resetButton);

    //interpolacja checkbox
    interpolacjaCheckBox = new QCheckBox("Interpolacja");
    interpolacjaCheckBox->setChecked(false);
    boxLayout5->addWidget(interpolacjaCheckBox);

    
    boxLayout->addWidget(sliderX);
    boxLayout->addWidget(sliderValueLabelX);
    boxLayout->addWidget(sliderY);
    boxLayout->addWidget(sliderValueLabelY);

    boxLayout2->addWidget(sliderR);
    boxLayout2->addWidget(sliderValueLabelR);


    boxLayout3->addWidget(sliderSx);
    boxLayout3->addWidget(sliderValueLabelSx);
    boxLayout3->addWidget(sliderSy);
    boxLayout3->addWidget(sliderValueLabelSy);


    boxLayout4->addWidget(sliderShx);
    boxLayout4->addWidget(sliderValueLabelShx);
    boxLayout4->addWidget(sliderShy);
    boxLayout4->addWidget(sliderValueLabelShy);

    // Dodajemy layout do grupy
    grupaTranslacja->setLayout(boxLayout);
    grupaRotacja->setLayout(boxLayout2);
    grupaSkalowanie->setLayout(boxLayout3);
    grupaPochylenie->setLayout(boxLayout4);
    grupaInne->setLayout(boxLayout5);

    // laczenie sliderow z funkcjami do mieniania wartosci zmiennych R, G , B
    connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(updateLabelX(int)));
    connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(updateLabelY(int)));

    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(setR(int)));
    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(updateLabelR(int)));



    connect(sliderSx, SIGNAL(valueChanged(int)), this, SLOT(updateLabelSx(int)));
    connect(sliderSy, SIGNAL(valueChanged(int)), this, SLOT(updateLabelSy(int)));

    connect(sliderShx, SIGNAL(valueChanged(int)), this, SLOT(updateLabelShx(int)));
    connect(sliderShy, SIGNAL(valueChanged(int)), this, SLOT(updateLabelShy(int)));

    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    connect(interpolacjaCheckBox, SIGNAL(stateChanged(int)), this, SLOT(interpolacja(int)));


    //kopiujDo(*temp, *img);

    PrzeksztalcanieObrazka(0,0,0,1,1,0,0);
    
    update();


}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
    delete img2;
    delete temp;
}


void MyWindow::PrzeksztalcanieObrazka(double x, double y, double alfa, double Sx, double Sy, double Shx, double Shy) {

   // double T0[3][3] = { {1, 0, -(double)wys / 2},{0, 1, -(double)szer / 2},{0, 0, 1} };
    double T2[3][3] = { {1, 0, -300},{0, 1, -300},{0, 0, 1} }; // T1 = obrazek wraca na srodek
    double T1[3][3] = { {1, 0, 128},{0, 1, 128},{0, 0, 1} }; // T2 = T(128, 128) - œrodek obrazka na 0,0

    //double Txy[3][3] = { {1, 0, x - 128},{0, 1, y - 128},{0, 0, 1} }; // Txy = T(x - 128, y - 128) - œrodek obrazka przesuwa siê do 

    //macierz translacji Txy-1 o x i y

    double Txy[3][3] = { {1,0,-x},{0,1,-y},{0,0,1} };

    //macierz rotacji R^-1 o kat alfa
    double a = alfa * (M_PI / 180); //zamiana na radiany
    double R[3][3] = { {cos(a),sin(a),0},{-sin(a),cos(a),0},{0,0,1} };

    //macierz skalowania 

    double S[3][3] = { {1.0 / Sx,0,0},{0,1.0 / Sy,0},{0,0,1} };

    //macierze pochylenia

    double Sh_x[3][3] = { {1,-Shx,0},{0,1,0},{0,0,1} };
    double Sh_y[3][3] = { {1,0,0},{-Shy,1,0},{0,0,1} };
    //zlozona maciez glowna (Poniewaz wszystkie sa juz odwrocone to kolejnosc mnozenia wyglaga tak: M = (((T1 * R) * S) * Txy) * T2

    double M[3][3];


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                M[i][j] += T1[i][k] * R[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += M[i][k] * S[k][j];
            }
            M[i][j] = sum;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += M[i][k] * Sh_y[k][j];
            }
            M[i][j] = sum;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += M[i][k] * Sh_x[k][j];
            }
            M[i][j] = sum;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += M[i][k] * Txy[k][j];
            }
            M[i][j] = sum;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += M[i][k] * T2[k][j];
            }
            M[i][j] = sum;
        }
    }

    /*double Matrix[3][3] = {
        {cos(a),sin(a),(wys * cos(a) + 2 * x * cos(a) + szer * sin(a) + 2 * y * sin(a) - 256) / 2},
        {-sin(a),cos(a),(szer * cos(a) + 2 * y * cos(a) - wys * sin(a) - 2 * x * sin(a) - 256) / 2},
        {0,0,1} };*/


        //iteracja po wszystkich pikselach obrazka img2 i przemnozenie ich przez macierz M^-1

        for (int i = 0; i < szer; i++) {
            for (int j = 0; j < wys; j++) {
				//pobranie wartosci piksela
				//QColor color = img2->pixelColor(i,j);                        
                //macierz 3x1 dla piksela
                double P[3][1] = {{(double)i},{(double)j},{1}};

                //obliczenie p`
                double Pprim[3][1];
                //mnozenie
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 1; j++) {
						Pprim[i][j] = 0;
                        for (int k = 0; k < 3; k++) {
							Pprim[i][j] += M[i][k] * P[k][j];
						}
					}
				}
                //pobranie koloru z oryginalnego obrazka jesli itnieje piksel o tych wspolrzednych a obrazek ma 256x256
                if (Pprim[0][0] >= 0 && Pprim[0][0] < 256 && Pprim[1][0] >= 0 && Pprim[1][0] < 256) {
                    QColor color;

                    if (interpolacja_status == true)
                    {
                        color = InterpolacjaDwuliniowa(img2, Pprim[0][0], Pprim[1][0]); //img2- sam obrazek oryginalny
                    }
                    else
                    {
                        color = img2->pixelColor(Pprim[0][0], Pprim[1][0]);
                    }

					
					//wstawienie piksela do obrazka
					wstawPiksel(i, j, *img, color);
				}
                else {
					QColor color = QColor(255, 255, 255);
					//wstawienie piksela do obrazka
					wstawPiksel(i, j, *img, color);
				}


                

                //wstawienie piksela do obrazka
				//wstawPiksel(i, j, *img, color);

				
			}
		}
    
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

void MyWindow::wstawPiksel(int x, int y, QImage& sourceImage, QColor color){
    unsigned char *ptr;
    ptr = sourceImage.bits();
    if (x >= 0 && x < szer && y >= 0 && y < wys)
    {
    ptr[szer*4*y + 4*x] = color.blue();
    ptr[szer*4*y + 4*x + 1] = color.green();
    ptr[szer*4*y + 4*x + 2] = color.red();
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
    QColor color = QColor(255,255,255);
    // Przechodzimy po wszystkich wierszach obrazu
    for(y=0; y<wys; y++)
    {
        for(x=0; x<szer; x++)
        {
            wstawPiksel(x, y, *img, color);
        }
    }
}


//kolorujaca obrazek jako przekroj szescianu RGB w zaleznosci od wartosci suwaka R i tylko R, wartosci G i B zaleza od wysokosci i szerokosci czyli x,y w ktorym znajduje sie dany piskel



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



void MyWindow::SetX(int value) {
    Tx = -value;
}
void MyWindow::updateLabelX(int value)
{

    czysc();
    PrzeksztalcanieObrazka(-value, Ty, alfa, Sx, Sy, Shx, Shy);
    Tx = -value;
    update();
    sliderValueLabelX->setText(QString("%1 ").arg(value));

}
void MyWindow::SetY(int value) {
    Ty =-value;
}
void MyWindow::updateLabelY(int value)
{
    czysc();
    PrzeksztalcanieObrazka(Tx, -value, alfa, Sx, Sy, Shx, Shy);
    Ty = -value;
    update();
    //sliderValueLabelX->setText(QString("%1 ").arg(value));
    sliderValueLabelY->setText(QString("%1 ").arg(value));
}

void MyWindow::SetR(int value) {
    alfa = value;
}
void MyWindow::updateLabelR(int value)
{
    czysc();
    PrzeksztalcanieObrazka(Tx, Ty, value,Sx,Sy, Shx, Shy);
    alfa = value;
    update();
    update();
    sliderValueLabelR->setText(QString("%1 ").arg(value));
}

void MyWindow::updateLabelSx(int value)
{
    czysc();
    
    float new_value = value/100.0;
    //if (new_value < 1) new_value = 0.01;
    PrzeksztalcanieObrazka(Tx, Ty, alfa, new_value, Sy, Shx, Shy);
    Sx = new_value;
    update();
    sliderValueLabelSx->setText(QString("%1 ").arg(new_value));
}

void MyWindow::updateLabelSy(int value)
{
    czysc();
    
    float new_value = value/100.0;
    PrzeksztalcanieObrazka(Tx, Ty, alfa, Sx, new_value, Shx, Shy);
    Sy = new_value;
    update();
    sliderValueLabelSy->setText(QString("%1 ").arg(new_value));
}

void MyWindow::updateLabelShx(int value)
{
	czysc();
    float new_value = value/10.0;
	PrzeksztalcanieObrazka(Tx, Ty, alfa, Sx, Sy, new_value, Shy);
    Shx = new_value;
	update();
	sliderValueLabelShx->setText(QString("%1 ").arg(new_value));
}


void MyWindow::updateLabelShy(int value)
{
    czysc();
    float new_value = value/10.0;
    PrzeksztalcanieObrazka(Tx, Ty, alfa, Sx, Sy, Shx, new_value);
    Shy = new_value;
    update();
    sliderValueLabelShy->setText(QString("%1 ").arg(new_value));
}

void MyWindow::reset()
{
    czysc();
    //ustawienie wszystkiego na wartosci poczatkowe
    Tx = 0.0;
    Ty = 0.0;
    alfa = 0.0;
    Sx = 1.0;
    Sy = 1.0;
    Shx = 0.0;
    Shy = 0.0;
    sliderX->setValue(0);
    sliderY->setValue(0);
    sliderR->setValue(0);
    sliderSx->setValue(100);
    sliderSy->setValue(100);
    sliderShx->setValue(0);
    sliderShy->setValue(0);

    PrzeksztalcanieObrazka(Tx, Ty, alfa, Sx, Sy, Shx, Shy);
    update();
}


void MyWindow::interpolacja(int value)
{
    //jesli klikniete to wlacz interpolacje interpolacja = True

    if (value == 2)
    {
		interpolacja_status = true;
	}
    else
    {
		interpolacja_status = false;
	}
    PrzeksztalcanieObrazka(Tx, Ty, alfa, Sx, Sy, Shx, Shy);
    update();
}



QColor MyWindow::InterpolacjaDwuliniowa(QImage* img, double x, double y) {

    if (floor(x) >= 0 && ceil(x) < 256 && floor(y) >= 0 && ceil(y) < 256) {

       
        //ptr[szer * 4 * y + 4 * x] = color.blue(); 
        //ptr[szer * 4 * y + 4 * x + 1] = color.green();
        //ptr[szer * 4 * y + 4 * x + 2] = color.red();//[256 *4*celi(y) + 4 *floor(x) + 2]
        unsigned char* ptr;
        ptr = img->bits();

        int red, green, blue;

        double a = x - floor(x);
        double b = y - floor(y);

        red = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * ceil(y)) + 2)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * ceil(y)) + 2)])
			+ (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * floor(y)) + 2)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * floor(y)) + 2)]);
        green = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * ceil(y)) + 1)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * ceil(y)) + 1)])
            + (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * floor(y)) + 1)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * floor(y)) + 1)]);
        blue = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * ceil(y)) + 0)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * ceil(y)) + 0)])
            + (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + 256 * floor(y)) + 0)] + a * (double)ptr[(int)(4 * (ceil(x) + 256 * floor(y)) + 0)]);




    

        return QColor(red, green, blue);
    }
    else {
        return QColor(255, 255, 255); //kolor t³a
    }
}













/*
////////////////////////////////////////////////
    //obliczenie rotacji w punkcie x,y czyli Rxy =  T2 * R * T1 
double Rxy[3][3];


 // mno¿enie macierzy: Rxy = T2 * R * T1

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        Rxy[i][j] = 0;
        for (int k = 0; k < 3; k++) {
            Rxy[i][j] += T0[i][k] * R[k][j];
        }
    }
}

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        double sum = 0;
        for (int k = 0; k < 3; k++) {
            sum += Rxy[i][k] * T2[k][j];
        }
        Rxy[i][j] = sum;
    }
}
/////////////////////////////////////////////////////////////


//macierz S^-1 o wartosci S i V póki co == 1



double Sxy[3][3];


for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        Sxy[i][j] = 0;
        for (int k = 0; k < 3; k++) {
            Sxy[i][j] += T2[i][k] * S[k][j];
        }
    }
}

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        double sum = 0;
        for (int k = 0; k < 3; k++) {
            sum += Sxy[i][k] * T1[k][j];
        }
        Sxy[i][j] = sum;
    }
}

////////////////////////////////////////////////////
*/