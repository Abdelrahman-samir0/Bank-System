#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include"STD_TYPE.h"
#include"bank_functions.h"

void bank_win(void)
{
	printf("\t\t\t**********HELLO TO IMT BANK**********\n");
	u16 choice ;
	printf("1- ADMIN \n2- CLIENT\n3- Exit the system\n\n\n");
	printf("Choice:");
	scanf("%u",&choice);
	switch(choice)
	{
		case 1 :
		Admin_log_or_cre();
		break;
		case 2 :
		client_log_in();
		break;
		case 3 : 
		printf("Exit the system");
		break;
	}
}	 

void Admin_log_or_cre(void)
{
	u32 ch;
	printf("****************************************************\n");
	printf("1- Log in \n2- create admin account\n");
	printf("choice:");
	scanf("%u",&ch);
	switch (ch)
	{
		case 1 : Admin_log_in();
		         break;
		 
		case 2 : create_admin_acc();
		         break ; 
				 
		default: printf("invalid choice !");
		         break;
	}
}

admin *head_ad = NULL; 
u32 admin_num = 0;

void create_admin_acc(void)
{
    admin *new_admin = (admin *)malloc(sizeof(admin));
    if (new_admin == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("First character must be uppercase, and don't use spaces in the username.\n"); 
    printf("ENTER USERNAME OF THE NEW ADMIN: ");
    fflush(stdin);
    if (fgets(new_admin->username, sizeof(new_admin->username), stdin) == NULL) 
	{
        printf("Error reading username.\n");
        free(new_admin);
        return;
    } 
    new_admin->username[strcspn(new_admin->username, "\n")] = '\0';
    
    if (!isupper(new_admin->username[0])) 
	{
        printf("Username should start with an uppercase letter.\n");
        free(new_admin);
		create_admin_acc();   
    }
    for (size_t i = 0; new_admin->username[i]; i++) {
        if (new_admin->username[i] == ' ') {
            printf("Username should not contain spaces.\n");
            free(new_admin);
     		create_admin_acc();
        }
    }
    new_admin->ad_pass = rand() % (9999 - 1000 + 1) + 1000;
    new_admin->next = NULL;

    if (head_ad == NULL) {
        head_ad = new_admin;
    } else {
        admin *last = head_ad;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_admin;
    }
    printf("Admin account added successfully!\n");
    printf("Your password: %u\n", new_admin->ad_pass); 
    admin_num++;
    Admin_log_or_cre();
}

void Admin_log_in()
{
    char username[100];
    u32 password;
    printf("Admin Login\n");
    printf("Enter Username: ");
    fflush(stdin);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    admin *current = head_ad;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            int attempts = 3;
            while (attempts > 0)
            {
                printf("Enter Password (Attempts left: %d): ", attempts);
                scanf("%u", &password);

                if (password == current->ad_pass)
                {
                    printf("Admin logged in successfully!\n");
					admin_win();
                    return; 
                }
                else
                {
                    attempts--;
                    printf("Invalid password. ");
                    if (attempts > 0)
                    {
                        printf("Try again.\n");
                    }
                    else
                    {
                        printf("No attempts left. Admin locked out.\n");
                        return; 
                    }
                }
            }
        }
        current = current->next;
    }
    printf("Admin not found.\n");
}
//admin window
void admin_win(void)
{
	u16 ch ;
 	printf("1- Create New Account \n2- Open Exciting Account \n3- Bank window\n");
    printf("choice:");
    scanf("%u",&ch);
	switch (ch)
	{
		case 1: 
		create_new_acc();
        break;
		
		case 2:
		open_exciting_acc();
		break;
		
		case 3:
		bank_win();
		break;		
	}	
}
// new acc
node *head = NULL; // Initialize head pointer to NULL

u32 global_u32ListLength = 0;

