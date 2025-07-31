#include<fstream>
#include<iostream>
#include<math.h>
#include <SFML/Graphics.hpp>
using namespace std;
const float displacement = 40;
float rotationfunc(int degree)
{
	return degree * 3.14159 / 180.0;
}
bool ForwardFunc(float xpos, float ypos, int angle, int distance)
{
	xpos += distance * cos(rotationfunc(270 + angle));
	ypos += distance * sin(rotationfunc(270 + angle));

	return true;
}
bool BackwardFunc(float xpos, float ypos, int angle, int distance)
{
	xpos -= distance * cos(rotationfunc(270 + angle));
	ypos -= distance * sin(rotationfunc(270 + angle));

	return true;
}

sf::RectangleShape bk(float& xpos, float& ypos, int angle, int distance, sf::Color color, int thickness)
{
	sf::RectangleShape lectangularlines(sf::Vector2f(distance, thickness));
	lectangularlines.setPosition(sf::Vector2f(xpos, ypos));
	lectangularlines.setFillColor(color);
	lectangularlines.setOutlineColor(color);
	lectangularlines.rotate(angle + 90);
	xpos -= distance * cos(rotationfunc(270 + angle));
	ypos -= distance * sin(rotationfunc(270 + angle));
	return lectangularlines;
}

sf::RectangleShape fd(float& xpos, float& ypos, int angle, int distance, sf::Color color, int thickness)
{
	sf::RectangleShape lectangularlines(sf::Vector2f(distance, thickness));
	lectangularlines.setPosition(sf::Vector2f(xpos, ypos));
	lectangularlines.setFillColor(color);
	lectangularlines.setOutlineColor(color);
	lectangularlines.rotate(angle - 90);
	xpos += distance * cos(rotationfunc(270 + angle));
	ypos += distance * sin(rotationfunc(270 + angle));
	return lectangularlines;
}

int rt(int angle, int right)
{
	return angle + right;
}
int lt(int angle, int left)
{
	return angle - left;
}

sf::Color pickColor(int num)
{
	int colorvals[][3] = {
		{255, 0, 0},
		{0, 0, 255},
		{0, 255, 0},
		{255, 255, 0},
		{128, 0, 128},
		{255, 165, 0},
		{255, 192, 203},
		{165, 42, 42},
		{255, 255, 255},
		{128, 128, 128}
	};
	return sf::Color(colorvals[num][0], colorvals[num][1], colorvals[num][2]);
}

sf::CircleShape circle(float xpos, float ypos, int radius, sf::Color color, int thickness)
{
	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(color);
	shape.setOutlineThickness(thickness);
	shape.setPosition(xpos - radius, ypos - radius);
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	return shape;
}

