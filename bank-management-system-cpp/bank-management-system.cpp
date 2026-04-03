#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;

enum enMenuChoice {Show = 1 ,Add = 2 ,Delete = 3 ,Update = 4 ,Find = 5 ,Transactions = 6 ,ManageUsers = 7,Logout = 8};
enum enTransactionsMenu {Deposit = 1 ,Withdraw = 2 ,TotalBalances = 3 ,ReturnMainMenu = 4};
enum enManageUsersMenu {ListUsers = 1,AddUser = 2 ,DeleteUser = 3 ,UpdateUser = 4 ,FindUser = 5 ,BackToMainMenu = 6};

const string ClientsFileName = "ClientsData.txt";
const string UsersFileName = "UsersData.txt";

struct stClient
{
    string AccNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccBalance;
    bool MarkForDelete = false;
};

struct stUser
{
    string Username;
    string Password;
    short Permission;
};

vector<string> SplitStringToWords(string S, string delim = "#//#")
{
    vector<string> vWords;
    int pos = 0;
    string word;

    while((pos = S.find(delim)) != string::npos)
    {
        word = S.substr(0, pos);

        if(word != "")
        {
            vWords.push_back(word);
        }

        S.erase(0, pos + delim.length());
    }

    if(S != "")
    {
        vWords.push_back(S);
    }

    return vWords;
}

stClient ConvertClientLineToRecord(const string &Line, string delim = "#//#")
{
    stClient ClientData;
    vector<string> temp = SplitStringToWords(Line, delim);

    ClientData.AccNumber   = temp.at(0);
    ClientData.PinCode     = temp.at(1);
    ClientData.Name        = temp.at(2);
    ClientData.PhoneNumber = temp.at(3);
    ClientData.AccBalance  = stod(temp.at(4));

    return ClientData;
}

string ConvertClientRecordToLine(const stClient &Client, string delim = "#//#")
{
    string Line = "";

    Line += Client.AccNumber   + delim;
    Line += Client.PinCode     + delim;
    Line += Client.Name        + delim;
    Line += Client.PhoneNumber + delim;
    Line += to_string(Client.AccBalance);

    return Line;
}

string ConvertUserRecordToLine(const stUser &User, string delim = "#//#")
{
    string Line = "";

    Line += User.Username   + delim;
    Line += User.Password    + delim;
    Line += to_string(User.Permission);

    return Line;
}

stUser ConvertUserLineToRecord(const string &Line, string delim = "#//#")
{
    stUser UserData;
    vector<string> temp = SplitStringToWords(Line, delim);

    UserData.Username   = temp.at(0);
    UserData.Password   = temp.at(1);
    UserData.Permission = stoi(temp.at(2));

    return UserData;
}

vector<stClient> LoadClientsDataFromFile(const string &FileName)
{ 
    fstream MyFile;
    vector<stClient> Clients;

    MyFile.open(FileName, ios::in);

    if(MyFile.is_open())
    {
        string Line;

        while(getline(MyFile, Line))
        {
            Clients.push_back(ConvertClientLineToRecord(Line));
        }

        MyFile.close();
    }

    return Clients;
}

vector<stUser> LoadUsersDataFromFile(const string &FileName)
{
    fstream MyFile;
    vector<stUser> Users;

    MyFile.open(FileName, ios::in);

    if(MyFile.is_open())
    {
        string Line;

        while(getline(MyFile, Line))
        {
            Users.push_back(ConvertUserLineToRecord(Line));
        }

        MyFile.close();
    }

    return Users;
}

void SaveClientsRecordToFile(const string &FileName, vector<stClient> &vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if(MyFile.is_open())
    {
        for(stClient &C : vClients)
        {
            if(C.MarkForDelete != true)
            {
                MyFile << ConvertClientRecordToLine(C) << endl;
            }
        }

        MyFile.close();
    }
}

void AddLineToFile(const string &Line, const string &FileName)
{
    fstream MyFile;

    MyFile.open(FileName, ios::app);

    if(MyFile.is_open())
    {
        MyFile << Line << endl;
    }

    MyFile.close();
}

bool IsFeatureAvailableForUser(const short &FeatureNumber ,const short &Permission)
{
  return ((FeatureNumber & Permission) == Permission);
}

