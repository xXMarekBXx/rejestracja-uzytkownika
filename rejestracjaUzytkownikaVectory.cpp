﻿#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>

using namespace std;

struct Uzytkownik
{
	int idUzytkownika;
	string login, haslo;
};

vector<Uzytkownik> odczytUzytkownikowZPliku(vector <Uzytkownik> uzytkownicy) {
		
	cout << "Wczytano dane z pliku" << endl;

	string linia;
	int numerLinii = 1;
	fstream plik;
	Uzytkownik uzytkownik;
	
	plik.open("uzytkownicy.txt", ios::in);
	

	if (plik.is_open()) {
		while (getline(plik, linia)) {
			string Uzytkownik[3];
			int dlugoscLinii = linia.length();
			int beginOfWord = 0;
			int lengthOfWord = 0;
			int numerUzytkownika = 0;

			for (int i = 0; i < dlugoscLinii; i++) {

				if ((int)linia[i] == 124) {
					lengthOfWord = i - beginOfWord;
					Uzytkownik[numerUzytkownika] = linia.substr(beginOfWord, lengthOfWord);
					beginOfWord = i + 1;
					numerUzytkownika++;
				}
			}
			uzytkownik.idUzytkownika = atoi(Uzytkownik[0].c_str());
			uzytkownik.login = Uzytkownik[1];
			uzytkownik.haslo = Uzytkownik[2];
			
			uzytkownicy.push_back(uzytkownik);
		}
		plik.close();
		
		return uzytkownicy;
	}
	else {
		plik.close();
		return uzytkownicy;
	}
	
	system("pause");
}

vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy)
{
	system("cls");
	fstream plik;
	string loginNowegoUzytkownika, haslo;
	Uzytkownik nowyUzytkownik;	
	
	plik.open("uzytkownicy.txt");
	if (plik.good()) {
		plik.close();
	}
	else {
		plik.open("uzytkownicy.txt", ios::out);
		plik.close();
	}

	cout << "Podaj nazwe uzytkownika: ";
	cin >> loginNowegoUzytkownika;

	int i = 0;
	while (i < uzytkownicy.size())
	{
		if (uzytkownicy[i].login == loginNowegoUzytkownika)
		{
			cout << endl;
			cout << "Uzytkownik o takim loginie juz istnieje. Wpisz inny login." << endl;
			cout << endl;
			cout << "Podaj nowa nazwe uzytkownika: ";
			cin >> loginNowegoUzytkownika;
			i = 0;
		}
		else {
			i++;
		}
	}
	cout << endl;
	cout << "Podaj haslo: ";
	cin >> haslo;

	int iloscUzytkownikow = uzytkownicy.size();
	int ostatnieID;
	if (uzytkownicy.empty()) {
		ostatnieID = 0;
	}
	else {
		ostatnieID = uzytkownicy[iloscUzytkownikow - 1].idUzytkownika;
	}

	nowyUzytkownik = { ostatnieID + 1, loginNowegoUzytkownika, haslo };

	uzytkownicy.push_back(nowyUzytkownik);

	plik.open("uzytkownicy.txt", ios::out | ios::app);
	if (plik.good()) {
		plik << uzytkownicy[iloscUzytkownikow].idUzytkownika << "|";
		plik << uzytkownicy[iloscUzytkownikow].login << "|";
		plik << uzytkownicy[iloscUzytkownikow].haslo << "|" << endl;
		cout << endl;
		cout << "Uzytkownik dodany" << endl;
		cout << endl;
		system("Pause");
		return uzytkownicy;
	}
	else {
		cout << "Nie udalo sie otworzyc pliku" << endl;
		system("Pause");
	}
}

int logowanie(vector <Uzytkownik> uzytkownicy)
{
	if (uzytkownicy.empty())
	{
		cout << endl;
		cout << "Nie ma zadnego uzytkownika" << endl;
		cout << endl;
		system("Pause");
		return 0;
	}

	string loginAktualnegoUzytkownika, hasloAktualnegoUzytkownika;

	int liczbaProb = 0;

	cout << endl;
	cout << "Podaj nazwe uzytkownika: ";
	cin >> loginAktualnegoUzytkownika;

	for (int i = 0; i < uzytkownicy.size(); i++)
	{
		if (uzytkownicy[i].login == loginAktualnegoUzytkownika)
		{			
			for (liczbaProb; liczbaProb < 3; liczbaProb++)
			{
				cout << endl;
				cout << "Podaj haslo: ";
				cin >> hasloAktualnegoUzytkownika;
				
				if (uzytkownicy[i].haslo == hasloAktualnegoUzytkownika)
				{
					cout << endl;
					cout << "Zalogowales sie poprawnie" << endl;
					cout << endl;
					system("Pause");
					return uzytkownicy[i].idUzytkownika;
				}

				if (liczbaProb == 2)
				{
					cout << endl;
					cout << "Nie poprawne haslo! " << endl;
					break;
				}

				cout << endl;
				cout << "Nie poprawne haslo! Sprobuj jeszcze raz." << endl;
										
			}

			cout << endl;
			cout << "Za duzo prob! Blokada na 3 sekundy." << endl;
			Sleep(3000);
			return 0;	

		}
	}

	cout << endl;
	cout << "Nie ma uzytkownika z takim loginem" << endl;
	cout << endl;
	system("Pause");
	return 0;	
}

