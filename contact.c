#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(AddressBook *addressBook, int sortChoice) 
{
    	int n = addressBook->contactCount;
	if (n == 0) {
		printf("No contacts to list.\n");
		return;
	}
	Contact temp;
	while(1) {
		int flag = 0;
		printf("Enter 1 to sort according to Name\n");
		printf("Enter 2 to sort according to Phone\n");
		printf("Enter 3 to sort according to email\n");
		printf("Enter your choice :");
		scanf("%d", &sortChoice);

		if(sortChoice == 1) {
			for(int i = 0; i < n - 1; i++) {
				for(int j = 0; j < n - 1 - i; j++) {
					if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0) {
						temp = addressBook->contacts[j];
						addressBook->contacts[j] = addressBook->contacts[j+1];
						addressBook->contacts[j+1] = temp;
					}
				}
			}
		} else if(sortChoice == 2) {
			for(int i = 0; i < n - 1; i++) {
				for(int j = 0; j < n - 1 - i; j++) {
					if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0) {
						temp = addressBook->contacts[j];
						addressBook->contacts[j] = addressBook->contacts[j+1];
						addressBook->contacts[j+1] = temp;
					}
				}
			}
		} else if(sortChoice == 3) {
			for(int i = 0; i < n - 1; i++) {
				for(int j = 0; j < n - 1 - i; j++) {
					if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0) {
						temp = addressBook->contacts[j];
						addressBook->contacts[j] = addressBook->contacts[j+1];
						addressBook->contacts[j+1] = temp;
					}
				}
			}
		} else {
			flag = 1;
		}

		if(flag == 1) {
			printf("Re-enter the choice\n");
		} else {
			break;
		}
	}

	for(int i = 0; i < n; i++) {
		printf("%s\t%s\t%s\n", addressBook->contacts[i].name,  addressBook->contacts[i].phone,  addressBook->contacts[i].email);
	}
    
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}




void createContact(AddressBook *addressBook)
{
	int present;
	int i = addressBook->contactCount;
	int flag = 0;

	if (i >= 100) {
		printf("Address book is full!\n");
		return;
	}

	while(1) {
		printf("Enter the Name :");
		scanf(" %[^\n]", addressBook->contacts[i].name);
		int n = strlen(addressBook->contacts[i].name);
		flag = 0;

		for(int j = 0; j < n; j++) {
			if(isalnum(addressBook->contacts[i].name[j]) || addressBook->contacts[i].name[j] == ' ') {
			}
			else {
				flag = 1;
				break;
			}
		}

		if(flag == 1 || n == 0) {
			printf("Invalid input\n");
		}
		else {
			break;
		}
	}

	while(1) {
		present = 0;
		printf("Enter the phone number: ");
		scanf("%s", addressBook->contacts[i].phone);
		int n = strlen(addressBook->contacts[i].phone);
		flag = 0;

		if(n == 10 && addressBook->contacts[i].phone[0] >= '6' && addressBook->contacts[i].phone[0] <= '9') {
			for(int j = 0; j < n; j++) {
				if(addressBook->contacts[i].phone[j] >= '0' && addressBook->contacts[i].phone[j] <= '9') {
				}
				else {
					flag = 1;
					break;
				}
			}
		}
		else {
			flag = 1;
		}

		if(flag == 1) {
			printf("Invalid phone number\n");
		}
		else {
			if(i >= 1) {
				for(int j = 0; j < i; j++) {
					if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[i].phone) == 0) {
						present = 1;
						break;
					}
				}
			}

			if(present == 1) {
				printf("Phone number already present\n");
			}
			else {
				break;
			}
		}
	}

	while (1) {
    present = 0;
    flag = 1;
    char ch[5] = ".com";

    printf("Enter the email id: ");
    scanf("%s", addressBook->contacts[i].email);

    int n = strlen(addressBook->contacts[i].email);
    int at = 0, atIdx = -1, dot = 0;

    if (!isalnum(addressBook->contacts[i].email[0])) {
        flag = 0;
    }

    if (flag == 1) {
        for (int j = 0; j < n; j++) {
            if (addressBook->contacts[i].email[j] == '.') {
                dot++;
            }
            if (isupper(addressBook->contacts[i].email[j])) {
                flag = 0;
                break;
            }
            if (addressBook->contacts[i].email[j] == '@') {
                at++;
                atIdx = j;
            }
        }
    }

    if (flag == 1 && at == 1 && dot == 1 && n >= 6) {
        if (atIdx > 0 && !isalnum(addressBook->contacts[i].email[atIdx - 1])) {
            flag = 0;
        } 
		else {
            for (int k = 0; k < 4; k++) {
                if (addressBook->contacts[i].email[n - 4 + k] != ch[k]) {
                    flag = 0;
                    break;
                }
            }
        }
    } 
	else {
        flag = 0;
    }

    if (flag == 1) {
        if ((n - 4) - (atIdx + 1) < 1) {
            flag = 0;
        }
    }

    if (flag == 0) {
        printf("Invalid email id\n");
    } 
	else {
        if (i >= 1) {
            for (int j = 0; j < i; j++) {
                if (strcmp(addressBook->contacts[j].email, addressBook->contacts[i].email) == 0) {
                    present = 1;
                    break;
                }
            }
        }

        if (present == 1) {
            printf("Email already present\n");
        } else {
            break;
        }
    }
}

	(addressBook->contactCount)++;
	printf("Contact created successfully!\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    int n = addressBook->contactCount;
	if (n == 0) {
		printf("Address book is empty.\n");
		return;
	}

	char target[50];
	int search;

	while(1) {
		int flag = 0;
		printf("Enter 1 to search Name\n");
		printf("Enter 2 to search Phone\n");
		printf("Enter 3 to search email\n");
		printf("Enter your choice :");
		scanf("%d", &search);

		if(search == 1) {
			printf("Enter the name to search :");
			scanf(" %[^\n]", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].name, target) != NULL) {
					flag = 1;
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
				}
			}
			if(flag == 0){
			    printf("Name not found\n");
			}
		} 
		else if(search == 2) {
			printf("Enter the phone number to search :");
			scanf("%s", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].phone, target) != NULL) {
					flag = 1;
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
				}
			}
			if(flag == 0){
			    printf("Phone number not found\n");
			}
		}
		else if(search == 3) {
			printf("Enter the email to search :");
			scanf("%s", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].email, target) != NULL) {
					flag = 1;
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
				}
			}
			if(flag == 0) {
			printf("Email not found\n");
			}
		} 
		else {
			printf("Invalid choice\n");
		}

		if(flag == 1){
		    break;
	}
}
}

