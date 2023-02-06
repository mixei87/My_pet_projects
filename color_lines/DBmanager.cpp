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
  QSqlQuery query("SELECT * FROM " + m_tableNameSettings + " WHERE id=1;");
  //  qDebug() << "default_color: " << query.value(0);
  //  qDebug() << "count_next_balls: " << query.value(1);
  //  qDebug() << "points_in_row: " << query.value(2);
  //  qDebug() << "height_field: " << query.value(3);
  //  qDebug() << "width_field: " << query.value(4);

  //  m_settings.m_default_color = QColor(query.value(0).toString());
  //  m_settings.m_count_next_balls = query.value(1).toInt();
  //  m_settings.m_points_in_row = query.value(2).toInt();
  //  m_settings.m_height_field = query.value(3).toInt();
  //  m_settings.m_width_field = query.value(4).toInt();
  return m_settings;
}

bool DBmanager::createSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("SELECT name FROM sqlite_schema WHERE type = 'table' "
              "AND name = tableNameSettings;"));
  qDebug() << "query.exec()" << query.exec();
  qDebug() << "query.next()" << query.next();
  //  query.prepare(
  //      "CREATE TABLE IF NOT EXISTS tableNameSettings (id INTEGER PRIMARY KEY
  //      " "AUTOINCREMENT, " "default_color TEXT, count_next_balls INTEGER,
  //      points_in_row INTEGER, " "height_field INTEGER, width_field
  //      INTEGER);");
  //  query.bindValue(":tableNameSettings", m_tableNameSettings);
  //  query.bindValue(":id", m_tables->table_settings.id);
  //  query.bindValue(":default_color", m_tables->table_settings.default_color);
  //  query.bindValue(":count_next_balls",
  //                  m_tables->table_settings.count_next_balls);
  //  query.bindValue(":points_in_row", m_tables->table_settings.points_in_row);
  //  query.bindValue(":height_field", m_tables->table_settings.height_field);
  //  query.bindValue(":width_field", m_tables->table_settings.width_field);
  //  if (!query.exec()) return false;

  //  query.prepare(
  //      "INSERT INTO tableNameSettings (id, default_color, count_next_balls, "
  //      "points_in_row, "
  //      "height_field, width_field) VALUES(1, \"Qt::black\", 3, "
  //      "5, 9, 9);");
  //  if (!query.exec()) return false;
  return true;
}
