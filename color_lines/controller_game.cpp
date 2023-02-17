#include "controller_game.h"

GameController::GameController(QObject* parent) : QObject(parent) {
#if defined(Q_OS_MAC)
  QString prefix = "/../resources/";
#elif defined(Q_OS_LINUX)
//    QString prefix = "C:\\User\\...\\Code\\Database\\";
#endif
  m_db = new DBmanager(QDir::currentPath() + prefix + "game.db");
  m_db->selectSettingsTable();
  m_db->selectGameBoardTable();
  m_gameModel = new GameModel();
}

GameController::~GameController() {
  delete m_gameModel;

  m_db->updateGameboardTable();
  m_db->updateSettingsTable();
  delete m_db;
}

GameModel* GameController::getModel() { return m_gameModel; }
