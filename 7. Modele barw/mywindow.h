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

    

private:

    bool isPressed = false;
    // Pole przechowujace obrazek
    QImage *img;
    QImage *temp;
    // Przyciski
    QPushButton *draw1Button;
    QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton *clean2Button;
    QLabel* sliderValueLabelR;
    QLabel* sliderValueLabelG;
    QLabel* sliderValueLabelB;
    QSlider* sliderR;
    QSlider* sliderG;
    QSlider* sliderB;
    QLabel* sliderValueLabelH;
    QLabel* sliderValueLabelV;
    QLabel* sliderValueLabelS;
    QSlider* sliderH;
    QSlider* sliderV;
    QSlider* sliderS;

    // Grupa przyciskows
    QGroupBox *grupaRGB;
    QGroupBox *grupaHSV;
    //struct RGB
    //{
    //    int R;
    //    int G;
    //    int B;
    //};
    
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
    int R;
    int G;
    int B;
    int H;
    int V;
    int S;
    void wstawPiksel(int x, int y, QImage& sourceImage, int color);
    // Deklaracje funkcji
    void czysc();

    void rysujSzescianR(int R);
    void rysujSzescianG(int G);
    void rysujSzescianB(int B);

    void rysujSzescianH(float H);
    void rysujSzescianS(float S);
    void rysujSzescianV(float V);
    
    RGB HSVtRGB(float H, float S, float V);
    //void rysujLinie();

    void kopiujDo(QImage& sourceImage, QImage& destinationImage);

    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    void SetR(int value);
    void updateLabelR(int value);
    void SetG(int value);
    void updateLabelG(int value);
    void SetB(int value);
    void updateLabelB(int value);
    void SetH(int value);
    void updateLabelH(int value);
    void SetV(int value);
    void updateLabelV(int value);
    void SetS(int value);
    void updateLabelS(int value);
    void paintEvent(QPaintEvent*);

};

