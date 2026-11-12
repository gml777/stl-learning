#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath> 

using namespace std;

struct Estudiante {
    string nombre;
    int anioNacimiento;
    float gpa;
    float presupuesto;
};

float calcularIndiceUniv(const Estudiante& est) {
    return abs(est.gpa - 3.0f) * est.presupuesto;
}

void imprimirEstudiantes(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "-> El vector esta vacio.\n";
        return;
    }
    
    cout << "\n--- LISTA DE ESTUDIANTES ---\n";
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const auto& est = estudiantes[i];
        cout << "[" << i << "] Nombre: " << est.nombre 
             << " | Anio: " << est.anioNacimiento 
             << " | GPA: " << est.gpa 
             << " | Presupuesto: " << est.presupuesto 
             << " | Indice Univ: " << calcularIndiceUniv(est) << "\n";
    }
    cout << "----------------------------\n";
}

int main() {
    vector<Estudiante> estudiantes; 
    int opcion = 0;

    do {
        cout << "\n=============== MENU ESTUDIANTES ===============\n";
        cout << "1. Insertar estudiante\n";
        cout << "2. Eliminar estudiante\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Ordenar estudiantes\n";
        cout << "5. Imprimir vector\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "================================================\n";

        switch (opcion) {
            case 1: {
                int tipoDatos, posicion;
                cout << "Tipo de datos (1: Por defecto [NN,0,0,0], 2: Personalizados): ";
                cin >> tipoDatos;
                
                Estudiante nuevoEstudiante;
                if (tipoDatos == 1) {
                    nuevoEstudiante = {"NN", 0, 0.0f, 0.0f};
                } else {
                    cout << "Ingrese Nombre, Anio, GPA y Presupuesto (separados por espacio):\n";
                    cin >> nuevoEstudiante.nombre >> nuevoEstudiante.anioNacimiento 
                        >> nuevoEstudiante.gpa >> nuevoEstudiante.presupuesto;
                }

                cout << "Ubicacion (1: Al final, 2: Indice especifico): ";
                cin >> posicion;

                if (posicion == 1) {
                    estudiantes.push_back(nuevoEstudiante); 
                    cout << "-> Insertado al final exitosamente.\n";
                } else {
                    int idx;
                    cout << "Ingrese el indice (0 a " << estudiantes.size() << "): ";
                    cin >> idx;

                    if (idx >= 0 && idx <= static_cast<int>(estudiantes.size())) {
                        estudiantes.insert(estudiantes.begin() + idx, nuevoEstudiante);
                        cout << "-> Insertado en el indice " << idx << " exitosamente.\n";
                    } else {
                        cout << "-> ERROR: Indice fuera de rango.\n";
                    }
                }
                break;
            }

            case 2: {
                if (estudiantes.empty()) {
                    cout << "-> ERROR: No se puede eliminar, el vector esta vacio.\n";
                    break;
                }

                int modoEliminar;
                cout << "Como eliminar? (1: Ultimo elemento, 2: Desde un indice): ";
                cin >> modoEliminar;

                if (modoEliminar == 1) {
                    estudiantes.pop_back();
                    cout << "-> Ultimo estudiante eliminado exitosamente.\n";
                } else {
                    int idx;
                    cout << "Ingrese el indice a eliminar (0 a " << estudiantes.size() - 1 << "): ";
                    cin >> idx;
                    if (idx >= 0 && idx < static_cast<int>(estudiantes.size())) {
                        estudiantes.erase(estudiantes.begin() + idx);
                        cout << "-> Estudiante eliminado exitosamente.\n";
                    } else {
                        cout << "-> ERROR: Indice fuera de rango.\n";
                    }
                }
                break;
            }

            case 3: {
                if (estudiantes.empty()) {
                    cout << "-> ERROR: El vector esta vacio, no hay datos para actualizar.\n";
                    break;
                }

                int idx;
                cout << "Ingrese el indice del estudiante a actualizar (0 a " << estudiantes.size() - 1 << "): ";
                cin >> idx;

                if (idx >= 0 && idx < static_cast<int>(estudiantes.size())) {
                    cout << "Ingrese los NUEVOS datos (Nombre Anio GPA Presupuesto):\n";
                    cin >> estudiantes[idx].nombre >> estudiantes[idx].anioNacimiento 
                        >> estudiantes[idx].gpa >> estudiantes[idx].presupuesto;
                    cout << "-> Estudiante actualizado exitosamente.\n";
                } else {
                    cout << "-> ERROR: Indice fuera de rango.\n";
                }
                break;
            }

            case 4: {
                if (estudiantes.empty()) {
                    cout << "-> ERROR: El vector esta vacio.\n";
                    break;
                }

                int modoOrdenar;
                cout << "Ordenar por (1: Anio, 2: GPA, 3: Presupuesto, 4: Indice Univ.): ";
                cin >> modoOrdenar;

                if (modoOrdenar == 1) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.anioNacimiento < b.anioNacimiento;
                    });
                } else if (modoOrdenar == 2) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.gpa < b.gpa;
                    });
                } else if (modoOrdenar == 3) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.presupuesto < b.presupuesto;
                    });
                } else if (modoOrdenar == 4) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return calcularIndiceUniv(a) < calcularIndiceUniv(b);
                    });
                } else {
                    cout << "-> ERROR: Opcion invalida.\n";
                    break;
                }
                cout << "-> Vector ordenado exitosamente.\n";
                break;
            }

            case 5:
                imprimirEstudiantes(estudiantes);
                break;

            case 6:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
                break;
        }

    } while (opcion != 6);

    return 0;
}