#include <iostream>
#include <QtCore>

#include <KLocalizedString>

#include "generated/app_meta_data.hpp"
#include "KWalletClient.hpp"


int parseCommandLine(KWalletClient &app, QCommandLineParser &parser) {
    QCommandLineOption setSMBCredentials(QStringLiteral("set-credentials"), i18n("Set the user credentials for accessing the SMB share."));
    QCommandLineOption getSMBCredentials(QStringLiteral("get-credentials"), i18n("Get the user credentials for accessing the SMB share."));
    QCommandLineOption setEncryptionPassword(QStringLiteral("set-password"), i18n("Set the password for accessing the encrypted backup disk."));
    QCommandLineOption getEncryptionPassword(QStringLiteral("get-password"), i18n("Get the password for accessing the encrypted backup disk."));

    parser.addPositionalArgument(QStringLiteral("wallet"), i18n("Wallet to query."));
    parser.addPositionalArgument(QStringLiteral("folder"), i18n("Folder to use."));

    parser.addOption(getSMBCredentials);
    parser.addOption(setSMBCredentials);
    parser.addOption(getEncryptionPassword);
    parser.addOption(setEncryptionPassword);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);

    const QStringList args = parser.positionalArguments();

    if (args.length() == 2) {
        app.setWalletName(args[0]);
        app.setFolderName(args[1]);

        if (parser.isSet(setSMBCredentials)) {
            app.setCommand(KWalletClient::SetCredentials);
        }

        if (parser.isSet(setEncryptionPassword)) {
            app.setCommand(KWalletClient::SetPassword);
        }

        if (parser.isSet(getSMBCredentials)) {
            app.setCommand(KWalletClient::GetCredentials);
        } else if (parser.isSet(getEncryptionPassword)) {
            app.setCommand(KWalletClient::GetPassword);
        }

        return app.exec();
    }

    std::cerr << "Expecting a <wallet>, <folder> and an option what to do." << std::endl;

    return 1;
}


/*
 * Main function.
 */
int main(int argc, char *argv[])
{
    KWalletClient app(argc, argv);

	QCoreApplication::setApplicationName(QStringLiteral(APP_NAME));
	QCoreApplication::setApplicationVersion(QStringLiteral(APP_VERSION));

	QCommandLineParser parser;

	parser.setApplicationDescription(QStringLiteral("Create backups at SURFsara. Backups are created on an encrypted\n"
            "disk. This disk is stored on a SMB share at SURFsara. For mounting\n"
            "the backup disk, user credentials are needed and to use the disk,\n"
            "a password needs to be provided."));

    return parseCommandLine(app, parser);
}
