#include "tuffle.h"

#include "gamestate.h"

crow::json::wvalue TuffleGame::GameStateInJson() {
  // The JSON object to return to the Tuffle Frontend.
  crow::json::wvalue game_state_json({});

  // ===================== YOUR CODE HERE =====================
  // Fill the game_state_json with the data expected by the
  // Tuffle frontend. The frontend expects the following keys:
  //   1. "answer"
  //   2. "boardColors"
  //   3. "guessedWords"
  //   4. "gameStatus"
  //   5. "errorMessage"
  //   6. [OPTIONAL] "letterColors"
  // See the "JSON Response" section of tinyurl.com/cpsc121-f22-tuffle
  //
  // You can set the key in the JSON to a value like so:
  //             game_state_json[<key>] = <value>
  //
  // See below for an example to set the "answer" key:
  game_state_json["answer"] = game_state_.GetAnswer();  // Replace this!
  game_state_json["boardColors"] = game_state_.GetBoardColors();
  game_state_json["guessedWords"] = game_state_.GetGuessedWords();
  game_state_json["gameStatus"] = game_state_.GetGameStatus();
  game_state_json["errorMessage"] = game_state_.GetErrorMessage();
  // ==========================================================
  return game_state_json;
}