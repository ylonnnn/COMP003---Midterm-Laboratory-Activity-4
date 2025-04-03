#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace std;

// Configure the passing grade for your purpose
int PASSING_GRADE = 75;

int *getStudentGrades(const int *students) {
  cout << "Enter the quiz grade of each student\n";

  int *grades = new int[*students];

  for (int i = 0; i < *students; i++) {
    int grade;

    cout << "Student " << i + 1 << ": ";
    cin >> grade;

    if (grade < 0 || grade > 100 || cin.fail()) {

      //   For Termination:
      //   string err = "Grade must be between 0 to 100";

      //   cout << err << "\n";
      //   throw range_error(err);

      //   Constant Loop
      i--;

      cin.clear();
      cin.ignore(1'000, '\n');
    }

    grades[i] = grade;
  }

  return grades;
}

bool passed(const int *grade) { return *grade >= ::PASSING_GRADE; }

int displayGrades(const int *grades, const int *students) {
  cout << "--- Quiz Grade Results ---\n";

  int passedStudents = 0;

  for (int i = 0; i < *students; i++) {
    int grade = *(grades + i);
    bool _passed = passed(&grade);

    if (_passed)
      passedStudents++;

    cout << "Student " << i + 1 << " | Score: " << grade << " | - "
         << (_passed ? "Passed" : "Failed") << "\n";
  }

  return passedStudents;
}

double calculateAverageGrade(const int *grades, const int &students) {
  int sum = 0;

  for (int i = 0; i < students; i++)
    sum += *(grades + i);

  return (double)(sum) / students;
}

void displaySummary(const int *grades, const int *students, const int *passed) {
  cout << "--- Summary ---\nAverage Quiz Grade: "
       << calculateAverageGrade(grades, *students)
       << "\nNumber of Students that Passed the Quiz (Score >= "
       << ::PASSING_GRADE << "): " << *passed << "\n";
}

int main() {
  //
  int students;
  cout << "Enter the number of students: ";
  cin >> students;

  // If the number of students specified is invalid, throw an error
  if (students < 1) {
    try {
      throw runtime_error("Invalid number of students!");
    } catch (const runtime_error err) {
      cout << err.what() << "\n";
    }

    return 1;
  }

  // Prompt the user for the grades of the students
  int *grades = getStudentGrades(&students);

  cout << "\n";

  // Display the grades of the students and
  // retrieve the number of students that passed
  int passedStudents = displayGrades(grades, &students);

  cout << "\n";

  // Display the summary
  displaySummary(grades, &students, &passedStudents);

  return 0;
}