#include <iostream>
#include <random>
#include "DynamicArray.h"
using namespace std;

/*
1. Create a buy menu at the beggining of the game
  - things to buy: Oxen, wheels, food, ammo, water, clothing, medicine
  - Have price listed with each option
  - subtract cost of items bought from amt of money (1000)
2. Travel
  - Everyday a random number is picked and it initiates a random option
      *Someone steals
      *Someone gets sick
      *Nothing happens
      *Find a broken down wagon with extra supplies
      *A pack of wolves attacks you
      *etc
  - Everyday you are given the option to keep going, hunt, or rest
      *If you rest there is a 1 in 4 chance of a sick party member getting cured
      *If you choose to hunt there will be a number guessing game where if you guess right you         will get the food.
  - After a certain amout of days have passed there will be milestones like natural landmarks
      *There will also be shops after a certain amount of days to restock
  - At some point there will be ferries and you can choose to wait your turn or to try to cross     the river on your own
      *There is a 50% chance you get accros safely, if not you loose some items
3. Ending
  - When you get to 100 days you will get the win
*/

struct Party {
  string name;
  int food;
  int ammo;
  int oxen;
  int spares;
  int medicine;
  int clothing;
  int money;
};


struct Person {
  string name;
  int order;
  bool isSick;
  int health;
};

bool travel(int ans, string people[], string items[], Party p, Person* all, Person John, Person Sally, Person Tim);
DynamicArray alive;

