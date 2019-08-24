#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

/*
 * Chapter 12 Boot Camp Exercise - Anagrams and Hash Tables
 *
 * Initial Thoughts:
 * An anagram between two strings exists when their sorted order with
 * all spaces removed are the same. For example, "listen" and "istenl"
 * both have a sorted representation of "eilnst"
 *
 * I don't have much experience with hash tables, so I'll be referring to
 * the solutions a lot for this chapter.
 */

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  unordered_map<string, vector<string>> sortedStringToAnagrams;
  for(const string &s : dictionary)
  {
      // Sortes the string, uses it as a key, then appends
      // the original string as another value into the hash table
      string sorted_str(s);
      sort(begin(sorted_str), end(sorted_str));
      sortedStringToAnagrams[sorted_str].emplace_back(s);
  }

  vector<vector<string>> anagramGroups;
  for(const auto& [key, group] : sortedStringToAnagrams)
  {
      if(group.size() >= 2) // found anagrams
      {
          anagramGroups.emplace_back(group);
      }
  }
  return anagramGroups;
}
/*
 * Results:
 * All tests passed
 * Average running time:   50 ms
 * Median running time:    42 ms
 */

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(
      args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
      &UnorderedComparator<std::vector<std::vector<std::string>>>, param_names);
}
