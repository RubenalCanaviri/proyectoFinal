#include <iostream>
#include "structures.h"
#include <fstream>
#include <stdlib.h>
#include "callFunctions.h"
#include <cstring>

using namespace std;


// Prototipos
void addProduct();
void addN_product();
void displayAllProducts();
int generateCodeProduct();
void displayProductsByCategory();
void deleteProduct();
//-----------------------

void addProduct()
{
    ofstream productFile;
    Product _product;

    productFile.open("inventory.bin", ios:: binary | ios:: app);

    if (productFile.fail())
    {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    _product.codeProd = generateCodeProduct();
    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    cin.getline(_product.nameProduct, sizeof(_product.nameProduct));
    cout << "Ingrese el precio: ";
    cin >> _product.price;
    cout << "Ingrese el stock: ";
    cin >> _product.stock;
    cout << "Ingrese la categoria: ";
    cin.ignore();
    cin.getline(_product.category, sizeof(_product.category));
    cout << "Ingrese la fecha de expedicion: ";
    cin.ignore();
    cin.getline(_product.dateOfSale, sizeof(_product.dateOfSale));
    cout << "Ingrese la fecha de vencimiento: ";
    cin.ignore();
    cin.getline(_product.dueDate, sizeof(_product.dueDate));

    productFile.write((char*)&_product, sizeof(Product));

    productFile.close();

    cout << "Producto adicionado." << endl;

};

void addN_product()
{
    int n;
    cout << "Cuantos productos deseas adicionar: ";
    cin.ignore();
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        addProduct();
    }
};  

void displayAllProducts()
{
    ifstream productFile;

    Product _product;

    productFile.open("inventory.bin", ios:: binary);

    if (productFile.fail())
    {
        cout << "El archivo no se pudo abrir.";
        exit(1);
    }
    
    cout << "\t CODIGO"<< "\t NOMBRE" << "\t\t PRECIO" << "\t\t STOCK" << "\t\t CATEGORIA" << "\t\t F. EXPEDICION" << "\t\t F. VENCIMIENTO" << endl;
    while (productFile.read((char*)&_product, sizeof(Product)))
    {
        cout << "\t   " << _product.codeProd << "\t" <<  _product.nameProduct << "\t" <<  _product.price << "\t" <<  _product.stock << "\t" <<  _product.category << "\t" <<  _product.dateOfSale << "\t" <<  _product.dueDate << endl;
    }

    productFile.close();
};

void displayProductsByCategory()
{

    ifstream productFile;
    Product _product;

    productFile.open("inventory.bin", ios:: binary);

    int option = 0;
    if (productFile.fail())
    {
        cout << "El archivo no se pudo abrir." << endl;
        exit(1);
    }
    
    do
    {
        cout << "Categorias:" << endl;
        cout << "1. Gaseosas, 2. Cervezas: ";
        cin >> option;

        if (option != 1 and option !=2)
        {
            cout << "Numero no valido." << endl;
        }
        
    } while (option != 1 and option !=2);
    
    cout << "\t CODIGO" << "\t NOMBRE" << "\t PRECIO" << "\t STOCK" << "\t CATEGORIA" << "\t F. EXPEDICION" << "\t F. VENCIMIENTO" << endl;
    while (productFile.read((char*)&_product, sizeof(Product)))
    {
        if (option == 1)
        {
            if (strcmp("Gaseosas", _product.category) == 0)
            {
                cout << _product.codeProd << _product.nameProduct << _product.price << _product.stock << _product.category << _product.dateOfSale << _product.dueDate << endl;
            }   
        } else
        {
            if (strcmp("Cervezas", _product.category) ==0)
            {
                cout << _product.codeProd << _product.nameProduct << _product.price << _product.stock << _product.category << _product.dateOfSale << _product.dueDate << endl;
            }
        }
    }    

}

void deleteProduct()
{
    displayAllProducts();
    ifstream productFile;
    ofstream tempFile;

    productFile.open("inventory.bin", ios::binary);
    tempFile.open("temporal.bin", ios::binary | ios::app);

    if (productFile.fail())
    {
        cout << "El archivo de inventarios no se pudo abrir. " << endl;
        exit(1);
    } else if (tempFile.fail())
    {
        cout << "El archivo de inventarios no se pudo abrir. " << endl;
        exit(1);
    }
    Product _product;

    int codigo;
    cout << "Ingrese codigo del producto a eliminar: ";
    cin >> codigo;

    while (productFile.read((char*)&_product, sizeof(Product)))
    {
        if (_product.codeProd != codigo)
        {
            tempFile.write((char*)&_product, sizeof(Product));
        }
        
    }

    tempFile.close();
    productFile.close();
    
    remove("inventory.bin");
    rename("temporal.bin", "inventory.bin");
    
    
};

int generateCodeProduct() {

    ifstream productFile;
    Product _product;

    productFile.open("inventory.bin", ios::binary);
    int contador = 0;
    while (productFile.read((char*)&_product, sizeof(Product)))
    {
        contador += 1;
    }
    productFile.close();
    return contador+1;   
}