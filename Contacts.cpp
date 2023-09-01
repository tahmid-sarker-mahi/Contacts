#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>
#include<iomanip>

using namespace std;

struct Contact
{
    char Name[60];
    char Address[30];
    char Contact_no[15];
    char Email[50];
};

void clearScreen()
{
    system("cls");
}

void displayTitle()
{
    clearScreen();
    cout << "\n\n\t\t\t========================================" << endl;
    cout << "\n\n\t\t\t\t     C O N T A C T S" << endl;
    cout << "\n\n\t\t\t========================================" << endl;
}

void displayMenu()
{
    cout << "\n\n\n\t\t\t\t1. Add Contact\n";
    cout << "\t\t\t\t2. View Contacts\n";
    cout << "\t\t\t\t3. Search Contact\n";
    cout << "\t\t\t\t4. Edit Contact\n";
    cout << "\t\t\t\t5. Delete Contact\n";
    cout << "\t\t\t\t6. Exit\n";
    cout << "\n\n\t\t\t\tChoose an option (1-6): ";
}

void addContact(Contact &contact)
{
    displayTitle();
    cout << "\n\n\t\t\t-------- Add Contact --------\n";

    cout << "\n\t\t\tName: ";
    cin.getline(contact.Name, sizeof(contact.Name));
    contact.Name[0] = toupper(contact.Name[0]);

    cout << "\n\t\t\tAddress: ";
    cin.getline(contact.Address, sizeof(contact.Address));
    contact.Address[0] = toupper(contact.Address[0]);

    do
    {
        cout << "\n\t\t\tContact no: ";
        cin.getline(contact.Contact_no, sizeof(contact.Contact_no));

        if (strlen(contact.Contact_no) != 11)
        {
            cout << "\n\t Sorry, Invalid Contact no. It must contain 11 digits. Please enter again." << endl;
        }
        else
        {
            int valid = 1;
            for (int i = 0; i < 11; i++)
            {
                if (!isdigit(contact.Contact_no[i]))
                {
                    valid = 0;
                    break;
                }
            }
            if (!valid)
            {
                cout << "\n\t\tContact no. contains invalid characters. Please enter again." << endl;
            }
        }
    }
    while (strlen(contact.Contact_no) != 11);

    cout << "\n\t\t\tEmail: ";
    cin.getline(contact.Email, sizeof(contact.Email));

    ofstream contacts("Contacts.dat", ios::app);
    if (!contacts)
    {
        cout << "\n\t\t\tError: Unable to open the Contacts file." << endl;
        return;
    }

    contacts << contact.Name << "|" << contact.Address << "|" << contact.Contact_no << "|" << contact.Email << "\n";
    contacts.close();

    cout << "\n\t\t\tContact added successfully." << endl;
}

void viewContacts()
{
    displayTitle();
    cout << "\n\n\t\t\t-------- View Contacts --------\n";

    ifstream contacts("Contacts.dat");
    if (!contacts)
    {
        cout << "\n\t\t\tThe contacts list is empty." << endl;
        return;
    }

    cout << left << setw(20) << "\nName" << setw(20) << "Address" << setw(20) << "Contact No" << setw(30) << "Email" << endl;
    cout << "===============================================================================================" << endl;

    Contact contact;
    while (contacts.getline(contact.Name, sizeof(contact.Name), '|'))
    {
        contacts.getline(contact.Address, sizeof(contact.Address), '|');
        contacts.getline(contact.Contact_no, sizeof(contact.Contact_no), '|');
        contacts.getline(contact.Email, sizeof(contact.Email), '\n');

        cout << left << setw(20) << contact.Name << setw(20) << contact.Address << setw(20) << contact.Contact_no << setw(30) << contact.Email << endl;
    }

    contacts.close();
}