void create_new_acc(void)
{	
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) 
	{
        printf("Memory allocation failed.\n");
        return;
    }
	//Name
    printf("NOTE : full nume consists of 4 names ,,, first character must be uppercase\n");
    printf("ENTER FULL NAME OF CLIENT: ");
	fflush(stdin);
    fgets(new_node->full_name, sizeof(new_node->full_name), stdin);
    new_node->full_name[strcspn(new_node->full_name, "\n")] = '\0';
    u16 space_count_FL = 0;
    u16 name_starts_upper_FL = 1; 
    for (u16 i = 0; new_node->full_name[i] != '\0'; i++) 
	{
        if (new_node->full_name[i] == ' ')  
		{
            space_count_FL++;
            name_starts_upper_FL = 1;
        }
		else if (name_starts_upper_FL) 
		{
            if (!isupper(new_node->full_name[i])) 
			{
                printf("names should start with uppercase characters!\n");
                free(new_node);
				create_new_acc();
                
            }
            name_starts_upper_FL = 0; 
        }
    }

    if (space_count_FL < 3) 
	{
        printf("full name must be 4 names!\n");
        free(new_node);
		create_new_acc();
        return;
    }
    // Address
	 u16 attempts_AD = 2;

    while (attempts_AD > 0) 
		{
			printf("ENTER FULL ADDRESS OF CLIENT: ");
			fflush(stdin);
			fgets(new_node->full_address, sizeof(new_node->full_address), stdin);
			new_node->full_address[strcspn(new_node->full_address, "\n")] = '\0';
			u16 space_count_AD = 0;
			for (u16 i = 0; new_node->full_address[i] != '\0'; i++) 
			{
				if (new_node->full_address[i] == ' ') 
				{
                space_count_AD++;
				}
			}
			if (space_count_AD >= 2)
			{
				break; 
			}	 
			else 
			{
				printf("The full address must contain at least 2 spaces!\n");
				attempts_AD--;

				if (attempts_AD == 0) 
				{
					printf("No more attempts left. Exiting...\n");
					free(new_node);
					create_new_acc();
					return ;
				}
			}
		}
    // Age
    printf("ENTER AGE OF CLIENT: ");
    scanf("%u", &new_node->Age);
    //National id
	printf("ENTER NATIONAL ID OF CLIENT (exactly 14 digits): ");
    
    u8 attempts = 2;
    while (attempts > 0) 
	{
        scanf("%lld", &new_node->National_ID);
                                                                       
        if (new_node->National_ID<9999999999999||new_node->National_ID>99999999999999) 
		{
            printf("National ID must be exactly 14 digits.\n");
            attempts--;
        } 
		else 
		{
            break;
        }
        if (attempts > 0) 
		{
            printf("Please try again:");
        }
		else 
		{
            printf("No more attempts left. Exiting...\n");
            free(new_node);      
      		admin_win();
			return;
        } 
    }	
    if (new_node->Age < 21) 
	{
   
	printf("NOTE : guardian nume consists of 4 names ,,, first character must be uppercase\n");
    printf("ENTER GUARDIAN FULL NAME OF CLIENT: ");
	fflush(stdin);
    fgets(new_node->Guardian, sizeof(new_node->Guardian), stdin);
    new_node->Guardian[strcspn(new_node->Guardian, "\n")] = '\0';
    u16 space_count = 0;
    u16 name_starts_upper = 1; 
    for (u16 i = 0; new_node->Guardian[i] != '\0'; i++) 
	{
        if (new_node->Guardian[i] == ' ')  
		{
            space_count++;
            name_starts_upper = 1;
        }
		else if (name_starts_upper) 
		{
            if (!isupper(new_node->Guardian[i])) 
			{
                printf("names should start with uppercase characters!\n");
                free(new_node);
				create_new_acc();
                
            }
            name_starts_upper = 0; 
        }
    }

    if (space_count < 3) 
	{
        printf("guardian full name must be 4 names!\n");
        free(new_node);
		admin_win();
        return;
    }
        
    printf("ENTER GUARDIAN NATIONAL ID: ");     
	u8 attempts = 2;
	while (attempts > 0) 
	{
        scanf("%lld", &new_node->Guardian_ID);
                                                                       
        if (new_node->Guardian_ID<9999999999999||new_node->Guardian_ID>99999999999999) 
		{
            printf("Guardian National ID must be exactly 14 digits.\n");
            attempts--;
        } 
		else 
		{
            break;
        }
        if (attempts > 0) 
		{
            printf("Please try again:");
        }
		else 
		{
            printf("No more attempts left. Exiting...\n");
            free(new_node);      
      		admin_win();
			return;
        } 
    }	
    }
    printf("ENTER BALANCE OF THE CLIENT: ");
    scanf("%f", &new_node->balance);
    new_node->Bank_ID = (rand() %9000000000)+10000000000;
    new_node->cl_pass = (rand() % 9000) + 1000;
 
    new_node->next = NULL;
    strcpy(new_node->ACC_status, "active"); 

    if (head == NULL) 
	{
        head = new_node;
    }
	else 
	{
        node *last = head;
        while (last->next != NULL)
		{
            last = last->next;
        }
        last->next = new_node;
    }
	printf("\n\n****************************************************\n\n");
	printf("account added successfully! \n");
	printf("Bank ID: %lld\n", new_node->Bank_ID);
	printf("your password: %u\n", new_node->cl_pass);
    printf("\n\n****************************************************\n\n");

    global_u32ListLength++;
	admin_win();
	
}
// opening exciting acc for admin  
void open_exciting_acc(void) 
{
    printf("\n\n****************************************************\n\n");

    if (global_u32ListLength != 0) 
	{
        u16 attempts_left = 3;
        u64 bankid;
        while (attempts_left > 0) 
		{
            printf("ENTER BANK ID: ");
            scanf("%lld", &bankid);

            node *current = head;
            while (current != NULL) {
                if (current->Bank_ID == bankid ) 
				{   
			        printf("Bank ID :%u \n",current->Bank_ID);
                    printf("Full Name: %s \n", current->full_name);
                    printf("Balance: %.2f\n", current->balance);
                    printf("Status: %s\n", current->ACC_status);
                    printf("\n****************************************************\n\n");
					exciting_acc(current);
                }
                current = current->next;
            }

            attempts_left--;
            if (attempts_left > 0) 
			{
                printf("Invalid BANK ID.\n", attempts_left);
            }
			else 
			{
                printf("Maximum login attempts reached.\n");
            }
        }
    } 
	else 
	{
        printf("List is Empty\n");
    }

    printf("\n****************************************************\n\n");
}   

