#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//shani
static char current_user[25];

typedef struct manager
{
	char last_name[25];
	char first_name[25];
	char user_name[25];
	char phone[11];
	int  age;
	char password[25];
}manager;

typedef struct customer
{
	char last_name[25];
	char first_name[25];
	char user_name[25];
	char phone[11];
	int age;
	char city[20];
	char adress[50];
	char password[25];
}customer;

typedef struct product
{
	char product_name[25];
	char price[10];
	char amount_of_product[5];
}product;

void menu();
int register_manager();
int register_customer();
int checkm(char last[25], char first[25], char user[25], char phone[11], int age, char password1[25], char password2[25]);
int checkc(char last[25], char first[25], char user[25], char phone[11], int age, char city[20], char adress[50], char password1[25], char password2[25]);
int termofuse();
int login_manager();
int login_customer();

int string_check(char str[25]);                                                 ////////    v
int capital_letters_check(char str[25]);                                        ////////    v
int check_price(char price[25]);                                                ////////    v
int check_number(char amount[25]);                                              ////////    v
int check_phone(char phone[11]);                                                ////////    v
int check_password(char password[25]);                                          ////////    v
int check_adress(char adress[50]);
int check_ID(char number[10]);

void add_category();                                                            ////////    v
void add_product(char choice[5]);                                               ////////    v
void delete_product(char choicecat[5], char choicepro[5]);                      ////////    v
void update_product_by_search();                                                ////////    v
void choose_product_to_update();                                                ////////    v
void print_all_orders();                                                        ////////    v
int print_all_category(); //returns number of printed categories                ////////    v


// print orders - manager, ZACC
void print_all_orders();                                                        ////////    v
void search_order_by_number();                                                  ////////    v
void search_order_by_customer();                     //לא בדקתי


// Status of order functions - manager, ZACC
void print_canceled_orders();                        //לא בדקתי
void print_approved_orders();                        //לא בדקתי
void print_not_updated_orders();                     //לא בדקתי
void update_status();                                //לא בדקתי


void manager_profile();                                                         ////////    v
void costumer_profile(char userName[25]);

// view stock functions - 3
void view_all_stock();                                                          ////////    v
int view_specific_category(int choice);                                         ////////    v
void view_specific_product(char product_name[25]);                              ////////    v


// Menu functions - Manager
void manager_menu();                              //לא בדקתי
void menu_add_category_product();                 //לא בדקתי
void menu_order_status();                         //לא בדקתי
void menu_view_orders_manager();                  //לא בדקתי
void menu_view_stock();                           //לא בדקתי
void menu_updating_product();                     //לא בדקת
void menu_delete();

// Menu functions - Costumer
void customer_menu();
void menu_customer_profile();
void menu_view_basket();


// Customer function
void search_product_customer(char productT[25]);
void print_previous_order_costumer();
int print_customer_basket();
void edit_customer_basket(int choice);
void payment();
void add_product_to_basket_from_menu(char choicecat[5], char choicepro[5], char quantity[5]);
int struct_cmp_by_increasing_order(const void* a, const void* b);
int struct_cmp_by_descending_order(const void* a, const void* b);
void print_struct_array(struct product* array, int len);
void sort_A(char category[5]);
void sort_D(char category[5]);


int main()
{
	FILE* fic = fopen("Basket.csv", "w+");
	fputc(' ', fic);
	fclose(fic);
	menu();
	return 0;
}

void menu()
{
	char account[2], connection[2];
	printf("\t\t\t1-Manager\n\t\t\t2-Customer\n");
	scanf(" %s", account);
	while (atoi(account) != 1 && atoi(account) != 2)
	{
		printf("Bad choice. Try again\n");
		scanf(" %s", account);
	}
	printf("\t\t\t1-Log In\n\t\t\t2-Register\n");
	scanf(" %s", connection);
	while (atoi(connection) != 1 && atoi(connection) != 2)
	{
		printf("Bad choice. Try again\n");
		scanf(" %s", connection);
	}

	if (atoi(account) == 1)
	{
		if (atoi(connection) == 1)
		{
			while (login_manager() == 0)
				printf("\nYour user name or your password is not correct. Please try again.\n");
			manager_menu();
		}
		else
		{
			if (register_manager() == 0)
				printf("Please note, you hasn't been registered.\n");
			return menu();

		}
	}
	else
	{
		if (atoi(connection) == 1)
		{
			while (login_customer() == 0)
				printf("\nYour user name or your password is not correct. Please try again.\n");
			customer_menu();
		}
		else
		{
			if (register_customer() == 0)
				printf("Please note, you hasn't been registered.\n");
			return menu();
		}
	}
	return menu;
}

int register_manager()
{
	FILE* fic = fopen("ManagersInformation.csv", "r+");
	if (fic == NULL)
		exit(1);
	char cpassword[25];
	manager data;

	do
	{
		printf("Last name (without characters): ");
		scanf("%s", data.last_name);
		printf("First name (without characters): ");
		scanf("%s", data.first_name);
		printf("User name: ");
		scanf("%s", data.user_name);
		printf("Phone number (must start with 05): ");
		scanf("%s", data.phone);
		printf("Age (must be under 120): ");
		scanf_s("%d", &data.age);
		printf("Password (must include one capital letter and minimum 6 characters): ");
		scanf("%s", data.password);
		printf("Write again your password: ");
		scanf("%s", cpassword);
	} while (checkm(data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password, cpassword) == 0);

	if (termofuse() == 0)
		return 0;

	fseek(fic, 0, SEEK_END);
	fprintf(fic, "\n%s,%s,%s,%s,%d,%s", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password);
	fclose(fic);
	return 1;
}

int register_customer()
{
	FILE* fic = fopen("CustomersInformation.csv", "r+");
	if (fic == NULL)
		exit(1);
	char cpassword[25];
	customer data;

	do
	{
		printf("Last name (without characters): ");
		scanf("%s", data.last_name);
		printf("First name (without characters): ");
		scanf("%s", data.first_name);
		printf("User name: ");
		scanf("%s", data.user_name);
		printf("Phone number (must start with 05): ");
		scanf("%s", data.phone);
		printf("Age (must be under 120): ");
		scanf_s("%d", &data.age);
		printf("City (without characters): ");
		scanf(" %[^\n]", data.city);
		printf("Adress (without characters and one number): ");
		scanf(" %[^\n]", data.adress);
		printf("Password (must include one capital letter and minimum 6 characters): ");
		scanf("%s", data.password);
		printf("Write again your password: ");
		scanf("%s", cpassword);
	} while (checkc(data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password, cpassword) == 0);

	if (termofuse() == 0)
		return 0;

	fseek(fic, 0, SEEK_END);
	fprintf(fic, "\n%s,%s,%s,%s,%d,%s,%s,%s", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password);
	fclose(fic);
	return 1;
}

int checkm(char last[25], char first[25], char user[25], char phone[11], int age, char password1[25], char password2[25])
{
	int cap_letter = 0;
	for (int i = 0; i < strlen(last); i++)
	{
		if (last[i] < 'A' || last[i]>'z' || (last[i] > 'Z' && last[i] < 'a'))
		{
			printf("\nYour last name is not correct. Please try again.\n");
			return 0;
		}
	}
	for (int i = 0; i < strlen(first); i++)
	{
		if (first[i] < 'A' || first[i]>'z' || (first[i] > 'Z' && first[i] < 'a'))
		{
			printf("\nYour first name is not correct. Please try again.\n");
			return 0;
		}
	}
	if (phone[0] != '0' || phone[1] != '5' || phone[10] != '\0')
	{
		printf("\nYour phone number is not correct. Please try again.\n");
		return 0;
	}
	if (age > 120)
	{
		printf("\nYour age is not correct. Please try again.\n");
		return 0;
	}
	for (int i = 2; i < 10; i++)
	{
		if (phone[i] < '0' || phone[i]>'9')
		{
			printf("\nYour phone number is not correct. Please try again.\n");
			return 0;
		}
	}
	for (int i = 0; i < strlen(password1); i++)
		if (password1[i] >= 'A' && password1[i] <= 'Z')
			cap_letter++;
	if (strlen(password1) < 6 || strlen(password2) < 6 || strlen(password1) != strlen(password2) || cap_letter == 0 || strcmp(password1, password2) != 0)
	{
		printf("\nYour password is not correct. Please try again.\n");
		return 0;
	}
	return 1;
}

