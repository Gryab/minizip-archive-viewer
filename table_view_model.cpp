#include "table_view_model.h"

TableViewModel::TableViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

void TableViewModel::setFilesInfo(std::vector<std::string>* filesInfo)
{
    m_filesInfo = filesInfo;
}

int TableViewModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_filesInfo->size() / m_nCols;
}

int TableViewModel::columnCount(const QModelIndex &/*parent*/) const
{
    return m_nCols;
}

QVariant TableViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
#ifdef DEBUG
    qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);
#endif
    switch (role) {
        case Qt::DisplayRole:	// what to write
        {
            if(m_filesInfo->size() > col)
            {
                return QString(m_filesInfo->at(row * m_nCols + col).c_str());
            }
        }break;
        case Qt::FontRole:
        {
        }break;
        case Qt::BackgroundRole:
        {
        }break;
        case Qt::TextAlignmentRole:
        {
        }break;
        case Qt::CheckStateRole:	// checkbox
        {
        }break;
    }

    return QVariant();
}
QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
        {

            if(orientation == Qt::Horizontal)
            {
                return QString::fromStdString(m_headerFields.at(section < m_nCols? section : m_nCols));
            }
        } break;
    }
    return QVariant();
}

void TableViewModel::update(void)
{
    beginResetModel();
    emit dataChanged(index(0,0), index(m_filesInfo->size()/m_nCols, m_nCols));
    endResetModel();
}
