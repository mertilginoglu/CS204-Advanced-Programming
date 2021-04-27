
// add #includes, using namespace std; here

IntegerSet Union(const IntegerSet& lhs, const IntegerSet& rhs) 
{
	IntegerSet res = lhs + rhs;

	return res;
}

void takeInputs(IntegerSet& intSet, int x) {
	cout << "Please enter elements of set " << x << ". Press CTRL + Z after all elements are entered " << endl;

	int element;
	while (cin >> element)
	{
		intSet = intSet + element;
	}
	cin.clear();
}

int main()
{
	
	IntegerSet intSet1;
	IntegerSet intSet2;

	takeInputs(intSet1, 1);
	cout << "intSet1" << endl;
	cout << intSet1 << endl << endl;

	takeInputs(intSet2, 2);
	cout << "intSet2" << endl;
	cout << intSet2 << endl << endl;

	IntegerSet intSet3(intSet1);

	cout << "intSet3 after IntegerSet intSet3(intSet1)" << endl;
	cout << intSet3 << endl << endl;
	intSet3 = intSet3;

	if (intSet1 != intSet3)
	{
		cout << "intSet3" << intSet3 << " is different than intSet1 " << intSet1 << endl << endl;
	}
	else 
	{
		cout << "intSet3" << intSet3 << " is equal to intSet1 " << intSet1 << endl << endl;
	}

	if (!(intSet1 != intSet2))
		cout << "intSet1 " << intSet1 << " is equal to intSet2 " << intSet2 << endl << endl;
	else
		cout << "intSet1 " << intSet1 << " is not equal to intSet2 " << intSet2 << endl << endl;
	
	intSet3 = Union(intSet1, intSet2);
	cout << "intSet3 after intSet3 = Union(intSet1, intSet2) " << endl << intSet3 << endl << endl;

	IntegerSet intSet4;
	intSet4 = intSet1 + intSet2;
	cout << "intSet4 after intSet4 = intSet1 + intSet2 "<< endl << intSet4 << endl << endl;

	if (!(intSet3 != intSet4))
		cout << "intSet3 " << intSet3 << " is equal to intSet4 " << intSet4 << endl << endl;
	else
		cout << "intSet3 " << intSet3 << " is not equal to intSet4 " << intSet4 << endl << endl;

	intSet1 = intSet1 + 22;
	cout << "intSet1 after intSet1 = intSet1 + 22" << endl;
	cout << intSet1 << endl << endl;
	intSet2 = intSet2 + -22;
	cout << "intSet2 after intSet2 = intSet2 + -22" << endl;
	cout << intSet2 << endl << endl;

	intSet4 = intSet3 * intSet2;

	cout << "intSet4 after intSet4 = intSet3 * intSet2" << endl;
	cout << intSet4 << endl << endl;

	intSet4 = intSet3 * intSet1;

	cout << "intSet4 after intSet4 = intSet3 * intSet1" << endl;
	cout << intSet4 << endl << endl;

	intSet3 = intSet1 + intSet2 + intSet4;
	cout << "intSet3 after intSet3 = intSet1 + intSet2 + intSet4" << endl;
	cout << intSet3 << endl << endl;

	intSet4 += intSet1;

	cout << "intSet4 after intSet4 += intSet1" << endl;
	cout << intSet4 << endl << endl;
	
	if (3 <= intSet1)
		cout << 3 << " is element of intSet1 " << intSet1 << endl << endl;
	else
		cout << 3 << " is not element of intSet1 " << intSet1 << endl << endl;

	if (intSet4 <= intSet3)
		cout << "intSet4 " << intSet4 << " is a subset of intSet3 " << intSet3 << endl << endl;
	else
		cout << "intSet4 " << intSet4 << " is not a subset of intSet3 " << intSet3 << endl << endl;

	intSet1 = intSet2 += intSet3;
	cout << "intSet2 after intSet1 = intSet2 += intSet3 " << endl << intSet2 << endl << endl;

	cout << "intSet1 after intSet1 = intSet2 += intSet3 " << endl << intSet1 << endl << endl;

	IntegerSet intSet5(11);
	cout << "intSet5 after IntegerSet intSet5(11) " << endl << intSet5 << endl << endl;

	intSet1 = intSet2 = intSet3 += intSet4 += intSet5;
	cout << "After intSet1 = intSet2 = intSet3 += intSet4 += intSet5 " << endl << endl;
	cout << "intSet1: " << intSet1 << endl;
	cout << "intSet2: " << intSet2 << endl;
	cout << "intSet3: " << intSet3 << endl;
	cout << "intSet4: " << intSet4 << endl;
	cout << "intSet5: " << intSet5 << endl;

	return 0;
}