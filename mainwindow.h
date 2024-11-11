#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "table_view_model.h"

QT_BEGIN_NAMESPACE
class QTableView; // forward declaration
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);

private:
    QTableView *m_tableView;
    std::vector<std::string> m_filesInfo;
    TableViewModel m_tableModel;
    QLabel *m_label;
    void setLabel(const QString &text);
    void displayTableView(void);

};

#endif // MAINWINDOW_H
