#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct das flores (aka produto):
typedef struct flowers
{
    char ID[3];
    float price;
    char name[20];
    char color[12];

} Flowers;

// declarando as funções para as opções do CRUD:
void header();
void addFlower();
void listAll();
void listByName();
void updateFlower();
void deleteFlower();

// main com o menu e as options:
int main()
{
    short option;

    // header:
    printf("\n\n--------------------------------");
    printf("\n----------- WELCOME ------------");
    printf("\n----------- TO THE  ------------");
    printf("\n--------- FLOWER SHOP ----------");
    printf("\n--------------------------------");
    printf("\n");

    do
    {
        printf("1 - Add new flower\n2 - List all flowers\n3 - Search by flower name\n4 - Update flowers info\n5 - Remove flower from the catalog\n0 - Exit\n\n");
        printf("Insert an option here: ");
        scanf("%d", &option);

        if (option == 1)
        {
            addFlower();
        }
        else if (option == 2)
        {
            listAll();
        }
        else if (option == 3)
        {
            listByName();
        }
        else if (option == 4)
        {
            updateFlower();
        }
        else if (option == 5)
        {
            deleteFlower();
        }

    } while (option != 0);
}
// inicializando as funções para as opções do CRUD:
void header()
{
    system("cls");
    printf("-----------------------------------\n\n");
    printf("------------ FLOWER SHOP ----------\n\n");
    printf("-----------------------------------\n\n");
}

void addFlower()
{
    // criando ponteiro para criar arquivo / abrindo arquivo:
    // abrindo no modo append
    FILE *p_Catalog_ADD = fopen("Catalog.txt", "ab");
    Flowers flower;
    short option_add;

    // testando se arquivo existe:
    if (p_Catalog_ADD == NULL)
    {
        printf("Cannot read file!\n");
    }
    else
    {
        // asking the user the details to add to the catalog:
        do
        {
            header();
            printf("Insert the ID of the flower (***): ");
            scanf("%s", flower.ID);
            printf("Insert the price of the flower: $");
            scanf("%f", &flower.price);
            printf("Insert the name of the flower: ");
            scanf("%s", flower.name);
            printf("Insert the color of the flower: ");
            scanf("%s", flower.color);

            // escrevendo dentro do arquivo previamente criado:
            fwrite(&flower, sizeof(Flowers), 1, p_Catalog_ADD);

            // double checking before going into the loop again:
            printf("\nFlower Added Successfully!\nDo you wish to keep adding? (1 to YES, 2 to NO): ");
            scanf("%d", &option_add);
            system("cls");
        } while (option_add != 2);
    }

    // fechando arquivo:
    fclose(p_Catalog_ADD);
}

// lendo oque foi armazenado no arquivo:
void listAll()
{
    FILE *p_Catalog_LIST;
    Flowers flower;
    header();

    p_Catalog_LIST = fopen("Catalog.txt", "rb");
    // testando se arquivo está vazio:
    if (p_Catalog_LIST == NULL)
    {
        printf("Cannot read file!\n");
    }

    else
    {
        while (fread(&flower, sizeof(Flowers), 1, p_Catalog_LIST))
        {
            printf("ID: %s\nPRICE: %.2f\nNAME: %s\nCOLOR: %s\n\n", flower.ID, flower.price, flower.name, flower.color);
        }
    }
    fclose(p_Catalog_LIST);
}

void listByName()
{
    char search_flower[20];
    FILE *p_Catalog_L_Name;
    Flowers flower;
    header();

    // abrindo arquivo:
    p_Catalog_L_Name = fopen("Catalog.txt", "rb");

    // testando se arquivo está vazio:
    if (p_Catalog_L_Name == NULL)
    {
        printf("Cannot read file!\n");
    }

    else
    {

        printf("Insert the name of the flower you wish to search: ");
        scanf("%s", &search_flower);

        while (fread(&flower, sizeof(Flowers), 1, p_Catalog_L_Name))
        {
            if (strcmp(search_flower, flower.name) == 0)
            {
                printf("\nID: %s\nPRICE: $%.2f\nNAME: %s\nCOLOR: %s\n\n", flower.ID, flower.price, flower.name, flower.color);
            }
        }
    }
    // fechando arquivo:
    fclose(p_Catalog_L_Name);
}

