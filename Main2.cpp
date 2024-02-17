#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstring>
using namespace std;
typedef char str6[7];

//STRUCTS
struct sMazo{
    short carta;
    bool usado;
};
 struct sCarta{
 	short valor;
 	str6 palo;
 	short numRef;
 };
 struct Nodo{
 	sCarta dato;
 	Nodo* siguiente;
 };



//PROTOTIPOS
void inicMazo(sMazo[][10]);
void printMazo(sMazo[][10]);
short eligeCarta(sMazo[][10],short&,short&,short&);
void inicCJ(sCarta[]);
void definePalo(short, str6);
void mostrarCJ(sCarta[]);
void repartir(sMazo[][10],sCarta[],sCarta[],short&,short&,short&);
void InicioPartida(sMazo[][10], sCarta[], sCarta[], short&, short&, short&, Nodo*& );
void insertarEnListaCir(Nodo*&,sCarta);
void mostrarListado(Nodo *);
void Interfaz(Nodo*&, sCarta[], Nodo*&);
void insertaListaDesord(sCarta, Nodo*&);
int tamanioMesa(Nodo*);
bool levSumaAcum(sCarta, Nodo*[], short, Nodo*&, Nodo*&);
void levAvanza(Nodo*[], short, short);
bool levAvanzaFin(Nodo*[], short&, short, int, Nodo*);
void levanta(int, Nodo*&, sCarta[], Nodo*&);

//void ordenarPorBurbuja(sCarta[], short);

int main(){
	short posicCarta,
          filaCarta,
          colCarta,
          juegoTermina = 0;

	Nodo*inicListaCarta = NULL;
	Nodo*punteroMazoSecJ1 = NULL;
	Nodo*punteroMazoSecJ2 = NULL;

	sCarta CJ1[3]; //cartasjugador1
	sCarta CJ2[3];//cartasjugador2

    sMazo mazo[4][10];

    inicMazo(mazo);
	inicCJ(CJ1);
	inicCJ(CJ2);
    //cout << "Cartas Random sacada: " << eligeCarta(mazo,posicCarta,filaCarta,colCarta)<< endl;
    printMazo(mazo);
	repartir(mazo,CJ1,CJ2,posicCarta,filaCarta,colCarta);
	mostrarCJ(CJ1);
	mostrarCJ(CJ2);
    printMazo(mazo);
    cout << endl << endl << endl << endl << "INICIO DE PARTIDA" << endl;
    InicioPartida(mazo, CJ1, CJ2, posicCarta, filaCarta, colCarta, inicListaCarta);

    cout << endl <<"¿Empezar el Juego?" << endl;
    system("pause");
    system("cls");

    while (juegoTermina != 1){
        cout << "La mesa tiene " << endl;
        mostrarListado(inicListaCarta);

        cout << "Jugador 1)"<< endl;
        Interfaz(punteroMazoSecJ1, CJ1, inicListaCarta);
        cout << endl<<"Pase computadora a Jugador 2" << endl;
        system("pause");
        system("cls");

        cout << "La mesa tiene " << endl;
        mostrarListado(inicListaCarta);
        cout << "Jugador 2)"<< endl;
        Interfaz(punteroMazoSecJ2, CJ2, inicListaCarta);
        cout << endl<<"Pase computadora a Jugador 1" << endl;
        system("pause");
        system("cls");

        cout << "Termino? 1: SI      2: NO";
        cin >> juegoTermina;
    }
    return 0;
};

// ---------------------------------------------------------------------------------------
void inicMazo(sMazo mazo[][10]){
    short i,
          j;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 10; j++){
            if ( j < 7){
                mazo[i][j].carta = j+1;
                mazo[i][j].usado = false;
            }
            else{   // (Mate Pirchi) Hice esta division para que saltear los numeros 8 y 9, y aun asi usar los espacios 7 y 8 de la matriz
            mazo[i][j].carta = j+3;
            mazo[i][j].usado = false;
            }
        }
    };
}

short eligeCarta(sMazo mazo[][10],short& posicCarta,short& filaCarta, short& colCarta){

 	  srand(time(0));
    posicCarta= rand()%30 + 1;

 	 colCarta= rand()%10+1;
     filaCarta= rand()%4;
   /* filaCarta =(posicCarta/10);
    colCarta = posicCarta-(filaCarta*10);*/
	    while (mazo[filaCarta][colCarta].usado){
        //colCarta++;
         colCarta= rand()%10+1;
   	  	filaCarta= rand()%4;
       ;
        if (colCarta >= 10){
            colCarta = 0;
            //filaCarta++;
            filaCarta= rand()%4;

            if (filaCarta >= 4){
                filaCarta = 0;
            }
        }
    }

    mazo[filaCarta][colCarta].usado = true;
    return mazo[filaCarta][colCarta].carta;
}

