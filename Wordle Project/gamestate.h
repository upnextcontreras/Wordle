#pragma once

#include <string>
#include <vector>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
 public:
  GameState(std::string answer) {
    answer_ = answer;
    game_status_ = "active";
    error_message_ = "";
  };
  std::string GetAnswer() const { return answer_; };

  void SetAnswer(std::string answer) { answer_ = answer; };

  std::vector<std::string>& GetBoardColors() { return board_colors_; };

  void SetAnswer(std::vector<std::string> boardColors) {
    board_colors_ = boardColors;
  };

  std::vector<std::string>& GetGuessedWords() { return guessed_words_; };

  void SetGuessedWords(std::vector<std::string> guessedWords) {
    guessed_words_ = guessedWords;
  };

  std::string GetGameStatus() const { return game_status_; };

  void SetGameStatus(std::string gameStatus) { game_status_ = gameStatus; };

  std::string GetErrorMessage() const { return error_message_; };

  void SetErrorMessage(std::string errorMessage) {
    error_message_ = errorMessage;
  };

  bool isActive() {
    if (game_status_ == "active") {
      return true;
    }
    return false;
  };

 private:
  std::string answer_;
  std::vector<std::string> board_colors_;
  std::vector<std::string> guessed_words_;
  std::string game_status_;
  std::string error_message_;

};
#endif  // GAMESTATE_H