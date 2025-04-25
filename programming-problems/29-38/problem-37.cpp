#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Patient
{
  string name;
  string gender;
  int lbs;
};

/*********/
/* Utils */
/*********/

void
safe_open(fstream *file, string name, ios_base::openmode flag)
{
  file->open(name, flag);
  if (file->fail()) {
    cerr << name << " for reading failed to open.\n";
    exit(1);
  }
}

void swap_patients(struct Patient *a,
		   struct Patient *b)
{
  Patient temp = *a;
  *a = *b;
  *b = temp;
}

void
bubble_sort_patients(struct Patient arr[], size_t n)
{
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (arr[j].lbs < arr[j+1].lbs) {
	swap_patients(arr+j, arr+j+1);
      }
    }
  }
}

/*************/
/* End Utils */
/*************/

void
add_patients(struct Patient patients[],
	     fstream *from_file,
	     size_t *size)
{
  string line;
  string lbs_s;
  stringstream ss;
  while(getline(*from_file, line)) {
    ss.clear();
    ss << line;
    getline(ss, patients->name, '|');
    getline(ss, patients->gender, '|');
    getline(ss, lbs_s, '|');
    patients->lbs = stoi(lbs_s);
    patients++;
    (*size)++;
  }
}
	     

void
split_patient_file(struct Patient patients[],
		   size_t *patients_size,
		   fstream *input_file,
		   fstream *male_output_file,
		   fstream *female_output_file)
{
  add_patients(patients, input_file, patients_size);
  bubble_sort_patients(patients, *patients_size);

  for (size_t i = 0; i < *patients_size; ++i) {
    if (patients[i].gender == "Female") {
      *female_output_file << patients[i].name << '|'
			  << patients[i].gender << '|'
			  << patients[i].lbs << '\n';
    } else if ((patients[i].gender == "Male")) {
      *male_output_file << patients[i].name << '|'
			  << patients[i].gender << '|'
			  << patients[i].lbs << '\n';
    }
  }
}

int
main ()
{
  fstream input_file_1_obj;
  string input_file_1_name;
  fstream male_output_obj;
  fstream female_output_obj;

  struct Patient patients[255];
  size_t patients_size = 0;

  cout << "Welcome to Patient File Separator Program!\n"
       << "\n"
       << "Split PATIENT FILE by gender; sort it by weight loss in descending order.\n"
       << "\n";
  
  // Open the text file for reading.
  cout << "Enter PATIENT FILE [1]: ";
  cin >> input_file_1_name;		// Prompt for text file for reading.
  safe_open(&input_file_1_obj, input_file_1_name, ios::in);

  safe_open(&male_output_obj, "37-male.txt", ios::out);
  safe_open(&female_output_obj, "37-female.txt", ios::out);

  // Notify user if done!
  split_patient_file(patients,
		     &patients_size,
		     &input_file_1_obj,
		     &male_output_obj,
		     &female_output_obj);
  cout << "\nSplitting done!\n"
       << "Please Check the file(s): "
       << "'37-male.txt' and '37-female.txt\n";

  // Cleanup
  input_file_1_obj.close();
  male_output_obj.close();
  female_output_obj.close();

  return 0;
}
