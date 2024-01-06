#include <iostream>
#include <random>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Record {
public:
    std::map<int, std::map<std::string, std::string>> BANK_AC_RECORD;
};

class Create_AC : public Record {
public:
    Create_AC() {
        auto flag = true;
        while (flag == true) {
            
            system("cls");
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(10000, 99999);

            int accountNumber = distribution(gen);
            auto it = BANK_AC_RECORD.find(accountNumber);

            while (it != BANK_AC_RECORD.end()) {
                cout << "\nWait till we find the perfect Account number for you" << endl;
                accountNumber = distribution(gen);
                it = BANK_AC_RECORD.find(accountNumber);
            }

            std::string name;
            int aadhar;
            double initialDeposit;
            cout<<"::::::::::Creating New Bank Account ::::::::::::\n  ";

            cout << "\nENTER THE NAME : ";
            cin >> name;
            cout << "\nENTER THE AADHAR NUMBER : ";
            cin >> aadhar;
            cout << "\nENTER INITIAL DEPOSIT AMOUNT : ";
            cin >> initialDeposit;

            std::string aadharStr = to_string(aadhar);
            std::string depositStr = to_string(initialDeposit);

            std::random_device rd1;
            std::mt19937 gen1(rd1());
            std::uniform_int_distribution<int> distribution1(10000000, 1000000000);
            double IFSC = distribution1(gen1);
            std::string IFSCStr = to_string(IFSC);

            BANK_AC_RECORD[accountNumber] = {
                {"NAME", name},
                {"AADHAR", aadharStr},
                {"BALANCE", depositStr},
                {"IFSC CODE", IFSCStr}
            };
            std::ofstream outFile(std::to_string(accountNumber)+ "_transaction.txt", std::ios::app);
            if (!outFile.is_open()) {
                   std::cerr << "Error opening the file!" << std::endl;
               }
            else{
                outFile<<"\nNAME : "<< BANK_AC_RECORD[accountNumber]["NAME"] << "\n"
                << "AADHAR : " << BANK_AC_RECORD[accountNumber]["AADHAR"] << "\nBALANCE :"
                << BANK_AC_RECORD[accountNumber]["BALANCE"] << "\nIFSC CODE : "<< BANK_AC_RECORD[accountNumber]["IFSC CODE"] << endl;
                
            }

            cout << "\nAccount created successfully with Account Number: " << accountNumber << endl;

            cout << "HERE ARE THESE DETAILS:\nNAME: " << BANK_AC_RECORD[accountNumber]["NAME"] << "\n"
                 << "AADHAR : " << BANK_AC_RECORD[accountNumber]["AADHAR"] << "\nBALANCE :"
                 << BANK_AC_RECORD[accountNumber]["BALANCE"] << "\nIFSC CODE : " << BANK_AC_RECORD[accountNumber]["IFSC CODE"] << endl;
            cout << "\n Enter termination or continuation code :: ";
            int num = 0;
            cout<<"\nENTER 0 for terminating Account Creation , else to add more , ENTER 1\n";
            cin >> num;
            if (num==1){
                flag = true;
                
            }
            else{
                flag = false;
            }
            // set flag to false to terminate
            

        }
    }
    
    ~Create_AC() {
        cout << "\n" << endl;
    }
};

class Deposit_Record : public Record {
public:
    void deposit(std::map<int, std::map<std::string, std::string>>& bankRecords) {
        system("cls");
        int deposit_ac;
        cout << "\nENTER ACCOUNT NUMBER : ";
        cin >> deposit_ac;
        auto it = bankRecords.find(deposit_ac);

        if (it == bankRecords.end()) {
            cout << "\nACCOUNT NOT FOUND" << endl;
        } else {
            int deposit;
            cout << "\nENTER DEPOSIT AMOUNT : ";
            cin >> deposit;

            int currentBalance = stoi(bankRecords[deposit_ac]["BALANCE"]);
            currentBalance += deposit;
            std::string currentBalanceStr = to_string(currentBalance);
            bankRecords[deposit_ac]["BALANCE"] = currentBalanceStr;

            cout << "DEPOSITED " << deposit << " IN ACCOUNT NUMBER " << deposit_ac
                 << ". CURRENT BALANCE IS " << bankRecords[deposit_ac]["BALANCE"] << endl;
            std::fstream file(std::to_string(deposit_ac) + "_transaction.txt", std::ios::in | std::ios::out);
            if (!file.is_open()) {
                    std::cerr << "Error opening the file!" << std::endl;
            }
            else{
                file.seekp(0, std::ios::end);
                file<<"\nDeposited "<<deposit<<" .Current Balance "<<currentBalance;
            }
        }
    }
};

