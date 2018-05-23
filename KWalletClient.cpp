#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
#include <KLocalizedString>

#include "KWalletClient.hpp"

KWalletClient::KWalletClient(int &argc, char *argv[]) :
    QApplication(argc, argv),
    verbose(true),
    mode(NO_MODE),
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

    wallet = Wallet::openWallet(walletName, 0);

    switch(mode) {
        case Get:
            break;
        case Set:
            break;
        case NO_MODE:
        default:
            std::cout << "Unknown method encounterd. Aborting." << std::endl;
            exit(1);
    }
}

void KWalletClient::getCredentials(void)
{
    std::cout << "Getting credentials." << std::endl;

    quit();
}

void KWalletClient::setCredentials(void)
{
    std::cout << "Setting credentials." << std::endl;

    quit();
}

void KWalletClient::getPassword(void)
{
    std::cout << "Getting password." << std::endl;

    if (!wallet->setFolder(folderName)) {
        std::cout << i18n("The folder %1 could not be found.", folderName).toUtf8().constData() << std::endl;
        exit(1);
    }

    quit();
}

void KWalletClient::setPassword(void)
{
    std::cout << "Setting password." << std::endl;

    quit();
}