int checkc(char last[25], char first[25], char user[25], char phone[11], int age, char city[20], char adress[50], char password1[25], char password2[25])
{
	int cap_letter = 0, number = 0;
	for (int i = 0; i < strlen(last); i++)
	{
		if (last[i] < 'A' || last[i]>'z' || (last[i] > 'Z' && last[i] < 'a'))
		{
			printf("\nYour last name is not correct. Please try again.\n");
			return 0;
		}
	}
	for (int i = 0; i < strlen(first); i++)
	{
		if (first[i] < 'A' || first[i]>'z' || (first[i] > 'Z' && first[i] < 'a'))
		{
			printf("\nYour first name is not correct. Please try again.\n");
			return 0;
		}
	}
	if (phone[0] != '0' || phone[1] != '5' || phone[10] != '\0')
	{
		printf("\nYour phone number is not correct. Please try again.\n");
		return 0;
	}
	for (int i = 2; i < 10; i++)
	{
		if (phone[i] < '0' || phone[i]>'9')
		{
			printf("\nYour phone number is not correct. Please try again.\n");
			return 0;
		}
	}
	if (age > 120)
	{
		printf("\nYour age is not correct. Please try again.\n");
		return 0;
	}
	for (int i = 0; i < strlen(city); i++)
	{
		if (city[i] < 'A' || city[i]>'z' || (city[i] > 'Z' && city[i] < 'a'))
		{
			printf("\nYour city is not correct. Please try again.\n");
			return 0;
		}
	}
	for (int i = 0; i < strlen(adress); i++)
	{
		if ((adress[i] < '0' && adress[i] != ' ') || adress[i] > 'z' || (adress[i] > 'Z' && adress[i] < 'a') || (adress[i] > '9' && adress[i] < 'A'))
		{
			printf("\nYour adress is not correct. Please try again.\n");
			return 0;
		}
		if (adress[i] >= '0' && adress[i] <= '9')
			number++;
	}
	if (number == 0)
	{
		printf("\nYour age is not correct. Please try again.\n");
		return 0;
	}
	for (int i = 0; i < strlen(password1); i++)
		if (password1[i] >= 'A' && password1[i] <= 'Z')
			cap_letter++;
	if (strlen(password1) < 6 || strlen(password2) < 6 || strlen(password1) != strlen(password2) || cap_letter == 0 || strcmp(password1, password2) != 0)
	{
		printf("\nYour password is not correct. Please try again.\n");
		return 0;
	}
	return 1;
}

int termofuse()
{
	int choice;
	printf("Welcome to the site, maintaining your privacy is important to us and we pay special attention to it.\n");
	printf("This document represents the privacy policy of 'CLICK AND GET' Ltd.regarding the information provided by you within the site.\nThe purpose of the privacy policy is to ensure that the data about you in databases and their use will be made only in accordance with your consent and the law.\n");
	printf("A legal obligation to provide the informationand its delivery depends on your consentand desire.");
	printf("\n- What information do we collectand why ?\nTechnical information that may include browsing and exposure data stored for statistical purposes.");
	printf("\n- Is the information about you passed on to third parties ?\nThe company will not pass on your personal information to others.");
	printf("\n- Is the information about you secure ?\nThe company uses advanced technological security measures to secure your information.\n");
	printf("\n\n1- Accept\t\t\t2- Deny\n");
	scanf_s("%d", &choice);
	while (choice != 1 && choice != 2)
	{
		printf("Bad choice. Try again\n");
		scanf_s("%d", &choice);
	}
	if (choice == 2)
		return 0;
	return 1;
}

int login_manager()
{
	FILE* fic = fopen("ManagersInformation.csv", "r+");
	if (fic == NULL)
		exit(1);
	char username1[25];
	char password1[25];
	manager data;
	printf("User name: ");
	scanf("%s", username1);
	printf("Password: ");
	scanf("%s", password1);
	fseek(fic, 58, SEEK_SET);
	do
	{
		fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.password);
		if (strcmp(username1, data.user_name) == 0 && strcmp(password1, data.password) == 0)
		{
			fclose(fic);
			strcpy(current_user, username1);
			return 1;
		}
	} while (!feof(fic));
	fclose(fic);
	return 0;
}

int login_customer()
{
	FILE* fic = fopen("CustomersInformation.csv", "r+");
	if (fic == NULL)
		exit(1);
	char username1[25];
	char password1[25];
	customer data;
	printf("User name: ");
	scanf("%s", username1);
	printf("Password: ");
	scanf("%s", password1);
	fseek(fic, 70, SEEK_SET);
	do
	{
		fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.city, data.adress, data.password);
		if (strcmp(username1, data.user_name) == 0 && strcmp(password1, data.password) == 0)
		{
			fclose(fic);
			strcpy(current_user, username1);
			return 1;
		}
	} while (!feof(fic));
	fclose(fic);
	return 0;
}

// Checks the string is string of only letters
int string_check(char str[25])
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i]>'z')
			return 1; //the stringis not only letters
		else
			return 0; //the string is correct
	}
}

// Checks if the string includes only capital letters
int capital_letters_check(char str[25])
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] < 'A' || str[i] > 'Z')
			return 1; //the string is not only capital letters
	}
	return 0; //the string is correct
}

// Checking if the entered product price is valid
int check_price(char price[25])
{
	for (int i = 0; i < strlen(price); ++i)
	{
		if (price[i] < '0' || price[i]>'9')
			return 1; // The price is not valid
	}
	return 0; // The price is valid
}

// Checking if the input is number
int check_number(char amount[25])
{
	for (int i = 0; i < strlen(amount); i++)
	{
		if (amount[i] < '0' || amount[i] >'9')
			return 1; // The amount is not valid
	}
	return 0;
}

// Check phone - start with 05
int check_phone(char phone[11])
{
	for (int i = 2; i < 10; i++)
	{
		if (phone[i] < '0' || phone[i]>'9')
		{
			return 1;
		}
	}
	if (phone[0] != '0' || phone[1] != '5' || phone[10] != '\0')
	{
		return 1;
	}
	return 0;
}

// check the password
int check_password(char password[25])
{
	int cap_letter = 0;
	for (int i = 0; i < strlen(password); i++)
		if (password[i] >= 'A' && password[i] <= 'Z')
			cap_letter++;
	if (strlen(password) < 6 || cap_letter == 0)
	{
		return 1;  //wrong
	}
	return 0;
}

// check adress
int check_adress(char adress[50])
{
	int number = 0;
	for (int i = 0; i < strlen(adress); i++)
	{
		if ((adress[i] < '0' && adress[i] != ' ') || adress[i] > 'z' || (adress[i] > 'Z' && adress[i] < 'a') || (adress[i] > '9' && adress[i] < 'A'))
		{
			return 1;
		}
		if (adress[i] >= '0' && adress[i] <= '9')
			number++;
	}
	if (number == 0)
	{
		return 1;
	}
	return 0;
}

int check_ID(char number[10])
{
	long tz = atol(number);
	int i = tz;
	int counter = 0, sum, bikoret = 0;
	while (i > 0)
	{
		i /= 10;
		counter++;
	}
	if (counter > 9)
		return 0;
	sum = (tz / 100000000) + (((tz / 10000000) % 10) * 2) / 10 + (((tz / 10000000) % 10) * 2) % 10 + ((tz / 1000000) % 10) + (((tz / 100000) % 10) * 2) / 10 + (((tz / 100000) % 10) * 2) % 10 + ((tz / 10000) % 10) + (((tz / 1000) % 10) * 2) / 10 + (((tz / 1000) % 10) * 2) % 10 + ((tz / 100) % 10) + (((tz % 100) / 10) * 2) / 10 + (((tz % 100) / 10) * 2) % 10;
	for (sum; sum % 10 != 0; sum++)
		bikoret++;
	tz %= 10;
	if (bikoret == tz)
		return 0;       //correct
	else
		return 1;       //uncorrect
}

// Adds new category
void add_category()
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char category[25];
	char some_category[25];
	printf("Enter the new category you want to add: \n");
	scanf(" %[^\n]", category);
	fseek(fic, 17, SEEK_SET);
	while (string_check(category) == 1)
	{
		printf("Your category name is not correct, Please try again\n");
		scanf(" %[^\n]", category);
	}
	char test[5000];
	do
	{
		fscanf(fic, " %[^,],%[^\n]\n", some_category, test);
		if (strcmp(some_category, category) == 0)
		{
			printf("\nThe inserted category already exists\n");
			fclose(fic);
			return manager_menu();
		}
	} while (!feof(fic));

	fprintf(fic, "\n%s,", category);
	printf("\nThe new category has been added\n");
	fclose(fic);
	return manager_menu();
}

