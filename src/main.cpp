#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>

#include "core/NumberBase.h"
#include "core/NumberFormatter.h"
#include "core/NumberParser.h"

int main(int argc, char *argv[])
{
    // Qt base object for non gui app
    QCoreApplication app(argc, argv);

    // Meta info for --help and --version
    QCoreApplication::setApplicationName("hex-bin-dec-plus");
    QCoreApplication::setApplicationVersion("0.1.0");

    // Parser for CLI args
    QCommandLineParser parser;
    parser.setApplicationDescription("Hex/Bin/Dec Converter Plus");
    parser.addHelpOption();
    parser.addVersionOption();

    // -i / --input (expects number input)
    QCommandLineOption inputOption(
        {"i", "input"},
        "Input value, e.g. 42, 2A or 101010",
        "value"
    );

    // -f / --from (define the from which base the conversion is made)
    QCommandLineOption fromOption(
        {"f", "from"},
        "Input base: dec, hex, bin",
        "base",
        "dec"
    );

    parser.addOption(inputOption);
    parser.addOption(fromOption);

    // Process CLI args
    parser.process(app);

    const QString inputText = parser.value(inputOption);
    const QString fromText = parser.value(fromOption);

    // Error if --input is empty
    if (inputText.isEmpty()) {
        QTextStream err(stderr);
        err << "Error: no input given.\n";
        return 1;
    }

    // Calc base from text input
    const NumberBase base = numberBaseFromString(fromText);

    // Convert text to number
    const auto parsed = NumberParser::parseUnsigned(inputText, base);

    // Error if parsed val is empty
    if (!parsed.has_value()) {
        QTextStream err(stderr);
        err << "Error: could not parse input.\n";
        return 1;
    }

    // Standard output on console
    QTextStream out(stdout);
    out << NumberFormatter::describeValue(*parsed) << '\n';
    out << "low byte: 0x" << NumberFormatter::toHex(*parsed & 0xFFULL, 2) << '\n';
    out << "high byte: 0x" << NumberFormatter::toHex((*parsed >> 8ULL) & 0xFFULL, 2) << '\n';

    return 0;
}