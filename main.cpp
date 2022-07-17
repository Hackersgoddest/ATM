#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

class ATM
{
private:
  // vector variable to store the names users whose cards have been registered
  vector<string> usersNames;
  // an array to keep track of user activities.
  string activitiesPerformed[10][10];
  // vector variable to store the corresponding users cards numbers
  vector<unsigned long long> usersCardNumbers;
  // vector variable to store the corresponding cards numbers pins
  vector<int> usersPins;
  // vector variable to store the corresponding users cards balance
  vector<float> userAccountBalance;
  // variables to help us iterate through the registered cards and also performs some validations
  int cardIndex = 0, pinIndex = 0, activity[10], tpm = 10;

public:
  // Function template for deallocation
  template<class del>
  void Delete(del *&num){
    delete num;
    num = nullptr;
  }
  // Function to register card
  void addCardDetails();
  // Function to allow already registered card to access various operations like check balance, deposit, etc.
  void login();
  // Function that display a menu
  void accountMenu();
  // Function that checks the validity of the user name(i.e the argument pass to it), i.e it ensures the user name contains only alphabets and maybe one hyphen(-)
  void isValidName(string &);
  // Function that checks validity the argument pass to it, i.e it ensures the argument contains only numbers
  void isDigit(string &);
  // Function that displays a menu
  void mainMenu();
  // Function that exit the program
  void exitMenu();
  // Fucntion that takes the program back to the accountMenu() function
  void Back();
  // Function that displays users account balance
  void checkBalance();
  // Function that allow the card user to deposit some amount into his or her account
  void deposit();
  // Function that allow the card user to withdraw some amount from his or her account
  void withdraw();
  // Function that  allow the card user to transfer some amount from his or her account to different registered account
  void transfer();
  // Function that display the user previous activities
  void displayActivities();
  // Function that checks the validity of the amount entered by the user.
  void isValidAmount(string &);
  // Function to display error message if the length of the card number is less than or greater than the expected length
  void isInvalidCardLength(const string);
  // Function to display error message if the length of the pin is less than or greater than the expected length
  void isInvalidPinLength(const string);
  // Declaring classs destructor
  ~ATM();
};

void ATM::isInvalidCardLength(const string number)
{
  if (number.length() < 10)
  {
    system("cls");
    cout << "ERROR: Card number length cannot be less than 10\n";
  }
  if (number.length() > 10)
  {
    system("cls");
    cout << "ERROR: Card number length cannot be greater than 10\n";
  }
}

void ATM::isInvalidPinLength(const string pin)
{
  if (pin.length() < 4)
  {
    system("cls");
    cout << "ERROR: Pin length cannot be less than 4\n";
  }
  if (pin.length() > 4)
  {
    system("cls");
    cout << "ERROR: Pin length cannot be greater than 4\n";
  }
}

void ATM::accountMenu()
{
  system("cls");
  string *option = new string;
  cout << "**********MENU**********" << endl
       << "* 1. Add Card Details  *" << endl
       << "* 2. Login Account     *" << endl
       << "* 0. Exit Menu         *" << endl
       << "************************" << endl;

  do
  {
    cout << "Enter option... ";
    getline(cin >> ws, *option);
    if (*option != "0" && *option != "1" && *option != "2")
      cout << "Invalid option\n";
  } while (*option != "0" && *option != "1" && *option != "2"); // Ensures the user enter a valid option, i.e either 1, 2, or 0.
  if (*option == "1")
  { 
    Delete<string>(option); 
    addCardDetails(); // Calling the addCardDetails function if the user enter 1
  }
  else if (*option == "2")
  {
    Delete<string>(option); 
    login(); // Calling the login function if the user enter 2
  }
  else
  {
    Delete<string>(option); 
    exitMenu(); // Calling the exitMenu function is the user enter 0
  }
}