//Adds new product
void add_product(char choice[5])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	product dataenter;
	char c = fgetc(fic);
	int choice2 = atoi(choice);
	int counter = 0;
	printf("Name of product (Only capital letters): ");
	scanf(" %[^\n]", dataenter.product_name);
	while (capital_letters_check(dataenter.product_name) == 1)
	{
		printf("Your product name is not valid, Please try again: ");
		scanf(" %[^\n]", dataenter.product_name);
	}

	printf("Price of product (Positive integer number): ");
	scanf(" %[^\n]", dataenter.price);
	while (check_price(dataenter.price) == 1)
	{
		printf("Your product price is not valid, Please try again :");
		scanf(" %[^\n]", dataenter.price);
	}

	printf("Amount of product: ");
	scanf(" %[^\n]", dataenter.amount_of_product);
	while (check_number(dataenter.amount_of_product) == 1)
	{
		printf("Your product quantity is not valid, Please try again");
		scanf(" %[^\n]", dataenter.amount_of_product);
	}

	product data;
	fseek(fic, 21, SEEK_SET);
	while (!feof(fic))
	{
		if (counter == choice2 - 1)
			break;
		c = fgetc(fic);
		if (c == '\n')
			++counter;
	}
	while (c != ',')
		c = fgetc(fic);

	while (!feof(fic) && c != '\n')
	{
		c = ' ';
		fscanf(fic, "%[^;]", data.product_name);
		if (strcmp(data.product_name, dataenter.product_name) == 0)
		{
			printf("The inserted product already exists");
			fclose(fic);
			return menu_add_category_product();
		}
		while (c != '\n' && !feof(fic) && c != ',')
		{
			c = fgetc(fic);
			if (c == '\n' && !feof(fic))
				break;
		}
	}
	fseek(fic, 0, SEEK_SET);
	c = fgetc(fic);
	counter = 0;
	FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
	while (!feof(fic))
	{
		if (c == '\n')
			++counter;
		if (counter == choice2 + 1)
		{
			fputc(',', fic2);
			fprintf(fic2, "%s;%s;%s;", dataenter.product_name, dataenter.price, dataenter.amount_of_product);
			counter++;
		}
		fputc(c, fic2);
		c = fgetc(fic);
		if (feof(fic) && (counter == choice2))
		{
			fputc(',', fic2);
			fprintf(fic2, "%s;%s;%s;", dataenter.product_name, dataenter.price, dataenter.amount_of_product);
		}
	}
	fseek(fic, 0, SEEK_SET);
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("\nThe product has been added successfully\n");
	return manager_menu();
}

// Deletes product
void delete_product(char choicecat[5], char choicepro[5])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c = fgetc(fic), d = ' ';
	int choice2 = atoi(choicecat), choice3 = atoi(choicepro);
	int counter1 = 0, counter2 = 0;
	product data;

	FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
	while (counter1 != choice2)
	{
		putc(c, fic2);
		c = fgetc(fic);
		if (c == '\n')
			counter1++;
	}
	while (counter2 != choice3)
	{
		putc(c, fic2);
		c = fgetc(fic);
		if (c == ',')
			counter2++;
	}
	fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
	d = fgetc(fic);
	while (!feof(fic))
	{
		putc(d, fic2);
		d = fgetc(fic);
	}

	fseek(fic, 0, SEEK_SET);
	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "w");
	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("\nThe product has been deleted successfully\n");
	return manager_menu();
}



//Prints all categories
int print_all_category()
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	fseek(fic, 18, SEEK_SET);
	char category[25];
	int num = 0;
	printf("CATEGORIES: \n");
	char c = fgetc(fic);
	while (!feof(fic))
	{
		++num;
		fscanf(fic, "%[^,]", category);
		printf("%d -  %s\n", num, category);
		c = fgetc(fic);
		while (c != '\n' && !feof(fic))
		{
			c = fgetc(fic);
		}
	}
	fclose(fic);
	return num;
}

// print all orders
void print_all_orders()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], status[2], nameofcustomer[25], product[31];
	int amount, total;
	char c = ' ';
	fseek(fic, 59, SEEK_SET);
	printf("\nNumber of the order / Status / Customer / Amount / Total / Products \n\n", nbr_orders, status, nameofcustomer);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, nameofcustomer, &amount, &total);
		printf("%s / %s / %s / %d / %d /", nbr_orders, status, nameofcustomer, amount, total);
		while (c != '\n' && c != EOF)
		{
			fscanf(fic, "%[^;];", product);
			printf("%s; ", product);
			c = fgetc(fic);
		}
		if (c == '\n')
			printf("\n");
	}
	fclose(fic);
	printf("\n");
}

// search order by its number and print it
void search_order_by_number()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], order[5], status[2], nameofcustomer[25], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	printf("\n Please enter the number of the order you are looking for :");
	scanf(" %s", order);
	fseek(fic, 59, SEEK_SET);
	while (c != EOF)
	{
		c = getc(fic);
		if (c == '\n')
			counter++;
	}
	for (i = 0; i < strlen(order); i++)
	{
		if (order[i] < '0' || order[i] >'9')
			break;
	}
	while (i != strlen(order) || atoi(order) > counter)
	{
		printf("\n Your number is not correct. Try again :");
		scanf(" %s", order);
		for (i = 0; i < strlen(order); i++)
		{
			if (order[i] < '0' || order[i] >'9')
				break;
		}
	}
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],", nbr_orders);
		if (strcmp(nbr_orders, order) == 0)
		{
			c = ' ';
			fscanf(fic, "%[^,],%[^,],%d,%d,", status, nameofcustomer, &amount, &total);
			printf("\nStatus: %s\nCustomer: %s\nAmount: %d\nTotal: %d\nProducts: ", status, nameofcustomer, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = 'X';
			break;
		}
		while (c != '\n' && c != EOF)
			c = fgetc(fic);
	}
	if (c != 'X')
		printf("\n Your order number is not correct.");
	fclose(fic);
	return manager_menu();
}

// search order by costumer name and print it
void search_order_by_customer()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);

	char nbr_orders[5], customer[25], status[2], nameofcustomer[25], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	printf("\n Please enter the name of the customer you are looking for :");
	scanf(" %s", customer);

	for (i = 0; i < strlen(customer); i++)
		if (customer[i] < 'A' || customer[i]>'z' || (customer[i] > 'Z' && customer[i] < 'a'))
			break;

	while (i != strlen(customer))
	{
		printf("\n Your name of the customer is not correct. Try again :");
		scanf(" %s", customer);
		for (i = 0; i < strlen(customer); i++)
			if (customer[i] < 'A' || customer[i]>'z' || (customer[i] > 'Z' && customer[i] < 'a'))
				break;
	}
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, nameofcustomer, &amount, &total);
		if (strcmp(nameofcustomer, customer) == 0)
		{
			c = ' ';
			printf("\nOrder's number: %s\nStatus: %s\nAmount: %d\nTotal: %d\nProducts: ", nbr_orders, status, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = 'X';
			counter = -1;
		}
		while (c != '\n' && c != EOF)
			c = fgetc(fic);
	}
	if (counter != -1)
		printf("\n Your customer name is not correct.");
	fclose(fic);
	return manager_menu();
}



// Prints all canceled orders
void print_canceled_orders()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], order[5], status[2], nameofcustomer[25], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, nameofcustomer, &amount, &total);
		if (strcmp(status, "X") == 0)
		{
			c = ' ';
			printf("\nOrder's number: %s\nCustomer: %s\nAmount: %d\nTotal: %d\nProducts: ", nbr_orders, nameofcustomer, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = ' ';
			counter = -1;
		}
		else
		{
			while (c != '\n' && c != EOF)
				c = fgetc(fic);
		}
	}
	if (counter != -1)
		printf("\n There are no canceled orders.");
	fclose(fic);
	return manager_menu();
}

// Prints all approved orders
void print_approved_orders()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], order[5], status[2], nameofcustomer[25], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, nameofcustomer, &amount, &total);
		if (strcmp(status, "V") == 0)
		{
			c = ' ';
			printf("\nOrder's number: %s\nCustomer: %s\nAmount: %d\nTotal: %d\nProducts: ", nbr_orders, nameofcustomer, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = ' ';
			counter = -1;
		}
		else
		{
			while (c != '\n' && c != EOF)
				c = fgetc(fic);
		}
	}
	if (counter != -1)
		printf("\n There are no approved orders.");
	fclose(fic);
	return manager_menu();
}

// Prints all not updated orders
void print_not_updated_orders()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], order[5], status[2], nameofcustomer[25], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, nameofcustomer, &amount, &total);
		if (strcmp(status, "-") == 0)
		{
			c = ' ';
			printf("\nOrder's number: %s\nCustomer: %s\nAmount: %d\nTotal: %d\nProducts: ", nbr_orders, nameofcustomer, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = ' ';
			counter = -1;
		}
		else
		{
			while (c != '\n' && c != EOF)
				c = fgetc(fic);
		}
	}
	if (counter != -1)
		printf("\n There are no orders that are no updated.");
	fclose(fic);
	return manager_menu();
}