void printMazo(sMazo mazo[][10]){
    short i,
          j;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 10; j++){
            cout << mazo[i][j].carta << " ";
        }
        cout << endl;
    }

    cout << endl <<"Fue usado?" << endl;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 10; j++){
            cout <<j+1 + (i*10) << ") "<< mazo[i][j].usado << "  ";
        }
        cout << endl;
    }
}

void repartir(sMazo mazo[][10],sCarta c1[], sCarta c2[],short&posicCarta,short& filaCarta, short& colCarta){
	int i=0;
	for(i; i<3 ; i++){
        eligeCarta(mazo,posicCarta,filaCarta,colCarta);
        c1[i].numRef= mazo[filaCarta][colCarta].carta;
        definePalo(filaCarta, c1[i].palo);
        c1[i].valor = colCarta+1;

	    eligeCarta(mazo,posicCarta,filaCarta,colCarta);
    	c2[i].numRef= mazo[filaCarta][colCarta].carta;
	    definePalo(filaCarta, c2[i].palo);
    	c2[i].valor = colCarta+1;

	}
//	ordenarPorBurbuja(c1,3);
//    ordenarPorBurbuja(c2,3);

}

void inicCJ(sCarta C[]){
	int i=0;
	for (i; i< 3; i++){
		C[i].valor=0;
		strcpy(C[i].palo, "Vacio");
		C[i].numRef=0;
	}
}

void mostrarCJ(sCarta C[]){
	int i=0;
	for (i; i<3 ; i++){
		if (C[i].numRef != 0){
            cout<< i+1 <<") "<<C[i].numRef<< " ";
            cout<<C[i].palo<< endl;
		}
	//	cout<<"valor"<<C[i].valor<< endl;
	}
}

void definePalo(short palo, str6 paloCarta){ //Le das el numero de la FILA y la VARIABLE donde GUARDAR el nombre del palo

    switch (palo){
        case 0:
            strcpy(paloCarta, "oro");
            break;
        case 1:
            strcpy(paloCarta, "copa");
            break;
        case 2:
            strcpy(paloCarta, "espada");
            break;
        case 3:
            strcpy(paloCarta, "basto");
            break;
        default:
            cout << "ERROR PALO INVALIDO, FILA NO ES NI 0, 1, 2 O 3";
    }
}

void InicioPartida(sMazo mazo[][10],sCarta c1[], sCarta c2[],short&posicCarta,short& filaCarta, short& colCarta,Nodo*& inicListaCarta){
 	 sCarta CartaActual;
    for (int i=0; i<4 ; i++){
		//eligeCarta(mazo,posicCarta,filaCarta,colCarta);
		CartaActual.numRef= i;//mazo[filaCarta][colCarta].carta;
		strcpy(CartaActual.palo, "oro"); //definePalo(filaCarta, CartaActual.palo);
		CartaActual.valor = i;//colCarta+1;
		insertarEnListaCir(inicListaCarta,CartaActual);
    }//primera parte volcar datos del mazo en nodos y agregarlos a la lista
    repartir(mazo,c1,c2,posicCarta,filaCarta,colCarta);//segunda parte utilizar la funcion repartir
}