void ATM::addCardDetails()
{
  system("cls");
  string *number = new string, *pin = new string, *name = new string;
  unsigned long long *card_num = new unsigned long long;
  int *pin_num = new int, *pinNum = new int;
  bool *cardNumberAlreadyExist = new bool;
  do
  {
    cout << "Enter user name... ";
    getline(cin >> ws, *name);
    isValidName(*name);
    if (name->length() < 3)
    {
      system("cls");
      cout << "User name length cannot be less than 3\n";
    }
    if (name->length() > 30)
    {
      system("cls");
      cout << "User name length cannot be greater than 30\n";
    }
  } while (name->length() < 3 || name->length() > 30); // Ensures that the length of user name is neither less than 3 nor greater than 30
  usersNames.push_back(*name);                        // adding name to the vector variable usersNames using the the push_back member function of string class
  Delete<string>(name);
  system("cls");
  do
  {
    *cardNumberAlreadyExist = false;
    do
    {
      cout << "Enter card number(must contain 10 digits)... ";
      getline(cin >> ws, *number);
      isDigit(*number);
      isInvalidCardLength(*number);
    } while (number->length() < 10 || number->length() > 10); // Ensures that the user enter exactly 10 digits
    *card_num = stoull(*number);                              // Convert number of string type to unsigned long long using stoull and stores it in card_num of unsigned long long type
    if (cardIndex == 0)                                     // This condition ensures that there is no check for existing card number at first registration of card number
      break;
    else
    {
      for (int index = 0; index < cardIndex; index++)
      {
        if (*card_num == usersCardNumbers[index])
        {
          system("cls");
          cout << "Card Number has already been registered\n";
          *cardNumberAlreadyExist = true;
          break;
        }
      }
    }
  } while (*cardNumberAlreadyExist); // ensures that the user enter card number that has not been registered yet
  usersCardNumbers.push_back(*card_num);
  Delete<string>(number), Delete<bool>(cardNumberAlreadyExist), Delete<unsigned long long>(card_num);
  do
  {
    system("cls");
    do
    {
      cout << "Enter your four digit pin... ";
      getline(cin >> ws, *pin);
      isDigit(*pin);
      isInvalidPinLength(*pin);
    } while (pin->length() < 4 || pin->length() > 4); // ensures user enter exactly four digits
    *pin_num = stoi(*pin);                            // conver pin of string type to integer with the help of the stoi and stores it in the pin_num of int type
    system("cls");
    // checks whether the user is familiar with the pin He or She is using to setup his or her card pin
    do
    {
      cout << "Enter the 4 digit pin again to confirm... ";
      getline(cin >> ws, *pin);
      isDigit(*pin);
      isInvalidPinLength(*pin);
    } while (pin->length() < 4 || pin->length() > 4);
    *pinNum = stoi(*pin);
    if (*pin_num != *pinNum)
    {
      system("cls");
      cout << "ERROR: The pin does not match\n";
      system("PAUSE");
    }
  } while (*pin_num != *pinNum); // ensures that the user enters pins which match before he or she can continue the process
  usersPins.push_back(*pin_num);
  userAccountBalance.push_back(1000.00); // Initially deposited $1000 to card which has been register
  activity[cardIndex] = 0;
  cardIndex += 1; // increasing the cardIndex to help stores information about users seperately;
  Delete<string>(pin), Delete<int>(pin_num), Delete<int>(pinNum);
  accountMenu();
}

void ATM::isValidName(string &user_name)
{
  bool *isValidName = new bool;
  *isValidName = false;
  while (!(*isValidName)) // ensures the user enters a valid name
  {
    *isValidName = true;
    int hyphen = 0;
    for (int y = 0; y < user_name.length(); y++)
    {
      if (!(isalpha(user_name[y]) || user_name[y] == ' ' || user_name[y] == '-'))
      {
        *isValidName = false;
        break;
      }
      if (user_name[y] == '-')
        hyphen++;
    }
    if (hyphen > 1)
      *isValidName = false;
    if (!(*isValidName))
    {
      system("cls");
      cout << "ERROR : Name can only contains alphabets\nEnter user name again... ";
      getline(cin >> ws, user_name);
    }
  }
  Delete<bool>(isValidName);
}

void ATM::isDigit(string &score)
{
  bool *isInteger = new bool;
  *isInteger = false;
  while (!(*isInteger)) // ensures the user enters a valid number
  {
    *isInteger = true;
    for (int i = 0; i < score.length(); i++)
    {
      if (!isdigit(score[i]))
      {
        *isInteger = false;
        break;
      }
    }
    if (!(*isInteger))
    {
      system("cls");
      cout << "ERROR: invalid number\n";
      cout << "Enter number...";
      getline(cin >> ws, score);
    }
  }
  Delete<bool>(isInteger);
}

