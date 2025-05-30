#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string &source)
{
    std::vector<std::string::iterator> spaceIterators = find_all(source.begin(), source.end(), [](char c)
                                                         { return std::isspace(static_cast<unsigned char>(c)); });

    std::set<Token> tokens;
    std::transform(
        spaceIterators.begin(), spaceIterators.end() - 1, spaceIterators.begin() + 1,
        std::inserter(tokens, tokens.end()),
        [&source](std::string::iterator begin, std::string::iterator end)
        {
            return Token(source, begin, end);
        }
    );
    std::erase_if(tokens, [](const Token &token) 
    {
        return token.content.empty();
    });

    return tokens;
}

std::set<Misspelling> spellcheck(const Corpus &source, const Dictionary &dictionary)
{
    namespace rv = std::ranges::views;
    auto view = source 
    | rv::filter([&dictionary](const Token &token) {
        return !dictionary.contains(token.content);
    }) 
    | rv::transform([&dictionary](const Token &token) {
        auto view = dictionary | rv::filter([&token](const std::string &word) {
            return levenshtein(token.content, word) <= 1;
        });
        std::set<std::string> suggestions(view.begin(), view.end());
        return Misspelling{ token, std::move(suggestions) };
    })
    | rv::filter([](const Misspelling &misspelling) {
        return !misspelling.suggestions.empty();
    });
    return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"