#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct student_struct
{
  int student_id;
  string last_name;
  string first_name;
  double gpa;
};

struct student_struct *
construct_student(int student_id, string last_name, string first_name, double gpa)
{
  struct student_struct *student;
  student = (struct student_struct *)malloc(sizeof(struct student_struct));
  if (student == NULL) {
    throw new runtime_error("Ran out of storage.");
  }

  student->student_id = student_id;
  student->last_name = last_name;
  student->first_name = first_name;
  student->gpa = gpa;

  return student;
}

void
clean_array_of_students(struct student_struct *students[], size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    free(students[i]);
  }
}

size_t
count_lines(fstream *file)
{
  string line;
  size_t count = 0;
  while(getline(*file, line)) {
    ++count;
  }
  file->clear();
  file->seekg(0);			// Position cursor back into
					// beginning of file.
  return count;
}

void swap_students(struct student_struct *a,
		   struct student_struct *b)
{
  student_struct temp = *a;
  *a = *b;
  *b = temp;
}

void
bubble_sort_students(struct student_struct **arr, size_t n)
{
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (arr[j]->student_id > arr[j+1]->student_id) {
	swap_students(*arr+j, *arr+j+1);
      }
    }
  }
}

void
merge_and_export(fstream *file1, fstream *file2, fstream *file_out)
{
  int student_id;
  string last_name;
  string first_name;
  double gpa;
  string file_name;
  size_t file1_line_count = count_lines(file1);
  size_t file2_line_count = count_lines(file2);
  size_t total_records = file1_line_count + file2_line_count;
  size_t i = 0;

  // Declare an array of `students'.
  struct student_struct *students[total_records];

  // For each line of the 1st file, fill out the fields of each
  // `student' in the `students' array.
  while (i < file1_line_count) {
    *file1 >> student_id;
    *file1 >> last_name;
    *file1 >> first_name;
    *file1 >> gpa;
    students[i++] = construct_student(student_id, last_name, first_name, gpa);
  }

  // For each line of the 2st file, fill out the fields of each
  // `student' in the `students' array.
  while (i < total_records) {
    *file2 >> student_id;
    *file2 >> last_name;
    *file2 >> first_name;
    *file2 >> gpa;
    students[i++] = construct_student(student_id, last_name, first_name, gpa);
  }
  
  // Sort the array of students by their `student_id'
  bubble_sort_students(students, total_records);


  // Place each item in the merged `students' array in the output
  // file.
  for (size_t i = 0; i < total_records; ++i) {
    *file_out << left << setw(8) << students[i]->student_id
	      << setw(12) << students[i]->last_name
	      << setw(12) << students[i]->first_name
	      << students[i]->gpa
	      << '\n';
  }

  // cout << "I'm here! i = " << i << '\n';
  // exit(0);

  // Cleanup: Avoid leaking memory.
  clean_array_of_students(students, total_records);
}    
    

int
main ()
{
  fstream input_file_obj;
  string input_file_name;
  fstream input2_file_obj;
  string input2_file_name;
  fstream output_file_obj;
  string output_file_name;

   cout << "Welcome to Student Database Merger Program!\n"
	<< "\n"
	<< "Merge student databases. You may provide one or more\n"
	<< "files separated by whitespace. Enter 'q' to finilize files.\n"
	<< "\n";

  // Open the text file for reading.
  cout << "Enter FILE 1: ";
  cin >> input_file_name;		// Prompt for text file for reading.
  input_file_obj.open(input_file_name, ios::in);
  if (input_file_obj.fail()) {
    cerr << "File for reading failed to open.\n";
    exit(1);
  }

  // Open the text file for reading.
  cout << "Enter FILE 2: ";
  cin >> input2_file_name;		// Prompt for text file for reading.
  input2_file_obj.open(input2_file_name, ios::in);
  if (input2_file_obj.fail()) {
    cerr << "File for reading failed to open.\n";
    exit(1);
  }

  // Open the text file for writing.
  cout << "Enter output FILE name: ";
  cin >> output_file_name;		// Prompt for text file for writing.
  output_file_obj.open(output_file_name, ios::out);
  if (output_file_obj.fail()) {
    cerr << "File for writing failed to open.\n";
    exit(1);
  }

  // Notify user if done!
  merge_and_export(&input_file_obj, &input2_file_obj, &output_file_obj);
  cout << "\nMerging done! Please Check the file '"
       << output_file_name << "'.\n";


  // Cleanup
  input_file_obj.close();
  input2_file_obj.close();
  output_file_obj.close();
}