void exciting_acc(node *current)
{
	printf("1- Make Transaction \n2- Change Account Status \n3- Get Cash \n4- Deposit in Account \n5- Return to main menu\n");
    u8 ch_op;
    printf("Choice: ");
    scanf("%d", &ch_op);
    switch (ch_op)
	{
		case 1:
		make_transaction(current);
		exciting_acc(current);
		break;
		case 2:
		change_acc_status(current);
		exciting_acc(current);
		break;
		case 3:
		get_cash(current);
		exciting_acc(current);
		break;
		case 4:
		deposit_in_acc(current);
		exciting_acc(current);
		break;
		case 5:
		admin_win();
		break;
		default:
		printf("INVALID CHOICE");
		bank_win();
    }

}
// find the receiver acc
node* find_receiver_by_id(u64 rec_id) 
{
    node *current = head;
 
    while (current != NULL) 
	{
        if (current->Bank_ID == rec_id)
		{
            return current; 
        }
        current = current->next;
    }
   
   return NULL; 

}
//make transaction for admin
void make_transaction(node *sender) 
{   
    if (strcmp(sender->ACC_status, "active") != 0)
	{
        printf("The account is not active. Process cannot be performed.\n");
        return;
    }
    u64 rec_id;
    u32 TR_mon;
    u16 ch;
    printf("Enter the ID of the account that will receive the money: ");
    scanf("%lld", &rec_id);

    node *receiver = find_receiver_by_id(rec_id);

    if (receiver == NULL) 
	{
        printf("Receiver account not found.\n");
       return;
    }

	if (strcmp(receiver->ACC_status, "active") != 0)
	{
        printf("Receiver's account is not active. Transaction cannot be performed.\n");
		return;
    }
    else 
	{
       printf("your balance now is %.2f\n",sender->balance);
       printf("Enter the amount of money to be transferred: ");
       scanf("%u", &TR_mon);

       if (sender->balance >= TR_mon)
	   {
           sender->balance -= TR_mon;
           receiver->balance += TR_mon; 
           printf("Transaction successful.\n");
		   printf("your balance now is : %.2f \n",sender->balance);
		   printf("\n****************************************************\n\n");
       }
	   else 
       {
           printf("you don't have enough balance to do this transaction.\n");
		   printf("\n****************************************************\n\n");
       }
    
    }
}
// change account status for admin
void change_acc_status(node *account) 
{
    u16 choice;
    printf("Enter the new account status:\n");
    printf("1 - Active\n");
    printf("2 - Restricted\n");
    printf("3 - Closed\n\n\n");
    printf("choise:");
    scanf("%d", &choice);

    switch (choice)
	{
        case 1:
            strcpy(account->ACC_status, "active");
            printf("Account status changed to active.\n");
			exciting_acc(account);
            break;
        case 2:
            strcpy(account->ACC_status, "restricted");
            printf("Account status changed to restricted.\n");
			exciting_acc(account);
            break;
        case 3:
            strcpy(account->ACC_status, "closed");
            printf("Account status changed to closed.\n");
            exciting_acc(account);
			break;
        default:
            printf("Invalid choice. Account status remains unchanged.\n");
            exciting_acc(account);
			break;
    }	
	printf("\n****************************************************\n\n");
}
//get cash for admin
void get_cash(node *account)
{
	if (strcmp(account->ACC_status, "active") != 0)
	{
        printf("The account is not active. Transaction cannot be performed.\n");
        return;
    }
    else 
	{
     	f32 cash ;
	    printf("your balance now is : %.2f \n",account->balance);
	    printf("Enter amount of money to get cash :");
	    scanf("%f",&cash);
	    if (account->balance > cash)
	    {
		    printf("successfull operation !\n");
		    account->balance -= cash ; 
	     	printf("your balance now is : %.2f \n", account->balance);
			printf("\n****************************************************\n\n");
	    }
    	else
	    {
		    printf("You don't have enough balance to get this amount of money. \n");
			printf("\n****************************************************\n\n");
	    }	
    } 
}
//deposit for admin 
void deposit_in_acc(node *account)
{
	if (strcmp(account->ACC_status, "active") != 0)
	{
        printf("The account is not active. Transaction cannot be performed.\n");
        return;
    }
	else
	{
	    f32 deposit ;
	    printf("your balance now is : %.2f \n",account->balance);
	    printf("Enter amount of money to deposit in your account :");
	    scanf("%f",&deposit);
	    account->balance += deposit ; 
	    printf("your balance now is : %.2f \n", account->balance);
        printf("\n****************************************************\n\n");  
	}
}
//client log in
void client_log_in(void) 
{
    printf("\n\n****************************************************\n\n");

    if (global_u32ListLength != 0) 
	{
        u64 bankID;
        u32 password;
        u16 attempts_left = 3;

        while (attempts_left > 0) 
		{
            printf("Enter your Bank ID: ");
            scanf("%lld", &bankID);
            printf("Enter your Password: ");
            scanf("%u", &password);

            node *current = head;
            while (current != NULL) 
			{
                if (current->Bank_ID == bankID && current->cl_pass == password) 
				{
                 printf ("CLIENT LOGGED IN SUCCESSFULLY!\n");
                 client_win(current);
                 return;				 
                }
            
                current = current->next;
            }

            attempts_left--;
            if (attempts_left > 0) 
			{
                printf("Invalid Bank ID or Password. %d attempts left.\n", attempts_left);
            }
			else 
			{
                printf("Maximum login attempts reached. Your account is locked.\n");
            }
        }
	}
	else 
	{
        printf("List is Empty\n");
    }

}
//client window
void client_win(node *account)
{
	printf ("Welcome In Client Window\n");
	 printf("Full Name: %s \n", account->full_name);
                    printf("Balance: %.2f\n", account->balance);
                    printf("Status: %s\n", account->ACC_status);
                    printf("\n****************************************************\n\n");

                    printf("1- Make Transaction \n2- Get Cash \n3- Deposit in Account \n4- Change your password\n5- Return to Bank window\n");
                    u16 ch_op;
                    printf("Choice: ");
                    scanf("%d", &ch_op);

                    switch (ch_op) 
					{
                        case 1:
                            make_transaction(account);
							client_win(account);
                            break;

                        case 2:
                            get_cash(account);
				     		client_win(account);
                            break;

                        case 3:
                            deposit_in_acc(account);
                            client_win(account);

                            break;

                        case 4:
                            change_your_password(account);
							client_win(account);
                            break;

                        case 5:
                            bank_win();
                            break;
						default:
						    printf("INVALID CHOICE");
							bank_win();
                    }
}
//chaning client password
void change_your_password(node *current) 
{
    u64 pass;
    u64 new_pass;
    
    if (strcmp(current->ACC_status, "active") != 0) 
	{
        printf("Account is not active. Changing password cannot be performed.\n");
    } 
	else 
	{
        printf("Please enter your current password: ");
        scanf("%llu", &pass);
        
        if (pass == current->cl_pass) 
		{
            printf("Enter your new password: ");
            scanf("%llu", &new_pass);
            
            if (new_pass >= 1000 && new_pass <= 9999) 
			{
                current->cl_pass = new_pass;
                printf("Password changed successfully!\n");
				printf("****************************************************\n\n");
				client_log_in();
            }
			else 
			{
                printf("Password should be 4 digits.\n");
                change_your_password(current);
            }
        } 
		else 
		{
            printf("Wrong password!\n");
			printf("****************************************************\n\n");
        }
    }
}

