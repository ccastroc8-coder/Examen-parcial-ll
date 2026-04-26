#include <iostream>               //Carlos Daniel Castro Caceres
#include <stdlib.h>

using namespace std;

struct NodoPila{
    int num;
    NodoPila *sig;
};

struct NodoCola{
    int num;
    NodoCola *sig;
};

struct NodoLista{
    int num;
    NodoLista *sig;
};

struct NodoDoble{
    int num;
    string tipo;
    int orden;
    NodoDoble *sig;
    NodoDoble *ant;
};

struct NodoArbol{
    int num;
    NodoArbol *izq;
    NodoArbol *der;
};

NodoPila *tope = NULL;
NodoCola *frente = NULL, *fin = NULL;
NodoLista *lista = NULL;
NodoDoble *hini = NULL, *hfin = NULL;
NodoArbol *raiz = NULL;

int orden = 1;
int pares = 0;
int impares = 0;
int negativos = 0;
int ceros = 0;
int validos = 0;
int mayor = 0;
int menor = 0;
bool primero = true;

void pausa(){
    cout << "Presione Enter para continuar...";
    cin.ignore(1000,'\n');
    cin.get();
}

void push(int num){
    NodoPila *nuevo = new NodoPila();
    nuevo->num = num;
    nuevo->sig = tope;
    tope = nuevo;
}

void encolar(int num){
    NodoCola *nuevo = new NodoCola();
    nuevo->num = num;
    nuevo->sig = NULL;

    if(frente == NULL){
        frente = nuevo;
        fin = nuevo;
    }else{
        fin->sig = nuevo;
        fin = nuevo;
    }
}

