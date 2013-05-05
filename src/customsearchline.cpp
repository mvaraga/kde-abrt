#include "customsearchline.h"

CustomSearchLine::CustomSearchLine(QWidget* parent, QListWidget* listWidget): KListWidgetSearchLine(parent, listWidget)
{

}

bool CustomSearchLine::itemMatches(const QListWidgetItem* item, const QString& s) const
{

    if (s.isEmpty())
        return true;

    if (item == 0)
        return false;

    return (item->data(Qt::UserRole).toString().indexOf(s, 0,
                                 caseSensitive() ? Qt::CaseSensitive : Qt::CaseInsensitive) >= 0);

}