void searchContact()
{
    displayTitle();
    cout << "\n\n\t\t\t-------- Search Contact --------\n";

    char name[60];
    cout << "\n\t\t\tEnter the Name of the person to search: ";
    cin.getline(name, sizeof(name));
    name[0] = toupper(name[0]);

    ifstream contacts("Contacts.dat");
    if (!contacts)
    {
        cout << "\n\t\t\tThe contacts list is empty." << endl;
        return;
    }

    Contact contact;
    bool found = false;
    while (contacts.getline(contact.Name, sizeof(contact.Name), '|'))
    {
        contacts.getline(contact.Address, sizeof(contact.Address), '|');
        contacts.getline(contact.Contact_no, sizeof(contact.Contact_no), '|');
        contacts.getline(contact.Email, sizeof(contact.Email), '\n');

        if (strcmp(contact.Name, name) == 0)
        {
            displayTitle();
            cout << "\n\n\t\t\t-------- Search Contact --------\n";
            cout << left << setw(20) << "\nName" << setw(20) << "Address" << setw(20) << "Contact No" << setw(30) << "Email" << endl;
            cout << "==============================================================================================" << endl;
            cout << left << setw(20) << contact.Name << setw(20) << contact.Address << setw(20) << contact.Contact_no << setw(30) << contact.Email << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n\t\t\tRecord not found." << endl;
    }

    contacts.close();
}

void editContact()
{
    displayTitle();
    cout << "\n\n\t\t\t-------- Edit Contact --------\n";

    char name[60];
    cout << "\n\t\t\tEnter the Name of the person to edit: ";
    cin.getline(name, sizeof(name));
    name[0] = toupper(name[0]);

    ifstream contacts("Contacts.dat");
    ofstream temp("Temp.dat");

    if (!contacts || !temp)
    {
        cout << "\n\t\t\tError: Unable to open contacts files." << endl;
        return;
    }

    Contact contact;
    bool found = false;

    while (contacts.getline(contact.Name, sizeof(contact.Name), '|'))
    {
        contacts.getline(contact.Address, sizeof(contact.Address), '|');
        contacts.getline(contact.Contact_no, sizeof(contact.Contact_no), '|');
        contacts.getline(contact.Email, sizeof(contact.Email), '\n');

        if (strcmp(contact.Name, name) == 0)
        {
            found = true;
            cout << "\n\t\t\tEnter New Details:\n";

            cout << "\n\t\t\tName: ";
            cin.getline(contact.Name, sizeof(contact.Name));
            contact.Name[0] = toupper(contact.Name[0]);

            cout << "\n\t\t\tAddress: ";
            cin.getline(contact.Address, sizeof(contact.Address));
            contact.Address[0] = toupper(contact.Address[0]);

            do
            {
                cout << "\n\t\t\tContact no: ";
                cin.getline(contact.Contact_no, sizeof(contact.Contact_no));

                if (strlen(contact.Contact_no) != 11)
                {
                    cout << "\n\t Sorry, Invalid Contact no. It must contain 11 digits. Please enter again." << endl;
                }
                else
                {
                    int valid = 1;
                    for (int i = 0; i < 11; i++)
                    {
                        if (!isdigit(contact.Contact_no[i]))
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                    {
                        cout << "\n\t\tContact no. contains invalid characters. Please enter again." << endl;
                    }
                }
            }
            while (strlen(contact.Contact_no) != 11);

            cout << "\n\t\t\tEmail: ";
            cin.getline(contact.Email, sizeof(contact.Email));

            temp << contact.Name << "|" << contact.Address << "|" << contact.Contact_no << "|" << contact.Email << "\n";
            cout << "\n\t\t\tContact updated successfully." << endl;
        }
        else
        {
            temp << contact.Name << "|" << contact.Address << "|" << contact.Contact_no << "|" << contact.Email << "\n";
        }
    }

    contacts.close();
    temp.close();

    if (found)
    {
        remove("Contacts.dat");
        rename("Temp.dat", "Contacts.dat");
    }
    else
    {
        cout << "\n\t\t\tRecord not found." << endl;
        remove("Temp.dat");
    }
}

void deleteContact()
{
    displayTitle();
    cout << "\n\n\t\t\t-------- Delete Contact --------\n";

    char name[60];
    cout << "\n\t\t\tEnter the Name of the person to delete: ";
    cin.getline(name, sizeof(name));
    name[0] = toupper(name[0]);

    ifstream contacts("Contacts.dat");
    ofstream temp("Temp.dat");

    if (!contacts || !temp)
    {
        cout << "\n\t\t\tError: Unable to open contacts files." << endl;
        return;
    }

    Contact contact;
    bool found = false;

    while (contacts.getline(contact.Name, sizeof(contact.Name), '|'))
    {
        contacts.getline(contact.Address, sizeof(contact.Address), '|');
        contacts.getline(contact.Contact_no, sizeof(contact.Contact_no), '|');
        contacts.getline(contact.Email, sizeof(contact.Email), '\n');

        if (strcmp(contact.Name, name) != 0)
        {
            temp << contact.Name << "|" << contact.Address << "|" << contact.Contact_no << "|" << contact.Email << "\n";
        }
        else
        {
            found = true;
        }
    }

    contacts.close();
    temp.close();

    if (found)
    {
        remove("Contacts.dat");
        rename("Temp.dat", "Contacts.dat");
        cout << "\n\t\t\tContact deleted successfully." << endl;
    }
    else
    {
        cout << "\n\t\t\tRecord not found." << endl;
        remove("Temp.dat");
    }
}

int main()
{
    int choice;
    Contact contact;

    do
    {
        displayTitle();
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            addContact(contact);
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            editContact();
            break;
        case 5:
            deleteContact();
            break;
        case 6:
            cout << "\n\t\t\tThank you for using Contacts!\n";
            break;
        default:
            cout << "\n\t\t\tInvalid option. Please enter a valid choice (1-6).\n";
        }

        if (choice != 6)
        {
            cout << "\n\t\t\tPress Enter to continue...";
            cin.get();
        }
    }
    while (choice != 6);

    return 0;
}