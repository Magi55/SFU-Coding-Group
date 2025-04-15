#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Contact {
    char *firstName;
    char *familyName;
    long long phoneNum;
    char *address;
    int age;
} Contact;

int countContacts(Contact **contacts) {
    if (contacts == NULL) return 0;
    int count = 0;
    while (contacts[count] != NULL) {
        count++;
    }
    return count;
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

Contact *readNewContact() {
    Contact *newContact = malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("Error: Memory allocation failed for Contact in readNewContact\n");
        return NULL;
    }
    newContact->firstName = NULL;
    newContact->familyName = NULL;
    newContact->address = NULL;
    newContact->phoneNum = 0;
    newContact->age = 0;

    char buffer[256];

    // Read first name
    printf("Enter the first name:\n");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        free(newContact);
        return NULL;
    }
    trimNewline(buffer);
    newContact->firstName = strdup(buffer);
    if (newContact->firstName == NULL) {
        printf("Error: unable to allocate memory for the first name string\n");
        free(newContact);
        return NULL;
    }

    // Read family name
    printf("Enter the family name:\n");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        free(newContact->firstName);
        free(newContact);
        return NULL;
    }
    trimNewline(buffer);
    newContact->familyName = strdup(buffer);
    if (newContact->familyName == NULL) {
        printf("Error: unable to allocate memory for the family name string\n");
        free(newContact->firstName);
        free(newContact);
        return NULL;
    }

    // Read address
    printf("Enter the address:\n");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        free(newContact->firstName);
        free(newContact->familyName);
        free(newContact);
        return NULL;
    }
    trimNewline(buffer);
    newContact->address = strdup(buffer);
    if (newContact->address == NULL) {
        printf("Error: unable to allocate memory for the address string\n");
        free(newContact->firstName);
        free(newContact->familyName);
        free(newContact);
        return NULL;
    }

    // Read phone number
    int attempts = 5;
    char phoneStr[256];
    long long phoneNum = 0;
    while (attempts > 0) {
        printf("Enter 10-digit phone number that must not start with 0:\n");
        if (fgets(phoneStr, sizeof(phoneStr), stdin) == NULL) {
            break;
        }
        trimNewline(phoneStr);
        size_t len = strlen(phoneStr);
        if (len != 10 || phoneStr[0] == '0') {
            printf("Error: Invalid phone number. Try again:\n");
            attempts--;
            continue;
        }
        int valid = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(phoneStr[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Error: Invalid phone number. Try again:\n");
            attempts--;
            continue;
        }
        phoneNum = atoll(phoneStr);
        break;
    }
    if (attempts == 0) {
        printf("Error: Could not read a valid phone number\n");
        phoneNum = 0;
    }
    newContact->phoneNum = phoneNum;

    // Read age
    attempts = 5;
    int age = 0;
    while (attempts > 0) {
        printf("Enter the age:\n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        trimNewline(buffer);
        if (sscanf(buffer, "%d", &age) != 1) {
            printf("Error: Invalid age. Try again:\n");
            attempts--;
            continue;
        }
        if (age < 1 || age > 150) {
            printf("Error: Invalid age. Try again:\n");
            attempts--;
            continue;
        }
        break;
    }
    if (attempts == 0) {
        printf("Error: Could not read a valid age\n");
        age = 0;
    }
    newContact->age = age;

    return newContact;
}

Contact **appendContact(Contact **contacts, Contact *newContact) {
    if (contacts == NULL || newContact == NULL) {
        return contacts;
    }
    int count = countContacts(contacts);
    Contact **newContacts = realloc(contacts, (count + 2) * sizeof(Contact*));
    if (newContacts == NULL) {
        printf("Memory reallocation error in appendContact\n");
        return contacts;
    }
    newContacts[count] = newContact;
    newContacts[count + 1] = NULL;
    printf("Contact appended successfully by appendContact\n");
    return newContacts;
}

int compareContacts(const void *a, const void *b) {
    Contact *contactA = *(Contact **)a;
    Contact *contactB = *(Contact **)b;
    int familyCmp = strcmp(contactA->familyName, contactB->familyName);
    if (familyCmp != 0) {
        return familyCmp;
    }
    return strcmp(contactA->firstName, contactB->firstName);
}

Contact **insertContactAlphabetical(Contact **contacts, Contact *newContact) {
    if (contacts == NULL || newContact == NULL) {
        return contacts;
    }
    int count = countContacts(contacts);
    int insertIndex = 0;
    while (insertIndex < count && compareContacts(&contacts[insertIndex], &newContact) < 0) {
        insertIndex++;
    }
    Contact **newContacts = realloc(contacts, (count + 2) * sizeof(Contact*));
    if (newContacts == NULL) {
        printf("Memory reallocation error in insertContactAlphabetical\n");
        return contacts;
    }
    for (int i = count; i > insertIndex; i--) {
        newContacts[i] = newContacts[i - 1];
    }
    newContacts[insertIndex] = newContact;
    newContacts[count + 1] = NULL;
    printf("Contact was successfully added in alphabetical order\n");
    return newContacts;
}

Contact **removeContactByIndex(Contact **contacts) {
    if (contacts == NULL) {
        printf("Error: value of addressBook received in removeContactByIndex was NULL\n");
        return NULL;
    }
    int index;
    printf("Removing a Contact by index\nEnter index to remove (0 based):\n");
    if (scanf("%d", &index) != 1) {
        printf("Error: Value of index supplied could not be read.\n");
        while (getchar() != '\n');
        return contacts;
    }
    while (getchar() != '\n');
    int count = countContacts(contacts);
    if (index < 0 || index >= count) {
        printf("Error: Index out of range in removeContactByIndex\n");
        return contacts;
    }
    Contact *toRemove = contacts[index];
    free(toRemove->firstName);
    free(toRemove->familyName);
    free(toRemove->address);
    free(toRemove);
    for (int i = index; i < count; i++) {
        contacts[i] = contacts[i + 1];
    }
    Contact **newContacts = realloc(contacts, (count) * sizeof(Contact*));
    if (newContacts == NULL) {
        printf("Error: Memory reallocation failed in removeContactByIndex\n");
        return contacts;
    }
    printf("Contact removed successfully by removeContactByIndex\n");
    return newContacts;
}

int removeContactByFullName(Contact ***contacts) {
    if (*contacts == NULL) {
        printf("Error: value of contacts received in removeContactByFullName was NULL\n");
        return 0;
    }
    char firstName[256], familyName[256];
    printf("Enter first name:\n");
    if (fgets(firstName, sizeof(firstName), stdin) == NULL) {
        return 0;
    }
    trimNewline(firstName);
    printf("Enter family name:\n");
    if (fgets(familyName, sizeof(familyName), stdin) == NULL) {
        return 0;
    }
    trimNewline(familyName);
    int count = countContacts(*contacts);
    for (int i = 0; i < count; i++) {
        Contact *c = (*contacts)[i];
        if (strcmp(c->firstName, firstName) == 0 && strcmp(c->familyName, familyName) == 0) {
            free(c->firstName);
            free(c->familyName);
            free(c->address);
            free(c);
            for (int j = i; j < count; j++) {
                (*contacts)[j] = (*contacts)[j + 1];
            }
            Contact **newContacts = realloc(*contacts, (count) * sizeof(Contact*));
            if (newContacts == NULL) {
                printf("Error: Memory reallocation failed in removeContactByFullName\n");
                return 1;
            }
            *contacts = newContacts;
            printf("Contact '%s %s' removed successfully\n", firstName, familyName);
            return 1;
        }
    }
    printf("Contact '%s %s' not found\n", firstName, familyName);
    return 2;
}

void listContacts(Contact **contacts) {
    int count = countContacts(contacts);
    if (count == 0) {
        printf("No contacts available.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        Contact *c = contacts[i];
        printf("%d. %s %s\n", i + 1, c->firstName, c->familyName);
        printf(" Phone: %lld\n", c->phoneNum);
        printf(" Address: %s\n", c->address);
        printf(" Age: %d\n\n", c->age);
    }
}

void saveContactsToFile(Contact **contacts, char *filename) {
    if (filename == NULL) {
        printf("Error: filename formal parameter passed value NULL in saveContactsToFile\n");
        return;
    }
    if (contacts == NULL) {
        printf("Error: addressBook formal parameter passed value NULL in saveContactsToFile\n");
        return;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: file not opened in saveContactsToFile\n");
        return;
    }
    int count = countContacts(contacts);
    for (int i = 0; i < count; i++) {
        Contact *c = contacts[i];
        fprintf(fp, "%s\n", c->firstName);
        fprintf(fp, "%s\n", c->familyName);
        fprintf(fp, "%s\n", c->address);
        fprintf(fp, "%lld\n", c->phoneNum);
        fprintf(fp, "%d\n", c->age);
    }
    fclose(fp);
}

void printContactsToFile(Contact **contacts, char *filename) {
    if (filename == NULL) {
        printf("Error: filename formal parameter passed value NULL in printContactsToFile\n");
        return;
    }
    if (contacts == NULL) {
        printf("Error: addressBook formal parameter passed value NULL in printContactsToFile\n");
        return;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: file not opened in printContactsToFile\n");
        return;
    }
    int count = countContacts(contacts);
    fprintf(fp, "Address Book Report\n-------------------\n");
    for (int i = 0; i < count; i++) {
        Contact *c = contacts[i];
        fprintf(fp, "%d. %s %s\n", i + 1, c->firstName, c->familyName);
        fprintf(fp, " Phone: %lld\n", c->phoneNum);
        fprintf(fp, " Address: %s\n", c->address);
        fprintf(fp, " Age: %d\n\n", c->age);
    }
    fprintf(fp, "-------------------\nTotal Contacts: %d\n", count);
    fclose(fp);
}

Contact **loadContactsFromFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }
    Contact **newContacts = NULL;
    int capacity = 0;
    int count = 0;
    char firstName[256], familyName[256], address[256], phoneStr[256], ageStr[256];
    while (fgets(firstName, sizeof(firstName), fp) != NULL) {
        trimNewline(firstName);
        if (fgets(familyName, sizeof(familyName), fp) == NULL) break;
        trimNewline(familyName);
        if (fgets(address, sizeof(address), fp) == NULL) break;
        trimNewline(address);
        if (fgets(phoneStr, sizeof(phoneStr), fp) == NULL) break;
        trimNewline(phoneStr);
        if (fgets(ageStr, sizeof(ageStr), fp) == NULL) break;
        trimNewline(ageStr);
        long long phoneNum = atoll(phoneStr);
        int age = atoi(ageStr);
        Contact *c = malloc(sizeof(Contact));
        c->firstName = strdup(firstName);
        c->familyName = strdup(familyName);
        c->address = strdup(address);
        c->phoneNum = phoneNum;
        c->age = age;
        if (count >= capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            newContacts = realloc(newContacts, (capacity + 1) * sizeof(Contact*));
        }
        newContacts[count++] = c;
    }
    if (count == 0) {
        newContacts = realloc(newContacts, sizeof(Contact*));
        newContacts[0] = NULL;
    } else {
        newContacts[count] = NULL;
    }
    fclose(fp);
    return newContacts;
}

