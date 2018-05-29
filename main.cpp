#include <iostream>
#include <list>
using namespace std;

// number of buckets in hash table
#define MAX 20


// employee class
class Employee
{
    
    // public visibility of id (which is the key), and the next employee linked afterwards
public:
    int id;
    Employee* next;
 
    // private visibility of employee's name, age, address, role, salary
private:
    string name;
    int age;
    string address;
    string role;
    double salary;
    
    
    
    
 
public:
    
    // constructor
    Employee(int ident, string nm, int yrs, string location, string job, double wage)
    {
        id = ident;
        name = nm;
        age = yrs;
        address = location;
        role = job;
        salary = wage;
        
    }
    
    
    
    // Accessors and mutators
    string getName()
    {
        return name;
    }
    
    
    void setName(string nm)
    {
        this->name = nm;
    }
    
    
    int getAge()
    {
        
        return age;
    }
    
    void setAge(int ag)
    {
        this->age = ag;
    }
    
    string getAddress()
    {
        return address;
    }
    
    
    void setAddress(string add)
    {
        this->address = add;
    }
    
    string getRole()
    {
        return role;
    }
    
    void setRole(string rl)
    {
        this->role = rl;
    }
    
    double getSalary()
    {
        return salary;
    }
    
    
    void setSalary(double slry)
    {
        this->salary = slry;
    }
    
    
    
    
};// end of employee class

// staffsystem class
class StaffSystem
{
private:
    
    // array of pointers to pointers
    Employee** table;
    
public:
    
    // constructor
    StaffSystem()
    {
        // create array of size MAX of linkedlists of employees
        table = new Employee*[MAX];
        
        // set each pointer in bucket to null
        for (int i = 0; i < MAX; i++)
        {
            table[i] = NULL;
        }
        
    }// end of constructor
    
    
    
    
    // insert function
    void INSERT(Employee* x)
    {
        Employee* temp = NULL;
        Employee* prev = NULL;
        
        // hash the employee's id
        int index = hashFunc(x->id);
        
        /// set temp to the bucket at index
        temp = table[index];
        
        // if bucket empty, set bucket to point to employee object
        if (temp == NULL)
        {
            table[index] = x;
        }
        
        // if not empty
        else
        {
            // while not at end of list yet,
            while (temp != NULL)
            {
                // set prev to temp
                prev = temp;
                
                // set temp to temp's next
                temp = temp->next;
            }
            
            // set prev's next to employee object
            prev->next = x;
            
            // set employee object's next to NULL
            x->next = NULL;
        }
        
    }// end of insert function
    
    
    
    
    
    // search function
    Employee* SEARCH(int i)
    {
        Employee* temp = NULL;
        
        // hash i
        int index = hashFunc(i);
        
        // set temp to bucket at index
        temp = table[index];
        
        // while not at end of list
        while (temp != NULL)
        {
            // if the id of the object matches with i
            if (temp->id == i)
            {
                // return the object
                return temp;
            }
            
            // set temp to temp's next
            temp = temp->next;
        }
        
        return NULL;
    }// end of search function
    
    
    
    
    
    
    // delete function
    void DELETE(Employee* x)
    {
        Employee* prev = NULL;
        Employee* curr = NULL;
        
        // hash id
        int index = hashFunc(x->id);
        
        // if bucket is empty
        if (table[index] == NULL)
        {
            
        }
        
        // if not empty
        else
        {
            // set curr to bucket
            curr = table[index];
            
            // if object to delete is first in the list
            if (curr->id == x->id)
            {
                //set bucket to bucket's next
                table[index] = table[index]->next;
                
                // delete object
                delete curr;
            }
            
            // if object is not first
            else
            {
                // while not at end of list and object's id does not match what we are looking for
                while(curr != NULL && curr->id != x->id)
                {
                    
                    // set prev to curr
                    prev = curr;
                    
                    // set curr to curr's next
                    curr = curr->next;
                }
                
                // if curr's next is nothing
                if (curr->next == NULL)
                {
                    // delete curr
                    delete curr;
                    
                    // set prev's next to null
                    prev->next = NULL;
                }
                
                // if curr has something after it
                else
                {
                    // link prev's next to curr's next
                    prev->next = curr->next;
                    
                    // delete curr
                    delete curr;
                }
            }
            
        }
    }// end of delete function
    
    
    