void DisplayAccessDenied()
{
 system("cls");

  cout<<"===============================\n";
  cout<<"Access Denied,\n";
  cout<<"You Don't have permission to do this,\n";
  cout<<"Please Contact your admin!\n";
  cout<<"===============================\n";
}

void PrintClientInfo(const stClient &Client)
{
    cout << "\nThe Following are the client details : " << endl;
    cout << "Account Number : " << Client.AccNumber   << endl;
    cout << "Pin Code       : " << Client.PinCode     << endl;
    cout << "Phone Number   : " << Client.PhoneNumber << endl;
    cout << "Name           : " << Client.Name        << endl;
    cout << "Account Balance: " << Client.AccBalance  << endl;
}

void PrintClientsTableHeader(const vector<stClient> &Clients)
{
    cout << "\n++++++++++++Clients List has (" << Clients.size() << ") Client(s)++++++++++++\n\n";
}

void PrintTotlalBalancesHeader(const vector<stClient> &Clients)
{
    cout << "\n++++++++++++Balances List has (" << Clients.size() << ") Client(s)++++++++++++\n\n";
}

void PrintTableColumnsForClients()
{
    cout << "|________________|_____________|_______________________|________________|________________\n";
    cout << "| Account Number | PinCode     | Client Name           | Phone          | Balance  \n";
    cout << "|________________|_____________|_______________________|________________|________________\n";
}

void PrintColumnsForTotalBalances()
{
    cout << "|________________|_______________________|________________\n";
    cout << "| Account Number | Client Name           | Balance  \n";
    cout << "|________________|_______________________|________________\n";
}

void PrintClientInfoForTotalBalances(const stClient &Client)
{
    cout << "|" << left << setw(16) << Client.AccNumber
         << "|" << left << setw(23) << Client.Name
         << "|" << left << setw(15) << Client.AccBalance << endl;
}

double CalculateTotalBalances(vector <stClient> &vClients)
{
  double TotalBalances = 0;

  for(stClient &C : vClients)
  {
    TotalBalances += C.AccBalance;
  }
  return TotalBalances;
}

void PrintTotalBalancesTable(vector<stClient> &vClients)
{
    system("cls");

    PrintTotlalBalancesHeader(vClients);
    PrintColumnsForTotalBalances();

    for(const stClient &x : vClients)
    {
        PrintClientInfoForTotalBalances(x);
    }

    cout << "|________________|_______________________|________________\n";

    cout<<"\nTotal Balances Are : "<<CalculateTotalBalances(vClients);
}

void PrintClientInfoInTable(const stClient &Client)
{
    cout << "|" << left << setw(16) << Client.AccNumber
         << "|" << left << setw(13) << Client.PinCode
         << "|" << left << setw(23) << Client.Name
         << "|" << left << setw(16) << Client.PhoneNumber
         << "|" << left << setw(15) << Client.AccBalance << endl;
}

void PrintClientsTable(const vector<stClient> &vClients)
{
    system("cls");
    
    
    PrintClientsTableHeader(vClients);
    PrintTableColumnsForClients();

    for(const stClient &x : vClients)
    {
        PrintClientInfoInTable(x);
    }

    cout << "|________________|_____________|_______________________|________________|________________\n";
}

string ReadAccountNumber()
{
    string S;

    cout << "Please enter Client Account Number : ";
    cin >> S;

    return S;
}

bool FindClientWithAccNumber(stClient &Client, string AccountNumber, const vector<stClient> &vClients)
{
    for(const stClient &x : vClients)
    {
        if(x.AccNumber == AccountNumber)
        {
            Client = x;
            return true;
        }
    }

    return false;
}

stClient ReadClientData(const string &AccountNumber)
{
    stClient Client;

    cout << "+++Taking Client Data+++\n\n";

    cin.ignore();
     
    Client.AccNumber = AccountNumber;

    cout << "\nEnter PinCode : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter PhoneNumber : ";
    getline(cin, Client.PhoneNumber);

    cout << "Enter Account Balance : ";
    cin >> Client.AccBalance;

    return Client;
}

void AddNewClientToFile(string &AccountNumber)
{
    stClient Client;
    string Line;

    Client = ReadClientData(AccountNumber);
    Line   = ConvertClientRecordToLine(Client);

    AddLineToFile(Line, ClientsFileName);
}

