/*
Task: H3
Family Name: Mia
Given Name: Mohammad Lal Mahmud
Matriculation number: 3055338
Uni-Email: mohammad.mia@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <string>
#include <iostream>
#include <fstream>

// #define TEST
using namespace std;

struct Pair
{
    string key;
    string value;
};

int total_collision;
int prime;

int calc_hash(string key)
{
    int index = 0;
    for (int i=0;i<key.size();i++)
    {
        if (i==0)
            index = (int)key[i]*128;
        else if (i == 1)
        {
            index = (index + (int)key[i]) % prime;
        }
        else
        {
            index = (index*128 + (int)key[i]) % prime;
        }
    }
    return index;
}

void insert_entry(string key, string value, Pair *dictionary)
{
    int index = calc_hash(key);
#ifdef TEST
    string test = "insert: ";
    test.append(key);
    test.append(" -> ");
    test.append(value);
    test.append(" at index: ");
    test.append(to_string(index));
    cout<<test<<endl;
#endif
    if (dictionary[index].key.size() < 1)
    {
        dictionary[index].key = key;
        dictionary[index].value = value;
    }
    else
    {
        total_collision++;
#ifdef TEST
        cout<<"\tcollision with "<<dictionary[index].key<<endl;
#endif
        index++;
        while (dictionary[index].key.size() != 0)
        {
            total_collision++;
#ifdef TEST
            cout<<"\tcollision with "<<dictionary[index].key<<endl;
#endif
            if (index < prime - 1)
                index++;
            else
                index=0;
        }
        dictionary[index].key = key;
        dictionary[index].value = value;
#ifdef TEST
        cout<<"\tlinear collision strategy results with index: "<<index<<endl;
#endif
    }
}

void find_entry(string key, Pair *dictionary)
{
    int index = calc_hash(key);
    if (dictionary[index].key.compare(key) == 0)
    {
        cout<<key << " -> "<< dictionary[index].value<<endl;
    }
    else
    {
        index++;
        while(true)
        {
            if (dictionary[index].key.compare(key) == 0)
            {
                cout<<key << " -> "<< dictionary[index].value<<endl;
                break;
            }
            if (index == calc_hash(key))
                break;
            if (dictionary[index].key.size() < 1)
            {
                cout<<"sorry not known"<<endl;
                break;
            }
            if (index < prime -1)
                index++;
            else
                index = 0;
        }
    }
}

void import_file(string fileName, Pair *dictionary)
{
    ifstream ifs(fileName);
#ifdef TEST
    cout<<fileName<<" opened..."<<endl;
#endif
    string line;
    while(getline(ifs,line))
    {
        string key = line.substr(0,line.find(";"));
        string value = line.substr(line.find(";")+1,line.size());
        value.erase(value.find_last_not_of(" \t\r\n\f\v") + 1);
        insert_entry(key,value,dictionary);
    }
    ifs.close();
#ifdef TEST
    cout<<fileName<<" closed"<<endl;
#endif
}

int main()
{
    cout<<"please input value for (prime) number of p: ";
    cin>>prime;
    Pair *dictionary = new Pair[prime];
    import_file("tiere_animals.txt",dictionary);
#ifdef TEST
    cout<<total_collision<<" collision(s) during insert"<<endl;
    for (int i=0;i<prime;i++)
    {
        if (dictionary[i].key.size()>1)
            cout<<i<<": "<<dictionary[i].key<<" -> "<<dictionary[i].value<<endl;
    }
#endif
    while(true)
    {
        cout<<"translate (0 for end): ";
        string word;
        cin>>word;
        if (word.compare("0") == 0)
            break;
        find_entry(word,dictionary);
    }
    delete[] dictionary;
    return 0;
}
