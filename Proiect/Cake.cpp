#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <Windows.h>

using namespace std;

class reteta  {
protected:
	string _nume;
	int _nr_minute;
public:
	reteta(string nume, int minute) 
	{
		this->_nume = nume;
		this->_nr_minute = minute;
	}

	int GetMinute() {
		return _nr_minute;
	}
};

class prajitura {
	string _nume;
	reteta* ret;
public:
	prajitura(string nume, reteta* ret) {
		this->_nume = nume;
		this->ret = ret;
	}
	
	void afisare_nume_prajitura()
	{
		cout << endl;
		cout << "Numele prajiturii: " << _nume << endl;
	}

	string GetNume() {
		return _nume;
	}
};



class prajitura_obisnuita : public prajitura
{
public:
	prajitura_obisnuita(string nume, reteta* r) : prajitura(nume, r) {}

};

class prajitura_diabetici : public prajitura
{
private:
	int cant_zahar;
public:
	prajitura_diabetici(string nume, reteta* r, int cant_zahar) : prajitura(nume, r)
	{
		this->cant_zahar = cant_zahar;
	}
};

void AdaugarePrajituraPosibile(list<prajitura*>& prajituri, list<reteta*>&retete) {

	string nume_prajitura, nume_reteta;
	int nr_prajituri, minute;
	reteta* r;
	ofstream fout("retete_posibile.txt");

	cout << "Nr de prajituri: "; cin >> nr_prajituri;
	for (int i = 0; i < nr_prajituri; i++)
	{
		cout << "Dati numele: "; cin >> nume_prajitura;
		cout << "Reteta: "; cin >> nume_reteta;
		cout << "Nr de minute: "; cin >> minute;
		fout << "Prajitura: " << nume_prajitura << " " << "Reteta: " << nume_reteta << " " << "Minute: " << minute << endl;
	}

	prajitura* p = new prajitura(nume_prajitura, r);
	prajituri.push_back(p);

	reteta* r = new reteta(nume_reteta, minute);
	retete.push_back(r);
}

void AfisareFisierPosibile() {

	ifstream fin("retete_posibile.txt");
	string linie_fisier;

	while (getline(fin, linie_fisier))
	{
		cout << linie_fisier << endl;
	}
}

void AdaugareDepozit() {

	ofstream fout("depozit.txt", ios::app);
	string nume;
	int stoc;

	cout << "Prajitura: "; cin >> nume;
	cout << "Stoc: "; cin >> stoc;
	fout << "Prajitura: " << nume << " " << "Stoc: " << stoc << endl;
}

void AdaugareDepozitComanda(string cautat, int stoc)
{
	ofstream fout("depozit.txt", ios::app);
	if (fout.is_open())
	{
		fout << "Prajitura: " << cautat << " " << "Stoc: " << stoc << endl;
	}
	fout.close();
}

void AfisareDepozit() {

	ifstream fis("depozit.txt");
	string linie_fisier;

	while (getline(fis, linie_fisier))
		{
			cout << linie_fisier << endl;
		}
}

void VerificareStoc() {
	ifstream fin("depozit.txt");
	string linie_fisier;

	int stoc = 0, stoc_prajituri;
	char c;
	string nume, cautat;
	cout << "Prajitura dorita: "; cin >> cautat; cout << endl;
	while (fin.get(c)) {
		 
		if (c == cautat[nume.size()]) {
			nume += c;
		}
		else {
			nume.clear();
		}

		if (nume == cautat) {
			stoc++;
			cout << "Prajitura dumneavoastra: " << cautat << endl;
			break;
		}
	}
	if (stoc == 0) {
		cout << "Nu este in stoc. Asteptati pentru livrare" << endl;
		Sleep(3000);
		cout << "Prajitura dumneavoastra: " << cautat << endl;
		stoc = 1;
		AdaugareDepozitComanda(cautat, stoc);
	}
}

int main() {
	int opt;
	list<prajitura*> prajituri;
	list<reteta*> retete;

	//AdaugarePrajituraPosibile(prajituri, retete);
	//AdaugareDepozit();

	do {
		cout << "Panou de comanda " << endl;
		cout << "1. Afisare prajituri disponibile " << endl;
		cout << "2. Selecteaza prajitura" << endl;
		cout << "3. Afisare prajituri existente" << endl;
		cout << "4. Exit" << endl;
		cout << "Alegeti optiunea dorita: "; cin >> opt; cout << endl;

		switch (opt)
		{

		case 1: AfisareFisierPosibile(); cout << endl;
			break;
		case 2: VerificareStoc(); cout << endl;
			break;
		case 3: AfisareDepozit(); cout << endl;
			break;
		case 4:
			exit(4);
			break;
		}
	} while (opt != 0);

	return 0;
}