#include <iostream>
#include <time.h>

using namespace std;

//STRUCTS
struct sMazo{
    short carta;
    bool usado;
};

struct sMesa {
    short carta;
    bool ocupado;
};

struct sMano {
    short carta[3]; 
    bool usado[3];
};

//PROTOTIPOS
void inicMazo(sMazo[][10]);
void printMazo(sMazo[][10]); //(Mate Pirchi) Lo agregue porque quiza lo necesitemos para comprobar que todo ande bien
short eligeCarta(sMazo[][10]);
void inicMesa(sMesa[][10]);
void printMesa(sMesa[][10]);
void inicializarMano(sMano &);
void printMano(sMano &);
void agregarCartaAMano(sMano &, short);

int main(){
    sMazo mazo[4][10];
    sMesa mesa[6][10];
    sMano mano;

    inicMazo(mazo);
    inicMesa(mesa);
    inicializarMano(mano);


    // Agregar cartas a la mano del jugador
    for (int i = 0; i < 3; i++) {
        short carta = eligeCarta(mazo);
        agregarCartaAMano(mano, carta);
    }

    // Agregar cartas a la mesa
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            mesa[i][j].carta = eligeCarta(mazo);
            mesa[i][j].ocupado = false;
        }
    }


    cout << "Cartas Random sacadas: " << eligeCarta(mazo);
    printMazo(mazo);
    printMesa(mesa);
    printMano(mano);


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

// ---------------------------------------------------------------------------------------
short eligeCarta(sMazo mazo[][10]){
    short posicCarta,
          filaCarta,
          colCarta;

    srand (time(0));
    posicCarta= rand()% 31;

    filaCarta =(posicCarta/10);
    colCarta = posicCarta-(filaCarta*10);

    while (mazo[filaCarta][colCarta].usado){
        colCarta++;
        if (colCarta >= 10){
            colCarta = 0;
            filaCarta++;

            if (filaCarta >= 4){
                filaCarta = 0;
            }
        }
    }

    mazo[filaCarta][colCarta].usado = true;
    return mazo[filaCarta][colCarta].carta;
}

// ---------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------
void inicMesa(sMesa mesa[][10]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            mesa[i][j].carta = 0;
            mesa[i][j].ocupado = false;
        }
    }
}

// ---------------------------------------------------------------------------------------
void printMesa(sMesa mesa[][10]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            cout << mesa[i][j].carta << " ";
        }
        cout << endl;
    }

    cout << endl
         << "¿Ocupado?" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            cout << j + 1 + (i * 10) << ") " << mesa[i][j].ocupado << "  ";
        }
        cout << endl;
    }
}

// ---------------------------------------------------------------------------------------

void inicializarMano(sMano &mano) {
    // Inicializar la mano del jugador con cartas no usadas
    for (int i = 0; i < 3; i++) {
        mano.carta[i] = 0;
        mano.usado[i] = false;
    }
}

// ---------------------------------------------------------------------------------------
void printMano(sMano &mano) {
    for (int i = 0; i < 3; i++) {
        cout << "Carta " << i + 1 << ": ";
        if (mano.usado[i]) {
            cout << "Usada" << endl;
        } else {
            cout << mano.carta[i] << endl;
        }
    }
}

// ---------------------------------------------------------------------------------------

void agregarCartaAMano(sMano &mano, short carta) {
    // Buscar la primera posición libre en la mano y agregar la carta
    for (int i = 0; i < 3; i++) {
        if (mano.usado[i] == false) {
            mano.carta[i] = carta;
            mano.usado[i] = true;
            break;
        }
    }
}
