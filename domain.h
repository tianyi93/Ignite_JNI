#include <string>
#include <vector>


class Address {
public:
	Address() { zipcode = 0; }
	Address(int zipcode) {
		this->zipcode = zipcode;
	}
	int zipcode;
};


class Person {
public:
	Person(std::string name, double balance, int zipcode) {
		this->name = name;
		this->balance = balance;
		Address address(zipcode);
		this->address = address;
	}
	double getBalance() {
		return balance;
	}

	std::string name;
	double balance;
	Address address;
};

double average(std::vector<Person> vp) {
	double total = 0;
	for (auto p : vp) {
		total += p.getBalance();
	}
	return total /= vp.size();
};

int numzip(std::vector<Person> vp, int zipcode) {
	int total = 0;
	for (auto p : vp) {
		if (p.address.zipcode == zipcode)
			total++;
	}
	return total;
}