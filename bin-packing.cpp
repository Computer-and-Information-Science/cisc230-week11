#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Bin - A bin that contains items of various sizes, up to some maximum
//	capacity.
class Bin {
friend ostream& operator<< (ostream& os, const Bin& b);
protected:
	// Capacity of a bin
	static const int CAPACITY = 10;
	// A list of items currently in the bin
	list<int> items;
	// The total size of all items currently in the bin
	int total;
public:
	Bin () { total = 0; }
	// add_item - Add an item to the bin. Adding the item must not exceed
	//	the remaining capacity of the bin. Throws an exception if the size
	//	of the item causes the bin to exceed its capacity.
	void add_item (int size) {
		if (size > size_max())
			throw 1;
		items.push_back(size);
		total += size;
	}
	// size_max - Get the remaining capacity of the bin.
	int size_max () const { return CAPACITY - total; }
};

// BinPack - Abstract base class for implementation of a bin packing
//	algorithm. Derived classes must provide an implementation for add_item.
class BinPack {
friend ostream& operator<< (ostream& os, const BinPack& p);
protected:
	// The bins in which items are stored. Initially there are no bins.
	//	Function add_item will add a bin in necessary.
	vector<Bin> bins;
public:
	// Add an item to the vector of bins, adding a new bin if necessary
	//	according to the packing algorithm.
	virtual void add_item (int size) = 0;
};

// Output a Bin object to an ostream object.
ostream& operator<< (ostream& os, const Bin& b) {
	list<int>::const_iterator i;
	int count = 0;
	for (i = b.items.begin(); i != b.items.end(); i++)
		os << (count++ ? " " : "") << *i;
	return os;
}

// Output all Bin objects in a BinPack object to an ostream object.
ostream& operator<< (ostream& os, const BinPack& p) {
	for (size_t i = 0; i < p.bins.size(); i++)
		cout << "Bin " << i << ": " << p.bins[i] << endl;
	return os;
}

void test_binpack (BinPack& bp, const list<int> items) {
	for (list<int>::const_iterator i = items.begin(); i != items.end(); i++)
		bp.add_item(*i);
	cout << bp;
}

class BinPackNext : public BinPack {
public:
	void add_item (int size) {
		if (!bins.size() || bins.back().size_max() < size)
			bins.push_back(Bin());
		bins.back().add_item(size);
	}
};

class BinPackFirst : public BinPack {
public:
	void add_item (int size) {
		for (int i = 0; i < bins.size(); i++)
			if (size <= bins[i].size_max()) {
				bins[i].add_item(size);
				return;
			}
		Bin b;
		b.add_item(size);
		bins.push_back(b);
	}
};

class BinPackBest : public BinPack {
public:
	void add_item (int size) {
		size_t bin = bins.size();
		for (size_t i = 0; i < bins.size(); i++) {
			if (bin == bins.size() && size <= bins[i].size_max())
				bin = i;
			else if (size <= bins[i].size_max() &&
					bins[i].size_max() < bins[bin].size_max())
				bin = i;
		}
		if (bin == bins.size()) {
			Bin b;
			b.add_item(size);
			bins.push_back(b);
		}
		else
			bins[bin].add_item(size);
	}
};

int main () {
	list<int> test_items = { 4, 3, 5, 4, 1, 3, 8, 3, 4, 3, 1, 4 };

	cout << "Testing BinPackNext..." << endl;
	BinPackNext bp1;
	test_binpack(bp1, test_items);

	cout << "Testing BinPackFirst..." << endl;
	BinPackFirst bp2;
	test_binpack(bp2, test_items);

	cout << "Testing BinPackBest..." << endl;
	BinPackBest bp3;
	test_binpack(bp3, test_items);

//	system("pause");
	return 0;
}