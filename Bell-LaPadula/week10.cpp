/***********************************************************************
* Program:
*    Week 10, Bell-LaPadula
*    Brother Helfrich, CS470
* Author:
*    your name here
* Summary:
*    This program tracks a collection of student grades
*    Currently, it performs no authentication and furthermore
*    is so trivially hack-able that it is a joke.  Hahaha.  Why
*    is noone laughing?  OK, as you guess, your job in a collection
*    of assignments is to make this program secure.  Enjoy!
************************************************************************/


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

// levels of permission
// ADMIN - can view any grade
// STUDENT - can only view own grade
// PUBLIC - cannot view any grade
enum Permission { PUBLIC, STUDENT, ADMIN };

/***********************************************
* BELLLAPADULA
* creates permission level based on Bell-LaPadula 
* Model
**********************************************/
class BellLaPadula
{
public:
	BellLaPadula(string name);
	bool isFileAccessible(string name);

private:
	Permission permission;
	string user;
};

/***********************************************
* BELLLAPADULA
* constructor
**********************************************/
BellLaPadula::BellLaPadula(string name)
{
	user = name;
	if (name == "Bob" || name == "Hans")
	{
		permission = ADMIN;
	}
	else if (name == "Sam" || name == "Sue" || name == "Sly")
	{
		permission = STUDENT;
	}
	else
	{
		permission = PUBLIC;
	}
}

/***********************************************
* ISFILEACCESSIBLE
* enforces permissions
**********************************************/
bool BellLaPadula::isFileAccessible(string name)
{
	// ADMIN permissions
	if (user == "Bob" || user == "Hans") { return true; }

	// STUDENT permissions
	else if (user == "Sam" && name == "Samual Stevenson") { return true; }
	else if (user == "Sue" && name == "Susan Bakersfield") { return true; }
	else if (user == "Sly" && name == "Sylvester Stallone") { return true; }

	// PUBLIC permissions
	else { return false; }
}


/******************************************
 * FILE
 * A single file resource
 *****************************************/
struct File
{
	const char *filename;   // where it is located
};

/****************************************
 * Files
 * All the files currently on the system
 ****************************************/
const File files[3] =
{
   { "/home/cs470/week10/sam.txt" },
   { "/home/cs470/week10/sue.txt" },
   { "/home/cs470/week10/sly.txt" }
};


/*****************************************************************
 *****************************************************************
 *                       Student Grade class                     *
 *****************************************************************
 *****************************************************************/
struct Item
{
	float weight;
	float score;
};

/***************************************************
 * One instance of a student grade
 ***************************************************/
class StudentGrade
{
public:
	StudentGrade(const File & files);
	~StudentGrade();
	string getLetterGrade(); // output letter grade B+
	float  getNumberGrade(); // integral number grade 88
	void   displayScores(); // display scores on screen
	bool   editScores(BellLaPadula b); // interactively edit score
	void   setScore(int iScore, float score);
	float  getScore(int iScore);
	void   setWeight(int iScore, float weight);
	float  getWeight(int iScore);
	string getName() { return name; };
private:
	bool change;
	string name;                    // student's name
	vector < Item > scores;         // list of scores and weightings
	const char * filename;

	void editScore(int);  // edit one score
};

/**********************************************
 * SET SCORE
 **********************************************/
void StudentGrade::setScore(int iScore, float score)
{
	assert(iScore >= 0 && iScore < scores.size());
	scores[iScore].score = score;
	change = true;
}

/**********************************************
 * GET SCORE
 **********************************************/
float StudentGrade::getScore(int iScore)
{
	assert(iScore >= 0 && iScore < scores.size());
	return scores[iScore].score;
}

/****************************************
 * SET WEIGHT
 ****************************************/
void StudentGrade::setWeight(int iScore, float weight)
{
	assert(iScore >= 0 && iScore < scores.size());
	if (weight >= 0.0)
	{
		scores[iScore].weight = weight;
		change = true;
	}
}

/**********************************************
 * GET WEIGHT
 **********************************************/
float StudentGrade::getWeight(int iScore)
{
	assert(iScore >= 0 && iScore < scores.size());
	return scores[iScore].weight;
}

/***********************************************
 * STUDENT GRADE
 * constructor: read the grades from a file
 **********************************************/
