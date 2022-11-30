#include "bfs.h"
#include "dfs.h"
#include "maze.h"
/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const {
  // HINT: use isStateValid()
  // --- Your code here
  std::vector<State> result;
  std::vector<std::pair<int, int>> offsets = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  if (allow_diagonal_) {
    std::vector<std::pair<int, int>> diag = {
        {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
    offsets.insert(offsets.end(), diag.begin(), diag.end());
  }
  State candidate;
  for (const auto &offset : offsets) {
    candidate = State(state.x + offset.first, state.y + offset.second);
    if (isStateValid(candidate)) {
      result.push_back(candidate);
    }
  }
  return result;
  // ---
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node) {
  // --- Your code here
  path_.push_back(node->state);
  while (node->parent) {
    node = node->parent;
    node->print();
    path_.push_back(node->state);
  }
  std::reverse(path_.begin(), path_.end());
  // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve() {
  // check start and goal are valid
  if (!pdef_.isStateValid(pdef_.startState()) ||
      !pdef_.isStateValid(pdef_.goalState())) {
    return false;
  }

  // if start and goal coincide, terminate
  auto start = pdef_.startState();
  if (pdef_.isGoal(start)) {
    // std::cout << "Start and goal are equal\n";
    return true;
  }

  NodePtr solution;
  // --- Your code here
  // add start and root
  auto nodePtr = std::make_shared<Node>();
  nodePtr->state = start;
  nodePtr->parent = NULL;
  addNode(nodePtr);
  visited_.push_back(start);
  todo.push(nodePtr);
  // search
  while (!todo.empty()) {
    // std::cout << "todo size: " << todo.size() << std::endl;
    const auto &curr = todo.front();
    todo.pop();
    // check curr
    if (pdef_.isGoal(curr->state)) {
      std::cout << "found goal" << std::endl;
      solution = curr;
      break;
    }
    // add neighbors
    auto candidates = pdef_.validStates(curr->state);
    for (const auto &candidate : candidates) {
      bool notVisited = std::find(visited_.begin(), visited_.end(),
                                  candidate) == visited_.end();
      if (notVisited) {
        // std::cout << "add todo: (" << candidate.x << ", " << candidate.y <<
        // ")" << std::endl;
        visited_.push_back(candidate);
        auto newNodePtr = std::make_shared<Node>();
        newNodePtr->state = candidate;
        newNodePtr->parent = curr;
        addNode(newNodePtr);
        todo.push(newNodePtr);
      }
    }
  }

  // ---

  // get the path from last node to root
  extractPath(solution);

  return true;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node) {
  // --- Your code here
  tree.push_back(node);
  // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool DFS::solve() {
  // check start and goal are valid
  if (!pdef_.isStateValid(pdef_.startState()) ||
      !pdef_.isStateValid(pdef_.goalState())) {
    return false;
  }

  // if start and goal coincide, terminate
  auto start = pdef_.startState();
  if (pdef_.isGoal(start)) {
    std::cout << "Start and goal are equal\n";
    return true;
  }

  NodePtr solution;
  // --- Your code here
  // add start and root
  auto nodePtr = std::make_shared<Node>();
  nodePtr->state = start;
  nodePtr->parent = NULL;
  addNode(nodePtr);
  visited_.push_back(start);
  todo.push(nodePtr);
  // search
  while (!todo.empty()) {
    const auto &curr = todo.top();
    todo.pop();
    // check curr
    if (pdef_.isGoal(curr->state)) {
      solution = curr;
      break;
    }
    std::cout << "check point: (" << curr->state.x << ", " << curr->state.y
              << ")" << std::endl;
    // add neighbors
    auto candidates = pdef_.validStates(curr->state);
    for (const auto &candidate : candidates) {
      bool notVisited = std::find(visited_.begin(), visited_.end(),
                                  candidate) == visited_.end();
      if (notVisited) {
        std::cout << "check candidate: (" << candidate.x << ", " << candidate.y
                  << ")"
                  << " notVisited: " << notVisited << std::endl;
        visited_.push_back(candidate);
        auto newNodePtr = std::make_shared<Node>();
        newNodePtr->state = candidate;
        newNodePtr->parent = curr;
        addNode(newNodePtr);
        todo.push(newNodePtr);
      }
    }
  }

  // ---

  // get the path from last node to root
  extractPath(solution);

  return true;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node) {
  // --- Your code here
  tree.push_back(node);
  // ---
}