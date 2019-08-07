#include <iostream>
#include <fstream>

using namespace std;

struct Item {
	int codigo;
	char nombres[30];
	char apellidos[30];
	char ciudad[50];
	Item() {

	};
};

class ArchivoItem{

	private:
		int num_registros;

	public:
		int getNum_Registros() {
			return num_registros;
		}

		void setNum_Registros(int num_registros) {
			this->num_registros = num_registros;
		}


		void agregarRegistros(Item struct_item) {
			ofstream fileC("archivoRegistros.dat", ios::out | ios::app | ios::binary);
			if (!fileC) {
				cout << "Error de apertura en el archivo. " << endl;
				return;
			}
			else {
				fileC.seekp(0, ios::end);
				fileC.seekp((struct_item.codigo - 1) * sizeof(struct_item));
				fileC.write(reinterpret_cast<const char*>(&struct_item), sizeof(struct_item));
				fileC.close();
			}
				
		}
		//stcmrp
		//-1 menor 1 mayor

		void buscarNombreS(const char* lookName) {
			bool encontro = false;
			ifstream fileC("archivoRegistros.dat", ios::in | ios::binary);
			if (!fileC) {
				cout << "Error de aprtura en el archivo!" << endl;
			}

			fileC.seekg(0, ios::beg);
			Item struct_item;
			fileC.read(reinterpret_cast<char*>(&struct_item), sizeof(struct_item));

			while (!fileC.eof()) {
				char nomb[30];
				strcpy_s(nomb, struct_item.nombres);
				if (strcmp(lookName, nomb) == 0) { //si lo encuentra. 
					cout << "Codigo: " << struct_item.codigo << " Nombre: " << struct_item.nombres
						<< " Apellidos: " << struct_item.apellidos
						<< " Ciudad: " << struct_item.ciudad << endl;
					encontro = true;
					break;
				}
				fileC.read(reinterpret_cast<char*>(&struct_item), sizeof(struct_item));
			}

			if (!encontro) {
				cout << "No existe ningun registro con ese nombre. " << endl;
			}
			fileC.close();

		}

		void buscarNombreB(const char* lookName, int mitad,int izquierda, int derecha) {
			Item struct_item;

			ifstream fileC("archivoRegistros.dat", ios::in | ios::binary);
			if (!fileC) {
				cout << "Error de aprtura en el archivo!" << endl;
			}

			fileC.seekg((mitad - 1) * sizeof(struct_item));
			fileC.read(reinterpret_cast<char*>(&struct_item), sizeof(struct_item));

			int resultado = strcmp(lookName, struct_item.nombres);

			if (izquierda > derecha) {
				cout << "No existe el registro." << endl;

			} else if (resultado == 0) { //si lo encuentra. 
				cout << "Codigo: " << struct_item.codigo << " Nombre: " << struct_item.nombres
					<< " Apellidos: " << struct_item.apellidos
					<< " Ciudad: " << struct_item.ciudad << endl;
			}
			else { //se va a la izquierda
				int m = -20;
				if (resultado < 0)
					 m = mitad--;
				else
					 m = mitad++;
				
				m /= 2;
				buscarNombreB(lookName, m,m-1,m+1);
			}
		}

};