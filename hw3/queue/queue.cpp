#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "robots.h"

using namespace std;

// define and implement a function here called compareBotsByName
// it should be of the proper form to be used as the comparison
// function in std::sort. You will use compareBotsByName and std::sort
// to sort a std::vector<Robot>
//  --- Your code here

bool compareBotsByName(Robot& a, Robot& b) { return a.getName() < b.getName(); }

// ---

int main() {
  ifstream botfile("bots.txt");
  ifstream jobfile("jobs.txt");
  ofstream outfile("output.txt");

  queue<Robot> bot_queue;

  // read the robots from botfile in to bot_queue
  // make sure you've looked at the definition
  // of the Robot class in robots.h first
  //  --- Your code here
  string robot_name, robot_type;
  while (botfile.peek() != EOF) {
    if (botfile.peek() == '\n') {
      botfile.get();
      continue;
    }
    botfile >> robot_name >> robot_type;
    bot_queue.emplace(robot_name, robot_type);
  }

  // ---

  // read in each job id and job in jobfile
  // and assign them to the robots as described in the problem
  //  --- Your code here
  int job_id;
  string job_name;
  while (jobfile.peek() != EOF) {
    if (jobfile.peek() == '\n') {
      jobfile.get();
      continue;
    }
    jobfile >> job_id >> job_name;
    while (true) {
      Robot& bot = bot_queue.front();
      auto& capability = TYPES2JOBS.at(bot.getType());
      bool found = find(capability.begin(), capability.end(), job_name) !=
                   capability.end();
      if (found) {
        bot.assignJob(job_id);
      }
      bot_queue.push(bot);
      bot_queue.pop();
      if (found) {
        break;
      }
    }
  }
  // ---

  vector<Robot> bots;

  // now that the jobs are assigned, get the robots from the queue
  // and put them in the bots vector
  // then sort that vector alphabetically using std::sort
  // you will need to use the compareBotsByName function above
  //  --- Your code here
  while (!bot_queue.empty()) {
    bots.push_back(bot_queue.front());
    bot_queue.pop();
  }
  sort(bots.begin(), bots.end(), compareBotsByName);

  // ---

  // print the bots to outfile and cout
  for (int i = 0; i < bots.size(); i++) {
    cout << bots[i].print(false);
    outfile << bots[i].print(false);
  }

  return 0;
}
