#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>

void fillGrid(std::array<char, 36>&);
void shuffleGrid(std::array<char, 36>&);
void showGrid(const std::array<char, 36>&, const bool&&);
void showHint(unsigned short&&, unsigned short*);
const bool&& isValid(const unsigned short&);

//test check for garbage input
void testCheck()
{
	unsigned short x, i = 0;
	while(i < 20)
	{
		std::cout << "enter from 1 to 6: ";
		std::cin >> x;
		if(!std::cin.fail())	//returns true if failed
		{
			if(isValid(x))
				std::cout << x << " is valid\n";
			else
				std::cout << x << " is invalid\n";
		}
		else
		{
			std::cout << "Input is invalid\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		i++;
	}
	std::cin.get();
}
//end test check

int main()
{
	std::array<char, 36> grid;
	unsigned short inputValues[4];
	bool gameOver = false;

	fillGrid(grid);
	shuffleGrid(grid);

	//while(!gameOver)
	//{
	//	showGrid(grid, true);
	//	showHint(1, inputValues);
	//	showHint(2, inputValues);
	//	//TODO: show grid with 2 guesses
	//	//TODO: pause game, clear screen, start over
	//	//TODO: remove correctly guessed letters by replacing elements in array with ' ' and restricting access to them
	//	//TODO: add game over logic
	//}

	//test check for garbage input
	testCheck();
	//end test check
}

void fillGrid(std::array<char, 36>& grid)
{
	for(int i = 0, j = 65; i < 36; i += 2, j++)
	{
		grid[i] = j;
		grid[i + 1] = j;
	}
}

void shuffleGrid(std::array<char, 36>& grid)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(grid.begin(), grid.end(), std::default_random_engine(seed));
}

void showGrid(const std::array<char, 36>& grid, const bool&& isHidden)
{
	for(int i = 0; i < 36; i++)
	{
		if(i > 0 && i % 6 == 0)
			std::cout << std::endl;

		if(isHidden)
			std::cout << "* ";
		else
			std::cout << grid[i] << " ";
	}
	std::cout << std::endl;
}

void showHint(unsigned short&& selection, unsigned short* inputValues)
{
	switch(selection)
	{
		case 1:
			std::cout << "1st selection\n";
			break;
		case 2:
			std::cout << "2nd selection\n";
			selection++;
			break;
	}

RowSelection:
	std::cout << "Enter row number: ";
	std::cin >> inputValues[selection - 1];
	//TODO: check for garbage input
	if(!isValid(inputValues[selection - 1]))
		goto RowSelection;

ColSelection:
	std::cout << "Enter column number: ";
	std::cin >> inputValues[selection];
	//TODO: check for garbage input
	if(!isValid(inputValues[selection]))
		goto ColSelection;
}

const bool&& isValid(const unsigned short& value)
{
	return value >= 1 && value <= 6;
}
