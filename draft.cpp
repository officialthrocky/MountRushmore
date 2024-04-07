#include "draft.h"
using namespace std;

Draft::Draft(vector<string> startup)
{
  /* Pulling Init Info from startup */
  draftType = startup.at(0);
  Category = startup.at(1);
  /* Checking the type of draft */
  if (draftType == "MountRushmore") // Mount Rushmore Type Draft
  {
    totalRounds = 4;
  }
  else if (draftType == "anything to add") // Spot for new preset
  {
    // add any new presets here
  }
  else // Draft type is default (10 round snake draft)
  {
    totalRounds = 10;
  }
  /*Initializing settings*/
  int numsettings = 1;
  for (int i = 0; i < numsettings; i++)
  {
    Settings.push_back(-1);
  }

  /*Reading in player names*/

  Player temp;
  string playername;
  cout << "Enter Drafters:" << endl;
  getline(cin, playername);
  while (playername != "-1")
  {
    temp.SetName(playername);
    Players.push_back(temp);
    getline(cin, playername);
  }
  // Filling picks in with round info
  string filler;
  int flip = 1;
  int start = 0;
  int picker = 0;
  for (int i = 0; i < totalRounds; i++)
  {
    for (int j = start; (j < Players.size() && j >= 0); j += flip)
    {
      filler = to_string(i + 1) + "." + to_string(picker + 1);
      Players.at(j).pushPick(filler);
      picker++;
    }
    flip *= -1;
    picker = 0;
    if (flip > 0)
    {
      start = 0;
    }
    else
    {
      start = Players.size() - 1;
    }
  }
};

void Draft::RandomizeOrder()
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine e(seed);
  for (int i = 0; i < 7; i++)
  {
    shuffle(Players.begin(), Players.end(), e);
  }
  // Clear now shuffled players picks
  for (int i = 0; i < Players.size(); i++)
  {
    Players.at(i).ClearPicks();
  }
  // Filling in Round and Pick info for new order
  //  Filling picks in with round info
  string filler;
  int flip = 1;
  int start = 0;
  int picker = 0;
  for (int i = 0; i < totalRounds; i++)
  {
    for (int j = start; (j < Players.size() && j >= 0); j += flip)
    {
      filler = to_string(i + 1) + "." + to_string(picker + 1);
      Players.at(j).pushPick(filler);
      picker++;
    }
    flip *= -1;
    picker = 0;
    if (flip > 0)
    {
      start = 0;
    }
    else
    {
      start = Players.size() - 1;
    }
  }
};

void Draft::RunSnakeDraft()
{
  int flip = 1;
  int start = 0;
  string pick;
  for (int i = 0; i < totalRounds; i++)
  {
    for (int j = start; (j < Players.size() && j >= 0); j += flip)
    {
      system("clear");
      PrintTable();
      cout << endl;
      cout << endl;
      cout << endl;
      cout << Players.at(j).GetName() << "'s pick: ";
      getline(cin, pick);
      Players.at(j).AddPick(pick, i);
    }
    flip *= -1;
    if (flip > 0)
    {
      start = 0;
    }
    else
    {
      start = Players.size() - 1;
    }
  }
};

string Draft::PrintOrder()
{
  string order = "";
  for (int i = 0; i < Players.size(); i++)
  {
    if (i < Players.size() - 1)
    {
      order += Players.at(i).GetName() + ", ";
    }
    else
    {
      order += Players.at(i).GetName();
    }
  }
  return order;
};

bool Draft::PrintSettings()
{
  int choice;
  bool inSettings = true;
  vector<int> tempsettings = Settings;
  while (inSettings)
  {
    system("clear");
    sysmessage = "";
    cout << StringHelper(62, " __      _   _   _                 ") << endl;
    cout << StringHelper(62, "/ _\\ ___| |_| |_(_)_ __   __ _ ___ ") << endl;
    cout << StringHelper(62, "\\ \\ / _ \\ __| __| | '_ \\ / _` / __|") << endl;
    cout << StringHelper(62, "_\\ \\  __/ |_| |_| | | | | (_| \\__ \\") << endl;
    cout << StringHelper(62, "\\__/\\___|\\__|\\__|_|_| |_|\\__, |___/") << endl;
    cout << StringHelper(62, "                         |___/     ") << endl;

    cout << endl;

    cout << StringHelper(62, "/================================\\") << endl;
    if (tempsettings.at(0) == -1)
    {
      cout << StringHelper(62, "||1. Randomize Drafters : False ||") << endl;
    }
    else
    {
      cout << StringHelper(62, "||1. Randomize Drafters : True  ||") << endl;
    }
    cout << StringHelper(62, "||2. Save and Quit              ||") << endl;
    cout << StringHelper(62, "||3. Quit W/O Saving            ||") << endl;
    cout << StringHelper(62, "\\================================/") << endl;
    cout << StringHelper(50, sysmessage) << endl;
    cout << "                  Select a setting to flip: ";
    cin >> choice;
    if (choice == 1)
    {
      tempsettings.at(0) = tempsettings.at(0) * -1;
    }
    else if (choice == 2)
    {
      inSettings = false;
      Settings = tempsettings;
      sysmessage = "Settings saved.";
      return true;
    }
    else
    {
      inSettings = false;
      sysmessage = "Settings not saved.";
      return false;
    }
  }
  return false;
}

