#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>

#include "core/ConversionService.h"
#include "core/ByteInspector.h"

int main(int argc, char *argv[])
{
    // -- Qt base object for non gui app
    QCoreApplication app(argc, argv);

    // -- Meta info for --help and [--version
    QCoreApplication::setApplicationName("hexcon++");
    QCoreApplication::setApplicationVersion("0.0.2");

    // -- Parser for CLI args
    QCommandLineParser parser;
    parser.setApplicationDescription("Convert numbers between decimal, hexadecimal and binary");
    parser.addHelpOption();
    parser.addVersionOption();

    // -- Option: Number input arg -i / --input (expects number input)
    QCommandLineOption inputOption(
        {"i", "input"},
        "Input value, e.g. 42, 2A or 101010",
        "value"
    );

    // -- Option: Number base format -f / --from (define the from which base the conversion is made)
    QCommandLineOption fromOption(
        {"f", "from"},
        "Input base: dec, hex, bin",
        "base",
        "dec"
    );

    // -- Option: Byte count to inspect
    QCommandLineOption bytesOption(
    {"b", "bytes"},
    "How many bytes should be inspected for the value",
    "count",
    "8"
);

    // -- Add options to parser
    parser.addOption(inputOption);
    parser.addOption(fromOption);
    parser.addOption(bytesOption);


    // -- Process CLI args
    parser.process(app);

    // -- Read args into vars
    const QString inputText = parser.value(inputOption);
    const QString fromText = parser.value(fromOption);


    // -- Error if --input is empty
    if (inputText.isEmpty()) {
        QTextStream err(stderr);
        err << "Error: no input given.\n";
        return 1;
    }

    // -- Read byteCount from cli arg
    bool okBytes = false;
    const int byteCount = parser.value(bytesOption).toInt(&okBytes);

    // -- Error if byte count is invalid
    if (!okBytes || byteCount <= 0 || byteCount > 8) {
        QTextStream err(stderr);
        err << "Error: invalid byte count. Use a value between 1 and 8.\n";
        return 1;
    }


    QString inputBase;

    // -- Do conversion
    const ConversionResult conversion = ConversionService::convert(inputText, inputBase);

    if (!conversion.ok) {
        QTextStream err(stderr);
        err << "Error: " << conversion.errorMessage << '\n';
        return 1;
    }

    // -- Analyse Byte layouts
    const ByteInspectorResult bytes = ByteInspector::inspect(conversion.value, byteCount);

    // -- Console output
    QTextStream out(stdout);
    out << "dec: " << conversion.decimalText() << '\n';
    out << "hex: " << conversion.hexText() << '\n';
    out << "bin: " << conversion.binaryText() << '\n';
    out << "low byte: " << bytes.lowByte << '\n';
    out << "high byte: " << bytes.highByte << '\n';
    out << "bytes (be): " << bytes.bytesBigEndian.join(' ') << '\n';
    out << "bytes (le): " << bytes.bytesLittleEndian.join(' ') << '\n';
    out << "bits: " << bytes.bitGroups << '\n';

    return EXIT_SUCCESS;
}