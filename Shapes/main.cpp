#include "ShapesDll.h"
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

	// ������������� ����� ��������� ��� ����������
class cmp
{
public:
	bool operator()(const Shape* lhs, const Shape* rhs)
	{
		return lhs->getArea() < rhs->getArea();
	}
} compare;

int  main()
{
	cout << " Create and initialize a container for the different shapes\n";
	vector<Shape*> shapes(10);
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		if (i % 3 == 0)
			shapes[i] = new Triangle(1 + rand() % 10, 1 + rand() % 10, 10 * (1 + rand() % 15));
		else
			if (i % 3 == 1)
				shapes[i] = new Rectangle(1 + rand() % 10, 1 + rand() % 10);
			else
				if (i % 3 == 2)
					shapes[i] = new RegPolygons(4 + rand() % 15, 1 + rand() % 10);
	}

	for (const auto &i: shapes)
	{
		i->showSets();			cout << endl;
	}
	system("pause");			cout << endl;

	cout << " Put in a separate container of pointers to triangles\n";
	vector<Shape*>triangles;
	for (const auto &i : shapes)
	{
		
		if (typeid(*i) == typeid(Triangle))
			triangles.push_back(i);
	}
	for (const auto &i : triangles)
	{
		i->showSets();
		cout << "\tArea: " << i->getArea() << endl;
	}
	system("pause");			cout << endl;

	bool error;
	do {
		error = false;
		try {
			cout << " Change one of the triangles\n";
			triangles[0]->showSets();	cout << endl;
			triangles[0]->editShape();
		}
		catch (Shape::SizeError ix) {
			cout << "Error in the process \"" << ix.origin << '\"' << ix.description << endl;
			error = true;
		}
	} while (error);
	cout << " Changed the contents of the first container:\n";
	shapes[0]->showSets();		cout << endl;
	system("pause");			cout << endl;

	cout << " Sorting triangles by area\n";
	sort(triangles.begin(), triangles.end(), compare);

	for (const auto &i : triangles)
	{
		i->showSets();
		cout << "\tArea: "<< i->getArea() << endl;
	}
	system("pause");			cout << endl;

	cout << " Calculate the sum of the areas of triangles\n";
	double sum = 0.0;
	int count = triangles.size();
	int i = 0;

#pragma omp parallel for lastprivate(i) shared(triangles) reduction(+: sum)
			for (i = 0; i < count; i++)
			{
				sum += triangles[i]->getArea();
			}

	cout << "Sum = " << sum << endl;
	
	system("pause");
	return 0;
}