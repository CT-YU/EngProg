// ===========   Eng Prog Project   ==================
// Directory set to "C://workspace//Test"

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>
#include<cmath>


using std::cout;
using std::cin;
using std::stack;
using std::string;
using std::vector;
using std::endl;
using std::ifstream;
using std::list;
using std::istringstream;
using std::map;
using std::pair;



void get_SubFolders(const string&, vector<string>&, stack<string>&);
void files_in_directory(const string&, vector<string>&);
void readFile_byWord(ifstream&, list<string>&);
void search_word_in_Lines(const string&, const string&);
int patternMatch(const string&, const string&);
void search_pattern_in_Lines(const string&, const string&);
void word_frequency_in_file(const string, map<string, int>&);
bool sortByVal(const pair<string, int>&, const pair< string, int >&);
bool sortByVal_2(const pair<string, float>&, const pair<string, float>&);
void rank_order_by_frequency(const map<string, int>, vector<pair<string, int>>&);
void check_balance_in_line(const string);
void TF_IDF(const string&, const vector<string>&, vector<pair<string, float>>&);
float term_Frequency(const string&, const string&);



int main()
{	
	// set Root directory to "C://workspace//Test"
	//string folder = "C://Eng Prog Project";
	string folder = "C://workspace//Test";
	vector<string> All_Dir;
	stack<string> stack_Folders;
	string curr_dir;
	vector<string> All_Files;

	All_Dir.push_back(folder);

	// Explore all subfolders under given root directory.
	// Store directories into a vector<string>.
	get_SubFolders(folder, All_Dir, stack_Folders);
	while (!stack_Folders.empty())
	{
		curr_dir = stack_Folders.top();
		stack_Folders.pop();
		get_SubFolders(curr_dir, All_Dir, stack_Folders);
	}

	int count_Dir = (int)All_Dir.size();
	cout << " Numbers of Folders = " << count_Dir << endl;
	cout << " We will walk thorugh all sub-dirctory under " << folder << endl;
	for (int i = 0; i < count_Dir; i++)
	{
		cout << All_Dir[i] << endl;
	}

	cout << endl << endl;


	// Using All_Dir to get all txt files.
	// Store files path into All_Files.

	auto itr = All_Dir.begin();
	while (itr != All_Dir.end())
	{
		files_in_directory(*itr, All_Files);
		itr++;
	}
	int count_Files = (int)All_Files.size();
	cout << " Numbers of Files = " << count_Files << endl;
	cout << endl << endl << endl;




	//  ========================== Part1 & Part2 ===============================================
	string searchWord;
	list<string> wordList;
	auto itr2 = All_Files.begin();
	int freq = 0;

	cout << "  ######   Part1 and Part2   ###### " << endl << endl;
	cout << " Please Enter a word to Search (upper/lower case are diffrent)  " << endl;
	cout << " Note that we define words to be divided by White Space." << endl;
	cout << " So, e.g. \"Andrew\" and \"Andrew,\" are 2 different words." << endl << endl;
	cout << " Input: ";
	cin >> searchWord;


	while (itr2 != All_Files.end())
	{
		ifstream text_file(*itr2);
		wordList.clear();
		readFile_byWord(text_file, wordList);
		// Count the freauency
		freq = 0;
		auto curr = wordList.begin();

		while (curr != wordList.end())
		{
			if (*curr == searchWord)
				freq++;

			curr++;
		}
		cout << endl;
		cout << " Freq of \"" << searchWord << "\"" << " in " << *itr2 << " :  " << freq << endl << endl;

		if (freq != 0)
		{
			cout << endl;
			search_word_in_Lines(searchWord, *itr2);
		}

		itr2++;
	}

	cout << " ----Finish Searching All Files.----" << endl;
	cout << endl;
	cout << endl;




	//  ========================== Part3 =======================================================
	string searchPattern;
	cout << "  ######   Part3   ###### " << endl << endl;
	cout << " Please Enter a pattern to Search (upper/lower case are diffrent)  " << endl;
	cout << " Be aware of '*' and '?' " << endl;
	cout << " We are searching for lines that CONTAIN pattern by Words, not chars (i.e. divide by Whilte Space)" << endl;
	cout << " (e.g.) \"i*s\" will match \"is\" by words, but not \"lives\"  by chars  " << endl;
	cout << endl;
	cout << " Input: ";
	cin >> searchPattern;
	string searchPattern_modified = "* " + searchPattern + " *";      // add "* ", " *" before and after pattern
																	// Lines could CONTAIN pattern in terms of words


	for (auto itr3 = All_Files.begin(); itr3 != All_Files.end(); itr3++)
	{
		search_pattern_in_Lines(searchPattern_modified, *itr3);
	}

	cout << endl;
	cout << " ----End of Searching Pattern.----" << endl << endl << endl;


	//======================================== Part4 =====================================================
	cout << "  ######   Part4   ###### " << endl << endl << endl;

	cout << "  Ranking the Word List : " << endl << endl;

	map<string, int> frequency_table;
	auto itr4 = All_Files.begin();
	while (itr4 != All_Files.end())
	{
		word_frequency_in_file(*itr4, frequency_table);
		itr4++;
	}


	vector<pair<string, int>> vec_word_frequecny_pair;
	rank_order_by_frequency(frequency_table, vec_word_frequecny_pair);

	for (auto itr = vec_word_frequecny_pair.begin(); itr != vec_word_frequecny_pair.end(); itr++)
	{
		cout << itr->first << " : " << itr->second << endl;
	}

	cout << endl << " ----End of word frequency table.----" << endl << endl << endl << endl;



	//======================================== Part5 =====================================================
	cout << "  ######   Part5   ###### " << endl << endl;
	cout << "  Check Unbalnaced Lines : " << endl;
	for (auto itr = All_Files.begin(); itr != All_Files.end(); itr++)
	{
		check_balance_in_line(*itr);
	}
	cout << endl << " ----End of checking balance.----" << endl << endl<< endl;



	//======================================== Part6 =====================================================
	
	cout << "  ######   Part6   ###### " << endl << endl;
	
	string searchTerm;
	cout << "  Please enter a word for the most matching file : ";
	cin >> searchTerm;
	cout << endl ;
	cout << "   The Tf-Idf for \"" << searchTerm << "\" in each files :" << endl <<endl;
	cout << " =======================================  " << endl;

	//TF_ITF(searchTerm, All_Files);

	vector<pair<string, float>> files_tfidf;

	TF_IDF(searchTerm, All_Files, files_tfidf);

	for (auto itr = files_tfidf.begin(); itr != files_tfidf.end(); itr++)
	{
		cout << itr->first << " :  " << itr->second << endl;
	}

	cout << " =======================================  " << endl;
	cout << endl << " ----End of TF-IDF ranking.----" << endl << endl;


	return 0;
}