void ATM::login()
{
  system("cls");
  string *number = new string, *pin = new string;
  unsigned long long *card_num = new unsigned long long;
  int *pin_num = new int, *counter = new int;
  *counter = 3;
  bool *cardNumberAlreadyExist = new bool, *isPinValid = new bool;
  *isPinValid = 0;
  do
  {
    system("cls");
    cout << "You have " << *counter << " attempts" << endl; // prompting the user about the number of chances he or she can attempt for that operation
    *cardNumberAlreadyExist = false;
    do
    {
      cout << "Enter card number(must contain 10 digits)... ";
      getline(cin >> ws, *number);
      isDigit(*number);
      isInvalidCardLength(*number);
    } while (number->length() < 10 || number->length() > 10);
    *card_num = stoull(*number);
    for (int index = 0; index < cardIndex; index++)
    {
      if (*card_num == usersCardNumbers[index])
      {
        *cardNumberAlreadyExist = true;
        pinIndex = index; // assigning index to pinIndex in order to know the card the user is trying to use to login.
        break;
      }
    }
    if (!(*cardNumberAlreadyExist))
    {
      cout << "ERROR: Card number has not been registered\n";
      system("PAUSE");
    }
    *counter -= 1;
  } while (!(*cardNumberAlreadyExist) && *counter > 0); // ensures the user does not login in with unregistered card
  Delete<string>(number), Delete<unsigned long long>(card_num), Delete<int>(counter);
  system("cls");
  if (*cardNumberAlreadyExist) // This block of codes will be executed if the user enters a register card number
  {
    Delete<bool>(cardNumberAlreadyExist);
    for (int i = 3; i > 0; i--)
    {
      cout << "You have " << i << " attempts\n";
      *isPinValid = false;
      do
      {
        cout << "Enter your 4 digit pin... ";
        getline(cin >> ws, *pin);
        isDigit(*pin);
        isInvalidPinLength(*pin);
      } while (pin->length() < 4 || pin->length() > 4);
      *pin_num = stoi(*pin);
      if (*pin_num == usersPins[pinIndex]) // checks whether the user has enter a valid pin than correspond to the card number with the help of pinIndex
      {
        *isPinValid = true;
        break;
      }
      else
      {
        system("cls");
        cout << "ERROR: Invalid Pin\n";
      }
    }
    Delete<string>(pin), Delete<int>(pin_num);

    if (*isPinValid){
      Delete<bool>(isPinValid);
      mainMenu(); // calling the mainMenu function if the user enters a valid pin that correspond to the card number used
    }
    else{
      Delete<bool>(isPinValid);
      accountMenu(); // calling the accountMenu function if the user fails to enter a valid pin that correspond to the card number used
    }
  }
  else{
    Delete<bool>(cardNumberAlreadyExist);
    accountMenu(); // calling the accountMenu function if the user fails to enter a regustered card number
  }
}

void ATM::mainMenu()
{
  system("cls");
  string *option = new string;
  int *opt = new int;
  cout << "**********MENU**********" << endl
       << "*   1. Check Balance   *" << endl
       << "*   2. Deposit         *" << endl
       << "*   3. Withdraw        *" << endl
       << "*   4. Transfer        *" << endl
       << "*   5. Activities      *" << endl
       << "*   0. Back            *" << endl
       << "************************" << endl;
  do
  {
    cout << "Enter option... ";
    getline(cin >> ws, *option);
    if (*option != "0" && *option != "1" && *option != "2" && *option != "3" && *option != "4" && *option != "5")
      cout << "Invalid option\n";
  } while (*option != "0" && *option != "1" && *option != "2" && *option != "3" && *option != "4" && *option != "5");
  *opt = stoi(*option);
  Delete<string>(option);
  switch (*opt)
  {
  case 1:
    Delete<int>(opt);
    checkBalance();
    break;
  case 2:
    Delete<int>(opt);
    deposit();
    break;
  case 3:
    Delete<int>(opt);
    withdraw();
    break;
  case 4:
    Delete<int>(opt);
    transfer();
    break;
  case 5:
    Delete<int>(opt);
    displayActivities();
    break;
  default:
    Delete<int>(opt);
    Back();
    break;
  }
}

void ATM::checkBalance()
{
  system("cls");
  cout << usersNames[pinIndex] << " your balance is : $" << fixed << setprecision(2) << userAccountBalance[pinIndex] << endl
       << "Press any key to continue...";
  cin.get();
  time_t now = time(0);
  char *t_now = ctime(&now);
  string *balance_time = new string;
  *balance_time = t_now;
  activitiesPerformed[pinIndex][activity[pinIndex]] = "You checked your balance on "+ *balance_time;
  ++activity[pinIndex];
  Delete<string>(balance_time);
  mainMenu();
}

