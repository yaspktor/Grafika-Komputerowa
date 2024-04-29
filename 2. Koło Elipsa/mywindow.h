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

    bool isPressedL = false;
    bool isPressedR = false;
    // Pole przechowujace obrazek
    QImage *img;
    QImage *temp;
    // Przyciski
    QPushButton *draw1Button;
    QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton *clean2Button;
    QSlider *slider;
    QLabel *sliderValueLabel;
    // Grupa przyciskow
    QGroupBox *grupa;
    
    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    int srKolaX;
    int srKolaY;
    int knKolaX;
    int knKolaY;
    int srElipsyX;
    int srElipsyY;
    int knElipsyX;
    int knElipsyY;
    int n;
    void wstawPiksel(int x, int y, QImage& sourceImage, int color);
    // Deklaracje funkcji
    void czysc();
    void swap(int &a, int &b);
    //void rysujLinie();
    void rysujKolo(int sX, int eX, int sY, int eY);
    void rysujLinie(int sX, int eX, int sY, int eY);
    void kopiujDo(QImage& sourceImage, QImage& destinationImage);
    void rysujElipse(int x1, int y1, int x2, int y2, int n);
    void wstawSegmenty(std::vector<std::pair<int, int> > punkty);
    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    void updateSliderValueLabel(int value);
    void updateNumberOfSides(int value);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

