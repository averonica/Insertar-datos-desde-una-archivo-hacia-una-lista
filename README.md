# Insertar-datos-desde-una-archivo-hacia-una-lista
Programa que lee desde un archivo datos de alumnos de un curso, que a medida que el archivo se va leyendo va insertando los registros en una lista.

Siendo la estructura "Alumnos" la siguiente:

```
Nombre char[50]
Apellido char[50]
DNI char[10]
Legajo int
CodigoCarrera int
```
Esructura "Materia":
```
Nombre de la materia char[50]
Fecha de aprobación char[11]
Nota int
Legajo int
Libro int
Folio int
```

Ademas lee otro archivo de materias aporbadas, utilizando como clave foranea entre "Materias" y "Alumnos" la variable Legajo.
- Cuando el sistema arranca, carga de los archivos.
- Se presenta al usuario un menú que permite:
1. Buscar un alumno y ver sus datos por Legajo.
2. Listar materias aprobadas de un alumno (se ingresa legajo).
3. Listar el promedio de un alumno (se ingresa legajo).
4. Agregar un alumno.
5. Agregar materia aprobada a un alumno.
6. Salir del programa.
Cuando el usuarion decide salir, posteriormente el programa inserta en los archivos correspondientes los
registros que se hayan agregado en la ejecución y libera toda la memoria solicitada.

veronica/Insertar-datos-desde-una-archivo-hacia-una-lista
### Arias, Verónica Yanina
