#include <iostream>
#include <string>
#include <sstream>

class Assembly
{
public:
	uint16_t convert(std::string input)
	{
		std::istringstream iss(input);
		std::string operation;
		std::string destination_registry, first_operand, second_operand;
		uint16_t result_code = 0;
		iss >> operation;
		if (operation == "ADD")
		{
			iss >> destination_registry >> first_operand >> second_operand;
			uint16_t second_operand_number = stoi(second_operand.substr(second_operand.size() - 1, 1));
			uint16_t first_operand_number = stoi(first_operand.substr(first_operand.size() - 1, 1));
			uint16_t destination_registry_number = stoi(destination_registry.substr(destination_registry.size() - 1, 1));
			result_code |= (second_operand_number & 0x7); // last 3 bits - second operand
			result_code |= ((first_operand_number & 0x7) << 6);
			result_code |= ((destination_registry_number & 0x7) << 9);
			result_code |= (1 << 12); // 0001 - operation code
		}
		else if (operation == "LOAD")
		{
			iss >> destination_registry >> first_operand;
			uint16_t first_operand_number = stoi(first_operand);
			uint16_t destination_registry_number = stoi(destination_registry.substr(destination_registry.size() - 1, 1));

			result_code |= (first_operand_number & 0x1FF); // last 9 bits - number to load
			result_code |= ((destination_registry_number & 0x7) << 9);
			result_code |= (2 << 12); // 0010 - operation code
		}
		else if (operation == "AND")
		{
			iss >> destination_registry >> first_operand >> second_operand;
			uint16_t second_operand_number = stoi(second_operand.substr(second_operand.size() - 1, 1));
			uint16_t first_operand_number = stoi(first_operand.substr(first_operand.size() - 1, 1));
			uint16_t destination_registry_number = stoi(destination_registry.substr(destination_registry.size() - 1, 1));
			result_code |= (second_operand_number & 0x7); // last 3 bits - second operand
			result_code |= ((first_operand_number & 0x7) << 6);
			result_code |= ((destination_registry_number & 0x7) << 9);
			result_code |= (3 << 12); // 0011 - operation code
		}
		else if (operation == "NOT")
		{
			iss >> destination_registry >> first_operand;
			uint16_t first_operand_number = stoi(first_operand.substr(first_operand.size() - 1, 1));
			uint16_t destination_registry_number = stoi(destination_registry.substr(destination_registry.size() - 1, 1));

			result_code |= ((first_operand_number & 0x7) << 6);
			result_code |= ((destination_registry_number & 0x7) << 9);
			result_code |= (4 << 12); // 0100 - operation code
		}
		else if (operation == "JMP")
		{
			iss >> first_operand;
			uint16_t first_operand_number = stoi(first_operand.substr(first_operand.size() - 1, 1));
			result_code |= ((first_operand_number & 0x7) << 6);
			result_code |= (5 << 12); // 0101 - operation code

		}
		else if (operation == "PRINT")
		{
			iss >> first_operand;
			uint16_t first_operand_number = stoi(first_operand.substr(first_operand.size() - 1, 1));
			result_code |= (first_operand_number & 0x7);
			result_code |= (6 << 12); // 0110 - operation code
		}
		return result_code;
	}
};