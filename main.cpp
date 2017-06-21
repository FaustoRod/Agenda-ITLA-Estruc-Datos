#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct contacto
{
	string nombre, telefono, email;
	contacto *next;
};

class Agenda
{

private:
	contacto *inicio, *ultimo;
	int numeroContactos = 0;

public:
	bool activo = true;
	ofstream escritor;
	Agenda()
	{
	    escritor.open("agendatest.txt",ios::app);
		inicio = NULL;
		ultimo = NULL;
	}

	void EscribirContacto(string nombre, string telefono, string email, int index) {
		escritor << index <<" - Nombre: " << nombre << endl;
		escritor << "  Telefono: " << telefono << endl;
		escritor << "  Email: " << email << endl;
		escritor << "////////////////////////////////////////////////////" << endl;
		escritor << string(1,'\n');
	}

	void ReescribirContactos() {
		int posicion = 1;
		contacto *temp = new contacto;
		temp = inicio;

		while (temp != NULL) {
			EscribirContacto(temp->nombre,temp->telefono,temp->email,posicion);
;			temp = temp->next;
			posicion++;
		}

		cout << string(2, '\n');
	}

	void AgregarContacto()
	{
		string _nombre, _telefono, _email;
		int seguir;

		cout << "Ingrese el  nombre del contacto" << endl;
		cin >> _nombre;
		cout << "Ingrese el telefono" << endl;
		cin >> _telefono;
		cout << "Ingrese el email" << endl;
		cin >> _email;


		contacto *temp = new contacto;
		temp->nombre = _nombre;
		temp->telefono = _telefono;
		temp->email = _email;
		temp->next = NULL;

		if (inicio == NULL)
		{
			inicio = temp;
			ultimo = temp;
			temp = NULL;
		}
		else {
			ultimo->next = temp;
			ultimo = temp;
		}
		numeroContactos++;
		EscribirContacto(_nombre,_telefono,_email,numeroContactos);
		cout << "Contacto Agregado";

		system("CLS");
	}

	void MostrarContactos()
	{
		int posicion = 1;
		contacto *temp = new contacto;
		temp = inicio;

		if (numeroContactos == 0)
		{
			cout << string(2, '\n');
			cout << "No hay contactos en la Agenda" << endl;
		}
		else {
			while (temp != NULL) {
				cout << posicion << " - Nombre: " << temp->nombre  << endl;
				cout << "    "<< "Telefono: " << temp->telefono << endl;
				cout << "    "<< "Email: " << temp->email << endl;
				cout << string(2, '\n');
				temp = temp->next;
				posicion++;
			}
		}

		cout << string(2, '\n');
	};

	void EliminarContacto()
	{
		contacto *prev = new contacto;
		contacto *actu = new contacto;
		int pos;
		actu = inicio;

		if (numeroContactos == 0) {
			cout << string(3, '\n');
			cout << "No hay contactos para eliminar" << endl;
			cout << string(3, '\n');
		}
		else {

			MostrarContactos();

			cout << "Seleccione contacto a eliminar => " << endl;
			cin >> pos;
			while (!cin)
			{
				cout << "Valor no numerico" << endl;
				cout << "Ingrese posicion" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> pos;
			};

			if (pos > numeroContactos)
			{
				cout << "No hay un contacto en esa posicion" << endl;
				EliminarContacto();
			}
			else {
				for (int i = 1; i < pos; i++)
				{
					prev = actu;
					actu = actu->next;
				}

				prev->next = actu->next;
				cout << "Contacto eliminado " << string(3,'\n');
				numeroContactos--;
			}
		}

	};

	void EditarContacto() {
		int index = 0;
		string nNombre, nTelefono, nEmail;

		if(numeroContactos == 0){
			cout << "No hay contactos en la Agenda" << string(3,'\n');
			return;
		}
		MostrarContactos();
		system("pause");
		cout << "Seleccione un Contacto: " << endl;
		cin >> index;

		while (!cin)
		{
			cout << "Valor no numerico" << endl;
			cout << "Ingrese cantidad" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> index;
		};

		//index--;

		if(index < numeroContactos){
			cout << "No existe ese contacto " << string(3,'\n');
			return;
		}

		struct contacto* actual = inicio;
		int contador = 0;

		while (actual != NULL) {
			if (contador == index)
				cout << "Ingrese Nuevo Nombre: " << endl;
				cout << "Ingrese Nuevo Nombre: " << endl;
				cin >> actual->nombre;

				cout << "Ingrese Nuevo Telefono: " << endl;
				cin >> actual->telefono;

				cout << "Ingrese Nuevo Email: " << endl;
				cin >> actual->email;
			contador++;
			actual = actual->next;

		}

		system("CLS");

		ReescribirContactos();

	}


	void Iniciar()
	{
		int opcion;

		cout << "1- Listar Contactos" << endl;
		cout << "2- Introducir Contacto" << endl;
		cout << "3- Eliminar Contacto" << endl;
		cout << "4- Editar Contacto" << endl;
		cout << "5- Salir" << endl;

		cout << "Elija una opcion => ";
		cin >> opcion;
		while (!cin)
		{
			cout << "Valor no numerico" << endl;
			cout << "Ingrese opcion" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> opcion;
		};

		switch (opcion)
		{
		case 1:
			MostrarContactos();
			break;
		case 2:
			AgregarContacto();
			break;
		case 3:
			EliminarContacto();
			break;
		case 4:
			EditarContacto();
			break;
		case 5:
		    escritor.close();
			activo = false;
			break;
		default:
			cout << string(1,'\n');
			cout << "Opcion invalida" << endl;
			cout << string(1, '\n');
			break;
		}

	}

};

int main()
{
	Agenda agenda;

	while (agenda.activo)
	{
		agenda.Iniciar();
	}

	return 0;
};



