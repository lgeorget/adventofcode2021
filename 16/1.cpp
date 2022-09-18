#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <sstream>
#include <numeric>

struct Packet
{
	int version;
	int typeId;
	int size;

	Packet(int v, int t) : version{v}, typeId{t}, size{6} {}
	virtual void print(std::ostream& os) const = 0;
	virtual int versionSum() const {
		return version;
	}
};

std::ostream& operator<<(std::ostream& os, const Packet& p)
{
	p.print(os);
	return os;
}

struct LiteralValue : public Packet
{
	int value;

	LiteralValue(int v, int t) :
		Packet{v, t}
	{}

	void print(std::ostream& os) const override {
		os << "LiteralValue{version=" << version << ", type=" << typeId << ", value=" << value << "}";
	}

	friend std::istream& operator>>(std::istream& is, LiteralValue& lv);
};

struct Operator : public Packet
{
	char lengthTypeId;
	std::vector<std::unique_ptr<Packet>> subpackets;
	static int indent;

	Operator(int v, int t) :
		Packet{v, t}
	{}

	void print(std::ostream& os) const override {
		os << "Operator{version=" << version << ", type=" << typeId << ", lengthTypeId=" << lengthTypeId << "\n";
		indent++;
		for (auto&& subpacket : subpackets) {
			for (int i=0 ; i<indent ; i++)
				os << "\t";
			os << (*subpacket) << "\n";
		}
		indent--;
		for (int i=0 ; i<indent ; i++)
			os << "\t";
		os << "}";
	}

	int versionSum() const override {
		return std::accumulate(subpackets.begin(), subpackets.end(), Packet::versionSum(),
			[](int s, auto&& p2) { return s + p2->versionSum(); });
	}

	friend std::istream& operator>>(std::istream& is, Operator& o);
};

int Operator::indent = 0;

class Binary
{
private:
	int length = 0;
	int value = 0;

public:
	explicit Binary(int length): length{length} {}
	friend std::istream& operator>>(std::istream& is, Binary& b);
	operator int() const { return value; }
};

std::unique_ptr<Packet> parseOnePacket(std::istream& is);


std::istream& operator>>(std::istream& is, Binary& b)
{
	b.value = 0;
	for (int l=b.length ; l>0 ; l--) {
		char c = is.get();
		b.value = b.value * 2 + c - '0';
	}
	return is;
}

std::istream& operator>>(std::istream& is, LiteralValue& lv)
{
	lv.value = 0;
	char continued = '1';
	do {
		is >> continued;
		Binary b{4};
		is >> b;
		lv.value = lv.value * (2 << 3) + b;
		lv.size += 5;
	} while (continued == '1');
	return is;
}

std::istream& operator>>(std::istream& is, Operator& o)
{
	is >> o.lengthTypeId;
	o.size += 1;

	if (o.lengthTypeId == '0') {
		Binary length{15};
		is >> length;
		int l{length};
		o.size += 15 + l;

		while (l > 0) {
			std::unique_ptr<Packet> subpacket = parseOnePacket(is);
			l -= subpacket->size;
			o.subpackets.push_back(std::move(subpacket));
		}
	} else { // lengthTypeId == '1'
		 Binary nbSubpackets{11};
		 is >> nbSubpackets;
		 o.size += 11;

		 for (int i = 0 ; i < nbSubpackets ; i++) {
			std::unique_ptr<Packet> subpacket = parseOnePacket(is);
			o.size += subpacket->size;
			o.subpackets.push_back(std::move(subpacket));
		 }
	}
	return is;
}


std::unique_ptr<Packet> parseOnePacket(std::istream& is)
{
	Binary version{3}, typeId{3};
	//parse the first version id
	is >> version >> typeId;

	std::unique_ptr<Packet> packet;
	if (typeId == 4) { // literal value
		packet = std::make_unique<LiteralValue>(version, typeId);
		is >> reinterpret_cast<LiteralValue&>(*packet);
	} else { // operator
		packet = std::make_unique<Operator>(version, typeId);
		is >> reinterpret_cast<Operator&>(*packet);
	}
	return packet;
}

int main()
{
	std::string input;
	for (auto it = std::istream_iterator<char>{std::cin} ; it != std::istream_iterator<char>{} ; ++it) {
		switch (*it) {
			case '0':
				input += "0000";
				break;
			case '1':
				input += "0001";
				break;
			case '2':
				input += "0010";
				break;
			case '3':
				input += "0011";
				break;
			case '4':
				input += "0100";
				break;
			case '5':
				input += "0101";
				break;
			case '6':
				input += "0110";
				break;
			case '7':
				input += "0111";
				break;
			case '8':
				input += "1000";
				break;
			case '9':
				input += "1001";
				break;
			case 'A':
				input += "1010";
				break;
			case 'B':
				input += "1011";
				break;
			case 'C':
				input += "1100";
				break;
			case 'D':
				input += "1101";
				break;
			case 'E':
				input += "1110";
				break;
			case 'F':
				input += "1111";
				break;
		}
	}

	std::cerr << input << std::endl;

	std::istringstream is{input};

	std::unique_ptr<Packet> root = parseOnePacket(is);

	std::cout << (*root) << std::endl;
	std::cout << root->versionSum() << std::endl;
}
