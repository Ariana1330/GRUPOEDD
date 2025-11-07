// ==================================================================================
// PARTE 4: MAIN, MENÚ PRINCIPAL Y GESTIÓN DE MEMORIA (PILA)
// Responsable: ORELLANA CONDEZO, CESAR DANIEL
// Descripción: Implementa la función main con el menú principal
//              y las funciones de gestión de memoria usando pila (push/pop)
// ==================================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Variables globales inicializadas
Proceso* listaProcesos = NULL;
NodoMemoria* pilaMemoria = NULL;
NodoCola* colaCPU = NULL;

// Declaración de funciones externas (de las otras partes)
extern void cargarProcesosDesdeArchivo();
extern void insertarProceso();
extern void listarProcesos();
extern void eliminarProceso();
extern void buscarProceso();
extern void modificarPrioridad();
extern void ordenarProcesos();
extern void encolarCPU();
extern void ejecutarCPU();
extern void mostrarColaCPU();

// ==================== FUNCIONES DE GESTIÓN DE MEMORIA ====================

// 10. Asignación de memoria (Push en la pila)
void pushMemoria() {
    string id;
    cout << "Ingrese el ID del proceso para asignar memoria: ";
    cin >> id;
    
    NodoMemoria* nuevo = new NodoMemoria;
    nuevo->procesoID = id;
    nuevo->siguiente = pilaMemoria;
    pilaMemoria = nuevo;
    
    cout << "Memoria asignada correctamente al proceso.\n";
    system("pause");
    system("CLS");
}

// 11. Liberación de memoria (Pop en la pila)
void popMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria ya esta vacia.\n";
    } else {
        cout << "Liberando memoria del proceso ID: " << pilaMemoria->procesoID << "\n";
        NodoMemoria* temp = pilaMemoria;
        pilaMemoria = pilaMemoria->siguiente;
        delete temp;
    }
    system("pause");
    system("CLS");
}

// 12. Estado actual de la pila de memoria
void mostrarMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria esta vacia.\n";
    } else {
        NodoMemoria* temp = pilaMemoria;
        int pos = 1;
        while (temp) {
            cout << "Posicion " << pos++ << ": " << temp->procesoID << "\n";
            temp = temp->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

// ==================== MAIN ====================
int main() {
    cargarProcesosDesdeArchivo();
    ofstream limpiar("procesos.txt");
    limpiar.close();
    
    int opcion;
    do {
        // Menú de opciones
        cout << "\n======= GESTOR DE PROCESOS Y MEMORIA =======\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Listar procesos (sin ordenar)\n";
        cout << "3. Eliminar proceso por ID\n";
        cout << "4. Buscar proceso por ID\n";
        cout << "5. Modificar prioridad de un proceso\n";
        cout << "6. Ordenar procesos por prioridad (Mayor -> Menor)\n";
        cout << "7. Encolar proceso a la cola CPU\n";
        cout << "8. Ejecutar (desencolar) proceso con mayor prioridad\n";
        cout << "9. Visualizar cola actual (ordenada)\n";
        cout << "10. Asignar memoria (push)\n";
        cout << "11. Liberar memoria (pop)\n";
        cout << "12. Ver estado actual de memoria\n";
        cout << "13. Salir\n";
        
        do {
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            if (opcion < 1 || opcion > 13) {
                cout << "Opcion no valida.\n";
                system("pause");
                system("CLS");
            }
        } while (opcion < 1 || opcion > 13);
        
        switch (opcion) {
            case 1: insertarProceso(); break;
            case 2: listarProcesos(); break;
            case 3: eliminarProceso(); break;
            case 4: buscarProceso(); break;
            case 5: modificarPrioridad(); break;
            case 6: ordenarProcesos(); break;
            case 7: encolarCPU(); break;
            case 8: ejecutarCPU(); break;
            case 9: mostrarColaCPU(); break;
            case 10: pushMemoria(); break;
            case 11: popMemoria(); break;
            case 12: mostrarMemoria(); break;
            case 13: cout << "Saliendo...\n"; break;
        }
    } while (opcion != 13);
    
    return 0;
}