class Withdraw_Record : public Record {
public:
    void withdraw(std::map<int, std::map<std::string, std::string>>& bankRecords) {
        system("cls");
        int withdraw_ac;
        cout << "\nENTER ACCOUNT NUMBER : ";
        cin >> withdraw_ac;
        auto it = bankRecords.find(withdraw_ac);

        if (it == bankRecords.end()) {
            cout << "\nACCOUNT NOT FOUND" << endl;
        } else {
            int withdrawal;
            cout << "\nENTER WITHDRAWAL AMOUNT : ";
            cin >> withdrawal;

            int currentBalance = stoi(bankRecords[withdraw_ac]["BALANCE"]);

            if (withdrawal > currentBalance) {
                cout << "INSUFFICIENT FUNDS" << endl;
            } else {
                currentBalance -= withdrawal;
                std::string currentBalanceStr = to_string(currentBalance);
                bankRecords[withdraw_ac]["BALANCE"] = currentBalanceStr;

                cout << "WITHDREW " << withdrawal << " FROM ACCOUNT NUMBER " << withdraw_ac
                     << ". CURRENT BALANCE IS " << bankRecords[withdraw_ac]["BALANCE"] << endl;
                std::fstream file(std::to_string(withdraw_ac) + "_transaction.txt", std::ios::in | std::ios::out);
                if (!file.is_open()) {
                        std::cerr << "Error opening the file!" << std::endl;
                }
                else{
                    file.seekp(0, std::ios::end);
                    file<<"\nWithdrawed "<<withdrawal<<" .Current Balance "<<currentBalance;
                }
            }
        }
    }
};
class Bank_Transfer : public Record{
public :
    void Transfer(std::map<int, std::map<std::string, std::string>>& bankRecords){
        system("cls");
        int Sender_ac ;
        int Reciever_ac;
        auto flag = false ;
        cout<<"\nFROM A/C Number :  ";
        cin>>Sender_ac;
        auto it_sender = BANK_AC_RECORD.find(Sender_ac);
        while(flag == false){
            if (it_sender != BANK_AC_RECORD.end()) {
                cout <<"\nACCOUNT DOESN'T EXIST , ENTER THE CORRECT ACCOUNT NUMBER\n" << endl;
            }
            else{
                cout<<"\nTO A/C Number :  ";
                cin>>Reciever_ac;
                auto it_reciever = BANK_AC_RECORD.find(Reciever_ac);
                if (it_reciever != BANK_AC_RECORD.end()) {
                    cout <<"\nACCOUNT DOESN'T EXIST , ENTER THE CORRECT ACCOUNT NUMBER\n" << endl;
                }
                else{
                    int Amount ;
                    cout<<"\nEnter the amount to be transfered :  ";
                    cin>>Amount;
                    int sender_bal = stoi(bankRecords[Sender_ac]["BALANCE"]);
                    int recieve_bal = stoi(bankRecords[Reciever_ac]["BALANCE"]);
                    sender_bal = sender_bal-Amount;
                    recieve_bal = recieve_bal+Amount;
                    std::string senderStr = to_string(sender_bal);
                    std::string recieveStr = to_string(recieve_bal);
                    bankRecords[Sender_ac]["BALANCE"] = senderStr;
                    bankRecords[Reciever_ac]["BALANCE"] = recieveStr;
                    cout<<"\nBalance for A/c number  "<<Sender_ac<<" amounts to "<<bankRecords[Sender_ac]["BALANCE"];
                    cout<<"\nBalance for A/c number  "<<Reciever_ac<<" amounts to "<<bankRecords[Reciever_ac]["BALANCE"];
                    std::fstream file(std::to_string(Sender_ac) + "_transaction.txt", std::ios::in | std::ios::out);
                    if (!file.is_open()) {
                            std::cerr << "Error opening the file!" << std::endl;
                    }
                    else{
                        file.seekp(0, std::ios::end);
                        file<<"\nDebited "<<Amount<<" to Reciever "<<bankRecords[Reciever_ac]["NAME"];
                    }
                    std::fstream afile(std::to_string(Reciever_ac) + "_transaction.txt", std::ios::in | std::ios::out);
                    if (!afile.is_open()) {
                            std::cerr << "Error opening the file!" << std::endl;
                    }
                    else{
                        afile.seekp(0, std::ios::end);
                        afile<<"\nCredited "<<Amount<<" by Sender "<<bankRecords[Sender_ac]["NAME"];
                    }
                    
                    
                    cout<<"\n*****Transfer Successful*****\n";
                    flag = true;
                    
                    
                }
                
            }
        }
        
        
    }
    
    
};

class Statement : public Record {
public:
    void OUT_FILE(){
        int num;
        cout<<"\nENTER BANK ACCOUNT NUMBER : ";
        cin>>num;
        
        // Open the file for reading
        std::fstream file(std::to_string(num) + "_transaction.txt", std::ios::in | std::ios::out);


        // Check if the file is successfully opened
        if (!file.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            
        }

        // Read and print the content of the file
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        // Close the file
        file.close();
    }
    
};


int main() {
    auto flag = true;
    int num = 0;
    
    Create_AC a1;

    while (flag == true) {
        cout<< "\n \n \n 1. Deposit\n"
             << "2. Withdraw\n"
             << "3. Transfer\n"
             << "4. Account Transaction Statement \n"
             << "Enter your choice (1-4, or any other number to exit): ";
        
        cin >> num;

        switch (num) {
            
            case 1: {
                Deposit_Record depobj;
                depobj.deposit(a1.BANK_AC_RECORD);
                break;
            }
            case 2: {
                Withdraw_Record withobj;
                withobj.withdraw(a1.BANK_AC_RECORD);
                break;
            }
            case 3: {
                Bank_Transfer BanktransfObj;
                BanktransfObj.Transfer(a1.BANK_AC_RECORD);
                break;
            }
            case 4:{
                Statement s1;
                s1.OUT_FILE();
                break;
            }
            default: {
                flag = false;
                break;
            }
        }
    }

    return 0;
}

//g++ -std=c++11  BANK_MANAGEMENT_SYSTEM.cpp -o BANK_SYSTEM  to convert to executable //

