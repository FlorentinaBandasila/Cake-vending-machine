#include<iostream>
#include<string>
#include<conio.h>
#include<list>

using namespace std;



class reteta
{
	string nume;
	float timp;


public:
	reteta() {};
	reteta(string nume, float timp);
	string getNume();
	float getTimp();
};

reteta::reteta(string nume, float timp) {
	this->nume = nume;
	this->timp = timp;
}

string reteta::getNume()
{
	return nume;
}

float reteta::getTimp()
{
	return timp;
}


class prajitura {

	string nume;

public:
	prajitura();
	prajitura(string nume);
	string getNume();
};

prajitura::prajitura() {
	this->nume = "";
}

prajitura::prajitura(string nume) {
	this->nume = nume;
}

string prajitura::getNume() {
	return nume;
}

class prep_prajitura
{
public:

	prep_prajitura();
	prajitura preia_comanda(reteta* reteta_prajitura);

};

prep_prajitura::prep_prajitura() {}

prajitura prep_prajitura::preia_comanda(reteta* reteta_prajitura) {
	prajitura* p = new prajitura(reteta_prajitura->getNume());
	cout << "Comanda" << reteta_prajitura->getNume() << "va fi gata in" << reteta_prajitura->getTimp() << "timp" << endl;
	return (*p);
}

class dep_praj
{
	prajitura* depozit[12];
	unsigned int cap_max = 12;
	unsigned int cap_min = 3;
public:
	dep_praj();
	bool addPrajitura(prajitura prajitura);
	prajitura getPrajitura(string nume);
	int getCap_curenta();
	void getPraj_din_depozit(prajitura p);
};

dep_praj::dep_praj() {
	for (int i = 0; i < cap_max; i++)
	{
		depozit[i] = nullptr;
	}
}

bool dep_praj::addPrajitura(prajitura prajitura1)
{
	for (int j = 0; j < cap_max; j++)
	{
		depozit[j] = new prajitura(prajitura1.getNume());
		return 1;
	}
	return 0;
}

prajitura dep_praj::getPrajitura(string nume)
{
	int i;
	for (i = 0; i < cap_max; i++)
	{
		if (depozit[i] != nullptr)
		{
			if ((*depozit[i]).getNume().compare(nume) != 1)
			{
				prajitura preia_prajitura = *depozit[i];
				delete depozit[i];
				depozit[i] = nullptr;
				return preia_prajitura;
			}
		}
	}
	return prajitura();
}

int dep_praj::getCap_curenta()
{
	int ct = 0;
	for (int i = 0; i < cap_max; i++) {
		if (depozit[i] != nullptr) {
			ct++;
		}
	}
	return ct;
}

void dep_praj::getPraj_din_depozit(prajitura p)
{
	for (int i = 0; i < cap_max; i++)
	{
		//if(strcmp(storage[i],a)!=1)
		cout << p.getNume() << endl;
	}
}

class preluare_comanda
{
	reteta* r;
	prep_prajitura* praji;
	dep_praj* dep;
public:
	preluare_comanda();
	prajitura preia_comanda(reteta* reteta_prajitura);
	prajitura* preia_comanda(reteta* reteta_prajitura, int nr_prajituri);
	prajitura preia_comanda(string nume_prajituri);
	void getPraj_din_depozit();
	bool checkDepozit_prajituri();
	bool refillDep();
};

preluare_comanda::preluare_comanda() {}

prajitura preluare_comanda::preia_comanda(reteta* reteta_prajitura)
{
	dep_praj* dep = new dep_praj();
	prajitura* p = new prajitura(dep->getPrajitura(reteta_prajitura->getNume()));
	cout << "Comanda primita " << reteta_prajitura->getNume() << " gata de servit" << endl;
	if (p->getNume() != "")
		return (*p);
	else
		(*p) = praji->preia_comanda(reteta_prajitura);
	return (*p);
}

prajitura* preluare_comanda::preia_comanda(reteta* reteta_prajitura, int nr_prajituri)
{
	prajitura p[13];
	int i = 0;
	while (nr_prajituri)
	{
		cout << "Prajitura " << reteta_prajitura->getNume() << " cu numarul " << i + 1 << " este in curs de pregatire" << endl;
		cout << "Numarul de prajituri ramase: " << nr_prajituri - 1 << endl;
		p[i] = praji->preia_comanda(reteta_prajitura);
		nr_prajituri--;
		i++;
	}
	return p;
}