// ========   Function to comput TF for given searchword in single file ==================================

float term_Frequency(const string& searchTerm, const string& file)
{
	float Tf = 0;
	// Definition: tf(i,j) is (occurence of the word i in file j)/ (total # of words in file j)
	ifstream rf(file);
	string word;
	float count_total_word = 0;
	float count_searchTerm = 0;

	while (rf >> word)
	{
		count_total_word++;
		if (word == searchTerm)
		{
			count_searchTerm++;
		}
	}

	Tf = count_searchTerm /( count_total_word+1);
	return Tf;
}



// ========  Function to compute TF-IDF for given searchword in all files ================
//  rank them in a vector of pairs by TF-IDF value 

void TF_IDF( const string& searchWord, const vector<string>& file_list, vector<pair<string,float>>& vecTFIDF)
{
	float Idf = 0;
	// Definition: tf(i,j) is (occurence of the word i in file j)/ (total # of words in file j)
	float count_file_with_word = 0;
	float count_files = 0;
	auto itr = file_list.begin();
	while (itr != file_list.end())
	{
		ifstream rf(*itr);
		string word;
		while (rf >> word)
		{
			if (word == searchWord)
			{
				count_file_with_word++;
				break;
			}
		}
		count_files++;
		itr++;
	}

	Idf = log(count_files / (count_file_with_word + 1));

	for (auto itr1 = file_list.begin(); itr1 != file_list.end(); itr1++)
	{  
		float tf = term_Frequency(searchWord, *itr1);
		float tf_idf = Idf * tf;
		vecTFIDF.push_back({ *itr1,tf_idf });
	}

	sort(vecTFIDF.begin(), vecTFIDF.end(), sortByVal_2);

}


// ======== Function to check () [] {} balance for each line in one given file ============
// using stack

void check_balance_in_line(const string file)
{	
	ifstream rf(file);
	string line;
	int line_index = 0;
	stack<char> stack;
	while (std::getline(rf, line))
	{	
		line_index++;

		for (auto itr = line.begin(); itr != line.end(); itr++)
		{
			if ((*itr == '(') ||( *itr == '{' )||( *itr == '['))
				stack.push(*itr);
			else if (*itr == ')')
			{
				if (stack.top() == '(')
					stack.pop();
				else
				{
					cout << " ====================================" << endl;
					cout << " " << file << endl;
					cout << " Line : " << line_index << endl;
					cout << " " << line << endl;
					cout << " ====================================" << endl;
					break;
				}
			}

			else if (*itr == ']')
			{
				if (stack.top() == '[')
					stack.pop();
				else
				{
					cout << " ====================================" << endl;
					cout << " " << file << endl;
					cout << " Line : " << line_index << endl;
					cout << " " << line << endl;
					cout << " ====================================" << endl;
					break;
				}
			}

			else if (*itr == '}')
			{
				if (stack.top() == '{')
					stack.pop();
				else
				{
					cout << " ====================================" << endl;
					cout << " " << file << endl;
					cout << " Line : " << line_index << endl;
					cout << " " << line << endl;
					cout << " ====================================" << endl;
					break;
				}
			}
		}
	}

	return;
}