void CheckBeforeAddingClient(vector <stClient> &vClients)
{
 string AccountNumber;
 stClient Client;

 cout<<"\nEnter Client's Account Number : ";
 cin>>AccountNumber;

 while(FindClientWithAccNumber(Client ,AccountNumber ,vClients))
 {
  cout<<"\nClient With Account Number "<<AccountNumber<<" Already Exists !!"<<endl;

  cout<<"Please enter another Account Number : ";
  cin>>AccountNumber;
 }

 AddNewClientToFile(AccountNumber);
}

void AddClients(vector <stClient> &vClients)
{
    char Choice;

    do
    {
        system("cls");

        cout<<"===============================\n";
        cout<<"     Add New Client Screen     \n";
        cout<<"===============================\n";

        cout << "Adding new client :\n\n";

        CheckBeforeAddingClient(vClients);

        cout << "\nClient Added Successfully, Do you want to add more clients? (y/n) : ";
        cin >> Choice;

    } while(toupper(Choice) == 'Y');

    cout << "\nAll Clients Have been Added Successfully !!!";
}

void MarkClientForDelete(vector<stClient> &vClients, const string &AccountNumber)
{
    for(stClient &C : vClients)
    {
        if(C.AccNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            break;
        }
    }
}

void DeleteClientFromFile(vector<stClient> &vClients)
{
    stClient Client;
    char Choice;
    string AccountNumber;
    
    cout<<"\nEnter Client Account Number : ";
    cin>>AccountNumber;

    if(FindClientWithAccNumber(Client, AccountNumber, vClients))
    {
        PrintClientInfo(Client);

        cout << "\nAre you sure you want to delete this Client from file? (y/n)";
        cin >> Choice;

        if(toupper(Choice) == 'Y')
        {
            MarkClientForDelete(vClients, AccountNumber);
            SaveClientsRecordToFile(ClientsFileName, vClients);
            
            cout << "\nClient was deleted Successfully !";
        }
        else
        {
            cout << "\nClient wasn't deleted !";
        }
    }
    else
    {
        cout << "\nClient Not Found !";
    }
}

stClient ReadClientDataToUpdate(string AccountNumber)
{
    stClient Client;

    cout << "+++Taking Client Data+++\n\n";

    Client.AccNumber = AccountNumber;

    cin.ignore();

    cout << "Enter PinCode : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter PhoneNumber : ";
    getline(cin, Client.PhoneNumber);

    cout << "Enter Account Balance : ";
    cin >> Client.AccBalance;

    return Client;
}

void UpdateClient(vector<stClient> &vClient, string AccountNumber)
{
    for(stClient &C : vClient)
    {
        if(C.AccNumber == AccountNumber)
        {
            C = ReadClientDataToUpdate(AccountNumber);
            break;
        }
    }
}

void UpdateClientInFile(vector<stClient> &vClients)
{
    stClient Client;
    char Choice;
    string AccountNumber;
    
    cout<<"\nEnter Client's Account Number : ";
    cin>>AccountNumber;

    if(FindClientWithAccNumber(Client, AccountNumber, vClients))
    {
        PrintClientInfo(Client);

        cout << "\nAre you sure you want to Update this Client? (y/n)";
        cin >> Choice;

        if(toupper(Choice) == 'Y')
        {
            UpdateClient(vClients, AccountNumber);
            SaveClientsRecordToFile(ClientsFileName, vClients);

            cout << "\nClient Updated Successfully !";
        }
        else
        {
            cout << "\nClient Not Updated !";
        }
    }
    else
    {
        cout << "\nClient Not Found !";
    }
}

int ReadMainMenuChoice()
{
 short Choice;
 do
 {
   cout<<"\nChoose what do you want to do ? [1-8]"<<endl;
   cin>>Choice;

 } while (Choice > 8 || Choice < 1);

 return Choice;
}

