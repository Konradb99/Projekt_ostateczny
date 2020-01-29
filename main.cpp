#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
using namespace std;
// ZMIENNE MENU
int opcja_menu{};
string napis = "                            _                     _               \n                           (_)                   | |              \n ___ _ __   __ _  ___ ___   _ _ ____   ____ _  __| | ___ _ __ ___ \n/ __| '_ \\ / _` |/ __/ _ \\ | | '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|\n\\__ \\ |_) | (_| | (_|  __/ | | | | \\ V / (_| | (_| |  __/ |  \\__ \\\n|___/ .__/ \\__,_|\\___\\___| |_|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/\n    | |                                                         \n    |_|                                                         \n\n\n";
int opcja_zapis{};
//ZMIENNE GRY
int gracz_x = 21;
int gracz_y = 45;
int pocisk_x[100]{};
int pocisk_y[100]{};
int przeciwnik_x[15]{};
int przeciwnik_y[15]{};
int nr_strzalu{};
int cykl_przeciwnicy{};
int cykl_przeciwnicy2{};
int punkty{};
int zycie_gracz = 100;
int zycie_baza = 100;
int ilosc_przeciwnikow = 15;
int runda{};
string plansza[50];
char plansza_wspolrzedne[60][40]{};
enum Kierunki_gracz { STOP = 0, LEWO, PRAWO };
Kierunki_gracz kierunek;
Kierunki_gracz ostatni_kierunek;
int boss_rdzen_1_x{};
int boss_rdzen_1_y{};
int boss_rdzen_2_x{};
int boss_rdzen_2_y{};
int boss_ramie_lewe_x{};
int boss_ramie_lewe_y{};
int boss_ramie_prawe_x{};
int boss_ramie_prawe_y{};
int zycie_boss = 30;
string nick;
//ZMIENNE LOGICZNE
bool czy_menu = true;
bool gameOver = false;
bool czy_boss = false;
bool czy_pokonany = false;
bool trafiony = false;
bool czy_zapis = true;
//				DEKLARACJE FUNKCJI
//FUNKCJE MENU
void menu();
void wybor();
void czyszczenie();
void wejscie_menu();
void instrukcja();
void wyniki();
//FUNKCJE GRY
void gra();
void nowy_nick();
void Odczyt_klawiatura();
void ruch_postaci();
void ustawienie_gry();
void ustawienie_planszy();
void rysowanie_planszy();
void Generuj_plansze();
void ruch_pociskow();
void ruch_przeciwnikow();
void sprawdzenie_trafien();
void reset_rundy();
void koniec_gry();
void Boss();
void wczytanie_gry();
void zapis_gry();
void wybor_zapis();
void zapis_menu();
void zapis();
void zapis_ranking();
//FUNKCJA GLOWNA
int main() {
	do {
		if (gameOver) {
			system("cls");
			gameOver = false;
		}
		czyszczenie();
		wejscie_menu();
		menu();
	} while (czy_menu);
}
//				FUNKCJE
//FUNKCJE MENU
void menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << napis;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	wybor();
}
void wejscie_menu() {
	if (_kbhit()) {
		switch (_getch()) {
		case 72:
			if (opcja_menu > 0) {
				opcja_menu--;
			}
			break;
		case 80:
			if (opcja_menu < 4) {
				opcja_menu++;
			}
			break;
		case 13:
			switch (opcja_menu) {
			case 0:
				gra();
				break;
			case 1:
				gra();
				break;
			case 2:
				wyniki();
				break;
			case 3:
				instrukcja();
				break;
			case 4:
				czy_menu = false;
				break;
			}
		}
	}
}
void wybor() {
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			if(opcja_menu==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                 Nowa Gra                                 \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == 1) {
			if (opcja_menu == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                               Wczytaj Gre                                \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == 2) {
			if (opcja_menu == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                  Wyniki                             \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == 3) {
			if (opcja_menu == 3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                Instrukcja                         \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == 4) {
			if (opcja_menu == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                  Koniec                            \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}
void instrukcja() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << napis;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	
	cout << "        Gra polega na odpieraniu fal kolejnych przeciwnikow\n            Poruszanie statkiem: A - lewo    D - prawo \n                    Strzelanie jest pod spacja\n            Okno konsoli powinno miec wymiar 80px na 65px";

	cout << "\n\n                  Nacisnij enter aby kontynuowac";
	cin.ignore();
	system("cls");
}
void wyniki() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << napis;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//ZLICZANIE ILOSCI WIERSZY W PLIKU WYNIKOWYM
	fstream wyniki;
	string wiersze;
	int wiersze_wyniki{};
	wyniki.open("wyniki.txt", ios::in);
	if (wyniki.is_open()) {
		while (!wyniki.eof()) {
			getline(wyniki, wiersze);
			wiersze_wyniki++;
		};
	}
	wyniki.close();
	string* nick = new string[wiersze_wyniki];
	string nick_1;
	string wynik_1;
	double* wynik = new double[wiersze_wyniki]{};
	//WPISANIE WSZYSTKICH WYNIKOW DO TABLICY
	int i_wyniki = 0;
	wyniki.open("wyniki.txt", ios::in);
	if (wyniki.is_open()) {
		while(!wyniki.eof()) {
			wyniki >> nick_1;
			wyniki >> wynik_1;
			nick[i_wyniki] = nick_1;
			wynik[i_wyniki] = stod(wynik_1);
			i_wyniki++;
		};
	}
	else cout << "Nie udalo sie otworzyc";
	//SORTOWANIE WYNIKOW OD NAJLEPSZEGO
	for (int i = 0; i < wiersze_wyniki - 1; i++)
		for (int j = 0; j < wiersze_wyniki - 1; j++)
			if (wynik[j] < wynik[j + 1]) {
				swap(wynik[j], wynik[j + 1]);
				swap(nick[j], nick[j + 1]);
			}
	//WYPISANIE 10 NAJLEPSZYCH WYNIKOW
	if (wiersze_wyniki < 10) {
		for (int i = 0; i < wiersze_wyniki; i++) {
			cout.width(20);
			cout << nick[i] << "\t";
			cout << wynik[i] << "\n";
		}
	}
	else if (wiersze_wyniki > 10) {
		for (int i = 0; i < 10; i++) {
			cout.width(20);
			cout << nick[i] << "\t";
			cout << wynik[i] << "\n";
		}
	}
	cout << "\n\n                  Nacisnij enter aby kontynuowac";
	cin.ignore();
	system("cls");
	delete[] nick;
	delete[] wynik;
}
void czyszczenie() {
	COORD poczatek;				// USTAWIENIE ZMIENNEJ Z WSPOLRZEDNYMI RAMKI EKRANU
	poczatek.X = 0;				// WSPOLRZEDNA X RAMKI
	poczatek.Y = 0; 			// WSPOLRZEDNA Y RAMKI
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), poczatek);	//USTAWIENIE KURSOWA NA POCZATKU RAMKI -> nadpisuje ramke zamiast czyscic i pisac od nowa
}
//FUNKCJE GRY
void gra() {
	gameOver = false;
	switch (opcja_menu) {
	case 0:
		nowy_nick();
		ustawienie_gry();
		break;
	case 1:
		wczytanie_gry();
	}
	system("cls");
	do {
		czyszczenie();
		Odczyt_klawiatura();
		ruch_postaci();
		ruch_pociskow();
		ruch_przeciwnikow();
		sprawdzenie_trafien();
		reset_rundy();
		ustawienie_planszy();
		Generuj_plansze();
		rysowanie_planszy();
		koniec_gry();
		Sleep(50);
	} while (!gameOver);
}
void ustawienie_gry() {
	czy_zapis = true;
	gracz_x = 21;
	gracz_y = 45;
	kierunek = STOP;
	ostatni_kierunek = STOP;
	runda = 1;
	zycie_gracz = 100;
	zycie_baza = 100;
	zycie_boss = 30;
	punkty = 0;
	cykl_przeciwnicy = 0;
	cykl_przeciwnicy2 = 0;
	for (int i = 0; i < 100; i++) {
		pocisk_x[i] = -100;
		pocisk_y[i] = -100;
	}
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 40; x++) {
			plansza_wspolrzedne[y][x] = ' ';
		}
	}
	int x{}, x1{};
	//USTAWIENIE WSPOLRZEDNYCH STARTOWYCH PRZECIWNIKOW
	for (int i = 0; i < 15; i++) {
		if (i < 8) {
			przeciwnik_y[i] = 5;
			przeciwnik_x[i] = 3 + x;
			x += 4;
		}
		else if (i >= 8 && i < 15) {
			przeciwnik_y[i] = 7;
			przeciwnik_x[i] = 5 + x1;
			x1 += 4;
		}
	}
	int boss_rdzen_1_x = -10000;
	int boss_rdzen_1_y = -10000;
	int boss_rdzen_2_x = -10000;
	int boss_rdzen_2_y = -10000;
	int boss_ramie_lewe_x = -10000;
	int boss_ramie_lewe_y = -10000;
	int boss_ramie_prawe_x = -10000;
	int boss_ramie_prawe_y = -10000;
}
void Odczyt_klawiatura() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'A':
			kierunek = LEWO;
			ostatni_kierunek = LEWO;
			break;
		case 'a':
			kierunek = LEWO;
			ostatni_kierunek = LEWO;
			break;
		case 'D':
			kierunek = PRAWO;
			ostatni_kierunek = PRAWO;
			break;
		case 'd':
			kierunek = PRAWO;
			ostatni_kierunek = PRAWO;
			break;
		case 75:
			kierunek = LEWO;
			ostatni_kierunek = LEWO;
			break;
		case 77:
			kierunek = PRAWO;
			ostatni_kierunek = PRAWO;
			break;
		
		case ' ':
			pocisk_y[nr_strzalu] = gracz_y;
			pocisk_x[nr_strzalu] = gracz_x;
			if (nr_strzalu >= 99) {
				nr_strzalu = 0;
			}
			else {
				nr_strzalu++;
			}
			kierunek = ostatni_kierunek;
			Beep(600, 45);
			break;
		case 27:
			zapis_gry();
			gameOver = true;
			system("cls");
			break;
		default:
			kierunek = STOP;
			ostatni_kierunek = STOP;
			break;
		}
	}
}
void ruch_postaci() {
	switch (kierunek) {
	case LEWO:
		if (gracz_x > 0) {
			gracz_x--;
		}
		else {
			kierunek = STOP;
			ostatni_kierunek = STOP;
		}
		break;
	case PRAWO:
		if (gracz_x < 39) {
			gracz_x++;
		}
		else {
		kierunek = STOP;
		ostatni_kierunek = STOP;
		}
		break;
	}
}
void ustawienie_planszy(){
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 40; x++) {
			if (x == gracz_x && y == gracz_y) {
				plansza_wspolrzedne[y][x] = char(219);
			}
			else plansza_wspolrzedne[y][x] = ' ';
			for (int i = 0; i < 100; i++) {
				if (x == pocisk_x[i] && y == pocisk_y[i]) {
					plansza_wspolrzedne[y][x] = '^';
				}
			}
			for (int i = 0; i < 15; i++) {
				if (x == przeciwnik_x[i] && y == przeciwnik_y[i]) {
					plansza_wspolrzedne[y][x] = 'V';
				}
			}
			if (runda % 10 == 0) {
				if (y == 3) {
					if (x > 4 && x < 4+zycie_boss) {
						plansza_wspolrzedne[y][x] = char(219);
					}
					else plansza_wspolrzedne[y][x] = ' ';
				}
				if (boss_rdzen_1_x == x && boss_rdzen_1_y == y) {
					plansza_wspolrzedne[y][x] = char(219);
				}
				else if (boss_rdzen_2_x == x && boss_rdzen_2_y == y) {
					plansza_wspolrzedne[y][x] = char(219);
				}
				else if (boss_ramie_lewe_x == x && boss_ramie_lewe_y == y) {
					plansza_wspolrzedne[y][x] = char(223);
				}
				else if (boss_ramie_prawe_x == x && boss_ramie_prawe_y == y) {
					plansza_wspolrzedne[y][x] = char(223);
				}
			}
		}
	}
}
void Generuj_plansze() {
	for (int i = 0; i < 50; i++) {
		plansza[i].clear();
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 40; j++) {
			plansza[i] += plansza_wspolrzedne[i][j];
		}
	}
}
void rysowanie_planszy() {
	for (int i = 0; i < 42; i++) {
		cout << char(219);
	}
	cout << "\n";
	for (int i = 0; i < 50; i++) {
		cout << char(219) << plansza[i] << char(219);
		if (i == 20) {
			cout << "\t Punkty: " << punkty;
		}
		else if (i == 10) {
			cout << "\t Runda: ";
			cout.width(3);
			cout << runda;
		}
		else if (i == 30) {
			cout.width(10);
			cout << "\t Zycie Gracza: ";
			cout.width(3);
			cout << zycie_gracz;
			cout << " / 100";
		}
		else if (i == 40) {
			cout << "\t Zycie Bazy: ";
			cout.width(3);
			cout << zycie_baza;
			cout << " / 100";
		}
		cout << endl;
	}
	for (int i = 0; i < 42; i++) {
		cout << char(219);
	}
	cout << endl;
}
void ruch_pociskow() {
	for (int i = 0; i < 100; i++) {
		if (pocisk_y[i] > 0) {
			pocisk_y[i]--;
		}
		else pocisk_y[i] = -100;
	}
}
void ruch_przeciwnikow() {
	if (cykl_przeciwnicy % 20 == 0 && cykl_przeciwnicy != 0) {
		for (int i = 0; i < 15; i++) {
			if (cykl_przeciwnicy2 % 20 == 0 && cykl_przeciwnicy2 % 40 != 0 && cykl_przeciwnicy2 != 0) {
				przeciwnik_x[i] += 4;
			}
			else if (cykl_przeciwnicy2 % 40 == 0 && cykl_przeciwnicy2 != 0) {
				przeciwnik_x[i] -= 4;
			}
			przeciwnik_y[i] += 2;
		}
	}
	if (runda % 10 == 0) {
		if (cykl_przeciwnicy % 20 == 0 && cykl_przeciwnicy != 0) {
			if (cykl_przeciwnicy2 % 20 == 0 && cykl_przeciwnicy2 % 40 != 0 && cykl_przeciwnicy2 == 20) {
				boss_ramie_lewe_x += 4;
				boss_rdzen_1_x += 4;
				boss_rdzen_2_x += 4;
				boss_ramie_prawe_x += 4;
			}
			else if (cykl_przeciwnicy2 % 20 == 0 && cykl_przeciwnicy2 % 40 != 0 && cykl_przeciwnicy2 != 0) {
				boss_ramie_lewe_x += 8;
				boss_rdzen_1_x += 8;
				boss_rdzen_2_x += 8;
				boss_ramie_prawe_x += 8;
			}
			else if (cykl_przeciwnicy2 % 40 == 0 && cykl_przeciwnicy2 != 0) {
				boss_ramie_lewe_x -= 8;
				boss_rdzen_1_x -= 8;
				boss_rdzen_2_x -= 8;
				boss_ramie_prawe_x -= 8;
			}
			boss_ramie_lewe_y += 1;
			boss_rdzen_1_y += 1;
			boss_rdzen_2_y += 1;
			boss_ramie_prawe_y += 1;
		}
	}
	cykl_przeciwnicy2++;
	cykl_przeciwnicy++;
}
void sprawdzenie_trafien() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 15; j++) {
			if (pocisk_x[i] == przeciwnik_x[j] && pocisk_y[i] == przeciwnik_y[j]) {
				przeciwnik_y[j] = -1000;
				przeciwnik_x[j] = -1000;
				punkty++;
				ilosc_przeciwnikow -= 1;
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		if (przeciwnik_x[i] == gracz_x && przeciwnik_y[i] == gracz_y) {
			przeciwnik_y[i] = -1000;
			przeciwnik_x[i] = -1000;
			punkty++;
			zycie_gracz--;
			ilosc_przeciwnikow -= 1;
		}
	}
	for (int i = 0; i < 15; i++) {
		if (przeciwnik_y[i] >= 50) {
			przeciwnik_y[i] = -1000;
			przeciwnik_x[i] = -1000;
			zycie_baza-=2;
			ilosc_przeciwnikow -= 1;
		}
	}
	if (runda % 10 == 0) {
		for (int i = 0; i < 100; i++) {
			if (boss_rdzen_1_x == pocisk_x[i] && boss_rdzen_1_y == pocisk_y[i]) {
				zycie_boss -= 2;
				pocisk_x[i] = -1000;
				pocisk_y[i] = -1000;
			}
			if (boss_rdzen_2_x == pocisk_x[i] && boss_rdzen_2_y == pocisk_y[i]) {
				zycie_boss -= 2;
				pocisk_x[i] = -1000;
				pocisk_y[i] = -1000;
			}
			if (boss_ramie_lewe_x == pocisk_x[i] && boss_ramie_lewe_y == pocisk_y[i]) {
				zycie_boss -= 2;
				pocisk_x[i] = -1000;
				pocisk_y[i] = -1000;
			}
			if (boss_ramie_prawe_x == pocisk_x[i] && boss_ramie_prawe_y == pocisk_y[i]) {
				zycie_boss -= 2;
				pocisk_x[i] = -1000;
				pocisk_y[i] = -1000;
			}
		}
		if (boss_rdzen_1_x == gracz_x && boss_rdzen_1_y == gracz_y) {
			if (!trafiony) {
				zycie_gracz -= 10;
				trafiony = true;
			}
		}
		if (boss_rdzen_2_x == gracz_x && boss_rdzen_2_y == gracz_y) {
			if(!trafiony) {
				zycie_gracz -= 10;
				trafiony = true;
			}
		}
		if (boss_ramie_lewe_x == gracz_x && boss_ramie_lewe_y == gracz_y) {
			if (!trafiony) {
				zycie_gracz -= 10;
				trafiony = true;
			}
		}
		if (boss_ramie_prawe_x == gracz_x && boss_ramie_prawe_y == gracz_y) {
			if (!trafiony) {
				zycie_gracz -= 10;
				trafiony = true;
			}
		}
		if (zycie_boss < 0) {
			punkty += 15;
			czy_pokonany = true;
			reset_rundy();
		}
		if (boss_rdzen_1_y >= 50) {
			gameOver = true;
			system("cls");
		}
		if (boss_rdzen_2_y >= 50) {
			gameOver = true;
			system("cls");
		}
		if (boss_ramie_lewe_y >= 50) {
			gameOver = true;
			system("cls");
		}
		if (boss_ramie_prawe_y >= 50) {
			gameOver = true;
			system("cls");
		}
	}
}
void reset_rundy() {
	if (ilosc_przeciwnikow <= 0 && runda % 10 != 0 ) {
		cykl_przeciwnicy = 0;
		cykl_przeciwnicy2 = 0;
		int x{}, x1{};
		for (int i = 0; i < 15; i++) {
			if (i < 8) {
				przeciwnik_y[i] = 5;
				przeciwnik_x[i] = 5 + x;
				x += 4;
			}
			else if (i >= 8 && i < 15) {
				przeciwnik_y[i] = 7;
				przeciwnik_x[i] = 7 + x1;
				x1 += 4;
			}
		}
		runda++;
		ilosc_przeciwnikow = 15;
	}
	else if (runda % 10 == 0 && !czy_boss) {
		Boss();
		czy_boss = true;
	}
	else if (runda % 10 == 0 && czy_boss) {
		if (czy_pokonany) {
			cykl_przeciwnicy = 0;
			cykl_przeciwnicy2 = 0;
			int x{}, x1{};
			for (int i = 0; i < 15; i++) {
				if (i < 8) {
					przeciwnik_y[i] = 5;
					przeciwnik_x[i] = 5 + x;
					x += 4;
				}
				else if (i >= 8 && i < 15) {
					przeciwnik_y[i] = 7;
					przeciwnik_x[i] = 7 + x1;
					x1 += 4;
				}
			}
			runda++;
			ilosc_przeciwnikow = 15;
			czy_boss = false;
			czy_pokonany = false;
			trafiony = false;
		}
	}
}
void koniec_gry() {
	if (zycie_gracz <= 0 || zycie_baza <= 0) {
		gameOver = true;	
		system("cls");
	}
}
void Boss() {
	for (int i = 0; i < 15; i++) {
		przeciwnik_x[i] = -100;
		przeciwnik_y[i] = -100;
	}
	boss_ramie_lewe_x = 19;
	boss_ramie_lewe_y = 5;
	boss_rdzen_1_x = 20;
	boss_rdzen_1_y = 5;
	boss_rdzen_2_x = 21;
	boss_rdzen_2_y = 5;
	boss_ramie_prawe_x = 22;
	boss_ramie_prawe_y = 5;
	czy_boss = true;
}
void wczytanie_gry() {
	fstream zapis;
	zapis.open("zapis.txt", ios::in);
	//PLIK MA FORMAT:
	//NICK		RUNDA		ZYCIE GRACZA		ZYCIE BAZY		PUNKTY
	if (zapis.is_open()) {
		zapis >> nick;
		zapis >> runda;
		zapis >> zycie_gracz;
		zapis >> zycie_baza;
		zapis >> punkty;
	}
	zapis.close();
	gracz_x = 21;
	gracz_y = 45;
	kierunek = STOP;
	ostatni_kierunek = STOP;
	cykl_przeciwnicy = 0;
	cykl_przeciwnicy2 = 0;
	for (int i = 0; i < 100; i++) {
		pocisk_x[i] = -100;
		pocisk_y[i] = -100;
	}
	int x{}, x1{};
	for (int i = 0; i < 15; i++) {
		if (i < 8) {
			przeciwnik_y[i] = 5;
			przeciwnik_x[i] = 3 + x;
			x += 4;
		}
		else if (i >= 8 && i < 15) {
			przeciwnik_y[i] = 7;
			przeciwnik_x[i] = 5 + x1;
			x1 += 4;
		}
	}
	int boss_rdzen_1_x = -10000;
	int boss_rdzen_1_y = -10000;
	int boss_rdzen_2_x = -10000;
	int boss_rdzen_2_y = -10000;
	int boss_ramie_lewe_x = -10000;
	int boss_ramie_lewe_y = -10000;
	int boss_ramie_prawe_x = -10000;
	int boss_ramie_prawe_y = -10000;
	czy_zapis = true;
}
void zapis_gry() {
	system("cls");
	do {
		czyszczenie();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << napis;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "                       Czy chcesz zapisac gre?\n\n";
		wybor_zapis();
		zapis_menu();
	} while (czy_zapis);
}
void wybor_zapis() {
	if (_kbhit()) {
		switch (_getch()) {
		case 72:
			if (opcja_zapis > 0) {
				opcja_zapis--;
			}
			break;
		case 80:
			if (opcja_zapis < 2) {
				opcja_zapis++;
			}
			break;
		case 13:
			switch (opcja_zapis) {
			case 0:
				zapis();
				break;
			case 1:
				zapis_ranking();
				czy_zapis = false;
				gameOver = true;
				system("cls");
				break;
			}
		}
	}
}
void zapis_menu() {
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			if (opcja_zapis == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                 TAK\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == 1) {
			if (opcja_zapis == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "                                 NIE\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}
void zapis() {
	fstream zapis;
	zapis.open("zapis.txt", ios::out);
	//PLIK MA FORMAT:
	//NICK		RUNDA		ZYCIE GRACZA		ZYCIE BAZY		PUNKTY
	if (zapis.is_open()) {
		zapis << nick;
		zapis << "\t";
		zapis << runda;
		zapis << "\t";
		zapis << zycie_gracz;
		zapis << "\t";
		zapis << zycie_baza;
		zapis << "\t";
		zapis << punkty;
	}
	czy_zapis = false;
	gameOver = true;
	system("cls");
}
void zapis_ranking() {
	fstream zapis;
	zapis.open("wyniki.txt", ios::app);
	//PLIK MA FORMAT:
	//NICK		PUNKTY
	if (zapis.is_open()) {
		zapis << "\n";
		if (nick != "") {
			zapis << nick;
		}	
		else zapis << "unknown";
		zapis << "\t";
		zapis << punkty;

	}
	czy_zapis = false;
	gameOver = true;
	system("cls");
}
void nowy_nick() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << napis;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "\n\nPodaj swoj nick ( maksymalnie 10 znakow ): ";
	getline(cin, nick);
}
