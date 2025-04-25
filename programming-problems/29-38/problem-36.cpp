#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Patient
{
  string first_name;
  string last_name;
  string address;
  int birth_year;
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
bubble_sort_patients(struct Patient *arr, size_t n)
{
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (arr[j].birth_year > arr[j+1].birth_year) {
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
	     fstream *file,
	     size_t *size)
{
  string first_name;
  string last_name;
  string address;
  string birth_year_s;
  string line;
  stringstream ss;
  patients = patients + *size;

  while (getline(*file, line)) {
    ss.clear();
    ss << line;
    getline(ss, patients->first_name, '|');
    getline(ss, patients->last_name, '|');
    getline(ss, patients->address, '|');
    getline(ss, birth_year_s);
    patients->birth_year = stoi(birth_year_s);
    (*size)++;
    patients++;
  }
}

void
write_patients_to_file(struct Patient patients[],
		       size_t size,
		       fstream *output_file)
{
  for (; size > 0; size--) {
    *output_file << patients->first_name << '|'
		 << patients->last_name << '|'
		 << patients->address << '|'
		 << patients->birth_year << '|'
		 << '\n';
    patients++;
  }
}

void
merge_patient_db(struct Patient patients[],
		 size_t *patients_size,
		 fstream *patient_file_obj_1,
		 fstream *patient_file_obj_2,
		 fstream *merged_db_obj)
{
  string cell;
  string first_name, last_name, address;
  string birth_year;

  add_patients(patients, patient_file_obj_1, patients_size);
  add_patients(patients, patient_file_obj_2, patients_size);

  bubble_sort_patients(patients, *patients_size);
  write_patients_to_file(patients, *patients_size, merged_db_obj);
}

struct Freq
{
  int birth_year;
  size_t count;
};

void
add_to_freq(struct Freq freq[], size_t *patients_size, int value)
{
  for (size_t i = 0; i < *patients_size; ++i) {
    if (freq[i].birth_year == value) {
      (freq[i].count)++;
      return;
    }
  }
  freq[*patients_size].birth_year = value;
  freq[*patients_size].count = 1;
  (*patients_size)++;
}

void
generate_frequency_dist(struct Patient patients[],
			size_t patients_size,
			fstream *output_file)
{
  struct Freq birth_year_freq[50];
  size_t birth_year_freq_size = 0;
  
  for (; patients_size > 0; --patients_size) {
    add_to_freq(birth_year_freq,
		&birth_year_freq_size,
		patients->birth_year);
    patients++;
  }

  for (size_t i = 0; i < birth_year_freq_size; ++i) {
    *output_file << birth_year_freq[i].birth_year << '|'
		 << birth_year_freq[i].count << '\n';
  }
}

int
main ()
{
  fstream patient_db_1_obj;
  string patient_db_1_name;
  fstream patient_db_2_obj;
  string patient_db_2_name;
  fstream merged_db_obj;
  fstream frequency_file_obj;

  struct Patient patients[255];
  size_t patients_size = 0;

  cout << "Welcome to Patient Database Merger Program!\n"
       << "\n"
       << "Merge two databases of patient records and sort\n"
       << "them by their birth year. Additionally, produce a\n"
       << "file containing the frequency of merged database's\n"
       << "birth year.\n"
       << "\n";
  
  // Open the text file for reading.
  cout << "Enter first Patient db file name: ";
  cin >> patient_db_1_name;		// Prompt for text file for reading.
  safe_open(&patient_db_1_obj, patient_db_1_name, ios::in);

  // Open the text file for reading.
  cout << "Enter second Patient db file name: ";
  cin >> patient_db_2_name;		// Prompt for text file for reading.
  safe_open(&patient_db_2_obj, patient_db_2_name, ios::in);

  safe_open(&merged_db_obj, "merged-patients-db.txt", (ios::out | ios::in));
  safe_open(&frequency_file_obj, "frequency.txt", ios::out);

  // Notify user if done!
  merge_patient_db(patients,
		   &patients_size,
		   &patient_db_1_obj,
		   &patient_db_2_obj,
		   &merged_db_obj);
  generate_frequency_dist(patients,
			  patients_size,
			  &frequency_file_obj);
  cout << "\nMerging done!\n"
       << "Please Check the file(s): "
       << "'merged-patients-db.txt' and 'frequency.txt'\n";

  // Cleanup
  patient_db_1_obj.close();
  patient_db_2_obj.close();
  merged_db_obj.close();
  frequency_file_obj.close();

  return 0;
}
