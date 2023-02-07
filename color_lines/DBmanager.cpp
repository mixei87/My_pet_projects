#include "DBmanager.h"

DBmanager::DBmanager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);
  m_tables = new _table_and_columns;
  if (m_db.open())
    qDebug() << "Database: connection ok";
  else
    qDebug() << "Error: fail connection with database";
  m_settings = Settings::getSettings();
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
  query.bindValue(":default_color", m_settings->default_color());
  query.bindValue(":count_next_balls", m_settings->count_next_balls());
  query.bindValue(":points_in_row", m_settings->points_in_row());
  query.bindValue(":height_field", m_settings->height_field());
  query.bindValue(":width_field", m_settings->width_field());
  query.bindValue(":game_is_started", m_settings->game_is_started());
  if (!query.exec()) return false;
  return true;
}

void DBmanager::selectSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("SELECT * FROM %1 WHERE id = 1;").arg(m_table_name_settings));
  if (!query.exec() || !query.next()) return;
  QSqlRecord rec = query.record();
  int name_default_color = rec.indexOf(m_tables->table_settings.default_color);
  int name_count_next_balls =
      rec.indexOf(m_tables->table_settings.count_next_balls);
  int name_points_in_row = rec.indexOf(m_tables->table_settings.points_in_row);
  int name_height_field = rec.indexOf(m_tables->table_settings.height_field);
  int name_width_field = rec.indexOf(m_tables->table_settings.width_field);
  int name_game_is_started =
      rec.indexOf(m_tables->table_settings.game_is_started);

  m_settings->setDefault_color(query.value(name_default_color).value<QColor>());
  m_settings->setCount_next_balls(query.value(name_count_next_balls).toInt());
  m_settings->setPoints_in_row(query.value(name_points_in_row).toInt());
  m_settings->setHeight_field(query.value(name_height_field).toInt());
  m_settings->setWidth_field(query.value(name_width_field).toInt());
  m_settings->setGame_is_started(query.value(name_game_is_started).toInt());
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
  for (int i = 0; i < m_settings->board_size(); ++i) {
    id << i + 1;
    index << i;
    color << m_settings->default_color();
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

void DBmanager::selectGameBoardTable() {
  QSqlQuery query;
  query.prepare(QString("SELECT * FROM %1;").arg(m_table_name_gameboard));
  if (!query.exec()) return;

  QSqlRecord rec = query.record();
  int name_index = rec.indexOf(m_tables->table_gameboard.index);
  int name_color = rec.indexOf(m_tables->table_gameboard.color);
  while (query.next()) {
    m_settings->setField(query.value(name_index).toInt(),
                         query.value(name_color).value<QColor>());
  }
}

bool DBmanager::updateGameboardTable() {
  std::vector<std::pair<QColor, QString>> field = m_settings->field();
  bool isUpdate = true && field.size();

  for (size_t index = 0; index < field.size(); ++index) {
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET %2 = :color WHERE %3 = :index;")
                      .arg(m_table_name_gameboard,
                           m_tables->table_gameboard.color,
                           m_tables->table_gameboard.index));
    query.bindValue(":index", static_cast<int>(index));
    query.bindValue(":color", field[index].first);
    if (!query.exec()) isUpdate = false;
  }
  return isUpdate;
}
