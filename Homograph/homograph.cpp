/***********************************************************************
* Program:
*    Week 13, Homographs
*    Brother Wilson, CS470
* Author:
*    John Vehikite
* Summary:
*    This program program detects file path homograph attacks. This is 
*    accomplished by prompting the user for two filenames and then 
*    displaying whether the two filenames are homographs.
*    
*    One common form of the homograph attack is for the user to attempt 
*    to access a forbidden resource. The programmer may attempt to prevent 
*    such requests by creating a blacklist of forbidden files. The problem 
*    arises when the attacker finds a way to specify the forbidden file 
*    that circumvents the blacklist. This is done, of course, with a 
*    homograph attack.
************************************************************************/

#include <string>
#include <iostream>

std::string getDir(std::string filename);

int main()
{
	std::string file1;
	std::string file2;
	
	// holds path without "../" and "./"
	std::string path;
	
	std::cout << "Specify the first filename:  ";
	std::cin >> file1;

	path = getDir(file1);

	std::cout << "Specify the second filename: ";
	std::cin >> file2;

	// output
	std::cout << "The files are " 
		
		// if file1 == file2, they are homographs
		<< ((path == getDir(file2)) ? "" : "NOT ") 
		
		<< "homographs\n";
	
    return 0;
}

/**********************************************
* GETDIR
* outputs file path without "../" and "./"
* not allowed to use realdir() or
* canonicalize_file_name()
**********************************************/
std::string getDir(std::string filename)
{
	// holds output
	std::string dir = "";
	
	// holds number of slashes
	// used in switch below
	int numSlashes = 0;

	// iterate through each char in filename
	for (int i = 0; i < filename.length(); i++)
	{
		// add '/' at the beginning of dir
		if (i == 0 && filename[i] != '/')
		{
			dir += "/";
		}

		// logic to catch "./" and "../"
		if (filename[i] == '.')
		{
			switch (filename[i + 1])
			{
			// current directory operator "./"
			case '/':
				// don't add to dir
				// move iterator to '/'
				i += 1;
				break;

			// parent directory operator "../"
			case '.':
				// move iterator to '/'
				i += 2;

				// if parent dir is '/', stay at '/'
				// numSlashes is decremented
				if (--numSlashes <= 1)
				{
					dir = "/";
					break;
				}

				// if parent dir is not '/'
				else
				{
					int tempSlashes = 0;
					std::string tempDir = "";
					int j = 0;

					// copy dir until decremented numSlashes
					while (tempSlashes != numSlashes)
					{
						if (dir[j] == '/')
						{
							tempSlashes++;
						}
						tempDir += dir[j++];
					}
					// copy tempDir to dir
					dir = tempDir;
					break;
				}
			}
			// go to end of loop
			continue;
		}

		// add char to dir
		if (filename[i] == '/')
		{
			numSlashes++;
		}
		dir += filename[i];
	}
	return dir;
}

