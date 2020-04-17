/*
Task: H2
Family Name: Mia
Given Name: Mohammad Lal Mahmud
Matriculation number: 3055338
Uni-Email: mohammad.mia@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#include <iterator>
#include <iomanip>

using namespace std;

struct Point
{
    string name;
    double x;
    double y;
    double d;
    Point *next;
};

double calc_distance(Point point1, Point point2)
{
    double d = sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y-point2.y)*(point1.y-point2.y));
    return d;
}

Point* find_nearest(list<Point> points, Point point)
{
    Point *nearest = nullptr;
    list<Point>::iterator it;
    for (it = points.begin(); it != points.end();++it)
    {
        if (it->name.compare(point.name) == 0)
            continue;
        else
        {
            if (!nearest)
            {
                nearest = &(*it);
                continue;
            }
            if (calc_distance(*it,point) < calc_distance(*nearest,point))
            {
                nearest = &(*it);
            }
        }
    }
    return nearest;
}

void insert_point(list<Point> &sorted_list, Point *p)
{
    // cout<<"size: "<<sorted_list.size();
    if (sorted_list.empty())
    {
        sorted_list.push_front(*p);
    }
    else {
        list<Point>::iterator it;
        for (it = sorted_list.begin(); it != sorted_list.end() ; ++it)
        {
            if (p->d < it->d)
            {
                break;
            }
        }
        sorted_list.insert(it,*p);
        list<Point>::iterator it2;
        Point *prev = nullptr;
        for (it2 = sorted_list.begin(); it2 != sorted_list.end() ; ++it2)
        {
            if (it2 == sorted_list.begin())
            {
                prev = &(*it2);
                continue;
            }
            else
            {
                prev->next = &(*it2);
                prev = &(*it2);
            }
        }
    }
}

void print_format(list<Point> points)
{
    cout.precision(2);
    for (Point p : points){
        cout<< "obstacle " << p.name <<": (";
        cout<<fixed << setw(6)<<setfill(' ')<< p.x<<",";
        cout<<fixed << setw(6)<<setfill(' ')<< p.y;
        cout<<"), distance: ";
        cout<< p.d <<"m, nearest to this: ";
        Point *temp =find_nearest(points,p);
        if (temp)
            cout<<temp->name;
        else
            cout<<" ";
        cout<<endl;
    }
}

void delete_all(list<Point> points)
{
    cout<<"delete: ";
    for(Point p : points)
    {
        cout<<p.name<<" ";
    }
    cout<<endl;
    points.clear();
}

int main()
{
    Point base;
    base.name = "BASE";
    base.x= 0;
    base.y=0;
    list<Point> obstacles;
    Point p;
    bool flag=true;
    do
    {
        cout<<"string describing obstacle (\"end\" for end of input): ";
        cin>>p.name;
        if (p.name.compare("end") == 0)
        {
            flag=false;
            continue;
        }
        cout<<"x and y coordinate: ";
        cin>>p.x >> p.y;
        p.d = calc_distance(base,p);
        p.next = nullptr;
        insert_point(obstacles,&p);
    }
    while(flag);
    print_format(obstacles);
    delete_all(obstacles);
    return 0;
}

