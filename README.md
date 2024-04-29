
# Grafika Komputerowa w C++ (Qt)



## 1. Rysowanie odcinka

Opis:

Projekt ten demonstruje podstawowe rysowanie odcinków w aplikacji Qt.

Funkcjonalność:
* Użytkownik może rysować linie na obszarze rysowania klikając i przeciągając myszą
* Dostępne są przyciski do czyszczenia rysunku i wyjścia z aplikacji

Poruszone zagadnienia:
* Rysowanie pikseli w Qt za pomocą własnej funkcji `wstawPiksel`
* Implementacja algorytmu rysującego linię
* Obsługa zdarzeń myszy w Qt
* Korzystanie z QImage

## 2. Rysowanie okręgów i elips

Opis:

Projekt pozwala na rysowanie okręgów i elips w aplikacji Qt.

Funkcjonalność:
* Użytkownik może lewym przyciskiem myszy narysować okrąg, a prawym elipsę

Poruszone zagadnienia:
* Implementacja algorytmu rysującego koło
* Implementacja algorytmu rysującego elipsę, z wykorzystaniem wcześniej stworzonej funkcji do rysowania linii

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/2.%20Koło%20Elipsa/demo.gif)


## 3. Krzywe Beziera

Opis:

Ten projekt demonstruje rysowanie krzywej Beziera w aplikacji Qt. 

Funkcjonalność:
* Użytkownik może klikać lewym przyciskiem myszy, aby dodać punkty kontrolne do krzywej.
* Użytkownik może klikać prawym przyciskiem myszy, aby usunąć punkty kontrolne.
* Użytkownik może klikać środkowym przyciskiem myszy, aby przesuwać punkty kontrolne.
* Można wybrać liczbę odcinków, z których składa się krzywa.
* Można włączyć/wyłączyć rysowanie odcinków łączących punkty kontrolne.

Poruszone zagadnienia:
* Implementacja  algorytmu de Casteljau do rysowania krzywej Bezier'a. Algorytm ten dzieli krzywą na mniejsze segmenty i oblicza współrzędne punktów na tych segmentach.

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/2.%20Koło%20Elipsa/demo.gif)