StudentGrade::StudentGrade(const File & file) : change(false)
{
	filename = file.filename;
	assert(filename && *filename);

	// open file
	ifstream fin(filename);
	if (fin.fail())
		return;

	// read name
	getline(fin, name);

	// read scores
	Item item;
	while (fin >> item.score >> item.weight)
		scores.push_back(item);

	// close up shop
	fin.close();
}

/**************************************************
 * DESTRUCTOR
 * Write the changes to the file if anything changed
 *************************************************/
StudentGrade::~StudentGrade()
{
	assert(filename && *filename);

	if (!change)
		return;

	// open file
	ofstream fout(filename);
	if (fout.fail())
		return;

	// header is the students name
	fout << name << endl;

	// write the data
	for (int iScore = 0; iScore < scores.size(); iScore++)
		fout << scores[iScore].score
		<< "\t"
		<< scores[iScore].weight
		<< endl;

	// make like a tree
	fout.close();
}

/****************************************
 * Edit only one score.
 ***************************************/
void StudentGrade::editScore(int iScoreEdit)
{
	float userInput;  // user inputed weight.

	assert(iScoreEdit >= 0 && iScoreEdit < scores.size());

	//
	// Score
	//

	// get new score
	cout << "Enter grade: ";
	cin >> userInput;

	// validate
	while (userInput > 100 || userInput < 0)
	{
		cout << "Invalid grade.  Select a number between 0 and 100: ";
		cin >> userInput;
	}
	setScore(iScoreEdit, userInput);

	//
	// Weight
	//

	// get the weight
	cout << "Enter the weight for the score or (0) for unchanged: ";
	cin >> userInput;

	// validate
	while (userInput > 1.0 || userInput < 0.0)
	{
		cout << "Invalid weight.  Select a number between 0 and 1: ";
		cin >> userInput;
	}
	if (userInput != 0.0)
		setWeight(iScoreEdit, userInput);

	return;
}


/*********************************************
 * Edit scores until user says he is done
 *******************************************/
bool StudentGrade::editScores(BellLaPadula b)
{
	// different views based on permissions
	bool isAuthorized = b.isFileAccessible(name);

	// Give the user some feedback
	cout << "Editing the scores of "
		<< name
		<< endl;

	// display score list
	cout << "Score list\n";

	// column headings only necessary with permissions
	if (isAuthorized)
	{
		cout << "\tScore \tWeight\n";
	}

	for (int iScore = 0; iScore < scores.size(); iScore++)
	{
		cout << "(" << iScore + 1 << ")"
			<< "\t";

		// show score/weight if authorized
		if (isAuthorized)
		{
			float score = getScore(iScore);
			float weight = getWeight(iScore);
			cout << score << "%"
				<< "\t"
				<< weight;
		}
		cout << endl;

	}
	cout << "(0)\tExit\n";

	// prompt
	bool done = false;
	while (!done)
	{
		// prompt
		int iScoreEdit;
		cout << "Which score would you like to edit (0-"
			<< scores.size()
			<< "): ";
		cin >> iScoreEdit;

		// validate score number
		while (iScoreEdit > scores.size() || iScoreEdit < 0)
		{
			cout << "Invalid number.  Select a number between 0 and "
				<< scores.size()
				<< ": ";
			cin >> iScoreEdit;
		}

		// from 1 based to 0 based
		iScoreEdit--;

		// edit the score
		if (iScoreEdit != -1)
		{
			// edit score
			editScore(iScoreEdit);

			// continue
			char response;
			cout << "Do you want to edit another score? (Y/N) ";
			cin >> response;
			done = (response == 'N' || response == 'n');
		}
		else
			done = true;
	}

	return isAuthorized;
}

/************************************************
 * Display scores
 ***********************************************/
void StudentGrade::displayScores()
{
	if (scores.size() == 0)
		return;

	// name
	cout << "Student name:\n\t"
		<< name
		<< endl;

	// grade
	cout << "Grade:\n\t"
		<< getNumberGrade() << "%"
		<< " : "
		<< getLetterGrade()
		<< endl;

	// detailed score
	cout << "Detailed score:\n"
		<< "\tScore \tWeight\n";
	for (int iScore = 0; iScore < scores.size(); iScore++)
		cout << "\t"
		<< getScore(iScore) << "%"
		<< "\t"
		<< getWeight(iScore)
		<< endl;

	// done
	return;
}

/***************************************************
 * Letter Grade include A- and C+
 ***************************************************/