prajitura preluare_comanda::preia_comanda(string nume_prajituri)
{
	reteta* reteta_p = new reteta(nume_prajituri, 5);
	prajitura* p = new prajitura(dep->getPrajitura(reteta_p->getNume()));
	if (p->getNume() != "")
		return (*p);
	else
		(*p) = praji->preia_comanda(reteta_p);
	return (*p);
}

void preluare_comanda::getPraj_din_depozit()
{
	preluare_comanda* dep = new preluare_comanda();
	dep->getPraj_din_depozit();
}
bool  preluare_comanda::checkDepozit_prajituri()
{
	if (dep->getCap_curenta() < 3)
		return 0;
	return 1;
}
bool preluare_comanda::refillDep()
{
	int capacitate = dep->getCap_curenta();
	bool n = true;
	prajitura* p = new prajitura(r->getNume());
	while (capacitate < 10)
	{
		n = dep->addPrajitura(*p);
		capacitate++;
	}
	return n;

	class panoul_de_comanda
	{
		list<reteta*>menu;
		preluare_comanda* preia_comanda = new preluare_comanda();

	public:
		panoul_de_comanda()
		{
			menu.push_back(new reteta("Biscuiti", 5));
			menu.push_back(new reteta("Briose", 10));
			menu.push_back(new reteta("Rafaelo", 5));
			menu.push_back(new reteta("Tiramisu", 15));
			menu.push_back(new reteta("Negrese", 5));
		};
		void showProduse() {

			for (auto i = menu.begin(); i != menu.end(); i++)
				cout << "Produse disponibile: " << (*i)->getNume() << endl;

		}
		void selectProduse(string nume);
		void selectProduse(string nume, int nr_produse);
		void showPraj_din_depozit();

	};

	void panoul_de_comanda::showProduse()
	{
		for (auto i = menu.begin(); i != menu.end(); i++)
			cout << "Produse disponibile: " << (*i)->getNume() << endl;

	}

	void panoul_de_comanda::selectProduse(string nume, int nr_produse)
	{
		reteta* ret_praj = new reteta();
		for (auto i = menu.begin(); i != menu.end(); ++i)
			if ((*i)->getNume() == nume) {
				ret_praj = (*i);
				break;
			}
		preluare_comanda->preia_comanda(prep_prajitura);
	}
	void panoul_de_comanda::selectProduse(string nume, int nr_produse)
	{
		reteta* ret_praj = new reteta();
		for (auto i = menu.begin(); i != menu.end(); ++i)
			if ((*i)->getNume() == nume) {
				ret_praj = (*i);
				break;
			}
		preluare_comanda->preia_comanda(ret_praj, nr_produse);
	}
	void panoul_de_comanda::showPraj_din_depozit() {
		preia_comanda->getPraj_din_depozit();
	}





	int main() {

		string nume_praj;
		panoul_de_comanda* p = new panoul_de_comanda();


		int opt
			int n;



		do {
			cout << "1.Prajiturile sunt:" << endl;
			cout << "2.Comanda dvs.:" << endl;
			cout << "3.Comandati produse mai multe:" << endl;
			cout << "4.Prajituri care sunt deja:" << endl;
			cout << "0.Iesire" << endl;


			cout << "Alegeti optiunea" << opt << endl;
			cin >> opt;


			if (!cin) {
				cin.clear();
				cout << "Alegeti o optiune data";
				opt = -1;
			}

			switch (opt) {
			case 1:
				system("cls");
				p->showProduse();
				break;

			case 2:
				system("cls");
				cout << "Ce prajitura doriti sa comandati?" << endl;
				cin.get();
				getline(cin, nume_praj);
				cout << "Pregatim prajitura: " << nume_praj << endl;
				p->selectProduse(nume_praj);
				break;

			case 3: {
				system("cls");
				cout << "Ce prajitura doriti sa comandati?" << endl;
				cin.get();
				getline(cin, nume_praj);
				cout << "Cate bucati doriti sa comandati?" << endl;
				do {
					cin >> n;
					if (!cin)
					{
						cin.clear();
						cout << "Alegeti o optiune data!" << endl;
					}
				} while (!cin)
					break; 
			}

			case 4: 
			{
				//system("cls");
				//cout << "Prajiturile care sunt disponibile:" << endl;
				//p->showPraj_din_depozit();
				break; 
			}

			case 0: {
				cout << "Va mai asteptam pe la noi" << endl;
				exit(0);
				break; 
			}

			default:
				cout << "Optiune gresita!" << endl;
				break;
			}

		} while (opt != 0);
		

	}