// ========== Function to define sorting rules =================================

bool sortByVal_2(const pair<string, float>& a, const pair<string, float>& b)
{
	return (a.second > b.second);
}

bool sortByVal(const pair<string, int>& a, const pair<string, int>& b)
{
	return (a.second > b.second);
}



// ================ Function to rank word list by frequency of occurrence ===============

void rank_order_by_frequency(const map<string, int>maptable, vector<pair<string, int>>& vec)
{

	for (auto itr = maptable.begin(); itr != maptable.end(); itr++)
	{
		vec.push_back(make_pair(itr->first, itr->second));
	}

	sort(vec.begin(), vec.end(), sortByVal);

}



// ================ Function to build word list ===================================
// using map

void word_frequency_in_file(const string file, map<string, int>& table)
{
	string word;
	ifstream rw(file);
	int temp = 0;
	while (rw >> word)
	{
		if (table.find(word) == table.end())
			table.insert({ word,1 });
		else
		{
			temp = table.find(word)->second;
			table.erase(table.find(word));
			table.insert({ word,temp + 1 });
		}
	}
	return;
}


// ========== Function to perform pattern match =============
// dynamic programming, filling up bottom-up table

int patternMatch(const string& line, const string& pattern)
{
	int ls = line.length();
	int ps = pattern.length();

	bool** table = new bool* [ls + 1];
	for (int i = 0; i < ls + 1; i++)
	{
		table[i] = new bool[ps + 1];
		for (int j = 0; j <= ps; j++)
			table[i][j] = false;
	}
	table[0][0] = true;

	for (int i = 0; i < ps; i++)
	{
		if (pattern[i] != '*')
			break;
		table[0][i + 1] = true;
	}

	for (int i = 0; i < ls; i++)
		for (int j = 0; j < ps; j++)
		{
			if (pattern[j] == '*')
			{
				table[i + 1][j + 1] = table[i + 1][j] || table[i][j + 1];
			}
			else if (pattern[j] == '?')
			{
				table[i + 1][j + 1] = table[i][j] || table[i][j + 1];
			}
			else if (pattern[j] == line[i])
			{
				table[i + 1][j + 1] = table[i][j];
			}
			else {
				table[i + 1][j + 1] = false;
			}
		}

	return table[ls][ps];

}


// =======  Function to perform pattern search in each line of a given file ==========

void search_pattern_in_Lines(const string& pattern, const string& file)
{
	string line;
	int line_index = 0;
	ifstream rf(file);
	while (std::getline(rf, line))
	{
		line_index++;
		if (patternMatch(" " + line + " ", pattern))    
		{
			cout << "   =========================================   " << endl;
			cout << "   file: " << file << endl;
			cout << "   (line : " << line_index << ")" << endl;
			cout << "   " << line << endl;
			cout << "   =========================================   " << endl;

		}
	}


	return;

}


// =========== Function to search word in each line of a given file ===========

void search_word_in_Lines(const string& word, const string& file)
{
	string line;
	string single_word;
	int line_index = 1;
	ifstream rf(file);
	while (std::getline(rf, line))
	{
		istringstream line_stream(line);
		while (line_stream >> single_word)
		{
			if (single_word == word)
			{
				cout << "   =========================================   " << endl;
				cout << "   line : " << line_index << endl;
				cout << "   " << line << endl;
				cout << "   =========================================   " << endl;
				break;
			}
		}

		line_index++;
	}
}


// ======== Function to explore folders in a given directory =================
// store them to a stack, then the new folder directory can be used later.

void get_SubFolders(const string& folder, vector<string>& subFolders, stack<string>& stack)
{

	WIN32_FIND_DATAA fileFindData;
	string nameWC = folder + "//*";
	HANDLE hFind = ::FindFirstFileA(nameWC.c_str(), &fileFindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "folder path error...." << endl;
		return;
	}

	do
	{
		if (fileFindData.cFileName[0] == '.')
		{
			continue; // filter the '..' and '.' in the path
		}

		if (fileFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			subFolders.push_back(folder + "//" + fileFindData.cFileName);
			stack.push(folder + "//" + fileFindData.cFileName);
		}

	} while (::FindNextFileA(hFind, &fileFindData));

	FindClose(hFind);
	return;
}




// =========== Function to explore txt files in a given directory =============
// store them (path) into a vector of string

void files_in_directory(const string& dir, vector<string>& vec_Files)
{
	string file_dir = dir + "//*.txt";
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(file_dir.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			vec_Files.push_back(dir + "//" + data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}



// ====== Functino to read words in a given file ===========
// Store them into a list of string 

void readFile_byWord(ifstream& text_file, list<string>& wList)
{
	string word;
	while (text_file >> word)                       //Note: white space will be skipped here. white space " " is a string, but not stored into wList.
	{
		wList.push_front(word);
	}

	return;

}