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
struct sPuntCJ{
    short cantOros,
          totCartas,
          cantSetentas;
    bool sO;
};



//PROTOTIPOS
void inicMazo(sMazo[][10]);
void printMazo(sMazo[][10]);
short eligeCarta(sMazo[][10],short&,short&);
void inicCJ(sCarta[]);
void definePalo(short, str6);
void mostrarCJ(sCarta[]);
sCarta pop(Nodo*&);
void repartir(sMazo[][10],sCarta[],sCarta[],short&,short&);
void InicioPartida(sMazo[][10], short&, short&, Nodo*& );
void insertarEnListaCir(Nodo*&,sCarta);
void mostrarListado(Nodo *);
void Interfaz(Nodo*&, sCarta[], Nodo*&,bool);
void insertaListaDesord(sCarta, Nodo*&);
int tamanioMesa(Nodo*);
bool levSumaAcum(sCarta, Nodo*[], short, Nodo*&, Nodo*&);
void levAvanza(Nodo*[], short, short);
bool levAvanzaFin(Nodo*[], short&, short, int,Nodo*);
void levanta(Nodo*&, sCarta, Nodo*&, bool&);
void leerMazoSec(Nodo*);
void ordenarPorBurbuja(sCarta[], short);
void casoB(Nodo*&,int , sCarta[]);
void mazovacio(Nodo*&, sCarta[]);
void puntaje(Nodo*&, Nodo*&, short[]);
short elijeMayor(short, short);
void inicPuntCJ(sPuntCJ[]);
void puntosMazo(Nodo*&,sPuntCJ&);
int cartasRestantesMazo(sMazo[][10]);
void reinicMazo(sMazo[][10]);


