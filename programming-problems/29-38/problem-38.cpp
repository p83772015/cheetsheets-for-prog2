#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct
Employee
{
  string name;
  string ssn;
  double hourly_rate;
  int hours_worked;
};

void
safe_open(fstream *file, string name, ios_base::openmode flag)
{
  file->open(name, flag);
  if (file->fail()) {
    cerr << name << " for reading failed to open.\n";
    exit(1);
  }
}

void
add_employee(struct Employee employees[],
	     fstream *from_file,
	     size_t *size)
{
  string line;
  string rate_s;
  string hrs_s;
  stringstream ss;
  while (getline(*from_file, line)) {
    ss.clear();
    ss << line;
    getline(ss, employees->name, '|');
    getline(ss, employees->ssn, '|');
    getline(ss, rate_s, '|');
    employees->hourly_rate = stod(rate_s);
    getline(ss, hrs_s, '|');
    employees->hours_worked = stoi(hrs_s);
    employees++;
    (*size)++;
  }
}

void
display_gross(fstream *input_file)
{
  struct Employee employees[255];
  size_t employee_size = 0;
  string line;

  add_employee(employees, input_file, &employee_size);

  cout << '\n';
  cout << setw(16) << "Name"
       << setw(16) << "SSN"
       << setw(14) << "Gross Pay"
       << '\n';
  cout << setw(16) << "==========="
       << setw(16) << "==========="
       << setw(14) << "==========="
       << '\n';
  for (size_t i = 0; i < employee_size; ++i) {
    cout << setw(16) << employees[i].name
	 << setw(16) << employees[i].ssn
	 << setw(14)
	 << employees[i].hourly_rate * employees[i].hours_worked
	 << '\n';
  }
}

int
main ()
{
  fstream input_file_1_obj;
  string input_file_1_name;

  cout << "Welcome to Gross Pay Calulator Program!\n"
       << "\n"
       << "Compute the gross pay of each employee from FILE.\n"
       << "\n";
  
  // Open the text file for reading.
  cout << "Enter input FILE [1]: ";
  cin >> input_file_1_name;		// Prompt for text file for reading.
  safe_open(&input_file_1_obj, input_file_1_name, ios::in);

  // Notify user if done!
  display_gross(&input_file_1_obj);

  // Cleanup
  input_file_1_obj.close();
  return 0;
}