void DisplayMainMenuScreen()
{
  cout << "============================================" << endl;
  cout << "         +++ Main Menue Screen +++              " << endl;
  cout << "============================================" << endl;
  cout << "       [1] Show Client List."<<endl;
  cout << "       [2] Add New Client."<<endl;
  cout << "       [3] Delete Client."<<endl;
  cout << "       [4] Update Client Info."<<endl;
  cout << "       [5] Find Client Info."<<endl;
  cout << "       [6] TransactionsMenu."<<endl;
  cout << "       [7] Manage Users."<<endl;
  cout << "       [8] Logout."<<endl;
  cout << "============================================" << endl;
}

void PauseAndReturn()
{
  cout<<"\n\nPress any key to return back to main menu...";
  system("pause>0");
}

void FindClient(vector <stClient> &vClients)
{
  string AccountNumber;
  stClient Client;

  cout<<"\nEnter Client's Account Number : ";
  cin>>AccountNumber;

  if(FindClientWithAccNumber(Client,AccountNumber,vClients))
  {
    PrintClientInfo(Client);
  }
  else
  {
   cout<<"\nClient Not Found!";  
  }
}

int ReadTransactionsChoice()
{
 short Choice;
 do
 {
   cout<<"\nChoose what do you want to do ? [1-4]"<<endl;
   cin>>Choice;

 } while (Choice > 4 || Choice < 1);

 return Choice;
}

void DisplayTransactionsMenu()
{
  cout << "============================================" << endl;
  cout << "      +++ Transactions Menue Screen +++              " << endl;
  cout << "============================================" << endl;
  cout << "       [1] Deposit."<<endl;
  cout << "       [2] Withdraw."<<endl;
  cout << "       [3] Total Balances."<<endl;
  cout << "       [4] Main Menu."<<endl;
  cout << "============================================" << endl;
}


void DepositOperation(vector <stClient> &vClients ,const string &AccountNumber ,const double &DepositAmount)
{
 for(stClient &C : vClients)
 {
   if(C.AccNumber == AccountNumber)
   {
      C.AccBalance += DepositAmount;
      break; 
   }
 }
}

void WithDrawMoney(vector <stClient> &vClients)
{
    string AccountNumber;
  stClient Client;
  double WithDrawAmmount;
  char Choice;
  
  system("cls");

  cout << "=======================================" << endl;
  cout << "        +++ Withdraw Screen +++       " << endl;
  cout << "=======================================" << endl;

  cout<<"\nPlease enter Client's Account Number : ";
  cin>>AccountNumber;

  while(!(FindClientWithAccNumber(Client ,AccountNumber ,vClients)))
  {
    cout<<"\nClient with account number ["<<AccountNumber<<"] not found !";
    cout<<"\nPlease enter Client's Account Number : ";
    cin>>AccountNumber;
  }

  PrintClientInfo(Client);
  
    cout<<"\nPlease Enter WithDrarw Amount : ";
    cin>>WithDrawAmmount;

    while(WithDrawAmmount<0 || Client.AccBalance<WithDrawAmmount)
    {
     cout<<"\nAmmount Exceeds Balance, You can Only WithDraw up to "<< Client.AccBalance<<" ,Please Enter Valid Ammount : ";
     cin>>WithDrawAmmount;
    }

  cout<<"\nAre you sure you want to performe this transaction (y/n) ?";
  cin>>Choice;

  if(toupper(Choice) == 'Y')
  {

    DepositOperation(vClients ,AccountNumber ,-WithDrawAmmount);
    SaveClientsRecordToFile(ClientsFileName ,vClients);
    
    cout<<"\nAmmount Withdrawed Successfully !";
  }
}

void DepositMoney(vector <stClient> &vClients)
{
  string AccountNumber;
  stClient Client;
  double Deposit;
  char Choice;
  
  system("cls");

  cout << "=======================================" << endl;
  cout << "        +++ Deposit Screen +++       " << endl;
  cout << "=======================================" << endl;

  cout<<"\nPlease enter Client's Account Number : ";
  cin>>AccountNumber;

  while(!(FindClientWithAccNumber(Client ,AccountNumber ,vClients)))
  {
    cout<<"\nClient with account number ["<<AccountNumber<<"] not found !";
    cout<<"\nPlease enter Client's Account Number : ";
    cin>>AccountNumber;
  }

  PrintClientInfo(Client);
  
  do
  {
    cout<<"\nPlease Enter Deposit Amount : ";
    cin>>Deposit;

  }while(Deposit<0);

  cout<<"\nAre you sure you want to performe this transaction (y/n) ?";
  cin>>Choice;

  if(toupper(Choice) == 'Y')
  {

    DepositOperation(vClients ,AccountNumber ,Deposit);
    SaveClientsRecordToFile(ClientsFileName ,vClients);
    
    cout<<"\nAmmount Deposited Successfully !";
  }
}

