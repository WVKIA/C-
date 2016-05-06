#ifndef __COSTMER_H__
#define __COSTMER_H__

struct costomer
{
    char id[20];
    char name[20];
    long phone;

};
struct id_node
{
    char id[20];
    long offset;
    struct id_node * next;
};
struct phone_node
{
    long phone;
    long offset;
    struct phone_node *next;
};
struct hash_node
{
    struct id_node * pid[19];

};

struct node
{
    long offset;
    struct node *next;
};
struct stack
{
    struct node * head;
    int (*push)(struct stack *,long );
    long (*pop)(struct stack *);
    int (*empty)(struct stack *);
    void (*clear)(struct stack *);
};

struct phone_hash
{
    struct phone_node * phone[19];
};
int init_stack(struct stack *);

int find_can_insert_offset(struct node *);

void init_hash_node(struct hash_node *);
struct hash_node* add_hash_node(struct id_node *,struct hash_node *);
int add_costomer(struct costomer*,FILE *,struct hash_node *,struct phone_hash*,struct stack *);
int find_id_from_hash(char *,struct hash_node *);

void show_one_chain(FILE *,struct hash_node *,int );
void show_all_chain(FILE *,struct hash_node *);
void showone(struct costomer *);
int find_offset_by_id(char *,struct hash_node *);
void show_all(FILE *);

void printf_offset_to_costomer(FILE *fp,long n);
void printf_list(FILE *fp,struct hash_node *);
void printf_phone_list(FILE * ,struct phone_hash*);
void read_hash(FILE * fp_hash,struct hash_node  *pid);
void save_hash(FILE * fp_hash,struct hash_node * pid);


void init_del_node(struct node *);
long del_hash_node(char *, struct hash_node *);
int add_del_node(struct node *,int );
void save_del_node(FILE *, struct stack *);
void  read_del_node(FILE *, struct stack *);
void del_phone_node_in_phone_hash(long phone,long offset,struct phone_hash * pphone);


void show_all_chain(FILE *, struct hash_node *);
void show_one_chain(FILE *, struct hash_node *,int );
struct stack* find_by_phone(long,struct phone_hash *,struct stack*);
//struct phone_node * del_by_phone(struct phone_hash *,long,struct phone_node *);
int phone_hash_translate(long);
void init_phone_hash(struct phone_hash *);
struct phone_hash * add_phone_node(struct phone_node *, struct phone_hash *);

void read_phone_hash(FILE *,struct phone_hash *);
void save_phone_hash(FILE * , struct phone_hash *);


int destroy_id_hash(struct hash_node *);
int destroy_phone_hash(struct phone_hash*);
#endif









