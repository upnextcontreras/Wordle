#include <string>
#include <vector>

#include "dictionary.h"
#include "gamestate.h"
#include "server_utils/crow_all.h"

#ifndef TUFFLE_H
#define TUFFLE_H

class TuffleGame {
 public:
  TuffleGame(Dictionary dict)
      : dictionary_(dict), game_state_(dict.GetRandomTuffle()) {}

  // Called by the Tuffle frontend when the user clicks "Next Tuffle".
  void NewGame() { game_state_ = GameState(dictionary_.GetRandomTuffle()); }
  // Called by the Tuffle frontend when the user enters a letter.
  void LetterKeyPressed(char key) {
    if (!game_state_.isActive()) {
      return;
    }
    game_state_.SetErrorMessage("");

    std::vector<std::string> guessedWords = game_state_.GetGuessedWords();

    if (guessedWords.size() == 0) {
      guessedWords.push_back("");
    }

    int index = guessedWords.size() - 1;
    std::string word = guessedWords.at(index);

    if (word.length() != 5) {
      guessedWords.at(index) = word + key;
    }
    game_state_.SetGuessedWords(guessedWords);
  }

  std::string ColorMask(std::string guess, std::string answer) {
    std::string result = "BBBBB";
    for (int i = 0; i < answer.size(); i++) {
      if (answer[i] == guess[i]) {
        result[i] = 'G';
        answer[i] = '$';
        guess[i] = '#';
      }
    }
    for (int i = 0; i < answer.size(); i++) {
      if (answer.find(guess.at(i)) != std::string::npos) {
        result[i] = 'Y';
        answer[answer.find(guess.at(i))] = '$';
      }
    }
    return result;
  }
  // Called by the Tuffle frontend when the user submits a guess.

  void EnterKeyPressed() {
    std::vector<std::string> guessedWords = game_state_.GetGuessedWords();
    if (!game_state_.isActive() || guessedWords.size() == 0) {
      return;
    }
    game_state_.SetErrorMessage("");

    int index = guessedWords.size() - 1;
    std::string word = guessedWords.at(index);

    if (word.size() != 5) {
      game_state_.SetErrorMessage("Not enough letters!");
      return;
    } else if (!dictionary_.IsValidGuess(word)) {
      game_state_.SetErrorMessage("Not a valid guess!");
      return;
    }
    std::string color_mask = ColorMask(word, game_state_.GetAnswer());
    game_state_.GetBoardColors().push_back(color_mask);
    if (color_mask == "GGGGG") {
      game_state_.SetGameStatus("win");
    } else if (game_state_.GetGuessedWords().size() == 6) {
      game_state_.SetGameStatus("lose");
    } else {
      guessedWords.push_back("");
      game_state_.SetGuessedWords(guessedWords);
    }
  }

  // Called by the Tuffle frontend when the presses backspace.
  void DeleteKeyPressed() {
    std::vector<std::string> guessedWords = game_state_.GetGuessedWords();
    if (!game_state_.isActive() || guessedWords.size() == 0) {
      return;
    }
    int index = guessedWords.size() - 1;
    std::string word = guessedWords.at(index);

    if (word.length() != 0) {
      guessedWords[index] = word.substr(0, word.length() - 1);
      game_state_.SetGuessedWords(guessedWords);
    }
  }

  crow::json::wvalue GameStateInJson();

 private:
  GameState game_state_;
  Dictionary dictionary_;
};

#endif  // TUFFLE_H