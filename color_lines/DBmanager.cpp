#include "DBmanager.h"

DBmanager::DBmanager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);
  m_tables = new _table_and_columns;
  if (m_db.open())
    qDebug() << "Database: connection ok";
  else
    qDebug() << "Error: fail connection with database";
}

DBmanager::~DBmanager() {
  delete m_tables;
  if (m_db.isOpen()) m_db.close();
}
