#ifndef KWALLET_CLIENT_HPP
#define KWALLET_CLIENT_HPP

#include <QtDBus/QtDBus>
#include <QtCore>
#include <QJsonDocument>
#include <QtWidgets/QApplication>

#include <KWallet>

using namespace KWallet;

/* class KWalletClient : public QApplication { */
class KWalletClient : public QApplication {
    Q_OBJECT

    public:
        enum Command {
            NO_COMMAND,
            SetCredentials,
            GetCredentials,
            SetPassword,
            GetPassword
        };

        KWalletClient(int &, char**);

        void setCommand(Command command) {
            this->command = command;
        }

        void setWalletName(const QString &walletName) {
            this->walletName = walletName;
        }

        void setFolderName(const QString &folderName) {
            this->folderName = folderName;
        }

    private:
        bool verbose;
        QString walletName;
        QString folderName;
        Command command;
        Wallet *wallet;

        void timerEvent(QTimerEvent *) override;

        void setCredentials(void);
        void getCredentials(void);
        void setPassword(void);
        void getPassword(void);

    private Q_SLOTS:
        void walletOpened(bool);
};

#endif
