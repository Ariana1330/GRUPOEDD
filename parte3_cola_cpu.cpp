// ==================================================================================
// PARTE 3: COLA DE CPU Y ORDENAMIENTO DE PROCESOS
// Responsable: URIBE OLIVA ELIAS XAVIER
// Descripción: Implementa el algoritmo de ordenamiento por prioridad
//              y gestiona la cola de CPU para ejecución de procesos
// ==================================================================================

#include <iostream>
#include <string>
using namespace std;

// Variables externas
extern Proceso* listaProcesos;
extern NodoCola* colaCPU;
extern void guardarProcesosEnArchivo();
extern void listarProcesos();

// ==================== FUNCIONES AUXILIARES ====================

// Verifica si un proceso ya está en la cola de CPU
bool procesoYaEnCola(string id) {
    NodoCola* temp = colaCPU;
    while (temp) {
        if (temp->id == id) return true;
        temp = temp->siguiente;
    }
    return false;
}

// ==================== FUNCIONES DE ORDENAMIENTO Y COLA ====================

// 6. Ordena los procesos por prioridad (mayor prioridad primero)
void ordenarProcesos() {
    if (!listaProcesos || !listaProcesos->siguiente) {
        cout << "No hay suficientes procesos para ordenar.\n";
        system("pause");
        system("CLS");
        return;
    }
    
    // Algoritmo de burbuja adaptado a lista enlazada
    bool intercambiado;
    do {
        intercambiado = false;
        Proceso* actual = listaProcesos;
        Proceso* anterior = NULL;
        
        while (actual && actual->siguiente) {
            Proceso* siguiente = actual->siguiente;
            
            // Compara prioridades para intercambiar
            if (actual->prioridad < siguiente->prioridad) {
                if (anterior) {
                    anterior->siguiente = siguiente;
                } else {
                    listaProcesos = siguiente;
                }
                actual->siguiente = siguiente->siguiente;
                siguiente->siguiente = actual;
                anterior = siguiente;
                intercambiado = true;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
    } while (intercambiado);
    
    guardarProcesosEnArchivo();
    cout << "Procesos ordenados por prioridad (Mayor -> Menor).\n";
    listarProcesos();
    system("pause");
    system("CLS");
}

// 7. Encola todos los procesos a la cola de CPU, ordenados por prioridad
void encolarCPU() {
    Proceso* actual = listaProcesos;
    
    while (actual) {
        if (!procesoYaEnCola(actual->id)) {
            NodoCola* nuevo = new NodoCola;
            nuevo->id = actual->id;
            nuevo->nombre = actual->nombre;
            nuevo->prioridad = actual->prioridad;
            nuevo->siguiente = NULL;
            
            if (!colaCPU || nuevo->prioridad < colaCPU->prioridad) {
                nuevo->siguiente = colaCPU;
                colaCPU = nuevo;
            } else {
                NodoCola* temp = colaCPU;
                while (temp->siguiente && temp->siguiente->prioridad <= nuevo->prioridad)
                    temp = temp->siguiente;
                nuevo->siguiente = temp->siguiente;
                temp->siguiente = nuevo;
            }
        }
        actual = actual->siguiente;
    }
    
    cout << "Procesos encolados a la CPU segun prioridad.\n";
    system("pause");
    system("CLS");
}

// 8. Desencola y ejecuta el proceso con mayor prioridad
void ejecutarCPU() {
    if (!colaCPU) {
        cout << "No hay procesos en la cola.\n";
        system("pause");
        system("CLS");
        return;
    }
    
    NodoCola* temp = colaCPU;
    colaCPU = colaCPU->siguiente;
    
    cout << "Ejecutando proceso:\n";
    cout << "ID: " << temp->id 
         << " | Nombre: " << temp->nombre 
         << " | Prioridad: " << temp->prioridad << "\n";
    
    delete temp;
    system("pause");
    system("CLS");
}

// 9. Muestra todos los procesos en la cola de CPU
void mostrarColaCPU() {
    if (!colaCPU) {
        cout << "La cola esta vacia.\n";
    } else {
        cout << "Cola actual (ordenada por prioridad):\n";
        NodoCola* temp = colaCPU;
        while (temp) {
            cout << "ID: " << temp->id 
                 << " | Nombre: " << temp->nombre 
                 << " | Prioridad: " << temp->prioridad << "\n";
            temp = temp->siguiente;
        }
    }
    system("pause");
    system("CLS");
}