void Draft::PrintTable()
{
  vector<string> rows;
  string round;
  string pick, holder;
  string sample;
  for (int i = 0; i < Players.size(); i++)
  {
    sample += StringHelper(25, Players.at(i).GetName());
  }
  rows.push_back(sample);
  sample = "";

  for (int i = 0; i < totalRounds; i++)
  {
    for (int j = 0; j < Players.size(); j++)
    {
      if (Players.at(j).GetPick(i) != "X")
      {
        sample += StringHelper(25, Players.at(j).GetPick(i));
      }
      else
      {
        round = to_string(i + 1);
        pick = to_string(j + 1);
        holder = round + "." + pick;
        sample += StringHelper(25, holder);
      }
    }
    rows.push_back(sample);
    sample = "";
  }
  /*Printing out completed work to console*/
  cout << StringHelper(25 * Players.size(), Category) << endl;
  for (int i = 0; i < rows.size(); i++)
  {
    cout << rows.at(i) << endl;
    cout << endl;
    cout << endl;
  }
};

void Draft::PrintLeaderboard(vector<Player> sorted)
{
  string first, second, third;
  first = StringHelper(24, sorted.at(0).GetName());
  second = StringHelper(24, sorted.at(1).GetName());
  third = StringHelper(24, sorted.at(2).GetName());
  cout << endl;
  cout << "########################################################################" << endl;
  cout << "# _     _____    _    ____  _____ ____  ____   ___    _    ____  ____  #" << endl;
  cout << "#| |   | ____|  / \\  |  _ \\| ____|  _ \\| __ ) / _ \\  / \\  |  _ \\|  _ \\ #" << endl;
  cout << "#| |   |  _|   / _ \\ | | | |  _| | |_) |  _ \\| | | |/ _ \\ | |_) | | | |#" << endl;
  cout << "#| |___| |___ / ___ \\| |_| | |___|  _ <| |_) | |_| / ___ \\|  _ <| |_| |#" << endl;
  cout << "#|_____|_____/_/   \\_\\____/|_____|_| \\_\\____/ \\___/_/   \\_\\_| \\_\\____/ #" << endl;
  cout << "########################################################################" << endl;
  cout << endl;
  cout << first << second << third << endl;
  cout << StringHelper(24, "___________")
       << StringHelper(24, "___________")
       << StringHelper(24, "___________") << endl;
  cout << StringHelper(24, "'._==_==_=_.'")
       << StringHelper(24, "'._==_==_=_.'")
       << StringHelper(24, "'._==_==_=_.'") << endl;
  cout << StringHelper(24, ".-\\:      /-.")
       << StringHelper(24, ".-\\:   _  /-.")
       << StringHelper(24, ".-\\:   _  /-.") << endl;
  cout << StringHelper(24, "| (|:. /|  |) |")
       << StringHelper(24, "| (|:.  _| |) |")
       << StringHelper(24, "| (|:.  _| |) |") << endl;
  cout << StringHelper(24, "'-|:. _|_ |-'")
       << StringHelper(24, "'-|:. |_  |-'")
       << StringHelper(24, "'-|:.  _| |-'") << endl;
  cout << StringHelper(24, "\\::.    /")
       << StringHelper(24, "\\::.    /")
       << StringHelper(24, "\\::.    /") << endl;
  cout << StringHelper(24, "'::. .'")
       << StringHelper(24, "'::. .'")
       << StringHelper(24, "'::. .'") << endl;
  cout << StringHelper(24, ") (")
       << StringHelper(24, ") (")
       << StringHelper(24, ") (") << endl;
  cout << StringHelper(24, "_.' '._ ")
       << StringHelper(24, "_.' '._ ")
       << StringHelper(24, "_.' '._") << endl;
  cout << StringHelper(24, "`\"\"\"\"\"\"\"`")
       << StringHelper(24, "`\"\"\"\"\"\"\"`")
       << StringHelper(24, "`\"\"\"\"\"\"\"`") << endl;
  cout << StringHelper(24, "Points: " + to_string(sorted.at(0).GetPoints()));
  cout << StringHelper(24, "Points: " + to_string(sorted.at(1).GetPoints()));
  cout << StringHelper(24, "Points: " + to_string(sorted.at(2).GetPoints()));

  for (int i = 0; i < 7; i++)
  {
    cout << endl;
  }
  cout << "Press enter to return";
  getline(cin, third);
}