// Updates status of an order
void update_status()
{
	print_all_orders();
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);
	char nbr_orders[5], order[5], status[2], nameofcustomer[25], product[31], choice[2];
	int amount, total, i, counter = 1;
	char c = ' ', d;
	printf("\nPlease enter the number of the order you want to change the status :");
	scanf(" %s", order);
	fseek(fic, 59, SEEK_SET);
	while (c != EOF)
	{
		c = getc(fic);
		if (c == '\n')
			counter++;
	}
	for (i = 0; i < strlen(order); i++)
	{
		if (order[i] < '0' || order[i] >'9')
			break;
	}
	while (i != strlen(order) || atoi(order) > counter)
	{
		printf("\nYour number is not correct. Try again :");
		scanf(" %s", order);
		for (i = 0; i < strlen(order); i++)
		{
			if (order[i] < '0' || order[i] >'9')
				break;
		}
	}
	fseek(fic, 0, SEEK_SET);
	c = fgetc(fic);

	FILE* fic2 = fopen("OrdersTEST.csv", "r+");
	while (c != '\n')
	{
		fputc(c, fic2);
		c = fgetc(fic);
	}
	fputc(c, fic2);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],", nbr_orders);
		if (strcmp(order, nbr_orders) == 0)
		{
			printf("\nWhat do you want to do : \t1 - Approve it\t\t2 - Cancel it\n", status);
			scanf(" %s", choice);
			while (atoi(choice) != 1 && atoi(choice) != 2)
			{
				printf("\nYour choice is not correct. Try again :");
				scanf(" %s", choice);
			}
			fprintf(fic2, "%s,", nbr_orders);
			fscanf(fic, "%[^,]", status);
			if (atoi(choice) == 1)
			{
				d = 'V';
				fprintf(fic2, "%c", d);
			}
			else
			{
				d = 'X';
				fprintf(fic2, "%c", d);
			}
			while (c != EOF)
			{
				c = fgetc(fic);
				if (c == EOF)
					break;
				fputc(c, fic2);
			}
			printf("The change has been made.\n");
			break;
		}
		else
		{
			c = ' ';
			fprintf(fic2, "%s,", nbr_orders);
			while (c != '\n')
			{
				c = fgetc(fic);
				if (c == EOF)
					break;
				fputc(c, fic2);
			}
			if (c == EOF)
				break;
		}
	}
	fclose(fic);
	fic = fopen("Orders.csv", "w");
	fclose(fic);
	fic = fopen("Orders.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (c != EOF)
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	return manager_menu();
}



// View all stock
void view_all_stock()
{
	int serial_num = 0;
	product some_product;
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c = fgetc(fic);
	fseek(fic, 19, SEEK_SET);

	while (!feof(fic))
	{
		while (c != ',')
			c = fgetc(fic);

		while (!feof(fic) && c != '\n')
		{
			++serial_num;
			fscanf(fic, " %[^;];%[^;];%[^;]", some_product.product_name, some_product.price, some_product.amount_of_product);
			printf("%d - %s\nPRICE: %s\nQUANTITY: %s\n", serial_num, some_product.product_name, some_product.price, some_product.amount_of_product);
			printf("\n");
			c = fgetc(fic);
			c = fgetc(fic);
		}
	}
	fclose(fic);
	return manager_menu();
}

//View stock of specific category
int view_specific_category(int choice)
{
	int serial_num = 0;
	char c = ' ';
	int categories_num;
	int counter = 0;
	product some_pro;
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);

	fseek(fic, 19, SEEK_SET);
	if (choice != 1)
	{
		while (!feof(fic))
		{
			c = fgetc(fic);
			if (c == '\n')
			{
				++counter;
			}
			if (counter == choice)
				break;
		}
	}
	while (c != ',')
		c = fgetc(fic);

	while (!feof(fic) && c != '\n')
	{
		++serial_num;
		fscanf(fic, " %[^;];%[^;];%[^;]", some_pro.product_name, some_pro.price, some_pro.amount_of_product);
		printf("%d - %s\nPRICE: %s\nQUANTITY: %s\n", serial_num, some_pro.product_name, some_pro.price, some_pro.amount_of_product);
		printf("\n");
		c = fgetc(fic);
		c = fgetc(fic);
	}
	fclose(fic);
	return serial_num;
}

// view specific product by searching
void view_specific_product(char product_name[25])
{
	int test = 0;
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	fseek(fic, 20, SEEK_SET);
	char c = ' ';
	product data;
	while (!feof(fic))
	{
		while (c != ',')
		{
			c = fgetc(fic);
		}
		c = ' ';
		while (c != '\n' && c != EOF)
		{
			fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
			if (strcmp(product_name, data.product_name) == 0)
			{
				printf("%s\nPRICE: %s\nQUANTITY: %s\n", data.product_name, data.price, data.amount_of_product);
				test = -1;
				break;
			}
			c = fgetc(fic);
		}
		if (test == -1)
			break;
	}
	fclose(fic);
	return manager_menu();
}

// Updates details of product by searching the product
void update_product_by_search()
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char price[10], amount_of_product[5];
	char choice;
	printf("\nPlease enter the name of the product you want to update (only with capital letters): ");
	char product_name[25], product_nameNew[25];
	product data;
	scanf(" %[^\n]", product_name);
	while (capital_letters_check(product_name) == 1)
	{
		printf("Your product name is not valid, Please try again: ");
		scanf(" %[^\n]", product_name);
	}
	fseek(fic, 21, SEEK_SET);
	char c = fgetc(fic), d = ' ';
	while (!feof(fic))
	{
		while (c != ',')
		{
			c = fgetc(fic);
		}
		c = ' ';
		while (c != '\n' && c != EOF)
		{
			fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
			if (strcmp(data.product_name, product_name) == 0)
			{
				break;
			}
			c = fgetc(fic);
		}
		if (strcmp(data.product_name, product_name) == 0)
		{
			break;
		}
	}
	if (strcmp(data.product_name, product_name) != 0)
	{
		printf("\nThe searched product has not been found.");
		return manager_menu();
	}

	printf("\n1 - Name\n2 - Price\n3 - Quantity\n");
	getchar();
	scanf("%c", &choice);
	while (choice < '0' && choice>'3')
	{
		printf("Your choice is not good. Try again.\n");
		getchar();
		scanf("%c", &choice);
	}
	if (choice == '1')
	{
		printf("\nPlease enter the new name of the product(only with capital letters): ");
		getchar();
		scanf("%[^\n]", product_nameNew);
		while (capital_letters_check(product_nameNew) == 1)
		{
			printf("Your product name is not valid, Please try again: ");
			getchar();
			scanf(" %[^\n]", product_nameNew);
		}
	}
	if (choice == '2')
	{
		printf("\nPlease enter the new price of the product (Positive integer number): ");
		getchar();
		scanf(" %[^\n]", price);
		while (check_price(price) == 1)
		{
			printf("Your product price is not valid, Please try again :");
			getchar();
			scanf(" %[^\n]", price);
		}
	}
	if (choice == '3')
	{
		printf("\nPlease enter the new amount of the product: ");
		getchar();
		scanf(" %[^\n]", amount_of_product);
		while (check_number(amount_of_product) == 1)
		{
			printf("Your product quantity is not valid, Please try again");
			getchar();
			scanf(" %[^\n]", amount_of_product);
		}
	}

	FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
	fseek(fic, 0, SEEK_SET);
	c = fgetc(fic);
	while (c != '\n')
	{
		putc(c, fic2);
		c = fgetc(fic);
	}
	while (!feof(fic))
	{
		while (c != ',' && c != EOF)
		{
			putc(c, fic2);
			c = fgetc(fic);
		}
		while (c != '\n' && c != EOF)
		{
			putc(c, fic2);
			fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
			if (choice == '1')
			{
				if (strcmp(data.product_name, product_name) == 0)
					fprintf(fic2, "%s;%s;%s;", product_nameNew, data.price, data.amount_of_product);
			}
			else if (choice == '2')
			{
				if (strcmp(data.product_name, product_name) == 0)
					fprintf(fic2, "%s;%s;%s;", data.product_name, price, data.amount_of_product);
			}
			else if (strcmp(data.product_name, product_name) == 0)
				fprintf(fic2, "%s;%s;%s;", data.product_name, data.price, amount_of_product);
			if (strcmp(data.product_name, product_name) != 0)
				fprintf(fic2, "%s;%s;%s;", data.product_name, data.price, data.amount_of_product);
			c = fgetc(fic);
		}
	}
	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "w");
	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("Product successfully updated\n");
	return manager_menu();
}