void ATM::isValidAmount(string &amt)
{
  bool *isValidAmount = new bool;
  *isValidAmount = false;
  while (!(*isValidAmount))
  {
    *isValidAmount = true;
    int *dot_count = new int;
    *dot_count = 0;
    for (int i = 0; i < amt.length(); i++)
    {
      if (!isdigit(amt[i]) && amt[i] != '.' && amt[i] != '+' && amt[i] != '-')
      {
        *isValidAmount = false;
        break;
      }
      if (amt[i] == '.')
        *dot_count += 1;

      if (i == 0)
        continue;
      else
      {
        if (amt[i] == '+' || amt[i] == '-' || *dot_count > 1)
        {
          *isValidAmount = false;
          break;
        }
      }
    }
    Delete<int>(dot_count);
    if (amt == "-" || amt == "+" || amt == ".")
      *isValidAmount = false;
    if (!(*isValidAmount))
    {
      system("cls");
      cout << "ERROR : Invalid amount\nEnter amount again... ";
      getline(cin, amt);
    }
  }
  Delete<bool>(isValidAmount);
}

void ATM::deposit()
{
  system("cls");
  string *amount = new string;
  float *cashDeposited = new float;
  do
  {
    cout << "Enter amount you want to deposit... ";
    getline(cin >> ws, *amount);
    isValidAmount(*amount);
    *cashDeposited = stof(*amount);
    if (*cashDeposited < 1)
    {
      system("cls");
      cout << "ERROR: amount cannot be less than $1.00\n";
    }
  } while (*cashDeposited < 1);
  Delete<string>(amount);
  userAccountBalance[pinIndex] += *cashDeposited; // updating user account balance after the operation
  system("cls");
  cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
       << "You have succesfully deposited an amount of $" << fixed << setprecision(2) << *cashDeposited << " to your account." << endl
       << "Your current balance is $" << userAccountBalance[pinIndex] << endl
       << "Press any key to continue...";
  cin.get();
  time_t now = time(0);
  char *t_now = ctime(&now);
  string *deposit_time = new string;
  *deposit_time = t_now;
  stringstream *cashToString = new stringstream;
  *cashToString << fixed << setprecision(2)<< *cashDeposited;
  Delete<float>(cashDeposited);
  string *amountDeposited = new string;
  *amountDeposited = cashToString->str();
  activitiesPerformed[pinIndex][activity[pinIndex]] = "You deposited an amount of $" + *amountDeposited + " into your account on "+ *deposit_time;
  ++activity[pinIndex];
  Delete<string>(deposit_time), Delete<stringstream>(cashToString), Delete<string>(amountDeposited);
  mainMenu();
}

void ATM::withdraw()
{
  system("cls");
  if (userAccountBalance[pinIndex] > 0)
  {
    string *amount = new string;
    float *cashWithdraw = new float;
    do
    {
      cout << "Enter amount you want to withdraw... ";
      getline(cin >> ws, *amount);
      isValidAmount(*amount);
      *cashWithdraw = stof(*amount);
      if (*cashWithdraw < 1)
      {
        system("cls");
        cout << "ERROR: amount cannot be less than $1.00\n";
      }
      if (*cashWithdraw > userAccountBalance[pinIndex])
      {
        system("cls");
        cout << "ERROR: Amount cannot be greater than account balance\n";
      }
    } while (*cashWithdraw < 1 || *cashWithdraw > userAccountBalance[pinIndex]); // ensures that the user enters a valid amount which is not more than current balance
    Delete<string>(amount);
    string *pin = new string;
    int *pin_num = new int;
    bool *isPinValid = new bool;
    for (int i = 3; i > 0; i--) // This block of code inside this loop ensures that is the actual user who is performing the operation by requesting for the user pin
    {
      cout << "You have " << i << " attempts\n";
      *isPinValid = false;
      do
      {
        cout << "Enter your 4 digit pin to confirm the operation... ";
        getline(cin >> ws, *pin);
        isDigit(*pin);
        isInvalidPinLength(*pin);
      } while (pin->length() < 4 || pin->length() > 4);
      *pin_num = stoi(*pin);
      if (*pin_num == usersPins[pinIndex])
      {
        *isPinValid = true;
        break;
      }
      else
      {
        system("cls");
        cout << "ERROR: Invalid Pin\n";
      }
    }
    Delete<string>(pin), Delete<int>(pin_num);
    if (*isPinValid)
    {
      Delete<bool>(isPinValid);
      userAccountBalance[pinIndex] -= *cashWithdraw; // updating user account balance after the operation
      system("cls");
      cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
           << "You have succesfully withdraw an amount of $" << fixed << setprecision(2) << *cashWithdraw << " from your account." << endl
           << "Your current balance is $" << userAccountBalance[pinIndex] << endl
           << "Press any key to continue...";
      cin.get();
      time_t now = time(0);
      char *t_now = ctime(&now);
      string *withdraw_time = new string;
      *withdraw_time = t_now;
      stringstream *cashToString = new stringstream;
      *cashToString << fixed << setprecision(2)<< *cashWithdraw;
      string *amountWithdrawn = new string;
      *amountWithdrawn = cashToString->str();
      Delete<float>(cashWithdraw);
      activitiesPerformed[pinIndex][activity[pinIndex]] = "You withdrawn an amount of $" + *amountWithdrawn + " from your account on "+ *withdraw_time;
      ++activity[pinIndex];
      Delete<string>(withdraw_time), Delete<stringstream>(cashToString), Delete<string>(amountWithdrawn);
    }
    else{
      Delete<bool>(isPinValid);
      accountMenu();
    }
  }
  else
  {
    system("cls");
    cout << "Sorry " << usersNames[pinIndex] << ',' << endl
         << "Your balance is insufficient for this operation" << endl
         << "Press any key to continue...";
    cin.get();
  }
  mainMenu();
}

