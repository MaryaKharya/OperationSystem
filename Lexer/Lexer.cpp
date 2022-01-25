#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "TokenTypes.h"

using namespace std;


struct Info
{
	TokenType typeToken;
	string lexema;
	int strNum;
	int position;
};


int main()
{
	ifstream fileIn("Input.txt");
	ofstream fileOut("Output.txt");
	std::string str, token;
	int strNum = 0, i = 0;
	vector<Info> tokens;
	string lexema;
	while (std::getline(fileIn, str))
	{
		strNum++;
		while (i < str.size())
		{
			switch (str[i])
			{
			case '+':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::PLUS, lexema, strNum, (int)i });
				break;
			}
			case '-':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::MINUS, lexema, strNum, (int)i });
				break;
			}
			case '*':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::ASTERISK, lexema, strNum, (int)i });
				break;
			}
			case '/':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::FORWARD_SLASH, lexema, strNum, (int)i });
				break;
			}
			case ':':
			{
				if (i + 1 < str.size())
				{
					if (str[i + 1] == '=')
					{
						lexema = ":=";
						i += 2;;
						tokens.push_back({ TokenType::ASSIGMENT, lexema, strNum, (int)i });
					}
					else
					{
						lexema = str[i];
						i++;
						tokens.push_back({ TokenType::COLON, lexema, strNum, (int)i });
					}
				}
				else
				{
					lexema = str[i];
					i++;
					tokens.push_back({ TokenType::COLON, lexema, strNum, (int)i });
				}
				break;
			}
			case '=':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::EQUALS, lexema, strNum, (int)i });
				break;
			}
			case '<':
			{
				if (i + 1 < str.size())
				{
					if (str[i + 1] == '>')
					{
						lexema = "<>";
						i += 2;
						tokens.push_back({ TokenType::INEQUALITY, lexema, strNum, (int)i });
						break;
					}
					else if (str[i + 1] == '=')
					{
						lexema = "<=";
						i += 2;
						tokens.push_back({ TokenType::LESS_EQUAL, lexema, strNum, (int)i });
					}
					else
					{
						lexema = str[i];
						i++;
						tokens.push_back({ TokenType::LESS, lexema, strNum, (int)i });
					}
				}
				else
				{
					lexema = str[i];
					i++;
					tokens.push_back({ TokenType::LESS, lexema, strNum, (int)i });
				}
				break;
			}
			case '>':
			{
				if (i + 1 < str.size())
				{
					if (str[i + 1] == '=')
					{
						lexema = ">=";
						i += 2;
						tokens.push_back({ TokenType::GREATER_EQUAL, lexema, strNum, (int)i });
					}
					else
					{
						lexema = str[i];
						i++;
						tokens.push_back({ TokenType::GREATER, lexema, strNum, (int)i });
					}
				}
				else
				{
					lexema = str[i];
					i++;
					tokens.push_back({ TokenType::GREATER, lexema, strNum, (int)i });
				}
				break;
			}
			case '.':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::DOT, lexema, strNum, (int)i });
				break;
			}
			case ',':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::COMMA, lexema, strNum, (int)i });
				break;
			}
			case '(':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::OPEN_PARENTHESIS, lexema, strNum, (int)i });
				break;
			}
			case ')':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::CLOSE_PARENTHESIS, lexema, strNum, (int)i });
				break;
			}
			case '[':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::OPEN_SQUARE_BRACKET, lexema, strNum, (int)i });
				break;
			}
			case ']':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::CLOSE_SQUARE_BRACKET, lexema, strNum, (int)i });
				break;
			}
			case '{':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::OPEN_CURLY_BRACE, lexema, strNum, (int)i });
				while ((str[i] != '}'))
				{
					i++;
					std::cout << str[i];
					if (i == str.size())
					{
						if ((fileIn.eof()))
						{
							break;
						}
						if (std::getline(fileIn, str))
						{
							i = 0;
						}
					}
				}
				break;
			}
			case '}':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::CLOSE_CURLY_BRACE, lexema, strNum, (int)i });
				break;
			}
			case ';':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::SEMICOLON, lexema, strNum, (int)i });
				break;
			}
			case '\'':
			{
				int startI = i;
				lexema = str[i];
				i++;
				while (str[i] != '\'')
				{
					lexema += str[i];
					i++;
				}
				lexema += str[i];
				i++;
				if (lexema.size() == 3)
				{
					tokens.push_back({ TokenType::CHAR, lexema, strNum, startI });
				}
				else
				{
					tokens.push_back({ TokenType::STRING, lexema, strNum, startI });
				}
			}

			case ' ':
			{
				lexema = str[i];
				i++;
				tokens.push_back({ TokenType::SPACE, lexema, strNum, (int)i });
				break;
			}
			default:
				if (isdigit(str[i]))
				{
					lexema = str[i];
					i++;
					int startI = i;
					while ((isdigit(str[i])) || (str[i] == 'e') || (str[i] == 'E') || (str[i] == '.'))
					{
						lexema += str[i];
						i++;
					}
					if ((str[i] == 'e') || (str[i] == 'E'))
					{
						i++;
						if ((str[i] == '+') || (str[i] == '-') || (isdigit(str[i])))
						{
							lexema += str[i];
							i++;
							while ((isdigit(str[i])))
							{
								lexema += str[i];
								i++;
							}
							if (isalpha(str[i]))
							{
								lexema += str[i];
								i++;
								while ((isalpha(str[i])) || (isalpha(str[i])))
								{
									lexema += str[i];
									i++;
								}
								tokens.push_back({ TokenType::ERROR, lexema, strNum, startI });
							}
							else
							{
								tokens.push_back({ TokenType::DOUBLE, lexema, strNum, startI });
							}

						}
						else
						{
							tokens.push_back({ TokenType::ERROR, lexema, strNum, startI });
						}
					}
					else if ((str[i] == '.'))
					{
						while ((isdigit(str[i])))
						{
							lexema += str[i];
							i++;
						}
						if (isalpha(str[i]))
						{
							lexema += str[i];
							i++;
							while ((isalpha(str[i])) || (isalpha(str[i])))
							{
								lexema += str[i];
								i++;
							}
							tokens.push_back({ TokenType::ERROR, lexema, strNum, startI });
						}
						else
						{
							tokens.push_back({ TokenType::DOUBLE, lexema, strNum, startI });
						}
					}
					else
					{
						if (isalpha(str[i]))
						{
							lexema += str[i];
							i++;
							while ((isalpha(str[i])) || (isalpha(str[i])))
							{
								lexema += str[i];
								i++;
							}
							tokens.push_back({ TokenType::ERROR, lexema, strNum, startI });
						}
						else
						{
							tokens.push_back({ TokenType::INTEGER, lexema, strNum, startI });
						}
					}
					break;
				}

				if ((isalpha(str[i])) || (str[i] == '_'))
				{
					lexema = str[i];
					i++;
					int startI = i;
					while (isalpha(str[i]))
					{
						lexema += str[i];
						i++;
					}
					if (isdigit(str[i]))
					{
						lexema += str[i];
						i++;
						while ((isdigit(str[i])) || (isalpha(str[i])))
						{
							lexema += str[i];
							i++;
						}
						tokens.push_back({ TokenType::ID, lexema, strNum, startI });
					}
					else
					{
						std::string lexemaTolowercase = lexema;
						transform(lexemaTolowercase.begin(), lexemaTolowercase.end(), lexemaTolowercase.begin(), tolower);

						if (lexemaTolowercase == "and") { tokens.push_back({ TokenType::AND, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "array") { tokens.push_back({ TokenType::ARRAY, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "begin") { tokens.push_back({ TokenType::BEGIN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "case") { tokens.push_back({ TokenType::CASE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "const") { tokens.push_back({ TokenType::CONST, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "div") { tokens.push_back({ TokenType::DIV, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "do") { tokens.push_back({ TokenType::DO, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "downto") { tokens.push_back({ TokenType::DOWNTO, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "else") { tokens.push_back({ TokenType::ELSE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "end") { tokens.push_back({ TokenType::END, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "file") { tokens.push_back({ TokenType::_FILE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "for") { tokens.push_back({ TokenType::FOR, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "function") { tokens.push_back({ TokenType::FUNCTION, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "goto") { tokens.push_back({ TokenType::GOTO, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "if") { tokens.push_back({ TokenType::IF, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "in") { tokens.push_back({ TokenType::IN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "label") { tokens.push_back({ TokenType::LABEL, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "mod") { tokens.push_back({ TokenType::MOD, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "nil") { tokens.push_back({ TokenType::NIL, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "not") { tokens.push_back({ TokenType::NOT, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "of") { tokens.push_back({ TokenType::OF, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "or") { tokens.push_back({ TokenType::OR, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "packed") { tokens.push_back({ TokenType::PACKED, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "procedure") { tokens.push_back({ TokenType::PROCEDURE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "program") { tokens.push_back({ TokenType::PROGRAM, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "record") { tokens.push_back({ TokenType::RECORD, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "repeat") { tokens.push_back({ TokenType::REPEAT, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "set") { tokens.push_back({ TokenType::SET, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "then") { tokens.push_back({ TokenType::THEN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "to") { tokens.push_back({ TokenType::TO, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "type") { tokens.push_back({ TokenType::TYPE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "until") { tokens.push_back({ TokenType::UNTIL, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "var") { tokens.push_back({ TokenType::VAR, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "while") { tokens.push_back({ TokenType::WHILE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "with") { tokens.push_back({ TokenType::WITH, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "integer") { tokens.push_back({ TokenType::INTEGER, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "double") { tokens.push_back({ TokenType::DOUBLE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "char") { tokens.push_back({ TokenType::CHAR, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "string") { tokens.push_back({ TokenType::STRING, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "boolean") { tokens.push_back({ TokenType::BOOLEAN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "word") { tokens.push_back({ TokenType::WORD, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "byte") { tokens.push_back({ TokenType::BYTE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "longint") { tokens.push_back({ TokenType::LONGINT, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "boolean") { tokens.push_back({ TokenType::BOOLEAN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "single") { tokens.push_back({ TokenType::SINGLE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "extended") { tokens.push_back({ TokenType::EXTENDED, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "read") { tokens.push_back({ TokenType::READ, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "readln") { tokens.push_back({ TokenType::READLN, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "write") { tokens.push_back({ TokenType::WRITE, lexema, strNum, startI }); }
						else if (lexemaTolowercase == "writeln") { tokens.push_back({ TokenType::WRITELN, lexema, strNum, startI }); }
						else {tokens.push_back({ TokenType::ID, lexema, strNum, startI });}
							break;
						}
					}
				}
			}
			i = 0;

	}
		for (auto s : tokens)
		{
			fileOut << "token - " << tokenTypeString[s.typeToken] << '\n';
			fileOut << "lexema - " << s.lexema << "\n";
			fileOut << "number of string - " << s.strNum << " | position - " << s.position << '\n';
			fileOut << '\n';
		}
}