    void EDIT(Employee* x, int eChoice)
    {
        
        // employee info
        string nm;
        int a;
        string add;
        string job;
        double slry;
        
        // choosing which info to edit
        switch(eChoice)
        {
                case 1:
            {
                
                // prompt for new name
                cout << "Enter the new name: " << endl;
                
                // input name
                cin >> nm;
                
                // change name
                x->setName(nm);
                
                break;
            }
                
            case 2:
            {
                
                // prompt for new age
                cout << "Enter the new age: " << endl;
                
                // input new age
                cin >> a;
                
                
                // change age
                x->setAge(a);
                
                break;
            }
                
                
            case 3:
            {
                // prompt for new address
                cout << "Enter the new address: " << endl;
                
                // input new address
                cin >> add;
                
                // change address
                x->setAddress(add);
                
                
                break;
            }
                
            case 4:
            {
            
                // prompt for new role
                cout << "Enter the new role: " << endl;
                
                // input new role
                cin >> job;
                
                // change role
                x->setRole(job);
                break;
            }
                
                
            case 5:
            {
                
                
                // prompt for new salary
                cout << "Enter the new salary: " << endl;
                
                
                // input new salary
                cin >> slry;
                
                // change salary
                x->setSalary(slry);
                
                
                break;
            }
        }
    }
    
    
    
    
    // destroy memory of hashtable
    void REMOVEALL()
    {
        
        // curr and prev pointers to nodes
        Employee* curr = NULL;
        Employee* prev = NULL;
        
        
        // for every linked list in a bucket
        for (int i = 0; i < MAX; i++)
        {
            // set curr to the first node in the bucket
            curr = table[i];
            
            // while the end of the list has not been reached
            while (curr != NULL)
            {
                // set prev to curr
                prev = curr;
                
                // set curr to curr's next
                curr = curr->next;
                
                // delete the prev node
                delete prev;
            }
            
        }
        
        // delete array of pointers
        delete[] table;
        
    }// end of removeall function
    
    
    // search20k function
    list<Employee> SEARCH20K()
    {
        list<Employee> sub;
        
        
        // curr and prev pointers to nodes
        Employee* curr = NULL;
        Employee* prev = NULL;
        
        
        // for every linked list in a bucket
        for (int i = 0; i < MAX; i++)
        {
            // set curr to the first node in the bucket
            curr = table[i];
            
            // while the end of the list has not been reached
            while (curr != NULL)
            {
                // set prev to curr
                prev = curr;
                
                // set curr to curr's next
                curr = curr->next;
                
                // if the salary is over 20,000
                if (prev->getSalary() > 20000)
                {
                    
                    // add object to list
                    sub.push_back(*prev);
                }
                
                
            }
            
        }
        
        // return linked list of employees
        return sub;
        
        
    }// end of search25k function
    
    
    // display function
    void DISPLAY(int i)
    {
        Employee* temp;
        
        // set temp to returned object of search
        temp = SEARCH(i);
        
        // display info about employee
        cout << "Name: " << temp->getName() << endl;
        
        cout << "ID: " << temp->id << endl;
    
        cout << "Age: " << temp->getAge() << endl;
        
        cout << "Address: " << temp->getAddress() << endl;
        
        cout << "Role: " << temp->getRole() << endl;
        
        cout << "Salary: " << temp->getSalary() << endl << endl;
        
    }// end of display function
    
    
    // hash function
    int hashFunc(int id)
    {
        return id % MAX;
        
        
        
    }// end of hash function
    
    
};// end of staffsystem class





