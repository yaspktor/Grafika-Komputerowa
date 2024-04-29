// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>
#include <QSlider>
#include <QLabel>
// Dolaczamy plik naglowkowy klasy QWidget,
// Jest to klasa bazowa wszystkich elementow GUI
#include <QWidget>

// Dolaczamy plik naglowkowy klasy QPushButton
// (standardowy przycisk)
#include <QPushButton>
#include <QSlider>
#include <QLabel>
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
#include <qcheckbox.h>

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

private:

    bool isPressed = false;
    // Pole przechowujace obrazek
    QImage *img;
    QImage *temp;
    QImage *img2;
    QImage *imgG;
    // Przyciski
   
   
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton *clean2Button;

    // Grupa przyciskow
    QGroupBox *grupa;
    
    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int szer2;
    int wys2;
    int poczX;
    int poczY;
    int poczX2;
    int poczY2;
    int pX;
    int pY;
    int licznik;
    int indexP;
    bool podKursorem;
    bool odcinki;
    std::vector<std::pair<int, int> > punkty;
    std::vector<std::pair<int, int> > punktyTrojkata1;
    std::vector<std::pair<int, int> > punktyTrojkata2;

    QCheckBox* interpolacjaCheckBox;
    bool interpolacja_status;
    int n;
    void wstawPiksel(int x, int y, QImage& sourceImage, QColor color);
    // Deklaracje funkcji
    void czysc();
    void czysc1(QImage& img);
    void swap(int &a, int &b);
    void czysc2(QImage& img);
    //void rysujLinie();
    void rysujLinie(int sX, int eX, int sY, int eY, int color, QImage& sourceImage);
    void kopiujDo(QImage& sourceImage, QImage& destinationImage);
    void hover(std::vector<std::pair<int, int> > punkty, int x, int y, QImage& sourceImage, int mode);
    void rysujPunkty(std::vector<std::pair<int, int> > punkty, QImage& sourceImage);
   
    void WypelnijTrojkat();
    void refreshBoard1();
    void refreshBoard2();
    QColor InterpolacjaDwuliniowa(QImage* img, double x, double y);
    void rysujTrojkat(std::vector<std::pair<int, int> > punkty, QImage& sourceImage);
    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    void interpolacja(int state);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent*);

};

