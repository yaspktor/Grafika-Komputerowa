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

#include <QTime>

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

    Tx = 1.0;
    Ty = 1.0;
    Tz = 1.0;
    alfa = 0.0;
    beta = 0.0;
    gamma = 0.0;
    Sx = 1.0;
    Sy = 1.0;
    Sz = 1.0;
    Shx = 0.0;
    Shy = 0.0;
    m_running= true;

    interpolacja_status = false;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    //img = new QImage(szer,wys,QImage::Format_RGB32);
    temp = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/przeksztalcenia3D/test.png"));
    img2 = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/przeksztalcenia3D/test.png")); //tylko obrazek
    imgG = new QImage(QString::fromStdString("C:/Users/Piotr/Desktop/Studia/PGK/przeksztalcenia3D/diamond.jpg"));
    img = new QImage(szer, wys, QImage::Format_RGB32); //obraz po przeksztalceniu 
    //fill image with white color
    img -> fill(Qt::white);
    //*img2 = *img;
    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupaTranslacja = new QGroupBox("Sterowanie Translacja",this);
    grupaRotacja = new QGroupBox("Sterowanie Rotacja",this);
    grupaSkalowanie = new QGroupBox("Sterowanie Skalowanie",this);
    //grupaPochylenie = new QGroupBox("Sterowanie Pochylenie",this);
    grupaInne = new QGroupBox("Inne",this);
    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna 
    grupaTranslacja->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX-20,poczY+150));
    grupaRotacja->setGeometry(QRect(poczX+szer+poczX,poczY+180,800-szer-2*poczX-20,poczY+150));
    grupaSkalowanie->setGeometry(QRect(poczX+szer+poczX,poczY+360,800-szer-2*poczX-20,poczY+150));
    //grupaPochylenie->setGeometry(QRect(poczX+szer+poczX,poczY+500,800-szer-2*poczX-20,poczY+100));
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
    sliderX->setMinimum(-wys);
    sliderX->setMaximum(wys);
    sliderX->setValue(0);
    sliderValueLabelX = new QLabel("0");

    // os Y
    sliderY = new QSlider(Qt::Horizontal);
    sliderY->setMinimum(-szer);
    sliderY->setMaximum(szer);
    sliderY->setValue(0);
    sliderValueLabelY = new QLabel("0");

    //os Z

    sliderZ = new QSlider(Qt::Horizontal);
    sliderZ->setMinimum(-szer);
    sliderZ->setMaximum(szer);
    sliderZ->setValue(0);
    sliderValueLabelZ = new QLabel("0");




    // Rotacja x
    sliderR = new QSlider(Qt::Horizontal);
    sliderR->setMinimum(0);
    sliderR->setMaximum(360);
    sliderR->setValue(0);
    sliderValueLabelR = new QLabel("0");

    // Rotacja y

    sliderB = new QSlider(Qt::Horizontal);
    sliderB->setMinimum(0);
    sliderB->setMaximum(360);
    sliderB->setValue(0);
    sliderValueLabelB = new QLabel("0");


    // Rotacja z 

    sliderG = new QSlider(Qt::Horizontal);
    sliderG->setMinimum(0);
    sliderG->setMaximum(360);
    sliderG->setValue(0);
    sliderValueLabelG = new QLabel("0");



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

    // sz

    sliderSz = new QSlider(Qt::Horizontal);
    sliderSz->setMinimum(1);
    sliderSz->setMaximum(1000);
    sliderSz->setValue(100);
    sliderValueLabelSz = new QLabel("1");



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
    resetButton->setGeometry(QRect(poczX + szer + poczX, poczY + 550, 800 - szer - 2 * poczX - 20, poczY + 20));
    boxLayout5->addWidget(resetButton);

    //exit button
    exitButton = new QPushButton("Exit");
    exitButton->setGeometry(QRect(poczX + szer + poczX, poczY + 550, 800 - szer - 2 * poczX - 20, poczY + 20));
    boxLayout5->addWidget(exitButton);

    // animation button
    animationButton = new QPushButton("Animation");
    animationButton->setGeometry(QRect(poczX + szer + poczX, poczY + 550, 800 - szer - 2 * poczX - 20, poczY + 20));
    boxLayout5->addWidget(animationButton);
    
    
    boxLayout->addWidget(sliderX);
    boxLayout->addWidget(sliderValueLabelX);
    boxLayout->addWidget(sliderY);
    boxLayout->addWidget(sliderValueLabelY);
    boxLayout->addWidget(sliderZ);
    boxLayout->addWidget(sliderValueLabelZ);

    boxLayout2->addWidget(sliderR);
    boxLayout2->addWidget(sliderValueLabelR);
    boxLayout2->addWidget(sliderB);
    boxLayout2->addWidget(sliderValueLabelB);
    boxLayout2->addWidget(sliderG);
    boxLayout2->addWidget(sliderValueLabelG);


    boxLayout3->addWidget(sliderSx);
    boxLayout3->addWidget(sliderValueLabelSx);
    boxLayout3->addWidget(sliderSy);
    boxLayout3->addWidget(sliderValueLabelSy);
    boxLayout3->addWidget(sliderSz);
    boxLayout3->addWidget(sliderValueLabelSz);



    // Dodajemy layout do grupy
    grupaTranslacja->setLayout(boxLayout);
    grupaRotacja->setLayout(boxLayout2);
    grupaSkalowanie->setLayout(boxLayout3);
   // grupaPochylenie->setLayout(boxLayout4);
    grupaInne->setLayout(boxLayout5);

    // laczenie sliderow z funkcjami do mieniania wartosci zmiennych R, G , B
    //connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(updateLabelX(int)));
    //connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(updateLabelY(int)));
    //connect(sliderZ, SIGNAL(valueChanged(int)), this, SLOT(setZ(int)));
    connect(sliderZ, SIGNAL(valueChanged(int)), this, SLOT(updateLabelZ(int)));
    //obroty
    //connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(setR(int)));
    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(updateLabelR(int)));
    //connect(sliderB, SIGNAL(valueChanged(int)), this, SLOT(setB(int)));
    connect(sliderB, SIGNAL(valueChanged(int)), this, SLOT(updateLabelB(int)));
    //connect(sliderG, SIGNAL(valueChanged(int)), this, SLOT(setG(int)));
    connect(sliderG, SIGNAL(valueChanged(int)), this, SLOT(updateLabelG(int)));



    connect(sliderSx, SIGNAL(valueChanged(int)), this, SLOT(updateLabelSx(int)));
    connect(sliderSy, SIGNAL(valueChanged(int)), this, SLOT(updateLabelSy(int)));
    connect(sliderSz, SIGNAL(valueChanged(int)), this, SLOT(updateLabelSz(int)));

    connect(sliderShx, SIGNAL(valueChanged(int)), this, SLOT(updateLabelShx(int)));
    connect(sliderShy, SIGNAL(valueChanged(int)), this, SLOT(updateLabelShy(int)));

    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(animationButton, SIGNAL(clicked()), this, SLOT(animation()));


    //kopiujDo(*temp, *img);

    //RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy , Sz);

    //animacjaObrotuKostki();

    //PrzeksztalcanieObrazka(0,0,0,1,1,0,0);
    czysc();
    update();


}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
    delete img2;
    delete temp;
    //qtimer

}

