#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
struct stclient_data
{
    string account_num;
    string pin_code;
    string name;
    string phone;
    double account_balance;
};
void quick_withdraw_screen();
vector<stclient_data> load_client_data_from_file();
void atm_main_menu();
stclient_data current_client;
constexpr string FILE_NAME="Clients.txt";

enum atm_main_menu_choice{
    equick_withdraw=1,enormal_withdraw=2,edeposit=3,echeck_balance=4,elogout=5
};
enum quick_withdraw_choice{
    twenty=1,fifty=2,hundred=3,two_hundred=4,four_hundred=5,six_hundred=6,eight_hundred=7,one_thousand=8,exit_=9,
};
void update_client_balance(vector<stclient_data>&clients){

    for (auto &i:clients) {
        if(i.account_num==current_client.account_num){
            i=current_client;
        }
    }
}
string join_st(stclient_data client, string sep = "#//#") {
    string joined;
    joined += client.account_num + sep;
    joined += client.pin_code + sep;
    joined += client.name + sep;
    joined += client.phone + sep;
    joined += to_string(client.account_balance);
    return joined;
}
void save_client_to_file(const vector <stclient_data>&clients) {
    fstream file;
    file.open(FILE_NAME, ios::out);
    string data;
    stclient_data new_client;
    if (file.is_open()) {
        for ( const stclient_data &c : clients)
        {
            string line= join_st(c);
            file<<line<<endl;

        }
        file.close();

    }

}
bool deposit_validate(int deposited_balance){
    return deposited_balance>=0;
}
void deposit_screen(){
    int deposited_balance;
    cout<<"========================================"<<endl;
    cout<<setw(30)<<"deposit balance screen"<<endl;
    cout<<"========================================"<<endl;
    do {
        cout << "\nenter a positive number to deposit: ";
        cin >> deposited_balance;
    }while(!deposit_validate(deposited_balance));
    char answer;
    do {
        cout << "are you sure you want to proceed y/n";
        cin >> answer;
    } while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');
    if(answer=='y'||answer=='Y'){
        current_client.account_balance+=deposited_balance;
        vector<stclient_data> clients = load_client_data_from_file();
        update_client_balance(clients);
        save_client_to_file(clients);
    }
    if(answer=='n'||answer=='N'){
        return;
    }
}
bool normal_withdraw_validation(int balance){
    return (balance % 5 == 0)&&(balance<=current_client.account_balance);
}
void normal_with_draw_screen(){
    int with_draw_balance;
    cout<<"========================================"<<endl;
    cout<<setw(30)<<"normal withdraw screen"<<endl;
    cout<<"========================================"<<endl;
    do {
        cout << "enter a number that is a multiple of 5's: ";
        cin >> with_draw_balance;
    }while(!normal_withdraw_validation(with_draw_balance));
    current_client.account_balance-=with_draw_balance;
    cout<<"your account balance is: "<<current_client.account_balance<<endl;
    vector<stclient_data> clients = load_client_data_from_file();
    update_client_balance(clients);
    save_client_to_file(clients);
}
 short validate_quick_withdraw_choice() {
    int choice;
    string input;
    do {
        cin >> input;
        if (all_of(input.begin(), input.end(), [](char c) { return isdigit(c); })) {
            choice = stoi(input);
        }
    }while (choice < 1 || choice > 9);
     return choice;
}
void go_back_to_with_draw(){
     quick_withdraw_screen();
 }

void quick_withdraw(quick_withdraw_choice choice){
    bool withdraw= false;
if(choice==::twenty&&current_client.account_balance>20){
    current_client.account_balance-=20;
    withdraw=true;
    go_back_to_with_draw();
}
    if(choice==::fifty&&current_client.account_balance>50){
        current_client.account_balance-=50;
        withdraw=true;
        go_back_to_with_draw();

    }
    if(choice==::hundred&&current_client.account_balance>100){
        current_client.account_balance-=100;
        withdraw=true;

        go_back_to_with_draw();

    }
    if(choice==::two_hundred&&current_client.account_balance>200){
        current_client.account_balance-=200;
        withdraw=true;

        go_back_to_with_draw();

    }
    if(choice==::four_hundred&&current_client.account_balance>400){
        current_client.account_balance-=400;
        withdraw=true;

        go_back_to_with_draw();

    }
    if(choice==::six_hundred&&current_client.account_balance>600){
        current_client.account_balance-=600;
        withdraw=true;

        go_back_to_with_draw();

    }
    if(choice==::eight_hundred&&current_client.account_balance>800){
        current_client.account_balance-=800;
        withdraw=true;

        go_back_to_with_draw();

    }
    if(choice==::one_thousand&&current_client.account_balance>1000){
        current_client.account_balance-=1000;
        withdraw=true;
        go_back_to_with_draw();

    }
    if(choice==::exit_){
        vector<stclient_data> clients = load_client_data_from_file();
        update_client_balance(clients);
        save_client_to_file(clients);
        withdraw=true;
        return;
    }

    if(!withdraw){
        cout<<"\nthe amount exceeds your balance please try another choice\n";
        system("pause");
        go_back_to_with_draw();
    }
 }
