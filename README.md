
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

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/3.%20Krzywe%20Beziera/demo.gif)

## 4. Krzywe B-sklejane

Opis:

Ten projekt demonstruje rysowanie krzywych B-spline w aplikacji Qt.

Funkcjonalność:
* Dodawanie punktów kontrolnych: Kliknięcie lewym przyciskiem myszy w dowolnym miejscu okna aplikacji.
* Usuwanie punktów kontrolnych: Kliknięcie prawym przyciskiem myszy na punkt kontrolny.
* Przesuwanie punktów kontrolnych: Kliknięcie środkowym przyciskiem myszy na punkt kontrolny i przeciąganie myszą.
* Zmiana liczby odcinków: Przesuwanie suwaka.
* Włączanie/wyłączenie rysowania odcinków łączących punkty kontrolne: Kliknięcie przycisku "Pokaż odcinki".



![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/4.%20B-Sklejane/demo.gif)

## 5. Flood Fill

Opis:
Ten projekt demonstruje algorytm Flood Fill, zaimplementowany w aplikacji graficznej Qt. Użytkownik może rysować linie i koła na obrazie, a także wypełniać obszary kolorem za pomocą funkcji Flood Fill.

Funkcjonalność:
* Rysowanie linii: Lewy przycisk myszy + przeciąganie myszy
* Rysowanie koła: Środkowy przycisk myszy + przeciąganie myszy
* Wypełnianie kolorem: Kliknięcie prawym przyciskiem myszy

Poruszone zagadnienia:
* Implementacja algorytmu Flood Fill

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/5.%20Flood%20fill/demo.gif)

## 6. Scan Line

Opis:
Ten projekt demonstruje algorytm Scan Line, zaimplementowany w aplikacji graficznej Qt. Użytkownik może rysować linie i koła na obrazie, a także wypełniać obszary kolorem za pomocą funkcji Scan Line.
Reszta analogicznie jak w projekcie Flood Fill.

## 7. Modele barw

Opis:
Ten projekt prezentuje implementację modeli barw RGB i HSV w aplikacji graficznej Qt. Użytkownik może sterować kolorami pikseli na 
obrazie za pomocą suwaków, które regulują wartości składowych RGB lub parametrów HSV.

Rysowanie sześcianów barw: Do rysowania sześcianów barwnych używana jest funkcja `rysujSzescian`, która przyjmuje jako argumenty wartości RGB lub HSV. Funkcja oblicza kolory pikseli na podstawie położenia piksela w sześcianie i rysuje je na obrazie.
Konwersja między modelami barw: Do konwersji między modelami RGB i HSV wykorzystywana jest funkcja `HSVtRGB` i `RGBtHSV`. Funkcje te opierają się na standardowych wzorach matematycznych.

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/7.%20Modele%20barw/demo.gif)


## 8. Alpha blending

Opis:
Ten projekt prezentuje implementację algorytmu Alpha Blending w aplikacji graficznej Qt. Użytkownik może blendować ze sobą kilka obrazów jednocześnie, regulując wartość współczynnika alpha oraz wybierając tryb mieszania kolorów.

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/8.%20Alpha%20blending/demo.gif)


## 9. Operacje morfologiczne

Opis:
Projekt ten implementuje aplikację graficzną, która pozwala użytkownikowi na wykonywanie operacji morfologicznych na obrazach. Aplikacja posiada takie funkcje jak dylatacja, erozja, domknięcie i otwarcie.

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/9.%20Operacje%20morfologiczne/demo.gif)

## 10. Przekształcenia geometryczne 2D

Opis:
Projekt ten implementuje aplikację graficzną, która pozwala użytkownikowi na wykonywanie przekształceń geometrycznych 2D na obrazku.

Funkcjonalność:
* Translacja: Umożliwia przesuwanie obrazu w poziomie i pionie za pomocą dwóch suwaków reprezentujących przesunięcie w osiach X i Y.
* Skalowanie: Umożliwia zmianę rozmiaru obrazu za pomocą suwaków reprezentujących skalowanie w osiach X i Y.
* Obrót: Umożliwia obracanie obrazu o dowolny kąt za pomocą suwaka.
* Pochylenie: Funkcja pochylenia obrazu w osiach X i Y.
* Interpolacja Dwuliniowa: Opcja wyboru interpolacji dwuliniowej, która poprawia jakość obrazu po przekształceniach.

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/10.%20Przekształcenia%20geometryczne%202D/demo.gif)

## 11. Teksturowanie trójkątów

Opis:
Projekt ten implementuje aplikację graficzną, która pozwala użytkownikowi na narysowanie trójkąta, a następnie nałożenie na niego tekstury. 

![Demo](https://github.com/yaspktor/Grafika-Komputerowa/blob/main/10.%20Teksturowanie%20trójkątów/demo.gif)