void penUp(bool& pd)
{
	pd = false;
}
void penDown(bool& pd)
{
	pd = true;
}
void width(int& thickness, int newvalue)
{
	if (newvalue >= 1 && newvalue <= 3)
	{
		thickness = newvalue;
	}
}
void insertCharacter(char arr[], int& currentPosition, int asciiValue) {
	if (currentPosition >= 100) {
		return;
	}
	if (asciiValue == 8) {
		if (currentPosition > 0) {
			arr[currentPosition - 1] = '\0';
			currentPosition--;
		}
	}
	else if (asciiValue == 13) {
		arr[currentPosition] = '\0';
		currentPosition = 0;
	}
	else {
		arr[currentPosition] = static_cast<char>(asciiValue);
		currentPosition++;
	}
}
bool isSubstringAtPosition(const char* Uppertexts, const char* undertexts, int& position) {

	int startpos = position;
	while (Uppertexts[position] == ' ')
	{
		position++;
	}
	if (position < 0 || position + strlen(undertexts) > strlen(Uppertexts)) {
		return false;
	}
	for (int i = 0; undertexts[i] != '\0'; ++i) {
		char mainChar = tolower(Uppertexts[position]);
		position++;
		char subChar = tolower(undertexts[i]);
		if (mainChar != subChar) {
			position = startpos;
			return false;
		}
	}
	return true;
}
int convertDigitsToInt(const char* input, int& position) {
	int result = 0;
	bool digitFound = false;
	while (std::isspace(input[position])) {
		position++;
	}
	if (!std::isdigit(input[position])) {
		return -1;
	}
	while (std::isdigit(input[position])) {
		digitFound = true;
		result = result * 10 + (input[position] - '0');
		position++;
	}
	position = position;
	return digitFound ? result : -1;
}
int findColorIndex(const char* input, int& position) {
	const char* colors[] = { "red", "blue", "green", "yellow", "purple", "orange", "pink", "brown", "white", "gray" };
	while (std::isspace(static_cast<unsigned char>(input[position]))) {
		++position;
	}
	for (int i = 0; i < 10; ++i) {
		int colorLength = std::strlen(colors[i]);
		bool match = true;
		for (int j = 0; j < colorLength; ++j) {
			if (std::tolower(static_cast<unsigned char>(input[position + j])) !=
				std::tolower(static_cast<unsigned char>(colors[i][j]))) {
				match = false;
				break;
			}
		}
		if (match) {
			position += strlen(colors[i]);
			return i;
		}
	}
	return -1;
}
void copySubstringTo2DArray(char dest[][101], const char source[], int destRow, int startIndex, int endIndex) {
	if (destRow < 0 || destRow >= 39 || startIndex < 0 || endIndex >= 100 || startIndex > endIndex) {
		return;
	}
	int substringLength = endIndex - startIndex + 1;
	if (strlen(source) < (endIndex + 1 - startIndex)) {
		return;
	}
	strncpy_s(dest[destRow], sizeof(dest[destRow]), source + startIndex, substringLength);
	dest[destRow][substringLength] = '\0';
}
void addCommand(char commands[100][101], char newCommand[101]) {
	for (int i = 100 - 1; i > 0; --i) {
		strcpy_s(commands[i], 101, commands[i - 1]);
	}
	strcpy_s(commands[0], 101, newCommand);
}
void save(char commandHistory[100][101], string fileName)
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		return;
	}
	for (int i = 0; i < 100; ++i) {
		if (commandHistory[i][0] == '\0') {
			break;
		}
		outFile << commandHistory[i] << endl;
	}
	outFile.close();
}
int load(char commandHistory[100][101], string fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		return 0;
	}
	int linesinsight = 0;
	for (int i = 0; i < 100; ++i) {
		inFile.getline(commandHistory[i], 101);
		if (!inFile || commandHistory[i][0] == '\0') {
			break;
		}
		linesinsight++;
	}
	for (int i = linesinsight; i < 100; ++i) {
		commandHistory[i][0] = '\0';
	}
	inFile.close();
	return linesinsight;
}
int main()
{
	string filename = "";
	char commandHistory[100][101] = { 0 };
	sf::Color color = sf::Color::White;
	int angle = 0;
	int thickness = 1;
	char command[101] = { 0 };
	int currentPosition = 0;
	bool pd = true;

	sf::RenderWindow window(sf::VideoMode(700, 530), "SFML works!");
	int circlenum = 0;
	int linenum = 0;
	sf::CircleShape shape, circlesarray[100];
	sf::RectangleShape linearray[100];
	float xpos = 250.0f,
		ypos = 250.0f;
	float cursor_right_hand_x, cursor_right_hand_y, cursor_left_hand_x, cursor_left_hand_y;

	sf::Vertex line[2];
	sf::Vertex line2[2];

	sf::Vertex cursor1[2];
	cursor1[0].position = sf::Vector2f(0, 500);
	cursor1[0].color = color;
	cursor1[1].position = sf::Vector2f(700, 500);
	cursor1[1].color = color;

	sf::Vertex cursor2[2];
	cursor2[0].position = sf::Vector2f(500, 0);
	cursor2[0].color = color;
	cursor2[1].position = sf::Vector2f(500, 500);
	cursor2[1].color = color;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::Text text;

	text.setFont(font);
	text.setString("");
	text.setCharacterSize(19);
	text.setPosition(0, 500);
	text.setFillColor(sf::Color::White);

	sf::Text error_message;
	error_message.setFont(font);
	error_message.setString("");
	error_message.setCharacterSize(10);
	error_message.setPosition(0, 100);
	error_message.setFillColor(sf::Color::Red);

	sf::Text errortext[16];
	for (int i = 0; i < 16; i++)
	{
		errortext[i].setFont(font);
		errortext[i].setString("");
		errortext[i].setCharacterSize(19);
		errortext[i].setPosition(500, i * 30);
		errortext[i].setFillColor(sf::Color::Red);
	}
	int pos;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				error_message.setString("");
				int ascii = event.text.unicode;
				if (ascii >= 65 && ascii <= 90)
				{
					ascii += 32;
				}
				insertCharacter(command, currentPosition, ascii);
				text.setString(command);
				if (ascii == 13)
				{
					pos = 0;
					bool read_command = true;
					bool rptcommand = false;
					int repeatCount = 0;
					char repeat_command[39][101] = { 0 };
					int repeat_command_count = 0;
					bool error = false;
					int repeat_command_exec = 0;
					bool execute_load = false;
					int loadcount = 0;
					while (read_command || rptcommand || repeatCount != 0 || (execute_load && loadcount != 0))
					{
						if (execute_load)
						{
							pos = 0;
							loadcount--;
							memcpy(command, commandHistory[loadcount], 101);
						}
						if (!read_command && !rptcommand && !execute_load)
						{

							if (repeatCount != 0 && repeat_command_exec == repeat_command_count * repeatCount)
							{
								break;
							}
							for (int i = 0; i < circlenum; i++)
							{
								window.draw(circlesarray[i]);
							}
							for (int i = 0; i < linenum; i++)
							{
								window.draw(linearray[i]);
							}
							window.draw(text);
							window.display();
							memcpy(command, repeat_command[repeat_command_exec % repeat_command_count], 101);
							pos = 0;
							repeat_command_exec++;
						}
						if (repeat_command_exec == 0 && repeat_command_count > 0)
						{
							if (command[pos] != ' ' && command[pos] != ']')
							{
								error = true;
								cout << endl << "1err" << endl;
								break;
							}
						}
						int start = pos, end = -1;
						if (!rptcommand && isSubstringAtPosition(command, "repeat", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							if (temp < 0)
							{
								error = true;
								break;
							}
							cout << temp << endl;
							repeatCount = temp;
							cout << repeatCount << endl;
							cout << endl << command[pos] << endl;
							if (isSubstringAtPosition(command, "[", pos))
							{
								rptcommand = true;
							}
							else
							{
								error = true;
								break;
							}
							start = pos;
						}
						else if (rptcommand && isSubstringAtPosition(command, "]", pos))
						{
							if (command[pos] == 0)
							{
								rptcommand = false;
								addCommand(commandHistory, command);
							}
							else {
								error = true;
								break;
							}
						}
						else if (isSubstringAtPosition(command, "fd", pos) || isSubstringAtPosition(command, "forward", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							if (temp < 0)
							{
								error = true;
								break;
							}
							cout << endl << command[pos] << endl;
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									if (ForwardFunc(xpos, ypos, angle, temp))
									{
										sf::RectangleShape rec = fd(xpos, ypos, angle, temp, color, thickness);
										if (pd)
										{
											if (linenum != 100)
											{
												linearray[linenum] = rec;
												linenum++;
											}
											else
											{
												for (int i = 1; i <= 99; i++)
												{
													linearray[i - 1] = linearray[i];
												}
												linearray[99] = rec;

											}
										}
									}
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "bk", pos) || isSubstringAtPosition(command, "backward", pos))
						{

							int temp = convertDigitsToInt(command, pos);

							if (temp < 0)
							{
								error = true;
								break;
							}
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									if (BackwardFunc(xpos, ypos, angle, temp))
									{
										sf::RectangleShape rec = bk(xpos, ypos, angle, temp, color, thickness);
										if (pd)
										{
											if (linenum != 100)
											{
												linearray[linenum] = rec;
												linenum++;
											}
											else
											{
												for (int i = 1; i <= 99; i++)
												{
													linearray[i - 1] = linearray[i];
												}
												linearray[99] = rec;

											}
										}
									}
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "rt", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							cout << temp << endl;
							if (temp < 0 && !(temp % 30 == 0 || temp % 45 == 0))
							{
								error = true;
								break;
							}
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									if (temp % 30 == 0 || temp % 45 == 0)
									{
										angle = rt(angle, temp);
									}
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "lt", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							if (temp < 0 && !(temp % 30 == 0 || temp % 45 == 0))
							{
								error = true;
								break;
							}
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									if (temp % 30 == 0 || temp % 45 == 0)
									{
										angle = lt(angle, temp);
										cout << "\nleftleft\n";
									}
								}
								else {
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "pu", pos))
						{
							cout << "penup\n";
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									penUp(pd);
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "pd", pos))
						{
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									penDown(pd);
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "color", pos))
						{
							if (command[pos] == ' ')
							{
								int c = findColorIndex(command, pos);
								if (c != -1)
								{
									if (!rptcommand)
									{
										if (command[pos] == 0)
										{
											if (!rptcommand && command[pos] == 0)
											{
												color = pickColor(c);
											}
										}
										else
										{
											error = true;
											break;
										}
									}
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "width", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							if (temp == -1)
							{
								error = true;
								break;
							}
							if (command[pos] == 0)
							{
								if (!rptcommand)
								{
									width(thickness, temp);
								}
								else
								{
									error = true;
									break;
								}
							}

							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "circle", pos))
						{
							int temp = convertDigitsToInt(command, pos);
							if (temp == -1)
							{
								error = true;
								break;
							}
							if (!rptcommand && pd)
							{
								if (command[pos] == 0 && temp >= 0 && temp < 125)
								{
									if (circlenum != 99)
									{
										circlesarray[circlenum] = circle(xpos, ypos, temp, color, thickness);
										circlenum++;
									}
									else
									{
										for (int i = 1; i <= 99; i++)
										{
											circlesarray[i - 1] = circlesarray[i];
										}
										circlesarray[circlenum] = circle(xpos, ypos, temp, color, thickness);
									}

								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (isSubstringAtPosition(command, "cs", pos))
						{
							if (!rptcommand)
							{
								if (command[pos] == 0)
								{
									circlenum = 0;
									linenum = 0;
								}
								else
								{
									error = true;
									break;
								}
							}
							end = pos - 1;
						}
						else if (!rptcommand && isSubstringAtPosition(command, "save", pos))
						{
							if (command[pos] == ' ')
							{
								while (command[pos] == ' ')
								{
									pos++;
								}
								int substringLength = strlen(command + pos);
								filename = string(command + pos, substringLength);
								if (filename == "")
								{
									error = true;
									break;
								}
								else
								{
									save(commandHistory, filename);
								}
							}
						}
						else if (!rptcommand && isSubstringAtPosition(command, "load", pos))
						{
							if (command[pos] == ' ')
							{
								while (command[pos] == ' ')
								{
									pos++;
								}
								int substringLength = strlen(command + pos);
								filename = string(command + pos, substringLength);
								if (filename == "")
								{
									error = true;
									break;
								}
								else
								{
									loadcount = load(commandHistory, filename);
									if (loadcount)
									{
										color = sf::Color::Red;
										angle = 0;
										thickness = 1;
										pd = true;
										circlenum = 0;
										linenum = 0;
										xpos = 250.0f;
										ypos = 250.0f;

										execute_load = true;
									}
								}
							}
						}
						else
						{
							error = true;
							error_message.setString("INVALID COMMAND");
						}
						if (!read_command && rptcommand)
						{
							copySubstringTo2DArray(repeat_command, command, repeat_command_count, start, end);
							puts(repeat_command[repeat_command_count]);
							repeat_command_count++;
						}
						read_command = false;
					}
					if (error)
					{
						error_message.setString("INVALID COMMAND");
					}
					else
					{
						if (!execute_load && repeat_command_exec == 0 && repeatCount == 0)
						{
							addCommand(commandHistory, command);
						}
					}
					for (int i = 0; i < 101; ++i) {
						command[i] = '\0';
					}
					cout << commandHistory[0][0] << (commandHistory[0][1]) << commandHistory[0][2];
					text.setString(command);
				}
			}
		}
		window.clear();
		cursor_right_hand_x = xpos + displacement * cos(rotationfunc(75 + angle));
		cursor_right_hand_y = ypos + displacement * sin(rotationfunc(75 + angle));
		cursor_left_hand_x = xpos + displacement * cos(rotationfunc(105 + angle));
		cursor_left_hand_y = ypos + displacement * sin(rotationfunc(105 + angle));
		line[0].position = sf::Vector2f(xpos, ypos);
		line[0].color = color;
		line[1].position = sf::Vector2f(cursor_right_hand_x, cursor_right_hand_y);
		line[1].color = color;
		line2[0].position = sf::Vector2f(xpos, ypos);
		line2[0].color = color;
		line2[1].position = sf::Vector2f(cursor_left_hand_x, cursor_left_hand_y);
		line2[1].color = color;

		window.draw(line, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);

		window.draw(cursor1, 2, sf::Lines);
		window.draw(cursor2, 2, sf::Lines);
		for (int i = 0; i < circlenum; i++)
		{
			window.draw(circlesarray[i]);
		}
		for (int i = 0; i < linenum; i++)
		{
			window.draw(linearray[i]);
		}
		for (int i = 0; i < 16; i++)
		{
			errortext[i].setString(commandHistory[i]);
			window.draw(errortext[i]);
		}
		window.draw(text);
		window.draw(error_message);
		window.display();
	}

	return 0;
}