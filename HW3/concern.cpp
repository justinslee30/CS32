//DONE

#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

//concern is the base class
class Concern
{
public:
	Concern(string person)
	{
		m_person = person;
	}
	virtual ~Concern()
	{

	}
	virtual string description() const = 0;
	string person() const
	{
		return m_person;
	}
	virtual bool possibleFelony() const = 0;
private:
	string m_person;
};

//all derived classes from the concern base class
class EthicsMatter : public Concern
{
public:
	EthicsMatter(string name) : Concern(name)
	{

	}
	virtual ~EthicsMatter()
	{
		cout << "Destroying " << Concern::person() << "'s ethics matter" << endl;
	}
	virtual string description() const
	{
		return "An ethics matter";
	}
	virtual bool possibleFelony() const
	{
		return false;
	}
};

class HushPayment : public Concern
{
public:
	HushPayment(string name, int money) : Concern(name)
	{
		m_payment = money;
	}
	virtual ~HushPayment()
	{
		cout << "Destroying " << Concern::person() << "'s hush payment" << endl;
	}
	virtual string description() const
	{
		string answer = "A $" + to_string(m_payment) + " payment";
		return answer;
	}
	virtual bool possibleFelony() const
	{
		return false;
	}
private:
	int m_payment;
};

class Investigation : public Concern
{
public:
	Investigation(string name) : Concern(name)
	{

	}
	virtual ~Investigation()
	{
		cout << "Destroying " << Concern::person() << "'s investigation" << endl;
	}
	virtual string description() const
	{
		return "An investigation";
	}
	virtual bool possibleFelony() const
	{
		return true;
	}
};

void display(const Concern* c)
{
	cout << c->description() << " involving " << c->person();
	if (c->possibleFelony())
		cout << ", possibly felonious";
	cout << endl;
}

int main()
{
	Concern* concerns[4];
	concerns[0] = new EthicsMatter("Pruitt");
	// Hush payments have a person's name and an amount of money (an int).
	concerns[1] = new HushPayment("Clifford", 130000);
	concerns[2] = new HushPayment("McDougal", 150000);
	concerns[3] = new Investigation("Mueller");

	cout << "Here are the concerns:" << endl;
	for (int k = 0; k < 4; k++)
		display(concerns[k]);

	// Clean up the concerns before exiting
	cout << "Cleaning up:" << endl;
	for (int k = 0; k < 4; k++)
		delete concerns[k];
}