void insertarEnListaCir(Nodo *&inicio, sCarta CartaActual){//insertaOrdenado

    Nodo *nuevo = new Nodo, *aux;
    nuevo->dato = CartaActual;
    aux = inicio;

    if (inicio == NULL){
        inicio = nuevo;
        nuevo->siguiente = inicio;
    }
    else{
        while (aux->siguiente != inicio){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo-> siguiente = inicio;
    }



    /*while (aux != NULL && aux->dato.valor < CartaActual.valor)
    {
        antecesor = aux;
        aux = aux->siguiente;
    }

    nuevo->siguiente = aux;

    if (aux != punteroListaCarta){


        antecesor->siguiente = nuevo;
    }
    else
    {
        punteroListaCarta = nuevo;
    }*/
}

void mostrarListado(Nodo *inicListaCarta){
    Nodo *aux = inicListaCarta;
    short i = 1;
    do{
        /*cout <<"valor "<< aux->dato.valor  ;
        cout << " palo " << aux-> dato.palo  ;
        cout << " Num Ref " << aux -> dato.numRef ;
        cout << endl;*/
        cout << i << ") "<<aux->dato.numRef<< " " << aux->dato.palo << "   ";
        i++;
        aux = aux->siguiente;
    }while (aux != inicListaCarta);
    cout << endl << endl;
}

Nodo* buscarCarta(Nodo* inicListaCarta, sCarta cartaBuscada) {
    Nodo* aux = inicListaCarta;

    while (aux->siguiente != inicListaCarta && aux->dato.numRef != cartaBuscada.numRef) {
        aux = aux->siguiente;
    }

    return aux;
}

Nodo* buscarMejorCarta(Nodo* inicListaCarta, sCarta cartaBuscada) {
    Nodo* aux = inicListaCarta;

    while (aux->siguiente != inicListaCarta && !(aux->dato.numRef < cartaBuscada.numRef)) {
        aux = aux->siguiente;
    }

    return aux;
}

bool eliminarCarta(Nodo*& inicListaCarta, sCarta cartaBuscada) {
    Nodo* aux, *antecesor;
    aux = inicListaCarta;

    while (aux->siguiente != inicListaCarta && aux->dato.numRef != cartaBuscada.numRef) {
        antecesor = aux;
        aux = aux->siguiente;
    }

    if (aux->siguiente != inicListaCarta) {
        if (aux == inicListaCarta) {
            inicListaCarta = aux->siguiente;
        } else {
            antecesor->siguiente = aux->siguiente;
        }

        delete aux;
        return true;
    } else {
        return false;
    }
}

Nodo* buscarInsertarCarta(Nodo*& inicListaCarta, sCarta cartaBuscada) {
    Nodo* aux = inicListaCarta, *antecesor;

    while (aux->siguiente != inicListaCarta && !(aux->dato.numRef < cartaBuscada.numRef)) {
        antecesor = aux;
        aux = aux->siguiente;
    }

    if (aux->siguiente != inicListaCarta && aux->dato.numRef == cartaBuscada.numRef) {
        return aux;
    } else {
        Nodo* nuevo = new Nodo;
        nuevo->dato = cartaBuscada;
        nuevo->siguiente = aux;

        if (aux != inicListaCarta) {
            antecesor->siguiente = nuevo;
        } else {
            inicListaCarta = nuevo;
        }

        return nuevo;
    }
}

void Interfaz(Nodo*& mazoSecundario, sCarta CJ[], Nodo*& inicListaCarta){
	int posCarta;
	char accion;
	mostrarCJ(CJ);
	cout << "Seleccione una Carta segun la posicion" << endl;
	cin >> posCarta;
	posCarta -= 1;
	cout << "¿Qué operacion desea realizar con esta carta?" <<endl;
	cout << "Si desea levantar inserte A o si desea tirar la carta inserte B" << endl;
	cin >> accion;
	switch (accion){
		case 'A':
		   levanta(posCarta, mazoSecundario, CJ, inicListaCarta);
		    CJ[posCarta].numRef = 0;
            break;
		case 'B':
		    insertarEnListaCir(inicListaCarta,CJ[posCarta]);
			CJ[posCarta].numRef=0;
			break;
		default:
		    break;
	}
	// menu preguntando que va a hacer si levantar o tirar
	// en caso de que levante debe elegir cartas con un menu que cierre cuantas cartas se levanta,  la condicion de que de 15 la suma de los valores de los nodo
	// en caso de tirar invoca la funcion inserta nodo y agrega la carta sobre la mesa
	//borrar todo en la pantalla
	//mostrar mesa y v2
	//ofrecer lo mismo para v2

}

void insertaListaDesord(sCarta datoNuevo, Nodo*&mazoSec){
    Nodo *nuevo = new Nodo();
    nuevo->dato = datoNuevo;

    nuevo->siguiente = mazoSec;
    mazoSec = nuevo;
}


int tamanioMesa(Nodo* mesa){
    if (mesa == NULL){
        return 0;
    }

    Nodo* aux = mesa->siguiente;
    int i = 1;
    while (aux != mesa){
        aux = aux->siguiente;
        i++;
    }
    return i;
}

bool levSumaAcum(sCarta carJug, Nodo*p[], short i, Nodo*&mazoSec, Nodo*& mazoMesa){
    short acum = carJug.valor,
          j;
    for (j = 0 ; j <= i; j++){
        acum += p[j]->dato.valor;
    }

    if(acum == 15){
        insertaListaDesord(carJug, mazoSec);
        cout << "Carta/s de la mesa usada/s: ";
        for (j = 0 ; j <= i; j++){
            cout << p[j]->dato.numRef << " " << p[j]->dato.palo << ", ";
            insertaListaDesord(p[j]->dato, mazoSec);
            eliminarCarta(mazoMesa, p[j]->dato);
        }
        return false;
    }
    else {
        return true;
    }

}

void levAvanza(Nodo*p[] , short curr, short i){
    bool band = true;
    short j;
    while (band){ //Si ocurre un error aca es que cantPunteros > cantCartas en Mesa
        band = false;
        for (j = 0; j < i; j++){
            if (p[curr] == p[j] && curr != j){
                band = true;
                p[curr] = p[curr]->siguiente;
            }
        }
    }
}

bool levAvanzaFin(Nodo*p[], short& i, short j, int tamMesa, Nodo*mazoMesa){
    cout << endl << "Entra a LevAvanzaFin" << endl;
    if (i == tamMesa-1){ //si hay mas punteros que cartas en mesa, terminar proceso
        cout << endl << "Entra a no hay lugar" << endl;
        system("pause");
        return true;
    }
    else if (p[j-1]->siguiente != p[j]) { //si el puntero anterior puede avanzar, que avance
        cout << endl << "Entra a puede avanzar" << endl;
        p[j-1] = p[j-1]->siguiente;
        return false;
    }
    else {// Si el puntero NO puede avanzar...
        cout << endl << "Entra a no puede avanzar" << endl;
        if (p[j-1] != p[0]){ //Y no es el cero, se repite este modulo (recursivo)
            cout << endl << "Entra a repite Modulo" << endl;
            levAvanzaFin(p, i, j-1 , tamMesa, mazoMesa);
            return false;
        }
        else{ // Si es el cero, entonces se posicionan todos los punteros al comienzo y se agrega un puntero
            cout << endl << "Entra a p[0] no avanza" << endl;
            cout << endl<< j << " " << p[0]->dato.valor << " "<<p[j]->dato.valor << endl;
            p[0] = mazoMesa;
            levAvanza(p, 0, i);
            cout << endl<< j << " " << p[0]->dato.valor << " "<<p[j]->dato.valor << endl<< "PASO LEVAVANZA"<< endl;
            while (p[j]->siguiente != p[0]){
                p[j] = p[j-1]->siguiente;
                j++;
            }
            cout <<endl <<"PASO EL WHILE" << endl;
            p[j]=p[j-1]-> siguiente;
            i++;
            cout <<endl <<"SOLO QUEDA RETURN" << endl;
            return false;
        }
    }
}

void levanta(int numCartaMano, Nodo*& mazoSecundario, sCarta mazoJugador[], Nodo*& mazoMesa ){
    short i = 0;
    bool band1 = true,
         band2 = true;
    Nodo**p = new Nodo*[tamanioMesa(mazoMesa)];

    p[i] = mazoMesa;
    while(band1 && band2){
        cout << "entro al while";
        cout << endl << i << " " << p[i]->dato.valor << endl;
        levAvanza(p, i, i);
        cout << "Curr"<< endl << i << " " << p[i]->dato.valor << endl;
        if (i>0){
            cout << endl <<"Ant" <<i-1 << " " << p[i-1]->dato.valor << endl;
        }
        band1 = levSumaAcum(mazoJugador[numCartaMano], p, i, mazoSecundario, mazoMesa);
        if (band1 && p[i]->siguiente != mazoMesa){
            cout << endl<< "entro al primer if";
            p[i] = p[i]->siguiente;
        }else if (band1){
            if (i == 0){
                cout << endl<< "entro al SEGUNDO if i == 0";
                p[0]=p[0]->siguiente;
                i++;
                p[i]= mazoMesa;
            }else{
                if (levAvanzaFin(p, i, i, tamanioMesa(mazoMesa),mazoMesa)){
                    cout << endl<< "NO ENCONTRO";
                    system("pause");
                    band2 = false;
                }
                else{
                     cout << endl<< "entro al TERCER if";
                     p[i]= mazoMesa;
                }
            }
        }
    cout << endl;
    }
}

