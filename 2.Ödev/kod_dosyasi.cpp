#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;
int x;

struct Dugum {

    int plaka;
    string sehir;
    Dugum* sol;
    Dugum* sag;
};

Dugum* add_To_Tree(Dugum* node, int plaka, string sehir) {

    if (node == NULL) {
    	Dugum *newNode = new Dugum;
    	newNode->plaka = plaka;
    	newNode->sehir = sehir;
    	newNode->sol = newNode->sag = NULL;
        return newNode;
    }
    if (plaka < node->plaka) {
        node->sol = add_To_Tree(node->sol, plaka, sehir);
    }
	else if (plaka > node->plaka) {
        node->sag = add_To_Tree(node->sag, plaka, sehir);
    }

    return node;
}

Dugum* find(Dugum* node, int plaka) {

    if (node == NULL || node->plaka == plaka) {
        return node;
    }

    if (plaka < node->plaka) {
        return find(node->sol, plaka);
    }

    return find(node->sag, plaka);
}

int Derinlik_Bul(Dugum* node) {

    if (node == NULL) {
        return 0;
    }

    int solDerinlik = Derinlik_Bul(node->sol);
    int sagDerinlik = Derinlik_Bul(node->sag);

    return  max(solDerinlik, sagDerinlik) + 1;
}

bool isDengeli(Dugum* node) {

    if (node == NULL) {
        return true;
    }

    int solDerinlik = Derinlik_Bul(node->sol);
    int sagDerinlik = Derinlik_Bul(node->sag);

    int duzeyFarki = abs(solDerinlik - sagDerinlik);

    if (duzeyFarki <= 1 && isDengeli(node->sol) && isDengeli(node->sag)) {
        return true;
    }

    return false;
}

void Agac_Yazdir(Dugum* node, int j = 0) {

    if (node == NULL) {
        return;
    }

    Agac_Yazdir(node->sag, j + 1);

    for (int i = 0; i < j; i++) {
        cout << "         ";
    }

    cout << node->plaka << endl;

    Agac_Yazdir(node->sol, j + 1);
}

int Duzey_Farki(Dugum* node, int plaka1, int plaka2) {

    Dugum* node1 = find(node, plaka1);
    Dugum* node2 = find(node, plaka2);

    if (node1 != NULL && node2 != NULL) {
        int level1 = 0;
        int level2 = 0;

        Dugum* temp = node;

        while (temp != NULL) {
            if (plaka1 < temp->plaka) {
                temp = temp->sol;
                level1++;
            }
			else if (plaka1 > temp->plaka) {
                temp = temp->sag;
                level1++;
            }
			else {
                break;
            }
        }

        temp = node;

        while (temp != NULL) {
            if (plaka2 < temp->plaka) {
                temp = temp->sol;
                level2++;
            }
			else if (plaka2 > temp->plaka) {
                temp = temp->sag;
                level2++;
            }
			else {
                break;
            }
        }
        return abs(level1 - level2);
    }
    return -1;
}

void Preorder_Yazdir(Dugum* node) {

    if (node == NULL) {
        return;
    }

    cout << node->plaka;

    if(x < 18){
    	cout << "-";
    	x++;
	}
    Preorder_Yazdir(node->sol);
    Preorder_Yazdir(node->sag);
}

void Inorder_Yazdir(Dugum* node) {

    if (node == NULL) {
        return;
    }
    Inorder_Yazdir(node->sol);

     cout << node->plaka;
     if(x < 18){
    	cout << "-";
    	x++;
	}
    Inorder_Yazdir(node->sag);
}

void Postorder_Yazdir(Dugum* node) {

    if (node == NULL) {
        return;
    }

    Postorder_Yazdir(node->sol);
    Postorder_Yazdir(node->sag);

    cout << node->plaka;

    if(x < 18){
    	cout << "-";
    	x++;
	}
}

int main() {

    Dugum* root = NULL;

    ifstream file("sehir_plaka_kodlari.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int virgulIndex = line.find(",");
            int plaka;
            stringstream(line.substr(0, virgulIndex)) >> plaka;
            string sehir = line.substr(virgulIndex + 1);
            root = add_To_Tree(root, plaka, sehir);
        }
        file.close();
    }
	else {
	    cout << "Dosya acilamadi." << endl;
	    return 0;
    }


    cout << "\nDerinlik: " << Derinlik_Bul(root);
    
	if (isDengeli(root))
        cout << ", Dengeli mi?: Evet\n\n" << endl;
	else
        cout << ", Dengeli mi?: Hayır\n\n" << endl;


    Agac_Yazdir(root);

	int plaka1, plaka2;
	cout << "\n\nAraya Sadece Boşluk Koyacak Şekilde 1. ve 2. Şehirler İçin Plaka Girin: ";

	string inputLine;
	getline(cin, inputLine);

	stringstream ss(inputLine);
    ss >> plaka1 >> plaka2;

	Dugum* node1 = find(root, plaka1);
	Dugum* node2 = find(root, plaka2);

	if (node1 != NULL && node2 != NULL) {
	    cout << "Şehirler: \n" << node1->sehir << "\n" << node2->sehir << endl;
	    cout << "\nAğaçtaki Düzey Farkı: " << Duzey_Farki(root, plaka1, plaka2) << endl;
	}
	else {
	    cout << "Yanlış Plaka Girişi, Tekrar deneyin!" << endl;
	}


    cout << "\n\nPreorder: ";
    x = 1;
    Preorder_Yazdir(root);
    cout << endl;

    cout << "Inorder: ";
    x = 1;
    Inorder_Yazdir(root);
    cout << endl;

    cout << "Postorder: ";
    x = 1;
    Postorder_Yazdir(root);
    cout << endl;

    return 0;
}