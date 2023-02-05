#include "controller_game.h"

GameController::GameController(QObject* parent) : QObject(parent) {
  DBmanager db(QDir::currentPath() + "/../resources/game.db");
  m_settings = db.getSettings();
  m_gameModel = new GameModel(m_settings);
}

GameController::~GameController() { delete m_gameModel; }

GameModel* GameController::getModel() { return m_gameModel; }