void MyWindow::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void MyWindow::rysujLinie(int x1, int y1, int x2, int y2, QColor color, QImage& img) {

    int x, y, dx, dy;
    float a;

    // obliczenie ró¿nic
    dx = x2 - x1;
    dy = y2 - y1;
    // obliczenie wartoœci wspó³czynnika kierunkowego
    a = (float)dy / dx;
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
        //std::cout << "Swapped " << std::endl;
    }
    // rysowanie pojedynczej kropki, jeœli punkty s¹ takie same
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
            wstawPiksel(x1, y, img, color);
        }

    }
    else if (abs(a) <= 1) {
        //iterowanie po szerokosci
        //std::cout << "Po X: " << std::endl;

        for (x = x1; x <= x2; x++) {
            float yn = a * x + (y1 - a * x1);
            wstawPiksel(x, (int)floor(yn + 0.5), img, color);

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
            float xn = (y - y1 + a * x1) / a;
            wstawPiksel((int)floor(xn + 0.5), y, img, color);

        }
    }

    update();
}

void MyWindow::obliczWektor(double points[4][3], double normal[3]) {
    // obliczanie wektorów na podstawie punktów

    // sa to 2 wektory na podstawie 3 punktów   
    double v1[3] = { points[1][0] - points[0][0], points[1][1] - points[0][1], points[1][2] - points[0][2] };
    double v2[3] = { points[2][0] - points[0][0], points[2][1] - points[0][1], points[2][2] - points[0][2] };

    // obliczanie iloczynu wektorowego 
    normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
    normal[1] = v1[2] * v2[0] - v1[0] * v2[2];
    normal[2] = v1[0] * v2[1] - v1[1] * v2[0];
}