void editContact(AddressBook *addressBook)
{
	int count = addressBook->contactCount;
	if (count == 0) {
		printf("Address book is empty.\n");
		return;
	}

	char target[50];
	int search;
	int match[100] = {0};

	while(1) {
		int l = 0, k = 1;
		printf("Enter 1 to edit Name\n");
		printf("Enter 2 to edit Phone\n");
		printf("Enter 3 to edit Email\n");
		printf("Enter your choice :");
		scanf("%d", &search);

		if(search == 1) {
			printf("Enter the name to find: ");
			scanf(" %[^\n]", target);
			for(int j = 0; j < count; j++) {
				if(strcasestr(addressBook->contacts[j].name, target) != NULL) {
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
					match[l++] = j;
					k++;
				}
			}
		} else if(search == 2) {
			printf("Enter the phone number to find: ");
			scanf("%s", target);
			for(int j = 0; j < count; j++) {
				if(strcasestr(addressBook->contacts[j].phone, target) != NULL) {
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
					match[l++] = j;
					k++;
				}
			}
		} else if(search == 3) {
			printf("Enter the email to find: ");
			scanf("%s", target);
			for(int j = 0; j < count; j++) {
				if(strcasestr(addressBook->contacts[j].email, target) != NULL) {
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
					match[l++] = j;
					k++;
				}
			}
		} else {
			printf("Invalid choice\n");
			continue;
		}

		if(l == 0) {
			printf("No matching contact found\n");
			continue;
		}

		int index;
		printf("Enter the index to edit : ");
		scanf("%d", &index);
		if(index < 1 || index > l) {
			printf("Invalid index selected.\n");
			continue;
		}

		int del = match[index - 1];

		int editChoice;
		printf("Enter 1 to edit Name\n");
		printf("Enter 2 to edit Phone\n");
		printf("Enter 3 to edit Email\n");
		printf("Enter choice: ");
		scanf("%d", &editChoice);

		if(editChoice == 1) {
			while(1) {
				char tempName[50];
				printf("Enter the new Name : ");
				scanf(" %[^\n]", tempName);
				int n = strlen(tempName), flag = 0;
				for(int j = 0; j < n; j++) {
					if(!isalnum(tempName[j]) && tempName[j] != ' ') {
						flag = 1;
						break;
					}
				}
				if(flag == 1 || n == 0) {
					printf("Invalid input\n");
				} else {
					strcpy(addressBook->contacts[del].name, tempName);
					printf("Name successfully changed!\n");
					return;
				}
			}
		} else if(editChoice == 2) {
			while(1) {
				char tempPhone[20];
				printf("Enter the new Phone number: ");
				scanf("%s", tempPhone);
				int n = strlen(tempPhone), flag = 0, present = 0;
				if(n != 10 || tempPhone[0] < '6' || tempPhone[0] > '9') flag = 1;
				for(int j = 0; j < n && !flag; j++) {
					if(!isdigit(tempPhone[j])) {
                        flag = 1;
				}
				if(flag == 1) {
					printf("Invalid phone number\n");
					continue;
				}
				for(int j = 0; j < count; j++) {
					if(j != del && strcmp(addressBook->contacts[j].phone, tempPhone) == 0) {
						present = 1;
						break;
					}
				}
				if(present) {
					printf("Phone number already present\n");
				} else {
					strcpy(addressBook->contacts[del].phone, tempPhone);
					printf("Phone number successfully changed!\n");
					return;
				}
			}
		} 
	}
		else if(editChoice == 3) {
			while(1) {
				char tempEmail[50];
				printf("Enter the new Email: ");
				scanf("%s", tempEmail);
				int n = strlen(tempEmail), flag = 1, at = 0, atIdx = -1, present = 0,dot=0;
				char ch[5] = ".com";

				if(!isalnum(tempEmail[0])){ 
				    flag = 0;
				}

				if(flag == 1) {
					for(int j = 0; j < n; j++) {
						if(tempEmail[j] == '.'){
							dot++;
						}
						if(isupper(tempEmail[j])) { 
						    flag = 0; 
						    break; 
						    
						}
						if(tempEmail[j] == '@') { 
						    at++; 
						    atIdx = j; 
						    
						}
					}
				}

				if(flag == 1 && at == 1 && dot==1 && n >= 5) {
					if(atIdx>0 && !isalnum(tempEmail[atIdx-1])){
						flag=0;
					}
					else{
					for(int k = 0; k < 4; k++) {
						if(tempEmail[n - 4 + k] != ch[k]) { 
						    flag = 0; 
						    break; 
						    
						}
					}
				} 
			}
				else { 
				    flag = 0; 
				    
				}

				if(flag == 1 && ((n - 4) - (atIdx + 1) < 1)) {
				flag = 0;
				}

				if(flag == 0) {
					printf("Invalid email id\n");
					continue;
				}

				for(int j = 0; j < count; j++) {
					if(j != del && strcmp(addressBook->contacts[j].email, tempEmail) == 0) {
						present = 1;
						break;
					}
				}
				if(present) {
					printf("Email already present\n");
				} else {
					strcpy(addressBook->contacts[del].email, tempEmail);
					printf("Email successfully changed!\n");
					return;
				}
			}
		} 
		else {
			printf("Invalid choice\n");
			return;
		}
	}
    
}

