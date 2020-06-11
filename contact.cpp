#include "contact.h"

Person Contact::str2person(char* line)
{
  Person cont;
  char *token;
  char temp[64];
  
  int i = 0;
  token = strtok(line, ";");
  while(token != NULL) {
    strcpy(temp, trim(token));
    
    switch(i) {
      case 0: strcpy(cont.name, temp); break;
      case 1: cont.dob = str2date(temp); break;
      case 2: strcpy(cont.email, temp); break;
      case 3: strcpy(cont.phone, temp); break;
    }
    i++;
    token = strtok(NULL, ";");
  }
  return cont;
}

Date Contact::str2date(char* str)
{
  Date date;
  char temp[10];
  
  strncpy(temp, str, 4);
  temp[4] = 0;
  date.year = atoi(temp);
  
  strncpy(temp, str+4, 2);
  temp[2] = 0;
  date.month = atoi(temp);
  
  strncpy(temp, str+6, 2);
  temp[2] = 0;
  date.day = atoi(temp);
  
  return date;
}

void Contact::load_contact(string file_name) {
  Contact* c;
  c = new Contact(MAX_NUM);

  char fname_l[MAX_NUM];
  strcpy(fname_l, file_name.c_str());
  
  char *line = NULL;
  size_t len;
  
  FILE *fp_l;
  fp_l = fopen(fname_l, "r");
  
  int cont_i = 0;
  while (getline(&line, &len, fp_l) != EOF){
    //persons[cont_i++] = str2person(line);
    insert_contact(line);
  }
  free(line);
  fclose(fp_l);
}

void Contact::save_contact(string file_name) {
  Person c;
  
  if(strcmp(persons[0].name, "\0") == 0)
    cout << "Load or insert the contacts first." << endl;
  else {
    char fname_s[MAX_NUM];
    strcpy(fname_s, file_name.c_str());
  
    FILE *fp_s;
    fp_s = fopen(fname_s, "w");
  
    for(int i = 0; i < MAX_NUM; i++) {
      c = persons[i];
      if(strcmp(c.name, "\0") != 0)
        fprintf(fp_s, "%s; %4d%02d%02d; %s; %s\n", c.name, c.dob.year, c.dob.month, c.dob.day, c.email, c.phone);
    }
    cout << "Contacts data is saved into " << file_name << endl;
    fclose(fp_s);
  }
}

void Contact::insert_contact(string data_to_insert)
{
  char new_contact[MAX_NUM];
  strcpy(new_contact, data_to_insert.c_str());
  
  int con = 1;
  int last = 0;
  
  while(con) {
    if(strcmp(persons[last].name, "\0") == 0) {
      persons[last] = str2person(new_contact);
      cout << "New contact inserted!" << endl;
      con = 0;
    }
    else
      last++;
  }
}

void Contact::delete_contact(string str_delete)
{
  int d = search(str_delete);
  
  if(d >= 0) {
    for(int i = d; i < MAX_NUM; i++) {
      memcpy(&persons[i], &persons[i+1], sizeof(Person));
    }
    cout << ">> " << str_delete << " was deleted!" << endl;
  }
}

void Contact::retrieve_contact(string str_retrieve)
{
  int r = search(str_retrieve);
  
  if(r >= 0)
    printf("%s; %4d%02d%02d; %s; %s\n", persons[r].name, persons[r].dob.year, persons[r].dob.month,
      persons[r].dob.day, persons[r].email, persons[r].phone);
}

int Contact::search(string str_search)
{
  char search[MAX_NUM];
  strcpy(search, str_search.c_str());
  int found = -1;
  
  for(int index_found = 0; index_found < MAX_NUM; index_found++) {
    if(strcmp(persons[index_found].name, search) == 0 || strcmp(persons[index_found].email, search) == 0) {
      found = index_found;
      break;
    }
  }
  
  if(found >= 0) {
    return found;
  }
  else {
    cout << "There is no " << str_search << " in contacts.." << endl;
    return found;
  }
}

void Contact::print()
{
  Person c;
  
  if(strcmp(persons[0].name, "\0") == 0)
    cout << "Load or insert the contacts first." << endl;
  else {
    for(int i = 0; i < MAX_NUM; i++) {
      c = persons[i];
     if(strcmp(c.name, "\0") != 0)
        printf("%s; %4d%02d%02d; %s; %s\n", c.name, c.dob.year, c.dob.month, c.dob.day, c.email, c.phone);
    }
  }
}

char* Contact::trim(char *s)
{
  char *ptr;
  
  if(!s) return NULL;
  
  while(isspace(*s)) s++;
  
  for(ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
  *(ptr+1) = '\0';
  
  return s;
}