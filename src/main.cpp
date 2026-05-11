#include <QCoreApplication>
#include <QDebug>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDebug>

#include <charconv>
#include <cstdint>
#include <string_view>
#include <optional>

namespace {

    struct ParseResult {
        bool ok = false;
        std::uint64_t value = 0;
    };

    // ----------------------------------------------
    // PARSE VALUE
    // ----------------------------------------------
    std::optional<std::uint64_t> parseUnsigned(QStringView text, int base)
    {
        const auto utf8 = text.toUtf8();
        const char* first = utf8.constData();
        const char* last = first + utf8.size();

        std::uint64_t value = 0;
        auto [ptr, ec] = std::from_chars(first, last, value, base);
        if (ec != std::errc{} || ptr != last) {
            return std::nullopt;
        }
        return value;
    }

    // ----------------------------------------------
    // BINARY CONVERT
    // ----------------------------------------------
    QString toBinary(std::uint64_t value, int width = 0)
    {
        QString out;
        do {
            out.prepend((value & 1ULL) ? QLatin1Char('1') : QLatin1Char('0'));
            value >>= 1ULL;
        } while (value != 0ULL);

        if (width > 0 && out.size() < width) {
            out = QString(width - out.size(), QLatin1Char('0')) + out;
        }
        return out;
    }

    // ----------------------------------------------
    // HEX CONVERT
    // ----------------------------------------------
    QString toHex(std::uint64_t value, int width = 0)
    {
        QString out = QString::number(value, 16).toUpper();
        if (width > 0 && out.size() < width) {
            out = QString(width - out.size(), QLatin1Char('0')) + out;
        }
        return out;
    }

    // ----------------------------------------------
    // PRINT VALUE
    // ----------------------------------------------
    void printValue(QTextStream& out, std::uint64_t value)
    {
        out << "dec: " << value << '\n';
        out << "hex: 0x" << toHex(value) << '\n';
        out << "bin: 0b" << toBinary(value) << '\n';
        out << "low byte: 0x" << toHex(value & 0xFFULL, 2) << '\n';
        out << "high byte: 0x" << toHex((value >> 8ULL) & 0xFFULL, 2) << '\n';
    }

} // end::namespace

// ----------------------------------------------
// MAIN
// ----------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("hex-converter");
    QCoreApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Hex/Bin/Dec Converter Plus");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption inputOption(
        {"i", "input"},
        "Input value, e.g. 42, 0x2A or 101010",
        "value"
    );

    QCommandLineOption fromOption(
        {"f", "from"},
        "Input base: dec, hex, bin",
        "base",
        "dec"
    );

    parser.addOption(inputOption);
    parser.addOption(fromOption);

    parser.process(app);

    const QString input = parser.value(inputOption);
    const QString from = parser.value(fromOption).toLower();

    if (input.isEmpty()) {
        QTextStream err(stderr);
        err << "Error: no input given.\n";
        err << "Example: hex-bin-dec-plus -i 2A -f hex\n";
        return 1;
    }

    std::optional<std::uint64_t> value;

    if (from == "dec") {
        value = parseUnsigned(input, 10);
    } else if (from == "hex") {
        value = parseUnsigned(input, 16);
    } else if (from == "bin") {
        value = parseUnsigned(input, 2);
    } else {
        QTextStream err(stderr);
        err << "Error: invalid base. Use dec, hex, or bin.\n";
        return 1;
    }

    if (!value.has_value()) {
        QTextStream err(stderr);
        err << "Error: could not parse input.\n";
        return 1;
    }

    QTextStream out(stdout);
    printValue(out, *value);
    return 0;
}