// Updates product the manager choose from list of products
void choose_product_to_update()
{
	int counter = 0;
	int serial_num;
	char choice1[3], choice2[3];
	int category_num;
	char product_name[25], price[10], amount_of_product[5];
	char product_nameNew[25];

	product some_product;
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c;
	printf("Please select the category of the product you want to update: \n");
	category_num = print_all_category();
	scanf(" %s", &choice1);
	while (check_number(choice1) != 0 || atoi(choice1) > category_num)
	{
		printf("The input is not valid!, please try again\n");
		scanf(" %s", &choice1);
	}

	printf("Please select the product you want to update: \n");
	serial_num = view_specific_category(atoi(choice1));
	scanf(" %s", &choice2);
	while (check_number(choice2) != 0 || atoi(choice2) > serial_num)
	{
		printf("The input is not valid!, please try again\n");
		scanf(" %s", &choice2);
	}
	FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
	c = fgetc(fic);
	while (c != '\n')
	{
		putc(c, fic2);
		c = fgetc(fic);
	}
	//fseek(fic, 19, SEEK_SET);
	while (!feof(fic))
	{
		if (c == '\n')
		{
			++counter;
		}
		if (counter == atoi(choice1))
			break;
		fputc(c, fic2);
		c = fgetc(fic);

	}
	counter = 0;
	while (counter != atoi(choice2))
	{
		fputc(c, fic2);
		c = fgetc(fic);
		if (c == ',')
			++counter;
	}
	fputc(c, fic2);
	// Choose the field the user wants to update
	printf("Please select the field you want to update:\n1 - Name\n2 - Price\n3 - Quantity\n");
	scanf(" %s", choice1);
	while (choice1 < '0' && choice1>'3')
	{
		printf("Your choice is not good. Try again.\n");
		getchar();
		scanf("%c", &choice1);
	}
	// Update the name of product
	if (atoi(choice1) == 1)
	{
		printf("\nPlease enter the new name of the product(only with capital letters): ");
		getchar();
		scanf("%[^\n]", product_nameNew);
		while (capital_letters_check(product_nameNew) == 1)
		{
			printf("Your product name is not valid, Please try again: ");
			getchar();
			scanf(" %[^\n]", product_nameNew);
		}
	}

	// Update the price of product
	if (atoi(choice1) == 2)
	{
		printf("\nPlease enter the new price of the product (Positive integer number): ");
		getchar();
		scanf(" %[^\n]", price);
		while (check_price(price) == 1)
		{
			printf("Your product price is not valid, Please try again :");
			getchar();
			scanf(" %[^\n]", price);
		}
	}

	// Update the quantity of product
	if (atoi(choice1) == 3)
	{
		printf("\nPlease enter the new amount of the product: ");
		getchar();
		scanf(" %[^\n]", amount_of_product);
		while (check_number(amount_of_product) == 1)
		{
			printf("Your product quantity is not valid, Please try again");
			getchar();
			scanf(" %[^\n]", amount_of_product);
		}
	}
	fscanf(fic, "%[^;];%[^;];%[^;];", some_product.product_name, some_product.price, some_product.amount_of_product);
	if (atoi(choice1) == 1)
	{
		fprintf(fic2, "%s;%s;%s;", product_nameNew, some_product.price, some_product.amount_of_product);
	}
	else if (atoi(choice1) == 2)
	{
		fprintf(fic2, "%s;%s;%s;", some_product.product_name, price, some_product.amount_of_product);
	}
	else
		fprintf(fic2, "%s;%s;%s;", some_product.product_name, some_product.price, amount_of_product);

	c = fgetc(fic);
	while (c != EOF)
	{
		putc(c, fic2);
		c = fgetc(fic);
	}

	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "w");
	fclose(fic);
	fic = fopen("CategoriesAndProducts.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("Product successfully updated\n");
	return manager_menu();
}

