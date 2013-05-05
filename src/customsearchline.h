#ifndef CUSTOMSEARCHLINE_H
#define CUSTOMSEARCHLINE_H

#include <KListWidgetSearchLine>
#include <QListWidgetItem>


class CustomSearchLine : public KListWidgetSearchLine
{

public:
    explicit CustomSearchLine(QWidget* parent = 0, QListWidget* listWidget = 0);

protected:
    virtual bool itemMatches(const QListWidgetItem* item, const QString& s) const;
};

#endif // CUSTOMSEARCHLINE_H