void updateFlower()
{
    header();
    FILE *p_Catalog_UPDATE;
    Flowers flower;
    char update[20];

    // abrindo arquivo
    p_Catalog_UPDATE = fopen("Catalog.txt", "r+b");

    // testando se arquivo está vazio:
    if (p_Catalog_UPDATE == NULL)
    {
        printf("Cannot read file!\n");
    }

    else
    {
        // perguntando qual flor quer atualizar:
        printf("Insert the name of the flower you wish to update: ");
        scanf("%s", &update);

        while (fread(&flower, sizeof(Flowers), 1, p_Catalog_UPDATE))
        {
            if (strcmp(update, flower.name) == 0)
            {
                //redireciona o p do arquivo para a flor que vai ser editada: 
                fseek(p_Catalog_UPDATE, sizeof(Flowers) * -1, SEEK_CUR); 

                // menu pra reescrever:
                printf("Insert the NEW ID of the flower (***): ");
                scanf("%s", flower.ID);
                printf("Insert the NEW price of the flower: $");
                scanf("%f", &flower.price);
                printf("Insert the NEW name of the flower: ");
                scanf("%s", flower.name);
                printf("Insert the NEW color of the flower: ");
                scanf("%s", flower.color);
                printf("\n");

                // escrevendo novamente no arquivo as info novas, na posição correta:
                fwrite(&flower, sizeof(Flowers), 1, p_Catalog_UPDATE); 

                // redefine o ponteiro pra apontar pro final do arquivo: 
                fseek(p_Catalog_UPDATE, sizeof(Flowers) * 0, SEEK_END);

                return;
            }
        }
    }
    // fechando arquivo
    fclose(p_Catalog_UPDATE);
}

void deleteFlower()
{
    header();
    FILE *p_Catalog_DELETE;
    FILE *p_Catalog_DELETE_T;
    Flowers flower;
    char delete_flower[20];

    // abrindo arquivo
    p_Catalog_DELETE = fopen("Catalog.txt", "rb");

    // testando se arquivo está vazio:
    // porque usando só o if n funfou?
    if (p_Catalog_DELETE == NULL)
    {
        printf("Cannot read file!\n");
    }
    else
    {
        // abrindo arquivo temporario
        p_Catalog_DELETE_T = fopen("TEMP_Catalog.txt", "a+b");

        printf("Insert the name of the flower you wish to delete: ");
        scanf("%s", delete_flower);
        printf("\n");

        // lendo arquivo principal
        while (fread(&flower, sizeof(Flowers), 1, p_Catalog_DELETE))
        {   
            // comparando struct por struct dentro do arquivo com a entrada do user: 
            if (strcmp(delete_flower, flower.name) == 0)
            {
                continue;
            }
            else // se n for igual, ele vai escrever no temp
                // ja que queremos deletar a flor igual a do user
            {   
                fwrite(&flower, sizeof(Flowers), 1, p_Catalog_DELETE_T);
            }
        }

        // fechando arquivo, deletando e recriando um novo dele:
        fclose(p_Catalog_DELETE);
        remove("Catalog.txt");
        p_Catalog_DELETE = fopen("Catalog.txt", "ab");

        freopen("TEMP_Catalog.txt", "rb", p_Catalog_DELETE_T);
        while (fread(&flower, sizeof(Flowers), 1, p_Catalog_DELETE_T))
        {
            fwrite(&flower, sizeof(Flowers), 1, p_Catalog_DELETE);
        }

        // fechando e deletando arquivo temporario:
        fclose(p_Catalog_DELETE_T);
        remove("TEMP_Catalog.txt");

        printf("Flower Deleted Successfuly!\n\n");
    }

    // fechando arquivo
    fclose(p_Catalog_DELETE);
}