// Edit profile of manager
void manager_profile()
{
	FILE* fic = fopen("ManagersInformation.csv", "r+");
	FILE* fic2 = fopen("ManagersInformationTEST.csv", "w+");
	if (fic == NULL)
		exit(1);
	manager data;
	char choice[2];
	char c = fgetc(fic);
	manager new_data;
	char age[4];

	while (c != '\n')
	{
		fputc(c, fic2);
		c = fgetc(fic);
	}
	fputc(c, fic2);

	while (!feof(fic))
	{
		fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.password);
		if (strcmp(current_user, data.user_name) == 0)
		{
			printf("1 - Last Name: %s\n2 - First Name: %s\n3 - User Name: %s\n4 - Phone: %s\n5 - Age: %d\n6 - Password: %s\n\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password);
			printf("If you want to edit your information, please enter 0\n");
			scanf(" %s", choice);

			if (atoi(choice) == 0)
			{
				printf("Which fild do you want to update?\n");
				scanf(" %s", choice);
				if ((check_number(choice) == 0) && atoi(choice) <= 6 && atoi(choice) > 0)
				{
					if (atoi(choice) == 1)
					{
						printf("Enter the updated last name(without characters):\n");
						scanf(" %s", new_data.last_name);
						while (string_check(new_data.last_name) == 1)
						{
							printf("Your last name is not valid, Please try again!\n");
							scanf(" %s", new_data.last_name);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", new_data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password);
					}
					else if (atoi(choice) == 2)
					{
						printf("Enter the updated first name(without characters):\n");
						scanf(" %s", new_data.first_name);
						while (string_check(new_data.first_name) == 1)
						{
							printf("Your last name is not valid, Please try again!\n");
							scanf(" %s", new_data.first_name);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, new_data.first_name, data.user_name, data.phone, data.age, data.password);
					}
					else if (atoi(choice) == 3)
					{
						printf("Enter the updated user name:\n");
						scanf(" %s", new_data.user_name);
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, data.first_name, new_data.user_name, data.phone, data.age, data.password);
					}
					else if (atoi(choice) == 4)
					{
						printf("Enter the updated phone (start with 05):\n");
						scanf(" %s", new_data.phone);
						while (check_phone(new_data.phone) == 1)
						{
							printf("Your phone is not valid, Please try again!\n");
							scanf(" %s", new_data.phone);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, data.first_name, data.user_name, new_data.phone, data.age, data.password);
					}
					else if (atoi(choice) == 5)
					{
						printf("Enter the updated age (25-120):\n");
						scanf(" %s", age);
						while (atoi(age) > 120 || atoi(age) < 25)
						{
							printf("Your age is not valid, Please try again!\n");
							scanf(" %s", age);
						}
						new_data.age = atoi(age);
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, data.first_name, data.user_name, data.phone, new_data.age, data.password);
					}
					else if (atoi(choice) == 6)
					{
						printf("Enter the updated password (must include one capital letter and minimum 6 characters):\n");
						scanf(" %s", new_data.password);
						while (check_password(new_data.password) == 1)
						{
							printf("Your password is not valid, Please try again!\n");
							scanf(" %s", new_data.password);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, new_data.password);
					}
					c = fgetc(fic);
					while (c != EOF)
					{
						fputc(c, fic2);
						c = fgetc(fic);
					}
					break;
				}
			}
			else
				return manager_menu();
		}
		fprintf(fic2, "%s,%s,%s,%s,%d,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password);
	}
	fclose(fic);
	fic = fopen("ManagersInformation.csv", "w");
	fclose(fic);
	fic = fopen("ManagersInformation.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("Information successfully updated\n");
	return manager_menu();
}

// Edit profile of costumer
void costumer_profile(char userName[25])
{
	FILE* fic = fopen("CustomersInformation.csv", "r+");
	FILE* fic2 = fopen("ManagersInformationTEST.csv", "w+");
	if (fic == NULL)
		exit(1);

	customer data;
	customer new_data;
	char choice[2];
	char c = fgetc(fic);
	char age[4];

	while (c != '\n')
	{
		fputc(c, fic2);
		c = fgetc(fic);
	}
	fputc(c, fic2);

	while (!feof(fic))
	{
		fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.city, data.adress, data.password);



		if (strcmp(userName, data.user_name) == 0)
		{
			printf("1 - Last Name: %s\n2 - First Name: %s\n3 - User Name: %s\n4 - Phone: %s\n5 - Age: %d\n6 - City: %s\n7 - Adress: %s\n8 - Password: %s\n\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password);
			printf("If you want to edit your information, please enter 0\n");
			scanf(" %s", choice);

			if (atoi(choice) == 0) //else////////////////////////////////////// 
			{
				printf("Which fild do you want to update?\n");
				scanf(" %s", choice);
				if ((check_number(choice) == 0) && atoi(choice) <= 8 && atoi(choice) > 0)
				{
					if (atoi(choice) == 1)
					{
						printf("Enter the updated last name(without characters):\n");
						scanf(" %s", new_data.last_name);
						while (string_check(new_data.last_name) == 1)
						{
							printf("Your last name is not valid, Please try again!\n");
							scanf(" %s", new_data.last_name);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", new_data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 2)
					{
						printf("Enter the updated first name(without characters):\n");
						scanf(" %s", new_data.first_name);
						while (string_check(new_data.first_name) == 1)
						{
							printf("Your last name is not valid, Please try again!\n");
							scanf(" %s", new_data.first_name);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, new_data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 3)
					{
						printf("Enter the updated user name:\n");
						scanf(" %s", new_data.user_name);
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, new_data.user_name, data.phone, data.age, data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 4)
					{
						printf("Enter the updated phone (start with 05):\n");
						scanf(" %s", new_data.phone);
						while (check_phone(new_data.phone) == 1)
						{
							printf("Your phone is not valid, Please try again!\n");
							scanf(" %s", new_data.phone);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, new_data.phone, data.age, data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 5)
					{
						printf("Enter the updated age (25-120):\n");
						scanf(" %s", age);
						while (atoi(age) > 120 || atoi(age) < 25)
						{
							printf("Your age is not valid, Please try again!\n");
							scanf(" %s", age);
						}
						new_data.age = atoi(age);
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, data.phone, new_data.age, data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 6)
					{
						printf("Enter the updated city (without characters):\n");
						scanf(" %s", new_data.city);
						while (string_check(new_data.city) == 1)
						{
							printf("The city is not valid, Please try again!\n");
							scanf(" %s", new_data.city);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, new_data.city, data.adress, data.password);
					}
					else if (atoi(choice) == 7)
					{
						printf("Enter the updated adress (without characters and minimum one number):\n");
						scanf(" %s", new_data.adress);
						while (check_adress(new_data.adress) == 1)
						{
							printf("Your adress is not valid, Please try again!\n");
							scanf(" %s", new_data.adress);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, new_data.adress, data.password);
					}
					else if (atoi(choice) == 8)
					{
						printf("Enter the updated password (must include one capital letter and minimum 6 characters):\n");
						scanf(" %s", new_data.password);
						while (check_password(new_data.password) == 1)
						{
							printf("Your password is not valid, Please try again!\n");
							scanf(" %s", new_data.password);
						}
						fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, new_data.password);
					}
					c = fgetc(fic);
					while (c != EOF)
					{
						fputc(c, fic2);
						c = fgetc(fic);
					}
					break;
				}
			}
			else
				return customer_menu();
		}
		fprintf(fic2, "%s,%s,%s,%s,%d,%s,%s,%s\n", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password);
	}
	fclose(fic);
	fic = fopen("CustomersInformation.csv", "w");
	fclose(fic);
	fic = fopen("CustomersInformation.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("Information successfully updated\n");
	return customer_menu();
}

// Manager main menu
void manager_menu()
{
	char choice[2];
	printf("-------------------------------------------------------------\nPlease select what do you want to do\n");
	printf("1 - To add an item or category.\n2 - To delete product from catalog.\n3 - To update product details.\n");
	printf("4 - To view the stock.\n5 - To see all order\n6 - To change status of an order\n7 - To view the profile\n");
	printf("-------------------------------------------------------------\n");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 7 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
	{
		return menu_add_category_product();
	}
	if (atoi(choice) == 2)
	{
		return menu_delete();
	}
	if (atoi(choice) == 3)
	{
		return menu_updating_product();
	}
	if (atoi(choice) == 4)
	{
		return menu_view_stock();
	}
	if (atoi(choice) == 5)
	{
		return menu_view_orders_manager();
	}
	if (atoi(choice) == 6)
	{
		return menu_order_status();
	}
	if (atoi(choice) == 7)
	{
		manager_profile();
	}
}


void menu_add_category_product()
{
	char choice[2];
	char choiceC[5];
	int num_category;
	printf("-------------------------------------------------\nSelect the action:\n");
	printf("1 - To add new category.\n2 - To add new product.\n");
	printf("-------------------------------------------------\n");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 2 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
	{
		return add_category();
	}
	else
	{
		num_category = print_all_category();
		printf("Please choose the category\n");
		scanf(" %s", choiceC);
		while ((check_number(choiceC) == 1) || atoi(choiceC) > num_category || atoi(choiceC) < 1)
		{
			printf("The input is invalid, Try again\n");
			scanf(" %s", choiceC);
		}
		return add_product(choiceC);
	}
}


void menu_delete()
{
	char choice1[5];
	char choice2[5];
	int num_category;
	int num_product;
	num_category = print_all_category();
	scanf(" %s", choice1);
	while ((check_number(choice1) == 1) || atoi(choice1) > num_category || atoi(choice1) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice1);
	}
	num_product = view_specific_category(atoi(choice1));
	scanf(" %s", choice2);
	while ((check_number(choice2) == 1) || atoi(choice2) > num_product || atoi(choice2) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice2);
	}
	return delete_product(choice1, choice2);
}


void menu_order_status()
{
	char choice[2];
	printf("1 - To see all the approved orders.\n2 - To see all canceled orders.\n3 - To see all orders that are not updated.\n4 - To update the status of an order.\n\nWhat is your choice? ");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 4 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
		return print_approved_orders();
	else if (atoi(choice) == 2)
		return print_canceled_orders();
	else if (atoi(choice) == 3)
		return print_not_updated_orders();
	else
		return update_status();
}

void menu_view_orders_manager()
{
	char choice[2];
	printf("1 - To search by order number.\n2 - To search by a customer.\n3 - To see all the orders.\n\nWhat your choice? ");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 3 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
		return search_order_by_number();
	else if (atoi(choice) == 2)
		return search_order_by_customer();
	else
	{
		print_all_orders();
		return manager_menu();
	}
}

void menu_view_stock()
{
	char choice[2];
	char choice_cat[5];
	char product_name[25];
	int num_category;
	printf("1 - To see all the products.\n2 - To search for a specific category.\n3 - Searching for a specific product.\n\nWhat your choice? ");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 3 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
		return view_all_stock();
	else if (atoi(choice) == 2)
	{
		printf("Choose category:\n ");
		num_category = print_all_category();
		scanf(" %s", choice_cat);
		while ((check_number(choice_cat) == 1) || atoi(choice_cat) > num_category || atoi(choice_cat) < 1)
		{
			printf("The input is invalid, Try again\n");
			scanf(" %s", choice_cat);
		}
		num_category = view_specific_category(atoi(choice_cat));
		return manager_menu();
	}
	else
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		char product_name[25];
		char c = fgetc(fic);
		product data;
		printf("\nPlease enter the name of the product you want to update (only with capital letters): ");
		scanf(" %[^\n]", product_name);
		while (capital_letters_check(product_name) == 1)
		{
			printf("Your product name is not valid, Please try again: ");
			scanf(" %[^\n]", product_name);
		}
		fseek(fic, 21, SEEK_SET);
		while (!feof(fic))
		{
			while (c != ',')
			{
				c = fgetc(fic);
			}
			c = ' ';
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
				if (strcmp(data.product_name, product_name) == 0)
				{
					break;
				}
				c = fgetc(fic);
			}
			if (strcmp(data.product_name, product_name) == 0)
			{
				break;
			}
		}
		if (strcmp(data.product_name, product_name) != 0)
		{
			printf("\nThe searched product has not been found.");
			return manager_menu();
		}
		return view_specific_product(product_name);
	}
}


void menu_updating_product()
{
	char choice[2];
	printf("1 - Searching for a specific product.\n2 - Print all categories choose.\n\nWhat your choice? ");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 2 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
		return update_product_by_search();
	else
		return choose_product_to_update();
}


void customer_menu()
{

	int num_category;
	int num_product;
	int check;
	char choice[5];
	char choice2[5];
	char d;
	char quantity[5];
	char product[25];
	printf("\n");
	num_category = print_all_category();
	printf("You can do the folowing:\nSelect category to shop from.\nSearch for specific product - Enter S.\nView your profile and update your information - Enter 0.\nView your basket - Enter V.\n");
	scanf(" %s", choice);
	if (strcmp(choice, "S") == 0 || strcmp(choice, "s") == 0)
	{
		printf("Enter name of product you want to add to your basket (capital letter only):\n");
		scanf(" %s", product);
		while (capital_letters_check(product) == 1)
		{
			printf("Your product name is not valid, Please try again\n");
		}
		return search_product_customer(product);
	}
	else if (strcmp(choice, "0") == 0)
	{
		return menu_customer_profile();
	}
	else if (strcmp(choice, "V") == 0 || strcmp(choice, "v") == 0)
	{
		return menu_view_basket();
	}
	else if (atoi(choice) > 0 || atoi(choice) <= num_category)
	{
		num_product = view_specific_category(atoi(choice));
		printf("Select the product you want to add to your basket :\n\tIf you want to sort them by increasing order enter A, or by in descending order enter D.\n");
		scanf(" %s", choice2);
		if (strcmp(choice2, "A") == 0 || strcmp(choice2, "a") == 0)
		{
			sort_A(choice);
			return customer_menu();
		}
		else if (strcmp(choice2, "D") == 0 || strcmp(choice2, "d") == 0)
		{
			sort_D(choice);
			return customer_menu();
		}
		else if (atoi(choice2) > 0 || atoi(choice2) <= num_category)
		{
			printf("What is the quantity you want?\n");
			scanf(" %s", quantity);
			while (check_number(quantity) == 1)
			{
				printf("Your input is not valid, Try again.\n");
				scanf(" %s", quantity);
			}
			add_product_to_basket_from_menu(choice, choice2, quantity);
			return customer_menu();
		}
		else
		{
			printf("Your choice is wrong!\n");
			return customer_menu();
		}

	}
}

/////////////////////////////////////////////////////////////////////////סיימנו
void search_product_customer(char productT[25])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char amount_of_product[5];
	char choice;
	char product_name[25], product_nameNew[25];
	product data;

	fseek(fic, 20, SEEK_SET);
	char c = fgetc(fic), d = ' ';
	while (!feof(fic))
	{
		while (c != ',')
		{
			c = fgetc(fic);
		}
		c = ' ';
		while (c != '\n' && c != EOF)
		{
			fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
			if (strcmp(data.product_name, productT) == 0)
			{
				break;
			}
			c = fgetc(fic);
		}
		if (strcmp(data.product_name, productT) == 0)
		{
			break;
		}
	}
	if (strcmp(data.product_name, productT) != 0)
	{
		printf("\nThe searched product has not been found.");
		return customer_menu();
	}
	printf("Name: %s\nPrice: %s\n", data.product_name, data.price);
	printf("To add the product to the basket enter the amount you want.\n");
	scanf(" %s", amount_of_product);
	while (check_number(amount_of_product) == 1 || atoi(amount_of_product) > atoi(data.amount_of_product))
	{
		printf("\nThe amount is not valid.\nthere is just %s in the stock\n", data.amount_of_product);
		scanf(" %s", amount_of_product);
	}
	FILE* fic2 = fopen("Basket.csv", "r+");
	if (fic2 == NULL)
		exit(1);
	fseek(fic2, 0, SEEK_END);
	fprintf(fic2, "\n%s,%s,%s;", data.product_name, amount_of_product, data.price);
	fclose(fic2);
	fclose(fic);
	printf("The product has been added successfully\n");
	return customer_menu();
}

