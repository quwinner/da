#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class rule
{
public:
	rule(string pingtype, string network)
	{
		PingT = pingtype;
		Network = network;
	};
	rule(string pingtype, string network, vector<unsigned short> ports)
	{
		PingT = pingtype;
		Network = network;
		Ports = ports;
	};
	void print()
	{
		cout << Network << " " << PingT << " ";
		for (size_t i = 0; i < Ports.size(); i++)
		{
			cout << Ports[i] << " ";
		}
		cout << endl;
	}

	string PingT;
	string Network;
	vector<unsigned short> Ports;
};

class rules
{
public:
	string Name;
	vector<rule> Rules;

	rules(string name)
	{
		Name = name;
	}
	void addrule(rule rule)
	{
		Rules.push_back(rule);
	}
	void print()
	{
		cout << "-- rule: " << Name << " --" << endl;
		for (size_t i = 0; i < Rules.size(); i++)
		{
			Rules[i].print();
		}
	}
};

