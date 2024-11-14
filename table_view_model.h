#ifndef TABLE_VIEW_MODEL_H
#define TABLE_VIEW_MODEL_H

#include <QStandardItemModel>
#include <vector>
#include <string>
#include <memory>

class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    static const int m_nCols = 3;
    std::vector<std::string>* m_filesInfo;
    std::array<std::string, m_nCols + 1> m_headerFields = {"Path", "Uncompressed", "Compressed", ""};

public:
    explicit TableViewModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setFilesInfo(std::vector<std::string>* filesInfo);

    void update(void);
};

#endif // TABLE_VIEW_MODEL_H