// Prints menu of customer profile - view and edit        ////////////////////////////////////////////////////סיימנו
void menu_customer_profile()
{
	char choice[2];
	printf("1 - To see your previous orders.\n2 - To view and update your details.\nWhat your choice? ");
	scanf(" %s", choice);
	while ((check_number(choice) == 1) || atoi(choice) > 2 || atoi(choice) < 1)
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
		return print_previous_order_costumer();
	else
		return costumer_profile(current_user);
}

// prints customers previous orders       ////////////////////////////////////////////////////סיימנו
void print_previous_order_costumer()
{
	FILE* fic = fopen("Orders.csv", "r+");
	if (fic == NULL)
		exit(1);

	char nbr_orders[5], customer[25], status[2], product[31];
	int amount, total, i, counter = 1;
	char c = ' ';
	fseek(fic, 59, SEEK_SET);
	while (!feof(fic))
	{
		c = ' ';
		fscanf(fic, "%[^,],%[^,],%[^,],%d,%d,", nbr_orders, status, current_user, &amount, &total);
		if (strcmp(current_user, customer) == 0)
		{
			c = ' ';
			printf("\nOrder's number: %s\nStatus: %s\nAmount: %d\nTotal: %d\nProducts: ", nbr_orders, status, amount, total);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];", product);
				printf("%s; ", product);
				c = fgetc(fic);
			}
			printf("\n");
			c = 'X';
			counter = -1;
		}
		while (c != '\n' && c != EOF)
			c = fgetc(fic);
	}
	if (counter != -1)
		printf("\n You dont have any orders yet.\n");
	fclose(fic);
	return customer_menu();
}


void menu_view_basket()
{
	int num_of_product;
	num_of_product = print_customer_basket();
	char choice[2];
	char product_choice[5];
	printf("1 - To edit your basket.\nB - To buy your basket.\nR - To return to the menu\nWhat your choice? ");
	scanf(" %s", choice);
	while (atoi(choice) != 1 || strcmp(choice, "B") == 0 || strcmp(choice, "b") == 0 || strcmp(choice, "R") == 0 || strcmp(choice, "r") == 0)     ///// or &&
	{
		printf("The input is invalid, Try again\n");
		scanf(" %s", choice);
	}
	if (atoi(choice) == 1)
	{
		printf("Select the number of the product you want to update: \n");
		scanf(" %s", product_choice);
		while (check_number(product_choice) == 1 || atoi(product_choice) > num_of_product || atoi(product_choice) < 1)
		{
			printf("The input is invalid, Try again\n");
			scanf(" %s", choice);
		}
		return edit_customer_basket(atoi(choice));
	}
	else if (strcmp(choice, "B") == 0 || strcmp(choice, "b") == 0)
		return payment();
	else if (strcmp(choice, "R") == 0 || strcmp(choice, "r") == 0)
		return customer_menu();
}


// prints all products in basket //////////////////////////////////// סיימנו
int print_customer_basket()
{
	FILE* fic = fopen("Basket.csv", "r+");
	if (fic == NULL)
		exit(1);
	char product_name[25];
	char quantity[5];
	char price[10];
	int num_product = 0;
	int sum = 0;
	char c = ' ';
	fseek(fic, 2, SEEK_SET);
	while (!feof(fic))
	{
		++num_product;
		fscanf(fic, "%[^,],%[^,],%[^;];", product_name, quantity, price);                           // maybe \n?
		sum += (atoi(price) * atoi(quantity));
		printf("%d - Product: %s\tQuantity: %s\tPrice: %s\n", num_product, product_name, quantity, price);
		c = fgetc(fic);
		if (c == EOF)
			break;
	}
	printf("Total of basket: %d\n", sum);
	fclose(fic);
	return num_product;
}

//////////////////////////////////// סיימנו/////////////////////////////
void edit_customer_basket(int choice)
{
	FILE* fic = fopen("Basket.csv", "r+");
	if (fic == NULL)
		exit(1);
	FILE* fic2 = fopen("OrdersTEST.csv", "w+");
	int counter = 1;
	char c = fgetc(fic);
	char d;
	char quantity[25];
	product data;

	while (c != '\n')
	{
		fputc(c, fic2);
		c = fgetc(fic);
	}
	fputc(c, fic2);
	while (counter != choice)
	{
		fscanf(fic, "%[^,],%[^,],%[^;];\n", data.product_name, data.amount_of_product, data.price);
		fprintf(fic2, "%s,%s,%s;\n", data.product_name, data.amount_of_product, data.price);
		counter++;
	} ///////////////////////////////////////////////////////check stock//////////////////////////////////////
	printf("What is the new quantity you want to update? Press x and then the new amount.\nIf you want to delete this product press x and then 0.\n");
	scanf(" %c", &d);
	scanf(" %s", quantity);
	while (d != 'x' || d != 'X' || check_number(quantity) == 1)
	{
		printf("Your input is not valid, Try again.\n");
		scanf(" %c", &d);
		scanf(" %s", quantity);
	}
	if (atoi(quantity) == 0)
	{
		scanf(fic, "%[^,],%[^,],%[^;];\n", data.product_name, data.amount_of_product, data.price);
	}
	else
	{
		fscanf(fic, "%[^,],%[^,],%[^;];\n", data.product_name, data.amount_of_product, data.price);
		fprintf(fic2, "%s,%s,%s;\n", data.product_name, data.amount_of_product, data.price);
	}
	c = fgetc(fic);
	while (c != EOF)
	{
		fputc(c, fic2);
		c = fgetc(fic);
	}
	fclose(fic);
	fic = fopen("Basket.csv", "w");
	fclose(fic);
	fic = fopen("Basket.csv", "r+");
	fseek(fic2, 0, SEEK_SET);
	c = fgetc(fic2);
	while (!feof(fic2))
	{
		fputc(c, fic);
		c = fgetc(fic2);
	}
	fclose(fic2);
	fclose(fic);
	printf("Quantity successfully updated\n");
	return menu_view_basket();
}

