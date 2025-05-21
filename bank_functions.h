#ifndef _bank_FUNCTIONS_H_
#define _bank_FUNCTIONS_H_

typedef struct NODE_t node;

struct NODE_t
{
    char full_name [50];
	char full_address[200];
	u64 National_ID ;
	u16 Age;
	u64 Bank_ID;
	u8 Guardian [50];
	u64 Guardian_ID ;
	char ACC_status [20];
	f32 balance ;
	u32 cl_pass;
	
    node *next;
};

typedef struct admin_t admin;

struct admin_t 
{
	u8 username [20] ;
	u32 ad_pass;
	admin *next;
};

void bank_win(void);
void Admin_log_or_cre(void);
void create_admin_acc(void);
void Admin_log_in(void);
void admin_win(void);
void create_new_acc(void);
void open_exciting_acc(void);
void exciting_acc(node *current);
void make_transaction(node *sender);
void change_acc_status(node *account);
void deposit_in_acc(node *account);
void get_cash(node *account);
void client_log_in(void); 
void change_your_password(node *current);
void client_win(node *account);






#endif