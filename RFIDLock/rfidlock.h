#ifndef RFIDLOCK_H
#define RFIDLOCK_H

#include <QMainWindow>

#include "banco_de_dados.h"
#include "sobre.h"
#include "websocket.h"

class RFIDLock : public QMainWindow
{
    Q_OBJECT

public:
    RFIDLock(QWidget *parent = nullptr);
    ~RFIDLock();
};
#endif // RFIDLOCK_H
