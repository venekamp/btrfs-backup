#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
#include <KLocalizedString>

#include "KWalletClient.hpp"

KWalletClient::KWalletClient(int &argc, char *argv[]) :
    QApplication(argc, argv),
    verbose(true),
    command(NO_COMMAND),
    wallet(nullptr)
{
    QTimerEvent *timerEvent = new QTimerEvent(100);
    postEvent(this, timerEvent);
}


void KWalletClient::timerEvent(QTimerEvent *event)
{
    QApplication::timerEvent(event);
    if (verbose) qDebug() << "timer event";

    auto wl = Wallet::walletList();
    if (wl.indexOf(walletName) == -1) {
        std::cout << i18n("Wallet '%1' could not be found.", walletName).toUtf8().constData() << std::endl;
        exit(1);
    } else {
        if (verbose) qDebug() << "standby opening wallet " << walletName;

        wallet = Wallet::openWallet(walletName, QApplication::desktop()->screen()->winId(), Wallet::Asynchronous);
        connect(wallet, SIGNAL(walletOpened(bool)), this, SLOT(walletOpened(bool)));
    }
}

void KWalletClient::walletOpened(bool success)
{
    if (!success) {
        std::cout << i18n("Failed to open wallet '%1'. Aborting", walletName).toUtf8().constData() << std::endl;
        exit(1);
    }

    switch(command) {
        case GetCredentials:
            getCredentials();
            break;
        case SetCredentials:
            setCredentials();
            break;
        case GetPassword:
            getPassword();
            break;
        case SetPassword:
            setPassword();
            break;
        default:
            std::cout << "Unknown method encounterd. Aborting." << std::endl;
            exit(1);
    }
}

void KWalletClient::getCredentials(void)
{
    std::cout << "Getting credentials." << std::endl;

    wallet = Wallet::openWallet(walletName, 0);

    quit();
}

void KWalletClient::setCredentials(void)
{
    std::cout << "Setting credentials." << std::endl;

    wallet = Wallet::openWallet(walletName, 0);

    quit();
}

void KWalletClient::getPassword(void)
{
    std::cout << "Getting password." << std::endl;

    wallet = Wallet::openWallet(walletName, 0);

    quit();
}

void KWalletClient::setPassword(void)
{
    std::cout << "Setting password." << std::endl;

    wallet = Wallet::openWallet(walletName, 0);

    quit();
}
