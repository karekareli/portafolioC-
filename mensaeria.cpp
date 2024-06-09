#include <iostream>
#include <vector>

using namespace std;

class Observer {
public:
    virtual void historial(vector<string> mensajes) = 0;
    virtual string getNombre() = 0;
};

class MyChat {
private:
    vector<Observer*> alumnos;
    vector<string> mensajes;

public:
    void registerUser(Observer* alumno) {
        alumnos.push_back(alumno);
    }

    void send(string mensaje, string remitente) {
        for (Observer* alumno : alumnos) {
            cout << remitente << " dice : " << mensaje << " a " << alumno->getNombre() << endl;
        }
        mensajes.push_back(mensaje);
        notify(); 
    }

    void notify() {
        for (Observer* alumno : alumnos) {
            alumno->historial(mensajes);
        }
    }
};

class Alumno : public Observer {
private:
    string nombre;

public:
    Alumno(string nombre) : nombre(nombre) {}

    void historial(vector<string> mensajes) override {
        cout << "-------------------------------------" << endl;
        cout << "Historial de: " << nombre << endl;
        for (string mensaje : mensajes) {
            cout << mensaje << endl;
        }
        cout << "-------------------------------------" << endl;
    }

    string getNombre() override {
        return nombre;
    }
};

int main() {
    MyChat chat;

    Alumno alumno1("Jesus");
    Alumno alumno2("Sofia");

    chat.registerUser(&alumno1);
    chat.registerUser(&alumno2);

    chat.send("¿Cómo están?", "Profesor");
    chat.send("Se hace envío de sus tareas", "Profesor");
    chat.send("Y de sus notas", "Profesor");

    return 0;
}