void DisplayLoginScreenHeader()
{
    cout<<"===============================\n";
    cout<<"         Login Screen     \n";
    cout<<"===============================\n";
}

void PrintUsersTableHeader(const vector<stUser> &Users)
{
    cout << "\n++++++++++++Users List has (" << Users.size() << ") Users(s)++++++++++++\n\n";
}

void PrintTableColumnsForUsers()
{
    cout << "|________________|_____________|_______________________|\n";
    cout << "| UserName       | Password    | Permissions           |\n";
    cout << "|________________|_____________|_______________________|\n";
}

short GiveUserPermissionOverClientList()
{
  char Choice;
  short Permission = 0;

  cout<<"\nDo you want to give full access : (y/n) ?";
  cin>>Choice;
  
  if(toupper(Choice) == 'Y')
     return -1;

  cout<<"\nDo you want to give access to : \n\n";
  
  cout<<"Show CLient List :  (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (1|Permission);

  cout<<"Add new CLient List : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (2|Permission);
  
  cout<<"Delete CLient List : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (4|Permission);
  
  cout<<"Update CLient List : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (8|Permission);
  
  cout<<"Find CLient List : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (16|Permission);
  
  cout<<"Transactions : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (32|Permission);
  
  cout<<"Manage Users : (y/n) ?";
  cin>>Choice;
  if(toupper(Choice) == 'Y') Permission = (64|Permission);

  return Permission;
 
}

void PrintUsersInfoInTable(const stUser &User)
{
    cout << "|" << left << setw(16) << User.Username
         << "|" << left << setw(13) << User.Password
         << "|" << left << setw(23) << User.Permission<<endl;
}

void PrintUsersTable(const vector <stUser> &vUsers)
{
   system("cls");

   PrintUsersTableHeader(vUsers);
   PrintTableColumnsForUsers();
   
   for(const stUser &x : vUsers)
   {
     PrintUsersInfoInTable(x);
   }

   cout << "|________________|_____________|_______________________|\n";
}

bool FindUserWithUserName(stUser &User, string UserName, const vector<stUser> &vUsers)
{
    for(const stUser &x : vUsers)
    {
        if(x.Username == UserName)
        {
           User = x;
           return true;
        }
    }

    return false;
}

void AddNewUserToFile(string &UserName ,string &Password ,short &Permission)
{
    stUser User;
    string Line;

    User.Username = UserName;
    User.Password = Password;
    User.Permission = Permission;

    Line   = ConvertUserRecordToLine(User);

    AddLineToFile(Line, UsersFileName);
}

void CheckBeforeAddingUser(vector <stUser> &vUsers ,string &UserName ,string &Password)
{
  stUser User;

  cout<<"\nEnter UserName : ";
  cin>>UserName;

  while(FindUserWithUserName(User ,UserName ,vUsers))
  {
    cout<<"\nUser With UserName "<<UserName<<" Already Exists !!"<<endl;

    cout<<"Please enter another User: ";
    cin>>UserName;
  }
  
  cout<<"\nEnter Password : ";
  cin>>Password;
  
}

void AddUsers(vector <stUser> &vUsers)
{
    string UserName ,Password;
    short Permission;
    
    char Choice;

    do
    {
        system("cls");

        cout<<"===============================\n";
        cout<<"     Add New User Screen     \n";
        cout<<"===============================\n";

        cout << "Adding new user :\n\n";

        CheckBeforeAddingUser(vUsers ,UserName ,Password);
        
        Permission = GiveUserPermissionOverClientList();

        AddNewUserToFile(UserName ,Password ,Permission);

        cout << "\nUser Added Successfully, Do you want to add more users? (y/n) : ";
        cin >> Choice;

    } while(toupper(Choice) == 'Y');

    cout << "\nAll users Have been Added Successfully !!!";
}

