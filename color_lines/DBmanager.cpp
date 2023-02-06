#include "DBmanager.h"

DBmanager::DBmanager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);
  m_tables = new _table_and_columns;
  if (m_db.open())
    qDebug() << "Database: connection ok";
  else
    qDebug() << "Error: fail connection with database";
  createSettingsTable();
}

DBmanager::~DBmanager() {
  qDebug() << "m_tables before delete" << m_tables;
  delete m_tables;
  qDebug() << "m_tables after delete" << m_tables;
  if (m_db.isOpen()) {
    m_db.close();
    qDebug() << "db is close";
  }
}

Settings &DBmanager::getSettings() {
  QSqlQuery query;
  query.prepare(
      QString("SELECT * FROM %1 WHERE id = 1;").arg(m_tableNameSettings));
  if (!query.exec() || !query.next()) return m_settings;

  m_settings.m_default_color = query.value(1).toInt();
  m_settings.m_count_next_balls = query.value(2).toInt();
  m_settings.m_points_in_row = query.value(3).toInt();
  m_settings.m_height_field = query.value(4).toInt();
  m_settings.m_width_field = query.value(5).toInt();
  return m_settings;
}

bool DBmanager::createSettingsTable() {
  QSqlQuery query;
  query.prepare(QString("SELECT name FROM sqlite_schema WHERE type = 'table' "
                        "AND name = '%1';")
                    .arg(m_tableNameSettings));
  if (!query.exec() || query.next()) return false;
  qDebug() << "Table m_tableNameSettings is not created";
  query.finish();
  query.prepare(
      QString(
          "CREATE TABLE '%1' (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT,"
          "%4 INTEGER, %5 INTEGER, %6 INTEGER, %7 INTEGER);")
          .arg(m_tableNameSettings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field));

  if (!query.exec()) return false;
  qDebug() << "Table m_tableNameSettings is CREATED";

  query.prepare(QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7) VALUES(:id, "
                        ":default_color, :count_next_balls, :points_in_row, "
                        ":height_field, :width_field);")
                    .arg(m_tableNameSettings, m_tables->table_settings.id,
                         m_tables->table_settings.default_color,
                         m_tables->table_settings.count_next_balls,
                         m_tables->table_settings.points_in_row,
                         m_tables->table_settings.height_field,
                         m_tables->table_settings.width_field));

  query.bindValue(":id", 1);
  query.bindValue(":default_color", m_settings.m_default_color);
  query.bindValue(":count_next_balls", m_settings.m_count_next_balls);
  query.bindValue(":points_in_row", m_settings.m_points_in_row);
  query.bindValue(":height_field", m_settings.m_height_field);
  query.bindValue(":width_field", m_settings.m_width_field);
  if (!query.exec()) return false;
  qDebug() << "Values are inserted";
  return true;
}