void quick_withdraw_screen(){
    cout<<"========================================"<<endl;
    cout<<setw(30)<<"quick withdraw screen"<<endl;
    cout<<"========================================"<<endl;
     cout<<setw(30);
     printf("[1]%0*d",2,20);
     printf("             ");
    printf("[2]%0*d\n",2,50);
    printf("[3]%0*d",3,100);
    printf("            ");
    printf("[4]%0*d\n",3,200);
    printf("[5]%0*d",3,400);
    printf("            ");
    printf("[6]%0*d\n",3,600);
    printf("[7]%0*d",3,800);
    printf("            ");
    printf("[8]%0*d\n",3,1000);
    printf("[9]%s\n","exit");
    cout<<left<<"your account balance is:"<<current_client.account_balance<<endl;
    cout<<"choose what do you want withdraw from [1] to [8]? ";
    short quick_withdraw_balance=validate_quick_withdraw_choice();

    char answer;
    do {
        cout << "are you sure you want to proceed y/n";
        cin >> answer;
    } while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

    if(answer=='y'||answer=='Y') {
        quick_withdraw(quick_withdraw_choice(quick_withdraw_balance));
    }
    if(answer=='n'||answer=='N'){
        go_back_to_with_draw();
    }
}
void check_balance_screen(){
    cout<<"========================================"<<endl;
    cout<<setw(30)<<"check account balance screen"<<endl;
    cout<<"========================================"<<endl;
    cout<<"your account balance is: "<<current_client.account_balance<<endl;
}

void atm(atm_main_menu_choice choice){
    while(true) {
        if (choice == ::equick_withdraw) {
            quick_withdraw_screen();
            system("pause");
            atm_main_menu();
            break;
        }
        if (choice == ::enormal_withdraw) {
             normal_with_draw_screen();
            atm_main_menu();
            break;
        }
        if (choice == ::edeposit) {
             deposit_screen();
             atm_main_menu();
            break;
        }
        if (choice == ::echeck_balance) {
            check_balance_screen();
            system("pause");
            atm_main_menu();
            break;
        }
        if (choice == ::elogout) {
            return;
        }

    }
}
atm_main_menu_choice validate_choice() {
    int choice;
    string input;
    do {
        cin >> input;
        if (all_of(input.begin(), input.end(), [](char c) { return isdigit(c); })) {
            choice = stoi(input);
        }
    }while (choice < 1 || choice > 5);
    return atm_main_menu_choice(choice);
}
void atm_main_menu(){
    cout<<"========================================"<<endl;
    cout<<setw(30)<<"ATM main menu screen"<<endl;
    cout<<"========================================"<<endl;
    cout<<setw(27)<<"[1] quick withdraw"<<endl;
    cout<<setw(29)<<"[2] normal withdraw "<<endl;
    cout<<setw(20)<<"[3] deposit"<<endl;
    cout<<setw(27)<<"[4] check balance "<<endl;
    cout<<setw(20)<<"[5] logout "<<endl;
    cout<<"========================================"<<endl;
    cout<<"choose what do you want to do? [1 to 5]? ";
    atm_main_menu_choice choice=validate_choice();
    atm(choice);
}

vector<string>split_rec(string whole_rec, string sep = "#//#") {
    short pos;
    string rec;
    vector<string>vrecord;

    while ((pos = whole_rec.find(sep)) != string::npos) {
        rec = whole_rec.substr(0, pos);
        if (rec != "") {
            vrecord.push_back(rec);
        }
        whole_rec.erase(0, pos + sep.size());
    }
    if (whole_rec != "") {
        vrecord.push_back(whole_rec);
    }

    return vrecord;
}
stclient_data ConvertLinetoRecord(string line) {
    stclient_data Client;
    vector<string> vClientData = split_rec(line);
    Client.account_num = vClientData[0];
    Client.pin_code = vClientData[1];
    Client.name = vClientData[2];
    Client.phone = vClientData[3];
    Client.account_balance = stod(vClientData[4]);
    return Client;
}
vector<stclient_data> load_client_data_from_file() {
    ifstream file(FILE_NAME);
    vector<stclient_data>rec;
    if (file.is_open()) {
        string line;
        stclient_data client;

        while (getline(file, line)) {
            client = ConvertLinetoRecord(line);
            rec.push_back(client);
        }
        file.close();
    }
    return rec;
}
bool find_by_account_number(string account_number,string pin_code,stclient_data &client) {
    vector<stclient_data> clients=load_client_data_from_file();
    for (stclient_data& c : clients)
    {
        if (c.account_num == account_number && c.pin_code==pin_code) {
            client = c;
            return true;
        }
    }
    return false;
}
bool  LoadclientInfo(string account_num, string pincode)
{
    if (find_by_account_number(account_num,pincode, current_client))
        return true;
    else
        return false;
}

void login_screen() {
    bool LoginFaild = false;
    string account_num, pincode;
    do    {
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (LoginFaild)  {
            cout << "Invalid Username/Password!\n";
        }
        cout << "Enter Account number? ";
        cin >> account_num;
        cout << "Enter Pin code? ";
        cin >> pincode;
        LoginFaild = !LoadclientInfo(account_num, pincode);
    }
    while (LoginFaild);
    atm_main_menu();
}
int main() {
    login_screen();
    return 0;
}
