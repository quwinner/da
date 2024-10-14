#pragma once
#include "rules.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class dionis
{
public:
	dionis(const std::string filename)
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Ошибка открытия файла: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			if (line.empty() || line.front() == '!') {
				continue;
			}
			//cout << line << endl;
			vector<string> string_words;
			string word;
			istringstream stream(line);
			while (getline(stream, word, ' ')) {
				if (!word.empty()) {
					string_words.push_back(word);
				}
			}
			if (string_words.empty()) { continue; }
			if (string_words[0] == "ip")
			{
				rules_list.push_back(rules(string_words[2]));
			}
			else
			{
				if (string_words[0] == "permit")
				{
					if (string_words.size() <= 3)
					{
						rules_list.back().addrule(rule((string_words[1] == "dst") ? "all" : string_words[2], string_words[2]));
					}
					else
					{
						vector<unsigned short> ports;
						for (size_t i = 5; i < string_words.size(); ++i) {
							ports.push_back(stoi(string_words[i]));
						}
						rules_list.back().addrule(rule(string_words[3], string_words[2], ports));
					}
				}
				else
				{
					if (string_words[0] == "call")
					{

					}
				}
			}
		}

		file.close();

	}
	void print()
	{
		for (size_t i = 0; i < rules_list.size(); i++)
		{
			rules_list[i].print();
		}
	}
	void drow()
	{
		std::ofstream outFile("example.xml");
		outFile << "<mxfile host=\"app.diagrams.net\">\n";
		outFile << "  <diagram name=\"Page-1\" id=\"0\">\n";
		outFile << "    <mxGraphModel dx=\"1000\" dy=\"1000\" grid=\"1\" gridSize=\"10\" guides=\"1\" tooltips=\"1\" connect=\"1\" arrows=\"1\" fold=\"1\" page=\"1\" pageScale=\"1\" pageWidth=\"827\" pageHeight=\"1169\" math=\"0\" shadow=\"0\">\n";
		outFile << "      <root>\n";
		outFile << "        <mxCell id=\"0\"/>\n";
		outFile << "        <mxCell id=\"1\" parent=\"0\"/>\n";

		outFile << "        <mxCell id=\"2\" value=\"Dionis\" style=\"rounded=0;whiteSpace=wrap;html=1;\" vertex=\"1\" parent=\"1\">\n";
		outFile << "          <mxGeometry x=\"100\" y=\"100\" width=\"80\" height=\"30\" as=\"geometry\"/>\n";
		outFile << "        </mxCell>\n";

		for (size_t i = 0; i < rules_list.size(); i++)
		{
			string da= "";
			for (size_t j = 0; j < rules_list[i].Rules.size(); j++)
			{
				string da2 = "";
				for (size_t k = 0; k < rules_list[i].Rules[j].Ports.size(); k++)
				{
					da2 += to_string(rules_list[i].Rules[j].Ports[k]) + " ";
				}
				da += rules_list[i].Rules[j].Network + " " + rules_list[i].Rules[j].PingT + " " + da2;
			}
			outFile << "        <mxCell id=\""<< (2 + i * 4 + 1) <<"\" value=\"" << da << "\" style=\"rounded=0;whiteSpace=wrap;html=1;\" vertex=\"1\" parent=\"1\">\n";
			outFile << "          <mxGeometry x=\"" << (100 + i * 200) << "\" y=\"50\" width=\"80\" height=\"30\" as=\"geometry\"/>\n";
			outFile << "        </mxCell>\n";


			outFile << "        <mxCell id=\"" << (2 + i * 4 + 2) << "\" value=\"" << da << "\" style=\"rounded=0;whiteSpace=wrap;html=1;\" vertex=\"1\" parent=\"1\">\n";
			outFile << "          <mxGeometry x=\"" << (100 + i * 200 + 100) << "\" y=\"250\" width=\"80\" height=\"30\" as=\"geometry\"/>\n";
			outFile << "        </mxCell>\n";

			outFile << "        <mxCell id=\"" << (2 + i * 4 + 3) << "\" style=\"edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;\" edge=\"1\" parent=\"1\" source=\"2\" target=\"" << (2 + i * 4 + 1) << "\">\n";
			outFile << "          <mxGeometry relative=\"1\" as=\"geometry\"/>\n";
			outFile << "        </mxCell>\n";

			outFile << "        <mxCell id=\"" << (2 + i * 4 + 4) << "\" style=\"edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;\" edge=\"1\" parent=\"1\" source=\"" << (2 + i * 4 + 2) << "\" target=\"2\">\n";
			outFile << "          <mxGeometry relative=\"1\" as=\"geometry\"/>\n";
			outFile << "        </mxCell>\n";

		}


		outFile << "      </root>\n";
		outFile << "    </mxGraphModel>\n";
		outFile << "  </diagram>\n";
		outFile << "</mxfile>\n";
	}
	vector<rules> rules_list;
};

