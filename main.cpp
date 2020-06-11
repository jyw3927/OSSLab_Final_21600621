#include "contact.h"

void printmenu();
void loading(Contact *contacts);
void saving(Contact *contacts);
void inserting(Contact *contacts);
void deleting(Contact *contacts);
void retrieving(Contact *contacts);
void sorting(Contact *contacts);

int main() {
  printmenu();
  
  Contact* contacts;
  contacts = new Contact(MAX_NUM);
  
  string input;
  char todo;
  int repeat = 1;
  
  while(repeat) {
    cout << "\n>> What you want to do:";
    cin >> todo;
    //input.charAt(0)
    todo = tolower(todo);
    
    if(todo == 'l') {
      loading(contacts);
    }
    else if(todo == 's') {
      saving(contacts);
    }
    else if(todo == 'i') {
      inserting(contacts);
    }
    else if(todo == 'd') {
      deleting(contacts);
    }
    else if(todo == 'r') {
      retrieving(contacts);
    }
    else if(todo == 'a') {
      
    }
    else if(todo == 'p') {
      contacts->print();
    }
    else if(todo == 'q') {
      cout << "Goodbye!" << endl;
      repeat = 0;
    }
    else {
      cout << ">> You entered wrong expression.\n"
        << ">> Please enter one of the follwing character: (L, S, I, D, R, A, P, Q)\n";
    }
  }
  return 0;
}

void printmenu()
{
  cout << "=======================================================\n"
    << "=========Welcome to the contact application!!==========\n"
    << "=======================================================\n"
    << "*** Please enter a character to choose a operation: ***\n" << endl
    << "\tL : Load contacts from a file\n" << "\tS : Save contacts into a file\n"
    << "\tI : Add a new person into the contacts\n" << "\tD : Delete a person from the contacts\n"
    << "\tR : Search a person\n" << "\tA : Sort the contacts\n" 
    << "\tP : Print out the contacts\n"
    << "\tQ : Quit the program\n";
}

void loading(Contact *contacts)
{
  string filename_load;

  cout << ">> Please enter the file name of contact data:";
  cin >> filename_load;

  contacts->load_contact(filename_load);
  
  cout << ">> Contact data loaded from the file!" << endl;
}

void saving(Contact *contacts)
{
  string filename_save;
  
  cout << ">> Please enter the file name to save the contacts:";
  cin >> filename_save;
  
  contacts->save_contact(filename_save);
}

void inserting(Contact *contacts)
{
  string new_data;
  
  cout << ">> Format: \"Name; Date; E-mail; Phone number\"\n"
  << ">> Please enter the new data:";
  
  cin.ignore(MAX_NUM,'\n');
  getline(cin, new_data);
  
  contacts->insert_contact(new_data);
}

void deleting(Contact *contacts)
{
  string str_del;
  
  cout << ">> Please enter the name or email of person who you want to delete:";
  
  cin.ignore(MAX_NUM,'\n');
  getline(cin, str_del);
  
  contacts->delete_contact(str_del);
}

void retrieving(Contact *contacts)
{
  string str_ret;
  
  cout << ">> Please enter the name or email of person who you want to retrieve:";
  
  cin.ignore(MAX_NUM,'\n');
  getline(cin, str_ret);
  
  contacts->retrieve_contact(str_ret);
}

void sorting()
{
  
}
