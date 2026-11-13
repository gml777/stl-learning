#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Estudiante {
private:
    string nombre;
    int anioNacimiento;
    float gpa;
    float presupuesto;

public:
    Estudiante(string nom = "NN", int anio = 0, float prom = 0.0f, float pres = 0.0f)
        : nombre(nom), anioNacimiento(anio), gpa(prom), presupuesto(pres) {}

    string getNombre() const { return nombre; }
    int getAnioNacimiento() const { return anioNacimiento; }
    float getGpa() const { return gpa; }
    float getPresupuesto() const { return presupuesto; }

    void setDatos(const string& nom, int anio, float prom, float pres) {
        nombre = nom;
        anioNacimiento = anio;
        gpa = prom;
        presupuesto = pres;
    }

    float calcularIndiceUniv() const {
        return abs(gpa - 3.0f) * presupuesto;
    }
};

void imprimirEstudiantes(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "-> El vector esta vacio.\n";
        return;
    }

    cout << "\n---------------------------- LISTA DE ESTUDIANTES ----------------------------\n";
    cout << left << setw(6) << "IDX"
         << setw(14) << "NOMBRE"
         << setw(10) << "ANIO"
         << setw(10) << "GPA"
         << setw(16) << "PRESUPUESTO"
         << "INDICE UNIV.\n";
    cout << "------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        const auto& est = estudiantes[i];
        cout << "[" << i << "]   "
             << left << setw(14) << est.getNombre()
             << setw(10) << est.getAnioNacimiento()
             << fixed << setprecision(2) << setw(10) << est.getGpa()
             << setw(16) << est.getPresupuesto()
             << est.calcularIndiceUniv() << "\n";
    }
    cout << "------------------------------------------------------------------------------\n";
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
                    nuevoEstudiante = Estudiante("NN", 0, 0.0f, 0.0f);
                } else {
                    string nom;
                    int anio;
                    float prom, pres;
                    cout << "Ingrese Nombre, Anio, GPA y Presupuesto (separados por espacio):\n";
                    cin >> nom >> anio >> prom >> pres;
                    nuevoEstudiante = Estudiante(nom, anio, prom, pres);
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
                    string nom;
                    int anio;
                    float prom, pres;
                    cout << "Ingrese los NUEVOS datos (Nombre Anio GPA Presupuesto):\n";
                    cin >> nom >> anio >> prom >> pres;
                    estudiantes[idx].setDatos(nom, anio, prom, pres);
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
                        return a.getAnioNacimiento() < b.getAnioNacimiento();
                    });
                } else if (modoOrdenar == 2) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.getGpa() < b.getGpa();
                    });
                } else if (modoOrdenar == 3) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.getPresupuesto() < b.getPresupuesto();
                    });
                } else if (modoOrdenar == 4) {
                    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
                        return a.calcularIndiceUniv() < b.calcularIndiceUniv();
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
