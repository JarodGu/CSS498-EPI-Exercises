#include <string>
#include <algorithm>
#include <unordered_map>
#include "test_framework/generic_test.h"

using std::string;
using std::unordered_map;

/*
 * Exercise 12.2 - Is an Anonymous Letter Constructible?
 * Write a program that takes text for an anonymous letter and
 * text from a magazine and returns whether it's possible to
 * compose the letter using snip-its from the magazine.
 *
 * Initial Thoughts:
 * I'm not sure how I would use a hash table for this one. The
 * case where it's true is if for each character in the letter text,
 * there's at least that much or more in the magazine text.
 * The brute force method would be to go through each character
 * in the letter, then iterate through each character in the magazine.
 */
bool IsLetterConstructibleFromMagazine(const string &letter_text,
                                       const string &magazine_text)
{
    unordered_map<char, int> charFrequencyForLetter;
    // compute frequencies for all characters in letter
    for(char c: letter_text) // the colon means it's iterating from the beginning to end of letter_text
    {
        ++charFrequencyForLetter[c]; // add to hash map
    }

    // Check if characters in magazine_text can cover character in
    // charFrequencyForLetter
    for(char c  : magazine_text) // For every character in magazine text
    {
        if(auto it = charFrequencyForLetter.find(c); // If we can find it in the letter
            it != charFrequencyForLetter.cend())
        {
            --it->second;    // Not sure what second does. It's part of a returned pair from find()
                            // This decrements the character count
            if(it->second == 0)  // If the character count is 0, remove it from the hash map
            {
                charFrequencyForLetter.erase(it);
                if(empty(charFrequencyForLetter))
                {
                    // Early exit. Once all characters are found, no need to search more.

                    // all characters for letter_text are matched
                    break;
                }
            }
        }
    }
    // Empty charFrequencyForLetter means every char in letter_text can be
    // covered by a charcter in magazine text
    return empty(charFrequencyForLetter);
}

/*
 * Conclusion:
 * The book's solution makes clever use of an unordered map for the letter text.
 * Unorderd maps are composed of a key and value. In this case, the key is the character
 * and value the number of occurrences.
 * It makes a single pass over the magazine text and for every character, decrements
 * the letter's key-value. Once it reaches 0, it's removed from the map.
 * At the end, if the map is empty, then the count for all characters in the letter
 * are present in the magazine, thus return true.
 *
 * Results:
 * All tests passed!
 * Average running time:  185 us
 * Median running time:    49 us
 */

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"letter_text", "magazine_text"};
    return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                           "is_anonymous_letter_constructible.tsv",
                           &IsLetterConstructibleFromMagazine,
                           DefaultComparator{}, param_names);
}
