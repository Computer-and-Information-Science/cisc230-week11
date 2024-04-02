// Three bin-packing algorithms. Each algorithm is implemented as a class
//	derived from class BinPack.
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
	int count = 0; // Used to avoid space before output of first item in bin.
	// Output each item in the bin as integers spearated by spaces.
	for (int item: b.items)
		os << (count++ ? " " : "") << item;
	return os;
}

// Output all Bin objects in a BinPack object to an ostream object.
ostream& operator<< (ostream& os, const BinPack& bp) {
	int i = 0; // Bin index
	for (auto bin: bp.bins)
		cout << "Bin " << i++ << ": " << bin << endl;
	return os;
}

void test_binpack (BinPack& bp, const list<int> items) {
	// Add all given items to the given BinPack object.
	for (int item: items)
		bp.add_item(item);
	cout << bp;
}

class BinPackNext : public BinPack {
public:
	void add_item (int item) {
		// If the BinPack object has no bins or the last bin does not
		//	have sufficient capackty for the item, create a new bin.
		if (!bins.size() || bins.back().size_max() < item)
			bins.push_back(Bin());
		bins.back().add_item(item);
	}
};

class BinPackFirst : public BinPack {
public:
	void add_item (int item) {
		// Cycle through all bins, add item to first bin in which the item
		//	will fit.
		for (Bin& bin: bins)
			if (item <= bin.size_max()) {
				// Item will fit, add it and return.
				bin.add_item(item);
				return;
			}
		// Did not find a bin in which item will fit. Create a new bin, add
		//	the item to the new bin, then add the bin to the BinPack.
		Bin bin;
		bin.add_item(item);
		bins.push_back(bin);
	}
};

class BinPackBest : public BinPack {
public:
	void add_item (int item) {
		size_t bin_index = bins.size(); // Initialize to one past last bin.
		// Find the best fit for the item.
		for (size_t i = 0; i < bins.size(); i++) {
			// If no bin found yet and item fits in this bin, save bin_index.
			if (bin_index == bins.size() && item <= bins[i].size_max())
				bin_index = i;
			// If item fits in this bin and a better fit than bin_index, save new bin_index
			else if (item <= bins[i].size_max() && bins[i].size_max() < bins[bin_index].size_max())
				bin_index = i;
		}
		// If no bin found in which item will fit, create a new bin, add item to bin, and add bin to BinPack.
		if (bin_index == bins.size()) {
			Bin bin;
			bin.add_item(item);
			bins.push_back(bin);
		}
		// Else add item to the identified bin_index.
		else
			bins[bin_index].add_item(item);
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