int main(){
    bool  band2 ;
    short filaCarta = 0,
          colCarta = 0,
          puntos[2] = {0,0},
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
    printMazo(mazo);
    repartir(mazo,CJ1,CJ2,filaCarta,colCarta);
    mostrarCJ(CJ1);
    mostrarCJ(CJ2);
    printMazo(mazo);
    cout << "Deberian quedar 34 cartas en el mazo: " << cartasRestantesMazo(mazo);
    cout << endl << endl << endl << endl << "INICIO DE PARTIDA" << endl;

    cout << endl <<"¿Empezar el Juego?" << endl;
    system("pause");
    system("cls");
    InicioPartida(mazo,filaCarta, colCarta, inicListaCarta);
    cout << endl  <<"Se reparten 3 cartas a cada uno..." << endl;
    cout << "Quedan "<< cartasRestantesMazo(mazo) << " cartas en el mazo" << endl;
    while (juegoTermina != 1){
        for(int i=0;i<3;i++){
            if (tamanioMesa(inicListaCarta) == 0){
                cout << "Hiciste una Escoba! Ganas 1 punto!" << endl;
                puntos[1]++;
                cout << endl << "Pase computadora a Jugador 1" << endl;
                system("pause");
                system("cls");
                mazovacio(inicListaCarta, CJ1);
            }else{
                cout << endl << "Pase computadora a Jugador 1" << endl;
                system("pause");
                system("cls");
                cout << "La mesa tiene " << endl;
                mostrarListado(inicListaCarta);
                cout << "Jugador 1)" << endl;
                Interfaz(punteroMazoSecJ1, CJ1, inicListaCarta, band2);
            }

            if (tamanioMesa(inicListaCarta) == 0){
                cout << endl <<"Hiciste una Escoba! Ganas 1 punto!" << endl;
                puntos[0]++;
                cout << endl << "Pase computadora a Jugador 2" << endl;
                system("pause");
                system("cls");
                mazovacio(inicListaCarta, CJ2);
            }else{
                cout << endl << "Pase computadora a Jugador 2" << endl;
                system("pause");
                system("cls");

                cout << "La mesa tiene " << endl;
                mostrarListado(inicListaCarta);
                cout << "Jugador 2)" << endl;
                Interfaz(punteroMazoSecJ2, CJ2, inicListaCarta, band2);
            }
            if (tamanioMesa(inicListaCarta) == 0){
                cout << "Hiciste una Escoba! Ganas 1 punto!" << endl;
                puntos[1]++;
            }
        }
        system("pause");
        system("cls");
        repartir(mazo,CJ1,CJ2,filaCarta,colCarta);
        cout << "Se reparten 3 cartas a cada uno..." << endl;
        cout << "Quedan "<< cartasRestantesMazo(mazo) << " cartas en el mazo" << endl;
        cout << endl << "Mazo Secundario" << endl << "1) " << endl;
        leerMazoSec(punteroMazoSecJ1);
        cout <<endl << "2) " << endl;
        leerMazoSec(punteroMazoSecJ2);
        cout << endl << "Puntaje" << endl;
        puntaje(punteroMazoSecJ1, punteroMazoSecJ2, puntos);
        system("pause");

        if (puntos[0] >= 15) {
            cout << "¡El Jugador 1 ha ganado la partida con " << puntos[0] << " puntos!" << endl;
            juegoTermina = 1;  // Finalizar el juego
        } else if (puntos[1] >= 15) {
            cout << "¡El Jugador 2 ha ganado la partida con " << puntos[1] << " puntos!" << endl;
            juegoTermina = 1;  // Finalizar el juego
        }
        system("cls");
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

int cartasRestantesMazo(sMazo mazo[][10]){
    int cantRest = 0;

    for (short i = 0; i < 4; i++){
        for(short j = 0; j < 10; j++){
            if (!(mazo[i][j].usado)){
                cantRest++;
            }
        }
    }
    return cantRest;
}

void reinicMazo(sMazo mazo[][10]){

    for (short i = 0; i < 4; i++){
        for(short j = 0; j < 10; j++){
            mazo[i][j].usado = false;
        }
    }
}

short eligeCarta(sMazo mazo[][10],short& filaCarta, short& colCarta){
    short i = 0;
    srand(time(0));
    colCarta= rand()%10;//+1;
    filaCarta= rand()%4;

    if (cartasRestantesMazo(mazo) <= 0){
        cout << endl <<"El mazo se ha quedado sin cartas suficientes, reiniciando mazo..." <<endl;
        reinicMazo(mazo);
    }

    while (mazo[filaCarta][colCarta].usado){
        if (i <= 5){ //agregue esto para que Si a la quinta vez que hace random, no le sale un numero util, que saque el siguiente de la lista
            colCarta = rand()%10;
            filaCarta= rand()%4;
            i++;
        }else{
            colCarta++;
            if (colCarta >= 10){
                colCarta = 0;
                filaCarta++; //rand()%4;

                if (filaCarta >= 4){
                    filaCarta = 0;
                }
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

void repartir(sMazo mazo[][10],sCarta c1[], sCarta c2[],short& filaCarta, short& colCarta){
    int i=0;
    for(i; i<3 ; i++){
        eligeCarta(mazo,filaCarta,colCarta);
        c1[i].numRef= mazo[filaCarta][colCarta].carta;
        definePalo(filaCarta, c1[i].palo);
        c1[i].valor = colCarta+1;

        eligeCarta(mazo,filaCarta,colCarta);
        c2[i].numRef= mazo[filaCarta][colCarta].carta;
        definePalo(filaCarta, c2[i].palo);
        c2[i].valor = colCarta+1;
  }
        ordenarPorBurbuja(c1,3);
        ordenarPorBurbuja(c2,3);

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
            cout<< i+1 <<") "<<C[i].numRef<< "(" << C[i].valor << ")" << " ";
            cout<<C[i].palo<< endl;
    }
  //	cout<<"valor"<<C[i].valor<< endl;
  }
}

void leerMazoSec(Nodo* mazoSec){
    short i = 0;
    while (mazoSec != NULL){
        cout << i <<") "<< mazoSec->dato.numRef << " ";
        //cout <<mazoSec->dato.valor << " " ;
        cout << mazoSec->dato.palo << endl;
        mazoSec = mazoSec->siguiente;
        i++;
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

void InicioPartida(sMazo mazo[][10],short& filaCarta, short& colCarta,Nodo*& inicListaCarta){
   sCarta CartaActual;
    for (int i=0; i<4 ; i++){
    eligeCarta(mazo,filaCarta,colCarta);
    CartaActual.numRef= mazo[filaCarta][colCarta].carta;
    definePalo(filaCarta, CartaActual.palo);
    CartaActual.valor = colCarta+1;
    insertarEnListaCir(inicListaCarta,CartaActual);
    }//primera parte volcar datos del mazo en nodos y agregarlos a la lista
    //repartir(mazo,c1,c2,posicCarta,filaCarta,colCarta);
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
}

void mostrarListado(Nodo *inicListaCarta){
    Nodo *aux = inicListaCarta;
    short i = 1;
    do{
        cout << i << ") "<<aux->dato.numRef<< " " << aux->dato.palo << "   ";// hay q corregir aca
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
    antecesor = aux;

    while (aux->siguiente != inicListaCarta && (aux->dato.numRef != cartaBuscada.numRef || strcmp(aux->dato.palo, cartaBuscada.palo) != 0)) {// Hice un cambio aca, el || antes era un &&
        antecesor = aux;
        aux = aux->siguiente;
    }

    if ( aux->dato.numRef != cartaBuscada.numRef && strcmp(aux->dato.palo, cartaBuscada.palo) != 0){
        cout << endl << "ERROR CARTA A ELIMINAR NO ENCONTRADA"<< endl;
        return false;
    }

    if (aux == inicListaCarta) {
            if (aux->siguiente == aux){
                inicListaCarta = NULL;
                delete aux;
                return true;
            }
            else{
                while (antecesor->siguiente != inicListaCarta){
                    antecesor = antecesor->siguiente;
                }
                antecesor ->siguiente = aux->siguiente;
                inicListaCarta = aux->siguiente;
                delete aux;
                return true;
            }
    }else{
        antecesor ->siguiente = aux->siguiente;
        inicListaCarta = aux->siguiente;
        delete aux;
        return true;
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

void ordenarPorBurbuja(sCarta c1[], short tam){
    int i, j;
    sCarta aux;
    for (i = 0; i < tam; i++)  {
        for (j = 0; j < tam - 1; j++){
            if (c1[j].numRef > c1[j+1].numRef) {
                aux = c1[j];
                c1[j] = c1[j+1];
                c1[j+1] = aux;

            }
        }
    }
}

void Interfaz(Nodo*& mazoSecundario, sCarta CJ[], Nodo*& inicListaCarta, bool band2){
    int posCarta;
    char accion;
    mostrarCJ(CJ);

    do{
        cout << "Seleccione una Carta segun la posicion" << endl;
        cin >> posCarta;
        posCarta -= 1;
        if ( 0> posCarta || posCarta > 2) {
            cout << "El jugador puede tener hasta tres cartas, no existe esa posicion"<< endl;
        }else if (CJ[posCarta].numRef == 0){
            cout << "Carta ya usada, elija de vuelta"<< endl;
        }
    } while (0> posCarta || posCarta > 2 || CJ[posCarta].numRef == 0);
    system("cls");
    mostrarListado(inicListaCarta);
    cout<< "elegiste la carta " << CJ[posCarta].numRef << " " <<CJ[posCarta].palo << endl;
    cout << "Que operacion desea realizar con esta carta?" <<endl;
    cout << "Si desea levantar inserte A o si desea tirar la carta inserte B" << endl;
    cin >> accion;
    accion = toupper(accion);
    switch (accion){
        case 'A':
            levanta(mazoSecundario, CJ[posCarta], inicListaCarta,band2);
            if (!band2){
                cout<< " la carta que elegiste no puede levantar nada por lo que queda tirada en la mesa"<< endl;
                casoB(inicListaCarta,posCarta,CJ);
            }else{
                CJ[posCarta].numRef = 0;
            }
            break;
        case 'B':
            casoB(inicListaCarta,posCarta,CJ);
            break;
        default:
            cout << "SELECCION INVALIDA, PIERDE TURNO"<<endl;
            break;
  }
  // menu preguntando que va a hacer si levantar o tirar
  // en caso de que levante debe elegir cartas con un menu que cierre cuantas cartas se levanta,  la condicion de que de 15 la suma de los valores de los nodo
  // en caso de tirar invoca la funcion inserta nodo y agrega la carta sobre la mesa
  //borrar todo en la pantalla
  //mostrar mesa y v2
  //ofrecer lo mismo para v2

}

void casoB(Nodo*& inicListaCarta,int posCarta, sCarta CJ[]){
	insertarEnListaCir(inicListaCarta,CJ[posCarta]);
	CJ[posCarta].numRef=0;
}

void insertaListaDesord(sCarta datoNuevo, Nodo*&mazoSec){
    Nodo *nuevo = new Nodo();
    nuevo->dato = datoNuevo;

    nuevo->siguiente = mazoSec;
    mazoSec = nuevo;
}

sCarta pop(Nodo*& pLista){
    Nodo *aux = pLista;
    sCarta info = aux->dato;
    pLista = aux->siguiente;
    delete aux;
    return info;
}

void mazovacio (Nodo*& inicListaCarta, sCarta CJ[]){
    int posCarta;

    do{
        cout << "La mesa no tiene cartas" << endl;
        mostrarCJ(CJ);
        cout << "Seleccione la posicion de la carta a tirar a la mesa: " << endl;
        cin >> posCarta;
        posCarta -= 1;
        if ( 0> posCarta || posCarta > 2) {
            cout << "El jugador puede tener hasta tres cartas, no existe esa posicion"<< endl;
            system("cls");
        }
    } while (0> posCarta || posCarta > 2);

    casoB(inicListaCarta, posCarta, CJ);

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
//--------------------INICIO COMBINATORIA (Levanta de Mesa)-----------------------
bool levSumaAcum(sCarta carJug, Nodo*p[], short i, Nodo*&mazoSec, Nodo*& mazoMesa){
    short acum = carJug.valor,
          j;
    for (j = 0 ; j <= i; j++){
        acum += p[j]->dato.valor;
    }

    if(acum == 15){
        insertaListaDesord(carJug, mazoSec);
        cout << "Carta/s de la mesa levantada/s: ";
        j = 0; //lo pongo afuera del for para que quede bien esteticamente;
        cout << p[j]->dato.numRef << " " << p[j]->dato.palo;
        insertaListaDesord(p[j]->dato, mazoSec);
        eliminarCarta(mazoMesa, p[j]->dato);
        for (j = 1 ; j <= i; j++){
            cout << ", "<<p[j]->dato.numRef << " " << p[j]->dato.palo;
            insertaListaDesord(p[j]->dato, mazoSec);
            eliminarCarta(mazoMesa, p[j]->dato);
        }
        cout << endl;
        system("pause");
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
    if (i >= tamMesa-1){ //si hay mas punteros que cartas en mesa, terminar proceso
      //    cout << "Tu carta no puede levantar nada." << endl;
       //   Interfaz( mazoSecundario, CJ[], Nodo*& inicListaCarta)
        return true;
    }
    else if (p[j-1]->siguiente != p[j]) { //si el puntero anterior puede avanzar, que avance
        p[j-1] = p[j-1]->siguiente;
        return false;
    }
    else {// Si el puntero NO puede avanzar...
        if (p[j-1] != p[0]){ //Y no es el cero, se repite este modulo (recursivo)
            levAvanzaFin(p, i, j-1 , tamMesa, mazoMesa);
            return false;
        }

        else{ // Si es el cero, entonces se posicionan todos los punteros al comienzo y se agrega un puntero
            p[0] = mazoMesa;
            levAvanza(p, 0, i);
            while (p[j]->siguiente != p[0]){
                p[j] = p[j-1]->siguiente;
                j++;
            };
            p[j]=p[j-1]-> siguiente;
            i++;
            return false;
        }
    }
}


void levanta(Nodo*& mazoSecundario, sCarta carJug, Nodo*& mazoMesa, bool& band2 ){
    short i = 0;
    bool band1 = true;
         band2 = true;
    Nodo**p = new Nodo*[tamanioMesa(mazoMesa)];
    for (short j = 0; j < tamanioMesa(mazoMesa); j++){
        p[j] = NULL;
    }

    p[i] = mazoMesa;
    while(band1 && band2){
        if (i >= tamanioMesa(mazoMesa)){
		band1 = false;
		band2 = false;
		}else {
           levAvanza(p, i, i);
           if (i>0){
           }
           band1 = levSumaAcum(carJug, p, i, mazoSecundario, mazoMesa);
		}
        if (band1 && p[i]->siguiente != mazoMesa){
            p[i] = p[i]->siguiente;
        }else if (band1){
            if (i == 0){
                p[0]=p[0]->siguiente;
                i++;
                p[i]= mazoMesa;
            }else{
                if (levAvanzaFin(p, i, i, tamanioMesa(mazoMesa),mazoMesa)){
                    band2 = false;
                }
                else{
                     p[i]= mazoMesa;
                }
            }
        }
    }
}
//-----------------------------FIN COMBINATORIA-----------------------------------

//------------------------------PROCESAMIENTO-------------------------------------
void puntosMazo(Nodo*&mazoSec, sPuntCJ &puntCJ) { //junte todos los contadores en uno solo, asi recorremos la lista una sola vez
    if(mazoSec==NULL){
        return;
    }
    sCarta dato;

    while(mazoSec->siguiente!=NULL){

        dato = pop(mazoSec);

        if(dato.valor==7){
            puntCJ.cantSetentas++;
        }
        if(strcmp(dato.palo,"oro")==0){
            puntCJ.cantOros++;
        }
        if(dato.valor==7 && (strcmp(dato.palo,"oro")==0)){
            puntCJ.sO=true;
        }

        puntCJ.totCartas++;
    }
    dato = pop(mazoSec);
    if(dato.valor==7){
        puntCJ.cantSetentas++;
    }
    if(strcmp(dato.palo,"oro")==0){
        puntCJ.cantOros++;
    }
    if(dato.valor==7 && (strcmp(dato.palo,"oro")==0)){
        puntCJ.sO=true;
    }
    puntCJ.totCartas++;

    return;
}

void inicPuntCJ(sPuntCJ puntCJ[]){
    for (short i = 0; i < 2; i++){
        puntCJ[i].cantOros = 0;
        puntCJ[i].cantSetentas = 0;
        puntCJ[i].totCartas = 0;
        puntCJ[i].sO = false;
    }
}

short elijeMayor(short v1, short v2){ // 4 si son iguales, 0 si v1 es mayor, 1 si v2 es mayor
    if(v1 > v2){
        return 0;
    }else if (v1 < v2){
        return 1;
    }else{
        return 4;
    }

}

void puntaje(Nodo*& mazoJ1, Nodo*& mazoJ2, short puntos[]) { // puntos 1 y 2 son los contadores de escobas
    short aux;
    sPuntCJ puntCJ[2];

    inicPuntCJ(puntCJ);

    puntosMazo(mazoJ1,puntCJ[0]);
    puntosMazo(mazoJ2,puntCJ[1]);

    aux = elijeMayor(puntCJ[0].totCartas, puntCJ[1].totCartas);
    if (aux < 3){
        puntos[aux]++;
        cout << "Jugador " << aux+1 << " Gana 1 punto por mayoria de cartas!" << endl;
    }else {
        cout << "Ambos Jugadores tienen la misma cantidad de cartas, Ninguno gana Puntos!"<< endl;
    }

    aux = elijeMayor(puntCJ[0].cantOros, puntCJ[1].cantOros);
    if (aux < 3){
        puntos[aux]++;
        cout << "Jugador " << aux+1 << "  Gana 1 punto por mayoria de Oros!" << endl;
    }else {
        cout << "Ambos Jugadores tienen la misma cantidad de Oros, Ninguno gana Puntos!"<< endl;
    }

    aux = elijeMayor(puntCJ[0].cantSetentas, puntCJ[1].cantSetentas);
    if (aux < 3){
        puntos[aux]++;
        cout << "Jugador " << aux+1 << " Gana 1 punto por mayoria de Sietes!" << endl;
    } else {
        cout << "Ambos Jugadores tienen la misma cantidad de Sietes, Ninguno gana Puntos!"<< endl;
    }

    if(puntCJ[0].sO){
        puntos[0]++;
        cout << "Jugador 1 Gana 1 punto por tener el Siete de Oro!" << endl;
    }
    if(puntCJ[1].sO){
        puntos[1]++;
        cout << "Jugador 2 Gana 1 punto por tener el Siete de Oro!" << endl;
    }

    cout <<endl<< "El jugador 1 tiene " << puntos[0] << " puntos" << endl;
    cout << "El jugador 2 tiene " << puntos[1] << " puntos" << endl;

    return;
}