vector<Uzytkownik> usuwanieUzytkownika(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika) {
	
	string wyborUrzytkownika;
	fstream plik;

	plik.open("temp.txt", ios::out);
	if (plik.good()) {

		for (int i = 0; i < uzytkownicy.size(); i++) {
			if (idZalogowanegoUzytkownika == uzytkownicy[i].idUzytkownika) {
				continue;
			}
			else {
				plik << uzytkownicy[i].idUzytkownika << "|";
				plik << uzytkownicy[i].login << "|";
				plik << uzytkownicy[i].haslo << "|" << endl;					
			}
		}

		plik.close();

		remove("uzytkownicy.txt");
		rename("temp.txt", "uzytkownicy.txt");

		int numerZnajomegoDoUsuniecia = 0;
		for (int i = 0; i < uzytkownicy.size(); i++) {
			if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
				numerZnajomegoDoUsuniecia = i;
			}
		}
		uzytkownicy.erase(uzytkownicy.begin() + numerZnajomegoDoUsuniecia);
						
		return uzytkownicy;
	}else {
		plik.close();
		cout << "Blad odczytu pliku!" << endl;
		cout << endl;
		system("Pause");
		return uzytkownicy;
	}
}

vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
	Uzytkownik uzytkownikZNowymHaslem;

	int indexDoEdycji;
	string noweHaslo;
	cout << endl;
	cout << "Podaj nowe haslo: ";
	cin >> noweHaslo;

	for (int i = 0; i < uzytkownicy.size(); i++) {
		if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
			indexDoEdycji = i;
		}
	}
	uzytkownicy[indexDoEdycji].haslo = noweHaslo;

	usuwanieUzytkownika(uzytkownicy, idZalogowanegoUzytkownika);
	
	fstream plik;

	plik.open("uzytkownicy.txt", ios::out | ios::app);
	if (plik.good()) {
		plik << uzytkownicy[indexDoEdycji].idUzytkownika << "|";
		plik << uzytkownicy[indexDoEdycji].login << "|";
		plik << uzytkownicy[indexDoEdycji].haslo << "|" << endl;		
		return uzytkownicy;
	}
	else {
		cout << "Nie udalo sie otworzyc pliku" << endl;
		system("Pause");
	}

	uzytkownicy.push_back(uzytkownikZNowymHaslem);
	   
	cout << endl;
	cout << "Udalo sie zmienic haslo." << endl;
	cout << endl;
	system("Pause");

	return uzytkownicy;
}

int main()
{	
	vector <Uzytkownik> uzytkownicy;

	uzytkownicy = odczytUzytkownikowZPliku(uzytkownicy);

	int idZalogowanegoUzytkownika = 0;
	int iloscUzytkownikow = 0;


	while (true)
	{
		if (idZalogowanegoUzytkownika == 0)
		{
			system("cls");
			cout << "1. Rejestracja" << endl;
			cout << "2. Logowanie" << endl;
			cout << "9. Zakoncz program" << endl;
			cout << endl;
			cout << "Twoj wybor: " << endl;

			int wybor;
			cin >> wybor;

			switch (wybor)
			{
			case 1:				
				uzytkownicy = rejestracja(uzytkownicy);
				break;
			case 2:				
				idZalogowanegoUzytkownika = logowanie(uzytkownicy);
				break;
			case 9:
				exit(0);
			}
		}
		else
		{
			system("cls");
			cout << "1. Zmiana hasla" << endl;
			cout << "2. Wylogowanie" << endl;
			cout << endl;
			cout << "Twoj wybor: " << endl;

			int wybor;
			cin >> wybor;

			switch (wybor)
			{
			case 1:				
				uzytkownicy = zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
				break;
			case 2:
				idZalogowanegoUzytkownika = 0;
				break;
			}
		}
	}
}
