Projekt MRÓWKA LANGTONA (LANGTON'S ANT)
Program został napisany w języku C.
KOMPILACJA
Można go skompilować poleceniem "make" korzystającym z pliku "Makefile". Polecenie to stworzy dodatkowo folder "boards" w którym zostaną zapisane wygenerowane plansze.

WYWOŁYWANIE
Po kompilacji program można wywołać poleceniem "./main.out". Do jego działania potrzebne są jednak parametry:
-m - ilość wiersz planszy
-n - ilość kolumn
-i - ilosc iteracji mrówki
-k - kierunek początkowy mrówki (0 - góra, 1 - prawo, 2 dół, 3 - lewo)

--name - opcjonalny argument zawierający nazwe plików planszy. Jego brak powoduje że plansze są wyświetlane na standardowym wyjściu
-s - opcjonalny argument zawierający liczbę informującą co która plansza ma być zapisywana. Np dla liczby 2 wyświetlone zostaną iteracje 0, 2, 4 itd. Ostatnia plansza zawsze będzie wyświetlona nawet jeśli nie bedzie podzielna przez wartość s. Wartość 0 powoduje że zostanie wyświetlona tylko 1 i ostatnia plansza.
-g - specialny parametr generujący plik planszy który można wgrać jako pierwsza plansze. Trzeba podać liczbe całkowitą z przedziału 1 do 100 informującą o stopnu zapełnienia planszy przez czarne pola. Parametr ten zmienia wymagane parametry na --name (nazwa pliku planszy), -m  i -n
-w - specialny parametr wczytujący jako pierwszą plansze podany plik. Należy po parametrze podać nazwe pliku jaki zawiera plansze. Zmienia wymagane parametry na -i i -k.
