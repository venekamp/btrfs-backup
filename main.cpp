#include <iostream>
#include <QtCore>

#include <KLocalizedString>

#include "generated/app_meta_data.hpp"
#include "KWalletClient.hpp"


int parseCommandLine(KWalletClient &app, QCommandLineParser &parser) {
    QCommandLineOption setMode(QStringLiteral("set"), i18n("Set <entry> in <folder> of <wallet>. Values are read from standard input."));
    QCommandLineOption getMode(QStringLiteral("get"), i18n("Get key or key values pairs from <entry>."));

    parser.addPositionalArgument(QStringLiteral("wallet"), i18n("Wallet to query."));
    parser.addPositionalArgument(QStringLiteral("folder"), i18n("Folder to use."));
    parser.addPositionalArgument(QStringLiteral("entry"), i18n("Entry to use."));

    parser.addOption(getMode);
    parser.addOption(setMode);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);

    const QStringList args = parser.positionalArguments();

    if (args.length() == 2) {
        app.setWalletName(args[0]);
        app.setFolderName(args[1]);

        if (parser.isSet(setMode)) app.setCommand(KWalletClient::Set);
        if (parser.isSet(getMode)) app.setCommand(KWalletClient::Get);

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