string StudentGrade::getLetterGrade()
{
	const char chGrades[] = "FFFFFFDCBAA";
	int nGrade = (int)getNumberGrade();

	// paranioa will destroy ya
	assert(nGrade >= 0.0 && nGrade <= 100.0);

	// Letter grade
	string s;
	s += chGrades[nGrade / 10];

	// and the + and - as necessary
	if (nGrade % 10 >= 7 && nGrade / 10 < 9 && nGrade / 10 > 5)
		s += "+";
	if (nGrade % 10 <= 2 && nGrade / 10 < 10 && nGrade / 10 > 5)
		s += "-";

	return s;
}

/***************************************************
 * Number grade guarenteed to be between 0 - 100
 ***************************************************/
float StudentGrade::getNumberGrade()
{
	// add up the scores
	float possible = 0.0;
	float earned = 0.0;
	for (int iScore = 0; iScore < scores.size(); iScore++)
	{
		earned += scores[iScore].score * scores[iScore].weight;
		possible += scores[iScore].weight;
	}

	if (possible == 0.0)
		return 0.0;
	else
		return (earned / possible);
}

/*****************************************************************
 *****************************************************************
 *                           INTERFACE                           *
 *****************************************************************
 *****************************************************************/
class Interface
{
public:
	Interface();

	void display();
	void interact(BellLaPadula b);
private:
	int promptForStudent();
	vector < StudentGrade > students;
};


/*************************************************
 * Prompt the user for which student it to be worked
 * with.  Return -1 for none
 *************************************************/
int Interface::promptForStudent()
{
	int iSelected;

	// prompt
	cout << "Which student's grade would you like to review?\n";
	for (int iStudent = 0; iStudent < students.size(); iStudent++)
		cout << '\t'
		<< iStudent + 1
		<< ".\t"
		<< students[iStudent].getName()
		<< endl;
	cout << "\t0.\tNo student, exit\n";
	cout << "> ";

	// get input
	cin >> iSelected;
	while (iSelected < 0 || iSelected > students.size())
	{
		cout << "Invalid selection.  Please select a number between 1 and "
			<< students.size()
			<< " or select -1 to exit\n";
		cout << ">";
		cin >> iSelected;
	}

	return --iSelected;
}

/***********************************************
 * update the student records interactively
 ***********************************************/
void Interface::interact(BellLaPadula b)
{
	int iSelected;
	while (-1 != (iSelected = promptForStudent()))
	{
		// edit grades as necessary
		bool isAuthorized = students[iSelected].editScores(b);

		// show the results if authorized
		if (isAuthorized)
		{
			students[iSelected].displayScores();
		}

		// visual separater
		cout << "---------------------------------------------------\n";
	}

	return;
}

/*****************************************************
 * CONSTRUCTOR
 * Populate the grades list from a file
 ****************************************************/
Interface::Interface()
{
	for (int i = 0; i < sizeof(files) / sizeof(File); i++)
	{
		StudentGrade student(files[i]);
		students.push_back(student);
	}
}

/**************************************************
 * DISPLAY
 * Display stuff
 *************************************************/
void Interface::display()
{
	for (int i = 0; i < students.size(); i++)
		students[i].displayScores();
}

/**************************************************************
 * USER
 * All the users currently in the system
 *************************************************************/
struct User
{
	const char *name;
	const char *password;
}
const users[] =
{
   { "Bob",  "passwordBob" },
   { "Hans", "passwordHans" },
   { "Sam",  "passwordSam" },
   { "Sue",  "passwordSue" },
   { "Sly",  "passwordSly" }
};

#define ID_INVALID -1

/**********************************************
 * authenticate the user
 *********************************************/
BellLaPadula authenticate()
{
	string name;
	bool isFound = false;
	// prompt for username
	cout << "Username: ";
	cin >> name;

	// prompt for password
	string password;
	cout << "Password: ";
	cin >> password;

	// search for username. If found, verify password
	for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
	{
		if (name == string(users[idUser].name) &&
			password == string(users[idUser].password))
		{
			isFound = true;
		}
	}
	// display error
	if (!isFound)
	{
		cout << "Failed to authenticate " << name << endl;
	}

	// Create then return BellLaPadula object
	BellLaPadula b(name);
	return b;
}

/*********************************************
 * Main:
 *  open files
 *  edit scores
 *  save files
 ********************************************/
int main()
{
	BellLaPadula b = authenticate();
	Interface interface;
	interface.interact(b);
	return 0;
}
