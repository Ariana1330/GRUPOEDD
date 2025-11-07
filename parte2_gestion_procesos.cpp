// ==================================================================================
// PARTE 2: GESTIÓN DE PROCESOS 
// Responsable: MARQUEZ ENRIQUEZ, JAVIER EDUARDO
// Descripción: Funciones para insertar, listar, eliminar, buscar y modificar procesos
//              Operaciones básicas de la lista enlazada de procesos
// ==================================================================================

#include <iostream>
#include <string>
using namespace std;

// Variables externas (definidas en main o parte 1)
extern Proceso* listaProcesos;
extern Proceso* buscarProcesoPorID(string id);
extern void guardarProcesosEnArchivo();

// ==================== FUNCIONES DE GESTIÓN DE PROCESOS ====================

// 1. Función para insertar un nuevo proceso ingresado por el usuario
void insertarProceso() {
    string id, nombre;
    int prioridad;
    
    cout << "Ingrese ID del proceso (entero): ";
    cin >> id;
    
    // Evita que se repita un proceso con el mismo ID
    if (buscarProcesoPorID(id)) {
        cout << "Ya existe un proceso con ese ID.\n";
        system("pause");
        system("CLS");
        return;
    }
    
    cout << "Ingrese nombre del proceso: ";
    cin >> nombre;
    
    // Validamos Prioridad
    do {
        cout << "Ingrese prioridad (entero del 1 al 10): ";
        cin >> prioridad;
        if (prioridad < 1 || prioridad > 10) {
            cout << "\tError (entero del 1 al 10) .... \n";
        }
    } while (prioridad < 1 || prioridad > 10);
    
    // Crea e inserta el proceso al final de la lista
    Proceso* nuevo = new Proceso(id, nombre, prioridad);
    if (!listaProcesos) {
        listaProcesos = nuevo;
    } else {
        Proceso* actual = listaProcesos;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    
    guardarProcesosEnArchivo();
    system("pause");
    system("CLS");
}

// 2. Lista todos los procesos existentes en la lista
void listarProcesos() {
    if (!listaProcesos) {
        cout << "No hay procesos registrados.\n";
    } else {
        Proceso* actual = listaProcesos;
        cout << "Lista de procesos:\n";
        while (actual) {
            cout << "ID: " << actual->id 
                 << " | Nombre: " << actual->nombre 
                 << " | Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

// 3. Elimina un proceso por su ID
void eliminarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a eliminar: ";
    cin >> id;
    
    Proceso* actual = listaProcesos;
    Proceso* anterior = NULL;
    
    while (actual && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (!actual) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }
    
    if (!anterior) {
        listaProcesos = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    
    delete actual;
    guardarProcesosEnArchivo();
    cout << "Proceso eliminado correctamente.\n";
    system("pause");
    system("CLS");
}

// 4. Busca y muestra un proceso por ID
void buscarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a buscar: ";
    cin >> id;
    
    Proceso* resultado = buscarProcesoPorID(id);
    if (resultado) {
        cout << "Proceso encontrado:\n";
        cout << "ID: " << resultado->id 
             << " | Nombre: " << resultado->nombre 
             << " | Prioridad: " << resultado->prioridad << "\n";
    } else {
        cout << "Proceso no encontrado.\n";
    }
    system("pause");
    system("CLS");
}

// 5. Permite cambiar la prioridad de un proceso
void modificarPrioridad() {
    string id;
    cout << "Ingrese el ID del proceso: ";
    cin >> id;
    
    Proceso* p = buscarProcesoPorID(id);
    if (!p) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }
    
    int nuevaPrioridad;
    cout << "Prioridad actual: " << p->prioridad << "\n";
    
    // Validamos Prioridad del 1 al 10
    do {
        cout << "Ingrese nueva prioridad: ";
        cin >> nuevaPrioridad;
        if (nuevaPrioridad < 1 || nuevaPrioridad > 10) {
            cout << "\tError (entero del 1 al 10) .... \n";
        }
    } while (nuevaPrioridad < 1 || nuevaPrioridad > 10);
    
    p->prioridad = nuevaPrioridad;
    guardarProcesosEnArchivo();
    cout << "Prioridad modificada correctamente.\n";
    system("pause");
    system("CLS");
}