void MyWindow::RysowanieSzescianu3D(double Tx, double Ty, double Tz, double alfa, double beta, double gamma, double Sx, double Sy, double Sz) {
    double const r = 100; // zmienna odpowiedzialna za srodek szescianu // punkt 0 bêdzie (-r, -r, -r) a punkt 7 bêdzie (r, r, r) 
    const int f = 500;




    // wektor padania  swiatla

    int swiatlo[3] = { 0,0,-1 };

    
    std::vector<std::pair<int, int>> punktyTrojkatuObrazek1 = {
        
        
    {0, 600},
    {600, 0},  
    {0, 0},
    
    };

    std::vector<std::pair<int, int>> punktyTrojkatuObrazek2 = {
         {0, 600},
        {600, 600},
        {600, 0},    
       
    };

    //cameraPoints

    double cameraPosition[3] = { 0,0, -f };

    //tablica z punktami szescianu
    double punkty[8][3] = {
            {-r, -r, -r},
            {r, -r, -r},
            {r, r, -r},
            {-r, r, -r},
            {-r, -r, r },
            {r, -r, r },
            {r, r, r },
            {-r, r, r}
    };

    double M[4][4] = { 0 }; //macierz transformacji 


    //macierz translacji szescianu wzgledem osi OZ
    double Txyz[4][4] = {
        {1,0,0,Tx},
        {0,1,0,Ty},
        {0,0,1,Tz + f},
        {0,0,0,1},
    };




    //macierz pochylenia szescianu 4x4 o kat 30 stopni w osi x
    float theta = alfa * M_PI / 180.0;  // 30 stopni


    // Macierz transformacji 4x4
    double transformationMatrix[4][4] = {
        {1.0, 0.0,         0.0,          0.0},
        {0.0, cos(theta), -sin(theta),  0.0},
        {0.0, sin(theta), cos(theta),   0.0},
        {0.0, 0.0,         0.0,          1.0}
    };

    //   // macierz transformacji oy 4x4 obrót 
    //   
    float theta2 = beta * M_PI / 180.0;  // 30 stopni

    //   // Macierz transformacji 4x4

    double transformationMatrix2[4][4] = {
        {cos(theta2), 0.0, sin(theta2),  0.0},
        {0.0,         1.0, 0.0,          0.0},
        {-sin(theta2),0.0, cos(theta2),  0.0},
        {0.0,         0.0, 0.0,          1.0}
    };


    float theta3 = gamma * M_PI / 180.0;  // 30 stopni

    //   // Macierz transformacji 4x4

    double transformationMatrix3[4][4] = {
        {cos(theta3), -sin(theta3), 0.0,  0.0},
        {sin(theta3),cos(theta3)  , 0.0,  0.0},
        {0.0,    0.0,               1.0,  0.0},
        {0.0,    0.0,               0.0,  1.0}
    };

    //macierz skalowania szescianu 4x4
    double scaleMatrix[4][4] = {
    {Sx,  0.0, 0.0, 0.0},
    {0.0, Sy,  0.0, 0.0},
    {0.0, 0.0, Sz,  0.0},
    {0.0, 0.0, 0.0, 1.0}
    };

    //tworzenie macierzy transformacji M

    double tmpMatrix[4][4] = { 0 };
    double tmpMatrix2[4][4] = { 0 };
    double tmpMatrix3[4][4] = { 0 };


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {

                sum += Txyz[i][k] * transformationMatrix2[k][j];
            }
            tmpMatrix[i][j] = sum;
        }
    }



    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += tmpMatrix[i][k] * transformationMatrix[k][j];
            }
            tmpMatrix2[i][j] = sum;
        }
    }


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += tmpMatrix2[i][k] * transformationMatrix3[k][j];
            }
            tmpMatrix3[i][j] = sum;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += tmpMatrix3[i][k] * scaleMatrix[k][j];
            }
            M[i][j] = sum;
        }
    }


    std::vector<int> punkty2d;
    std::vector<double> punkty3D;

    // Przekszta³cenie punktów szeœcianu
    for (int i = 0; i < 8; i++) {
        double P[4][1] = { {punkty[i][0]}, {punkty[i][1]}, {punkty[i][2]}, {1} };
        double Pprim[4][1] = { {0}, {0}, {0}, {0} };
        for (int i = 0; i < 4; i++) {

            for (int j = 0; j < 4; j++) {

                Pprim[i][0] += M[i][j] * P[j][0];
            }
        }

        double x = Pprim[0][0];
        double y = Pprim[1][0];
        double z = Pprim[2][0];
        double x2d = (x * f / (z + f));
        double y2d = (y * f / (z + f));
        //dodajmy do punktow polowe szerokosci i wysokosci obrazka aby wysrodkowac
        x2d += szer / 2;
        y2d += wys / 2;
        punkty2d.push_back(x2d);
        punkty2d.push_back(y2d);
        punkty3D.push_back(x);
        punkty3D.push_back(y);
        punkty3D.push_back(z);
    }

    //sciany

    int sciany[6][4] = {
    {0, 1, 5, 4},  
    {7, 6, 2, 3},  
    {6, 5, 1, 2}, 
    {7, 3, 0, 4},  
    {7, 4, 5, 6},
    {3, 2, 1, 0}  
    };


    //trojkaty 

    int trojkaty[12][3] = {
        {0, 1, 5}, 
        {7, 6, 2}, 
        {2, 3, 7}, 
        {6, 5, 1}, 
        {1, 2, 6}, 
        {7, 3, 0}, 
        {0, 4, 7}, 
        {7, 4, 5}, 
        {5, 6, 7}, 
        {3, 2, 1}, 
        {1, 0, 3}  
    };


    for (int i = 0; i < 6; i++) { //mamy 6 scian
        double punktySciany[4][3]; // jedna sciana z 4 punktami i kazdy punkt ma 3 wspolrzedne
        for (int j = 0; j < 4; j++) { // kazda sciana ma 4 punkty 
            int pointIndex = sciany[i][j]; // indeks danego punktu 

            // do jtego punktu szukamy wszystkie jego 3 wspolrzedne x y z,  z tablicy ze wszystkimi wspolrzednymi 3d 

            punktySciany[j][0] = punkty3D[pointIndex * 3];
            punktySciany[j][1] = punkty3D[pointIndex * 3 + 1];
            punktySciany[j][2] = punkty3D[pointIndex * 3 + 2];



        }

        //na koniec petli mamy punkty jednej sciany i wszystkie wspolrzedne kazdego punktu

        double normal[3];
        obliczWektor(punktySciany, normal); // obliczamy wektor prostopad³y do tej œciany i przechowujemy go w normal

        // wektor od  œciany do kamery
        double viewVector[3] = { cameraPosition[0] - punktySciany[0][0], cameraPosition[1] - punktySciany[0][1], cameraPosition[2] - punktySciany[0][2] };

        // iloczyn skalarny
        double dotProduct = normal[0] * viewVector[0] + normal[1] * viewVector[1] + normal[2] * viewVector[2];


        // je¿eli iloczyn skalarny jest dodatni, sciana jest widoczna
        //jeœli iloczyn skalarny jest dodatni, oznacza to, ¿e k¹t miêdzy wektorami jest mniejszy ni¿ 90 stopni
        if (dotProduct > 0) {
            // rysuje scianê za pomoca linii
           // QColor color = QColor(0, 255, 0);
           // for (int j = 0; j < 4; j++) {
                //int pointIndex1 = sciany[i][j]; // indeks j tego punktu itej sciany 
                //int pointIndex2 = sciany[i][(j + 1) % 4]; // indeks j+1 tego punktu itej sciany
                //w punkty2d mamy wypisane wszystkie wspolrzedne punktow 2d \

                //pobieramy odpowiedniki punktow 2d dla obu punktow ktore chemy polaczyc linia
                //int x1 = punkty2d[pointIndex1 * 2];
                //int y1 = punkty2d[pointIndex1 * 2 + 1];
                //int x2 = punkty2d[pointIndex2 * 2];
                //int y2 = punkty2d[pointIndex2 * 2 + 1];
                //rysujLinie(x1, y1, x2, y2, color, *img);
                //no i laczenie tych punktow za pomoca linii 

                //rysujLinie(x1 - 1, y1 - 1, x2 - 1, y2 - 1, color, *img);
                //rysujLinie(x1 + 1, y1 + 1, x2 + 1, y2 + 1, color, *img);
                //rysujLinie(x1 + 1, y1 + 1, x2 + 1, y2 + 1, color, *img);
                //rysujLinie(x1 + 1, y1 - 1, x2 + 1, y2 - 1, color, *img);
                //rysujLinie(x1 - 1, y1 + 1, x2 - 1, y2 + 1, color, *img);
                //////linie pod katem 45 stopni maja dziury 
                //rysujLinie(x1 - 1, y1, x2 - 1, y2, color, *img);
                //rysujLinie(x1 + 1, y1, x2 + 1, y2, color, *img);
                //rysujLinie(x1, y1 - 1, x2, y2 - 1, color, *img);
                //rysujLinie(x1, y1 + 1, x2, y2 + 1, color, *img);
                //rysujLinie(punkty2d[pointIndex1 * 2], punkty2d[pointIndex1 * 2 + 1], punkty2d[pointIndex2 * 2], punkty2d[pointIndex2 * 2 + 1], color, *img);
                
            //}

            std::vector<std::pair<int, int> > punktyTrojkata;


            // normalizacja wektora  prospopadlego do sciany

            double len = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

            normal[0] /= len;
            normal[1] /= len;
            normal[2] /= len;
            

            // obliczamy iloczyn skalarny wektora normalnego sciany  i wektora padania œwiat³a
            double ile_swiatla = normal[0] * swiatlo[0] + normal[1] * swiatlo[1] + normal[2] * swiatlo[2];

            //jesli < 0 
            if (ile_swiatla < 0.1) {
                ile_swiatla = 0.1;
            }



            // Obliczamy trójk¹ty na tej œcianie


            for (int t = 0; t < 2; t++) { // dla ka¿dego trójk¹ta na œcianie
                int trojkat[3]; // trójk¹t sk³ada siê z 3 punktów
                if (t == 0) {
                    trojkat[0] = sciany[i][0]; // dla pierwszego trójk¹ta bierzemy punkty 0, 1, 2
                    trojkat[1] = sciany[i][1];
                    trojkat[2] = sciany[i][2];


                    for (int j = 0; j < 3; j++) { // iterujemy przez punkty trójk¹ta
                        int punktIndeks = trojkat[j]; // bierzemy indeks punktu

                        // pobieramy odpowiedniki punktów 2D dla punktów trójk¹ta
                        punktyTrojkata.push_back(std::make_pair(punkty2d[punktIndeks * 2], punkty2d[punktIndeks * 2 + 1]));

                    }

                    //wypelnij trojkat z uzyciem punktytrojkata1
                    WypelnijTrojkat(punktyTrojkata, punktyTrojkatuObrazek2, ile_swiatla);

                    punktyTrojkata.clear();


                }
                else {
                    trojkat[0] = sciany[i][0]; // dla drugiego trójk¹ta bierzemy punkty 0, 2, 3
                    trojkat[1] = sciany[i][2];
                    trojkat[2] = sciany[i][3];


                    for (int j = 0; j < 3; j++) { // iterujemy przez punkty trójk¹ta
                        int punktIndeks = trojkat[j]; // bierzemy indeks punktu

                        // pobieramy odpowiedniki punktów 2D dla punktów trójk¹ta
                        punktyTrojkata.push_back(std::make_pair(punkty2d[punktIndeks * 2], punkty2d[punktIndeks * 2 + 1]));

                    }


                    WypelnijTrojkat(punktyTrojkata, punktyTrojkatuObrazek1, ile_swiatla);
                    punktyTrojkata.clear();

                }

                //double punktyTrojkatu[3][2]; // tu przechowamy 2D wspó³rzêdne punktów dla danego trójk¹ta






            }




        



        }

        //tablica z parami punktow szescianu tworz¹ce krawêdzie

        int krawedzie[12][2] = {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 0},
                {4, 5},
                {5, 6},
                {6, 7},
                {7, 4},
                {0, 4},
                {1, 5},
                {2, 6},
                {3, 7}
        };





        //wyznaczenie wspolrzednych punktow trojkatow na scianach szescianu 2d



        //tablica z parami punktow szescianu tworz¹ce krawedzie ale tak aby by³y widoczne trojkaty na scianach


        //narysowanie lini miedzy punktami szescianu czyli krawedzie 

    //    for (int i = 0; i < 12; i++) {
    //        double punkt1 = krawedzie[i][0];
    //        double punkt2 = krawedzie[i][1];
    //        double x1 = punkty2d[punkt1 * 2];
    //        double y1 = punkty2d[punkt1 * 2 + 1];
    //        double x2 = punkty2d[punkt2 * 2];
    //        double y2 = punkty2d[punkt2 * 2 + 1];
    //        //QColor color = QColor(10 * i % 255, 20 * i % 255, 30 * i % 255);
    //        // jasno zielony
    //        QColor color = QColor(0, 255, 0);
    //		rysujLinie(x1, y1, x2, y2, color, *img);
    //        //rysowanie pogrubionej lini czyli 3x
            //rysujLinie(x1 - 1, y1 - 1, x2 - 1, y2 - 1, color, *img);
            //rysujLinie(x1 + 1, y1 + 1, x2 + 1, y2 + 1, color, *img);
            //rysujLinie(x1 + 1, y1 + 1, x2 + 1, y2 + 1, color, *img);
            //rysujLinie(x1 + 1, y1 - 1, x2 + 1, y2 - 1, color, *img);
            //rysujLinie(x1 - 1, y1 + 1, x2 - 1, y2 + 1, color, *img);
            //////linie pod katem 45 stopni maja dziury 
            //rysujLinie(x1 - 1, y1, x2 - 1, y2, color, *img);
            //rysujLinie(x1 + 1, y1, x2 + 1, y2, color, *img);
            //rysujLinie(x1, y1 - 1, x2, y2 - 1, color, *img);
            //rysujLinie(x1, y1 + 1, x2, y2 + 1, color, *img); 
    //	}
    //
    }
}


