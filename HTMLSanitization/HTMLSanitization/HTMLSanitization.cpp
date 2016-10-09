/***********************************************************************
* Program:
*    Ponder 04, Sanitization
*    Brother WilsonDa, CS470
* Author:
*    John Vehikite
* Summary:
*    This program contains a white list to sanitize HTML
************************************************************************/

#include <string>
#include <iostream>
#include <stack>

int main()
{
	std::string input;
	std::string output;
	
	// HTML tags follow a LIFO structure, so we will use a stack to
	// keep track of the closing tags
	std::stack<std::string> closeTags;

	// list of valid tags per instructions
	std::string validTags[] = { "a", "abbr", "acronym", "b", "blockquote",
		"cite", "code", "del", "em", "i", "q", "strike", "strong" };
	
	// do while continues until the user enters quit
	// that will cause keepPlaying to be assigned as false
	bool keepPlaying = true;
	do
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		// break out of do while
		if (input == "quit")
		{
			keepPlaying = false;
			break;
		}

		int begBracket = input.find('<');
		
		// print Plain text if no brackets
		if (begBracket == std::string::npos)
		{
			output = input;
		}

		// if there is at least one opening bracket
		else
		{
			// needed to know if '>' or "&gt;" should be printed
			bool needsCloseTag = true;
			
			// iterate through each character in input
			for (std::string::size_type i = 0; i < input.size(); ++i) 
			{
				std::string::size_type currentpos = i;
				
				// this block determines whether '<' or "&lt;" should be printed
				if (input[i] == '<')
				{
					std::string::size_type startpos = currentpos + 1;
					std::string::size_type endpos = input.find('>', currentpos);
					
					// tag is just the text between '<' and '>'
					std::string tag = input.substr(startpos, endpos - startpos);
					
					// if hyperlink
					if (tag.substr(0, 2) == "a ")
					{
						output += '<';
						
						// if valid tag, push onto stack
						closeTags.push("a");
						needsCloseTag = true;
					}

					// if '<' is part of a closing tag
					else if (tag[0] == '/')
					{
						// if closing tag has corresponding opening tag, output '<'
						if (!closeTags.empty() && tag.substr(1) == closeTags.top())
						{
							output += '<';

							// since we closed the tag, pop tag off stack
							closeTags.pop();
							needsCloseTag = true;
						}
						else
						{
							output += "&lt;";
							needsCloseTag = false;
						}
					}
					// if not part of hyperlink or part of closing tag, search for tag in validTags
					else
					{
						bool tagFound = false;
						for (int j = 0; j < sizeof(validTags) / sizeof(validTags[0]); j++)
						{
							// ouput '<' and push tag to stack if found
							if (tag == validTags[j])
							{
								output += "<";
								closeTags.push(tag);
								needsCloseTag = true;
								tagFound = true;
							}
						}
						if (!tagFound)
						{
							output += "&lt;";
							needsCloseTag = false;
						}
					}
				} // end of '>' if statement

				else if (input[i] == '>')
				{
					if (needsCloseTag)
					{
						output += ">";
					}
					else
					{
						output += "&gt;";
					}
				}
				
				// if neither '<' or '>'
				else
				{
					output += input[i];
				}
			}
		}
		// close dangling tags
		while (!closeTags.empty())
		{
			output += "</" + closeTags.top() + ">";
			closeTags.pop();
		}
		// output to user
		std::cout << "\t" << output << std::endl;

		// reset output
		output = "";
	} while (keepPlaying);

	std::cout << "\tquit\n";
	return 0;
}