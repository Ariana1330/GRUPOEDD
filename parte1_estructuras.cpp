// ==================================================================================
// PARTE 1: ESTRUCTURAS DE DATOS Y GESTIÓN 
// Responsable: ENRIQUE RICCE, ANGELA ARIANA
// Descripción: Define las estructuras de datos (Proceso, NodoMemoria, NodoCola)
//              y maneja la persistencia de datos en archivos
// ==================================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ==================== ESTRUCTURAS ====================

// Nodo para lista enlazada de procesos
struct Proceso {
    string id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
    
    Proceso(string _id, string _nombre, int _prioridad) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        siguiente = NULL;
    }
};

// Nodo para pila (gestión de memoria)
struct NodoMemoria {
    string procesoID;
    NodoMemoria* siguiente;
};

// Cola de prioridad basada en lista enlazada ordenada
struct NodoCola {
    string id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};

// ==================== VARIABLES GLOBALES ====================
extern Proceso* listaProcesos;
extern NodoMemoria* pilaMemoria;
extern NodoCola* colaCPU;

// ==================== FUNCIONES DE ARCHIVOS ====================

// Busca un proceso por su ID en la lista
Proceso* buscarProcesoPorID(string id) {
    Proceso* actual = listaProcesos;
    while (actual) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

// Guarda todos los procesos de la lista en un archivo de texto
void guardarProcesosEnArchivo() {
    ofstream archivo("procesos.txt");
    Proceso* actual = listaProcesos;
    while (actual) {
        archivo << "ID: " << actual->id << ", "
                << "Nombre: " << actual->nombre << ", "
                << "Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }
    archivo.close();
}

// Carga los procesos almacenados previamente en el archivo "procesos.txt"
void cargarProcesosDesdeArchivo() {
    ifstream archivo("procesos.txt");
    string id, nombre;
    int prioridad;
    
    while (archivo >> id >> nombre >> prioridad) {
        if (buscarProcesoPorID(id) == NULL) {
            Proceso* nuevo = new Proceso(id, nombre, prioridad);
            if (!listaProcesos) {
                listaProcesos = nuevo;
            } else {
                Proceso* temp = listaProcesos;
                while (temp->siguiente) temp = temp->siguiente;
                temp->siguiente = nuevo;
            }
        }
    }
    archivo.close();
}
