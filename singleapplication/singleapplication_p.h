
//
//  W A R N I N G !!!
//  -----------------
//
// This file is not part of the SingleApplication API. It is used purely as an
// implementation detail. This header file may change from version to
// version without notice, or may even be removed.
//

#ifndef SINGLEAPPLICATION_P_H
#define SINGLEAPPLICATION_P_H

#include <QtCore/QSharedMemory>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include "singleapplication.h"

struct InstancesInfo {
    bool primary;
    quint32 secondary;
    qint64 primaryPid;
};

class SingleApplicationPrivate : public QObject {
Q_OBJECT
public:
    enum ConnectionType : quint8 {
        InvalidConnection = 0,
        NewInstance = 1,
        SecondaryInstance = 2,
        Reconnect = 3
    };
    Q_DECLARE_PUBLIC(SingleApplication)

    SingleApplicationPrivate( SingleApplication *q_ptr );
     ~SingleApplicationPrivate();

    void genBlockServerName( int msecs );
    void startPrimary( bool resetMemory );
    void startSecondary();
    void connectToPrimary(int msecs, ConnectionType connectionType );
    qint64 primaryPid();

#ifdef Q_OS_UNIX
    void crashHandler();
    static void terminate( int signum );
#endif

    QSharedMemory *memory;
    SingleApplication *q_ptr;
    QLocalSocket *socket;
    QLocalServer *server;
    quint32 instanceNumber;
    QString blockServerName;
    SingleApplication::Options options;

public Q_SLOTS:
    void slotConnectionEstablished();
    void slotDataAvailable( QLocalSocket*, quint32 );
    void slotClientConnectionClosed( QLocalSocket*, quint32 );
};

#endif // SINGLEAPPLICATION_P_H