int ReadManageUsersMenuChoice()
{
 short Choice;
 do
 {
   cout<<"\nChoose what do you want to do ? [1-6]"<<endl;
   cin>>Choice;

 } while (Choice > 6 || Choice < 1);

 return Choice;
}

void DisplayManageUsersMenuScreen()
{
  cout << "============================================" << endl;
  cout << "       +++ Manage Users Menu Screen +++              " << endl;
  cout << "============================================" << endl;
  cout << "       [1] List Users."<<endl;
  cout << "       [2] Add New User."<<endl;
  cout << "       [3] Delete User."<<endl;
  cout << "       [4] Update User."<<endl;
  cout << "       [5] Find User."<<endl;
  cout << "       [6] MainMenu."<<endl;
  cout << "============================================" << endl;
}

void TransactionsMenu(vector <stClient> &vClients)
{
    while(true)
  {
    vClients = LoadClientsDataFromFile(ClientsFileName); 
    
    system("cls");
    DisplayTransactionsMenu();

    enTransactionsMenu choice = (enTransactionsMenu) ReadTransactionsChoice();

    switch (choice)
    {
      
    case Deposit:
      
      DepositMoney(vClients);
      break;

    case Withdraw:
      
      WithDrawMoney(vClients);
      break;

    case TotalBalances:
      
      PrintTotalBalancesTable(vClients);
      PauseAndReturn();
      break;

    case ReturnMainMenu:
      return;
      
    default:
      break;
    }
  }
}

void ManageUsersMenu(vector <stUser> &vUsers)
{
    while(true)
  {
    vUsers = LoadUsersDataFromFile(UsersFileName); 
    
    system("cls");
    DisplayManageUsersMenuScreen();

    enManageUsersMenu choice = (enManageUsersMenu) ReadManageUsersMenuChoice();

    switch (choice)
    {
      
    case ListUsers:

      PrintUsersTable(vUsers);
      PauseAndReturn();
      break;

    case AddUser:
    
      AddUsers(vUsers);
      PauseAndReturn();
      break;      
     
    case DeleteUser:
      break;
      
    case UpdateUser:
      break;
      
    case FindUser:
      break;
      
    case BackToMainMenu:
      return;

    default:
      break;
    }
  }
}

void MainMenu(vector <stClient> &vClients ,vector <stUser> &vUsers)
{

  while(true)
  {
    vClients = LoadClientsDataFromFile(ClientsFileName); 
    
    system("cls");
    DisplayMainMenuScreen();

    enMenuChoice choice = (enMenuChoice) ReadMainMenuChoice();

    switch (choice)
    {

    case Show:

        PrintClientsTable(vClients);
        PauseAndReturn();
        break;

    case Add:

        AddClients(vClients);
        PauseAndReturn();
        break;

    case Delete:
        
        DeleteClientFromFile(vClients);
        PauseAndReturn();
        break;

    case Update:

        UpdateClientInFile(vClients);
        PauseAndReturn();
        break;

    case Find:
        
        FindClient(vClients);
        PauseAndReturn();
        break;
    
    case Transactions:

        TransactionsMenu(vClients);
        break;

    case ManageUsers:

        ManageUsersMenu(vUsers);
        break;

    case Logout:
         return;

    default:
        break;
    }       
  }
}

bool IsUserLoginInfoCorrect(const vector <stUser> &vUsers ,const string &Username ,const string &Password)
{
 for(const stUser &X : vUsers)
 {
   if(X.Username == Username)
   {
    if(X.Password == Password)
    {
      return true;
    }
   }
 }
  return false;
}

void Login(vector <stUser> &vUsers ,vector <stClient> &vClients)
{
  string Username ,Password;
  
  vUsers = LoadUsersDataFromFile(UsersFileName);

  system("cls");
  DisplayLoginScreenHeader();  

  while(true)
  {
    cout<<"\nPlease enter Username : ";
    cin>>Username;

    cout<<"Please enter Password? : ";
    cin>>Password;

    if(IsUserLoginInfoCorrect(vUsers ,Username ,Password))
       return MainMenu(vClients ,vUsers);

    system("cls");
    cout<<"\nInvalid Username/Password Info!!!\n";
  
  }
}

int main()
{
 vector <stClient> vClients;
 vector <stUser> vUsers;

 while(true)
 {
  Login(vUsers ,vClients);
 }
 
}