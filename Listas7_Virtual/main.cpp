/*7. Agregar el siguiente comportamiento al programa anterior:
- Cuando el sistema arranca, carga de los archivos las listas del punto anterior.
- Se presenta al usuario un menú que permite:
o Buscar un alumno y ver sus datos por Legajo.
o Listar materias aprobadas de un alumno (se ingresa legajo).
o Listar el promedio de un alumno (se ingresa legajo).
o Agregar un alumno.
o Agregar materia aprobada a un alumno.
o Salir del programa: Debe insertar en los archivos correspondientes los
registros que se hayan agregado en la ejecución y liberar toda la memoria
solicitada.
*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Materia
{
    char NombreMateria[50];
    char Fechadeaprobacion[11];
    int Legajo;
    int Nota;
    int Libro;
    int Folio;
};
struct NodoMaterias
{
    Materia info;
    NodoMaterias *sgte;
};
struct alumno
{
    char Nombre[50];
    char Apellido[50];
    char DNI[10];
    int Legajo;
    int CodigoCarrera;
    NodoMaterias *listamaterias=NULL;
};
struct NodoAlumnos
{
    alumno info;
    NodoAlumnos *sgte;
};

void creararchivo()
{
    FILE *f;
    f=fopen("DatosAlumnos.txt","wb");
    alumno a;

    strcpy(a.Nombre,"Karen");
    strcpy(a.Apellido,"Garcia");
    strcpy(a.DNI,"34612343");
    a.Legajo= 1252337;
    a.CodigoCarrera= 2;
    fwrite(&a,sizeof(alumno),1,f);

    strcpy(a.Nombre,"Veronica");
    strcpy(a.Apellido,"Arias");
    strcpy(a.DNI,"34689543");
    a.Legajo= 1386128;
    a.CodigoCarrera= 2;
    fwrite(&a,sizeof(alumno),1,f);

    strcpy(a.Nombre,"Maximiliano");
    strcpy(a.Apellido,"Kempes");
    strcpy(a.DNI,"36234712");
    a.Legajo= 1279845;
    a.CodigoCarrera= 2;
    fwrite(&a,sizeof(alumno),1,f);
    fclose(f);
}

void creararchmaterias()
{
    FILE *f;
    f=fopen("DatosMaterias.txt","wb");
    Materia m;

    strcpy(m.NombreMateria,"Analisis Matematico");
    strcpy(m.Fechadeaprobacion,"13-08-20");
    m.Nota=10;
    m.Legajo=1386128;
    m.Libro= 034;
    m.Folio= 832;
    fwrite(&m,sizeof(Materia),1,f);

    strcpy(m.NombreMateria,"Quimica");
    strcpy(m.Fechadeaprobacion,"12-06-20");
    m.Nota=7;
    m.Legajo=1252337;
    m.Libro= 828;
    m.Folio= 543;
    fwrite(&m,sizeof(Materia),1,f);

    strcpy(m.NombreMateria,"Algebra");
    strcpy(m.Fechadeaprobacion,"28-09-20");
    m.Nota=7;
    m.Legajo=1386128;
    m.Libro= 628;
    m.Folio= 283;
    fwrite(&m,sizeof(Materia),1,f);

    fclose(f);
    return;
}

void leerarchivo(NodoAlumnos *&lista)
{
    FILE *f;
    NodoAlumnos *paux=NULL;
    f=fopen("DatosAlumnos.txt","rb");
    alumno a;
    while(fread(&a,sizeof(alumno),1,f))
    {
        if(!lista)
        {
            lista=new NodoAlumnos();
            lista->info=a;
            lista->sgte=NULL;
            paux=lista;
        }
        else
        {
            while(paux && paux->sgte)
                paux=paux->sgte;
            paux->sgte=new NodoAlumnos();
            paux=paux->sgte;
            paux->info=a;
            paux->sgte=NULL;
        }
    }
    fclose(f);
    return;
}

NodoAlumnos* BuscarAlumnoPorLegajo(NodoAlumnos *raiz, int legajobuscado)
{
    NodoAlumnos *p=raiz;
    while (p && p->info.Legajo!=legajobuscado)
    {
        p = p->sgte;
    }
    return p;
}

void ListaMateriaInsertarSiguiente(NodoMaterias *&slista, Materia mat)
{
    NodoMaterias *nuevo= new NodoMaterias();//Se crea un nuevo nodo en ListaMaterias
    nuevo->info=mat;//En ese nodo se vuelca toda la info del arhivo
    if (slista!=NULL)//Si n es difernete de null
    {
        nuevo->sgte= slista->sgte;//nuevo->sgte se mueve a n->sgte
        slista->sgte = nuevo;//n->sgte es igual a nuevo
    }
    else//si n es igual a NULL
    {
        nuevo->sgte=slista;//nuevo->sgte avanza a n
        slista=nuevo;//n es igual a nuevo
    }
    return;
}
//Inserta la sublista de materias en su correspondiente nodo alumno
void asignarmaterias(NodoAlumnos *&lista)
{
    FILE *f;
    f=fopen("DatosMaterias.txt","rb");
    Materia m;
    while(fread(&m,sizeof(Materia),1,f))
    {
        NodoAlumnos *aux=BuscarAlumnoPorLegajo(lista,m.Legajo);//Devuelve la direccion de memoria
        //Se inserta la lista y el legajo que tiene el arcivo
        if (aux)//Si existe lo inserta
        {
            ListaMateriaInsertarSiguiente(aux->info.listamaterias,m);//Crea la sublsita materias
            //aux->info.listamaterias es donde empieza la sublista y m es el arhivo correspondiente
        }
    }
    fclose(f);
    return;
}

void ListaMateriaListar(NodoMaterias *lista)
{
    while (lista)
    {
        cout << "Nombre: " << lista->info.NombreMateria<< endl;
        cout << "Fecha: " << lista->info.Fechadeaprobacion<< endl;
        cout << "Nota: " << lista->info.Nota<< ", Libro: " << lista->info.Libro << ", Folio: " << lista->info.Folio<< endl;
        cout << "---------------------------------" << endl;
        lista = lista->sgte;
    }
}

void mostraralumno(NodoAlumnos *lista, int legajo)
{
    NodoAlumnos *aux=BuscarAlumnoPorLegajo(lista,legajo);
    if(aux)
    {
        cout << "Nombre:     " << aux->info.Nombre << endl;
        cout << "Apellido:   " << aux->info.Apellido << endl;
        cout << "DNI:        " << aux->info.DNI << endl;
        cout << "CodCarrera: " << aux->info.CodigoCarrera << endl;
        cout << "Legajo:     " << aux->info.Legajo << endl;
        cout << "---------------------------------" << endl;
        //ListaMateriaListar(aux->info.listamaterias);
    }
    else
    {
        cout << "No se encontro el alumno" << endl;
    }
    return;
}

void mostrarmatporleg(NodoAlumnos *lista, int legajo)
{//Busca con la clave foranea
    NodoAlumnos *aux=BuscarAlumnoPorLegajo(lista,legajo);//Devuelve la direccion de memoria
    if(aux)//Si existe entra
    {
        ListaMateriaListar(aux->info.listamaterias);//Muestra las materias en la sublista
    }
    else//Si no existe muestra mensaje
    {
        cout << "No se encontro el alumno" << endl;
    }
    return;
}

float buscarnota(NodoMaterias *lista)
{
    int sum=0,cont=0;
    float prom;
    while(lista)
    {
        cout << "Nota: " << lista->info.Nota << endl;
        sum=(lista->info.Nota)+sum;
        cont++;
        lista=lista->sgte;
    }
    prom=sum/cont;
    return prom;
}

void buscarpromedio(NodoAlumnos *lista,int leg)
{
    NodoAlumnos *aux=BuscarAlumnoPorLegajo(lista,leg);
    float prom;
    if(aux)
    {
        prom=buscarnota(aux->info.listamaterias);
        cout << "El promedio del alumno es: " << prom << endl;
    }
    else
        cout << "ERROR: No se encontro el alumno!" << endl;
    cout << "---------------------------------" << endl;
    return;
}

void agregaralumno(NodoAlumnos *&lista)
{
    NodoAlumnos *paux=lista;
    while(paux && paux->sgte)
    {
        paux=paux->sgte;
    }
    paux->sgte=new NodoAlumnos();
    paux=paux->sgte;
    cout << "Ingrese Nombre: " << endl;
    cin >> paux->info.Nombre;
    cout << "Ingrese Apellido: " << endl;
    cin >> paux->info.Apellido;
    cout << "Ingrese DNI: " << endl;
    cin >> paux->info.DNI;
    cout << "Ingrese Legajo: " << endl;
    cin >> paux->info.Legajo;
    cout << "Ingrese Codigo de carrera:" << endl;
    cin >> paux->info.CodigoCarrera;
    cout << "INGRESO EXITOSO" << endl;
    cout << "---------------------------" << endl;
    return;
}

void agregardatos(NodoMaterias *&mat,int leg)
{
    NodoMaterias *aux=mat;
    if(!mat)
    {
        mat=new NodoMaterias();
        mat->info.Legajo=leg;
        cout << "Ingrese nombre de la materia: " << endl;
        cin >> mat->info.NombreMateria;
        cout << "Ingrese Nota: " << endl;
        cin >> mat->info.Nota;
        cout << "Ingrese Folio: " << endl;
        cin >> mat->info.Folio;
        cout << "Ingrese Libro: " << endl;
        cin >> mat->info.Libro;
        mat->sgte=aux;
    }
    else
    {
        while(aux->sgte)
        {
           aux=aux->sgte;
        }
        aux->sgte=new NodoMaterias();
        aux=aux->sgte;
        aux->info.Legajo=leg;
        cout << "Ingrese Nombre de la materia: " << endl;
        cin >> aux->info.NombreMateria;
        cout << "Ingrese Nota: " << endl;
        cin >> aux->info.Nota;
        cout << "Ingrese Fecha de Aprobacion:" << endl;
        cin >> aux->info.Fechadeaprobacion;
        cout << "Ingrese Folio: " << endl;
        cin >> aux->info.Folio;
        cout << "Ingrese Libro: " << endl;
        cin >> aux->info.Libro;
        aux->sgte=NULL;
    }
    return;
}

void agregarmateria(NodoAlumnos *&lista,int leg)
{
    NodoAlumnos *aux=BuscarAlumnoPorLegajo(lista,leg);
    if(aux)
    {
        agregardatos(aux->info.listamaterias,leg);
    }
    else
        cout << "ERROR: No se ha encontrado el alumno!" << endl;
    return;
}

void mostrar(NodoAlumnos *&lista)
{
    NodoAlumnos *paux=lista;
    while(paux)
    {
        cout << "Nombre:     " << paux->info.Nombre << endl;
        cout << "Apellido:   " << paux->info.Apellido << endl;
        cout << "DNI:        " << paux->info.DNI << endl;
        cout << "CodCarrera: " << paux->info.CodigoCarrera << endl;
        cout << "Legajo:     " << paux->info.Legajo << endl;
        cout << "--------------------------------" << endl;
        paux=paux->sgte;
    }
    return;
}
//Desde la lista hacia el archivo
void insertarenarchivo(NodoAlumnos *&lista)
{
    NodoAlumnos *paux=lista;
    NodoMaterias *paux2=NULL;
    FILE *f;
    FILE *f2;
    f=fopen("DatosAlumnos.txt","wb");
    f2=fopen("DatosMaterias.txt","wb");
    alumno a;
    Materia m;
     while(paux)//Mientras exista la lista
     {
         a=paux->info;//Vuelva la info del nodo al buffer alumno
         fwrite(&a,sizeof(alumno),1,f);//Lo escribe en el arhivo
         paux2=paux->info.listamaterias;//
         while(paux2)
         {
             m=paux2->info;
             fwrite(&m,sizeof(Materia),1,f2);
             paux2=paux2->sgte;
         }
         paux=paux->sgte;
     }
    fclose(f);
    fclose(f2);
    return;
}

void ListaMateriaborrarLista(NodoMaterias *&lista)
{
    NodoMaterias *anterior;
    NodoMaterias *paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux= lista;
        while (paux && paux->sgte)
        {
            anterior = paux;
            paux= paux->sgte;
        }
        if (paux)
        {
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista =NULL;
        }
    }
    return;
}
void ListaAlumnoborrarLista(NodoAlumnos *&lista)
{
    NodoAlumnos *anterior;
    NodoAlumnos *paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux= lista;
        while (paux && paux->sgte)
        {
            anterior = paux;
            paux= paux->sgte;
        }
        if (paux)
        {
            ListaMateriaborrarLista(paux->info.listamaterias);
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista =NULL;
        }
    }
    return;
}
void menu()
{
    cout << "0.Levantar archivos" << endl;
    cout << "1.Buscar un alumno y ver sus datos por legajo" << endl;
    cout << "2.Listar materias aprobadas de un alumno (se ingresa legajo)." << endl;
    cout << "3.Listar el promedio de un alumno (se ingresa legajo)." << endl;
    cout << "4.Agregar un alumno." << endl;
    cout << "5.Agregar materia aprobada a un alumno." << endl;
    cout << "Esc.Salir" << endl;
    return;
}

int main()
{
    NodoAlumnos *inicio=NULL;
    int legajo,opcion;
    creararchivo();
    creararchmaterias();
    do
    {
        do
        {
            menu();
            cout << "Ingrese una opcion: ";
            cin >> opcion;
        }
        while(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4 && opcion!=5 && opcion!=27);
        switch(opcion)
        {
        case 0:
            cout << "Levantar archivos" << endl;
            leerarchivo(inicio);
            asignarmaterias(inicio);
            break;
        case 1:
            cout << "Ingrese el legajo del alumno: " << endl;
            cin >> legajo;
            cout << "  " << endl;
            mostraralumno(inicio,legajo);
            break;
        case 2:
            cout << "Ingrese el legajo del alumno: " << endl;
            cin >> legajo;
            cout << "  " << endl;
            mostrarmatporleg(inicio,legajo);
            break;
        case 3:
            cout << "Ingrese el legajo del alumno: " << endl;
            cin >> legajo;
            cout << "  " << endl;
            buscarpromedio(inicio,legajo);
            break;
        case 4:
            agregaralumno(inicio);
            break;
        case 5:
            cout << "Ingrese el legajo del alumno: " << endl;
            cin >> legajo;
            cout << "  " << endl;
            agregarmateria(inicio,legajo);
            break;
        }
    }
    while(opcion!=27);
    insertarenarchivo(inicio);
    mostrar(inicio);
    ListaAlumnoborrarLista(inicio);
    return 0;
}
