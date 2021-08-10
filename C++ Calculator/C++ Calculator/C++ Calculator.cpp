// C++ Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


class Calculator {

private:
    double num1, num2;
    char oper;

public:
    Calculator() {
        num1 = 0;
        num2 = 0;
        oper = ' ';
    }

    Calculator(int n1, int n2, char o) {
        num1 = n1;
        num2 = n2;
        oper = o;
    }

    double getNum1() { return num1; }
    void setNum1(int n1) { num1 = n1; }

    double getNum2() { return num2; }
    void setNum2(int n2) { num2 = n2; }

    double getOper() { return oper; }
    void setOper(char o) { oper = o; }

    double Calculation(){
        int result = 0;
        switch(oper){
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
        }
        return result;
    }

    //Takes expression and changes reference string from main as the result of the expression. 
    void EvalExpression(string &str) {
 
        vector <double> nums;
        vector <char> opers;

        //Concatination of multiple chars in str, is made from chars in temp and put into nums
        string concat;         

        //Put info into correct vectors
        for (int i = 0; i < str.size(); i+=1) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
                opers.push_back(str[i]);
                nums.push_back(stod(concat));
                concat = "";
            }
            else {    
                concat += str[i];
            }
        }
        nums.push_back(stod(concat));

        bool hasMult_Div;

     

        while (nums.size() > 1 && !opers.empty()) {
            hasMult_Div = false;
            for (int i = 0; i < opers.size(); i++) {
                if (opers[i] == '*' || opers[i] == '/') {
                    hasMult_Div = true;
                }
            }
            
            if((opers[0] == '*' || opers[0] == '/') && hasMult_Div) {
                setNum1(nums[0]);
                setNum2(nums[1]);
                setOper(opers[0]);
                nums.push_back(Calculation());
                nums.erase(nums.begin(), nums.begin() + 2);
                opers.erase(opers.begin());

            }

            else if ((opers[0] == '+' || opers[0] == '-') && hasMult_Div) {
                opers.push_back(opers[0]);
                opers.erase(opers.begin());
                nums.push_back(nums[0]);
                nums.erase(nums.begin());
            }

            else if ((opers[0] == '+' || opers[0] == '-') && hasMult_Div == false) {
                setNum1(nums[0]);
                setNum2(nums[1]);
                setOper(opers[0]);
                nums.push_back(Calculation());
                nums.erase(nums.begin(), nums.begin() + 2);
                opers.erase(opers.begin());
            }
        }   
        str = to_string(nums[0]);
        return;
    }
};


int main()
{
    //Standard Calculator
    string str, parSubstr, tempStr;
    Calculator calc;
    do {
        getline(cin, str);
        while (str.size() > 0) {
            str.erase(remove(str.begin(), str.end(), ' '), str.end());
            if (str.find_first_of('(') == -1) {
                calc.EvalExpression(str);
                cout << stod(str) << endl;
                str = "";
            }
            else {
                int lastPar = str.rfind('(');
                tempStr = str.substr(lastPar);
                int parSize = tempStr.find(')') - 1;
                parSubstr = str.substr(str.rfind('(') + 1, parSize);
                calc.EvalExpression(parSubstr);
                str.erase(str.rfind('('), parSize + 2);
                str.insert(lastPar, parSubstr);
                
                
            }
        }
        cout << endl;
    } while (true);

    system("pause");
    return 0;
}