// main function
int main()
{
    
    
    int choice, id, age;
    int editChoice;
    string name, address, role;
    double salary;
    StaffSystem staff;
    
    
    // display title of program
    cout << "Staff Management System" << endl;
    cout << "-----------------------" << endl << endl;
    
    
    
    while (true)
    {
        
        // display choices
        cout << "1. Insert employee into system" << endl;
        cout << "2. Search for employee" << endl;
        cout << "3. Edit employee's details" << endl;
        cout << "4. Delete an employee" << endl;
        cout << "5. Search for employees with salary higher than $20,000" << endl;
        cout << "6. Exit" << endl << endl;
        
        cin >> choice;
        
        
        switch (choice) {
            case 1:
            {
                // prompt for info
                cout << "Enter the employee's id number: " << endl;
                
                cin >> id;
                
                cout << "Enter the employee's name: " << endl;
                
                cin >> name;
                
                cout << "Enter the employee's age: " << endl;
                
                cin >> age;
                
                cout << "Enter the address of the employee: " << endl;
                
                cin >> address;
                
                cout << "Enter the role of the employee: " << endl;
                
                cin >> role;
                
                cout << "Enter the employee's salary: " << endl;
                
                cin >> salary;
                
                
                if (staff.SEARCH(id) == NULL)
                {
                    // create employee
                    Employee* employ = new Employee(id, name, age, address, role, salary);
                
                    // insert employee
                    staff.INSERT(employ);
                }
                
                else
                {
                    
                
                    cout << "Can't insert that employee because one already exists with that id number. " << endl << endl;
                
                }
                
                
                break;
            }
            case 2:
            {
                // prompt for id
                cout << "Enter the employee's id number to search for: " << endl << endl;
                cin >> id;
                
                // if employee does not exist, display message
                if (staff.SEARCH(id) == NULL)
                {
                    cout << "The employee id entered does not exist. " << endl << endl;
                    
                }
                
                // otherwise, call display function to show info
                else
                {
                    staff.DISPLAY(id);
                }
                
                break;
            }
            case 3:
            {
                
                // prompt for id
                cout << "Enter the id number for the employee info you want to edit: " << endl << endl;
                cin >> id;
                
                // search for employee
                Employee* empl2 = staff.SEARCH(id);
                
                // if employee does not exist, then can't edit info
                if (empl2 == NULL)
                {
                    cout << "Can't edit information because the employee does not exist in the system. " << endl << endl;
                }
                
                // otherwise, ask what info should be edited
                else
                {
                    // prompt for edit choice
                    cout << "Enter which piece of info you would like to change: " << endl;
                    cout << "1. Name " << endl;
                    cout << "2. Age " << endl;
                    cout << "3. Address " << endl;
                    cout << "4. Role " << endl;
                    cout << "5. Salary " << endl << endl;
                    cin >> editChoice;
                    
                    // edit info
                    staff.EDIT(empl2, editChoice);
                    
                    // display success message
                    cout << "The employee's information has been changed. " << endl << endl;
                }
                break;
            }
            case 4:
            {
                // prompt for id
                cout << "Enter the employee's id number to delete: " << endl << endl;
                
                
                cin >> id;
                
                // search for employee
                Employee* empl1 = staff.SEARCH(id);
                
                
                // if employee does not exist, then cannot be deleted
                if (empl1 == NULL)
                {
                    cout << "The employee cannot be deleted since it does not exist. " << endl << endl;
                }
                
                // otherwise, delete employee and display success message
                else
                {
                    staff.DELETE(empl1);
                    
                    cout << "The employee was deleted." << endl << endl;
                }
                break;
            }
            case 5:
            {
                // create list of employees
                list<Employee> a;
                
                // store returned list
                a = staff.SEARCH20K();
                
                // iterator for list
                list<Employee>::iterator it;
                
                // display name of each employee in the list
                for (it = a.begin(); it != a.end(); it++)
                {
                    cout << it->getName() << endl;
                }
                
                
                
                break;
            }
            case 6:
            {
                // destroy every employee in the hash table
                staff.REMOVEALL();
                system("pause");
                exit(0);
                //break;
            }
            
            
            default:
            {
                break;
            }
        }// end of switch case
        
        
        
        
        
    }// end of while loop
    
    
    
    
    
}// end of main function
