#include <iostream>
using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int año;

public:
    Fecha(int d = 1, int m = 1, int a = 1900) : dia(d), mes(m), año(a) {}

    bool añobisiesto() const {
        return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
    }

    int ultimodia() const {
        if (mes == 2) {
            return añobisiesto() ? 29 : 28;
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    void nuevafecha(int d, int m, int a) {
        dia = d;
        mes = m;
        año = a;
    }

    Fecha& operator++() {
        dia++;
        if (dia > ultimodia()) {
            dia = 1;
            mes++;
            if (mes > 12) {
                mes = 1;
                año++;
            }
        }
        return *this;
    }

    Fecha& operator--() {
        dia--;
        if (dia < 1) {
            mes--;
            if (mes < 1) {
                mes = 12;
                año--;
            }
            dia = ultimodia();
        }
        return *this;
    }

    Fecha& operator+=(const Fecha& f) {
        dia += f.dia;
        while (dia > ultimodia()) {
            dia -= ultimodia();
            mes++;
            if (mes > 12) {
                mes -= 12;
                año++;
            }
        }
        mes += f.mes;
        while (mes > 12) {
            mes -= 12;
            año++;
        }
        año += f.año;
        return *this;
    }

    Fecha& operator-=(const Fecha& f) {
        dia -= f.dia;
        while (dia < 1) {
            mes--;
            if (mes < 1) {
                mes += 12;
                año--;
            }
            dia += ultimodia();
        }
        mes -= f.mes;
        while (mes < 1) {
            mes += 12;
            año--;
        }
        año -= f.año;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Fecha& fecha) {
        os << fecha.dia << '/' << fecha.mes << '/' << fecha.año;
        return os;
    }

    friend istream& operator>>(istream& is, Fecha& fecha) {
        is >> fecha.dia >> fecha.mes >> fecha.año;
        return is;
    }
};

int main() {
    Fecha fecha;

    cout << "Fecha inicial (d m a con espacios):" << endl;
    cin >> fecha;

    cout << "Fecha inicial: " << fecha << endl;

    char opcion;
    Fecha sumafecha;

    do {
        cout << "\nSeleccione la operacion:" << endl;
        cout << "1. Aumentar un dia (++)" << endl;
        cout << "2. Restar un día (--)" << endl;
        cout << "3. Sumar una fecha (+=)" << endl;
        cout << "4. Restar una fecha (-=)" << endl;
        cout << "5. Salir" << endl;

        cin >> opcion;

        switch (opcion) {
            case '1':
                ++fecha;
                break;
            case '2':
                --fecha;
                break;
            case '3':
                cout << "Fecha a sumar (Ingresar con espacios en el mismo orden: d m a): ";
                cin >> sumafecha;
                fecha += sumafecha;
                break;
            case '4':
                cout << "Fecha a restar (Ingresar con espacios en el mismo orden: d m a): ";
                cin >> sumafecha;
                fecha -= sumafecha;
                break;
            case '5':
                cout << "Programa finalizado" << endl;
                break;
            default:
                cout << "No válido" << endl;
                break;
        }

        if (opcion != '5') {
            cout << "Fecha resultante: " << fecha << endl;
        }
    } while (opcion != '5');

    return 0;
}