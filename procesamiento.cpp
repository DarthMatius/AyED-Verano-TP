//------------------------------PROCESAMIENTO-------------------------------------

void setenta(Nodo* mazoSec, short &r) {
    if(mazoSec==NULL)
    {
        return;
    }
    Nodo* aux = mazoSec;
    while(aux->siguiente!=NULL){
        if(aux->dato.valor==7)
        {
            r++;
        }
        aux=aux->siguiente;
    }
    if(aux->dato.valor==7)
    {
        r++;
    }
    return;
}

void oros(Nodo* mazoSec, short &k) {
    if(mazoSec==NULL)
    {
        return;
    }
    Nodo* aux = mazoSec;
    while(aux->siguiente!=NULL){
        if(strcmp(aux->dato.palo,"oro")==0)
        {
            k++;
        }
        aux=aux->siguiente;
    }
    if(strcmp(aux->dato.palo,"oro")==0)
    {
        k++;
    }
    return;
}

void sieteDeOro(Nodo* mazoSec, bool &SO) {
    if(mazoSec==NULL)
    {
        return;
    }
    Nodo* aux = mazoSec;
    SO=false;
    while(aux->siguiente!=NULL){
        if(aux->dato.valor==7 && (strcmp(aux->dato.palo,"oro")==0))
        {
            SO=true;
            return;
        }
        aux=aux->siguiente;
    }
    if(aux->dato.valor==7 && (strcmp(aux->dato.palo,"oro")==0))
    {
        SO=true;
        return;
    }
    return;
}

void totalCartas(Nodo* mazoSec, short &c) {
    if(mazoSec==NULL)
    {
        return;
    }
    Nodo* aux = mazoSec;
    while(aux->siguiente!=NULL){
        c++;
        aux=aux->siguiente;
    }
    c++;

    return;
}

void puntaje(Nodo* mazoJ1, Nodo* mazoJ2, short puntos1, short puntos2) { // puntos 1 y 2 son los contadores de escobas
    short aux1=0, aux2=0;
    bool sO1=false, sO2=false;
    totalCartas(mazoJ1,aux1);
    totalCartas(mazoJ2,aux2);
    if(aux1>aux2)
    {
        puntos1++;
    }
    if(aux2>aux1)
    {
        puntos2++;
    }
    aux1=0;
    aux2=0;
    sieteDeOro(mazoJ1,sO1);
    sieteDeOro(mazoJ2,sO2);
    if(sO1)
    {
        puntos1++;
    }
    if(sO2)
    {
        puntos2++;
    }
    oros(mazoJ1,aux1);
    oros(mazoJ2,aux2);
    if(aux1>aux2)
    {
        puntos1++;
    }
    if(aux2>aux1)
    {
        puntos2++;
    }
    aux1=0;
    aux2=0;
    setenta(mazoJ1,aux1);
    setenta(mazoJ2,aux2);
    if(aux1>aux2)
    {
        puntos1++;
    }
    if(aux2>aux1)
    {
        puntos2++;
    }

}
