#include <iostream>
#include <fstream>
using namespace std;

// A `quiz' item data structure.
struct quiz
{
  string last_name;
  string first_name;
  int grades[10];
  double avg;
};

// Function to initialize a `quiz' data structure.
struct quiz *
init_quiz(string last_name, string first_name, int grades[])
{
  struct quiz *qs;
  int total = 0;
  qs = (struct quiz *)malloc(sizeof(struct quiz));

  if (qs == NULL)
    throw new runtime_error("Ran out of storage.");

  qs->last_name = last_name;
  qs->first_name = first_name;
  for (size_t i = 0; i < 10; ++i) {
    total += grades[i];
    qs->grades[i] = grades[i];
  }
  qs->avg = total / 10.0;

  return qs;
}

void
export_avg(fstream *input_file_obj, fstream *output_file_obj)
{
  // Temporary storage.
  string cell;
  string last_name;
  string first_name;
  int grades[10];
  struct quiz *quizzes[10];

  // For each empty array element, build the quiz structure and assign
  // it to a position of the quizzes array.
  for (size_t i = 0; i < 10; ++i) {
    *input_file_obj >> last_name;
    *input_file_obj >> first_name;
    for (size_t j = 0; j < 10; ++j) {
      *input_file_obj >> grades[j];
    }
    quizzes[i] = init_quiz(last_name, first_name, grades); // Bulid struct.
  }

  // For each quiz item, write it to the file object for output.
  for (size_t i = 0; i < 10; ++i) {
    *output_file_obj << quizzes[i]->last_name << ' ';
    *output_file_obj << quizzes[i]->first_name << ' ';
    // Iterate through the grades array field of the current quiz
    // struct.
    for (size_t j = 0; j < 10; ++j) {
      *output_file_obj << quizzes[i]->grades[j] << ' ';
    }
    *output_file_obj << quizzes[i]->avg << '\n';
  }

  // Memory safety!
  for (size_t i = 0; i < 10; ++i) {
    free(quizzes[i]);
  }

}

int
main ()
{
    fstream input_file_obj;
    fstream output_file_obj;
    string input_file_name;
    string output_file_name;

    cout << "Welcome to Quiz Averager Program!\n"
	 << "\n"
	 << "Compute the average of the students' quizzes in FILE.\n"
	 << "FILE should be a text file containing the records of students'\n"
	 << "quizzes. Records are separated by a newline; columns are\n"
	 << "separated by one or more white space characters.\n"
	 << "\n\n";

    // Open the text file for reading.
    cout << "Enter input FILE: ";
    cin >> input_file_name;		// Prompt for text file for reading.
    input_file_obj.open(input_file_name, ios::in);
    if (input_file_obj.fail()) {
      cerr << "File for reading failed to open.\n";
      exit(1);
    }

    // Open the text file for writing.
    output_file_name =
      input_file_name.substr(0, input_file_name.find_last_of("."))
      + "-with-avg.txt";
    output_file_obj.open(output_file_name, ios::out);
    if (output_file_obj.fail()) {
      cerr << "File for writing failed to open.\n";
      exit(1);
    }

    // Notify user if done!
    export_avg(&input_file_obj, &output_file_obj);
    cout << "Averaging done! Please Check the file '"
	 << output_file_name << "'.\n";

    // Cleanup
    input_file_obj.close();
    output_file_obj.close();

  return 0;
}
