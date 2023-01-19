#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class CStudent {
private:
	string name;
	string fakNumber;
	double grade;

public:
	const string& getName() const
	{
		return name;
	}
	const double getGrade() const
	{
		return grade;
	}

	CStudent()
	{
		name = "N/A";
		fakNumber = "N/A";
		grade = 0;
	}
	CStudent(const string& tName, const string& tFakNumber, double tGrade)
	{
		name = tName;
		fakNumber = tFakNumber;
		grade = tGrade;
	}
	CStudent(const CStudent& obj)
	{
		name = obj.name;
		fakNumber = obj.fakNumber;
		grade = obj.grade;
	}

	bool operator < (const CStudent& s) const
	{
		return grade < s.getGrade();
	}
	/*friend bool operator < (const CStudent& a, const CStudent& s)
	{
		return a.getGrade() < s.getGrade();
	}*/
	bool operator == (const CStudent& s) const
	{
		return fakNumber == s.fakNumber;
	}
	CStudent& operator = (const CStudent& s)
	{
		if (this == &s)
		{
			return *this;
		}
		name = s.name;
		grade = s.grade;
		fakNumber = s.fakNumber;
		return *this;
	}

	ostream& output(ostream& out) const {
		out << name << " " << fakNumber << " " << grade << endl;
		return out;
	}
	istream& input(istream& in) {
		if (&in == &cin)
		{
			cout << "Name: ";
			in >> name;
			cout << "Faculty number: ";
			in >> fakNumber;
			cout << "Grade: ";
			in >> grade;
		}
		else {
			in >> name >> fakNumber >> grade;
		}
		return in;
	}

	friend ostream& operator << (ostream& out, const CStudent& s)
	{
		return s.output(out);
	}

	friend istream& operator >> (istream& in, CStudent& s)
	{
		return s.input(in);
	}
};


class CAnalizeData {
private:
	string m_strCourse;
	vector<CStudent> m_vStudentData;

public:
	CAnalizeData(const string& tFileName, const string& tFileExtension) {
		string file = tFileName + tFileExtension;
		ifstream myfile(file);
		if (myfile.is_open())
		{
			int counter = -1;
			myfile >> m_strCourse;
			while (!myfile.eof())
			{
				CStudent newStudent;
				myfile >> newStudent;
				m_vStudentData.push_back(newStudent);
			}
			myfile.close();
		}
		else {
			throw runtime_error("Unable to open file");
		};
	}
	CAnalizeData(const vector<CStudent>& tStudentData) {
		m_vStudentData = tStudentData;
	}
	const string& getCourse() const {
		return m_strCourse;
	}
	void setCourse(string newCourse) {
		m_strCourse = newCourse;
	}
	const vector<CStudent>& getStudentData() const {
		return m_vStudentData;
	}
	void setAddressVarna(const vector<CStudent>& newStudentdata) {
		m_vStudentData = newStudentdata;
	}

	ostream& output(ostream& out) const {
		out << m_strCourse << endl;
		for (const CStudent& student : m_vStudentData)
		{
			student.output(out);
		}
		return out;
	}

	friend ostream& operator << (ostream& out, const CAnalizeData& obj)
	{
		obj.output(out);
		return out;
	}

	void sort() {
		std::sort(m_vStudentData.begin(), m_vStudentData.end(), [](const CStudent& a, const CStudent& b) {
			return a.getGrade() < b.getGrade();
		});
	}

	double calcMean() {
		double sum = 0;
		for (const CStudent& student : m_vStudentData)
		{
			sum += student.getGrade();
		}
		return sum / m_vStudentData.size();
	}
};


int main()
{
	try
	{
		CAnalizeData data("exampleData", ".txt");
		cout << data << endl;
		cout << data.calcMean() << endl;
		data.sort();

		cout << data << endl;
	}
	catch (const runtime_error& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
}
