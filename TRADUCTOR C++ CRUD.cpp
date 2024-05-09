#include <iostream>
using namespace std;

const char *nombre_archivo = "Traductor.dat";

struct Traduc{
	int codigo;
	char palabra[50];
	char traduccion[50];
	char funcion[100];
};

void leer();
void crear();
void actualizar();
void eliminar();

main(){
	
	leer();
	crear();
	//actualizar();
	//eliminar();
	
	system("pause");
}

void leer(){
	system("cls");
	
	FILE* Traductor = fopen(nombre_archivo, "rb");
	if (!Traductor){
		Traductor = fopen(nombre_archivo, "w+b");
	}
	
	Traduc traduc;
	int id=1; //Posición de una palabra, dentro de nuestro archivo.
	
	fread(&traduc, sizeof(Traduc),1,Traductor);
	
	cout<<"			|TRADUCTOR C++|							"<<endl;
	cout<<"_____________________________________________________________"<<endl;
	cout<<"ID"<<"|"<<"Codigo"<<"|"<<"Palabra"<<"|"<<"	Traduccion	"<<endl;
	
	do{
		cout<<id<<" "<<"|"<<"  "<<traduc.codigo<<"  "<<"|"<<traduc.palabra<<"    "<<"|"<<traduc.traduccion<<endl;
		fread(&traduc,sizeof(Traduc),1,Traductor);
		id+=1;
	}while(feof(Traductor)==0);
	fclose(Traductor);
}

void crear(){
	FILE* Traductor = fopen(nombre_archivo,"a+b");
	
	char res;
	Traduc traduc;
	
	do{
		fflush(stdin);
		
		cout<<"Ingrese Codigo: ";
		cin>>traduc.codigo;
		cin.ignore();
		
		cout<<"Ingrese una palabra: ";
		cin.getline(traduc.palabra, 60); 
		cout<<"Ingrese su traduccion: ";
		cin.getline(traduc.traduccion, 100); 
		
		fwrite(&traduc,sizeof(Traduc),1,Traductor);
		
		cout<<"Desea ingresar otro estudiante(s/n): ";
		cin>>res;
	}while(res=='s' || res=='s');
	
	fclose(Traductor); 
	leer();
}

void actualizar(){
	FILE* Traductor = fopen(nombre_archivo,"r+b");
	
	Traduc traduc;
	int id=1;
	cout<<"Ingrese el ID que desea modificar: "<<endl;
	cin>>id;
	fseek(Traductor,id * sizeof(Traduc),SEEK_SET);
	
		cout<<"Ingrese Codigo: ";
		cin>>traduc.codigo;
		cin.ignore();
		
		cout<<"Ingrese una palabra: ";
		cin.getline(traduc.palabra, 60); 
		cout<<"Ingrese su traduccion: ";
		cin.getline(traduc.traduccion, 100);
		
		fwrite(&traduc,sizeof(Traduc),1,Traductor);
	
	fclose(Traductor); 
	leer();
}

void eliminar(){
	const char *nombre_archivo_temp = "Traductor_temp.dat";
	
	FILE* Traductor_temp = fopen(nombre_archivo_temp, "w+b");
	FILE* Traductor = fopen(nombre_archivo, "rb");
	Traduc traduc;
	
	int id=1, id_n=1;
	
	cout<<"Ingrese el ID a eliminar: ";
	cin>>id;
	
	while(fread(&traduc, sizeof(Traduc),1,Traductor)){
		if (id_n !=id ){
			fwrite(&traduc,sizeof(Traduc),1,Traductor_temp);
		}
		id_n++;
	}
	
	fclose(Traductor_temp);
	fclose(Traductor);
	
	Traductor_temp = fopen(nombre_archivo_temp, "rb");
	Traductor = fopen(nombre_archivo, "wb");
	while(fread(&traduc,sizeof(Traduc),1,Traductor_temp)){
		fwrite(&traduc,sizeof(Traduc),1,Traductor);
	}
	fclose(Traductor);
	fclose(Traductor_temp);
}
