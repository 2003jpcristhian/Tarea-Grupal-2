#include <iostream>

using namespace std;

const char *nombre_archivo = "archivo.dat";
struct Traductor{
	char p_ing[50];
	char p_esp[50];
};
void Leer();
void Crear();
void Actualizar();
void Borrar();

main(){
   int opcion;
    do {
    	cout<<"_______________________________________"<<endl;
        cout << "Fase I - Administracion de Palabras" << endl;
        cout << "1. Crear Palabra" << endl;
        cout << "2. Leer Palabras" << endl;
        cout << "3. Actualizar Palabra" << endl;
        cout << "4. Eliminar Palabra" << endl;
        cout<<"--------------------------------------"<<endl;
        cout << "Fase II - Traduccion de Codigo C++" << endl;
        cout << "5. Traducir Codigo" << endl;
        cout << "6. Salir" << endl;
        cout<<"_______________________________________"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                Crear();
                break;
            case 2:
                Leer();
                break;
            case 3:
				Actualizar();
			case 4:
				Borrar();
				break;
			case 5:
				break;
            default:
                cout << "Opcion no valida. Por favor, seleccione una opcion valida." << endl;
        }
    } while (opcion != 6);
	
	
	system("pause");
}

void Leer(){
	system("cls");
	FILE* archivo= fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo= fopen(nombre_archivo, "w+b");
	}
	Traductor traductor;
	int id= 0;
	fread(&traductor,sizeof(Traductor),1,archivo);
	cout<<"________________________________"<<endl;
	cout<<"ID"<<"|"<<"English  "<<"="<<"Spanish      "<<endl;
	do{
		cout<<id<<"|"<<traductor.p_ing<<" = "<<traductor.p_esp<<endl;
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;
		
	}while(feof(archivo)==0);
	fclose(archivo);
}

void Crear(){
	
	
	FILE* archivo= fopen(nombre_archivo,"a+b");
	char res;
	do{
		fflush(stdin);
		Traductor traductor;
		Leer();
		cout<<"Ingres palabra en Ingles: ";
		cin>> traductor.p_ing;
		cout<< "Ingrese la traduccion de la palabra: ";
		cin>> traductor.p_esp;
		fwrite(&traductor,sizeof(Traductor),1,archivo);	
		cout<<"Desea ingrear otro palabra: (s/n)";
		cin>> res;		
	}while(res== 's'||res== 'S');
	fclose(archivo);
	Leer();
}

void Actualizar(){
	FILE* archivo= fopen(nombre_archivo,"r+b");
	Traductor traductor;
	int id= 0;
	Leer();
	cout<<"Ingrse el ID que desea modificar: ";
	cin>>id;
	fseek(archivo,id * sizeof(traductor),SEEK_SET);
	cout<<"Ingres palabra en Ingles: ";
	cin>> traductor.p_ing;
	cout<< "Ingrese la traduccion de la palabra: ";
	cin>> traductor.p_esp;
	fwrite(&traductor, sizeof(Traductor),1,archivo);
	fclose(archivo);
	Leer();
}

void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo= fopen(nombre_archivo, "rb");
	FILE* archivo_temp= fopen(nombre_archivo_temp, "w+b");
	Traductor traductor;
	int id= 0, id_n= 0;
	Leer();
	cout<<"Ingrese el Id a eliminar: ";
	cin>> id;
	while(fread(&traductor, sizeof(Traductor),1, archivo)){
		if(id_n!= id){
			fwrite(&traductor, sizeof(traductor),1, archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp= fopen(nombre_archivo_temp,"rb");
	archivo= fopen(nombre_archivo, "w+b");
	while(fread(&traductor, sizeof(traductor), 1, archivo_temp)){
		fwrite(&traductor, sizeof(traductor), 1, archivo);
	}
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}