void deleteContact(AddressBook *addressBook)
{
	int n = addressBook->contactCount;
	if (n == 0) {
		printf("Address book is empty.\n");
		return;
	}

	char target[50];
	int search;
	int match[100] = {0};
	int l = 0, k = 1, index = 0;

	while(1) {
		int flag = 0;
		l = 0;
		k = 1;

		printf("Enter 1 to delete by Name\n");
		printf("Enter 2 to delete by Phone\n");
		printf("Enter 3 to delete by Email\n");
		printf("Enter your choice :");
		scanf("%d", &search);

		if(search == 1) {
			printf("Enter the name to delete : ");
			scanf(" %[^\n]", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].name, target) != NULL) {
					flag = 1;
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					match[l++] = i;
					k++;
				}
			}
		} else if(search == 2) {
			printf("Enter the phone number to delete : ");
			scanf("%s", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].phone, target) != NULL) {
					flag = 1;
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					match[l++] = i;
					k++;
				}
			}
		} else if(search == 3) {
			printf("Enter the email to delete : ");
			scanf("%s", target);
			for(int i = 0; i < n; i++) {
				if(strcasestr(addressBook->contacts[i].email, target) != NULL) {
					flag = 1;
					printf("%d = %s\t%s\t%s\n", k, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					match[l++] = i;
					k++;
				}
			}
		} else {
			printf("Invalid choice\n");
			continue;
		}

		if(flag == 1) {
			printf("Enter the index to delete: ");
			scanf("%d", &index);
			if(index >= 1 && index <= l) {
				int delIdx = match[index - 1];
				for(int i = delIdx; i < n - 1; i++) {
					addressBook->contacts[i] = addressBook->contacts[i + 1];
				}
				(addressBook->contactCount)--;
				printf("Contact deleted successfully.\n");
				break;
			} else {
				printf("Invalid index selected.\n");
			}
		} else {
			printf("No matching contact found.\n");
		}
	}
   
}
