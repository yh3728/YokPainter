#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <QObject>
#include <QWidget>

class SelectionBox : public QObject
{
    Q_OBJECT
public:
    explicit SelectionBox(QObject *parent = nullptr);

signals:
};

#endif // SELECTIONBOX_H