int main() {
  srand(time(0));
  Party p = {"", 0, 0, 0, 0, 0, 0, 1500};
  string items[] = {"Food", "Food", "Ammo", "Ammo", "Oxen", "Wagon Spares", "Medicine", "Medicine", "Clothing", "Clothing"};
  Person John = {"John", 0, false, 100};
  Person Sally = {"Sally", 1, false, 100};
  Person Tim = {"Tim", 2, false, 100};
  Person all[3] = {John, Sally, Tim};
  string people[] = {"John", "Sally", "Tim"};
  DynamicArray array = DynamicArray();
  alive = DynamicArray();
  alive.add("John");
  alive.add("Sally");
  alive.add("Tim");
  int ans = 1;
  
  cout << "Welcome to the Oregon Trail! You will have to buy supplies, survive attacks, and take risks in order to successfully get to the end. Make your purchases below: " << endl;
  cout << endl;
  cout << "What is the name of your party?: ";
  std::getline (std::cin,p.name);
  cout << endl;
  cout << "1. Buy Food (10$ each)" << endl;
  cout << "2. Buy Ammo (20$ each)" << endl;
  cout << "3. Buy Oxen (100$ each)" << endl;
  cout << "4. Buy Wagon Spares (50$ each)" << endl;
  cout << "5. Buy Medicine (75$ each)" << endl;
  cout << "6. Buy Clothing (25$ each)" << endl;
  int amt;
  cout << endl;
  cout << "What would you like to buy for your Journey? Select a number then a quantity. Type 0 to finish. You Start with $1500." << endl;
  while (ans != 0) {
    cout << "Which item do you want?: ";
    cin >> ans;
    cout << "How much would you like?: ";
    cin >> amt;
    if (ans == 1) {
      if ((p.money - (amt*10)) >= 0) {
        p.money -= (amt*10);
        p.food += amt;
      }
      else if ((p.money - (amt*10)) < 0) {
        cout << "You do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    if (ans == 2) {
      if ((p.money - (amt*20)) >= 0) {
        p.money -= (amt*20);
        p.ammo += amt;
      }
      else if ((p.money - (amt*20)) < 0) {
        cout << "You do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    if (ans == 3) {
      if ((p.money - (amt*100)) >= 0) {
        p.money -= (amt*100);
        p.oxen += amt;
      }
      else if ((p.money - (amt*100)) < 0) {
        cout << "You do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    if (ans == 4) {
      if ((p.money - (amt*50)) >= 0) {
        p.money -= (amt*50);
        p.spares += amt;
      }
      else if ((p.money - (amt*50)) < 0) {
        cout << "You do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    if (ans == 5) {
      if ((p.money - (amt*75)) >= 0) {
        p.money -= (amt*75);
        p.medicine += amt;
      }
      else if ((p.money - (amt*25)) < 0) {
        cout << "You Do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    if (ans == 6) {
      if ((p.money - (amt*25)) >= 0) {
        p.money -= (amt*25);
        p.clothing += amt;
      }
      else if ((p.money - (amt*25)) < 0) {
        cout << "You Do not have enough money to buy that much of this item." << endl;
      }
      cout << "Money left: " + to_string(p.money) << endl;
    }
    cout << endl;
  }
  bool lose = travel(ans, people, items, p, all, John, Sally, Tim);
  if (lose == true) {
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Your entire party has died. Game Over" << endl;
  }
    
    
  else if (lose == false) {
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "You Did It! You Made It All The Way!" << endl;
  }
}

bool travel(int ans, string people[], string items[], Party p, Person* all, Person John, Person Sally, Person Tim) {
  if (ans == 0) {
    cout << "Now that you have your supplies your journey begins! Everyday you will be given the option to: Continue, Hunt, or Rest." << endl;
    int day = 0;
    int miles = 0;
    int hchance = (rand() % 3);
    string sick[3];
    int i = 0;
    bool lose = false;
    string actions[16][2] = {{to_string(1), " is sick."}, {to_string(2), "Your party has been robbed while you were sleeping."}, {to_string(3), "Your party is attacked by a pack of wolves."}, {to_string(4), "You found a broken down wagon with extra supplies."}, {to_string(5), "You find an oxen that seems to have run away from its party."}, {to_string(6), " is bitten by a snake"}, {to_string(7), "Nothing out of the ordinary"}, {to_string(8), "Nothing out of the ordinary"}, {to_string(9), "Nothing out of the ordinary"}, {to_string(10), "Nothing out of the ordinary"}, {to_string(11), "Nothing out of the ordinary"}, {to_string(12), "Nothing out of the ordinary"}, {to_string(13), "Nothing out of the ordinary"}, {to_string(14), "Nothing out of the ordinary"}, {to_string(15), "Nothing out of the ordinary"}, {to_string(16), "Nothing out of the ordinary"}};
    DynamicArray array = DynamicArray();
    while (miles <= 2170) {
      day += 1;
      for (i = 0; i <= 1000; i += 25) {
        if (day == i) {
          cout << "Supplies: " << endl;
          cout << "  Food: " + to_string(p.food) << endl;
          cout << "  Ammo: " + to_string(p.ammo)  << endl;
          cout << "  Oxen: " + to_string(p.oxen)  << endl;
          cout << "  Wagon Spares: " + to_string(p.spares)  << endl;
          cout << "  Medicine: " + to_string(p.medicine)  << endl;
          cout << "  Clothing: " + to_string(p.clothing)  << endl;
          cout << "  Money : " << p.money << endl;
          cout << endl;
          cout << "Shop: " << endl;
          cout << "  1. Buy Food (10$ each)" << endl;
          cout << "  2. Buy Ammo (20$ each)" << endl;
          cout << "  3. Buy Oxen (100$ each)" << endl;
          cout << "  4. Buy Wagon Spares (50$ each)" << endl;
          cout << "  5. Buy Medicine (25$ each)" << endl;
          cout << "  6. Buy Clothing (25$ each)" << endl;
          int amt;
          cout << endl;
          cout << "You have reached a milestone in your Journey. Take the time to restock on supplies!" << endl;
          int ans = 1;
          int bos;
          while (ans != 0) {
            cout << "Would you like to buy(0) or sell(1)?: " << endl;
            cin >> bos;
            if (bos == 0) {
              cout << "Which item do you want?: ";
              cin >> ans;
              cout << "How much would you like?: ";
              cin >> amt;
              if (ans == 1) {
                
                if ((p.money - (amt*10)) >= 0) {
                  p.money -= (amt*10);
                  p.food += amt;
                }
                else if ((p.money - (amt*10)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              if (ans == 2) {
                
                if ((p.money - (amt*20)) >= 0) {
                  p.money -= (amt*20);
                  p.ammo += amt;
                }
                else if ((p.money - (amt*20)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              if (ans == 3) {
                
                if ((p.money - (amt*100)) >= 0) {
                  p.money -= (amt*100);
                  p.oxen += amt;
                }
                else if ((p.money - (amt*100)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              if (ans == 4) {
                
                if ((p.money - (amt*50)) >= 0) {
                  p.money -= (amt*50);
                  p.spares += amt;
                }
                else if ((p.money - (amt*50)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              if (ans == 5) {
                
                if ((p.money - (amt*25)) >= 0) {
                  p.money -= (amt*25);
                  p.medicine += amt;
                }
                else if ((p.money - (amt*25)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              if (ans == 6) {
                
                if ((p.money - (amt*25)) >= 0) {
                  p.clothing += amt;
                  p.money -= (amt*25);
                }
                else if ((p.money - (amt*25)) < 0) {
                  cout << "You do not have enough money to buy that much of this item." << endl;
                }
                cout << "Money left: " + to_string(p.money) << endl;
              }
              cout << endl;
            }
            if (bos == 1) {
              cout << "Which item do you want to sell?: ";
              cin >> ans;
              cout << "How much would you like to sell?: ";
              cin >> amt;
              switch (ans) {
                case 1:
                  if ((p.food - amt) >= 0) {
                    p.money += (amt*10);
                    p.food -= amt;
                  }
                  else if ((p.food - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
                case 2:
                  
                  if ((p.ammo - amt) >= 0) {
                    p.money += (amt*20);
                    p.ammo -= amt;
                  }
                  else if ((p.ammo - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
                case 3:
                  
                  if ((p.oxen - amt) >= 0) {
                    p.money += (amt*100);
                    p.oxen -= amt;
                  }
                  else if ((p.oxen - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
                case 4:
                  
                  if ((p.spares - amt) >= 0) {
                    p.money += (amt*50);
                    p.spares -= amt;
                  }
                  else if ((p.spares - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
                case 5:
                  
                  if ((p.medicine - amt) >= 0) {
                    p.money += (amt*25);
                    p.medicine -= amt;
                  }
                  else if ((p.medicine - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
                case 6:
                  
                  if ((p.clothing - amt) >= 0) {
                    p.money += (amt*25);
                    p.clothing -= amt;
                  }
                  else if ((p.clothing - amt) < 0) {
                    cout << "You do not have enough supplies to sell that much of this item." << endl;
                  }
                  cout << "Money left: " + to_string(p.money) << endl;
                  break;
              }
              cout << endl;
            }
          }
        }
      }
      int act = (rand() % 16);

      //------------------------------------------------------
      if (act == 0) {
        int r = (rand() % 3);
        if (alive.contains(people[r])) {
          if (array.size < 3) {
            while (true) {
              r = (rand() % 3);
              if (alive.contains(people[r])) {
                if (array.contains(people[r]) == false) {
                  array.add(people[r]);
                  p.medicine -= 1;
                  cout << people[r] + " got sick. 1 medicine is used and you can rest to heal faster." << endl;
                  break;
                }
              }
            }
          }
        }
      }
      if (p.medicine >= 1) {
        hchance = (rand() % 5);
        if (p.clothing <= 0) {
          hchance = (rand() % 7);
        }
      }
      if (p.medicine < 1) {
        hchance = (rand() % 8);
        if (p.clothing <= 0) {
          hchance = (rand() % 10);
        }
      }
      
      //-----------------------------------------------------
      if (p.money > 50) {
        if (act == 1) {
          cout << "Your party has been robbed while you were sleeping. You lost 50 coins." << endl;
          p.money -= 50;
        }
      }
      //-------------------------------------------------------
      if (act == 2) {

        if (p.food < 5) {
          cout << "Your party was attacked by a pack of wolves. John loses health and 1 clothing." << endl;
          if (p.clothing > 0) {
            p.clothing -= 1;
          }
          if (p.clothing >= 1) {
            John.health -= 5;
          }
          if (p.clothing <= 0) {
            John.health -= 10;
          }
        }
        
        if (p.food >= 5) {
          cout << "Your party was attacked by a pack of wolves. You lose 5 food and 1 clothing." << endl;
          p.food -= 5;
          if (p.clothing > 0) {
            p.clothing -= 1;
          }
        }
      }
      //---------------------------------------------------

      if (act == 3) {
        int fchance = (rand() % 9);
        int achance = (rand() % 2) + 1;
        cout << "You found a broken down wagon with extra supplies! You find: " + to_string(achance) + " " + items[fchance] + "!" << endl;
        if (fchance == 0) {
          p.food += achance;
        }
        if (fchance == 1) {
          p.food += achance;
        }
        if (fchance == 2) {
          p.ammo += achance;
        }
        if (fchance == 3) {
          p.ammo += achance;
        }
        if (fchance == 4) {
          p.oxen += achance;
        }
        if (fchance == 5) {
          p.spares += achance;
        }
        if (fchance == 6) {
          p.medicine += achance;
        }
        if (fchance == 7) {
          p.medicine += achance;
        }
        if (fchance == 8) {
          p.clothing += achance;
        }
        if (fchance == 9) {
          p.clothing += achance;
        }
        cout << endl;
      }


      //-----------------------------------------------------------------------------------

      if (act == 4) {
        int snake = (rand() % 3);
        if (alive.contains(people[snake])) {
          cout << people[snake] << " is bitten by a snake" << endl;
          if (people[snake] == "John") {
            John.health -= 10;
          }
          if (people[snake] == "Sally") {
            Sally.health -= 10;
          }
          if (people[snake] == "Tim") {
            Tim.health -= 10;
          }
        }
      }

      //-------------------------------------------------------------------------
      if (p.oxen > 0) {
        if (act == 5) {
          cout << "One of your oxen dies,  + 20 Food!" << endl;
          p.oxen -= 1;
          p.food += 20;
        }
      }
      
      if (p.spares > 0) {
        if (act == 6) {
          cout << "One of your wagon wheels break,  -1 Wagon Spare." << endl;
          p.spares -= 1;
        }
      }
      //-------------------------------------------------------------------------
      
      if (act == 7) {
        cout << "You decide to help a lost traveler. In exchange for your hospitality they give you 100 coins!" << endl;
        p.money += 100;
        if (p.food > 0) {
          p.food -= 1;
        }
        if (p.clothing > 0) {
          p.clothing -= 1;
        }
      }
      
      int opt;
      int dec = true;
      while (dec == true) {
        cout << "It is day " + to_string(day) + ". What would you like to do? Continue(1), Hunt(2), Rest?(3), Look at Supplies(4), or Heal Party Members(5)?: ";
        cin >> opt;
        if (opt == 1) {
          dec = false;
          miles += 30;
          if (p.spares <= 0) {
            miles -= 5;
          }
          if (p.oxen <= 0) {
            miles -= 10;
          }
          continue;
        }
        if (opt == 2) {
          p.ammo -= 1;
          int hunting = (rand() % 2) + 1;
          int hans = 0;
          cout << "Pick a number between 1 and 3." << endl;
          cin >> hans;
          if (hans == hunting) {
            p.food += 10;
            cout << "You win! +10 Food" << endl;
          }
          if (hans != hunting) {
            cout << "Tough luck, no food for you." << endl;
            }
          }
          if (opt == 3) {
            day += 1;
            dec = false;
            if (p.medicine >= 1) {
              hchance = (rand() % 3);
              if (p.clothing <= 0) {
                hchance = (rand() % 5);
              }
            }
            if (p.medicine < 1) {
              hchance = (rand() % 7);
              if (p.clothing <= 0) {
                hchance = (rand() % 9);
              }
            }
          }
          if (opt == 4) {
            cout << "Resources: " << endl;
            cout << "  Food: " + to_string(p.food) << endl;
            cout << "  Ammo: " + to_string(p.ammo)  << endl;
            cout << "  Oxen: " + to_string(p.oxen)  << endl;
            cout << "  Wagon Spares: " + to_string(p.spares)  << endl;
            cout << "  Medicine: " + to_string(p.medicine)  << endl;
            cout << "  Clothing: " + to_string(p.clothing)  << endl;
            cout << "  Money : " << p.money << endl;
            cout << endl;
            cout << "Party Health: " << endl;
            cout << "  John's Health: " << John.health << endl;
            cout << "  Sally's Health: " << Sally.health << endl;
            cout << "  Tim's Health: " << Tim.health << endl;
            cout << "Distance Traveled: " << endl;
            cout << "  " << miles << " Miles" << endl;
          }
          if (opt == 5) {
            if (p.medicine > 0) {
              int choice = 0;
              cout << "Which Party Member Would You Like To Heal?: John(1), Sally(2), or Tim(3)?: ";
              cin >> choice;
              cout << endl;
              cout << "One Medicine Is Used To Regain 15 Health!" << endl;
              p.medicine -= 1;
              if (choice == 1) {
                John.health += 15;
                if (John.health > 100) {
                  John.health = 100;
                }
              }
              if (choice == 2) {
                Sally.health += 15;
                if (Sally.health > 100) {
                  Sally.health = 100;
                }
              }
              if (choice == 3) {
                Tim.health += 15;
                if (Tim.health > 100) {
                  Tim.health = 100;
                }
              }
            }
            if (p.medicine <= 0) {
              cout << "You Do Not Have Enough Medicine To Heal A Party Member." << endl;
            }
          }
      }
      if (alive.contains("John")) {
        if (John.health < 100) {
          John.health += 3;
        }
      }
      if (alive.contains("Sally")) {
        if (Sally.health < 100) {
          Sally.health += 3;
        }
      }
      if (alive.contains("Tim")) {
        if (Tim.health < 100) {
          Tim.health += 3;
        }
      }
      cout << endl;
      
      if (John.health <= 0 && Sally.health <= 0 && Tim.health <= 0) {
        lose = true;
        return lose;
      }
      
      if (miles >= 2170) {
        lose = false;
      }
      
      if (hchance == 0) {
        if (array.contains("Sally") || array.contains("John") || array.contains("Tim")) {
          cout << array.get(0) + " has recovered from their illness" << endl;
          array.removeFirst();
        }
      }
      
      
      if (array.contains("Sally") && alive.contains("Sally")) {
        Sally.health -= 10;
      }
      if (array.contains("John") && alive.contains("John")) {
        John.health -= 10;
      }
      if (array.contains("Tim") && alive.contains("Tim")) {
        Tim.health -= 10;
      }
      
      
      if (John.health <= 0 && alive.contains("John")) {
        cout << "John has died" << endl;
        alive.remove("John");
      }
      if (Sally.health <= 0 && alive.contains("Sally")) {
        cout << "Sally has died" << endl;
        alive.remove("Sally");
      }
      if (Tim.health <= 0 && alive.contains("Tim")) {
        cout << "Tim has died" << endl;
        alive.remove("Tim");
      }
    if (p.food > 0) {
      p.food -= 1;
    }
    if (p.food <= 0) {
      John.health -= 10;
      Sally.health -= 10;
      Tim.health -= 10;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    }
  }
}