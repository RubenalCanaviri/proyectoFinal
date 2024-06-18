#ifndef STRUCTURES_H
#define STRUCTURE_H

struct User
{

    long id;
    char firstName[21];
    char lastName[21];
    long identityCard;
    char password[21];
    char email[21];
    long phoneNumber;
    char birthdate[11];
    char accountCreationDate[11];
    char department[11];
    char address[51];
    long points;
};

struct Product
{

    int codeProd;
    char nameProduct[16];
    float price;
    int stock;
    char category[16];
    char dateOfSale[11];
    char dueDate[11];

};

struct Admin
{
    long id;
    char firstName[21];
    char lastName[21];
    long identityCard;
    char password[21];
    char email[21];
    long phoneNumber;
    char birthdate[11];
    char accountCreationDate[11];
    char department[11];
    char address[51];

};

#endif