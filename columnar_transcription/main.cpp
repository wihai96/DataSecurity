#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <list>
#include <numeric>
#include <functional>
#include <iterator>
#include <cstdlib>

using namespace std;

const string key = "zebras";

void PrintInGroupsOf5(const string & aString)
{
  for (size_t i = 0; i < aString.size(); i++)
  {
    cout << aString[i];
    if (i % 5 == 4)
      cout << ' ';
  }
}

string Encrypt(const string & aText)
{
  string encrypted;

  vector<vector<char>> columns(key.size(), vector<char>());

  for (size_t i = 0; i < aText.size(); i++)
  {
    columns[i % key.size()].push_back(aText[i]);
  }

  // sort the columns by using a sorted associative container
  map<char, vector<char>> sortedCols;
  for (size_t i = 0; i < key.size(); i++)
  {
    sortedCols[key[i]] = move(columns[i]);
  }

  for (auto &&[_, column] : sortedCols)
  {
    for (auto && ch : column)
    {
      encrypted.push_back(ch);
    }
  }

  return encrypted;
}

string Decrypt(const string & aEncryptedText)
{
  vector<vector<char>> columns(key.size(), vector<char>());

  // build the columns
  for (size_t i = 0; i < aEncryptedText.size(); i++)
  {
    columns[i % key.size()].push_back(' ');
  }

  // move the columns in the sorted order
  map<char, vector<char>> sortedCols;
  for (size_t i = 0; i < key.size(); i++)
  {
    sortedCols[key[i]] = move(columns[i]);
  }

  size_t encryptedPosition = 0;
  for (auto &&[ch, column] : sortedCols)
  {
    for (size_t i = 0; i < column.size(); i++)
    {
      column[i] = aEncryptedText[encryptedPosition++];
    }
  }

  // put the columns back in the original order
  columns.clear();
  for (auto && ch : key)
  {
    columns.push_back(move(sortedCols[ch]));
  }

  string decrypted;
  for (size_t i = 0; i < columns[0].size(); i++)
  {
    for (size_t j = 0; j < columns.size(); j++)
    {
      if (columns[j].size() <= i)
        break;

      decrypted += columns[j][i];
    }
  }

  return decrypted;
}

int main()
{
  string plainText;

  cout << "String to encrypt: ";
  getline(cin, plainText);

  // keep only the alpha characters
  plainText.erase(
    remove_if(plainText.begin(), plainText.end(), [](char ch) { return !isalpha(ch); }),
    plainText.end()
  );

  // make the string lowercase
  transform(plainText.begin(), plainText.end(), plainText.begin(), tolower);

  cout << "Plain text:     ";
  PrintInGroupsOf5(plainText);
  cout << '\n';

  auto encrypted = Encrypt(plainText);
  cout << "Encrypted text: ";
  PrintInGroupsOf5(encrypted);
  cout << '\n';

  auto decrypted = Decrypt(encrypted);
  cout << "Decrypted text: ";
  PrintInGroupsOf5(decrypted);
  cout << '\n';

  return 0;
}
