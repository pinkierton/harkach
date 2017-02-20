#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractListModel>
#include "Board.h"

class BoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BoardModel(QObject *parent = nullptr);
    ~BoardModel();

    enum BoardRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CategoryRole,
        DefaultNameRole,
        BumpLimitRole,
        PagesRole,
        EnableLikesRole,
        EnablePostingRole,
        EnableThreadTagsRole,
        SageRole,
        TripcodesRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    void setBoards(QList<Board*>&& boards);

    const QList<Board*> &getBoards() const noexcept;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Board*> mBoards;
};

#endif // BOARDMODEL_H
