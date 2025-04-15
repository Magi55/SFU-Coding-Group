#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Contact
{
char *firstName; 
char *familyName; 
long long phoneNum;
char *address; 
int age; 
} Contact; 

void menu();
int countContacts(Contact **contacts);
Contact *readNewContact();
Contact **appendContact(Contact **contacts, Contact *newContact);
Contact **insertContactAlphabetical(Contact **contacts, Contact *newContact);
Contact **removeContactByIndex(Contact **contacts);
int removeContactByFullName(Contact ***contacts);
Contact **editContact(Contact **contacts);
void listContacts(Contact **contacts);
void saveContactsToFile(Contact **contacts, char *filename);
void printContactsToFile(Contact **contacts, char *filename);
void cleaningUp(Contact **contacts, int count, FILE *file);
Contact **loadContactsFromFile(Contact **addressBook, char *filename);
Contact **appendContactsFromFile(Contact **contacts, char *filename);
Contact **mergeContactsFromFile(Contact **contacts, char *filename);
void freeAllContacts(Contact **contacts);

int main()
{
    menu();
}

void menu()
{
    int choice = 0;
	Contact **contacts = NULL;
	
	while(1)
	{
	    printf("Address Book Menu \n\
1.  Append Contact \n\
2.  Insert Contact in Alphabetical Order \n\
3.  Remove Contact by Index \n\
4.  Remove Contact by Full Name \n\
5.  Find and Edit Contact \n\
6.  List Contacts \n\
7.  Print Contacts to File with the format of an input file \n\
8.  Print Contacts to File (Human Readable) \n\
9.  Load Contacts from File Replacing Existing Contacts \n\
10. Append Contacts from File \n\
11. Merge Contacts from File \n\
12. Exit \n\
Choose an option: ");
	    
		scanf("%d", &choice);
		if(choice >= 1 && choice <= 12)
		{
			if(1 == choice) /*Append Contact*/
			{
				printf("Adding a constact interactively: \n");

				Contact *newContact = readNewContact();
                contacts = appendContact(contacts, newContact);
                printf("\n");
			}

			else if(2 == choice) /*Insert Contact in Alphabetical Order*/
			{
                Contact *newContact = readNewContact();
                if(newContact) 
                {
                    contacts = insertContactAlphabetical(contacts, newContact);
                }
			}

			else if(3 == choice) /*Remove Contact by Index*/
			{
				contacts = removeContactByIndex(contacts);
			}

			else if(4 == choice) /*Remove Contact by Full Name*/
			{
				int result = removeContactByFullName(&contacts);
			}

			else if(5 == choice) /*Find and Edit Contact*/
			{
                contacts = editContact(contacts);
			}

			else if(6 == choice) /*List Contacts*/
			{
                listContacts(contacts);
			}

			else if(7 == choice) /*Print Contacts to File with the format of an input file*/
			{
                char filename[256];
                printf("Enter output filename: ");
                scanf("%255s", filename);
                saveContactsToFile(contacts, filename);
                printf("\n");
			}

			else if(8 == choice) /*Print Contacts to File (Human Readable)*/
			{
                char filename[256];
                printf("Enter output filename: ");
                scanf("%255s", filename);
                printContactsToFile(contacts, filename);
                printf("\n");
			}

			else if(9 == choice) /*Load Contacts from File Replacing Existing Contacts*/
			{
                char filename[256];
                printf("Enter filename to load: ");
                scanf("%255s", filename);
                contacts = loadContactsFromFile(contacts, filename);
			}

			else if(10 == choice) /*Append Contacts from File*/
			{
                char filename[256];
                printf("Enter filename to append: ");
                scanf("%255s", filename);
                contacts = appendContactsFromFile(contacts, filename);
			}
			
			else if(11 == choice) /*Merge Contacts from File*/
			{
                char filename[256];
                printf("Enter filename to merge: ");
                scanf("%255s", filename);
                contacts = mergeContactsFromFile(contacts, filename);
			}

			else if(12 == choice) /*Exit*/
			{
				freeAllContacts(contacts);

				printf("Exiting program. Goodbye!");
				
				exit(0);
			}
		}
		else
		{
			printf("Error: option not available. Try again: ");
		}
	}
}

