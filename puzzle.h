#ifndef PUZZLE_H
#define PUZZLE_H

struct Puzzle {
  Puzzle() : activated(false), solved(false), hasCooldown(false) {};

  void activate();
  void deactivate();
  bool isActive();
  bool isSolved();

  virtual void solve();

private:
  bool activated;
  bool solved;
  bool hasCooldown;
};

#endif
