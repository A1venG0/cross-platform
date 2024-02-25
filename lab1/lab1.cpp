#include <bits/stdc++.h>
#include <winsock2.h>
#include <random>


template<typename T>
T ConvertBetweenEndians(T value)
{
	union 
	{
		T val;
		uint8_t bytes[sizeof(T)];
	} source, destination;

	source.val = value;

	for (size_t i = 0; i < sizeof(T); i++)
	{
		destination.bytes[i] = source.bytes[sizeof(T) - i - 1];
	}

	return destination.val;
}

int main()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<uint32_t> distribution(0, std::numeric_limits<uint32_t>::max());

	for (int i = 0; i < 10; i++)
	{
		uint32_t value = distribution(rng);

		uint32_t bigEndianValue = ConvertBetweenEndians(value);
		uint32_t libraryBigEndianValue = htonl(value);

		uint32_t original = ConvertBetweenEndians(bigEndianValue);
		uint32_t libraryOriginal = ntohl(libraryBigEndianValue);

		std::cout << "little endian: " << std::hex << value << '\n';
		std::cout << "big endian: " << std::hex << bigEndianValue << '\n';
		std::cout << "original little endian: " << std::hex << original << '\n';

		std::cout << "(Library) little endian: " << std::hex << value << '\n';
		std::cout << "(Library) big endian: " << std::hex << libraryBigEndianValue << '\n';
		std::cout << "(Library) original little endian: " << std::hex << libraryOriginal << '\n';

		if (bigEndianValue != libraryBigEndianValue || original != libraryOriginal)
		{
			std::cout << "Results are not the same" << '\n';
		}

		std::cout << "-------------------------------------------------------" << '\n';
	}
	
	return 0;
}