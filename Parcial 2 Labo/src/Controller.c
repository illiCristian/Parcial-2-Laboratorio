#include <stdio.h>
#include <stdlib.h>

#include "Libro.h"
#include "Editorial.h"
#include "LinkedList.h"
#include "Parser.h"

//static int saveId(char* PATH, int auxId);


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(LinkedList* pArrayListLibros, int (*pFunc) (FILE*, LinkedList*))
{
	int retorno;
	retorno =-1;
	char nombreArchivo[50];

	PedirCadenaB(nombreArchivo, "Ingrese el nombre del archivo");
	FILE* pFile;

		if(pArrayListLibros!=NULL)
		    {
		       pFile = fopen (nombreArchivo, "r");
		       if(pFile!=NULL && pArrayListLibros != NULL)
		            {
		    	      retorno =pFunc(pFile,pArrayListLibros);
		            }
		        fclose(pFile);
		    }

	    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)

{

	int retorno = -1;

	FILE*pFile = fopen(path, "rb");

	if (pFile != NULL)
	{

		retorno = parser_LibroFromBinary(pFile, pArrayListEmployee);
	}

	return retorno;
}

/*int controller_loadFromTextEditorial(LinkedList* pArrayListEditorial)
{
	int retorno;
	retorno =-1;
	char cadena[50];
	PedirCadenaB(cadena, "Ingrese el nombre del archivo que desea leer");
	FILE* pFile;

		if(path!=NULL && pArrayListEditorial!=NULL)
		    {
		       pFile = fopen (path, "r");
		       if(pFile!=NULL && pArrayListEditorial != NULL)
		            {
		     	   	   parser_EditorialFromText(pFile, pArrayListEditorial);
		    	   	   retorno =0;
		            }
		        fclose(pFile);
		    }
	    return retorno;
}*/

int controller_ListLibros(LinkedList* pArrayListLibros, LinkedList* listaEditoriales)
{
	int retorno;
	int len;
	eLibro* pLibro;


	retorno =-1;
	printf("\nID\t\tTITULO\t\tAUTOR\tPRECIO\tID EDITORIAL\n");

	len = ll_len(pArrayListLibros);
	if(pArrayListLibros != NULL)
	{
	    for(int i=0;i<len;i++)
			{
	    	pLibro =(eLibro*)ll_get(pArrayListLibros,i);
			imprimirUnLibro(pLibro,listaEditoriales);
			retorno =0;
			}
	}
	printf("\nID\t\tTITULO\t\tAUTOR\tPRECIO\tID EDITORIAL\n");

    return retorno;
}

int controller_ListEditoriales(LinkedList* pArrayListEditoriales)
{
	int retorno;
	int len;
	eEditorial* pEditorial;

	retorno =-1;
	printf("\nID\t\tTITULO\t\tAUTOR\tPRECIO\tID EDITORIAL\n");

	len = ll_len(pArrayListEditoriales);
	if(pArrayListEditoriales != NULL)
	{
	    for(int i=0;i<len;i++)
			{
	    		pEditorial =(eEditorial*)ll_get(pArrayListEditoriales,i);
				imprimirUnaEditorial(pEditorial);
				retorno =0;
			}
	}
	printf("\nID\t\tTITULO\t\tAUTOR\tPRECIO\tID EDITORIAL\n");

    return retorno;
}



/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortLibros(LinkedList* pArrayListLibros, LinkedList* pArrayEditoriales)
{
		int retorno = -1;
		int menu;

		if (pArrayListLibros != NULL)
		{

			menu = MostrarMenuB();
			switch (menu)
			{

			case 1:
				if(ll_sort(pArrayListLibros,libro_CompararPorAutor,1)!=-1)
				{
					retorno = 0;
				}
				controller_ListLibros(pArrayListLibros, pArrayEditoriales);

				break;
			case 2:
				ll_sort(pArrayListLibros,libro_CompararPorAutor,0);
				controller_ListLibros(pArrayListLibros, pArrayEditoriales);

				break;

			}
		}
		else
		{
			printf("No se ingresan datos \n");
		}

		return retorno;

}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListLibro)
{
	int   retorno = -1;
	int   tamLista;

	int   id;
	char  titulo[20];
	char  autor[20];
	float precio;
	int   idEditorial;

	  if (path != NULL && pArrayListLibro != NULL)
	    {

	        tamLista = ll_len(pArrayListLibro);

	        FILE *pFile = fopen(path, "w");

	        if (pFile != NULL)
	        {

	            eLibro* pLibro = Libro_new();


	            fprintf(pFile,"id,titulo,autor,precio,idEditorial\n");

	            for (int i = 0; i < tamLista; i++)
	            {
	                pLibro = (eLibro*) ll_get(pArrayListLibro, i);
	                if(Libro_getId(pLibro, &id)!=-1
	                &&Libro_getTitulo(pLibro, titulo) !=-1
					&&Libro_getAutor(pLibro, autor)!=-1
	                &&Libro_getPrecio(pLibro, &precio) !=-1
					&&Libro_getIdEditorial(pLibro, &idEditorial)!=-1)
	                {
	                	fprintf(pFile,"%d,%s,%s,%.2f,%d\n",id,titulo,autor,precio,idEditorial);
	                }

	            }
	            retorno = 0;
	            fclose(pFile);
	        }
	    }
	    return retorno;
}

int controller_filtrarLibros(LinkedList* listaLibros,LinkedList* listaEditoriales)
{

	int retorno = -1;

	LinkedList* listaFiltrada = ll_newLinkedList();

	listaFiltrada= ll_filter(listaLibros,filtrarMinotauro);

	if(controller_saveAsText("MINOTAURO.csv",listaFiltrada)!=-1)
	{
		retorno = 0;
	}


	printf("_______________________________________________________________\n"
		"    [Message]: Lista listaFiltrada y guardada como MINOTAURO.csv\n");

	controller_ListLibros(listaFiltrada, listaEditoriales);

	return retorno;
}



/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
/*int controller_saveAsBinary(char* path , LinkedList* pArrayListLibro)
{

	int retorno = -1;

	FILE* pFile;

	pFile = fopen(path, "wb"); // escribe en binario

	eLibro* pLibro;

	int tamLista = ll_len(pArrayListLibro);

	if (pArrayListLibro != NULL)
	{
		for (int i = 0; i < tamLista; i++)
		{
			pLibro = (eLibro*) ll_get(pArrayListLibro, i);

			fwrite(pLibro, sizeof(eLibro), 1, pFile);
		}

		fclose(pFile);

		retorno = 0;

	}
	else
	{
		printf("No hay Datos\n");
	}

	return retorno;
}

*/

/*static int saveId(char* PATH, int auxId)
{
	int retorno;
	retorno =-1;
	FILE* pFile;

	if(PATH != NULL)
	{

		pFile= fopen(PATH,"w");
		if (pFile!=NULL)
		{
			fprintf(pFile,"%d",auxId);
			retorno = 0;
			fclose(pFile);
		}

	}

	return retorno;
}
*/