void insertarLista(int num){
    NodoLista *nuevo = new NodoLista();
    nuevo->num = num;
    nuevo->sig = NULL;

    if(lista == NULL){
        lista = nuevo;
    }else{
        NodoLista *aux = lista;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

void historial(int num, string tipo){
    NodoDoble *nuevo = new NodoDoble();
    nuevo->num = num;
    nuevo->tipo = tipo;
    nuevo->orden = orden++;
    nuevo->sig = NULL;
    nuevo->ant = hfin;

    if(hini == NULL){
        hini = nuevo;
        hfin = nuevo;
    }else{
        hfin->sig = nuevo;
        hfin = nuevo;
    }
}

void insertarBST(NodoArbol *&r, int num){
    if(r == NULL){
        r = new NodoArbol();
        r->num = num;
        r->izq = NULL;
        r->der = NULL;
    }else if(num < r->num){
        insertarBST(r->izq, num);
    }else if(num > r->num){
        insertarBST(r->der, num);
    }
}

void inOrden(NodoArbol *r){
    if(r != NULL){
        inOrden(r->izq);
        cout << r->num << " ";
        inOrden(r->der);
    }
}

void preOrden(NodoArbol *r){
    if(r != NULL){
        cout << r->num << " ";
        preOrden(r->izq);
        preOrden(r->der);
    }
}

void postOrden(NodoArbol *r){
    if(r != NULL){
        postOrden(r->izq);
        postOrden(r->der);
        cout << r->num << " ";
    }
}

bool buscarBST(NodoArbol *r, int num){
    if(r == NULL) return false;
    if(r->num == num) return true;

    if(num < r->num)
        return buscarBST(r->izq, num);
    else
        return buscarBST(r->der, num);
}

void mostrarPila(){
    NodoPila *aux = tope;

    if(aux == NULL){
        cout << "Pila vacia\n";
        return;
    }

    while(aux != NULL){
        cout << aux->num << endl;
        aux = aux->sig;
    }
}

void mostrarCola(){
    NodoCola *aux = frente;

    if(aux == NULL){
        cout << "Cola vacia\n";
        return;
    }

    while(aux != NULL){
        cout << aux->num << endl;
        aux = aux->sig;
    }
}

void mostrarLista(){
    NodoLista *aux = lista;

    if(aux == NULL){
        cout << "Lista vacia\n";
        return;
    }

    while(aux != NULL){
        cout << aux->num << " ";
        aux = aux->sig;
    }

    cout << endl;
}

void mostrarHistorial(){
    NodoDoble *aux = hini;

    if(aux == NULL){
        cout << "Sin historial\n";
        return;
    }

    while(aux != NULL){
        cout << aux->orden << ". ";
        cout << aux->num << " -> ";
        cout << aux->tipo << endl;
        aux = aux->sig;
    }
}

void liberarArbol(NodoArbol *&r){
    if(r != NULL){
        liberarArbol(r->izq);
        liberarArbol(r->der);
        delete r;
        r = NULL;
    }
}

void construirBST(){
    liberarArbol(raiz);
    raiz = NULL;

    NodoPila *a = tope;
    while(a != NULL){
        insertarBST(raiz, a->num);
        a = a->sig;
    }

    NodoCola *b = frente;
    while(b != NULL){
        insertarBST(raiz, b->num);
        b = b->sig;
    }

    if(raiz == NULL){
        cout << "No hay datos positivos\n";
        return;
    }

    cout << "InOrden: ";
    inOrden(raiz);
    cout << endl;

    cout << "PreOrden: ";
    preOrden(raiz);
    cout << endl;

    cout << "PostOrden: ";
    postOrden(raiz);
    cout << endl;
}

void eliminarNegativos(){
    NodoLista *aux = lista;
    NodoLista *ant = NULL;
    int cont = 0;

    cout << "Lista original: ";
    mostrarLista();

    while(aux != NULL){
        if(abs(aux->num) < 10){
            NodoLista *temp = aux;

            if(aux == lista){
                lista = aux->sig;
                aux = lista;
            }else{
                ant->sig = aux->sig;
                aux = aux->sig;
            }

            delete temp;
            cont++;
        }else{
            ant = aux;
            aux = aux->sig;
        }
    }

    cout << "Lista resultante: ";
    mostrarLista();
    cout << "Eliminados: " << cont << endl;
}

void estadisticas(){
    cout << "Pares positivos: " << pares << endl;
    cout << "Impares positivos: " << impares << endl;
    cout << "Negativos: " << negativos << endl;
    cout << "Ceros rechazados: " << ceros << endl;
    cout << "Total validos: " << validos << endl;

    if(validos > 0){
        cout << "Mayor valor: " << mayor << endl;
        cout << "Menor valor: " << menor << endl;
    }
}

void reorganizar(){
    liberarArbol(raiz);
    raiz = NULL;

    NodoLista *l1 = NULL;
    NodoLista *l2 = NULL;

    while(tope != NULL){
        NodoLista *nuevo = new NodoLista();
        nuevo->num = tope->num;
        nuevo->sig = l1;
        l1 = nuevo;

        insertarBST(raiz, tope->num);

        NodoPila *temp = tope;
        tope = tope->sig;
        delete temp;
    }

    while(frente != NULL){
        NodoLista *nuevo = new NodoLista();
        nuevo->num = frente->num;
        nuevo->sig = l2;
        l2 = nuevo;

        insertarBST(raiz, frente->num);

        NodoCola *temp = frente;
        frente = frente->sig;
        delete temp;
    }

    fin = NULL;

    cout << "Lista auxiliar pila: ";
    NodoLista *a = l1;
    while(a != NULL){
        cout << a->num << " ";
        a = a->sig;
    }

    cout << endl;

    cout << "Lista auxiliar cola: ";
    NodoLista *b = l2;
    while(b != NULL){
        cout << b->num << " ";
        b = b->sig;
    }

    cout << endl;

    cout << "Nuevo BST InOrden: ";
    inOrden(raiz);
    cout << endl;
}

void liberarTodo(){

    while(tope != NULL){
        NodoPila *temp = tope;
        tope = tope->sig;
        delete temp;
    }

    while(frente != NULL){
        NodoCola *temp = frente;
        frente = frente->sig;
        delete temp;
    }

    while(lista != NULL){
        NodoLista *temp = lista;
        lista = lista->sig;
        delete temp;
    }

    while(hini != NULL){
        NodoDoble *temp = hini;
        hini = hini->sig;
        delete temp;
    }

    liberarArbol(raiz);
}

int main(){

    int opc, n, num, dato;

    do{
        cout << "\n1. Ingresar N numeros\n";
        cout << "2. Mostrar pila\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Mostrar lista negativos\n";
        cout << "5. Mostrar historial\n";
        cout << "6. Construir y mostrar BST\n";
        cout << "7. Eliminar negativos\n";
        cout << "8. Buscar valor en BST\n";
        cout << "9. Mostrar estadisticas\n";
        cout << "10. Reorganizar estructuras\n";
        cout << "11. Salir\n";
        cin >> opc;

        switch(opc){

        case 1:

            cout << "Cantidad: ";
            cin >> n;

            if(n <= 0){
                cout << "Dato invalido\n";
                break;
            }

            for(int i=1; i<=n; i++){

                cout << "Numero " << i << ": ";
                cin >> num;

                if(num == 0){
                    ceros++;
                }
                else if(num > 0 && num % 2 == 0){
                    encolar(num);
                    historial(num,"COLA");
                    pares++;
                    validos++;
                }
                else if(num > 0){
                    push(num);
                    historial(num,"PILA");
                    impares++;
                    validos++;
                }
                else{
                    insertarLista(num);
                    historial(num,"LISTA SIMPLE");
                    negativos++;
                    validos++;
                }

                if(num != 0){
                    if(primero){
                        mayor = num;
                        menor = num;
                        primero = false;
                    }else{
                        if(num > mayor) mayor = num;
                        if(num < menor) menor = num;
                    }
                }
            }

            break;

        case 2:
            mostrarPila();
            break;

        case 3:
            mostrarCola();
            break;

        case 4:
            mostrarLista();
            break;

        case 5:
            mostrarHistorial();
            break;

        case 6:
            construirBST();
            break;

        case 7:
            eliminarNegativos();
            break;

        case 8:
            cout << "Valor a buscar: ";
            cin >> dato;

            if(buscarBST(raiz,dato))
                cout << "Encontrado\n";
            else
                cout << "No encontrado\n";

            break;

        case 9:
            estadisticas();
            break;

        case 10:
            reorganizar();
            break;

        case 11:
            liberarTodo();
            cout << "Programa finalizado\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

        if(opc != 11)
            pausa();

    }while(opc != 11);

    return 0;
}