void Draft::CountScore()
{
  string first, second, third;
  cout << "First Place: ";
  getline(cin, first);
  first.erase(remove(first.begin(), first.end(), '\n'), first.cend());
  cout << "Second Place: ";
  getline(cin, second);
  second.erase(remove(second.begin(), second.end(), '\n'), second.cend());
  cout << "Third Place: ";
  getline(cin, third);
  third.erase(remove(third.begin(), third.end(), '\n'), third.cend());
  for (int i = 0; i < Players.size(); i++)
  {
    if (Players.at(i).GetName() == first)
    {
      Players.at(i).AddPoints(3);
    }
    else if (Players.at(i).GetName() == second)
    {
      Players.at(i).AddPoints(2);
    }
    else if (Players.at(i).GetName() == third)
    {
      Players.at(i).AddPoints(1);
    }
  }
}

void Draft::EditPlayername()
{
  string playername;
  for (int i = 0; i < Players.size(); i++)
  {
    cin >> playername;
    Players.at(i).SetName(playername);
  }
  for (int i = 0; i < Players.size(); i++)
  {
    cout << Players.at(i).GetName() << endl;
  }
};

void Draft::SetCategory(string newCategory)
{
  Category = newCategory;
  string filler;
  int flip = 1;
  int start = 0;
  int picker = 0;
  for (int i = 0; i < Players.size(); i++)
  {
    Players.at(i).ClearPicks();
  }

  for (int i = 0; i < totalRounds; i++)
  {
    for (int j = start; (j < Players.size() && j >= 0); j += flip)
    {
      filler = to_string(i + 1) + "." + to_string(picker + 1);
      Players.at(j).pushPick(filler);
      picker++;
    }
    flip *= -1;
    picker = 0;
    if (flip > 0)
    {
      start = 0;
    }
    else
    {
      start = Players.size() - 1;
    }
  }
}

string Draft::StringHelper(int width, const string &str)
{
  int len = str.length();
  if (width < len)
  {
    return str;
  }
  int diff = width - len;
  int pad1 = diff / 2;
  int pad2 = diff - pad1;
  return string(pad1, ' ') + str + string(pad2, ' ');
}

vector<Player> Draft::SortLeader()
{
  vector<Player> sorted;
  sorted = Players;
  int i, j;
  bool swapped;
  for (i = 0; i < sorted.size() - 1; i++)
  {
    swapped = false;
    for (j = 0; j < sorted.size() - i - 1; j++)
    {
      if (sorted.at(j).GetPoints() < sorted.at(j + 1).GetPoints())
      {
        swap(sorted.at(j), sorted.at(j + 1));
        swapped = true;
      }
    }

    // If no two elements were swapped
    // by inner loop, then break
    if (swapped == false)
      break;
  }
  return sorted;
}

void Draft::PrintTitle()
{
  cout << " _____                                                  _____" << endl;
  cout << "( ___ )------------------------------------------------( ___ )" << endl;
  cout << " |   |                                                  |   | " << endl;
  cout << " |   |          __  __                   _              |   | " << endl;
  cout << " |   |          |  \\/  | ___  _   _ _ __ | |_           |   | " << endl;
  cout << " |   |          | |\\/| |/ _ \\| | | | '_ \\| __|          |   | " << endl;
  cout << " |   |          | |  | | (_) | |_| | | | | |_           |   | " << endl;
  cout << " |   |          |_|  |_|\\___/ \\__,_|_| |_|\\__|          |   | " << endl;
  cout << " |   |  ____            _                               |   | " << endl;
  cout << " |   | |  _ \\ _   _ ___| |__  _ __ ___   ___  _ __ ___  |   | " << endl;
  cout << " |   | | |_) | | | / __| '_ \\| '_ ` _ \\ / _ \\| '__/ _ \\ |   | " << endl;
  cout << " |   | |  _ <| |_| \\__ \\ | | | | | | | | (_) | | |  __/ |   | " << endl;
  cout << " |   | |_| \\_|\\__,_|___/_| |_|_| |_| |_|\\___/|_|  \\___| |   | " << endl;
  cout << " |___|                                                  |___| " << endl;
  cout << "(_____)------------------------------------------------(_____)" << endl;
}

void Draft::PrintMenuOptions()
{
  cout << StringHelper(62, "/========================\\") << endl;
  cout << StringHelper(62, "||1. Randomize Drafters ||") << endl;
  cout << StringHelper(62, "||2. Change Category    ||") << endl;
  cout << StringHelper(62, "||3. Start Draft        ||") << endl;
  cout << StringHelper(62, "||4. Leaderboard        ||") << endl;
  cout << StringHelper(62, "||5. Edit Settings      ||") << endl;
  cout << StringHelper(62, "||6. Exit Program       ||") << endl;
  cout << StringHelper(62, "\\========================/") << endl;
}