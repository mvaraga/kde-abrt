#ifndef CUSTOMSEARCHLINE_H
#define CUSTOMSEARCHLINE_H

#include <KListWidgetSearchLine>
#include <QListWidgetItem>

/**
 * This class is subclass from KListWidgetSearchLine, it extend it, because
 * we need custom filter for items. It is filtering items by Qt::UserRole
 */
class CustomSearchLine : public KListWidgetSearchLine
{

public:
    explicit CustomSearchLine(QWidget* parent = 0, QListWidget* listWidget = 0);

protected:
    virtual bool itemMatches(const QListWidgetItem* item, const QString& s) const;
};

#endif // CUSTOMSEARCHLINE_H
