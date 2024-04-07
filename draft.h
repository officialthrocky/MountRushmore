#include "player.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <random>
#include <format>
using namespace std;

class Draft
{
public:
  // Constructors
  Draft(vector<string> startup);
  //~Draft();

  // Debug & Test
  void EditPlayername();
  string StringHelper(int width, const string &str);

  // Accessors
  string GetCat() { return Category; }
  string GetType() { return draftType; }
  int GetRounds() { return totalRounds; }
  int GetPlayers() { return Players.size(); }
  vector<Player> SortLeader();
  string GetMessage() { return sysmessage; }
  int GetSetting(int index) { return Settings.at(index); }
  // Mutators
  void SetCategory(string newCategory); // Sets new draft category for display
  void RandomizeOrder();                // Randomizes order of pickers
  void RunSnakeDraft();
  void CountScore(); // Does all the entering of information
  void SetMessage(string sys) { sysmessage = sys; }

  // Print Functions
  string PrintOrder(); // Prints names in draft order
  void PrintTable();   // Prints names and picks in table form
  void PrintLeaderboard(vector<Player> sorted);
  void PrintMenuOptions();
  void PrintTitle();
  bool PrintSettings();

private:
  string sysmessage;
  string Category;  // Placeholder for category of Draft
  string draftType; // Determines type of draft (Currently supported: SnakeDraft, Regular Draft, ReverseDraft(Reverse order of existing draft));
  int totalRounds;  // Amount of rounds per draft
  vector<Player> Players;
  vector<int> Settings;
};
