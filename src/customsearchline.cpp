#include "customsearchline.h"

CustomSearchLine::CustomSearchLine(QWidget* parent, QListWidget* listWidget): KListWidgetSearchLine(parent, listWidget)
{

}

/**
 * This method matches item to string.
 * When @p item match @p s, it returns @c true
 *
 * @param item tested QListWidgetItem
 * @param s string from search line
 * 
 * @return true if item match string
 */
bool CustomSearchLine::itemMatches(const QListWidgetItem* item, const QString& s) const
{

    if (s.isEmpty())
        return true;

    if (item == 0)
        return false;

    return (item->data(Qt::UserRole).toString().indexOf(s, 0,
                                 caseSensitive() ? Qt::CaseSensitive : Qt::CaseInsensitive) >= 0);
}
