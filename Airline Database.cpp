#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <string.h>
struct fleet
{
    char manuf[21];
    char model[21];
    char reg_number[7];
    int capacity;
    int fab_year;
}a;
void display_fleet();
void add();
void edit();
void del();
int main()
{
    char i;
    printf("D - Display the entire fleet\n");
    printf("A - Add a new aircraft to the fleet\n");
    printf("E - Edit an aircraft\n");
    printf("L - Delete an aircraft\n");
    printf("X - Exit\n");
    i = _getch();
    if (i == 'D' || i == 'd') display_fleet();
    else if (i == 'A' || i == 'a') add();
    else if (i == 'E' || i == 'e') edit();
    else if (i == 'L' || i == 'l') del();
    else if (i == 'X' || i == 'x') return 0;
    else
    {
        printf("Invalid chioce, returning to the main screen:\n\n");
        main();
    }
}
void display_fleet()//1
{
    FILE* DB;
    DB = fopen("DataB.txt", "r");
    fseek(DB, 0, SEEK_END);
    if (ftell(DB) == 0) printf("\n-------------EMPTY FILE, ADD NEW AIRCRAFTS----------------\n\n");
    else
    {
        fseek(DB, 0, SEEK_SET);
        char line[256] = "";
        int nr = 1;
        printf("\n-----------------SHOWING THE ENTIRE FLEET-----------------");
        while (fgets(line, sizeof(line), DB))
        {
            char* e = strtok(line, ", ");
            printf("\n%s%d", "Aircraft no. ", nr);
            printf("\n%s", "Manufacturer: ");
            printf("%s", e);
            e = strtok(NULL, ", ");
            printf("\n%s", "Model: ");
            printf("%s", e);
            e = strtok(NULL, ", ");
            printf("\n%s", "Registration number: ");
            printf("%s", e);
            e = strtok(NULL, ", ");
            printf("\n%s", "Capacity: ");
            printf("%s%s", e, " people");
            e = strtok(NULL, ", ");
            printf("\n%s", "Year of fabrication: ");
            printf("%s", e);
            printf("\n");
            nr++;
        }
        printf("\n----------------------------------------------------------\n\n");
    }
    fclose(DB);
    main();
}
void add()//2
{
    FILE* DB;
    DB = fopen("DataB.txt", "a");
    printf("---------------------------ADD----------------------------");
    printf("\nEnter the aircraft manufacturer: ");
    scanf("%s", a.manuf);
    fprintf(DB, "%s", a.manuf);
    fprintf(DB, "%s", ", ");
    printf("Enter the aircraft model: ");
    scanf("%s", a.model);
    fprintf(DB, "%s", a.model);
    fprintf(DB, "%s", ", ");
    printf("Enter the aircraft registration number: ");
    scanf("%s", a.reg_number);
    fprintf(DB, "%s", a.reg_number);
    fprintf(DB, "%s", ", ");
    printf("Enter the aircraft capacity: ");
    scanf("%d", &a.capacity);
    fprintf(DB, "%d", a.capacity);
    fprintf(DB, "%s", ", ");
    printf("Enter the aircraft year of production: ");
    scanf("%d", &a.fab_year);
    fprintf(DB, "%d", a.fab_year);
    fprintf(DB, "%s", ",");
    fprintf(DB, "\n");
    printf("----------------------------------------------------------");
    printf("\n");
    fclose(DB);
    main();
}
void edit()//3
{
    FILE* DB;
    DB = fopen("DataB.txt", "r");
    fseek(DB, 0L, SEEK_END);
    if (ftell(DB) == 0)
    {
        printf("\n--------------THERE ARE NO AIRCRAFTS TO EDIT--------------\n\n");
        fclose(DB);
    }
    else
    {
        fseek(DB, 0, SEEK_SET);
        FILE* DBtmp;
        DBtmp = fopen("DataB_tmp.txt", "w");
        printf("--------------------------EDIT----------------------------");
        char line[256] = "", c, am, ch;
        int i = 1, l, count = 0;
        for (c = getc(DB); c != EOF; c = getc(DB))
            if (c == '\n')count++;
        printf("\nWhich aircraft you want to modify (nr)? ");
        am = _getch();
        printf("%c\n", am);
        l = am - '0';
        if (l > count || l <= 0)
        {
            printf("Invalid choice, returning to the main screen\n");
            printf("-----------------------------------------------------------\n");
            fclose(DB);
            fclose(DBtmp);
            remove("DataB_tmp.txt");
        }
        else
        {
            printf("\nWhat would you like to edit (nr)?");
            printf("\nAircraft manufacturer 1");
            printf("\nAircraft model 2");
            printf("\nAircraft registration number 3");
            printf("\nAircraft capacity 4");
            printf("\nAircraft year of production 5\n");
            printf("\nYour choice: ");
            ch = _getch();
            if (ch == '1')
            {
                printf("Type the new manufacturer: ");
                scanf("%s", a.manuf);
            }
            if (ch == '2')
            {
                printf("Type the new model: ");
                scanf("%s", a.model);
            }
            if (ch == '3')
            {
                printf("Type the new registration number: ");
                scanf("%s", a.reg_number);
            }
            if (ch == '4')
            {
                printf("Type the new capacity: ");
                scanf("%d", &a.capacity);
            }
            if (ch == '5')
            {
                printf("Type the new year of production: ");
                scanf("%d", &a.fab_year);
            }
            if (ch < '1' || ch > '5')
            {
                printf("Invalid choice, returning to the main screen\n");
                printf("-----------------------------------------------------------\n");
                fclose(DB);
                fclose(DBtmp);
                remove("DataB_tmp.txt");
            }
            else
            {
                fseek(DB, 0, SEEK_SET);
                while (fgets(line, sizeof(line), DB))
                {
                    char* e = strtok(line, ", ");
                    if (i == l)
                    {
                        if (ch == '1')fprintf(DBtmp, "%s, ", a.manuf);
                        else fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        if (ch == '2')fprintf(DBtmp, "%s, ", a.model);
                        else fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        if (ch == '3')fprintf(DBtmp, "%s, ", a.reg_number);
                        else fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        if (ch == '4')fprintf(DBtmp, "%d, ", a.capacity);
                        else fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        if (ch == '5')fprintf(DBtmp, "%d,\n", a.fab_year);
                        else fprintf(DBtmp, "%s,\n", e);
                    }
                    else
                    {
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s,\n", e);
                    }
                    i++;
                }
                fclose(DB);
                fclose(DBtmp);
                remove("DataB.txt");
                rename("DataB_tmp.txt", "DataB.txt");
                printf("-----------------------------------------------------------");
                printf("\n");
            }
        }
    }
    main();
}
void del()//4
{
    FILE* DB;
    DB = fopen("DataB.txt", "r");
    fseek(DB, 0L, SEEK_END);
    if (ftell(DB) == 0)
    {
        printf("\n-------------THERE ARE NO AIRCRAFTS TO DELETE-------------\n\n");
        fclose(DB);
    }
    else
    {
        FILE* DBtmp;
        DBtmp = fopen("DataB_tmp.txt", "w");
        printf("-------------------------DELETE---------------------------");
        char line[256] = "",am;
        int i = 1, l, ch;
        printf("\nDo you want to delete one aircraft (1) or all aircrafts (2)? ");
        am = _getch();
        printf("%c\n", am);
        ch = am - '0';
        if (ch == 1)
        {
            fseek(DB, 0, SEEK_SET);
            int count = 0;
            char c, ch;
            for (c = getc(DB); c != EOF; c = getc(DB))
                if (c == '\n')count++;
            printf("%c", c);
            printf("\nWhich aircraft you want to delete (nr)? ");
            ch = _getch();
            printf("%c\n", ch);
            l = ch - '0';
            if (l > count || l <= 0)
            {
                printf("\nInvalid choice, returning to the main screen\n");
                fclose(DB);
                fclose(DBtmp);
                remove("DataB_tmp.txt");
            }
            else
            {
                fseek(DB, 0, SEEK_SET);
                while (fgets(line, sizeof(line), DB))
                {
                    char* e = strtok(line, ", ");
                    if (i == l)
                    {
                        e = strtok(NULL, ", ");
                        e = strtok(NULL, ", ");
                        e = strtok(NULL, ", ");
                        e = strtok(NULL, ", ");
                    }
                    else
                    {
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s, ", e);
                        e = strtok(NULL, ", ");
                        fprintf(DBtmp, "%s,\n", e);
                    }
                    i++;
                }
                fclose(DB);
                fclose(DBtmp);
                remove("DataB.txt");
                rename("DataB_tmp.txt", "DataB.txt");
            }

        }
        else if (ch == 2)
        {
            fclose(DB);
            fclose(DBtmp);
            remove("DataB.txt");
            rename("DataB_tmp.txt", "DataB.txt");
        }
        else printf("Invalid choice, returning to the main screen\n");
        printf("\n-----------------------------------------------------------\n");
    }
    main();
}