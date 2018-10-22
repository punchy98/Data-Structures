#include <iostream>
#include <iomanip>  // for setw()
using namespace std;

#include <iostream>

using namespace std;

/*******************************************
  Author  :  
  Program : Memory Manager
  Due Date: 
  Course  : CSC 300 Data Structures - Spring 2017 - DSU
  Instr   : Krebsbach
********************************************
*/

// GLOBAL DATA STRUCTURES =======================
typedef struct FREE_NODE * FREEPTR;
typedef struct ALLOCNODE * ALLOCPTR;

struct FREE_NODE  // FREE LIST NODES
{
  int start_byte;
  int end_byte;
  int size;
  
  FREEPTR next;
};
struct ALLOCNODE // ALLOCTADED LIST NODES
{
  int start_byte;
  int end_byte;
  int size;
  int id;
  
  ALLOCPTR next;
};
// ======   GLOBAL DATA =========================
FREEPTR  freelist = NULL;  // the FREE link list
ALLOCPTR alloclist = NULL; // the ALLOCATED link list
int total_memory_managed = 0; // the amount of memory managed

//======   PROTOTYPES ===========================
//--- test only ---
void dump_freelist(void);
void dump_alloclist(void);
//--- utility ---

//--- interface ---
void init_memory_manager(const int amount);
int allocate_memory(const int job, const int amount);
void release_memory(const int job);
int total_free(void);
int total_allocated(void);
int largest_free(void);
int job_allocated(const int job);
void report_memory(void);
void report_jobs(void);

//======= TESTING ONLY FUNCTIONS ====================
void dump_freelist(void)
{ FREEPTR tmp = freelist; // temp pointer to list
  cout << "==================" << endl;
  cout << "  FREE LIST DUMP  " << endl;
  cout << "==================" << endl;
  while (tmp !=NULL)
  {
    cout << tmp->start_byte << " : ";
	cout << tmp->end_byte << " : ";
	cout << tmp->size << endl;
	tmp = tmp->next; //move pointer to next node (or NULL)
  }
}
//----------------------
void dump_alloclist(void)
{ ALLOCPTR tmp = alloclist; // temp pointer to list
  cout << "========================" << endl;
  cout << "  ALLOCATED LIST DUMP  " << endl;
  cout << "========================" << endl;
  while (tmp !=NULL)
  {
    cout << tmp->start_byte << " : ";
	cout << tmp->end_byte << " : ";
	cout << tmp->size << " : ";
	cout << tmp->id << endl;
	tmp = tmp->next; //move pointer to next node (or NULL)
  }
}

//======= UTILITY FUNCTIONS ====================


//======= INTERFACE FUNCTIONS ==================
void init_memory_manager(const int amount)
{
  total_memory_managed = amount;
  // set up the freelist linked list
  freelist = new FREE_NODE;
  freelist -> size = amount;
  freelist -> start_byte = 0;
  freelist -> end_byte = amount -1;
  freelist -> next = NULL;
  // set up the alloclist linked list
  alloclist = NULL;
}
//----------------------
int allocate_memory(const int job, const int amount)
{
   FREEPTR tmpfree = NULL;
   ALLOCPTR tmpalloc = NULL;

  if  (amount <= 0)
    return 0;
  if (amount > total_memory_managed)
    return 0;
  //if (largest_free() < amount)
  //  return 0;
  //There is a node large enough! 

  tmpalloc = new ALLOCNODE;
  tmpalloc->next = NULL;

  tmpfree = freelist;

  while (tmpfree != NULL)
  {

    if (tmpfree -> size >= amount)
    {
      //fill up the alloc node
      tmpalloc -> end_byte = tmpfree -> end_byte;
      tmpalloc -> start_byte = tmpfree -> end_byte - amount + 1;
      tmpalloc -> size = amount;
      tmpalloc -> id = job;

      //update freenode
      tmpfree -> end_byte = tmpfree -> end_byte - amount;
      tmpfree -> size = tmpfree -> size - amount;
 

      break;


    }

    tmpfree = tmpfree->next;
  }

    //remove_empty_freenodes()

  return amount;




              // return amount of memory allocated
 // return 0;  // return 0 if not able to allocate
}
//----------------------
void release_memory(const int job)
{
   // STUB
}
//----------------------
int total_free(void)
{
  // STUB
  
  return 0; // return amount of free memory
}
//-----------------------
int total_allocated(void)
{
   // STUB
   
   return 0; //return amount of allocated memory
};
//----------------------
int largest_free(void)
{
  // STUB
  return 0;
}
//----------------------
int job_allocated(const int job)
{
  //STUB
  return 0; // return amount of allocated memory
}
//----------------------
void report_memory(void)
{
   // STUB
}
//----------------------
void report_jobs(void)
{
    // STUB
}
//==========  MAIN =============================
int main(void)
{
   init_memory_manager(500);

   dump_freelist();
   dump_alloclist();

   return 0;
}














