#include "DBmanager.h"

DBmanager::DBmanager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);
  m_tables = new _table_and_columns;
  if (m_db.open())
    qDebug() << "Database: connection ok";
  else
    qDebug() << "Error: fail connection with database";
  if (isTableNotExist(m_table_name_settings)) {
    if (createSettingsTable()) insertSettingsTable();
  }
  if (isTableNotExist(m_table_name_gameboard)) {
    qDebug() << "begin create GameboardTable";
    if (createGameboardTable()) {
      qDebug() << "begin insert in GameboardTable";
      insertGameboardTable();
    }
  }
}

DBmanager::~DBmanager() {
  delete m_tables;
  if (m_db.isOpen()) {
    m_db.close();
    qDebug() << "db is close";
  }
}

bool DBmanager::createSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString(
          "CREATE TABLE '%1' (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT,"
          "%4 INTEGER, %5 INTEGER, %6 INTEGER, %7 INTEGER, %8 BOOL);")
          .arg(m_table_name_settings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field,
               m_tables->table_settings.game_is_started));
  if (!query.exec()) return false;
  return true;
}

bool DBmanager::isTableNotExist(const QString &table) {
  QSqlQuery query;
  query.prepare(QString("SELECT name FROM sqlite_schema WHERE type = 'table' "
                        "AND name = '%1';")
                    .arg(table));
  query.exec();
  if (query.next()) return false;
  return true;
}

bool DBmanager::insertSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8) VALUES(:id, "
              ":default_color, :count_next_balls, :points_in_row, "
              ":height_field, :width_field, :game_is_started);")
          .arg(m_table_name_settings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field,
               m_tables->table_settings.game_is_started));

  query.bindValue(":id", 1);
  query.bindValue(":default_color", m_settings.m_default_color);
  query.bindValue(":count_next_balls", m_settings.m_count_next_balls);
  query.bindValue(":points_in_row", m_settings.m_points_in_row);
  query.bindValue(":height_field", m_settings.m_height_field);
  query.bindValue(":width_field", m_settings.m_width_field);
  query.bindValue(":game_is_started", m_settings.m_game_is_started);
  if (!query.exec()) return false;
  return true;
}

Settings &DBmanager::getSettings() {
  QSqlQuery query;
  query.prepare(
      QString("SELECT * FROM %1 WHERE id = 1;").arg(m_table_name_settings));
  if (!query.exec() || !query.next()) return m_settings;

  m_settings.m_default_color = query.value(1).value<QColor>();
  m_settings.m_count_next_balls = query.value(2).toInt();
  m_settings.m_points_in_row = query.value(3).toInt();
  m_settings.m_height_field = query.value(4).toInt();
  m_settings.m_width_field = query.value(5).toInt();
  return m_settings;
}

bool DBmanager::updateGameboardTable() {
  ;
  ;
  return true;
}

bool DBmanager::createGameboardTable() {
  QSqlQuery query;
  query.prepare(
      QString(
          "CREATE TABLE '%1' (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER,"
          "%4 TEXT);")
          .arg(m_table_name_gameboard, m_tables->table_gameboard.id,
               m_tables->table_gameboard.index,
               m_tables->table_gameboard.color));
  if (!query.exec()) return false;
  return true;
}

bool DBmanager::insertGameboardTable() {
  QVariantList id;
  QVariantList index;
  QVariantList color;
  for (int i = 0; i < m_settings.m_height_field * m_settings.m_width_field;
       ++i) {
    id << i + 1;
    index << i;
    color << m_settings.m_default_color;
  }

  QSqlQuery query;
  query.prepare(QString("INSERT INTO %1 (%2, %3, %4) VALUES(:id, "
                        ":index, :color);")
                    .arg(m_table_name_gameboard, m_tables->table_gameboard.id,
                         m_tables->table_gameboard.index,
                         m_tables->table_gameboard.color));
  query.addBindValue(id);
  query.addBindValue(index);
  query.addBindValue(color);

  if (!query.execBatch())
    qDebug() << query.lastError();
  else
    qDebug() << "insertGameboardTable is true";
  return true;
}