Contact **mergeContactsFromFile(Contact **contacts, char *filename) {
    Contact **fileContacts = loadContactsFromFile(filename);
    if (fileContacts == NULL) {
        return contacts;
    }
    int fileCount = countContacts(fileContacts);
    for (int i = 0; i < fileCount; i++) {
        Contact *c = fileContacts[i];
        int exists = 0;
        for (int j = 0; contacts != NULL && j < countContacts(contacts); j++) {
            if (strcmp(contacts[j]->firstName, c->firstName) == 0 && strcmp(contacts[j]->familyName, c->familyName) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            contacts = insertContactAlphabetical(contacts, c);
        } else {
            free(c->firstName);
            free(c->familyName);
            free(c->address);
            free(c);
        }
    }
    free(fileContacts);
    return contacts;
}

Contact **appendContactsFromFile(Contact **contacts, char *filename) {
    Contact **fileContacts = loadContactsFromFile(filename);
    if (fileContacts == NULL) {
        return contacts;
    }
    int fileCount = countContacts(fileContacts);
    for (int i = 0; i < fileCount; i++) {
        Contact *c = fileContacts[i];
        int exists = 0;
        for (int j = 0; contacts != NULL && j < countContacts(contacts); j++) {
            if (strcmp(contacts[j]->firstName, c->firstName) == 0 && strcmp(contacts[j]->familyName, c->familyName) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            contacts = appendContact(contacts, c);
        } else {
            free(c->firstName);
            free(c->familyName);
            free(c->address);
            free(c);
        }
    }
    free(fileContacts);
    return contacts;
}

Contact *editContact(Contact **contacts, int index) {
    if (contacts == NULL || index < 0 || index >= countContacts(contacts)) {
        return NULL;
    }
    Contact *c = contacts[index];
    int choice;
    do {
        printf("1. Edit First Name\n2. Edit Last Name\n3. Edit Address\n4. Edit Phone Number\n5. Edit Age\n6. Cancel\n");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        char buffer[256];
        switch (choice) {
            case 1:
                printf("Enter new first name:\n");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
                trimNewline(buffer);
                char *newFirstName = strdup(buffer);
                if (newFirstName == NULL) {
                    printf("Error: Memory allocation failed for first name\n");
                    break;
                }
                free(c->firstName);
                c->firstName = newFirstName;
                break;
            case 2:
                printf("Enter new family name:\n");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
                trimNewline(buffer);
                char *newFamilyName = strdup(buffer);
                if (newFamilyName == NULL) {
                    printf("Error: Memory allocation failed for family name\n");
                    break;
                }
                free(c->familyName);
                c->familyName = newFamilyName;
                break;
            case 3:
                printf("Enter new address:\n");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
                trimNewline(buffer);
                char *newAddress = strdup(buffer);
                if (newAddress == NULL) {
                    printf("Error: Memory allocation failed for address\n");
                    break;
                }
                free(c->address);
                c->address = newAddress;
                break;
            case 4: {
                int attempts = 5;
                long long phoneNum = 0;
                while (attempts > 0) {
                    printf("Enter new 10-digit phone number that must not start with 0:\n");
                    if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
                    trimNewline(buffer);
                    size_t len = strlen(buffer);
                    if (len != 10 || buffer[0] == '0') {
                        printf("Error: Invalid phone number. Try again:\n");
                        attempts--;
                        continue;
                    }
                    int valid = 1;
                    for (int i = 0; i < 10; i++) {
                        if (!isdigit(buffer[i])) {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Error: Invalid phone number. Try again:\n");
                        attempts--;
                        continue;
                    }
                    phoneNum = atoll(buffer);
                    break;
                }
                if (attempts == 0) {
                    printf("Error: Could not read a valid phone number\n");
                } else {
                    c->phoneNum = phoneNum;
                }
                break;
            }
            case 5: {
                int attempts = 5;
                int age = 0;
                while (attempts > 0) {
                    printf("Enter new age:\n");
                    if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
                    trimNewline(buffer);
                    if (sscanf(buffer, "%d", &age) != 1) {
                        printf("Error: Invalid age. Try again:\n");
                        attempts--;
                        continue;
                    }
                    if (age < 1 || age > 150) {
                        printf("Error: Invalid age. Try again:\n");
                        attempts--;
                        continue;
                    }
                    break;
                }
                if (attempts == 0) {
                    printf("Error: Could not read a valid age\n");
                } else {
                    c->age = age;
                }
                break;
            }
            case 6:
                return c;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 6);
    return c;
}

void freeContacts(Contact **contacts) {
    if (contacts == NULL) return;
    for (int i = 0; contacts[i] != NULL; i++) {
        free(contacts[i]->firstName);
        free(contacts[i]->familyName);
        free(contacts[i]->address);
        free(contacts[i]);
    }
    free(contacts);
}

int main() {
    Contact **addressBook = NULL;
    int choice;
    do {
        printf("Address Book Menu\n1. Append Contact\n2. Insert Contact in Alphabetical Order\n3. Remove Contact by Index\n4. Remove Contact by Full Name\n5. Find and Edit Contact\n6. List Contacts\n7. Print Contacts to File with the format of an input file\n8. Print Contacts to File (Human Readable)\n9. Load Contacts from File Replacing Existing Contacts\n10. Append Contacts from File\n11. Merge Contacts from File\n12. Exit\nChoose an option:\n");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 1: {
                Contact *newContact = readNewContact();
                if (newContact != NULL) {
                    addressBook = appendContact(addressBook, newContact);
                }
                break;
            }
            case 2: {
                Contact *newContact = readNewContact();
                if (newContact != NULL) {
                    addressBook = insertContactAlphabetical(addressBook, newContact);
                }
                break;
            }
            case 3:
                addressBook = removeContactByIndex(addressBook);
                break;
            case 4:
                removeContactByFullName(&addressBook);
                break;
            case 5: {
                int index;
                printf("Enter index to edit:\n");
                if (scanf("%d", &index) != 1) {
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                Contact *edited = editContact(addressBook, index - 1);
                if (edited == NULL) {
                    printf("Invalid index\n");
                }
                break;
            }
            case 6:
                listContacts(addressBook);
                break;
            case 7: {
                char filename[256];
                printf("Enter filename:\n");
                if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                trimNewline(filename);
                saveContactsToFile(addressBook, filename);
                break;
            }
            case 8: {
                char filename[256];
                printf("Enter filename:\n");
                if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                trimNewline(filename);
                printContactsToFile(addressBook, filename);
                break;
            }
            case 9: {
                char filename[256];
                printf("Enter filename:\n");
                if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                trimNewline(filename);
                Contact **newContacts = loadContactsFromFile(filename);
                if (newContacts != NULL) {
                    freeContacts(addressBook);
                    addressBook = newContacts;
                }
                break;
            }
            case 10: {
                char filename[256];
                printf("Enter filename:\n");
                if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                trimNewline(filename);
                addressBook = appendContactsFromFile(addressBook, filename);
                break;
            }
            case 11: {
                char filename[256];
                printf("Enter filename:\n");
                if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                trimNewline(filename);
                addressBook = mergeContactsFromFile(addressBook, filename);
                break;
            }
            case 12:
                freeContacts(addressBook);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 12);
    return 0;
}
