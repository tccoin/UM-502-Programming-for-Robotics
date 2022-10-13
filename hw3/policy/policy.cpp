#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

using State = vector<int>;  // this defines the type State to be a vector of
                            // ints
using Action =
    vector<int>;  // this defines the type Action to be a vector of ints

// this function should print out a state to the given stream
// the ostream could be something like cout, or cerr
// or it could be a filestream
void printState(const State& state, ostream& stream) {
  // --- Your code here
  stream << state[0] << " " << state[1] << endl;
  // ---
}

State dynamics(const State& state, const Action& action) {
  State next_state(state.size());
  for (int j = 0; j < state.size(); j++) {
    next_state[j] = state[j] + action[j];
  }
  return next_state;
}

int main() {
  ifstream policyfile("policy.txt");
  ofstream outputfile("output.txt");

  const int StateSize = 2;
  const int ActionSize = 2;

  State key(StateSize);
  Action value(ActionSize);
  map<State, Action> policy;

  // read the policy file information into std::pair objects,
  // insert each std::pair into the map
  //  --- Your code here
  while (policyfile.peek() != EOF) {
    if (policyfile.peek() == '\n') {
      policyfile.get();
      continue;
    }
    policyfile >> key[0] >> key[1];
    policyfile >> value[0] >> value[1];
    policy.insert({key, value});
  }

  // ---

  // optional (but recommended) print out the policy to cout
  // to make sure that it was read in correctly
  //  --- Your code here
  for (const auto [key, value] : policy) {
    cout << key[0] << ", " << key[1] << " -> " << value[0] << ", " << value[1]
         << endl;
  }
  // ---

  // read in rollout
  ifstream rolloutfile("rollout.txt");
  State startState(StateSize);  // this stores the start stae
  int numSteps;                 // this is the number of steps in the rollout
  rolloutfile >> startState[0];
  rolloutfile >> startState[1];
  rolloutfile >> numSteps;
  rolloutfile.close();

  // Now use the the policy map to do the rollout
  //  --- Your code here
  State state(startState);
  printState(state, outputfile);
  for (int i = 0; i < numSteps; i++) {
    if (!policy.count(state)) {
      cerr << "State " << state[0] << " " << state[1]
           << " is not in policy, terminating.";
      return 1;
    }
    state = dynamics(state, policy[state]);
    printState(state, outputfile);
  }
  // ---

  outputfile.close();
  return 0;
}