int countContacts(Contact **contacts)
{
    int count = 0;
    
    if(!contacts) 
    {
        return 0;
    }

    while(contacts[count] != NULL) 
    {
        count++;
    }
    return count;
}

Contact *readNewContact() 
{
    int ageTemp = 0;
    int ageTries = 0;
    long long phoneTemp = 0;
    int phoneTries = 0;

    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    if(!newContact) 
    {
        printf("Error: Memory allocation failed for Contact in readNewContact \n");
        return NULL;
    }

    newContact->firstName = (char*)malloc(100 * sizeof(char));
    if(!newContact->firstName) 
    {
        printf("Error: unable to allocate memory for the first name string\n");
        free(newContact);
        return NULL;
    }
    
    newContact->familyName = (char*)malloc(100 * sizeof(char));
    if(!newContact->firstName) 
    {
        printf("Error: unable to allocate memory for the family name string\n");
        free(newContact->firstName);
        free(newContact);
        return NULL;
    }
    
    newContact->address = (char*)malloc(200 * sizeof(char));
    if(!newContact->firstName) 
    {
        printf("Error: unable to allocate memory for the address string\n");
        free(newContact->familyName);
        free(newContact->firstName);
        free(newContact);
        return NULL;
    }

    /*Read first name*/
    printf("Enter the first name: ");
    scanf("%99s", newContact->firstName);
    while(getchar() != '\n');

    /*Read family name*/
    printf("Enter the family name: ");
    scanf("%99s", newContact->familyName);
    while(getchar() != '\n');

    /*Read address*/
    printf("Enter the address: ");
    scanf("%199[^\n]", newContact->address);
    while(getchar() != '\n');

    /*Read phone number*/
    while(1) 
    {
        printf("Enter 10-digit phone number that must not start with 0: ");
        
        if(scanf("%lld", &phoneTemp) != 1) 
        {
            printf("Error: Invalid phone number. Try again: ");
            while(getchar() != '\n');
            phoneTries++;
        } 
        
        /*Phone number re-tries*/
        else 
        {
            if(phoneTemp >= 1000000000LL && phoneTemp <= 9999999999LL) 
            {
                newContact->phoneNum = phoneTemp;
                break;
            } 
            
            else 
            {
                printf("Error: Invalid phone number. Try again: ");
                phoneTries++;
            }
        }

        if(phoneTries >= 5) 
        {
            printf("Error: Could not read a valid phone number\n");
            newContact->phoneNum = 0;
            break;
        }
    }

    /*Read age*/
    while(1) 
    {
        printf("Enter the age: ");
        
        if(scanf("%d", &ageTemp) != 1) 
        {
            printf("Error: Invalid age. Try again: ");
            while(getchar() != '\n');
            ageTries++;
        } 
        
        /*Age re-tries*/
        else 
        {
            if(ageTemp >= 1 && ageTemp <= 150) 
            {
                newContact->age = ageTemp;
                break;
            } 
            
            else 
            {
                printf("Error: Invalid age. Try again: ");
                ageTries++;
            }
        }

        if(ageTries >= 5) 
        {
            printf("Error: Could not read a valid age\n");
            newContact->age = 0;
            break;
        }
    }
    return newContact;
}

Contact **appendContact(Contact **contacts, Contact *newContact)
{
    int count = countContacts(contacts);
    int newSize = count + 2;
    
    if(newContact == NULL)
    {
        return contacts;
    }

    Contact **newList = realloc(contacts, newSize * sizeof(Contact *));
    if(newList == NULL) 
    {
        printf("Error: Memory reallocation error in appendContact\n");
        return contacts;
    }

    newList[count] = newContact;
    newList[count + 1] = NULL;

    printf("Contact appended successfully by appendContact \n");
    return newList;
}