void ATM::transfer()
{
  system("cls");
  if (userAccountBalance[pinIndex] > 0)
  {
    string *number = new string;
    unsigned long long *card_num = new unsigned long long;
    int *pin_index = new int;
    bool *cardNumberAlreadyExist = new bool, *isPinValid = new bool;
    int *count = new int;
    *count = 0;

    do
    {
      *cardNumberAlreadyExist = false;
      do
      {
        cout << "Enter card number you want to transfer the money to... ";
        getline(cin >> ws, *number);
        isDigit(*number);
        isInvalidCardLength(*number);
      } while (number->length() < 10 || number->length() > 10);
      *card_num = stoull(*number);
      for (int index = 0; index < cardIndex; index++)
      {
        *pin_index = -1;
        if (*card_num == usersCardNumbers[index])
        {
          *cardNumberAlreadyExist = true;
          *pin_index = index;
          break;
        }
      }
      if (!(*cardNumberAlreadyExist))
      {
        system("cls");
        cout << "ERROR: The card number you are trying to send money to has not been registered yet\n";
      }
      if (*card_num == usersCardNumbers[pinIndex])
      {
        system("cls");
        cout << "Sorry " << usersNames[pinIndex] << ',' << endl
             << "You can't transfer money to yourself" << endl;
      }
      *count += 1;
      if (*count == 3 && (!(*cardNumberAlreadyExist) || (*card_num == usersCardNumbers[pinIndex])))
        system("PAUSE");
    } while ((!(*cardNumberAlreadyExist) || (*card_num == usersCardNumbers[pinIndex])) && *count < 3); // ensures that the user don't transfer money to himself or herself or to unregistered card
    Delete<string>(number), Delete<int>(count);
    system("cls");
    if (*cardNumberAlreadyExist && (*card_num != usersCardNumbers[pinIndex])) // ensures that the registered card number entered by the user is not the same as his or her card number, before the block of codes under it is executed
    {
      Delete<unsigned long long>(card_num), Delete<bool>(cardNumberAlreadyExist);
      string *amount = new string;
      float *cashTransfer = new float;
      do
      {
        cout << "Enter amount you want to transfer... ";
        getline(cin >> ws, *amount);
        isValidAmount(*amount);
        *cashTransfer = stof(*amount);
        if (*cashTransfer < 1)
        {
          system("cls");
          cout << "ERROR: amount cannot be less than $1.00\n";
        }
        if (*cashTransfer > userAccountBalance[pinIndex])
        {
          system("cls");
          cout << "ERROR: Amount cannot be greater than account balance\n";
        }
      } while (*cashTransfer < 1 || *cashTransfer > userAccountBalance[pinIndex]);
      Delete<string>(amount);
      system("cls");
      string *select = new string;
      cout << usersNames[pinIndex] << " are you sure you want to tranfer an amount of \n$"
           << fixed << setprecision(2) << *cashTransfer << " to " << usersNames[*pin_index] << endl
           << "1. YES" << endl
           << "2. NO" << endl;
      do
      {
        cout << "Enter choice... ";
        getline(cin >> ws, *select);
        if (*select != "1" && *select != "2")
        {
          cout << "ERROR: Invalid choice\n";
        }
      } while (*select != "1" && *select != "2");
      if (*select == "1")
      {
        Delete<string>(select);
        system("cls");
        string *pin = new string;
        int *pin_num = new int;
        for (int i = 3; i > 0; i--)
        {
          cout << "You have " << i << " attempts\n";
          *isPinValid = false;
          do
          {
            cout << "Enter your 4 digit pin to confirm the operation... ";
            getline(cin >> ws, *pin);
            isDigit(*pin);
            isInvalidPinLength(*pin);
          } while (pin->length() < 4 || pin->length() > 4);
          *pin_num = stoi(*pin);
          if (*pin_num == usersPins[pinIndex])
          {
            *isPinValid = true;
            break;
          }
          else
          {
            system("cls");
            cout << "ERROR: Invalid Pin\n";
          }
        }
        Delete<string>(pin), Delete<int>(pin_num);
        if (*isPinValid)
        {
          Delete<bool>(isPinValid);
          userAccountBalance[pinIndex] -= *cashTransfer;
          userAccountBalance[*pin_index] += *cashTransfer;
          system("cls");
          cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
               << "You have succesfully transfer an amount of $" << fixed << setprecision(2) << *cashTransfer << " from your account to" << endl
               << usersNames[*pin_index] << ", your current balance is $" << userAccountBalance[pinIndex] << endl
               << "Press any key to continue...";
          cin.get();
          time_t now = time(0);
          char *t_now = ctime(&now);
          string *transfer_time = new string;
          *transfer_time = t_now;  
          stringstream *cashToString = new stringstream;
          *cashToString << fixed << setprecision(2)<< *cashTransfer;
          string *amountTranferred = new string;
          *amountTranferred = cashToString->str();
          Delete<float>(cashTransfer);
          activitiesPerformed[pinIndex][activity[pinIndex]] = "You transferred an amount of $" + *amountTranferred + " from your account to " + usersNames[*pin_index] + ", card no. " + to_string(usersCardNumbers[*pin_index]) + " on "+  *transfer_time;
          ++activity[pinIndex];
          activitiesPerformed[*pin_index][activity[*pin_index]] = "You received an amount of $" + *amountTranferred + " from " + usersNames[pinIndex] + ", card no. " + to_string(usersCardNumbers[pinIndex]) + " on "+  *transfer_time;
          ++activity[*pin_index];
          Delete<string>(transfer_time), Delete<stringstream>(cashToString), Delete<string>(amountTranferred), Delete<int>(pin_index);
        }
        else{
          Delete<int>(pin_index), Delete<bool>(isPinValid);
          accountMenu();
          }
      }
      else{
        Delete<string>(select);
        mainMenu();
      }
    }
    Delete<unsigned long long>(card_num), Delete<bool>(cardNumberAlreadyExist);
  }
  else
  {
    system("cls");
    cout << "Sorry " << usersNames[pinIndex] << ',' << endl
         << "Your balance is insufficient for this operation" << endl
         << "Press any key to continue...";
    cin.get();
  }
  mainMenu();
}

void ATM::displayActivities()
{
  for (int count = activity[pinIndex] - 1, line = 1; count >= 0; count--, line++)
    cout << line << ". " << activitiesPerformed[pinIndex][count] << endl;
  if (!activity[pinIndex])
  {
    system("cls");
    cout << "no activity to show\n";
  }
  cout << "Press any key to continue...";
  cin.get();
  mainMenu();
}

void ATM::Back()
{
  accountMenu();
}

void ATM::exitMenu()
{
  system("cls");
  cout << "*************************************************" << endl
       << "*  THANKS FOR USING HACKERSGODDEST ATM MACHINE  *" << endl
       << "*************************************************" << endl
       << "Press any key to continue...";
  cin.get();
  exit(0); // terminates the program
}

ATM::~ATM()
{
  // deleting various information stored in the variables
  usersNames.clear(), userAccountBalance.clear(), usersCardNumbers.clear(), usersPins.clear();
  cardIndex = pinIndex = 0;
}

int main()
{
  // created a pointer object that is dynamically allocated
  ATM *account = new ATM;
  account->accountMenu();
  // deallocating pointer object
  delete account;
  account = nullptr;
  return 0;
}