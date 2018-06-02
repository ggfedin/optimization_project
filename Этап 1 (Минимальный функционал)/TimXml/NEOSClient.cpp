#include <iostream>
#include <stdio.h>
#include <fstream>
#include "TimXmlRpc.h"

//Categories of tasks.
const std::string milp("milp");
const std::string lp("lp");

//Returns a list of all solvers available on NEOS, formated as "category:solver:inputMethod".
static void SolversAvailable()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	if (! Connection.execute("listAllSolvers", args, result)) {
		std::cout << Connection.getError();
	}
	else if (result.getType() == XmlRpcValue::TypeArray) {
		for (int i = 0; i < result.size(); i++) {
			XmlRpcValue el = result[i];
			std::string buf = el.GetStdString();
			size_t found = buf.find(milp);
			size_t found1 = buf.find(lp);
			if (found != std::string::npos || found1 != std::string::npos)
				std::cout << buf << "\n";
		}
	}
}

//Returns a string with a list of the current jobs on NEOS.
static void JobsRunning()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	if (!Connection.execute("printQueue", args, result)) {
		std::cout << Connection.getError();
	}
	else if (result.getType() == XmlRpcValue::TypeString) {
		std::cout << result.GetStdString() << "\n";
	}
}

//List all NEOS solvers in the specified category, formatted as solver:input. The category can be the full name or the abbreviation.
static void SolversAvailableInCategory()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	std::string test;
	std::cin >> test;
	args[0] = test;
	if (!Connection.execute("listSolversInCategory", args, result)) {
		std::cout << Connection.getError();
	}
	else if (result.getType() == XmlRpcValue::TypeArray) {
		for (int i = 0; i < result.size(); i++) {
			XmlRpcValue el = result[i];
			std::string buf = el.GetStdString();
			std::cout << buf << "\n";
		}
	}
}

//Returns a template for the requested solver for the particular category and inputMethod provided. 
static void GetSolverTemplate()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	std::cout << "Available categories : milp, lp\n";
	std::string category;
	std::string solver;
	std::string format;
	std::cin >> category;
	std::cout << "\n";
	std::cin >> solver;
	std::cout << "\n";
	std::cin >> format;
	args[0] = category;
	args[1] = solver;
	args[2] = format;
	if (!Connection.execute("getSolverTemplate", args, result)) {
		std::cout << Connection.getError();
	}
	else if (result.getType() == XmlRpcValue::TypeString) {
			std::string buf = result.GetStdString();
			std::cout << buf << "aaaaa\n";
	}
}

//Exports data from "xmljob.txt", sends to NEOS and returns job number and password in "jobinformation.txt".
static void SubmitJob()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	std::ifstream fin("xmljob.txt");
	std::string xmlstring((std::istreambuf_iterator<char>(fin)),
		(std::istreambuf_iterator<char>()));
	fin.close();
	std::cout << xmlstring;
	args[0] = xmlstring;
	if (!Connection.execute("submitJob", args, result)) {
		std::cout << Connection.getError();
	}
	else {
		XmlRpcValue jobNumber, password;
		jobNumber = result[0];
		password = result[1];
		std::cout << jobNumber.GetStdString() << "\n";
		std::cout << password.GetStdString() << "\n";
		std::ofstream fout("jobinformation.txt");
		fout << jobNumber.GetStdString() << "\n" << password.GetStdString() << "\n";
		fout.close();
	}
}

//Get status of your previous job, using number and password in "jobinformation.txt".
static void GetStatus()
{
	XmlRpcClient Connection("https://neos-server.org:3333");
	Connection.setIgnoreCertificateAuthority();
	XmlRpcValue args, result;
	std::ifstream fin("jobinformation.txt");
	std::string buffer(""), password;
	int job;
	getline(fin, buffer);
	job = std::stoi(buffer);
	getline(fin, buffer);
	password = buffer;
	fin.close();
	args[0] = job;
	args[1] = password;
	if (!Connection.execute("getJobStatus", args, result)) {
		std::cout << Connection.getError();
	}
	else {
		std::cout << result.GetStdString() << "\n";
	}
}

//---------------------------- main(): -------------------------

int main(int argc, char* argv[])
{
    //SolversAvailable();
	//JobsRunning();
	//SolversAvailableInCategory();
	//SubmitJob();
	GetSolverTemplate();
	//GetStatus();
	int a;
	std::cin >> a;
	return 0;
}

