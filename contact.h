#ifndef __CONTACT_H__
#define __CONTACT_H__
#include <iostream>
#include <string.h>
#include <string>
#include <memory.h>
#include "error.h"


using namespace std;

#define MAX_NUM 1000

typedef struct {
  char name[64];
  char email[64];
  char phone[16];
} Person;

class Contact {
  private:
    Person* persons;
    int total_num;
    
    Person str2person(char*);
    
  public:
    Contact(int size) {
      total_num = 0;
      persons = new Person[size];
      memset(persons, 0, size);
    }
    ~Contact() {delete persons;}
    
    void load_contact(string);
    void save_contact(string);
    void insert_contact(string);
    void delete_contact(string);
    void retrieve_contact(string);
    void sort_contact();
    int search(string);
    void print();
    char* trim(char*);
};

#endif