void payment()
{
	char credit_card1[5];
	char credit_card2[5];
	char credit_card3[5];
	char credit_card4[5];
	char month[3];
	char year[5];
	char id[10];
	char cvv[4];

	char day[2];
	char time[2];
	printf("Enter your payment details:\nCredit card number (16 digits):\n");
	scanf(" %s", credit_card1);
	scanf(" %s", credit_card2);
	scanf(" %s", credit_card3);
	scanf(" %s", credit_card4);
	while (check_number(credit_card1) == 1 || check_number(credit_card2) == 1 || check_number(credit_card3) == 1 || check_number(credit_card4) == 1)
	{
		printf("Your credit card number is not valid, Try again.\n");
		scanf(" %s", credit_card1);
		scanf(" %s", credit_card2);
		scanf(" %s", credit_card3);
		scanf(" %s", credit_card4);
	}

	printf("Enter month:\n");
	scanf(" %s", month);
	while (check_number(month) == 1 || atoi(month) > 12 || atoi(month) < 1)
	{
		printf("The month you entered is not valid, Try again.\n");
		scanf(" %s", month);
	}
	printf("Enter year: \n");
	scanf(" %s", year);
	while (check_number(year) == 1 || atoi(month) < 2021)
	{
		printf("The year you entered is not valid, Try again.\n");
		scanf(" %s", month);
	}
	printf("Enter ID (9): \n");
	scanf(" %s", id);
	while (check_ID(id) == 1)
	{
		printf("Your ID number is not correct, Try again.\n");
		scanf(" %s", id);
	}
	printf("Enter CVV (3 digits in the back of the card): \n");
	scanf(" %s", cvv);
	while (check_number(cvv) == 1 || atoi(cvv) != 0)
	{
		printf("Your CVV is not correct, try again.\n");
		scanf(" %s", cvv);
	}
	///////////////////////////////////////////// reduce from stock

	printf("Please choose the time and the day you wat to be delivered:\n1 - SUNDAY, 2 - MONDAY, 3 - TUSEDAY, 4 -WEDNESDAY, 5 - THURSDAY\n");
	scanf(" %s", day);
	while (check_number(day) == 1 || atoi(day) > 5 || atoi(day) < 1)
	{
		printf("Your choice is not correct, try again.\n");
		scanf(" %s", day);
	}
	printf("Choose the time:\n1 - 9:00 - 12:00\n2 - 12:00 - 15:00\n3 - 15:00 - 18:00\n");
	scanf(" %s", time);
	while (check_number(time) == 1 || atoi(time) > 3 || atoi(time) < 1)
	{
		printf("Your choice is not correct, try again.\n");
		scanf(" %s", time);
	}

	printf("Your order is on the way to you, Come shop with us again!\n");
	return customer_menu();
}

void add_product_to_basket_from_menu(char choicecat[5], char choicepro[5], char quantity[5])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c = fgetc(fic), d = ' ';
	int choice2 = atoi(choicecat), choice3 = atoi(choicepro);
	int counter1 = 0, counter2 = 0;
	product data;

	FILE* fic2 = fopen("Basket.csv", "r+");
	while (counter1 != choice2)
	{
		c = fgetc(fic);
		if (c == '\n')
			counter1++;
	}
	while (counter2 != choice3)
	{
		c = fgetc(fic);
		if (c == ',')
			counter2++;
	}
	fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
	if (atoi(quantity) > data.amount_of_product)
	{
		printf("Your input is not valid, Try again.\n");
		return;
	}
	else
	{
		fseek(fic2, 0, SEEK_END);
		fprintf(fic2, "\n%s,%s,%s;", data.product_name, quantity, data.price);
	}

	fclose(fic2);
	fclose(fic);
	printf("\nThe product has been added successfully\n");
	return;
}

int struct_cmp_by_increasing_order(const void* a, const void* b)
{
	product* ia = (struct product*)a;
	product* ib = (struct product*)b;
	return strcmp(ia->price, ib->price);
}

int struct_cmp_by_descending_order(const void* a, const void* b)
{
	product* ia = (struct product*)a;
	product* ib = (struct product*)b;
	return -1 * strcmp(ia->price, ib->price);
}

void print_struct_array(struct product* array, int len)
{
	int counter = 1;
	printf("\n");
	for (int i = 0; i < len; i++)
		printf("%d - %s\nPRICE: %s\nQUANTITY: %s\n\n", counter, array[i].product_name, array[i].price, array[i].amount_of_product);
}

void sort_A(char category[5])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c = ' ', d = ' ';
	int counter1 = 0, counter2 = 0, check;
	char quantity[5];
	char temp[25], choice2[5];
	while (counter1 != atoi(category))
	{
		c = getc(fic);
		if (c == '\n')
			counter1++;
	}
	c = ' ';
	while (c != '\n' && c != EOF)
	{
		c = getc(fic);
		if (c == ',')
			counter2++;
	}
	product* test = (struct product*)malloc(counter2 * sizeof(struct product));
	if (test == NULL)
		return NULL;
	counter1 = 0;
	fseek(fic, 0, SEEK_SET);
	while (counter1 != atoi(category))
	{
		c = getc(fic);
		if (c == '\n')
			counter1++;
	}
	while (c != ',')
		c = fgetc(fic);
	for (int i = 0; i < counter2; i++)
	{
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].product_name, temp);
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].price, temp);
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].amount_of_product, temp);
		c = fgetc(fic);
		if (c == '\n' || c == EOF)
			break;
	}
	qsort(test, counter2, sizeof(struct product), struct_cmp_by_increasing_order);
	print_struct_array(test, counter2);


	printf("Select the product you want to add to your basket :\n");
	scanf(" %s", choice2);
	if (atoi(choice2) > 0 || atoi(choice2) <= atoi(category))
	{ ///////////////////////////////////////////////////////check stock//////////////////////////////////////
		printf("What is the quantity you want? \n");
		scanf(" %s", quantity);
		while (check_number(quantity) == 1 || atoi(quantity) > atoi(test->amount_of_product) || 0 < atoi(test->amount_of_product))
		{
			printf("Your input is not valid, Try again.\n");
			scanf(" %s", quantity);
		}
		FILE* fic2 = fopen("Basket.csv", "r+");
		fseek(fic2, 0, SEEK_END);
		fprintf(fic2, "\n%s;%s;%s,", test[atoi(choice2) - 1].product_name, test[atoi(choice2) - 1].amount_of_product, test[atoi(choice2) - 1].price);
		fclose(fic2);
		fclose(fic);
		printf("\nThe product has been added successfully\n");
	}
	return;/////////////////
}

void sort_D(char category[5])
{
	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	if (fic == NULL)
		exit(1);
	char c = ' ', d = ' ';
	int counter1 = 0, counter2 = 0, check;
	char quantity[5];
	char temp[25], choice2[5];
	while (counter1 != atoi(category))
	{
		c = getc(fic);
		if (c == '\n')
			counter1++;
	}
	c = ' ';
	while (c != '\n' && c != EOF)
	{
		c = getc(fic);
		if (c == ',')
			counter2++;
	}
	product* test = (struct product*)malloc(counter2 * sizeof(struct product));
	if (test == NULL)
		return NULL;
	counter1 = 0;
	fseek(fic, 0, SEEK_SET);
	while (counter1 != atoi(category))
	{
		c = getc(fic);
		if (c == '\n')
			counter1++;
	}
	while (c != ',')
		c = fgetc(fic);
	for (int i = 0; i < counter2; i++)
	{
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].product_name, temp);
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].price, temp);
		fscanf(fic, "%[^;];", temp);
		strcpy(test[i].amount_of_product, temp);
		c = fgetc(fic);
		if (c == '\n' || c == EOF)
			break;
	}
	qsort(test, counter2, sizeof(struct product), struct_cmp_by_descending_order);
	print_struct_array(test, counter2);

	printf("Select the product you want to add to your basket :\n");
	scanf(" %s", choice2);
	if (atoi(choice2) > 0 || atoi(choice2) <= atoi(category))
	{ ///////////////////////////////////////////////////////check stock//////////////////////////////////////
		printf("What is the quantity you want? Press x and then the new amount.\n");
		scanf(" %c", &d);
		scanf(" %s", quantity);
		while (d != 'x' || d != 'X' || check_number(quantity) == 1 || atoi(quantity) > atoi(test->amount_of_product) || 0 < atoi(test->amount_of_product))
		{
			printf("Your input is not valid, Try again.\n");
			scanf(" %c", &d);
			scanf(" %s", quantity);
		}
		FILE* fic2 = fopen("Basket.csv", "r+");
		fseek(fic2, 0, SEEK_END);
		fprintf(fic2, "\n%s;%s;%s,", test[atoi(choice2) - 1].product_name, test[atoi(choice2) - 1].amount_of_product, test[atoi(choice2) - 1].price);
		fclose(fic2);
		fclose(fic);
		printf("\nThe product has been added successfully\n");
	}
	return;
}