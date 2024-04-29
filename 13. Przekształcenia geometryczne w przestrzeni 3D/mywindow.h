// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
// Dolaczamy plik naglowkowy klasy QWidget,
// Jest to klasa bazowa wszystkich elementow GUI
#include <QWidget>
#include <math.h>
// Dolaczamy plik naglowkowy klasy QPushButton
// (standardowy przycisk)
#include <QPushButton>


// Dolaczamy plik naglowkowy klasy QGroupBox
// (do grupowania komponentow GUI)
#include <QGroupBox>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>

// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>

#include<vector>

struct RGB
{
    float R;
    float G;
    float B;
};


// MyWindow jest podklasa klasy QWidget
class MyWindow : public QWidget
{
    // Makro ktore musimy dodac jezeli definiujemy wlasne sygnaly lub sloty
    Q_OBJECT
public:
    
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();

   

    

    //void WysrodkowanieObrazka();

    

private:

    bool isPressed = false;
    // Pole przechowujace obrazek
    QImage *img;
    QImage *img2;
    QImage* imgG;
    QImage *temp;

    // Przyciski
    QPushButton *draw1Button;
    QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton* resetButton;
    QPushButton *clean2Button;
    QPushButton* animationButton;
    QLabel* sliderValueLabelX;
    QLabel* sliderValueLabelY;
    QLabel* sliderValueLabelZ;
    QSlider* sliderX;
    QSlider* sliderY;
    QSlider* sliderZ;

    QLabel* sliderValueLabelR;
    QSlider* sliderR;

    QLabel* sliderValueLabelB;
    QSlider* sliderB;

    QLabel* sliderValueLabelG;
    QSlider* sliderG;

    QLabel* sliderValueLabelSx;
    QLabel* sliderValueLabelSy;
    QLabel* sliderValueLabelSz;
    
    QSlider* sliderSx;
    QSlider* sliderSy;
    QSlider* sliderSz;

    QLabel* sliderValueLabelShx;
    QLabel* sliderValueLabelShy;
    QSlider* sliderShx;
    QSlider* sliderShy;
    // Grupa przyciskows
    QGroupBox *grupaTranslacja;
    QGroupBox *grupaRotacja;
    QGroupBox *grupaSkalowanie;
    QGroupBox *grupaPochylenie;
    //grupa inne
    QGroupBox *grupaInne;
    //checkbox dla interpolacji

    QCheckBox *interpolacjaCheckBox;
    bool interpolacja_status;
    
    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    int startLineX;
    int startLineY;
    int endLineX;
    int endLineY;
    double Tx;
    double Ty;
    double Tz;
    double alfa;
    double beta;
    double gamma;
    double Sx;
    double Sy;
    double Sz;
    double V;
    double S;
    double Shx;
    double Shy;
    bool m_running;
    void swap(int& a, int& b);
    void rysujLinie(int x1, int y1, int x2, int y2, QColor color, QImage& img);
    void obliczWektor(double points[4][3], double normal[3]);
    void wstawPiksel(int x, int y, QImage& sourceImage, QColor color);
    // Deklaracje funkcji
    void czysc();

    void RysowanieSzescianu3D(double Tx, double Ty,double Tz,  double alfa, double beta, double gamma, double Sx, double Sy, double Sz);
    void animacjaObrotuKostki();
    void kopiujDo(QImage& sourceImage, QImage& destinationImage);
    int zaokragl(double x);
    void WypelnijTrojkat(const std::vector<std::pair<int, int>>& punktyTrojkatu, const std::vector<std::pair<int, int>>& punktyTrojkatuObrazek, double swiatlo);
    QColor InterpolacjaDwuliniowa(QImage* img, double x, double y);
   // void rysujLinie(int sX, int eX, int sY, int eY, int color, QImage& sourceImage);
    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
  
    void updateLabelX(int value);

    void updateLabelY(int value);
  
    void updateLabelZ(int value);

 

    void updateLabelB(int value);

 

    void updateLabelG(int value);

 
    void updateLabelR(int value);



    void updateLabelSx(int value);

    void updateLabelSy(int value);

    void updateLabelSz(int value);

    void updateLabelShy(int value);
    void updateLabelShx(int value);



    void reset();

    void animation();

   

    void paintEvent(QPaintEvent*);

    

};