Contact **insertContactAlphabetical(Contact **contacts, Contact *newContact) 
{
    if(newContact == NULL) 
    {
        return contacts;
    }
    
    int contactCount = countContacts(contacts);
    int newSize = contactCount + 2;
    int insertPosition = 0;

    Contact **newList = realloc(contacts, newSize * sizeof(Contact *));
    if(newList == NULL) 
    {
        printf("Error: Memory reallocation failed\n");
        return contacts;
    }

    while(insertPosition < contactCount) 
    {
        Contact *current = newList[insertPosition];
        
        /*Comparing family names*/
        int familyCompare = strcmp(newContact->familyName, current->familyName);
        if(familyCompare < 0) 
        {
            break;
        }

        /*Comparing first names*/
        if(familyCompare == 0) 
        {
            int firstCompare = strcmp(newContact->firstName, current->firstName);
            if(firstCompare < 0) 
            {
                break;
            }
        }
        
        insertPosition++;
    }

    for(int i = contactCount; i > insertPosition; i--) 
    {
        newList[i] = newList[i - 1];
    }

    /*Adding new position*/
    newList[insertPosition] = newContact;
    newList[contactCount + 1] = NULL;

    printf("Contact added in alphabetical order successfully.\n");
    return newList;
}

Contact **removeContactByIndex(Contact **contacts) 
{
    int contactCount = countContacts(contacts);
    int newSize = contactCount;
    
    if(contacts == NULL) 
    {
        printf("Error: value of addressBook received in removeContactByIndex was NULL\n");
        return NULL;
    }

    int index;
    printf("Removing a Contact by index\n\
    Enter index to remove (0 based): ");
    
    // Read index input
    if(scanf("%d", &index) != 1) 
    {
        printf("Error: Value of index supplied could not be read.\n");
        while(getchar() != '\n');
        return contacts;
    }
    
    if(index < 0 || index >= contactCount) 
    {
        printf("Error: Index out of range in removeContactByIndex\n");
        return contacts;
    }

    Contact *oldContact = contacts[index];
    free(oldContact->firstName);
    free(oldContact->familyName);
    free(oldContact->address);
    free(oldContact);

    for(int i = index; i < contactCount; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    
    /*Reallocate to smaller size*/
    Contact **newList = realloc(contacts, newSize * sizeof(Contact *));
    if(newList == NULL) 
    {
        printf("Error: Memory reallocation failed in removeContactByIndex\n");
        return contacts;
    }

    printf("Contact removed successfully by removeContactByIndex\n");
    return newList;
}

int removeContactByFullName(Contact ***contacts) 
{
    char firstName[100] = "";
    char familyName[100] = "";
    int count = countContacts(*contacts);
    int foundIndex = -1;
    
    if(contacts == NULL) 
    {
        printf("Error: value of contacts received in removeContactByFullName was NULL\n");
        return 0;
    }

    printf("Enter first name: ");
    scanf("%99s", firstName);
    printf("Enter family name: ");
    scanf("%99s", familyName);

    if(*contacts == NULL) 
    {
        printf("Contact '%s %s' not found\n", firstName, familyName);
        return 2;
    }

    /*Search for matching contact*/
    for(int i = 0; i < count; i++) 
    {
        Contact *current = (*contacts)[i];
        if(strcmp(current->firstName, firstName) == 0 && strcmp(current->familyName, familyName) == 0) 
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1) 
    {
        printf("Contact '%s %s' not found\n", firstName, familyName);
        return 2;
    }

    Contact *removed = (*contacts)[foundIndex];
    free(removed->firstName);
    free(removed->familyName);
    free(removed->address);
    free(removed);

    for(int i = foundIndex; i < count; i++) 
    {
        (*contacts)[i] = (*contacts)[i + 1];
    }

    int newCount = count - 1;
    Contact **newArray = realloc(*contacts, (newCount + 1) * sizeof(Contact *));

    if(newArray) 
    {
        *contacts = newArray;
        printf("Contact '%s %s' removed successfully\n", firstName, familyName);
    } 
    
    else 
    {
        printf("Error: Memory reallocation failed in removeContactByFullName\n");
    }

    return 1;
}

Contact **editContact(Contact **contacts) 
{
    int choice;
    int contactIndex = 0;
    int count = countContacts(contacts);

    if (count == 0) 
    {
        printf("Error: No contacts available to edit.\n");
        return 0;
    }

    printf("Enter index of contact to edit (0-%d): ", count-1);
    if (scanf("%d", &contactIndex) != 1 || contactIndex < 0 || contactIndex >= count) 
    {
        printf("Error: Invalid index\n");
        return 0;
    }

    while(getchar() != '\n');

    Contact *contact = contacts[contactIndex];

    while(1) 
    {
        printf("Editing Contact: %s %s\n", contact->firstName, contact->familyName);
        printf("1. Edit First Name\n\
2. Edit Family Name\n\
3. Edit Address\n\
4. Edit Phone Number\n\
5. Edit Age\n\
6. Cancel\n\
Choose an option: ");

        scanf("%d", &choice);
        if(choice >= 1 && choice <= 6)
		{
			if(1 == choice) /*First name*/
			{
                char newName[100];
                
                printf("Enter new first name: ");
                scanf("%99s", newName);


                char *newStr = strdup(newName);
                if(!newStr) 
                {
                    printf("Error: Memory allocation error for string in editContact\n");
                    return 0;
                }

                free(contact->firstName);
                contact->firstName = newStr;
                printf("First name updated.\n");

                return 0;
			}

			else if(2 == choice) /*Family name*/
			{
                char newName[100];
                
                printf("Enter new family name: ");
                scanf("%99s", newName);

                char *newStr = strdup(newName);
                if(!newStr) 
                {
                    printf("Error: Memory allocation error for string in editContact\n");
                    return 0;
                }

                free(contact->familyName);
                contact->familyName = newStr;
                printf("Family name updated.\n");

                return 0;
			}

			else if(3 == choice) /*Address*/
			{
                char newAddress[200];
                
                printf("Enter new address: ");
                scanf(" %199[^\n]", newAddress);

                char *newStr = strdup(newAddress);
                if(!newStr) 
                {
                    printf("Error: Memory allocation error for string in editContact\n");
                    return 0;
                }

                free(contact->address);
                contact->address = newStr;
                printf("Address updated.\n");

                return 0;
			}

			else if(4 == choice) /*Phone number*/
			{
                long long newPhone = 0;
                int tries = 0;
                
                while(1) 
                {
                    printf("Enter new phone number: Enter 10-digit phone number that must not start with 0: ");
                    if(scanf("%lld", &newPhone) != 1) 
                    {
                        printf("Error: Invalid phone number. Try again: ");
                        tries++;
                    } 

                    else if(newPhone < 1000000000LL || newPhone > 9999999999LL) 
                    {
                        printf("Error: Invalid phone number. Try again: ");
                        tries++;
                    } 

                    else 
                    {
                        contact->phoneNum = newPhone;
                        printf("Phone number updated.\n");
                        return 0;
                    }
                    
                    if (tries >= 5) 
                    {
                        printf("Error: Could not read a valid phone number. Keeping original.\n");
                        return 0;
                    }
                    while(getchar() != '\n');
                }
			}

			else if(5 == choice) /*Age*/
			{
                int newAge;
                int tries = 0;

                while(1) 
                {
                    printf("Enter new age (0-150): ");
                    if(scanf("%d", &newAge) != 1) 
                    {
                        printf("Error: Invalid age. Try again: ");
                        tries++;
                    } 

                    else if(newAge < 0 || newAge > 150) 
                    {
                        printf("Error: Invalid age. Try again: ");
                        tries++;
                    } 

                    else 
                    {
                        contact->age = newAge;
                        printf("Age updated.\n");
                        return 0;
                    }
                    
                    if (tries >= 5) 
                    {
                        printf("Error: Could not read a valid age. Keeping original.\n");
                        return 0;
                    }
                    while(getchar() != '\n');
                }
			}

			else if(6 == choice) /*Cancel*/
			{
                printf("Edit cancelled.\n");
                return 0;
			}
 
        } 

        else
        {
            printf("Error: option not available. Try again: ");
        }  
    }
}

void listContacts(Contact **contacts) 
{
    int count = countContacts(contacts);
    
    if(count == 0) 
    {
        printf("Error: No contacts available.\n");
        return 0;
    }

    printf("\nContacts List:\n");
    for(int i = 0; i < count; i++) 
    {
        Contact *current = contacts[i];
        printf("%2d.    %s %s\n", i + 1, current->firstName, current->familyName);
        printf("       Phone: %-15lld\n", current->phoneNum);
        printf("       Address: %-30s\n", current->address);
        printf("       Age: %-3d\n", current->age);
    }
}

void saveContactsToFile(Contact **contacts, char *filename) 
{

    if(filename == NULL) 
    {
        printf("Error: filename formal parameter passed value NULL in saveContactsToFile");
        return 0;
    }

    if(contacts == NULL) 
    {
        printf("Error: contacts formal parameter passed value NULL in saveContactsToFile");
        return 0;
    }

    FILE *file = fopen(filename, "w");
    if(file == NULL) 
    {
        printf("Error: file not opened in saveContactsToFile");
        return 0;
    }

    int count = countContacts(contacts);
    
    fprintf(file, "%d\n", count);

    for(int i = 0; i < count; i++)
    {
        Contact *current = contacts[i];
        fprintf(file, "%s\n", current->firstName);
        fprintf(file, "%s\n", current->familyName);
        fprintf(file, "%s\n", current->address);
        fprintf(file, "%lld\n", current->phoneNum);
        fprintf(file, "%d\n", current->age);
    }

    fclose(file);
}

void printContactsToFile(Contact **contacts, char *filename)
{
    int count = countContacts(contacts);
    
    if(filename == NULL) 
    {
        printf("Error: filename formal parameter passed value NULL in printContactsToFile");
        return 0;
    }

    if(contacts == NULL) 
    {
        printf("Error: contacts formal parameter passed value NULL in printContactsToFile");
        return 0;
    }

    FILE *file = fopen(filename, "w");
    if(file == NULL) 
    {
        printf("Error: file not opened in printContactsToFile");
        return 0;
    }

    fprintf(file, "Address Book Report\n");
    fprintf(file, "-------------------\n");

    for (int i = 0; i < count; i++) 
    {
        Contact *current = contacts[i];
        fprintf(file, "%d.   %s %s\n", i + 1, current->firstName, current->familyName);
        fprintf(file, "      Phone: %lld\n", current->phoneNum);
        fprintf(file, "      Address: %s\n", current->address);
        fprintf(file, "      Age: %d\n", current->age);
    }

    fprintf(file, "-------------------\n");
    fprintf(file, "Total Contacts: %d", count);

    fclose(file);
}

void cleaningUp(Contact **contacts, int count, FILE *file) 
{
    if(contacts) 
    {
        for(int j = 0; j < count; j++) 
        {
            if(contacts[j]) 
            {
                free(contacts[j]->firstName);
                free(contacts[j]->familyName);
                free(contacts[j]->address);
                free(contacts[j]);
            }
        }
        free(contacts);
    }
    
    if(file) 
    {
        fclose(file);
    }
}

Contact **loadContactsFromFile(Contact **addressBook, char *filename)
{
    int contactCount = 0;
    
    if(filename == NULL) 
    {
        printf("Error: filename formal parameter passed value NULL in loadContactsFromFile\n");
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL) 
    {
        printf("Error: File to load not found\n");
        return NULL;
    }

    if(fscanf(file, "%d", &contactCount) != 1) 
    {
        printf("Error: Memory allocation error, addressBook in loadContactsFromFile\n");
        fclose(file);
        return NULL;
    }
    while(fgetc(file) != '\n');

    if(addressBook != NULL) 
    {
        for(int i = 0; addressBook[i] != NULL; i++) 
        {
            free(addressBook[i]->firstName);
            free(addressBook[i]->familyName);
            free(addressBook[i]->address);
            free(addressBook[i]);
        }
        free(addressBook);
    }

    Contact **newBook = malloc((contactCount + 1) * sizeof(Contact *));
    if(newBook == NULL) 
    {
        printf("Error: Memory allocation error, addressBook in loadContactsFromFile\n");
        fclose(file);
        return NULL;
    }
    newBook[contactCount] = NULL;

    for(int i = 0; i < contactCount; i++) 
    {
        char firstName[100] = "";
        char familyName[100] = "";
        char address[200] = "";
        long long phone = 0;
        int age = 0;

        newBook[i] = malloc(sizeof(Contact));
        if(newBook[i] == NULL) 
        {
            printf("Error: Memory allocation error, Contact %d in loadContactsFromFile\n", i);
            cleaningUp(newBook, i, file);
        }

        /*Read first name*/
        if(fgets(firstName, sizeof(firstName), file) == NULL)
        {
            firstName[0] = '\0';
        }

        firstName[strcspn(firstName, "\n")] = '\0';
        newBook[i]->firstName = strdup(firstName);

        if(newBook[i]->firstName == NULL) 
        {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            free(newBook[i]);
            cleaningUp(newBook, i, file);
        }

        /*Read family name*/
        if(fgets(familyName, sizeof(familyName), file) == NULL) 
        {
            familyName[0] = '\0';
        }

        familyName[strcspn(familyName, "\n")] = '\0';
        newBook[i]->familyName = strdup(familyName);

        if(newBook[i]->familyName == NULL) 
        {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            free(newBook[i]->firstName);
            free(newBook[i]);
            cleaningUp(newBook, i, file);
        }

        /*Read address*/
        if(fgets(address, sizeof(address), file) == NULL) 
        {
            address[0] = '\0';
        }

        address[strcspn(address, "\n")] = '\0';
        newBook[i]->address = strdup(address);

        if(newBook[i]->address == NULL) 
        {
            printf("Error: Memory allocation error, memory for string in Contact %d not allocated\n", i);
            free(newBook[i]->firstName);
            free(newBook[i]->familyName);
            free(newBook[i]);
            cleaningUp(newBook, i, file);
        }

        /*Read phone number*/
        if(fscanf(file, "%lld", &phone) != 1 || phone < 1000000000LL || phone > 9999999999LL) 
        {
            printf("Error: Invalid phone number.\n");
            phone = 0;
        }

        newBook[i]->phoneNum = phone;
        while(fgetc(file) != '\n');

        /*Read age*/
        if(fscanf(file, "%d", &age) != 1 || age < 0 || age > 150) 
        {
            printf("Error: Invalid age.\n");
            age = 0;
        }

        newBook[i]->age = age;
        while(fgetc(file) != '\n');
    }

    fclose(file);
    printf("Contacts loaded from file: %s\n", filename);
    return newBook;
}

Contact **appendContactsFromFile(Contact **contacts, char *filename) 
{
    int fileContactCount = 0;
    
    if(filename == NULL) 
    {
        printf("Error: filename formal parameter passed value NULL\n");
        return contacts;
    }

    FILE *file = fopen(filename, "r");
    if(!file) 
    {
        printf("Error: file not opened in appendContactsFromFile\n");
        return contacts;
    }

    if(fscanf(file, "%d", &fileContactCount) != 1) 
    {
        fclose(file);
        return contacts;
    }
    while(fgetc(file) != '\n');

    for(int i = 0; i < fileContactCount; i++) 
    {
        char firstName[100];
        char familyName[100];
        char address[200];
        long long phone = 0;
        int age = 0;
        int exists = 0;
        int contactCount = countContacts(contacts);

        /*Read first name*/
        if(!fgets(firstName, sizeof(firstName), file) )
        {
            break;
        }
        firstName[strcspn(firstName, "\n")] = '\0';
        
        /*Read family name*/
        if(!fgets(familyName, sizeof(familyName), file))
        {
            break;
        }
        familyName[strcspn(familyName, "\n")] = '\0';
        
        /*Read address*/
        if(!fgets(address, sizeof(address), file))
        {
            break;
        }
        address[strcspn(address, "\n")] = '\0';

        /*Read phone number*/
        if(fscanf(file, "%lld", &phone) != 1) 
        {
            phone = 0;
        }
        while(fgetc(file) != '\n');
        
        /*Read age*/
        if(fscanf(file, "%d", &age) != 1)
        {
            age = 0;
        }
        while(fgetc(file) != '\n');

        for(int j = 0; j < contactCount; j++) 
        {
            if(strcmp(contacts[j]->firstName, firstName) == 0 &&strcmp(contacts[j]->familyName, familyName) == 0) 
            {
                exists = 1;
                break;
            }
        }

        if(!exists) 
        {
            Contact *newContact = malloc(sizeof(Contact));
            if(!newContact) 
            {
                fprintf(stderr, "Error: Memory allocation failed for Contact\n");
                return 0;
            }

            newContact->firstName = strdup(firstName);
            newContact->familyName = strdup(familyName);
            newContact->address = strdup(address);
            
            if(!newContact->firstName || !newContact->familyName || !newContact->address) 
            {
                free(newContact->firstName);
                free(newContact->familyName);
                free(newContact->address);
                free(newContact);
                fprintf(stderr, "Error: Memory allocation failed for strings\n");
                return 0;
            }

            newContact->phoneNum = phone;
            newContact->age = age;

            Contact **newList = appendContact(contacts, newContact);
            if(newList) contacts = newList;
        }
    }

    fclose(file);
    printf("Appended contacts from %s\n", filename);
    return contacts;
}

Contact **mergeContactsFromFile(Contact **contacts, char *filename)
{
    if(!filename) 
    {
        printf("Error: filename is NULL in mergeContactsFromFile\n");
        return contacts;
    }

    FILE *file = fopen(filename, "r");
    if(!file) 
    {
        printf("Error: file not opened in mergeContactsFromFile\n");
        return contacts;
    }

    int fileCount;
    if(fscanf(file, "%d", &fileCount) != 1) 
    {
        fclose(file);
        return contacts;
    }

    while(fgetc(file) != '\n');

    for(int i = 0; i < fileCount; i++) 
    {
        char firstName[100] = "";
        char familyName[100] = "";
        char address[200]= "";
        long long phone = 0;
        int age = 0;
        int exists = 0;
        
        if(!fgets(firstName, sizeof(firstName), file)) 
        {
            break;
        }
        firstName[strcspn(firstName, "\n")] = 0;
        
        if(!fgets(familyName, sizeof(familyName), file))
        {
            break;
        }
        familyName[strcspn(familyName, "\n")] = 0;
        
        if(!fgets(address, sizeof(address), file))
        {
            break;
        }
        address[strcspn(address, "\n")] = 0;
        
        if(fscanf(file, "%lld", &phone) != 1) 
        {
            phone = 0;
        }
        while(fgetc(file) != '\n');
        
        if(fscanf(file, "%d", &age) != 1) 
        {
            age = 0;
        }
        while(fgetc(file) != '\n');

        if(contacts) 
        {
            for(int j = 0; contacts[j]; j++) 
            {
                if(strcmp(contacts[j]->firstName, firstName) == 0 && strcmp(contacts[j]->familyName, familyName) == 0) 
                {
                    exists = 1;
                    break;
                }
            }
        }

        if(!exists) 
        {
            Contact *newContact = malloc(sizeof(Contact));
            if(!newContact) 
            {
                continue;
            }

            newContact->firstName = strdup(firstName);
            newContact->familyName = strdup(familyName);
            newContact->address = strdup(address);
            newContact->phoneNum = phone;
            newContact->age = age;

            if (!newContact->firstName || !newContact->familyName || !newContact->address) 
            {
                free(newContact->firstName);
                free(newContact->familyName);
                free(newContact->address);
                free(newContact);
                continue;
            }

            Contact **newContacts = appendContact(contacts, newContact);
            if (newContacts) 
            {
                contacts = newContacts;
            }
        }
    }

    fclose(file);
    printf("Appended contacts from %s\n", filename);
    return contacts;
}

void freeAllContacts(Contact **contacts) 
{
    if(contacts == NULL) return 0;
    
    for(int i = 0; contacts[i] != NULL; i++) 
    {
        free(contacts[i]->firstName);
        free(contacts[i]->familyName);
        free(contacts[i]->address);
        free(contacts[i]);
    }
    
    free(contacts);
}

