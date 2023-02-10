#include "controller_game.h"

GameController::GameController(QObject* parent) : QObject(parent) {
  m_db = new DBmanager(QDir::currentPath() + "/../resources/game.db");
  m_db->selectSettingsTable();
  m_db->selectGameBoardTable();
  m_gameModel = new GameModel();

  //  if (!Settings::getSettings().game_is_started()) {
  //    m_gameModel->addRandomPoints();
  //  }
}

GameController::~GameController() {
  delete m_gameModel;

  m_db->updateGameboardTable();
  m_db->updateSettingsTable();
  delete m_db;
}

GameModel* GameController::getModel() { return m_gameModel; }
