#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// valid the user input phone number
bool isValidPhoneNumber(string &phone) {
  if (phone.length() != 8 || phone[3] != '-')
    return false;
  for (int i = 0; i < 8; ++i) {
    if (i == 3)
      continue;
    if (phone[i] < '2' || phone[i] > '9')
      return false;
  }
  return true;
}

// pass-by-reference necessary
vector<string> findCombinations(vector<string> &threeLetterWords,
                                vector<string> &fourLetterWords,
                                vector<string> &sevenLetterWords,
                                string &phoneNumber) {
  vector<string> result;
  string mapping[] = {"",    "",    "abc",  "def", "ghi",
                      "jkl", "mno", "pqrs", "tuv", "wxyz"};

  // need to figure out nested for loops to iterate through and combine combos
  for (int i = 0; i < threeLetterWords.size(); ++i) {
    string threeLetterWord = threeLetterWords[i];
    for (int j = 0; j < fourLetterWords.size(); ++j) {
      string fourLetterWord = fourLetterWords[j];
      bool match = true;
      for (int k = 0; k < 3 && match; ++k) {
        if (mapping[phoneNumber[k] - '0'].find(threeLetterWord[k]) ==
            string::npos) {
          match = false;
        }
      }
      for (int k = 0; k < 4 && match; ++k) {
        if (mapping[phoneNumber[k + 4] - '0'].find(fourLetterWord[k]) ==
            string::npos) {
          match = false;
        }
      }
      if (match) {
        result.push_back(threeLetterWord + " " + fourLetterWord);
      }
    }
  }
  // need to figure out if there's any 7letter word combos to match test cases
  for (int i = 0; i < sevenLetterWords.size(); ++i) {
    string sevenLetterWord = sevenLetterWords[i];
    bool match = true;
    for (int j = 0; j < 7 && match; ++j) {
      int phoneIndex; // need new variable to store index
      if (j < 3) {
        phoneIndex = j;
      } else {
        phoneIndex = j + 1;
      }
      if (mapping[phoneNumber[phoneIndex] - '0'].find(sevenLetterWord[j]) ==
          string::npos) {
        match = false;
      }
    }
    if (match) { // if boolean is true, match found and added to vector
      result.push_back(sevenLetterWord);
    }
  }
  return result;
}

int main() {
  // open "ShortList.txt"
  ifstream fin("ShortList.txt");

  if (!fin.is_open()) {
    cout << "Missing file!" << endl;
    return 1;
  }

  // set up vectors to store 3, 4 and 7 letter words
  string word;
  vector<string> threeLetterWords, fourLetterWords, sevenLetterWords;

  while (fin >> word) {
    if (word.length() == 3) {
      threeLetterWords.push_back(word);
    }
    if (word.length() == 4) {
      fourLetterWords.push_back(word);
    }
    if (word.length() == 7) {
      sevenLetterWords.push_back(word);
    }
  }

  fin.close();

  // get user phone number input
  string phoneNumber;
  cin >> phoneNumber;

  // you have to validate the phone number input is ###-####, use function
  if (!isValidPhoneNumber(phoneNumber)) {
    cout << "Invalid phone number" << endl;
    return 0;
  }

  // call function to figure out valid word combos
  vector<string> combinations = findCombinations(
      threeLetterWords, fourLetterWords, sevenLetterWords, phoneNumber);
  ofstream fout("output.txt");

  // if no valid combos
  if (combinations.empty()) {
    fout << "No results!" << endl;

    // if valid combos, output to output.txt
  } else {
    for (int i = 0; i < combinations.size(); ++i) {
      string combination = combinations[i];
      fout << combination << endl;
    }
  }

  fout.close();
  // use replit formating to make code look nice
  return 0;
}
