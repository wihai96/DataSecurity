#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <map>
#include <list>
#include <numeric>
#include <functional>
#include <iterator>
#include <cstdlib>

#define KEY "Cheie"

using namespace std;

map<char, pair<int, int>> coordinates;
char playfair[5][5]{};

vector<string> Split(const string & str)
{
  vector<string> result;

  for (int i = 0; i < str.size(); i += 5)
  {
    result.push_back(str.substr(i, 5));
  }

  return result;
}

string Join(const vector<string> & strings)
{
  return std::reduce(strings.begin(), strings.end());
}

string BifidEncrypt(const string & str)
{
  string result;

  for (auto & group : Split(str))
  {
    vector<int> coords;

    for (auto ch : group)
      coords.push_back(coordinates[ch].first);

    for (auto ch : group)
      coords.push_back(coordinates[ch].second);

    for (int i = 0; i < coords.size(); i += 2)
      result += playfair[coords[i]][coords[i + 1]];
  }

  return result;
}

string BifidDecrypt(const string & str)
{
  string result;

  for (auto & group : Split(str))
  {
    vector<int> coords;

    for (auto ch : group)
    {
      coords.push_back(coordinates[ch].first);
      coords.push_back(coordinates[ch].second);
    }

    for (int i = 0; i < group.size(); i++)
    {
      result += playfair[coords[i]][coords[i + group.size()]];
    }
  }

  return result;
}

void Build(const string & key)
{
  int line = 0;
  int col = 0;

  auto addKeyChar = [&](char ch) {
    ch = ch == 'j' ? 'i' : ch;

    if (coordinates.find(ch) != coordinates.end())
      return;

    coordinates[ch] = make_pair(line, col);
    playfair[line][col] = ch;

    col++;
    if (std::size(playfair[0]) == col)
    {
      col = 0;
      line++;
    }
  };

  for_each(key.begin(), key.end(), addKeyChar);

  for (auto ch = 'a'; ch <= 'z'; ch++)
  {
    addKeyChar(ch);
  }
}

string ToLower(const string & str)
{
  auto res = str;

  transform(res.begin(), res.end(), res.begin(), ::tolower);

  return res;
}

int main()
{
  cout << "Key=";
  string key;
  getline(cin, key);
  key.erase(
    remove_if(key.begin(), key.end(), [](char ch) { return !::isalpha(ch); }),
    key.end()
  );
  key = ToLower(key);

  Build(key);

  cout << "Plain text = ";
  string plainText;
  getline(cin, plainText);

  plainText.erase(
    remove_if(plainText.begin(), plainText.end(), [](char ch) { return !::isalpha(ch); }),
    plainText.end()
  );

  plainText = ToLower(plainText);

  auto encrypted = BifidEncrypt(plainText);
  cout << "Encrypted text: " << encrypted << endl;

  auto decrypted = BifidDecrypt(encrypted);
  cout << "Decrypted text: " << decrypted << endl;

  return 0;
}
