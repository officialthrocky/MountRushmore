#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "draft.h"
#include <chrono>
#include <stdlib.h>
using namespace std;

/*Function Definition*/
vector<string> ReadSettings(string filename);

int main()
{
  bool inApp = true;
  int choice;
  int case_mult = 0;
  int repeat = 1;
  bool HasCat = false;
  int ShowRandomDrafters = -1;
  string cat;
  bool settingChange = false;
  string sysmessage = " ";
  string buffer;
  vector<string> startup = ReadSettings("settings.txt");
  Draft draft(startup);
  vector<Player> sortedPlayers;
  while (inApp)
  {
    system("clear");
    draft.PrintTitle();
    draft.PrintMenuOptions();
    cout << draft.GetMessage() << endl;
    cout << "Enter a menu option: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1: // Randomize Drafters
      if (case_mult == 1)
      {
        repeat++;
        if (repeat > 1)
        {
          buffer = "Draft Order Randomized. x" + to_string(repeat);
        }
        if (draft.GetSetting(0) == 1)
        {
          buffer += "\n" + draft.PrintOrder();
        }
      }
      else
      {
        repeat = 1;
        buffer = "Draft Order Randomized.";
        if (draft.GetSetting(0) == 1)
        {
          buffer += "\n" + draft.PrintOrder();
        }
      }
      case_mult = choice;
      draft.RandomizeOrder();
      draft.SetMessage(buffer);
      break;

    case 2: // Edit Category
      if (case_mult == 2)
      {
        repeat++;
        if (repeat > 1)
        {
          buffer = to_string(repeat);
          draft.SetMessage("Category Edited. x" + buffer);
        }
      }
      else
      {
        repeat = 1;
        draft.SetMessage("Category Edited.");
      }
      case_mult = choice;
      cout << "Enter new category: ";
      getline(cin, cat);
      draft.SetCategory(cat);
      HasCat = true;
      break;

    case 3: // Run Draft
      case_mult = choice;
      if (HasCat)
      {
        draft.RunSnakeDraft();
        draft.SetMessage("Draft Completed. Leaderboard updated.");
        system("clear");
        draft.PrintTable();
        draft.CountScore();
        /*Space to add points for winners and rankings and update them to each player for records*/
      }
      else
      {
        draft.SetMessage("Please set a category before running.");
      }
      HasCat = false;
      break;

    case 4: // Display leaderboard
      if (draft.GetPlayers() >= 3)
      {
        sortedPlayers = draft.SortLeader();
        system("clear");
        draft.PrintLeaderboard(sortedPlayers);
      }
      else
      {
        draft.SetMessage("Minimum of 3 players required for leaderboards.");
      }
      break;
    case 5:
      system("clear");
      settingChange = draft.PrintSettings();
      break;
    case 6: // Quit Program
      case_mult = choice;
      inApp = false;
      system("clear");
      break;

    default:
      sysmessage = "Invalid menu choice. Please try again.";
      break;
    }
    // Add Function to append segment to output file
  }
}

/*Function Code*/

vector<string> ReadSettings(string filename)
{
  vector<string> settings;
  ifstream fin;
  string parse;
  fin.open(filename);
  if (fin.fail())
  {
    cout << "Error opening preset. Please check Spelling" << endl;
  }
  // Assigning first setting to draft preset
  fin >> parse;
  settings.push_back(parse);
  // Assiging second setting to category (Default "Null")
  fin >> parse;
  settings.push_back(parse);
  // This reads in rest of file as playernames
  int i = 0;
  fin.close();
  return settings;
}