void MyWindow::animacjaObrotuKostki()
{
    //obracamy kostke jednoczesnie wzgledem z x y 

    double alfa = 0.0;
    double beta = 0.0;
    double gamma = 0.0;

    //petla do obrotu od 1 do 10000000 i modulo 360

    for (int i = 0; i < 10000; i++)
    {
        alfa = i/2 % 360;
        beta = i/2 * 2 % 360;
        gamma =i/2 * 3 % 360;

        

        czysc();
        RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
        update();
        sliderR->setValue(alfa);
        sliderB->setValue(beta);
        sliderG->setValue(gamma);




        if (!m_running) {break;}


        QTime dieTime = QTime::currentTime().addMSecs(5);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
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
    QColor color = QColor(0,0,0);
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




void MyWindow::updateLabelX(int value)
{

    czysc();
    //PrzeksztalcanieObrazka(-value, Ty, alfa, Sx, Sy, Shx, Shy);
    Tx = -value;
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    update();
    sliderValueLabelX->setText(QString("%1 ").arg(value));

}

void MyWindow::updateLabelY(int value)
{
    czysc();
    //PrzeksztalcanieObrazka(Tx, -value, alfa, Sx, Sy, Shx, Shy);
    Ty = -value;
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    update();
    //sliderValueLabelX->setText(QString("%1 ").arg(value));
    sliderValueLabelY->setText(QString("%1 ").arg(value));
}

void MyWindow::updateLabelZ(int value)
{
    czysc();
    //PrzeksztalcanieObrazka(Tx, -value, alfa, Sx, Sy, Shx, Shy);
    Tz = -value;
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    update();
    //sliderValueLabelX->setText(QString("%1 ").arg(value));
    sliderValueLabelZ->setText(QString("%1 ").arg(value));
}


void MyWindow::updateLabelB(int value)
{
    czysc();
    beta = value;
    //PrzeksztalcanieObrazka(Tx, Ty, value,Sx,Sy, Shx, Shy);
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    

    update();
    sliderValueLabelB->setText(QString("%1 ").arg(value));
}



void MyWindow::updateLabelG(int value)
{
    czysc();
    gamma = value;
    //PrzeksztalcanieObrazka(Tx, Ty, value,Sx,Sy, Shx, Shy);
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);


    update();
    sliderValueLabelG->setText(QString("%1 ").arg(value));
}



void MyWindow::updateLabelR(int value)
{
    czysc();
    //PrzeksztalcanieObrazka(Tx, Ty, value, Sx, Sy, Shx, Shy);
    alfa = value;
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    update();
    sliderValueLabelR->setText(QString("%1 ").arg(value));
}



void MyWindow::updateLabelSx(int value)
{
    czysc();
    
    float new_value = value/100.0;
    //if (new_value < 1) new_value = 0.01;
    //PrzeksztalcanieObrazka(Tx, Ty, Tz, alfa, new_value, Sy, Shx, Shy);
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    Sx = new_value;
    update();
    sliderValueLabelSx->setText(QString("%1 ").arg(new_value));
}

void MyWindow::updateLabelSy(int value)
{
    czysc();
    
    float new_value = value/100.0;
    //PrzeksztalcanieObrazka(Tx, Ty, Tz, alfa, Sx, new_value, Shx, Shy);
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    Sy = new_value;
    update();
    sliderValueLabelSy->setText(QString("%1 ").arg(new_value));
}

void MyWindow::updateLabelSz(int value)
{
    czysc();
    
    float new_value = value/100.0;
    //PrzeksztalcanieObrazka(Tx, Ty, Tz, alfa, Sx, new_value, Shx, Shy);
    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    Sz = new_value;
    update();
    sliderValueLabelSz->setText(QString("%1 ").arg(new_value));
}

void MyWindow::updateLabelShx(int value)
{
	czysc();
    float new_value = value/10.0;
	//PrzeksztalcanieObrazka(Tx, Ty, Tz, alfa, Sx, Sy, new_value, Shy);
    Shx = new_value;
	update();
	sliderValueLabelShx->setText(QString("%1 ").arg(new_value));
}


void MyWindow::updateLabelShy(int value)
{
    czysc();
    float new_value = value/10.0;
    //PrzeksztalcanieObrazka(Tx, Ty, Tz, alfa, Sx, Sy, Shx, new_value);
    Shy = new_value;
    update();
    sliderValueLabelShy->setText(QString("%1 ").arg(new_value));
}

void MyWindow::reset()
{
    czysc();
    //ustawienie wszystkiego na wartosci poczatkowe
    Tx = 1.0;
    Ty = 1.0;
    Tz = 1.0;
    alfa = 0.0;
    beta =  0.0;
    gamma = 0.0;
    Sx = 1.0;
    Sy = 1.0;
    Sz = 1.0;
    Shx = 0.0;
    Shy = 0.0;
    sliderX->setValue(0);
    sliderY->setValue(0);
    sliderZ->setValue(0);

    sliderR->setValue(0);
    sliderB->setValue(0);
    sliderG->setValue(0);

    sliderSx->setValue(100);
    sliderSy->setValue(100);

    sliderSz->setValue(100);


    RysowanieSzescianu3D(Tx, Ty, Tz, alfa, beta, gamma, Sx, Sy, Sz);
    update();
    m_running = false;
    //animacjaObrotuKostki();
}


void MyWindow::animation()
{
    m_running = true;
    animacjaObrotuKostki();
    

}

void MyWindow::WypelnijTrojkat(const std::vector<std::pair<int, int>>& punktyTrojkatu, const std::vector<std::pair<int, int>>& punktyTrojkatuObrazek, double swiatlo)
{
    //sprawdzene czy punkt lezy w trojkacie wyznaczonym przez punkty z punktyTrojkata2 i pobranie jego koloru z img
    //wstawienie koloru do img2

    //petla po pikselach w img2 zaczynajac od punktu najbardziej na lewo i najnizej 

    //znajdz najnizszy i najwyzej punkt trojkata
    std::vector<std::pair<int, int> > punkty = punktyTrojkatu; //t1 czyli ten na pustym obrazie
    std::vector<std::pair<int, int> > punkty2 = punktyTrojkatuObrazek; //trojkat na obrazku z ktorego kopiujemy kolor
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

    for (int y = najnizszy; y <= najwyzej; y++)
    {
        for (int x = najbardziejNaLewo; x <= najbardziejNaPrawo; x++)
        {






            //wyznaczenie wspolrzednych barycentrycznych

            double u = ((punkty[1].second - punkty[2].second) * (x - punkty[2].first) + (punkty[2].first - punkty[1].first) * (y - punkty[2].second)) / wz;
            double v = ((punkty[2].second - punkty[0].second) * (x - punkty[2].first) + (punkty[0].first - punkty[2].first) * (y - punkty[2].second)) / wz;
            double w = 1.0 - u - v;

            //sprawdzenie czy punkt lezy w trojkacie 

            if (u >= 0 && u < 1 && v >= 0 && v < 1 && w >= 0 && w < 1)
                //if (u + v + w == 1 && u >= 0 && v >= 0 && w >= 0)
                //if (czyPunktWtrojkacie(x, y, punktyTrojkata1))
            {

                //obliczenie wspolrzednych punktu p prim 

                double Ppx = u * punkty2[0].first + v * punkty2[1].first + w * punkty2[2].first;

                double Ppy = u * punkty2[0].second + v * punkty2[1].second + w * punkty2[2].second;


                //pobranie koloru z img
                QColor color;
                
                color = InterpolacjaDwuliniowa(imgG, Ppx, Ppy); //imgG- sam obrazek oryginalny

                //zmiana jasnosci koloru na podstawie swiatla

                color.setRed(color.red() * swiatlo);
                color.setGreen(color.green() * swiatlo);
                color.setBlue(color.blue() * swiatlo);
                
                //color = imgG->pixelColor(Ppx, Ppy);

                //wstawienie koloru do img - wypelnienie trojkata na czarnej planszy 
                wstawPiksel(x, y, *img, color);
                update();
            }
            //  }
        }
    }
}



QColor MyWindow::InterpolacjaDwuliniowa(QImage* img, double x, double y) {


    if ((int)floor(x) >= 0 && (int)ceil(x) < szer && (int)floor(y) >= 0 && (int)ceil(y) < img->height()) {
        unsigned char* ptr;
        ptr = img->bits();

        int red, green, blue;

        double a = x - floor(x);
        double b = y - floor(y);

        red = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * ceil(y)) + 2)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * ceil(y)) + 2)])
            + (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * floor(y)) + 2)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * floor(y)) + 2)]);
        green = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * ceil(y)) + 1)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * ceil(y)) + 1)])
            + (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * floor(y)) + 1)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * floor(y)) + 1)]);
        blue = b * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * ceil(y)) + 0)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * ceil(y)) + 0)])
            + (1.0 - b) * ((1.0 - a) * (double)ptr[(int)(4 * (floor(x) + szer * floor(y)) + 0)] + a * (double)ptr[(int)(4 * (ceil(x) + szer * floor(y)) + 0)]);




        return QColor(red, green, blue);
    }


    else {
        return QColor(0, 0, 0); //kolor t³a
    }
}