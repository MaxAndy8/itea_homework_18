#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class IPAddress {
protected:
	std::string ip;

public:
	IPAddress(const std::string& ipAddress) : ip(ipAddress) {}
	IPAddress(const IPAddress& other) : ip(other.ip) {}
	virtual void print() {
		std::cout << ip;
	}
	virtual ~IPAddress() {}
};

class IPAddressChecked : public IPAddress {
private:
	bool isValid;

	bool validateIPAddress(const std::string& ipAddress) {

		char delimiter = '.';  // Роздільник
		std::vector<std::string> result;
		std::istringstream ss(ipAddress);
		std::string s;

		while (std::getline(ss, s, delimiter)) {
			result.push_back(s);
		}

		if (result.size() != 4) {
			return false;
		}

		for (size_t i = 0; i < 4; i++)
		{
			std::string str = result[i];

			try {
				size_t idx;
				int number = std::stoi(str, &idx);

				if (idx == str.length()) {
					if ( !( 0 <= number && number <= 255) ) {
						return false;
					}
				}
				else {
					return false;
				}
			}
			catch (std::invalid_argument const& ex) {
				return false;
			}
			catch (std::out_of_range const& ex) {
				return false;
			}

		}

		return true;
	}

public:
	IPAddressChecked(const std::string& ipAddress) : IPAddress(ipAddress) {
		isValid = validateIPAddress(ipAddress);
	}

	IPAddressChecked(const IPAddressChecked& other) : IPAddress(other), isValid(other.isValid) {}

	virtual void print() {
		IPAddress::print();
		if (isValid) {
			std::cout << " - Правильно";
		}
		else {
			std::cout << " - Неправильно";
		}
	}

};

int main() {
	system("chcp 1251>nul");
	
	IPAddressChecked ip{ "1.2.3.4" };
	ip.print();
	std::cout << std::endl;

	ip = { "999.29.29.29" };
	ip.print();
	std::cout << std::endl;

	ip = { "199.29.29.29" };
	ip.print();
	std::cout << std::endl;

	ip = { "199.29.29." };
	ip.print();
	std::cout << std::endl;

	ip = { "Address - 1.2.3.4" };
	ip.print();
	std::cout << std::endl;

	ip = { "203.2.13.4" };
	ip.print();
	std::cout << std::endl;

	return 0;
}