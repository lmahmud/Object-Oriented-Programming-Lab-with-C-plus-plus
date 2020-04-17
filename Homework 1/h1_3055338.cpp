/*
Task: H1
Family Name: Mia
Given Name: Mohammad Lal Mahmud
Matriculation number: 3055338
Uni-Email: mohammad.mia@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <string>
#include <iostream>

struct team {
    std::string name;
    int sum_points;
    int done_matches;
};

bool should_sort;

void show_title(std::string);
void show_menu();

void init(team*,int);
void table(team*,int);
int choose(team*,int);
void store(team*,int,int,int);
void reset(team*,int);

int main(void) {
    int amount;
    int index1;
    int index2;
    int point1;
    int point2;
    char delimiter;
    team *team_array;
    std::cout<<"number of teams: ";
    std::cin>>amount;
    team_array = new team[amount];
    init(team_array,amount);
    show_title("initial ranking");
    table(team_array,amount);
    int item;
    for (;;) {
        show_menu();
        std::cin>>item;
        switch (item) {
            case 0:
                delete[] team_array;
                exit(0);
                break;
            case 1:
                std::cout<<"please choose team 1?";
                std::cout<<std::endl;
                index1 = choose(team_array,amount);
                std::cout<<"please choose team 2?";
                std::cout<<std::endl;
                index2 = choose(team_array,amount);
                if (index1 != index2) {
                    std::cout<<"input as [points of ";
                    std::cout<<team_array[index1].name;
                    std::cout<<"] : [points of ";
                    std::cout<<team_array[index2].name;
                    std::cout<<"]? ";
                    std::cin>>point1;
                    std::cin>>delimiter;
                    std::cin>>point2;
                    should_sort = false;
                    store(team_array,amount,index1,point1);
                    should_sort = true;
                    store(team_array,amount,index2,point2);
                }
                else {
                    std::cout<<"*** sorry teams need to be different ***";
                    std::cout<<std::endl;
                    std::cout<<std::endl;
                }
                break;
            case 2:
                show_title("ranking");
                table(team_array,amount);
                break;
            case 9:
                reset(team_array,amount);
                break;
        }
    }
    return 0;
}

void init(team *team_array, int amount) {
    std::string name;
    show_title("input of teams");
    for (int i=0; i< amount; i++){
        std::cout<<"team ";
        std::cout<<i+1;
        std::cout<<": ";
        std::cin>>name;
        team_array[i].name = name;
        team_array[i].sum_points = 0;
        team_array[i].done_matches = 0;
    }
}

void table(team *team_array, int amount) {
    std::cout<<"points\tdone matches\tname";
    std::cout<<std::endl;
    for (int i=0; i< amount; i++) {
        std::cout<<team_array[i].sum_points;
        std::cout<<"\t";
        std::cout<<team_array[i].done_matches;
        std::cout<<"\t\t";
        std::cout<<team_array[i].name;
        std::cout<<std::endl;
    }
}

int choose(team *team_array, int amount) {
    int c;
    show_title("teams");
    for (int i=0; i < amount; i++) {
        std::cout<<i+1;
        std::cout<<"\t";
        std::cout<<team_array[i].name;
        std::cout<<std::endl;
    }
    std::cout<<"choose team by number: ";
    std::cin>>c;
    return c-1;
}

void store(team *team_array,int amount,int index, int points) {
    bool swapped;
    team_array[index].sum_points += points;
    team_array[index].done_matches += 1;
    if (should_sort) {
        for (int i=0;i< amount-1;i++){
            swapped = false;
            for (int j=0;j< amount - i - 1; j++){
                if (team_array[j+1].sum_points > team_array[j].sum_points){
                    team temp = team_array[j+1];
                    team_array[j+1]=team_array[j];
                    team_array[j] = temp;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }
}

void reset(team *team_array, int amount) {
    for (int i=0; i< amount; i++){
        team_array[i].sum_points = 0;
        team_array[i].done_matches = 0;
    }
}

void show_title(std::string title) {
    std::cout<<std::endl;
    std::cout<<title;
    std::cout<<std::endl;
    for (int i=0;i<title.size();i++)
        std::cout<<"=";
    std::cout<<std::endl;
}

void show_menu() {
    std::cout<<std::endl;
    std::cout<<"0 end";
    std::cout<<std::endl;
    std::cout<<"1 add result of a match";
    std::cout<<std::endl;
    std::cout<<"2 show ranking";
    std::cout<<std::endl;
    std::cout<<"9 reset points";
    std::cout<<std::endl;
    std::cout<<"your choice: ";
}

