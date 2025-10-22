//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Cameron Beck
// Version     : 1.0
// Copyright   : Copyright © 2025 SNHU COCE
// Description : Designing data structure and algorithms for courses
//============================================================================


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

//Established struct for Course
struct Course {
	string courseNumber;//Unique identifier
	string courseName;
	vector<string> prerequisites;

};

//User Inputs 1 from menu to load courses from
//the csv file onto the program's data structure
vector<Course> loadCourses(const string& fileName) {
	vector<Course> courses;
	vector<string> prereq;
	
	cout << "Loading CSV file: " << fileName << endl;
	//Opening file
	ifstream file;
	file.open(fileName);
	//If the file cannot open, an error message will display
	//and return to the menu
	if (!file.is_open()) {
		cout << "ERROR: Cannot open file " << fileName <<endl;
		exit(EXIT_FAILURE);
	}

	string line;
	while (getline(file,line)){
		stringstream ss(line);//reads string file in line
		Course course; //creates empty course in each loop 
		string courseNumber, courseName, prerequisite; //the course's information
		getline(ss, courseNumber, ','); //first element is the course number 
		getline(ss, courseName, ','); //second element is the course name
		
		//adds course number and course name
		course.courseNumber = courseNumber;
		course.courseName = courseName;
		
		//The while statement indicates that there are prerequisties 
		//to the class. During the while loop, all of the prerequisites
		// are added to the Course classes prerequisite vector
		while (getline(ss, prerequisite, ',')) {
			course.prerequisites.push_back(prerequisite);
		}

		//All of the courses course number, course name, and prerequisites (if any)
		//are added to courses vector
		courses.push_back(course);
	}
	cout << fileName << " load complete!" << endl;
	file.close();

	//Returns all of the stored courses data to main.
	return courses;
}

//User inputs choice no. 2 from menu to print
//all of the courses in order
//from lowest to highest
void printCoursesList(vector<Course> courses) {
	//Sorts the courses in order
	Course temp;
	for (int i = 0; i < courses.size(); i++) {
		for (int j = i + 1; j < courses.size(); j++) {
			//The if statement sorts the all of the courses by the Courses course number (I.E 100, 101, 300)
			if(courses.at(i).courseNumber.substr(4, 7) > courses.at(j).courseNumber.substr(4, 7))
			{
				temp = courses.at(i);
				courses.at(i) = courses.at(j);
				courses.at(j) = temp;
			}
		}
	}

	//prints out the courses and it's prerequisites
	for (Course course : courses) {
		cout << course.courseNumber << " " << course.courseName;
		//If prerequisites exists, then the program prints all of the course's prerequisites.
		if (course.prerequisites.size() > 0) {
			for (int i = 0; i < course.prerequisites.size(); i++) {
				cout << " " << course.prerequisites[i];
			}
		}
		cout << endl;
	}
}

//User inputs choice no. 3 from menu and inputs course number
//to display not only the course ID and title
//but the course prerequisites as well (if it exists)
void printCourse(vector<Course> courses, string courseID) {
	//Iterates through the Courses
	for (Course course : courses) {
		if (course.courseNumber.compare(courseID) == 0) {//course's course number matches user's inpuut
			cout << course.courseNumber << " " << course.courseName;

			//If prerequisites exists, then the program prints all of the course's prerequisites.
			if (course.prerequisites.size() > 0) {
				for (int i = 0; i < course.prerequisites.size(); i++) {
					cout << " " << course.prerequisites[i];
				}
			}
			cout << endl;
		}
	}
}

//MAIN METHOD
int main() {
	vector<Course> courses; //created variable courses from struct Course
	int menuChoice = 0; //initialized for while loop to operate
	const string fileName = "CS_300_ABCU_Advising_Program_Input.csv";//I edited the file name with '_' in between spaces to open file.
	string courseNumber; //user input for case 3

	//Menu loop until user inputs 9
	while (menuChoice != 9) {
		//The menu's options for the user to choose from
		cout << "Menu:" << endl;
		cout << "  1. Load courses" << endl;
		cout << "  2. Display all courses" << endl;
		cout << "  3. Display course title and prerequisites" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> menuChoice;

		switch (menuChoice) {
		//Load courses onto the data structure
		case 1:
			courses = loadCourses(fileName);
			break;
		//Print courses in order from lowest to highest
		case 2:
			printCoursesList(courses);
			break;
		//Input course number and display the course title and it's prerequisite(s)
		case 3:
			cout << "Enter course number: ";
			cin >> courseNumber;
			printCourse(courses, courseNumber);
			break;
		//Input is neither 1, 2, nor 3
		default:
			if (menuChoice != 9) {
				cout << "ERROR: Invalid option, try again...." << endl;
				break;
			}
			else {//Input is 9, so it will break not only the default case but the while-loop too.
				break;
			}
		}
		
	}
	//End of program
	cout << "Good bye." << endl;
}