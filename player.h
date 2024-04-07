#include <vector>
#include <string>

using namespace std;

class Player
{
public:
  // Constructors
  Player();
  Player(string name);
  ~Player();
  void operator=(const Player &x);

  // Accessors
  string GetName() { return playerName; }
  vector<string> GetPicks() { return picks; }
  string GetPick(int index) { return picks.at(index); }
  int GetPoints() { return points; }

  // Mutators
  void AddPick(string pick, int index) { picks.at(index) = pick; }
  void pushPick(string pick) { picks.push_back(pick); }
  void SetName(string newName) { playerName = newName; }
  void ClearPicks() { picks.clear(); }
  void ResetPlayer(); // Resets all player's vectors and info excluding name for reruns of drafts
  void AddPoints(int earnings) { points += earnings; }

private:
  string playerName;
  vector<string> picks; // Vector to hold all of Player's Picks
  int points;
};
